#include "Utility.h"

#include "common/IDebugLog.h"  // gLog
#include "common/IErrors.h"  // ASSERT
#include "common/IFileStream.h"  // IFileStream
#include "common/ITypes.h"  // UInt32
#include "skse/GameData.h"  // DataHandler
#include "skse/GlobalLocks.h"  // g_loadGameLock

#include <minwindef.h>  // MAX_PATH
#include <ShlObj.h>  // SHGetFolderPath, CSIDL_LOCAL_APPDATA, SHGFP_TYPE_CURRENT
#include <winerror.h>  // SUCCEEDED

#include <cctype>  // toupper
#include <cstring>  // strlen
#include <ios>  // hex
#include <sstream>  // stringstream
#include <string>  // string, strlen


namespace iEquip_SoulSeeker
{
	bool GIST = false;
	UInt32 GISTindex = 0x0;


	bool checkForGIST()
	{
		char appdataPath[MAX_PATH];
		ASSERT(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, appdataPath)));

		std::string	modlistPath = appdataPath;
		modlistPath += "\\Skyrim Special Edition\\plugins.txt";

		// Parse mod list file to acquire GIST presence
		IFileStream modlistFile;
		UInt32 modIndex = 0x04;  // main, update, and DLC
		if (modlistFile.Open(modlistPath.c_str())) {
			while (!modlistFile.HitEOF()) {
				char buf[512];
				modlistFile.ReadString(buf, 512, '\n', '\r');

				// skip comments
				if (buf[0] == '#')
					continue;

				// Determine extension type
				std::string line = buf;

				// SE: added this
				if (line.length() > 0) {
					if (line.front() != '*')
						continue; // Skip not enabled files

					line = line.substr(1); // Remove the * from name
				}

				std::string::size_type lastDelim = line.rfind('.');
				if (lastDelim != std::string::npos) {
					std::string ext = line.substr(lastDelim);

					if (_stricmp(ext.c_str(), ".ESM") == 0 || _stricmp(ext.c_str(), ".ESP" ) == 0 || _stricmp(ext.c_str(), ".ESP") == 0) {
						++modIndex;
						std::string name = line.substr(0, lastDelim);
						if (name == "GIST soul trap") {
							GIST = true;
							GISTindex = modIndex;
							GISTindex *= 0x1000000;
							break;
						}
					}
				}
			}
		}

		modlistFile.Close();
		return GIST;
	}


	std::string boolToString(bool a_bool)
	{
		return a_bool ? "True" : "False";
	}


	std::string numToHexString(long a_num, int a_bytes)
	{
		// Convert to hex
		std::stringstream sstream;
		sstream << std::hex << a_num;
		std::string hexStr = sstream.str();

		// Convert lowercase characters to uppercase
		for (auto& c : hexStr) {
			c = toupper(c);
		}

		// Sign extension
		while (std::strlen(hexStr.c_str()) < a_bytes * 2) {
			hexStr = '0' + hexStr;
		}

		return hexStr;
	}
}