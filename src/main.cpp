#include "common/IDebugLog.h"  // gLog, IDebugLog
#include "common/ITypes.h"  // UInt32
#include "skse/PluginAPI.h"  // PluginHandle, SKSEPapyrusInterface, SKSEInterface, PluginInfo, SKSEMessagingInterface
#include "skse/skse_version.h"  // RUNTIME_VERSION

#include <ShlObj.h>  // CSIDL_MYDOCUMENTS
#include <string>  // string

#include "iEquip_SoulSeeker.h"  // RegisterFuncs
#include "Utility.h"  // checkForGIST
#include "SoulGem.h"  // gemUtil


static PluginHandle	g_pluginHandle = kPluginHandle_Invalid;
static SKSEPapyrusInterface* g_papyrus = 0;
static SKSEMessagingInterface* g_messaging = 0;
iEquip_SoulSeeker::GemUtil iEquip_SoulSeeker::gemUtil;


void MessageHandler(SKSEMessagingInterface::Message * a_msg)
{
	switch (a_msg->type) {
	case SKSEMessagingInterface::kMessage_DataLoaded:
	{
#if 0
		_DMESSAGE("Data loaded!");
		if (iEquip_SoulSeeker::checkForGIST()) {
			_DMESSAGE("GIST present\n");
			iEquip_SoulSeeker::gemUtil.GISTFound();
		} else {
			_DMESSAGE("GIST not found\n");
		}
#endif
		break;
	}
	}
}


extern "C" {
	bool SKSEPlugin_Query(const SKSEInterface* a_skse, PluginInfo* a_info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\iEquip_SoulSeeker.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_Warning);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		_MESSAGE("iEquip_SoulSeeker");

		// populate info structure
		a_info->infoVersion = PluginInfo::kInfoVersion;
		a_info->name = "iEquip_SoulSeeker";
		a_info->version = 1;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = a_skse->GetPluginHandle();

		if (a_skse->isEditor) {
			_FATALERROR("Loaded in editor, marking as incompatible");
			return false;
		} else if (a_skse->runtimeVersion != RUNTIME_VERSION_1_9_32_0) {
			_FATALERROR("Unsupported runtime version %08X", a_skse->runtimeVersion);
			return false;
		}

		// supported runtime version
		return true;
	}


	bool SKSEPlugin_Load(const SKSEInterface* a_skse)
	{
		_MESSAGE("iEquip_SoulSeeker loaded");

		g_papyrus = (SKSEPapyrusInterface *)a_skse->QueryInterface(kInterface_Papyrus);

		//Check if the function registration was a success...
		bool btest = g_papyrus->Register(iEquip_SoulSeeker::RegisterFuncs);

		if (btest) {
			_MESSAGE("Papyrus registration succeeded!\n");
			g_messaging = (SKSEMessagingInterface *)a_skse->QueryInterface(kInterface_Messaging);
			g_messaging->RegisterListener(g_pluginHandle, "SKSE", MessageHandler);
		} else {
			_ERROR("Papyrus registration failed!");
		}

		return true;
	}
};
