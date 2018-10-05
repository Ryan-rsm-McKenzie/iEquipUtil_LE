#pragma once

#include "common/ITypes.h"  // UInt8, UInt32
#include "skse/GameExtraData.h"  // InventoryEntryData

#include <vector> // vector


namespace iEquip_SoulSeeker
{
	enum SoulSize : UInt8
	{
		kSoulSize_Empty,
		kSoulSize_Petty,
		kSoulSize_Lesser,
		kSoulSize_Common,
		kSoulSize_Greater,
		kSoulSize_Grand
	};


	// Player filled soulgems have the same ID as unfilled soulgems
	enum SoulGemType : UInt32
	{
		kSoulGem_Petty = 0x0002E4E2,
		kSoulGem_PettyFilled = 0x0002E4E3,
		kSoulGem_Lesser = 0x0002E4E4,
		kSoulGem_LesserFilled = 0x0002E4E5,
		kSoulGem_Common = 0x0002E4E6,
		kSoulGem_CommonFilled = 0x0002E4F3,
		kSoulGem_Greater = 0x0002E4F4,
		kSoulGem_GreaterFilled = 0x0002E4FB,
		kSoulGem_Grand = 0x0002E4FC,
		kSoulGem_GrandFilled = 0x0002E4FF,
		kSoulGem_Black = 0x0002E500,
		kSoulGem_BlackFilled = 0x0002E504,
		kSoulGem_AzurasStar = 0x00063B27,
		kSoulGem_BlackStar = 0x00063B29,

		kSoulGem_GISTBlackFilledGrand = 0x000012D2,
		kSoulGem_GISTBlackFilledGreater = 0x00000D62,
		kSoulGem_GISTBlackFilledCommon = 0x00000D63,
		kSoulGem_GISTBlackFilledLesser = 0x00000D64,
		kSoulGem_GISTBlackFilledPetty = 0x00000D65,
		kSoulGem_GISTGrandFilledGreater = 0x00000D66,
		kSoulGem_GISTGrandFilledCommon = 0x00000D67,
		kSoulGem_GISTGrandFilledLesser = 0x00000D68,
		kSoulGem_GISTGrandFilledPetty = 0x00000D69,
		kSoulGem_GISTGreaterFilledCommon = 0x00000D6A,
		kSoulGem_GISTGreaterFilledLesser = 0x00000D6B,
		kSoulGem_GISTGreaterFilledPetty = 0x00000D6C,
		kSoulGem_GISTCommonFilledLesser = 0x00000D6D,
		kSoulGem_GISTCommonFilledPetty = 0x00000D6E,
		kSoulGem_GISTLesserFilledPetty = 0x00000D6F,
	};


	class Gem
	{
	public:
		explicit Gem(UInt32 a_soulGemType);
		bool empty();
		bool addGem(InventoryEntryData* a_entry);

		UInt32 soulGemType;
		std::vector<InventoryEntryData*> entryData;
	};


	class GemUtil
	{
	public:
		GemUtil();
		void GISTFound();

		struct GemInfo
		{
			UInt32 maxFill;
			std::vector<Gem> compat;
		};

		GemInfo petty;
		GemInfo lesser;
		GemInfo common;
		GemInfo greater;
		GemInfo grand;

	private:
		void fillCompatGems(UInt32 a_soulSize, GemInfo& a_gemInfo);
		void addGISTGems(UInt32 a_soulSize, GemInfo& a_gemInfo);
	};


	class Soul
	{
	public:
		explicit Soul(UInt32 a_soulSize);
		bool empty();
		bool addSoul(InventoryEntryData* a_entry);
		InventoryEntryData* findGem(bool a_partialFill);

		UInt32 soulSize;
		std::vector<Gem> compatGems;
	};


	class SoulGem
	{
	public:
		SoulGem();
		bool empty();
		bool addSoulGem(InventoryEntryData* a_entry, UInt32 a_soulSize);
		InventoryEntryData* findSoul(UInt32 a_soulSize, bool a_partialFill);

		std::vector<Soul> souls;
	};


	extern GemUtil gemUtil;


	UInt32 getMaxFillCount(UInt32 a_soulSize);
}