/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplayreplay.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef HTMLSKINDISPLAYREPLAY_H_
#define HTMLSKINDISPLAYREPLAY_H_

#include <jansson.h>
#include <vdr/skins.h>
#include "osdupdatethread.h"

class cHtmlSkinDisplayReplay: public cSkinDisplayReplay, public cOsdUpdateThread {
private:
    cOsd *osd;
    cPixmapMemory *pixmap;

    bool doFlush;
    json_t* data;

public:
    explicit cHtmlSkinDisplayReplay(bool ModeOnly);
    ~cHtmlSkinDisplayReplay()  override;
    void SetTitle(const char *Title) override;
    void SetMode(bool Play, bool Forward, int Speed) override;
    void SetProgress(int Current, int Total) override;
    void SetCurrent(const char *Current) override;
    void SetTotal(const char *Total) override;
    void SetJump(const char *Jump) override;
    void SetMessage(eMessageType Type, const char *Text) override;
    void Flush() override;
};

#endif /* HTMLSKINDISPLAYREPLAY_H_ */
