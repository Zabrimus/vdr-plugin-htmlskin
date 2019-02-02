/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  browser.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef BROWSER_H
#define BROWSER_H

#include <string>
#include <vdr/tools.h>
#include <jansson.h>
#include <thread>
#include <vdr/osd.h>

// to enable much more debug data output to stderr, set this variable to true
extern bool DumpDebugData;
#define dbgbrowser(a...) if (DumpDebugData) fprintf(stderr, a)

class Browser {

public:
    Browser(std::string ipcCommandFile, std::string ipcStreamFile);
    ~Browser();

    bool loadPage(std::string url, int rootFontSize);

    bool hideBrowser();
    bool showBrowser();

    bool setBrowserSize(int width, int height);
    bool setZoomLevel(double zoom);
    bool setRootFontSize(int px);

    // TODO sendKeyEvent is currently not working in CEF. I don't know what exactly is wrong.
    bool sendKeyEvent(cString key);

    void callJavascript(cString method, cString page, json_t* data);
    void callRawJavascript(cString script);

    void startUpdate(int left, int top, int width, int height);
    void stopUpdate();
    void FlushOsd();

private:
    std::thread *updateThread;
    cPixmapMemory *pixmap;
    bool isRunning;

    cOsd* osd;
    int osdWidth;
    int osdHeight;

    int commandSocketId;
    int commandEndpointId;

    int streamSocketId;
    int streamEndpointId;

    bool sendCommand(const char* command);
    static void readStream(cPixmapMemory *pixmap);
};


#endif // BROWSER_H
