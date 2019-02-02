/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskin.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef HTMLSKIN_H_
#define HTMLSKIN_H_

#include <jansson.h>
#include <vdr/skins.h>
#include "lib/browser.h"

// to enable much more debug data output to stderr, set this variable to true
extern bool DumpSkinDebugData;
#define dbgskin(a...) if (DumpSkinDebugData) fprintf(stderr, a)

class cHtmlSkin: public cSkin {
public:
    cHtmlSkin();
    ~cHtmlSkin() override;

    const char *Description() override;
    cSkinDisplayChannel *DisplayChannel(bool WithInfo) override;
    cSkinDisplayMenu *DisplayMenu() override;
    cSkinDisplayReplay *DisplayReplay(bool ModeOnly) override;
    cSkinDisplayVolume *DisplayVolume() override;
    cSkinDisplayTracks *DisplayTracks(const char *Title, int NumTracks, const char * const *Tracks) override;
    cSkinDisplayMessage *DisplayMessage() override;

private:
    char* skinUrl;
};

extern cHtmlSkin* skin;
extern Browser *browser;

#endif /* HTMLSKIN_H_ */
