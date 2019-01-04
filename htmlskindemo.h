/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindemo.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef HTMLSKINDEMO_H
#define HTMLSKINDEMO_H

#include <vdr/osdbase.h>
#include <vdr/menu.h>

class cHtmlSkinDemoMenu: public cOsdMenu {
public:
    cHtmlSkinDemoMenu(const char* title);
    virtual ~cHtmlSkinDemoMenu();
    virtual eOSState ProcessKey(eKeys key);

private:

};

class cHtmlSkinDemoPage: public cOsdMenu {
public:
    cHtmlSkinDemoPage(const char* title, int demo);
    ~cHtmlSkinDemoPage();
    virtual eOSState ProcessKey(eKeys key);

private:
    int number;
};


#endif // HTMLSKINDEMO_H
