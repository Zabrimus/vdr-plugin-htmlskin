/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  browser.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/pipeline.h>
#include "browser.h"

bool DumpDebugData = true;

Browser *upd;

Browser::Browser(std::string ipcCommandFile, std::string ipcStreamFile) {
    // command socket
    auto commandUrl = std::string("ipc://");
    commandUrl.append(ipcCommandFile);

    if ((commandSocketId = nn_socket(AF_SP, NN_REQ)) < 0) {
        esyslog("Unable to create socket");
    }

    if ((commandEndpointId = nn_connect(commandSocketId, commandUrl.c_str())) < 0) {
        esyslog("unable to connect nanomsg socket to %s\n", commandUrl.c_str());
    }

    // set timeout
    int to = 2000;
    nn_setsockopt (commandSocketId, NN_SOL_SOCKET, NN_RCVTIMEO, &to, sizeof (to));
    nn_setsockopt (commandSocketId, NN_SOL_SOCKET, NN_SNDTIMEO, &to, sizeof (to));

    // update thread
    upd = this;

    // stream socket
    auto streamUrl = std::string("ipc://");
    streamUrl.append(ipcStreamFile);

    if ((streamSocketId = nn_socket(AF_SP, NN_PULL)) < 0) {
        esyslog("unable to create nanomsg socket");
    }

    if ((streamEndpointId = nn_connect(streamSocketId, streamUrl.c_str())) < 0) {
        esyslog("unable to connect nanomsg socket to %s", streamUrl.c_str());
    }

    showBrowser();

}

Browser::~Browser() {
    hideBrowser();

    nn_close(streamSocketId);
    nn_close(commandSocketId);
    stopUpdate();

    upd = nullptr;

    if (osd) {
        delete osd;
    }
}

bool Browser::loadPage(std::string url, int rootFontSize) {
    std::string cmdUrl("URL ");
    cmdUrl.append(url);

    sendCommand(cmdUrl.c_str());
    setRootFontSize(rootFontSize);

    return true;
}

bool Browser::hideBrowser() {
    return sendCommand("PAUSE");
}

bool Browser::showBrowser() {
    return sendCommand("RESUME");
}

void Browser::callJavascript(cString method, cString page, json_t* data) {
    // construct call
    char *datastr;
    if (DumpDebugData) {
        datastr = json_dumps(data, JSON_PRESERVE_ORDER | JSON_INDENT(2));
    } else {
        datastr = json_dumps(data, JSON_PRESERVE_ORDER);
    }

    char *cmd;
    asprintf(&cmd, "JS var _skinjson = %s;\nvar _skinpage = \"%s\";\n%s(_skinpage,_skinjson);", datastr, *page, *method);
    sendCommand(cmd);
    free(cmd);
}

void Browser::callRawJavascript(cString script) {
    char *cmd;
    asprintf(&cmd, "JS %s", *script);
    sendCommand(cmd);
    free(cmd);
}

bool Browser::setBrowserSize(int width, int height) {
    char *cmd;

    osdWidth = width;
    osdHeight = height;

    hideBrowser();

    asprintf(&cmd, "SIZE %d %d", osdWidth, osdHeight);
    auto result = sendCommand(cmd);
    free(cmd);

    showBrowser();

    return result;
}

bool Browser::setZoomLevel(double zoom) {
    char *cmd;

    asprintf(&cmd, "ZOOM %f", zoom);
    auto result = sendCommand(cmd);
    free(cmd);

    return result;
}

bool Browser::setRootFontSize(int px) {
    char *cmd;

    asprintf(&cmd, "document.getElementsByTagName('html').item(0).style.fontSize = '%dpx'", px);
    callRawJavascript(cmd);
    free(cmd);

    return true;
}

bool Browser::sendKeyEvent(cString key) {
    char *cmd;

    asprintf(&cmd, "KEY %s", *key);
    auto result = sendCommand(cmd);
    free(cmd);

    return result;
}

bool Browser::sendCommand(const char* command) {
    bool returnValue;

    dbgbrowser("Send command '%s'\n", command);

    char *response = nullptr;
    int bytes;

    if ((bytes = nn_send(commandSocketId, command, strlen(command) + 1, 0)) < 0) {
        esyslog("Unable to send command...");
        return false;
    }

    if (bytes > 0 && (bytes = nn_recv(commandSocketId, &response, NN_MSG, 0)) < 0) {
        esyslog("Unable to read response...");
        returnValue = false;
    } else {
        dbgbrowser("Response received: '%s', %d\n", response, bytes);

        returnValue = strcasecmp(response, "ok") == 0;
    }

    if (response) {
        nn_freemsg(response);
    }

    return returnValue;
}

void Browser::startUpdate(int left, int top, int width, int height) {
    setBrowserSize(width, height);

    // try to calculate an appropriate zoom level
    // Full HD is 1920 x 1080 = 2073600 Pixel
    auto newPixel = (double)width * (double)height;
    auto zoom = sqrt(newPixel / 2073600.0);
    setZoomLevel(zoom);

    osd = cOsdProvider::NewOsd(left, top);

    tArea Area = { 0, 0, width, height, 32 };
    osd->SetAreas(&Area, 1);

    cRect rect(0, 0, width, height);
    pixmap = dynamic_cast<cPixmapMemory *>(osd->CreatePixmap(0, rect, rect));

    isRunning = true;
    updateThread = new std::thread(readStream, pixmap);
}

void Browser::stopUpdate() {
    dbgbrowser("Stop called\n");

    isRunning = false;
    updateThread->join();

    dbgbrowser("Finished stop\n");
}

void Browser::FlushOsd() {
    osd->Flush();
}

void Browser::readStream(cPixmapMemory *pixmap) {
    int bytes;

    // read count of dirty rects
    while(upd->isRunning) {
        unsigned long dirtyRecs = 0;
        if ((bytes = nn_recv(upd->streamSocketId, &dirtyRecs, sizeof(dirtyRecs), 0)) > 0) {
            dsyslog("Count of dirty recs: %lu\n", dirtyRecs);
            dbgbrowser("Count of dirty recs: %lu\n", dirtyRecs);

            for (unsigned long i = 0; i < dirtyRecs; ++i) {
                // read coordinates and size
                int x, y, w, h;
                if ((bytes = nn_recv(upd->streamSocketId, &x, sizeof(x), 0)) > 0) {
                }

                if ((bytes = nn_recv(upd->streamSocketId, &y, sizeof(y), 0)) > 0) {
                }

                if ((bytes = nn_recv(upd->streamSocketId, &w, sizeof(w), 0)) > 0) {
                }

                if ((bytes = nn_recv(upd->streamSocketId, &h, sizeof(h), 0)) > 0) {
                }

                dsyslog("Received dirty rec: (x %d, y %d) -> (w %d, h %d)\n", x, y, w, h);
                dbgbrowser("Received dirty rec: (x %d, y %d) -> (w %d, h %d)\n", x, y, w, h);

                cPixmapMemory::Lock();

                auto data = const_cast<uint8_t*>(pixmap->Data());

                for (int j = y; j < y + h; ++j) {
                    if ((bytes = nn_recv(upd->streamSocketId, data + 4 * (cOsd::OsdWidth() * j + x), 4 * w, 0)) > 0) {
                        // everything is fine
                    }
                }

                auto dirty1 = const_cast<cRect*>(&pixmap->DirtyDrawPort());
                auto dirty2 = const_cast<cRect*>(&pixmap->DirtyViewPort());

                // dirty1->Set(x, y, w, h);
                // dirty2->Set(x, y, w, h);

                dirty1->Set(0, 0, cOsd::OsdWidth(), cOsd::OsdHeight());
                dirty2->Set(0, 0, cOsd::OsdWidth(), cOsd::OsdHeight());

                cPixmapMemory::Unlock();

                upd->osd->Flush();
            }
        }
    }

    dbgbrowser("Finish readStream\n");
}