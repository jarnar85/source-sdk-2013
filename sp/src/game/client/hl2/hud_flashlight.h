//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef HUD_FLASHLIGHT_H
#define HUD_FLASHLIGHT_H
#ifdef _WIN32
#pragma once
#endif

//-----------------------------------------------------------------------------
// Purpose: Shows the flashlight icon
//-----------------------------------------------------------------------------
class CHudFlashlight : public CHudElement, public vgui::Panel
{
	DECLARE_CLASS_SIMPLE(CHudFlashlight, vgui::Panel);

public:
	CHudFlashlight(const char *pElementName);
	virtual void ApplySchemeSettings(vgui::IScheme *pScheme);

protected:
	virtual void Paint();

private:
	void SetFlashlightState(bool flashlightOn);
	void Reset(void);

	bool	m_bFlashlightOn;
	CPanelAnimationVar(vgui::HFont, m_hFont, "Font", "WeaponIconsSmall");
	CPanelAnimationVarAliasType(float, m_IconX, "icon_xpos", "4", "proportional_float");
	CPanelAnimationVarAliasType(float, m_IconY, "icon_ypos", "4", "proportional_float");

	CPanelAnimationVarAliasType(float, m_flBarInsetX, "BarInsetX", "2", "proportional_float");
	CPanelAnimationVarAliasType(float, m_flBarInsetY, "BarInsetY", "18", "proportional_float");

	CPanelAnimationVarAliasType(float, m_flBarWidth, "BarWidth", "28", "proportional_float");
	CPanelAnimationVarAliasType(float, m_flBarHeight, "BarHeight", "2", "proportional_float");
	CPanelAnimationVarAliasType(float, m_flBarChunkWidth, "BarChunkWidth", "2", "proportional_float");
	CPanelAnimationVarAliasType(float, m_flBarChunkGap, "BarChunkGap", "2", "proportional_float");
};


#endif // HUD_FLASHLIGHT_H
