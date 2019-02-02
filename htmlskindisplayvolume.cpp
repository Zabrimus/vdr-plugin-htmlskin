/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplayvolume.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <vdr/skins.h>
#include "htmlskin.h"
#include "JsonUtil.h"
#include "htmlskindisplayvolume.h"

cHtmlSkinDisplayVolume::cHtmlSkinDisplayVolume(void) {
    dbgskin("Skin:cHtmlSkinDisplayVolume::Show\n");

    doFlush = true;
    data = json_object();

    browser->startUpdate(cOsd::OsdLeft(), cOsd::OsdTop(), cOsd::OsdWidth(), cOsd::OsdHeight());
}

cHtmlSkinDisplayVolume::~cHtmlSkinDisplayVolume() {
    dbgskin("Skin:cHtmlSkinDisplayVolume::Hide\n");

    browser->hideBrowser();
}

void cHtmlSkinDisplayVolume::SetVolume(int Current, int Total, bool Mute) {
    dbgskin("Skin:cHtmlSkinDisplayVolume::SetVolume(%d, %d, %d)\n", Current, Total, Mute);

    doFlush = true;
    const char* key = "volume";
    JsonUtil::replaceKey(data, key, json_pack("{si,si,sb}", "current", Current, "total", Total, "mute", Mute));
}

void cHtmlSkinDisplayVolume::Flush() {
    dbgskin("Skin:cHtmlSkinDisplayVolume::Flush\n");

    if (doFlush) {
        browser->callJavascript(cString("showPage"), cString("displayvolume"), data);
    }

    doFlush = false;
}
