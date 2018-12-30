/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplaytracks.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef HTMLSKINDISPLAYTRACKS_H_
#define HTMLSKINDISPLAYTRACKS_H_

#include <jansson.h>
#include <vdr/skins.h>
#include "osdupdatethread.h"

class cHtmlSkinDisplayTracks: public cSkinDisplayTracks, public cOsdUpdateThread {
private:
    cOsd *osd;
    cPixmapMemory *pixmap;

    bool doFlush;
    json_t* data;

public:
    cHtmlSkinDisplayTracks(const char *Title, int NumTracks, const char * const *Tracks);
    ~cHtmlSkinDisplayTracks() override;
    void SetTrack(int Index, const char * const *Tracks) override;
    void SetAudioChannel(int AudioChannel) override;
    void Flush() override;
};

#endif /* HTMLSKINDISPLAYTRACKS_H_ */
