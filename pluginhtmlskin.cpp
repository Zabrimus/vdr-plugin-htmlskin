/**
 *  VDR Skin Plugin which uses CEF OSR as rendering engine
 *
 *  pluginhtmlskin.cpp
 *
 *  (c) 2019 Robert Hannebauer
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 **/

#include <vdr/plugin.h>
#include "htmlskin.h"
#include "htmlskindemo.h"

static const char *VERSION = "0.0.1";
static const char *DESCRIPTION = "Enter description for 'htmlskin' plugin";
static const char *MAINMENUENTRY = "HTML Skin";

class htmlskin;

static const char *DUMMY = tr("WAT");

class cPluginHtmlSkin: public cPlugin {
private:
    // Add any member variables or functions you may need here.
    cHtmlSkin* skin;

public:
    cPluginHtmlSkin();
    ~cPluginHtmlSkin() override;

    const char *Version() override { return VERSION; }
    const char *Description() override { return DESCRIPTION; }
    const char *CommandLineHelp() override;
    bool ProcessArgs(int argc, char *argv[]) override;
    bool Initialize() override;
    bool Start() override;
    void Stop() override;
    void Housekeeping() override;
    void MainThreadHook() override;
    cString Active() override;
    time_t WakeupTime() override;
    const char *MainMenuEntry() override { return MAINMENUENTRY; }
    cOsdObject *MainMenuAction() override;
    cMenuSetupPage *SetupMenu() override;
    bool SetupParse(const char *Name, const char *Value) override;
    bool Service(const char *Id, void *Data = nullptr) override;
    const char **SVDRPHelpPages() override;
    cString SVDRPCommand(const char *Command, const char *Option, int &ReplyCode) override;
};

cPluginHtmlSkin::cPluginHtmlSkin() {
    // Initialize any member variables here.
    // DON'T DO ANYTHING ELSE THAT MAY HAVE SIDE EFFECTS, REQUIRE GLOBAL
    // VDR OBJECTS TO EXIST OR PRODUCE ANY OUTPUT!
    skin = nullptr;
}

cPluginHtmlSkin::~cPluginHtmlSkin() {
    // Clean up after yourself!
}

const char *cPluginHtmlSkin::CommandLineHelp() {
    // Return a string that describes all known command line options.
    return nullptr;
}

bool cPluginHtmlSkin::ProcessArgs(int argc, char *argv[]) {
    // Implement command line argument processing here if applicable.
    return true;
}

bool cPluginHtmlSkin::Initialize() {
    // Initialize any background activities the plugin shall perform.
    return true;
}

bool cPluginHtmlSkin::Start() {
    // Start any background activities the plugin shall perform.
    skin = new cHtmlSkin();

    return true;
}

void cPluginHtmlSkin::Stop() {
    // Stop any background activities the plugin is performing.
}

void cPluginHtmlSkin::Housekeeping() {
    // Perform any cleanup or other regular tasks.
}

void cPluginHtmlSkin::MainThreadHook() {
    // Perform actions in the context of the main program thread.
    // WARNING: Use with great care - see PLUGINS.html!
}

cString cPluginHtmlSkin::Active() {
    // Return a message string if shutdown should be postponed
    return nullptr;
}

time_t cPluginHtmlSkin::WakeupTime() {
    // Return custom wakeup time for shutdown script
    return 0;
}

cOsdObject *cPluginHtmlSkin::MainMenuAction() {
    return new cHtmlSkinDemoMenu("Html Skin Demo");
}

cMenuSetupPage *cPluginHtmlSkin::SetupMenu() {
    // Return a setup menu in case the plugin supports one.
    return nullptr;
}

bool cPluginHtmlSkin::SetupParse(const char *Name, const char *Value) {
    // Parse your own setup parameters and store their values.
    return false;
}

bool cPluginHtmlSkin::Service(const char *Id, void *Data) {
    // Handle custom service requests from other plugins
    return false;
}

const char **cPluginHtmlSkin::SVDRPHelpPages() {
    return nullptr;
}

cString cPluginHtmlSkin::SVDRPCommand(const char *Command, const char *Option, int &ReplyCode) {
    return nullptr;
}

VDRPLUGINCREATOR(cPluginHtmlSkin); // Don't touch this!
