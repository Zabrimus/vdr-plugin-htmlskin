/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  config.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef HTMLSKIN_CONFIG_H
#define HTMLSKIN_CONFIG_H

#include <vdr/themes.h>
#include <vdr/config.h>

class cHtmlSkinConfig {

public:
    cHtmlSkinConfig(void);
    ~cHtmlSkinConfig();

    bool SetupParse(const char *Name, const char *Value);

    int rootFontSize;
};

extern cHtmlSkinConfig htmlskinConfig;

#endif // HTMLSKIN_CONFIG_H
