#pragma once

#include "skse/GameExtraData.h"


namespace RE
{
	class InventoryEntryData
	{
	public:
		struct EquipData
		{
			SInt32			itemCount;

			BaseExtraList*	itemExtraList;

			BaseExtraList*	wornExtraList;
			BaseExtraList*	wornLeftExtraList;

			bool			isItemWorn;
			bool			isItemWornLeft;
			bool			isTypeWorn;
			bool			isTypeWornLeft;

			EquipData();
		};

		InventoryEntryData(TESForm * item, UInt32 count);

		TESForm* type;
		ExtendDataList* extendDataList;
		SInt32 countDelta;

		// Heap allocated
		static InventoryEntryData * Create(TESForm * item, UInt32 count);
		void Delete(void);

		void GetExtraWornBaseLists(BaseExtraList ** pWornBaseListOut, BaseExtraList ** pWornLeftBaseListOut) const;
		void GetEquipItemData(EquipData& stateOut, SInt32 itemId, SInt32 baseCount) const;

		MEMBER_FN_PREFIX(InventoryEntryData);
		DEFINE_MEMBER_FN(GenerateName, const char *, 0x00475AA0);
		DEFINE_MEMBER_FN(GetValue, SInt32, 0x00475450);
		DEFINE_MEMBER_FN(IsOwnedBy, bool, 0x00477010, TESForm * actor, bool unk1);
		DEFINE_MEMBER_FN(GetSoulLevel, UInt32, 0x004756F0);
	};
}