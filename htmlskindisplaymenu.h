/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskindisplaymenu.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef HTMLSKINDISPLAYMENU_H_
#define HTMLSKINDISPLAYMENU_H_

#include <jansson.h>
#include <vdr/skins.h>
#include "osdupdatethread.h"

class cHtmlSkinDisplayMenu: public cSkinDisplayMenu, public cOsdUpdateThread {
private:
    cOsd *osd;
    cPixmapMemory *pixmap;

    bool doFlush;
    json_t* data;

public:
    cHtmlSkinDisplayMenu();
    ~cHtmlSkinDisplayMenu() override;
    void Scroll(bool Up, bool Page) override;
    int MaxItems() override;
    void Clear() override;
    void SetTitle(const char *Title) override;
    void SetButtons(const char *Red, const char *Green = nullptr, const char *Yellow = nullptr, const char *Blue = nullptr) override;
    void SetMessage(eMessageType Type, const char *Text) override;
    void SetItem(const char *Text, int Index, bool Current, bool Selectable) override;
    void SetScrollbar(int Total, int Offset) override;
    void SetEvent(const cEvent *Event) override;
    void SetRecording(const cRecording *Recording) override;
    void SetText(const char *Text, bool FixedFont) override;
    int GetTextAreaWidth() const override;
    const cFont* GetTextAreaFont(bool FixedFont) const override;
    void Flush() override;
    void SetMenuCategory(eMenuCategory MenuCategory) override;
    void SetTabs(int Tab1, int Tab2 , int Tab3 = 0, int Tab4 = 0, int Tab5 = 0) override;
    void SetMenuSortMode(eMenuSortMode MenuSortMode) override;
    bool SetItemEvent(const cEvent *Event, int Index, bool Current, bool Selectable, const cChannel *Channel, bool WithDate, eTimerMatch TimerMatch, bool TimerActive) override;
    bool SetItemTimer(const cTimer *Timer, int Index, bool Current, bool Selectable) override;
    bool SetItemChannel(const cChannel *Channel, int Index, bool Current, bool Selectable, bool WithProvider) override;
    bool SetItemRecording(const cRecording *Recording, int Index, bool Current, bool Selectable, int Level, int Total, int New) override;

#if DEPRECATED_SKIN_SETITEMEVENT

    bool SetItemEvent(const cEvent *Event, int Index, bool Current, bool Selectable, const cChannel *Channel, bool WithDate, eTimerMatch TimerMatch) override { return SetItemEvent(Event, Index, Current, Selectable, Channel, WithDate, TimerMatch, true); }
    ///< This function is here for comaptibility with older plugins and may be removed
    ///< in a future version. Use the above version of SetItemEvent() with the TimerActive
    ///< parameter instead.
#endif
};

#endif /* HTMLSKINDISPLAYMENU_H_ */
