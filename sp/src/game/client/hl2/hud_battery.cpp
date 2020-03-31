//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
//
// battery.cpp
//
// implementation of CHudBattery class
//
#include "cbase.h"
#include "hud.h"
#include "hudelement.h"
#include "hud_macros.h"
#include "hud_numericdisplay.h"
#include "iclientmode.h"

#include "vgui_controls/AnimationController.h"
#include "vgui/ILocalize.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#define INIT_BAT	-1

//-----------------------------------------------------------------------------
// Purpose: Displays suit power (armor) on hud
//-----------------------------------------------------------------------------
class CHudBattery : public CHudNumericDisplay, public CHudElement
{
	DECLARE_CLASS_SIMPLE( CHudBattery, CHudNumericDisplay );

public:
	CHudBattery( const char *pElementName );
	void Init( void );
	void Reset( void );
	void VidInit( void );
	void OnThink(void);
	void MsgFunc_Battery(bf_read &msg);
	bool ShouldDraw();
	
private:
	int		m_iBat;	
	int		m_iNewBat;
};

DECLARE_HUDELEMENT( CHudBattery );
DECLARE_HUD_MESSAGE(CHudBattery, Battery);
DECLARE_HUD_MESSAGE(CHudBattery, HudColor);

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CHudBattery::CHudBattery( const char *pElementName ) : BaseClass(NULL, "HudSuit"), CHudElement( pElementName )
{
	SetHiddenBits( HIDEHUD_HEALTH | HIDEHUD_NEEDSUIT );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudBattery::Init( void )
{
	HOOK_HUD_MESSAGE(CHudBattery, Battery);
	HOOK_HUD_MESSAGE(CHudBattery, HudColor);
	Reset();
	m_iBat		= INIT_BAT;
	m_iNewBat   = 0;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudBattery::Reset( void )
{
	SetLabelText(g_pVGuiLocalize->Find("#Valve_Hud_SUIT"));
	SetDisplayValue(m_iBat);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudBattery::VidInit( void )
{
	Reset();
}

//-----------------------------------------------------------------------------
// Purpose: Save CPU cycles by letting the HUD system early cull
// costly traversal.  Called per frame, return true if thinking and 
// painting need to occur.
//-----------------------------------------------------------------------------
bool CHudBattery::ShouldDraw( void )
{
	bool bNeedsDraw = ( m_iBat != m_iNewBat ) || ( GetAlpha() > 0 );

	return ( bNeedsDraw && CHudElement::ShouldDraw() );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudBattery::OnThink( void )
{
	if ( m_iBat == m_iNewBat )
		return;

	if ( !m_iNewBat )
	{
		g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitPowerZero");
	}
	else if ( m_iNewBat < m_iBat )
	{
		// battery power has decreased, so play the damaged animation
		switch (m_hudColor)
		{
		case HUDCLR_RED:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitDamageTakenRed", "SuitDamageTaken");
			break;
		case HUDCLR_GRN:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitDamageTakenGrn", "SuitDamageTaken");
			break;
		case HUDCLR_BLU:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitDamageTakenBlu", "SuitDamageTaken");
			break;
		default:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitDamageTaken");
			break;
		}

		// play an extra animation if we're super low
		if ( m_iNewBat < 20 )
		{
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitArmorLowRed", "SuitArmorLow");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitArmorLowGrn", "SuitArmorLow");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitArmorLowBlu", "SuitArmorLow");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitArmorLow");
				break;
			}
		}
	}
	else
	{
		// battery power has increased (if we had no previous armor, or if we just loaded the game, don't use alert state)
		if ( m_iBat == INIT_BAT || m_iBat == 0 || m_iNewBat >= 20)
		{
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitPowerIncreasedAbove20Red", "SuitPowerIncreasedAbove20");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitPowerIncreasedAbove20Grn", "SuitPowerIncreasedAbove20");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitPowerIncreasedAbove20Blu", "SuitPowerIncreasedAbove20");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitPowerIncreasedAbove20");
				break;
			}
		}
		else
		{
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitPowerIncreasedBelow20Red", "SuitPowerIncreasedBelow20");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitPowerIncreasedBelow20Grn", "SuitPowerIncreasedBelow20");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitPowerIncreasedBelow20Blu", "SuitPowerIncreasedBelow20");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("SuitPowerIncreasedBelow20");
				break;
			}
		}
	}

	m_iBat = m_iNewBat;

	SetDisplayValue(m_iBat);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudBattery::MsgFunc_Battery(bf_read &msg)
{
	m_iNewBat = msg.ReadShort();
}
