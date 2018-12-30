/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplaymessage.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef HTMLSKINDISPLAYMESSAGE_H_
#define HTMLSKINDISPLAYMESSAGE_H_

#include <jansson.h>
#include <vdr/skins.h>
#include "osdupdatethread.h"

class cHtmlSkinDisplayMessage: public cSkinDisplayMessage, public cOsdUpdateThread {
private:
    cOsd *osd;
    cPixmapMemory *pixmap;

    bool doFlush;
    json_t* data;

public:
    cHtmlSkinDisplayMessage();
    ~cHtmlSkinDisplayMessage() override;
    void SetMessage(eMessageType Type, const char *Text) override;
    void Flush() override;
};

#endif /* HTMLSKINDISPLAYMESSAGE_H_ */
