/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplaychannel.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef HTMLSKINDISPLAYCHANNEL_H_
#define HTMLSKINDISPLAYCHANNEL_H_

#include <jansson.h>
#include <vdr/skins.h>
#include "osdupdatethread.h"

class cHtmlSkinDisplayChannel: public cSkinDisplayChannel, public cOsdUpdateThread {
private:
    bool doFlush;
    json_t* data;

public:
    cHtmlSkinDisplayChannel(bool WithInfo);

    ~cHtmlSkinDisplayChannel() override;
    void SetChannel(const cChannel *Channel, int Number) override;
    void SetEvents(const cEvent *Present, const cEvent *Following) override;
    void SetMessage(eMessageType Type, const char *Text) override;
    void Flush() override;
};

#endif /* HTMLSKINDISPLAYCHANNEL_H_ */
