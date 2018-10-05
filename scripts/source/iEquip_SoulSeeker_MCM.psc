ScriptName iEquip_SoulSeeker_MCM Extends SKI_ConfigBase


Actor Property PlayerRef Auto
GlobalVariable Property SoulSeeker_FillMethod Auto  ; Float
GlobalVariable Property SoulSeeker_PartialFill Auto  ; Int
GlobalVariable Property SoulSeeker_WasteOK Auto  ; Int


; Called when the config menu is initialized.
Event OnConfigInit()
	ModName = "Soul Seeker"
	pages = New String[1]
	pages[0] = "Config"
EndEvent


; Called when the config menu is closed.
Event OnConfigClose()
EndEvent


; Called when a version update of this script has been detected.
; a_version - The new version.
Event OnVersionUpdate(Int a_version)
EndEvent


; Called when a new page is selected, including the initial empty page.
; a_page - The name of the the current page, or "" if no page is selected.
Event OnPageReset(String a_page)
	If (a_page == "Config")
		SetCursorFillMode(TOP_TO_BOTTOM)
		AddTextOptionST("SoulSeeker_Petty_T", "Remove Petty", "")
		AddTextOptionST("SoulSeeker_Lesser_T", "Remove Lesser", "")
		AddTextOptionST("SoulSeeker_Common_T", "Remove Common", "")
		AddTextOptionST("SoulSeeker_Greater_T", "Remove Greater", "")
		AddTextOptionST("SoulSeeker_Grand_T", "Remove Grand", "")
		SetCursorPosition(1)
		AddSliderOptionST("SoulSeeker_FillMethod_S", "Fill Method:", SoulSeeker_FillMethod.GetValue() As Float)
		AddToggleOptionST("SoulSeeker_PartialFill_B", "Partial Fill:", SoulSeeker_PartialFill.GetValue() As Bool)
		AddToggleOptionST("SoulSeeker_WasteOK_B", "Waste OK:", SoulSeeker_WasteOK.GetValue() As Bool)
	EndIf
EndEvent


State SoulSeeker_Petty_T
	Event OnSelectST()
		InvokeBringMeASoul(1)
	EndEvent

	Event OnDefaultST()
	EndEvent

	Event OnHighlightST()
	EndEvent
EndState


State SoulSeeker_Lesser_T
	Event OnSelectST()
		InvokeBringMeASoul(2)
	EndEvent

	Event OnDefaultST()
	EndEvent

	Event OnHighlightST()
	EndEvent
EndState


State SoulSeeker_Common_T
	Event OnSelectST()
		InvokeBringMeASoul(3)
	EndEvent

	Event OnDefaultST()
	EndEvent

	Event OnHighlightST()
	EndEvent
EndState


State SoulSeeker_Greater_T
	Event OnSelectST()
		InvokeBringMeASoul(4)
	EndEvent

	Event OnDefaultST()
	EndEvent

	Event OnHighlightST()
	EndEvent
EndState


State SoulSeeker_Grand_T
	Event OnSelectST()
		InvokeBringMeASoul(5)
	EndEvent

	Event OnDefaultST()
	EndEvent

	Event OnHighlightST()
	EndEvent
EndState


State SoulSeeker_FillMethod_S
	Event OnSliderOpenST()
		SetSliderDialogStartValue(SoulSeeker_FillMethod.GetValue() As Float)
		SetSliderDialogDefaultValue(1)
		SetSliderDialogRange(0, 1)
		SetSliderDialogInterval(1)
	EndEvent

	Event OnSliderAcceptST(Float a_value)
		SoulSeeker_FillMethod.SetValue(a_value)
		SetSliderOptionValueST(SoulSeeker_FillMethod.GetValue() As Float)
	EndEvent

	Event OnDefaultST()
	EndEvent

	Event OnHighlightST()
	EndEvent
EndState


State SoulSeeker_PartialFill_B
	Event OnSelectST()
		If (SoulSeeker_PartialFill.GetValue() As Bool)
			SoulSeeker_PartialFill.SetValue(0)
		Else
			SoulSeeker_PartialFill.SetValue(1)
		EndIf
		SetToggleOptionValueST(SoulSeeker_PartialFill.GetValue() As Int)
	EndEvent

	Event OnDefaultST()
	EndEvent

	Event OnHighlightST()
	EndEvent
EndState


State SoulSeeker_WasteOK_B
	Event OnSelectST()
		If (SoulSeeker_WasteOK.GetValue() As Bool)
			SoulSeeker_WasteOK.SetValue(0)
		Else
			SoulSeeker_WasteOK.SetValue(1)
		EndIf
		SetToggleOptionValueST(SoulSeeker_WasteOK.GetValue() As Int)
	EndEvent

	Event OnDefaultST()
	EndEvent

	Event OnHighlightST()
	EndEvent
EndState


; Returns the static version of this script.
; RETURN - The static version of this script.
; History:
; 1 - Initial Release (v1.0.0)
Int Function GetVersion()
	Return 2
EndFunction


Function InvokeBringMeASoul(Int a_reqCharge)
	Int fillMethod = SoulSeeker_FillMethod.GetValue() As Int
		Bool partialFill = SoulSeeker_PartialFill.GetValue() As Bool
		Bool wasteOK = SoulSeeker_WasteOK.GetValue() As Bool
		Form targetSoulGem = NONE
		targetSoulGem = iEquip_SoulSeeker.BringMeASoul(a_reqCharge, fillMethod, partialFill, wasteOK)
		Int soulSize = iEquip_SoulSeeker.GetSoulSize()
		If (soulSize != 0)
			If (targetSoulGem)
				PlayerRef.RemoveItem(targetSoulGem, 1, False)
			Else
				Debug.Trace("SoulSeekerDBG: BringMeASoul() returned a NONE form!")
			EndIf
			Debug.Trace("SoulSeekerDBG: GetSoulSize() returned soulSize == " + soulSize)
		Else
			Debug.Trace("SoulSeekerDBG: BringMeASoul() failed to find a soul!")
		EndIf
EndFunction