#pragma once

#include "common/ITypes.h"  // UInt32

#include <string>  // string


namespace iEquip_SoulSeeker
{
	extern bool GIST;
	extern UInt32 GISTIndex;

	bool checkForGIST();
	std::string boolToString(bool a_bool);
	std::string numToHexString(long a_num, int a_bytes);
}