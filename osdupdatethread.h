/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  osdupdatethread.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef OSDUPDATETHREAD_H
#define OSDUPDATETHREAD_H

#include <thread>
#include <vdr/skins.h>

class cOsdUpdateThread {
public:
    cOsdUpdateThread();
    ~cOsdUpdateThread();

    void startUpdate(int width, int height);
    void stopUpdate();

private:
    int streamSocketId;
    int streamEndpointId;

    std::thread *updateThread;
    bool isRunning;

    cOsd* osd;
    cPixmapMemory *pixmap;

    static void readStream(cPixmapMemory *pixmap);
};

#endif // OSDUPDATETHREAD_H
