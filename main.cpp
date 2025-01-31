#define WLR_USE_UNSTABLE

#include <hyprland/src/config/ConfigManager.hpp>
#include "globals.hpp"

#include "nstackLayout.hpp"

#include <unistd.h>
#include <thread>

// Methods
inline std::unique_ptr<CHyprNstackLayout> g_pNstackLayout;

// Do NOT change this function.
APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}


APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:orientation", SConfigValue{.strValue = "left"});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:new_on_top", SConfigValue{.intValue = 0});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:new_is_master", SConfigValue{.intValue = 1});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:no_gaps_when_only", SConfigValue{.intValue = 0});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:special_scale_factor", SConfigValue{.floatValue = 0.8f});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:inherit_fullscreen", SConfigValue{.intValue = 1});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:stacks", SConfigValue{.intValue = 2});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:center_single_master", SConfigValue{.intValue = 0});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:mfact", SConfigValue{.floatValue = 0.5f});
    g_pNstackLayout = std::make_unique<CHyprNstackLayout>();

    HyprlandAPI::addLayout(PHANDLE, "nstack", g_pNstackLayout.get());

    HyprlandAPI::reloadConfig();

    return {"N_Stack layout", "Plugin for column layout", "Zakk", "1.0"};
}

APICALL EXPORT void PLUGIN_EXIT() {
    HyprlandAPI::invokeHyprctlCommand("seterror", "disable");
}
