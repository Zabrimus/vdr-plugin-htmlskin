/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindemo.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include "htmlskin.h"
#include "htmlskindemo.h"

//***************************************************************************
// main menu
//***************************************************************************
cHtmlSkinDemoMenu::cHtmlSkinDemoMenu(const char* title) : cOsdMenu(title) {
    Clear();

    cOsdMenu::Add(new cOsdItem(tr("Show HTML5 Test")));
    cOsdMenu::Add(new cOsdItem(tr("Show Kaleidoscope")));
    cOsdMenu::Add(new cOsdItem(tr("Show WEBGL Animation")));

    SetHelp(0, 0, 0, 0);
    Display();
}

cHtmlSkinDemoMenu::~cHtmlSkinDemoMenu() = default;

eOSState cHtmlSkinDemoMenu::ProcessKey(eKeys key) {
    eOSState state = cOsdMenu::ProcessKey(key);

    if (state != osUnknown)
        return state;

    switch (key) {
        case kOk: {
            if (Current() == 0) {
                // show HTML 5 Test
                return AddSubMenu(new cHtmlSkinDemoPage(cOsdMenu::Get(Current())->cOsdItem::Text(), 0));
            } else if (Current() == 1) {
                // show Kaleidoscope
                return AddSubMenu(new cHtmlSkinDemoPage(cOsdMenu::Get(Current())->cOsdItem::Text(), 1));
            } else if (Current() == 2) {
                // show WEBGL Animation
                return AddSubMenu(new cHtmlSkinDemoPage(cOsdMenu::Get(Current())->cOsdItem::Text(), 2));
            }

            return osEnd;
        }

        default:
            break;
    }

    return state;
}

//***************************************************************************
// demo menu
//***************************************************************************

cHtmlSkinDemoPage::cHtmlSkinDemoPage(const char* title, int nr) : cOsdMenu(title) {
    number = nr;
    Clear();

    SetCols(0, 0, 0, 0);
    SetHelp(0, 0, 0, 0);

    // a not so nice solution to trigger loading a new HTML page
    SetMenuCategory(eMenuCategory::mcUndefined);

    switch (number) {
        case 0:
            SetTitle("$>>>http://html5test.com");
            cOsdMenu::Add(new cOsdItem("not used"));
            break;
        case 1:
            SetTitle("$>>>http://www.chiptune.com/kaleidoscope/");
            cOsdMenu::Add(new cOsdItem("not used"));
            break;
        case 2:
            SetTitle("$>>>http://animateyourhtml5.appspot.com/part4-webgl/index.html");
            cOsdMenu::Add(new cOsdItem("not used"));
            break;
        default:
            break;
    }

    Display();
}

cHtmlSkinDemoPage::~cHtmlSkinDemoPage() = default;

eOSState cHtmlSkinDemoPage::ProcessKey(eKeys key) {
    // catch at first some VDR keys
    switch (key) {
        case kOk: {
            return osEnd;
        }

        case kLeft: {

        }

        case kRight: {
            /* TODO: do not work, because of the iframe cross-orgin exeception
            if (number == 2) {
                cHtmlSkin::callRawJavascript("document.getElementById(\"next\").click();");
                return osContinue;
            }
             */
        }

        case kUp: {

        }

        case kDown: {

        }

        default:
            break;
    }

    // do normal VDR processing
    eOSState state = cOsdMenu::ProcessKey(key);
    return state;
}
