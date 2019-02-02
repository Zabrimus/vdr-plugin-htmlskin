/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplaychannel.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <stdlib.h>
#include <jansson.h>
#include <vdr/skins.h>
#include <vdr/interface.h>
#include <vdr/plugin.h>
#include "htmlskin.h"
#include "htmlskindisplaychannel.h"
#include "JsonUtil.h"

cHtmlSkinDisplayChannel::cHtmlSkinDisplayChannel(bool WithInfo) {
    dbgskin("Skin:cHtmlSkinDisplayChannel::Show\n");

    doFlush = true;
    data = json_object();

    browser->startUpdate(cOsd::OsdLeft(), cOsd::OsdTop(), cOsd::OsdWidth(), cOsd::OsdHeight());
}

cHtmlSkinDisplayChannel::~cHtmlSkinDisplayChannel() {
    dbgskin("Skin:cHtmlSkinDisplayChannel::Hide\n");

    json_decref(data);
}

void cHtmlSkinDisplayChannel::SetChannel(const cChannel *Channel, int Number) {
    dbgskin("Skin:cHtmlSkinDisplayChannel::DisplayChannel(%s, %d)\n", Channel ? Channel->Name() : "<null>", Channel ? Channel->Number() : -1);

    doFlush = true;
    const char* key = "channel";
    JsonUtil::replaceKey(data, key, JsonUtil::fromChannel(Channel));
}

void cHtmlSkinDisplayChannel::SetEvents(const cEvent *Present, const cEvent *Following) {
    dbgskin("Skin:cHtmlSkinDisplayChannel::SetEvents, Present(%s, %s)\n",
            Present ? (Present->Description() ? Present->Description() : "<null>") : "<null>",
            Present ? (Present->ShortText() ? Present->ShortText() : "<null>") : "<null>");
    dbgskin("Skin:cHtmlSkinDisplayChannel::SetEvents, Following(%s, %s)\n",
            Following ? Following->Description() : "<null>", Following ? Following->ShortText() : "<null>");

    doFlush = true;
    const char* key = "events";
    JsonUtil::replaceKey(data, key, json_pack("{so?:so?}", "present", JsonUtil::fromEvent(Present), "following", JsonUtil::fromEvent(Following)));
}


void cHtmlSkinDisplayChannel::SetMessage(eMessageType Type, const char *Text) {
    dbgskin("Skin:cHtmlSkinDisplayChannel::SetMessage(%s)\n", Text);

    doFlush = true;
    const char* key = "message";
    JsonUtil::replaceKey(data, key, json_pack("{ss:si}", "text", Text, "type", Type));
}

void cHtmlSkinDisplayChannel::Flush() {
    dbgskin("Skin:cHtmlSkinDisplayChannel::Flush\n");

    if (doFlush) {
        browser->callJavascript(cString("showPage"), cString("displaychannel"), data);
    }

    // FlushOsd();

    doFlush = false;
}
