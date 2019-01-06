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

#include "config.h"


cHtmlSkinConfig::cHtmlSkinConfig(void) {
    // set default values
    rootFontSize = 16;
}

cHtmlSkinConfig::~cHtmlSkinConfig() = default;

bool cHtmlSkinConfig::SetupParse(const char *Name, const char *Value) {
    if      (strcmp(Name, "RootFontSize") == 0)   rootFontSize = atoi(Value);
    else return false;

    return true;
}

cHtmlSkinConfig htmlskinConfig;