/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  setup.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef VDR_PLUGIN_HTMLSKIN_SETUP_H
#define VDR_PLUGIN_HTMLSKIN_SETUP_H

#include <vdr/menu.h>
#include "config.h"

class SkinhtmlSetup : public cMenuSetupPage
{

private:
    cHtmlSkinConfig tmpHtmlskinConfig;
    void Setup();

protected:
    virtual eOSState ProcessKey(eKeys Key);
    virtual void Store();

public:
    SkinhtmlSetup();
    virtual ~SkinhtmlSetup();
};


#endif //VDR_PLUGIN_HTMLSKIN_SETUP_H
