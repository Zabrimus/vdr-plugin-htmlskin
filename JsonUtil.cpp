/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  jsonutil.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <jansson.h>
#include "JsonUtil.h"

json_t* JsonUtil::fromChannel(const cChannel* channel) {
    if (!channel) {
        return json_pack("{}");
    }

    return json_pack("{ss,ss,ss,ss,sb,si,si}",
            "name", channel->Name(),
            "shortName", channel->ShortName(),
            "provider", channel->Provider(),
            "portalName", channel->PortalName(),
            "groupSep", channel->GroupSep(),
            "number", channel->Number(),
            "lcn", channel->Lcn());
}

json_t* JsonUtil::fromEvent(const cEvent* event) {
    if (!event) {
        return json_pack("{}");
    }

    return json_pack("{ss?,ss?,ss?,si,ss?,sI,ss?,sI,ss?,ss?,si,sI,ss?,sI,ss?}",
            "title", event->Title(),
            "shortText", event->ShortText(),
            "description", event->Description(),
            "parentalRating", event->ParentalRating(),
            "parentalRatingStr", *event->GetParentalRatingString(),
            "startTime", event->StartTime(),
            "startTimeStr", *event->GetTimeString(),
            "endTime", event->EndTime(),
            "endTimeStr", *event->GetEndTimeString(),
            "startDateStr",*event->GetDateString(),
            "duration", event->Duration(),
            "vps", event->Vps(),
            "vpsStr", *event->GetVpsString(),
            "seen", event->Seen(),
            "Aux", event->Aux());
}

json_t* JsonUtil::fromTimer(const cTimer* timer) {
    if (!timer) {
        return json_pack("{}");
    }

    return json_pack("{si,sb,sb,si,so?,si,si,si,si,si,si,ss,si,ss,ss,sb,si,ss,so?,sb,sb,si,si,ss}",
        "id", timer->Id(),
        "recording", timer->Recording(),
        "pending", timer->Pending(),
        "flags", timer->Flags(),
        "channel", fromChannel(timer->Channel()),
        "day", timer->Day(),
        "weekdays", timer->WeekDays(),
        "start", timer->Start(),
        "stop", timer->Stop(),
        "priority", timer->Priority(),
        "lifetime", timer->Lifetime(),
        "file", timer->File(),
        "firstday", timer->FirstDay(),
        "aux", timer->Aux(),
        "remote", timer->Remote(),
        "local", timer->Local(),
        "deferred", timer->Deferred(),
        "description", *timer->ToDescr(),
        "event", fromEvent(timer->Event()),
        "single", timer->IsSingleEvent(),
        "expired", timer->Expired(),
        "stoptime", timer->StopTime(),
        "starttime", timer->StartTime(),
        "firstdayStr",*timer->PrintFirstDay());
}

json_t* JsonUtil::fromRecording(const cRecording* recording) {
    if (!recording) {
        return json_pack("{}");
    }

    return json_pack("{si,si,si,si,ss,ss,ss,ss,si,si,sb,si,si,sb,si,sb,si,si,sf,so?,sb,sb,si}",
        "lifetime", recording->Lifetime(),
        "priority", recording->Priority(),
        "start", recording->Start(),
        "id", recording->Id(),
        "name", recording->Name(),
        "basename", *recording->BaseName(),
        "filename", recording->FileName(),
        "folder", *recording->Folder(),
        "filesize", recording->FileSizeMB(),
        "resume", recording->GetResume(),
        "hasmarks", recording->HasMarks(),
        "hiararchylevel", recording->HierarchyLevels(),
        "index", recording->Index(),
        "isedited", recording->IsEdited(),
        "isinuse", recording->IsInUse(),
        "videofilesystem", recording->IsOnVideoDirectoryFileSystem(),
        "length", recording->LengthInSeconds(),
        "numframes", recording->NumFrames(),
        "framespersecond", recording->FramesPerSecond(),
        "info", fromRecordingInfo(recording->Info()),
        "isnew", recording->IsNew(),
        "ispes", recording->IsPesRecording(),
        "deleted", recording->Deleted());
}

json_t* JsonUtil::fromRecordingInfo(const cRecordingInfo* recordingInfo) {
    if (!recordingInfo) {
        return json_pack("{}");
    }

    return json_pack("{sf,ss,ss,ss,ss,ss,so?}",
        "framespersecond", recordingInfo->FramesPerSecond(),
        "aux", recordingInfo->Aux(),
        "title", recordingInfo->Title(),
        "description", recordingInfo->Description(),
        "shorttext", recordingInfo->ShortText(),
        "channelname", recordingInfo->ChannelName(),
        "event", fromEvent(recordingInfo->GetEvent()));
}

void JsonUtil::replaceKey(json_t* obj, const char* key, json_t* newObj) {
    json_t* old = json_object_get(obj, key);

    if (old != nullptr) {
        json_decref(old);
    }

    json_object_set(obj, key, newObj);
}

void JsonUtil::replaceKeyIndex(json_t* obj, const char* key, int index, json_t* newObj) {
    // ensure correct array size
    json_t* arr = json_object_get(obj, key);
    int size = json_array_size(arr);

    for (int i = size; i <= index; ++i) {
        json_array_append_new(arr, json_object());
    }

    // replace/insert new object
    json_array_set_new(arr, index, newObj);
}