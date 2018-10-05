#include "SoulGem.h"

#include "common/IDebugLog.h"  // gLog
#include "common/ITypes.h"  // UInt32
#include "skse/GameExtraData.h"  // InventoryEntryData

#include <vector>  // vector

#include "Utility.h"  // GIST, GISTIndex


namespace iEquip_SoulSeeker
{
	GemUtil::GemUtil()
	{
		fillCompatGems(kSoulSize_Petty, petty);
		fillCompatGems(kSoulSize_Lesser, lesser);
		fillCompatGems(kSoulSize_Common, common);
		fillCompatGems(kSoulSize_Greater, greater);
		fillCompatGems(kSoulSize_Grand, grand);
	}


	void GemUtil::GISTFound()
	{
		addGISTGems(kSoulSize_Petty, petty);
		addGISTGems(kSoulSize_Lesser, lesser);
		addGISTGems(kSoulSize_Common, common);
		addGISTGems(kSoulSize_Greater, greater);
		addGISTGems(kSoulSize_Grand, grand);
	}


	void GemUtil::fillCompatGems(UInt32 a_soulSize, GemInfo& a_gemInfo)
	{
		switch (a_soulSize) {
		case kSoulSize_Petty:
			a_gemInfo.compat.emplace_back(kSoulGem_PettyFilled);
			a_gemInfo.compat.emplace_back(kSoulGem_Petty);
			if (a_soulSize == kSoulSize_Petty) {
				a_gemInfo.maxFill = a_gemInfo.compat.size();
			}
		case kSoulSize_Lesser:
			a_gemInfo.compat.emplace_back(kSoulGem_LesserFilled);
			a_gemInfo.compat.emplace_back(kSoulGem_Lesser);
			if (a_soulSize == kSoulSize_Lesser) {
				a_gemInfo.maxFill = a_gemInfo.compat.size();
			}
		case kSoulSize_Common:
			a_gemInfo.compat.emplace_back(kSoulGem_CommonFilled);
			a_gemInfo.compat.emplace_back(kSoulGem_Common);
			if (a_soulSize == kSoulSize_Common) {
				a_gemInfo.maxFill = a_gemInfo.compat.size();
			}
		case kSoulSize_Greater:
			a_gemInfo.compat.emplace_back(kSoulGem_GreaterFilled);
			a_gemInfo.compat.emplace_back(kSoulGem_Greater);
			if (a_soulSize == kSoulSize_Greater) {
				a_gemInfo.maxFill = a_gemInfo.compat.size();
			}
		case kSoulSize_Grand:
			a_gemInfo.compat.emplace_back(kSoulGem_GrandFilled);
			a_gemInfo.compat.emplace_back(kSoulGem_Grand);
			a_gemInfo.compat.emplace_back(kSoulGem_BlackFilled);
			a_gemInfo.compat.emplace_back(kSoulGem_Black);
			a_gemInfo.compat.emplace_back(kSoulGem_AzurasStar);
			a_gemInfo.compat.emplace_back(kSoulGem_BlackStar);
			if (a_soulSize == kSoulSize_Grand) {
				a_gemInfo.maxFill = a_gemInfo.compat.size();
			}
			break;
		default:
			std::string msg = "ERROR: In GemUtil::fillCompatGems : Invalid soul size!" + numToHexString(a_soulSize, 4) + "\n";
			_ERROR(msg.c_str());
		}
	}


	void GemUtil::addGISTGems(UInt32 a_soulSize, GemInfo& a_gemInfo)
	{
		switch (a_soulSize) {
		case kSoulSize_Petty:
			a_gemInfo.compat.emplace_back(kSoulGem_GISTBlackFilledPetty + GISTindex);
			a_gemInfo.compat.emplace_back(kSoulGem_GISTGrandFilledPetty + GISTindex);
			a_gemInfo.compat.emplace_back(kSoulGem_GISTGreaterFilledPetty + GISTindex);
			a_gemInfo.compat.emplace_back(kSoulGem_GISTCommonFilledPetty + GISTindex);
			a_gemInfo.compat.emplace_back(kSoulGem_GISTLesserFilledPetty + GISTindex);
			break;
		case kSoulSize_Lesser:
			a_gemInfo.compat.emplace_back(kSoulGem_GISTBlackFilledLesser + GISTindex);
			a_gemInfo.compat.emplace_back(kSoulGem_GISTGrandFilledLesser + GISTindex);
			a_gemInfo.compat.emplace_back(kSoulGem_GISTGreaterFilledLesser + GISTindex);
			a_gemInfo.compat.emplace_back(kSoulGem_GISTCommonFilledLesser + GISTindex);
			break;
		case kSoulSize_Common:
			a_gemInfo.compat.emplace_back(kSoulGem_GISTBlackFilledCommon + GISTindex);
			a_gemInfo.compat.emplace_back(kSoulGem_GISTGrandFilledCommon + GISTindex);
			a_gemInfo.compat.emplace_back(kSoulGem_GISTGreaterFilledCommon + GISTindex);
			break;
		case kSoulSize_Greater:
			a_gemInfo.compat.emplace_back(kSoulGem_GISTBlackFilledGreater + GISTindex);
			a_gemInfo.compat.emplace_back(kSoulGem_GISTGrandFilledGreater + GISTindex);
			break;
		case kSoulSize_Grand:
			a_gemInfo.compat.emplace_back(kSoulGem_GISTBlackFilledGrand + GISTindex);
			a_gemInfo.maxFill = a_gemInfo.compat.size();
			break;
		default:
			std::string msg = "ERROR: In GemUtil::addGISTGems : Invalid soul size!" + numToHexString(a_soulSize, 4) + "\n";
			_ERROR(msg.c_str());
		}
	}


	Gem::Gem(UInt32 a_soulGemType) :
		soulGemType(a_soulGemType)
	{}


	bool Gem::empty()
	{
		return entryData.empty();
	}


	bool Gem::addGem(InventoryEntryData* a_entry)
	{
		entryData.push_back(a_entry);
		return true;
	}


	Soul::Soul(UInt32 a_soulSize) :
		soulSize(a_soulSize)
	{
		switch (soulSize) {
		case kSoulSize_Petty:
			compatGems = gemUtil.petty.compat;
			break;
		case kSoulSize_Lesser:
			compatGems = gemUtil.lesser.compat;
			break;
		case kSoulSize_Common:
			compatGems = gemUtil.common.compat;
			break;
		case kSoulSize_Greater:
			compatGems = gemUtil.greater.compat;
			break;
		case kSoulSize_Grand:
			compatGems = gemUtil.grand.compat;
			break;
		default:
			std::string msg = "ERROR: In Soul::Soul : Invalid soul size!" + numToHexString(a_soulSize, 4) + "\n";
			_ERROR(msg.c_str());
		}
	}


	bool Soul::empty()
	{
		for (auto& gem : compatGems) {
			if (!gem.empty()) {
				return false;
			}
		}
		return true;
	}


	bool Soul::addSoul(InventoryEntryData* a_entry)
	{
		for (auto& gem : compatGems) {
			if (gem.soulGemType == a_entry->type->formID) {
				return gem.addGem(a_entry);
			}
		}
		std::string msg = "ERROR: In Soul::addSoul : Invalid soulgem type!" + numToHexString(a_entry->type->formID, 4) + "\n";
		_ERROR(msg.c_str());
		return false;
	}


	InventoryEntryData* Soul::findGem(bool a_partialFill)
	{
		if (!empty()) {
			UInt32 max = a_partialFill ? compatGems.size() : getMaxFillCount(soulSize);
			InventoryEntryData* entry = 0;
			for (UInt32 i = 0; i < max; ++i) {
				if (!compatGems[i].empty()) {
					entry = compatGems[i].entryData.back();
					compatGems[i].entryData.pop_back();
					return entry;
				}
			}
			_ERROR("ERROR: In Soul::findGem : Unexpectedly exited for loop!\n");
		}
		return 0;
	}


	SoulGem::SoulGem()
	{
		souls.emplace_back(kSoulSize_Petty);
		souls.emplace_back(kSoulSize_Lesser);
		souls.emplace_back(kSoulSize_Common);
		souls.emplace_back(kSoulSize_Greater);
		souls.emplace_back(kSoulSize_Grand);
	}


	bool SoulGem::empty()
	{
		for (auto& soul : souls) {
			if (!soul.empty()) {
				return false;
			}
		}
		return true;
	}


	bool SoulGem::addSoulGem(InventoryEntryData* a_entry, UInt32 a_soulSize)
	{
		for (auto& soul : souls) {
			if (a_soulSize == soul.soulSize) {
				return soul.addSoul(a_entry);
			}
		}
		_ERROR("ERROR: In SoulGem::addSoulGem : Invalid soul size!\n");
		return false;
	}


	InventoryEntryData* SoulGem::findSoul(UInt32 a_soulSize, bool a_partialFill)
	{
		return empty() ? 0 : souls[a_soulSize - 1].findGem(a_partialFill);
	}


	UInt32 getMaxFillCount(UInt32 a_soulSize)
	{
		switch (a_soulSize) {
		case kSoulSize_Petty:
			return gemUtil.petty.maxFill;
		case kSoulSize_Lesser:
			return gemUtil.lesser.maxFill;
		case kSoulSize_Common:
			return gemUtil.common.maxFill;
		case kSoulSize_Greater:
			return gemUtil.greater.maxFill;
		case kSoulSize_Grand:
			return gemUtil.grand.maxFill;
		default:
			_ERROR("ERROR: In getMaxFillCount : Invalid soul size!\n");
			return 0;
		}
	}
}