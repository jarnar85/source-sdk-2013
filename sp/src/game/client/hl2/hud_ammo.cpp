//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "hud.h"
#include "hudelement.h"
#include "hud_macros.h"
#include "hud_numericdisplay.h"
#include "hud_ammo.h"
#include "iclientmode.h"
#include "iclientvehicle.h"
#include <vgui_controls/AnimationController.h>
#include <vgui/ILocalize.h>
#include <vgui/ISurface.h>
#include "ihudlcd.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

using namespace vgui;


DECLARE_HUDELEMENT(CHudAmmo);
DECLARE_HUD_MESSAGE(CHudAmmo, HudColor);

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CHudAmmo::CHudAmmo( const char *pElementName ) : BaseClass(NULL, "HudAmmo"), CHudElement( pElementName )
{
	SetHiddenBits( HIDEHUD_HEALTH | HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT | HIDEHUD_WEAPONSELECTION );

	hudlcd->SetGlobalStat( "(ammo_primary)", "0" );
	hudlcd->SetGlobalStat( "(ammo_secondary)", "0" );
	hudlcd->SetGlobalStat( "(weapon_print_name)", "" );
	hudlcd->SetGlobalStat( "(weapon_name)", "" );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudAmmo::Init( void )
{
	HOOK_HUD_MESSAGE(CHudAmmo, HudColor);
	m_iAmmo		= -1;
	m_iAmmo2	= -1;
	
	m_iconPrimaryAmmo = NULL;

	wchar_t *tempString = g_pVGuiLocalize->Find("#Valve_Hud_AMMO");
	if (tempString)
	{
		SetLabelText(tempString);
	}
	else
	{
		SetLabelText(L"AMMO");
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudAmmo::VidInit( void )
{
}

//-----------------------------------------------------------------------------
// Purpose: Resets hud after save/restore
//-----------------------------------------------------------------------------
void CHudAmmo::Reset()
{
	BaseClass::Reset();

	m_hCurrentActiveWeapon = NULL;
	m_hCurrentVehicle = NULL;
	m_iAmmo = 0;
	m_iAmmo2 = 0;

	UpdateAmmoDisplays();
}

//-----------------------------------------------------------------------------
// Purpose: called every frame to get ammo info from the weapon
//-----------------------------------------------------------------------------
void CHudAmmo::UpdatePlayerAmmo( C_BasePlayer *player )
{
	// Clear out the vehicle entity
	m_hCurrentVehicle = NULL;

	C_BaseCombatWeapon *wpn = GetActiveWeapon();

	hudlcd->SetGlobalStat( "(weapon_print_name)", wpn ? wpn->GetPrintName() : " " );
	hudlcd->SetGlobalStat( "(weapon_name)", wpn ? wpn->GetName() : " " );

	if ( !wpn || !player || !wpn->UsesPrimaryAmmo() )
	{
		hudlcd->SetGlobalStat( "(ammo_primary)", "n/a" );
        hudlcd->SetGlobalStat( "(ammo_secondary)", "n/a" );

		SetPaintEnabled(false);
		SetPaintBackgroundEnabled(false);
		return;
	}

	SetPaintEnabled(true);
	SetPaintBackgroundEnabled(true);

	// Get our icons for the ammo types
	m_iconPrimaryAmmo = gWR.GetAmmoIconFromWeapon( wpn->GetPrimaryAmmoType() );

	// get the ammo in our clip
	int ammo1 = wpn->Clip1();
	int ammo2;
	if (ammo1 < 0)
	{
		// we don't use clip ammo, just use the total ammo count
		ammo1 = player->GetAmmoCount(wpn->GetPrimaryAmmoType());
		ammo2 = 0;
	}
	else
	{
		// we use clip ammo, so the second ammo is the total ammo
		ammo2 = player->GetAmmoCount(wpn->GetPrimaryAmmoType());
	}

	hudlcd->SetGlobalStat( "(ammo_primary)", VarArgs( "%d", ammo1 ) );
	hudlcd->SetGlobalStat( "(ammo_secondary)", VarArgs( "%d", ammo2 ) );

	if (wpn == m_hCurrentActiveWeapon)
	{
		// same weapon, just update counts
		SetAmmo(ammo1, true);
		SetAmmo2(ammo2, true);
	}
	else
	{
		// diferent weapon, change without triggering
		SetAmmo(ammo1, false);
		SetAmmo2(ammo2, false);

		// update whether or not we show the total ammo display
		if (wpn->UsesClipsForAmmo1())
		{
			SetShouldDisplaySecondaryValue(true);
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponUsesClips");
		}
		else
		{
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponDoesNotUseClips");
			SetShouldDisplaySecondaryValue(false);
		}

		switch (m_hudColor)
		{
		case HUDCLR_RED:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponChangedRed", "WeaponChanged");
			break;
		case HUDCLR_GRN:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponChangedGrn", "WeaponChanged");
			break;
		case HUDCLR_BLU:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponChangedBlu", "WeaponChanged");
			break;
		default:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponChanged");
		}
		m_hCurrentActiveWeapon = wpn;
	}
}

void CHudAmmo::UpdateVehicleAmmo( C_BasePlayer *player, IClientVehicle *pVehicle )
{
	m_hCurrentActiveWeapon = NULL;
	CBaseEntity *pVehicleEnt = pVehicle->GetVehicleEnt();

	if ( !pVehicleEnt || pVehicle->GetPrimaryAmmoType() < 0 )
	{
		SetPaintEnabled(false);
		SetPaintBackgroundEnabled(false);
		return;
	}

	SetPaintEnabled(true);
	SetPaintBackgroundEnabled(true);

	// get the ammo in our clip
	int ammo1 = pVehicle->GetPrimaryAmmoClip();
	int ammo2;
	if (ammo1 < 0)
	{
		// we don't use clip ammo, just use the total ammo count
		ammo1 = pVehicle->GetPrimaryAmmoCount();
		ammo2 = 0;
	}
	else
	{
		// we use clip ammo, so the second ammo is the total ammo
		ammo2 = pVehicle->GetPrimaryAmmoCount();
	}

	if (pVehicleEnt == m_hCurrentVehicle)
	{
		// same weapon, just update counts
		SetAmmo(ammo1, true);
		SetAmmo2(ammo2, true);
	}
	else
	{
		// diferent weapon, change without triggering
		SetAmmo(ammo1, false);
		SetAmmo2(ammo2, false);

		// update whether or not we show the total ammo display
		if (pVehicle->PrimaryAmmoUsesClips())
		{
			SetShouldDisplaySecondaryValue(true);
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponUsesClips");
		}
		else
		{
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponDoesNotUseClips");
			SetShouldDisplaySecondaryValue(false);
		}

		switch (m_hudColor)
		{
		case HUDCLR_RED:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponChangedRed", "WeaponChanged");
			break;
		case HUDCLR_GRN:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponChangedGrn", "WeaponChanged");
			break;
		case HUDCLR_BLU:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponChangedBlu", "WeaponChanged");
			break;
		default:
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponChanged");
		}
		m_hCurrentVehicle = pVehicleEnt;
	}
}

//-----------------------------------------------------------------------------
// Purpose: called every frame to get ammo info from the weapon
//-----------------------------------------------------------------------------
void CHudAmmo::OnThink()
{
	UpdateAmmoDisplays();
}

//-----------------------------------------------------------------------------
// Purpose: updates the ammo display counts
//-----------------------------------------------------------------------------
void CHudAmmo::UpdateAmmoDisplays()
{
	C_BasePlayer *player = C_BasePlayer::GetLocalPlayer();
	IClientVehicle *pVehicle = player ? player->GetVehicle() : NULL;

	if ( !pVehicle )
	{
		UpdatePlayerAmmo( player );
	}
	else
	{
		UpdateVehicleAmmo( player, pVehicle );
	}
}

//-----------------------------------------------------------------------------
// Purpose: Updates ammo display
//-----------------------------------------------------------------------------
void CHudAmmo::SetAmmo(int ammo, bool playAnimation)
{
	if (ammo != m_iAmmo)
	{
		if (ammo == 0)
		{
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoEmptyRed", "AmmoEmpty");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoEmptyGrn", "AmmoEmpty");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoEmptyBlu", "AmmoEmpty");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoEmpty");
			}
		}
		else if (ammo < m_iAmmo)
		{
			// ammo has decreased
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoDecreasedRed", "AmmoDecreased");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoDecreasedGrn", "AmmoDecreased");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoDecreasedBlu", "AmmoDecreased");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoDecreased");
			}
		}
		else
		{
			// ammunition has increased
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoIncreasedRed", "AmmoIncreased");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoIncreasedGrn", "AmmoIncreased");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoIncreasedBlu", "AmmoIncreased");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoIncreased");
			}
		}

		m_iAmmo = ammo;
	}

	SetDisplayValue(ammo);
}

//-----------------------------------------------------------------------------
// Purpose: Updates 2nd ammo display
//-----------------------------------------------------------------------------
void CHudAmmo::SetAmmo2(int ammo2, bool playAnimation)
{
	if (ammo2 != m_iAmmo2)
	{
		if (ammo2 == 0)
		{
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2EmptyRed", "Ammo2Empty");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2EmptyGrn", "Ammo2Empty");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2EmptyBlu", "Ammo2Empty");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2Empty");
			}
		}
		else if (ammo2 < m_iAmmo2)
		{
			// ammo has decreased
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2DecreasedRed", "Ammo2Decreased");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2DecreasedGrn", "Ammo2Decreased");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2DecreasedBlu", "Ammo2Decreased");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2Decreased");
			}
		}
		else
		{
			// ammunition has increased
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2IncreasedRed", "Ammo2Increased");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2IncreasedGrn", "Ammo2Increased");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2IncreasedBlu", "Ammo2Increased");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("Ammo2Increased");
			}
		}

		m_iAmmo2 = ammo2;
	}

	SetSecondaryValue(ammo2);
}

//-----------------------------------------------------------------------------
// Purpose: We add an icon into the 
//-----------------------------------------------------------------------------
void CHudAmmo::Paint( void )
{
	BaseClass::Paint();

#ifndef HL2MP
	if ( m_hCurrentVehicle == NULL && m_iconPrimaryAmmo )
	{
		int nLabelHeight;
		int nLabelWidth;
		surface()->GetTextSize( m_hTextFont, m_LabelText, nLabelWidth, nLabelHeight );

		// Figure out where we're going to put this
		int x = text_xpos + ( nLabelWidth - m_iconPrimaryAmmo->Width() ) / 2;
		int y = text_ypos - ( nLabelHeight + ( m_iconPrimaryAmmo->Height() / 2 ) );
		
		m_iconPrimaryAmmo->DrawSelf( x, y, GetFgColor() );
	}
#endif // HL2MP
}



DECLARE_HUDELEMENT(CHudSecondaryAmmo);
DECLARE_HUD_MESSAGE(CHudSecondaryAmmo, HudColor);

//-----------------------------------------------------------------------------
// Purpose: Displays the secondary ammunition level
//-----------------------------------------------------------------------------
CHudSecondaryAmmo::CHudSecondaryAmmo(const char *pElementName) : BaseClass(NULL, "HudAmmoSecondary"), CHudElement(pElementName)
{
	m_iAmmo = -1;

	SetHiddenBits( HIDEHUD_HEALTH | HIDEHUD_WEAPONSELECTION | HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT );
}

void CHudSecondaryAmmo::Init(void)
{
	HOOK_HUD_MESSAGE(CHudSecondaryAmmo, HudColor);
#ifndef HL2MP
	wchar_t *tempString = g_pVGuiLocalize->Find("#Valve_Hud_AMMO_ALT");
	if (tempString)
	{
		SetLabelText(tempString);
	}
	else
	{
		SetLabelText(L"ALT");
	}
#endif // HL2MP
}

void CHudSecondaryAmmo::VidInit(void)
{
}

void CHudSecondaryAmmo::SetAmmo(int ammo)
{
	if (ammo != m_iAmmo)
	{
		if (ammo == 0)
		{
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryEmptyRed", "AmmoSecondaryEmpty");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryEmptyGrn", "AmmoSecondaryEmpty");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryEmptyBlu", "AmmoSecondaryEmpty");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryEmpty");
			}
		}
		else if (ammo < m_iAmmo)
		{
			// ammo has decreased
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryDecreasedRed", "AmmoSecondaryDecreased");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryDecreasedGrn", "AmmoSecondaryDecreased");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryDecreasedBlu", "AmmoSecondaryDecreased");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryDecreased");
			}
		}
		else
		{
			// ammunition has increased
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryIncreasedRed", "AmmoSecondaryIncreased");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryIncreasedGrn", "AmmoSecondaryIncreased");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryIncreasedBlu", "AmmoSecondaryIncreased");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("AmmoSecondaryIncreased");
			}
		}

		m_iAmmo = ammo;
	}
	SetDisplayValue( ammo );
}

void CHudSecondaryAmmo::Reset()
{
	// hud reset, update ammo state
	BaseClass::Reset();
	m_iAmmo = 0;
	m_hCurrentActiveWeapon = NULL;
	SetAlpha( 0 );
	UpdateAmmoState();
}

void CHudSecondaryAmmo::Paint(void)
{
	BaseClass::Paint();

#ifndef HL2MP
	if ( m_iconSecondaryAmmo )
	{
		int nLabelHeight;
		int nLabelWidth;
		surface()->GetTextSize( m_hTextFont, m_LabelText, nLabelWidth, nLabelHeight );

		// Figure out where we're going to put this
		int x = text_xpos + ( nLabelWidth - m_iconSecondaryAmmo->Width() ) / 2;
		int y = text_ypos - ( nLabelHeight + ( m_iconSecondaryAmmo->Height() / 2 ) );

		m_iconSecondaryAmmo->DrawSelf( x, y, GetFgColor() );
	}
#endif // HL2MP
}

void CHudSecondaryAmmo::OnThink()
{
	// set whether or not the panel draws based on if we have a weapon that supports secondary ammo
	C_BaseCombatWeapon *wpn = GetActiveWeapon();
	C_BasePlayer *player = C_BasePlayer::GetLocalPlayer();
	IClientVehicle *pVehicle = player ? player->GetVehicle() : NULL;
	if (!wpn || !player || pVehicle)
	{
		m_hCurrentActiveWeapon = NULL;
		SetPaintEnabled(false);
		SetPaintBackgroundEnabled(false);
		return;
	}
	else
	{
		SetPaintEnabled(true);
		SetPaintBackgroundEnabled(true);
	}

	UpdateAmmoState();
}

void CHudSecondaryAmmo::UpdateAmmoState()
{
	C_BaseCombatWeapon *wpn = GetActiveWeapon();
	C_BasePlayer *player = C_BasePlayer::GetLocalPlayer();

	if (player && wpn && wpn->UsesSecondaryAmmo())
	{
		SetAmmo(player->GetAmmoCount(wpn->GetSecondaryAmmoType()));
	}

	if ( m_hCurrentActiveWeapon != wpn )
	{
		if ( wpn->UsesSecondaryAmmo() )
		{
			// we've changed to a weapon that uses secondary ammo
			switch (m_hudColor)
			{
			case HUDCLR_RED:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponUsesSecondaryAmmoRed", "WeaponUsesSecondaryAmmo");
				break;
			case HUDCLR_GRN:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponUsesSecondaryAmmoGrn", "WeaponUsesSecondaryAmmo");
				break;
			case HUDCLR_BLU:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponUsesSecondaryAmmoBlu", "WeaponUsesSecondaryAmmo");
				break;
			default:
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponUsesSecondaryAmmo");
			}
		}
		else 
		{
			// we've changed away from a weapon that uses secondary ammo
			g_pClientMode->GetViewportAnimationController()->StartAnimationSequence("WeaponDoesNotUseSecondaryAmmo");
		}
		m_hCurrentActiveWeapon = wpn;
			
		// Get the icon we should be displaying
		m_iconSecondaryAmmo = gWR.GetAmmoIconFromWeapon( m_hCurrentActiveWeapon->GetSecondaryAmmoType() );
	}
}
