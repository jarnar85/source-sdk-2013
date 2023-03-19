#if !defined( HUD_HINTDISPALAY_H )
#define HUD_HINTDISPALAY_H
#ifdef _WIN32
#pragma once
#endif

#include "hud_macros.h"

//-----------------------------------------------------------------------------
// Purpose: Displays hints across the center of the screen
//-----------------------------------------------------------------------------
class CHudHintDisplay : public vgui::Panel, public CHudElement
{
	DECLARE_CLASS_SIMPLE(CHudHintDisplay, vgui::Panel);

public:
	CHudHintDisplay(const char *pElementName);

	void Init();
	void Reset();
	void MsgFunc_HintText(bf_read &msg);
	void MsgFunc_HudColor(bf_read &msg);
	void FireGameEvent(IGameEvent * event);

	bool SetHintText(wchar_t *text);
	void LocalizeAndDisplay(const char *pszHudTxtMsg, const char *szRawString);

	virtual void PerformLayout();

protected:
	virtual void ApplySchemeSettings(vgui::IScheme *pScheme);
	virtual void OnThink();

protected:
	vgui::HFont m_hFont;
	Color		m_bgColor;
	vgui::Label *m_pLabel;
	CUtlVector<vgui::Label *> m_Labels;
	CPanelAnimationVarAliasType(int, m_iTextX, "text_xpos", "8", "proportional_int");
	CPanelAnimationVarAliasType(int, m_iTextY, "text_ypos", "8", "proportional_int");
	CPanelAnimationVarAliasType(int, m_iCenterX, "center_x", "0", "proportional_int");
	CPanelAnimationVarAliasType(int, m_iCenterY, "center_y", "0", "proportional_int");

	bool		m_bLastLabelUpdateHack;
	CPanelAnimationVar(float, m_flLabelSizePercentage, "HintSize", "0");
};


//-----------------------------------------------------------------------------
// Purpose: Displays small key-centric hints on the right hand side of the screen
//-----------------------------------------------------------------------------
class CHudHintKeyDisplay : public vgui::Panel, public CHudElement
{
	DECLARE_CLASS_SIMPLE(CHudHintKeyDisplay, vgui::Panel);

public:
	CHudHintKeyDisplay(const char *pElementName);
	void Init();
	void Reset();
	void MsgFunc_KeyHintText(bf_read &msg);
	void MsgFunc_HudColor(bf_read &msg);
	bool ShouldDraw();

	bool SetHintText(const char *text);

protected:
	virtual void ApplySchemeSettings(vgui::IScheme *pScheme);
	virtual void OnThink();

private:
	CUtlVector<vgui::Label *> m_Labels;
	vgui::HFont m_hSmallFont, m_hLargeFont;
	int		m_iBaseY;

	CPanelAnimationVarAliasType(float, m_iTextX, "text_xpos", "8", "proportional_float");
	CPanelAnimationVarAliasType(float, m_iTextY, "text_ypos", "8", "proportional_float");
	CPanelAnimationVarAliasType(float, m_iTextGapX, "text_xgap", "8", "proportional_float");
	CPanelAnimationVarAliasType(float, m_iTextGapY, "text_ygap", "8", "proportional_float");
	CPanelAnimationVarAliasType(float, m_iYOffset, "YOffset", "0", "proportional_float");
};


#endif // HUD_HINTDISPALAY_H