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

// to enable much more debug data output to stderr, set this variable to true
static bool DumpDebugData = false;

#define dbgskin(a...) if (DumpDebugData) fprintf(stderr, a)

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

    static bool loadSkinPage();

    static bool hideBrowser();
    static bool showBrowser();

    static bool setBrowserSize(int width, int height);
    static bool setZoomLevel(double zoom);

    static void callJavascript(cString method, cString page, json_t* data);

private:
    static char* skinUrl;

    int commandSocketId;
    int commandEndpointId;

    bool sendCommand(const char* command);
};

extern cHtmlSkin* skin;

#endif /* HTMLSKIN_H_ */
