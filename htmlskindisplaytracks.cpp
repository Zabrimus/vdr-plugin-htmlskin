/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplaytracks.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <vdr/skins.h>
#include "htmlskindisplaytracks.h"
#include "htmlskin.h"
#include "JsonUtil.h"


cHtmlSkinDisplayTracks::cHtmlSkinDisplayTracks(const char *Title, int NumTracks, const char * const *Tracks) {
    dbgskin("Skin:cHtmlSkinDisplayTracks::Show(%s, %d)\n", Title, NumTracks);

    startUpdate(cOsd::OsdWidth(), cOsd::OsdHeight());

    doFlush = true;
    data = json_object();

    const char* keyTitle = "title";
    JsonUtil::replaceKey(data, keyTitle, json_string(Title));

    const char* keyNumTracks = "numTracks";
    JsonUtil::replaceKey(data, keyNumTracks, json_integer(NumTracks));

    const char* keyTracks = "tracks";
    json_t* trackArr = json_array();

    for (int i = 0; i < NumTracks; ++i) {
        json_array_append_new(trackArr, json_string(Tracks[i]));
    }

    JsonUtil::replaceKey(data, keyTracks, trackArr);
}

cHtmlSkinDisplayTracks::~cHtmlSkinDisplayTracks() {
    dbgskin("Skin:cHtmlSkinDisplayTracks::Hide\n");
}

void cHtmlSkinDisplayTracks::SetTrack(int Index, const char * const *Tracks) {
    dbgskin("Skin:cHtmlSkinDisplayTracks::SetTrack(%d)\n", Index);

    doFlush = true;
    const char* key = "track";
    JsonUtil::replaceKey(data, key, json_pack("{ss:si}", "value", Tracks[Index], "index", Index));
}

void cHtmlSkinDisplayTracks::SetAudioChannel(int AudioChannel) {
    dbgskin("Skin:cHtmlSkinDisplayTracks::SetAudioChannel(%d)\n", AudioChannel);

    doFlush = true;
    const char* key = "audio";
    JsonUtil::replaceKey(data, key, json_pack("{si}", "channel", AudioChannel));
}

void cHtmlSkinDisplayTracks::Flush() {
    dbgskin("Skin:cHtmlSkinDisplayTracks::Flush\n");

    if (doFlush) {
        cHtmlSkin::callJavascript(cString("showPage"), cString("displaytracks"), data);
    }

    doFlush = false;
}
