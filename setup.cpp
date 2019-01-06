/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  setup.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include "setup.h"
#include "config.h"

SkinhtmlSetup::SkinhtmlSetup() {
    tmpHtmlskinConfig = htmlskinConfig;
    Setup();
}

SkinhtmlSetup::~SkinhtmlSetup() {
}

void SkinhtmlSetup::Setup() {
    Add(new cMenuEditIntItem(tr("Font size in pixel"), &tmpHtmlskinConfig.rootFontSize));
}

eOSState SkinhtmlSetup::ProcessKey(eKeys Key) {
    eOSState state = cOsdMenu::ProcessKey(Key);

    if (state == osUnknown) {
        switch (Key) {
            case kOk:
                Store();
                state = osBack;
                break;

            case kBack:
                state = osBack;
                break;

            default: break;
        }
    }

    return state;
}

void SkinhtmlSetup::Store() {
    htmlskinConfig = tmpHtmlskinConfig;
    SetupStore("RootFontSize", tmpHtmlskinConfig.rootFontSize);
}
