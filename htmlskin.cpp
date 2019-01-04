/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  htmlskin.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include <nanomsg/pipeline.h>
#include <string>

#include <vdr/skins.h>
#include <vdr/plugin.h>

#include "htmlskin.h"
#include "htmlskindisplaychannel.h"
#include "htmlskindisplaymenu.h"
#include "htmlskindisplayreplay.h"
#include "htmlskindisplayvolume.h"
#include "htmlskindisplaytracks.h"
#include "htmlskindisplaymessage.h"

char* cHtmlSkin::skinUrl;

cHtmlSkin* skin;

cHtmlSkin::cHtmlSkin() : cSkin("html-skin") {
    asprintf(&skinUrl, "file://%s%s", cPlugin::ResourceDirectory("htmlskin"), "/skin/classic.html");

    skin = this;

    // command socket

    auto commandUrl = std::string("ipc:///tmp/vdrosr_command.ipc");

    if ((commandSocketId = nn_socket(AF_SP, NN_REQ)) < 0) {
        esyslog("Unable to create socket");
    }

    if ((commandEndpointId = nn_connect(commandSocketId, commandUrl.c_str())) < 0) {
        esyslog("unable to connect nanomsg socket to %s\n", commandUrl.c_str());
    }

    // set timeout
    int to = 2000;
    nn_setsockopt (commandSocketId, NN_SOL_SOCKET, NN_RCVTIMEO, &to, sizeof (to));
    nn_setsockopt (commandSocketId, NN_SOL_SOCKET, NN_SNDTIMEO, &to, sizeof (to));

    loadSkinPage();
}

cHtmlSkin::~cHtmlSkin() {
    if (skinUrl != nullptr) {
        free(skinUrl);
    }
}

const char *cHtmlSkin::Description() {
    // return tr("VDR HTML Skin");
    return "VDR HTML Skin";
}

cSkinDisplayChannel *cHtmlSkin::DisplayChannel(bool WithInfo) {
    loadSkinPage();
    return new cHtmlSkinDisplayChannel(WithInfo);
}

cSkinDisplayMenu *cHtmlSkin::DisplayMenu() {
    loadSkinPage();
    return new cHtmlSkinDisplayMenu;
}

cSkinDisplayReplay *cHtmlSkin::DisplayReplay(bool ModeOnly) {
    loadSkinPage();
    return new cHtmlSkinDisplayReplay(ModeOnly);
}

cSkinDisplayVolume *cHtmlSkin::DisplayVolume() {
    loadSkinPage();
    return new cHtmlSkinDisplayVolume;
}

cSkinDisplayTracks *cHtmlSkin::DisplayTracks(const char *Title, int NumTracks, const char * const *Tracks) {
    loadSkinPage();
    return new cHtmlSkinDisplayTracks(Title, NumTracks, Tracks);
}

cSkinDisplayMessage *cHtmlSkin::DisplayMessage() {
    loadSkinPage();
    return new cHtmlSkinDisplayMessage;
}

bool cHtmlSkin::loadSkinPage() {
    std::string cmdUrl("URL ");
    cmdUrl.append(skinUrl);
    skin->sendCommand(cmdUrl.c_str());

    return true;
}

bool cHtmlSkin::hideBrowser() {
    return skin->sendCommand("PAUSE");
}

bool cHtmlSkin::showBrowser() {
    return skin->sendCommand("RESUME");
}

void cHtmlSkin::callJavascript(cString method, cString page, json_t* data) {
    // construct call
    char *datastr;
    if (DumpDebugData) {
        datastr = json_dumps(data, JSON_PRESERVE_ORDER | JSON_INDENT(2));
    } else {
        datastr = json_dumps(data, JSON_PRESERVE_ORDER);
    }

    char *cmd;
    asprintf(&cmd, "JS var _skinjson = %s;\nvar _skinpage = \"%s\";\n%s(_skinpage,_skinjson);", datastr, *page, *method);
    skin->sendCommand(cmd);
    free(cmd);
}

void cHtmlSkin::callRawJavascript(cString script) {
    char *cmd;
    asprintf(&cmd, "JS %s", *script);
    skin->sendCommand(cmd);
    free(cmd);
}

bool cHtmlSkin::setBrowserSize(int width, int height) {
    char *cmd;

    skin->hideBrowser();

    asprintf(&cmd, "SIZE %d %d", width, height);
    auto result = skin->sendCommand(cmd);
    free(cmd);

    skin->showBrowser();

    return result;
}

bool cHtmlSkin::setZoomLevel(double zoom) {
    char *cmd;

    asprintf(&cmd, "ZOOM %f", zoom);
    auto result = skin->sendCommand(cmd);
    free(cmd);

    return result;
}

bool cHtmlSkin::sendCommand(const char* command) {
    bool returnValue = true;

    dbgskin("Send command '%s'\n", command);

    char *response = nullptr;
    int bytes = -1;

    if ((bytes = nn_send(commandSocketId, command, strlen(command) + 1, 0)) < 0) {
        esyslog("Unable to send command...");
        return false;
    }

    if (bytes > 0 && (bytes = nn_recv(commandSocketId, &response, NN_MSG, 0)) < 0) {
        esyslog("Unable to read response...");
        returnValue = false;
    } else {
        dbgskin("Response received: '%s', %d\n", response, bytes);

        returnValue = strcasecmp(response, "ok") == 0;
    }

    if (response) {
        nn_freemsg(response);
    }

    return returnValue;
}

bool cHtmlSkin::sendKeyEvent(cString key) {
    char *cmd;

    asprintf(&cmd, "KEY %s", *key);
    auto result = skin->sendCommand(cmd);
    free(cmd);

    return result;
}