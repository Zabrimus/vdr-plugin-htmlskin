/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplayreplay.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <vdr/skins.h>
#include "htmlskindisplayreplay.h"
#include "htmlskin.h"
#include "JsonUtil.h"

cHtmlSkinDisplayReplay::cHtmlSkinDisplayReplay(bool ModeOnly) {
    dbgskin("Skin:cHtmlSkinDisplayReplay::Show(%d)\n", ModeOnly);

    doFlush = true;
    data = json_object();

    browser->startUpdate(cOsd::OsdLeft(), cOsd::OsdTop(), cOsd::OsdWidth(), cOsd::OsdHeight());
}

cHtmlSkinDisplayReplay::~cHtmlSkinDisplayReplay() {
    dbgskin("Skin:cHtmlSkinDisplayReplay::Hide\n");
}

void cHtmlSkinDisplayReplay::SetTitle(const char *Title) {
    dbgskin("Skin:cHtmlSkinDisplayReplay::SetTitle(%s)\n", Title);

    doFlush = true;
    const char* key = "title";
    // JsonUtil::replaceKey(data, key, json_pack("{ss}", "title", Title));
    JsonUtil::replaceKey(data, key, json_string(Title));
}

void cHtmlSkinDisplayReplay::SetMode(bool Play, bool Forward, int Speed) {
    dbgskin("Skin:cHtmlSkinDisplayReplay::SetMode(%d, %d, %d)\n", Play, Forward, Speed);

    doFlush = true;
    const char* key = "mode";
    JsonUtil::replaceKey(data, key, json_pack("{sb,sb,si}", "play", Play, "forward", Forward, "speed", Speed));
}

void cHtmlSkinDisplayReplay::SetProgress(int Current, int Total) {
    dbgskin("Skin:cHtmlSkinDisplayReplay::SetProgress(%d, %d)\n", Current, Total);

    doFlush = true;
    const char* key = "progress";
    JsonUtil::replaceKey(data, key, json_pack("{si,si}", "current", Current, "total", Total));
}

void cHtmlSkinDisplayReplay::SetCurrent(const char *Current) {
    dbgskin("Skin:cHtmlSkinDisplayReplay::SetCurrent(%s)\n", Current);

    doFlush = true;
    const char* key = "current";
    JsonUtil::replaceKey(data, key, json_string(Current));
}

void cHtmlSkinDisplayReplay::SetTotal(const char *Total) {
    dbgskin("Skin:cHtmlSkinDisplayReplay::SetTotal(%s)\n", Total);

    doFlush = true;
    const char* key = "total";
    JsonUtil::replaceKey(data, key, json_string(Total));
}

void cHtmlSkinDisplayReplay::SetJump(const char *Jump) {
    dbgskin("Skin:cHtmlSkinDisplayReplay::SetJump(%s)\n", Jump);

    doFlush = true;
    const char* key = "jump";
    JsonUtil::replaceKey(data, key, json_string(Jump));
}

void cHtmlSkinDisplayReplay::SetMessage(eMessageType Type, const char *Text) {
    dbgskin("Skin:cHtmlSkinDisplayReplay::SetMessage(%s)\n", Text);

    doFlush = true;
    const char* key = "message";
    JsonUtil::replaceKey(data, key, json_pack("{ss,si}", "text", Text, "type", Type));
}

void cHtmlSkinDisplayReplay::Flush() {
    dbgskin("Skin:cHtmlSkinDisplayReplay::Flush\n");

    if (doFlush) {
        browser->callJavascript(cString("showPage"), cString("displayreplay"), data);
    }

    doFlush = false;
}
