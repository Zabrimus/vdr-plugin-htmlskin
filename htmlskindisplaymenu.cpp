/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplaymenu.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <vdr/skins.h>
#include <vdr/timers.h>
#include <vdr/device.h>
#include "htmlskin.h"
#include "htmlskindisplaymenu.h"
#include "JsonUtil.h"
#include "config.h"

cHtmlSkinDisplayMenu::cHtmlSkinDisplayMenu() {
    dbgskin("Skin:cHtmlSkinDisplayMenu::Show\n");

    doFlush = true;
    data = json_object();

    browser->startUpdate(cOsd::OsdLeft(), cOsd::OsdTop(), cOsd::OsdWidth(), cOsd::OsdHeight());
}

cHtmlSkinDisplayMenu::~cHtmlSkinDisplayMenu() {
    dbgskin("Skin:cHtmlSkinDisplayMenu::Hide\n");
}

void cHtmlSkinDisplayMenu::Scroll(bool Up, bool Page) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::Scroll(%d, %d)\n", Up, Page);
}

int cHtmlSkinDisplayMenu::MaxItems() {
    dbgskin("Skin:cHtmlSkinDisplayMenu::MaxItems\n");

    int Width;
    int Height;
    double Aspect;
    cDevice::PrimaryDevice()->GetOsdSize(Width, Height, Aspect);

    int h = (int) ( (double)cOsd::OsdHeight() * 1080.0 / (double)Height);
    return (4 * h) / (5 * htmlskinConfig.rootFontSize);
}

void cHtmlSkinDisplayMenu::Clear() {
    dbgskin("Skin:cHtmlSkinDisplayMenu::Clear\n");

    doFlush = true;

    const char *keyItem = "items";
    JsonUtil::replaceKey(data, keyItem, json_array());

    const char *keyItemTimer = "itemTimer";
    JsonUtil::replaceKey(data, keyItemTimer, json_array());

    const char *keyItemChannel = "itemChannel";
    JsonUtil::replaceKey(data, keyItemChannel, json_array());

    const char *keyItemRecording = "itemRecording";
    JsonUtil::replaceKey(data, keyItemRecording, json_array());

    const char *keyItemEvent = "itemEvent";
    JsonUtil::replaceKey(data, keyItemEvent, json_array());

    const char *keyScrollbar = "scrollbar";
    JsonUtil::replaceKey(data, keyScrollbar, json_object());
}

void cHtmlSkinDisplayMenu::SetTitle(const char *Title) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetTitle(%s)\n", Title);

    doFlush = true;

    const char* key = "title";
    JsonUtil::replaceKey(data, key, json_string(Title));
}

void cHtmlSkinDisplayMenu::SetButtons(const char *Red, const char *Green, const char *Yellow, const char *Blue) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetButtons(%s, %s, %s, %s\n", Red, Green, Yellow, Blue);

    doFlush = true;

    const char* key = "buttons";
    JsonUtil::replaceKey(data, key, json_pack("{ss?:ss?:ss?:ss?}", "red", Red, "green", Green, "yellow", Yellow, "blue", Blue));
}

void cHtmlSkinDisplayMenu::SetMessage(eMessageType Type, const char *Text) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetMessage(%s)\n", Text);

    doFlush = true;

    const char* key = "message";
    JsonUtil::replaceKey(data, key, json_pack("{ss?:si}", "message", Text, "type",Type));
}

void cHtmlSkinDisplayMenu::SetItem(const char *Text, int Index, bool Current, bool Selectable) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetItem(%s, %d, %d, %d)\n", Text, Index, Current, Selectable);

    doFlush = true;

    const char* key = "items";
    JsonUtil::replaceKeyIndex(data, key, Index, json_pack("{ss?:si:sb:sb}", "text", Text, "index", Index, "current", Current, "selectable", Selectable));
}

void cHtmlSkinDisplayMenu::SetScrollbar(int Total, int Offset) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetScrollbar(%d, %d, %d)\n", Total, Offset, MaxItems());

    doFlush = true;

    const char* key = "scrollbar";
    JsonUtil::replaceKey(data, key, json_pack("{si,si,si}", "total", Total, "offset", Offset, "max", MaxItems()));
}

void cHtmlSkinDisplayMenu::SetEvent(const cEvent *Event) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetEvent(%s, %s)\n", Event ? Event->Description() : "<null>", Event ? Event->ShortText() : "<null>");

    doFlush = true;

    const char* key = "event";
    JsonUtil::replaceKey(data, key, json_pack("{so?}", "event", JsonUtil::fromEvent(Event)));
}

void cHtmlSkinDisplayMenu::SetRecording(const cRecording *Recording) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetRecording(%s, %s)\n", Recording ? Recording->FileName() : "<null>", Recording ? Recording->Name() : "<null>");

    printf("Set Recording....\n");
}

void cHtmlSkinDisplayMenu::SetText(const char *Text, bool FixedFont) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetText(%s, %d)\n", Text, FixedFont);

    doFlush = true;

    const char* key = "menutext";
    JsonUtil::replaceKey(data, key, json_pack("{ss,sb}", "text", Text, "fixedFont", FixedFont));
}

int cHtmlSkinDisplayMenu::GetTextAreaWidth() const {
    dbgskin("Skin:cHtmlSkinDisplayMenu::GetTextAreaWidth\n");
    return 0;
}

const cFont* cHtmlSkinDisplayMenu::GetTextAreaFont(bool FixedFont) const {
    return cFont::GetFont(FixedFont ? fontFix : fontOsd);    // dummy code
}

void cHtmlSkinDisplayMenu::SetMenuCategory(eMenuCategory MenuCategory) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetMenuCategory(%d)\n", MenuCategory);
    cSkinDisplayMenu::SetMenuCategory(MenuCategory);

    doFlush = true;

    const char* key = "menucategory";
    JsonUtil::replaceKey(data, key, json_pack("i", MenuCategory));
}

void cHtmlSkinDisplayMenu::SetTabs(int Tab1, int Tab2, int Tab3, int Tab4, int Tab5) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetTabs(%d,%d,%d,%d,%d)\n", Tab1, Tab2, Tab3, Tab4, Tab5);

    doFlush = true;

    const char* key = "tabs";
    JsonUtil::replaceKey(data, key, json_pack("[iiiii]", Tab1, Tab2, Tab3, Tab4, Tab5));
}

void cHtmlSkinDisplayMenu::SetMenuSortMode(eMenuSortMode MenuSortMode) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetMenuSortMode(%d)\n", MenuSortMode);
}

bool cHtmlSkinDisplayMenu::SetItemEvent(const cEvent *Event, int Index, bool Current, bool Selectable, const cChannel *Channel, bool WithDate, eTimerMatch TimerMatch, bool TimerActive) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetItemEvent(%s, %d, %d, %d, %s, %d, %d, %d)\n",
            Event ? Event->Title() : "<null>", Index, Current, Selectable, Channel ? Channel->ShortName() : "",
            WithDate, TimerMatch, TimerActive);

    doFlush = true;

    const char* key = "itemEvent";
    JsonUtil::replaceKeyIndex(data, key, Index, json_pack("{so?,so?,si,si,sb,sb,si,sb}", "item", JsonUtil::fromEvent(Event), "channel", JsonUtil::fromChannel(Channel), "index", Index, "current", Current, "selectable", Selectable, "withDate", WithDate, "timerMatch", TimerMatch, "timerActive", TimerActive));

    return false;
}

bool cHtmlSkinDisplayMenu::SetItemTimer(const cTimer *Timer, int Index, bool Current, bool Selectable) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetItemTimer(%d, %d, %d, %d)\n", Timer ? Timer->Id() : 0, Index, Current, Selectable);

    doFlush = true;

    const char* key = "itemTimer";
    JsonUtil::replaceKeyIndex(data, key, Index, json_pack("{so?,si,si,sb}", "item", JsonUtil::fromTimer(Timer), "index", Index, "current", Current, "selectable", Selectable));

    return false;
}

bool cHtmlSkinDisplayMenu::SetItemChannel(const cChannel *Channel, int Index, bool Current, bool Selectable, bool WithProvider) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetItemChannel(%s, %d, %d, %d, %d)\n", Channel ? Channel->ShortName() : "<null>", Index, Current, Selectable, WithProvider);

    doFlush = true;

    const char* key = "itemChannel";
    JsonUtil::replaceKeyIndex(data, key, Index, json_pack("{so?,si,si,sb,sb}", "item", JsonUtil::fromChannel(Channel), "index", Index, "current", Current, "selectable", Selectable, "withProvider", WithProvider));

    return false;
}

bool cHtmlSkinDisplayMenu::SetItemRecording(const cRecording *Recording, int Index, bool Current, bool Selectable, int Level, int Total, int New) {
    dbgskin("Skin:cHtmlSkinDisplayMenu::SetItemRecording(%d, %d, %d, %d, %d, %d, %d)\n", Recording? Recording->Id() : 0, Index, Current, Selectable, Level, Total, New);

    doFlush = true;

    const char* key = "itemRecording";
    JsonUtil::replaceKeyIndex(data, key, Index, json_pack("{so?,si,si,sb,si,si,si}", "item", JsonUtil::fromRecording(Recording), "index", Index, "current", Current, "selectable", Selectable, "level", Level, "total", Total, "new", New));

    return false;
}

void cHtmlSkinDisplayMenu::Flush() {
    dbgskin("Skin:cHtmlSkinDisplayMenu::Flush\n");

    if (doFlush) {
        browser->callJavascript(cString("showPage"), cString("displaymenubase"), data);

        // delete some objects
        json_object_del(data, "menutext");
    }

    doFlush = false;
}
