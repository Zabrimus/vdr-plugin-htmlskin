/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  jsonutil.h
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#ifndef VDR_PLUGIN_WEBSKIN_JSONUTIL_H
#define VDR_PLUGIN_WEBSKIN_JSONUTIL_H

#include <jansson.h>
#include <vdr/channels.h>
#include <vdr/epg.h>
#include <vdr/timers.h>
#include <vdr/recording.h>

class JsonUtil {
public:
    static json_t* fromChannel(const cChannel* channel);
    static json_t* fromEvent(const cEvent* event);
    static json_t* fromTimer(const cTimer* timer);
    static json_t* fromRecording(const cRecording* recording);
    static json_t* fromRecordingInfo(const cRecordingInfo* recordingInfo);

    static void replaceKey(json_t* obj, const char* key, json_t* newObj);
    static void replaceKeyIndex(json_t* obj, const char* key, int index, json_t* newObj);
};


#endif //VDR_PLUGIN_WEBSKIN_JSONUTIL_H
