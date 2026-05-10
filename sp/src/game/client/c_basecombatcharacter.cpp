//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Client's C_BaseCombatCharacter entity
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#include "c_basecombatcharacter.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#if defined( CBaseCombatCharacter )
#undef CBaseCombatCharacter	
#endif

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
C_BaseCombatCharacter::C_BaseCombatCharacter()
{
	for ( int i=0; i < m_iAmmo.Count(); i++ )
	{
		m_iAmmo.Set( i, 0 );
	}

#ifdef GLOWS_ENABLE
	m_pGlowEffect = NULL;
	m_bGlowEnabled = false;
	m_bOldGlowEnabled = false;
#endif // GLOWS_ENABLE
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
C_BaseCombatCharacter::~C_BaseCombatCharacter()
{
#ifdef GLOWS_ENABLE
	DestroyGlowEffect();
#endif // GLOWS_ENABLE
}

/*
//-----------------------------------------------------------------------------
// Purpose: Returns the amount of ammunition of the specified type the character's carrying
//-----------------------------------------------------------------------------
int	C_BaseCombatCharacter::GetAmmoCount( char *szName ) const
{
	return GetAmmoCount( g_pGameRules->GetAmmoDef()->Index(szName) );
}
*/




//-----------------------------------------------------------------------------
// Character stats
//-----------------------------------------------------------------------------


const char * C_BaseCombatCharacter::GetCitizenId(uint id, uint city, uint unit) {

	 char citIdPrefix[8];
	 char* citId = new char[64];

	 if (city > 99)
		  city = city % 100;

	 if (city > 0)
		  Q_snprintf(citIdPrefix, 8, "314-C%02i", city);
	 else
		  V_snprintf(citIdPrefix, 8, "UU");

	 const char* pFormatDUI = "%s.%s-%s-%d.%d";
	 const char* pFormatDI = "%s.%s-%s.%d";
	 const char* pFormatUI = "%s.%s-%d.%d";

	 if (id == 0)
		  id = rand();

	 switch (m_Class)
	 {
	 case PLC_NONE:
	 case PLC_SOLDIER:
	 case PLC_POLICE:
		  V_snprintf(citId, 64, "%d", id);
		  break;
	 case PLC_PLAYER:
	 case PLC_CITIZEN:
	 case PLC_REBEL:
	 case PLC_REBEL_MEDIC:
		  V_snprintf(citId, 64, "%s.CIV.%d", citIdPrefix, id);
		  break;
	 case PLC_MEDIC:
	 case PLC_SCIENTIST:
	 case PLC_COMBINE_WORKER:
		  if (m_Job == JOB_MEDIC)
				V_snprintf(citId, 64, pFormatDI, citIdPrefix, "CWU", "MED", id);
		  else if (m_Job == JOB_ENGINEER || m_Job == JOB_SCIENTIST)
				V_snprintf(citId, 64, pFormatDI, citIdPrefix, "CWU", "IND", id);
		  else
				V_snprintf(citId, 64, pFormatDI, citIdPrefix, "CWU", "ECO", id);

		  break;
	 case PLC_COMBINE_WORKER_HAZMAT:
		  V_snprintf(citId, 64, pFormatUI, citIdPrefix, "CHS", unit, id);
		  break;
	 case PLC_CREMATOR:
		  V_snprintf(citId, 64, pFormatDI, citIdPrefix, "CHS", "VICE", id);
		  break;
	 case PLC_METROPOLICE:
		  if (m_iMemRepl > 0){
				if (m_Job == JOB_SNIPER || m_Job == JOB_PILOT)
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "MCP", "WRAITH", unit, id);
				else if (m_Job == JOB_GUARD)
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "MCP", "SPEAR", unit, id);
				else if (m_Job == JOB_MEDIC)
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "MCP", "APEX", unit, id);
				else if (m_Job == JOB_ENGINEER)
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "MCP", "ANVIL", unit, id);
				else // if (m_Job == JOB_OFFICER)
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "MCP", "BLADE", unit, id);
		  }
		  else
		  {
				if (m_Job == JOB_SNIPER || m_Job == JOB_PILOT)
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "MCP", "GHOST", unit, id);
				else if (m_Job == JOB_GUARD)
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "MCP", "RAZOR", unit, id);
				else if (m_Job == JOB_MEDIC)
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "MCP", "HELIX", unit, id);
				else if (m_Job == JOB_ENGINEER)
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "MCP", "GRID", unit, id);
				else // if (m_Job == JOB_OFFICER)
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "MCP", "UNION", unit, id);
		  }
		  break;
	 case PLC_METROPOLICE_RECRUIT:
		 V_snprintf(citId, 64, pFormatDI, citIdPrefix, "MCP", "RCT", id);
		 break;
	 case PLC_CONSCRIPT:
		  V_snprintf(citId, 64, pFormatUI, citIdPrefix, "CON", unit, id);
		  break;
	 case PLC_COMBINE_CHARGER:
	 case PLC_COMBINE_ELITE:
	 case PLC_COMBINE_GRUNT:
	 case PLC_COMBINE_HEAVY:
	 case PLC_COMBINE_MEDIC:
	 case PLC_COMBINE_ORDINAL:
	 case PLC_COMBINE_PRISONHEAVY:
	 case PLC_COMBINE_SOLDIER:
	 case PLC_COMBINE_SUPPRESSOR:
		  if (m_Job == JOB_SNIPER)
				V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "OTA", "RANGER", unit, id);
		  else if (m_Job == JOB_PILOT)
				V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "OTA", "HURRICANE", unit, id);
		  else if (m_Job == JOB_MEDIC)
				V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "OTA", "XRAY", unit, id);
		  else if (m_Job == JOB_BRUTE)
				V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "OTA", "MACE", unit, id);
		  else if (m_Job == JOB_HEAVY)
				V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "OTA", "HAMMER", unit, id);
		  else if (m_Job == JOB_SOLDIER) {
				if (m_iMemRepl > 2)
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "OTA", "KING", unit, id);
				else
					 V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "OTA", "PHANTOM", unit, id);
		  }
		  else
				V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "OTA", "ECHO", unit, id);

		  break;
	 case PLC_STALKER:
		  V_snprintf(citId, 64, "%s.VICE.%d", citIdPrefix, id);
		  break;
	 case PLC_COMBINE_PRISONGUARD:
		  V_snprintf(citId, 64, pFormatDUI, citIdPrefix, "OTA", "NOVA", unit, id);
		  break;
	 }

	 return citId;
}

const char * C_BaseCombatCharacter::GetCitizenId(uint id) {
	 return GetCitizenId(id, m_iCity, m_iSquad);
}



//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void C_BaseCombatCharacter::OnPreDataChanged( DataUpdateType_t updateType )
{
	BaseClass::OnPreDataChanged( updateType );

#ifdef GLOWS_ENABLE
	m_bOldGlowEnabled = m_bGlowEnabled;
#endif // GLOWS_ENABLE
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void C_BaseCombatCharacter::OnDataChanged( DataUpdateType_t updateType )
{
	BaseClass::OnDataChanged( updateType );

#ifdef GLOWS_ENABLE
	if ( m_bOldGlowEnabled != m_bGlowEnabled )
	{
		UpdateGlowEffect();
	}
#endif // GLOWS_ENABLE
}

//-----------------------------------------------------------------------------
// Purpose: Overload our muzzle flash and send it to any actively held weapon
//-----------------------------------------------------------------------------
void C_BaseCombatCharacter::DoMuzzleFlash()
{
	// Our weapon takes our muzzle flash command
	C_BaseCombatWeapon *pWeapon = GetActiveWeapon();
	if ( pWeapon )
	{
		pWeapon->DoMuzzleFlash();
		//NOTENOTE: We do not chain to the base here
	}
	else
	{
		BaseClass::DoMuzzleFlash();
	}
}

#ifdef GLOWS_ENABLE
//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void C_BaseCombatCharacter::GetGlowEffectColor( float *r, float *g, float *b )
{
	*r = 0.76f;
	*g = 0.76f;
	*b = 0.76f;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void C_BaseCombatCharacter::UpdateGlowEffect( void )
{
	// destroy the existing effect
	if ( m_pGlowEffect )
	{
		DestroyGlowEffect();
	}

	// create a new effect
	if ( m_bGlowEnabled )
	{
		float r, g, b;
		GetGlowEffectColor( &r, &g, &b );

		m_pGlowEffect = new CGlowObject( this, Vector( r, g, b ), 1.0, true );
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void C_BaseCombatCharacter::DestroyGlowEffect( void )
{
	if ( m_pGlowEffect )
	{
		delete m_pGlowEffect;
		m_pGlowEffect = NULL;
	}
}
#endif // GLOWS_ENABLE

IMPLEMENT_CLIENTCLASS(C_BaseCombatCharacter, DT_BaseCombatCharacter, CBaseCombatCharacter);

// Only send active weapon index to local player
BEGIN_RECV_TABLE_NOBASE( C_BaseCombatCharacter, DT_BCCLocalPlayerExclusive )
	RecvPropTime( RECVINFO( m_flNextAttack ) ),
END_RECV_TABLE();


BEGIN_RECV_TABLE(C_BaseCombatCharacter, DT_BaseCombatCharacter)
	RecvPropDataTable( "bcc_localdata", 0, 0, &REFERENCE_RECV_TABLE(DT_BCCLocalPlayerExclusive) ),
	RecvPropEHandle( RECVINFO( m_hActiveWeapon ) ),
	RecvPropArray3( RECVINFO_ARRAY(m_hMyWeapons), RecvPropEHandle( RECVINFO( m_hMyWeapons[0] ) ) ),
#ifdef GLOWS_ENABLE
	RecvPropBool( RECVINFO( m_bGlowEnabled ) ),
#endif // GLOWS_ENABLE

#ifdef INVASION_CLIENT_DLL
	RecvPropInt( RECVINFO( m_iPowerups ) ),
#endif
	RecvPropInt(RECVINFO(m_Class)),
	RecvPropInt(RECVINFO(m_Faction)),
	RecvPropInt(RECVINFO(m_Job)),

	RecvPropInt(RECVINFO(m_iCity)),
	RecvPropInt(RECVINFO(m_iSquad)),

END_RECV_TABLE()


BEGIN_PREDICTION_DATA( C_BaseCombatCharacter )

	DEFINE_PRED_ARRAY( m_iAmmo, FIELD_INTEGER,  MAX_AMMO_TYPES, FTYPEDESC_INSENDTABLE ),
	DEFINE_PRED_FIELD( m_flNextAttack, FIELD_FLOAT, FTYPEDESC_INSENDTABLE ),
	DEFINE_PRED_FIELD( m_hActiveWeapon, FIELD_EHANDLE, FTYPEDESC_INSENDTABLE ),
	DEFINE_PRED_ARRAY(m_hMyWeapons, FIELD_EHANDLE, MAX_WEAPONS, FTYPEDESC_INSENDTABLE),
	DEFINE_PRED_FIELD(m_iCity, FIELD_INTEGER, FTYPEDESC_INSENDTABLE),
	DEFINE_PRED_FIELD(m_iSquad, FIELD_INTEGER, FTYPEDESC_INSENDTABLE),


END_PREDICTION_DATA()
