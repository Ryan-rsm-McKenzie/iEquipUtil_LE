ScriptName iEquip_SoulSeeker


; @brief Fetch the most optimal soulgem to fill an enchanted weapon
; @param a_reqCharge The required soul to fetch. Valid inputs 1-5.
; @param a_fillMethod The method used to fill the soulgem. Valid inputs 0-1.
; @param a_partialFill Determines whether partially filled soul gems can be returned.
; @param a_wasteOK Determines whether soulgems exceeding the requred size can be returned.
; @return Returns the Form to be removed. Call GetSoulSize to determine if the search was a success.
Form Function BringMeASoul(Int a_reqCharge, Int a_fillMethod, Bool a_partialFill, Bool a_wasteOK) Global Native


; @brief Gets the soul size of the last returned soul.
; @return Returns the size of the last returned soul if the search was a success, otherwise returns 0.
Int Function GetSoulSize() Global Native