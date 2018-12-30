/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplaymessage.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <vdr/skins.h>
#include "htmlskindisplaymessage.h"
#include "htmlskin.h"
#include "JsonUtil.h"

cHtmlSkinDisplayMessage::cHtmlSkinDisplayMessage() {
    dbgskin("Skin:cHtmlSkinDisplayMessage::Show\n");

    doFlush = true;
    data = json_object();

    startUpdate(cOsd::OsdWidth(), cOsd::OsdHeight());
}

cHtmlSkinDisplayMessage::~cHtmlSkinDisplayMessage() {
    dbgskin("Skin:cHtmlSkinDisplayMessage::Hide\n");
}

void cHtmlSkinDisplayMessage::SetMessage(eMessageType Type, const char *Text) {
    dbgskin("Skin:cHtmlSkinDisplayMessage::SetMessage(%s)\n", Text);

    doFlush = true;
    const char* key = "message";
    JsonUtil::replaceKey(data, key, json_pack("{ss:si}", "text", Text, "type", Type));
}

void cHtmlSkinDisplayMessage::Flush() {
    dbgskin("Skin:cHtmlSkinDisplayMessage::Flush\n");

    if (doFlush) {
        cHtmlSkin::callJavascript(cString("showPage"), cString("displaymessage"), data);
    }

    doFlush = false;
}
