#pragma once

#include "GameForms.h"  // BGSListForm
#include "GameObjects.h" // MagicItem
#include "ITypes.h"  // UInt32


namespace RE
{
	class EnchantmentItem : public MagicItem
	{
	public:
		enum { kTypeID = kFormType_Enchantment };

		enum
		{
			kFlag_ManualCalc = 0x00000001,
		};

		// 24
		struct Data
		{
			struct Calculations
			{
				UInt32 cost; // 00
				UInt32 flags; // 04
			};

			Calculations calculations; // 00
			UInt32 unk08; // 08
			UInt32 amount; // 0C - init'd to FFFFFFFF
			UInt32 deliveryType; // 10
			UInt32 castingType; // 14 - init'd to 6
			float castTime; // 18
			EnchantmentItem* baseEnchantment; // 1C
			BGSListForm* restrictions; // 20
		};

		Data data; // 50

		friend bool operator==(const EnchantmentItem& a_lhs, const EnchantmentItem& a_rhs);
	};


#if 0
	class EnchantmentItem : public MagicItem
	{
	public:
		enum { kTypeID = kFormType_Enchantment };

		enum
		{
			kFlag_ManualCalc = 0x00000001,
		};

		// 30
		struct Data
		{
			struct Calculations
			{
				UInt32 cost;  // 00 - init'd to FFFFFFFF
				UInt32 flags;  // 04
			};

			Calculations calculations;  // 00
			UInt32 unk08;  // 08
			UInt32 amount;  // 0C - init'd to FFFFFFFF
			UInt32 deliveryType;  // 10 - init'd to 5
			UInt32 castingType;  // 14 - init'd to 6
			float castTime;  // 18
			UInt32 pad1C;  // 1C
			EnchantmentItem* baseEnchantment;  // 20
			BGSListForm* restrictions;  // 28
		};

		Data data;  // 90

		friend bool operator==(const EnchantmentItem& a_lhs, const EnchantmentItem& a_rhs);
	};
#endif
}