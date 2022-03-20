#include <skse64/PluginAPI.h>
#include <skse64/GameAPI.h>

extern "C" {
    bool SKSEPlugin_Query(const SKSEInterface*, PluginInfo* info) {
        info->infoVersion = PluginInfo::kInfoVersion;
        info->name = "ExamplePlugin";
        info->version = 1;
        return true;
    }

    bool SKSEPlugin_Load(const SKSEInterface*) {
        Console_Print("Hello from a basic SKSE64 plugin!");
        return true;
    }
}