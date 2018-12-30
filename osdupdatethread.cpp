/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  osdupdatethread.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <byteswap.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>
#include <string>

#include "htmlskin.h"
#include "osdupdatethread.h"

cOsdUpdateThread *upd;

cOsdUpdateThread::cOsdUpdateThread() {
    dbgskin("Construct UpdateThread\n");

    upd = this;

    // stream socket
    auto streamUrl = std::string("ipc:///tmp/vdrosr_stream.ipc");

    if ((streamSocketId = nn_socket(AF_SP, NN_PULL)) < 0) {
        esyslog("unable to create nanomsg socket");
    }

    if ((streamEndpointId = nn_connect(streamSocketId, streamUrl.c_str())) < 0) {
        esyslog("unable to connect nanomsg socket to %s", streamUrl.c_str());
    }

    cHtmlSkin::showBrowser();

    dbgskin("Finish Construct UpdateThread\n");
}

cOsdUpdateThread::~cOsdUpdateThread() {
    dbgskin("Kill UpdateThread\n");

    cHtmlSkin::hideBrowser();

    nn_close(streamSocketId);
    stopUpdate();

    upd = nullptr;

    if (osd) {
        delete osd;
    }

    dbgskin("Finished kill UpdateThread\n");
}

void cOsdUpdateThread::startUpdate(int width, int height) {
    cHtmlSkin::setBrowserSize(width, height);

    osd = cOsdProvider::NewOsd(cOsd::OsdLeft(), cOsd::OsdTop());

    tArea Area = { 0, 0, cOsd::OsdWidth(), cOsd::OsdHeight(), 32 };
    osd->SetAreas(&Area, 1);

    cRect rect(0, 0, cOsd::OsdWidth(), cOsd::OsdHeight());
    pixmap = dynamic_cast<cPixmapMemory *>(osd->CreatePixmap(0, rect, rect));

    isRunning = true;
    updateThread = new std::thread(readStream, pixmap);
}

void cOsdUpdateThread::stopUpdate() {
    dbgskin("Stop called\n");

    isRunning = false;
    updateThread->join();

    dbgskin("Finished stop\n");
}

void cOsdUpdateThread::readStream(cPixmapMemory *pixmap) {
    int bytes;

    // read count of dirty rects
    while(upd->isRunning) {
        unsigned long dirtyRecs = 0;
        if ((bytes = nn_recv(upd->streamSocketId, &dirtyRecs, sizeof(dirtyRecs), 0)) > 0) {
            dsyslog("Count of dirty recs: %lu", dirtyRecs);

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

                dsyslog("Received dirty rec: (x %d, y %d) -> (w %d, h %d)",x,y,w,h);
                dbgskin("Received dirty rec: (x %d, y %d) -> (w %d, h %d)",x,y,w,h);

                {
                    // create empty image and fill the image data
                    cSize size(w, h);
                    cImage image(size, nullptr);

                    auto color = const_cast<tColor*>(image.Data());

                    for (int j = 0; j < h; ++j) {
                        if ((bytes = nn_recv(upd->streamSocketId, color + j * w, 4 * w, 0)) > 0) {
                            // everything is fine
                        }
                    }

                    // write image to pixmap
                    cPoint point(x,y);
                    pixmap->DrawImage(point, image);

                    upd->osd->Flush();
                }
            }
        }
    }

    dbgskin("Finish readStream\n");
}