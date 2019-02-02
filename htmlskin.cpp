/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskin.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/pipeline.h>
#include <string>

#include <vdr/skins.h>
#include <vdr/plugin.h>

#include "htmlskin.h"
#include "htmlskindisplaychannel.h"
#include "htmlskindisplaymenu.h"
#include "htmlskindisplayreplay.h"
#include "htmlskindisplayvolume.h"
#include "htmlskindisplaytracks.h"
#include "htmlskindisplaymessage.h"
#include "config.h"

bool DumpSkinDebugData = true;

cHtmlSkin* skin;
Browser *browser;

cHtmlSkin::cHtmlSkin() : cSkin("html-skin") {
    asprintf(&skinUrl, "file://%s%s", cPlugin::ResourceDirectory("htmlskin"), "/skin/classic.html");

    skin = this;

    browser = new Browser("/tmp/vdrosr_command.ipc", "/tmp/vdrosr_stream.ipc");
    browser->loadPage(skinUrl, htmlskinConfig.rootFontSize);
}

cHtmlSkin::~cHtmlSkin() {
    if (skinUrl != nullptr) {
        free(skinUrl);
    }

    if (browser) {
        delete browser;
    }

}

const char *cHtmlSkin::Description() {
    // return tr("VDR HTML Skin");
    return "VDR HTML Skin";
}

cSkinDisplayChannel *cHtmlSkin::DisplayChannel(bool WithInfo) {
    browser->loadPage(skinUrl, htmlskinConfig.rootFontSize);
    return new cHtmlSkinDisplayChannel(WithInfo);
}

cSkinDisplayMenu *cHtmlSkin::DisplayMenu() {
    browser->loadPage(skinUrl, htmlskinConfig.rootFontSize);
    return new cHtmlSkinDisplayMenu;
}

cSkinDisplayReplay *cHtmlSkin::DisplayReplay(bool ModeOnly) {
    browser->loadPage(skinUrl, htmlskinConfig.rootFontSize);
    return new cHtmlSkinDisplayReplay(ModeOnly);
}

cSkinDisplayVolume *cHtmlSkin::DisplayVolume() {
    browser->loadPage(skinUrl, htmlskinConfig.rootFontSize);
    return new cHtmlSkinDisplayVolume;
}

cSkinDisplayTracks *cHtmlSkin::DisplayTracks(const char *Title, int NumTracks, const char * const *Tracks) {
    browser->loadPage(skinUrl, htmlskinConfig.rootFontSize);
    return new cHtmlSkinDisplayTracks(Title, NumTracks, Tracks);
}

cSkinDisplayMessage *cHtmlSkin::DisplayMessage() {
    browser->loadPage(skinUrl, htmlskinConfig.rootFontSize);
    return new cHtmlSkinDisplayMessage;
}