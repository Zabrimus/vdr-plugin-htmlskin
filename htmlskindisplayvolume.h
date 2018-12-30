/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplayvolume.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef HTMLSKINDISPLAYVOLUME_H_
#define HTMLSKINDISPLAYVOLUME_H_

#include <jansson.h>
#include <vdr/skins.h>
#include "osdupdatethread.h"

class cHtmlSkinDisplayVolume: public cSkinDisplayVolume, public cOsdUpdateThread {
private:
    cOsd *osd;
    cPixmapMemory *pixmap;

    bool doFlush;
    json_t* data;

public:
    cHtmlSkinDisplayVolume();
    ~cHtmlSkinDisplayVolume() override;
    void SetVolume(int Current, int Total, bool Mute) override;
    void Flush() override;
};

#endif /* HTMLSKINDISPLAYVOLUME_H_ */
