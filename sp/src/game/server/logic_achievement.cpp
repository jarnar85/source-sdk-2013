//========= Copyright Valve Corporation, All rights reserved. ============//
//	
//	Defines a logical entity which passes achievement related events to the gamerules system.

#include "cbase.h"
#include "gamerules.h"
#include "entityinput.h"
#include "entityoutput.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

/*
	These are the string choices in the FGD:

	ACHIEVEMENT_EVENT_HL2_HIT_CANCOP_WITHCAN
	ACHIEVEMENT_EVENT_HL2_ESCAPE_APARTMENTRAID
	ACHIEVEMENT_EVENT_HL2_FIND_ONEGMAN
	ACHIEVEMENT_EVENT_HL2_BREAK_MINITELEPORTER
	ACHIEVEMENT_EVENT_HL2_GET_PISTOL
	ACHIEVEMENT_EVENT_HL2_GET_AIRBOAT
	ACHIEVEMENT_EVENT_HL2_GET_AIRBOATGUN
	ACHIEVEMENT_EVENT_HL2_FIND_VORTIGAUNTCAVE
	ACHIEVEMENT_EVENT_HL2_KILL_CHOPPER
	ACHIEVEMENT_EVENT_HL2_FIND_HEVFACEPLATE
	ACHIEVEMENT_EVENT_HL2_GET_GRAVITYGUN
	ACHIEVEMENT_EVENT_HL2_MAKEABASKET
	ACHIEVEMENT_EVENT_HL2_BEAT_RAVENHOLM_NOWEAPONS_START
	ACHIEVEMENT_EVENT_HL2_BEAT_RAVENHOLM_NOWEAPONS_END
	ACHIEVEMENT_EVENT_HL2_BEAT_CEMETERY
	ACHIEVEMENT_EVENT_HL2_KILL_ENEMIES_WITHCRANE
	ACHIEVEMENT_EVENT_HL2_PIN_SOLDIER_TOBILLBOARD
	ACHIEVEMENT_EVENT_HL2_KILL_ODESSAGUNSHIP
	ACHIEVEMENT_EVENT_HL2_BEAT_DONTTOUCHSAND
	ACHIEVEMENT_EVENT_HL2_ENTER_NOVAPROSPEKT,
	ACHIEVEMENT_EVENT_HL2_BEAT_TURRETSTANDOFF2
	ACHIEVEMENT_EVENT_HL2_BEAT_NOVAPROSPEKT
	ACHIEVEMENT_EVENT_HL2_BEAT_TOXICTUNNEL
	ACHIEVEMENT_EVENT_HL2_BEAT_PLAZASTANDOFF
	ACHIEVEMENT_EVENT_HL2_KILL_ALLC17SNIPERS
	ACHIEVEMENT_EVENT_HL2_BEAT_SUPRESSIONDEVICE
	ACHIEVEMENT_EVENT_HL2_BEAT_C17STRIDERSTANDOFF
	ACHIEVEMENT_EVENT_HL2_REACH_BREENSOFFICE
	ACHIEVEMENT_EVENT_HL2_FIND_LAMDACACHE

	// EP1
	ACHIEVEMENT_EVENT_EP1_BEAT_MAINELEVATOR
	ACHIEVEMENT_EVENT_EP1_BEAT_CITADELCORE
	ACHIEVEMENT_EVENT_EP1_BEAT_CITADELCORE_NOSTALKERKILLS
	ACHIEVEMENT_EVENT_EP1_BEAT_GARAGEELEVATORSTANDOFF
	ACHIEVEMENT_EVENT_EP1_KILL_ENEMIES_WITHSNIPERALYX
	ACHIEVEMENT_EVENT_EP1_BEAT_HOSPITALATTICGUNSHIP
	ACHIEVEMENT_EVENT_EP1_BEAT_CITIZENESCORT_NOCITIZENDEATHS

	// EP2
	ACHIEVEMENT_EVENT_EP2_BREAK_ALLWEBS
	ACHIEVEMENT_EVENT_EP2_BEAT_ANTLIONINVASION
	ACHIEVEMENT_EVENT_EP2_BEAT_ANTLIONGUARDS
	ACHIEVEMENT_EVENT_EP2_BEAT_HUNTERAMBUSH
	ACHIEVEMENT_EVENT_EP2_KILL_COMBINECANNON
	ACHIEVEMENT_EVENT_EP2_FIND_RADAR_CACHE
	ACHIEVEMENT_EVENT_EP2_BEAT_RACEWITHDOG
	ACHIEVEMENT_EVENT_EP2_BEAT_ROCKETCACHEPUZZLE
	ACHIEVEMENT_EVENT_EP2_BEAT_WHITEFORESTINN
	ACHIEVEMENT_EVENT_EP2_PUT_ITEMINROCKET
	ACHIEVEMENT_EVENT_EP2_BEAT_MISSILESILO2
	ACHIEVEMENT_EVENT_EP2_BEAT_OUTLAND12_NOBUILDINGSDESTROYED

	// PORTAL
	ACHIEVEMENT_EVENT_PORTAL_GET_PORTALGUNS
	ACHIEVEMENT_EVENT_PORTAL_KILL_COMPANIONCUBE
	ACHIEVEMENT_EVENT_PORTAL_ESCAPE_TESTCHAMBERS
	ACHIEVEMENT_EVENT_PORTAL_BEAT_GAME

	"ACHIEVEMENT_EVENT_EZ_HULA_01"      : "[EZ] Hula Doll: Doll 1"
	"ACHIEVEMENT_EVENT_EZ_HULA_02"      : "[EZ] Hula Doll: Doll 2"
	"ACHIEVEMENT_EVENT_EZ_HULA_03"      : "[EZ] Hula Doll: Doll 3"
	"ACHIEVEMENT_EVENT_EZ_HULA_04"      : "[EZ] Hula Doll: Doll 4"
	"ACHIEVEMENT_EVENT_EZ_HULA_05"      : "[EZ] Hula Doll: Doll 5"
	"ACHIEVEMENT_EVENT_EZ_HULA_06"      : "[EZ] Hula Doll: Doll 6"
	"ACHIEVEMENT_EVENT_EZ_HULA_07"      : "[EZ] Hula Doll: Doll 7"

	"ACHIEVEMENT_EVENT_EZ_NXTGEN_01"      : "[EZ] LG Tag: 1"
	"ACHIEVEMENT_EVENT_EZ_NXTGEN_02"      : "[EZ] LG Tag: 2"
	"ACHIEVEMENT_EVENT_EZ_NXTGEN_03"      : "[EZ] LG Tag: 3"
	"ACHIEVEMENT_EVENT_EZ_NXTGEN_04"      : "[EZ] LG Tag: 4"
	"ACHIEVEMENT_EVENT_EZ_NXTGEN_05"      : "[EZ] LG Tag: 5"
	"ACHIEVEMENT_EVENT_EZ_NXTGEN_06"      : "[EZ] LG Tag: 6"
	"ACHIEVEMENT_EVENT_EZ_NXTGEN_07"      : "[EZ] LG Tag: 7"

	// Entropy Zero
	"ACHIEVEMENT_EVENT_EZ_POEM_01"
	"ACHIEVEMENT_EVENT_EZ_POEM_02"
	"ACHIEVEMENT_EVENT_EZ_POEM_03"
	"ACHIEVEMENT_EVENT_EZ_POEM_04"
	"ACHIEVEMENT_EVENT_EZ_POEM_05"
	"ACHIEVEMENT_EVENT_EZ_POEM_06"
	"ACHIEVEMENT_EVENT_EZ_POEM_07"
	"ACHIEVEMENT_EVENT_EZ_POEM_08"
	"ACHIEVEMENT_EVENT_EZ_POEM_09"
	"ACHIEVEMENT_EVENT_EZ_POEM_10"
	"ACHIEVEMENT_EVENT_EZ_PCAN"
	"ACHIEVEMENT_EVENT_EZ_TCAN"
	"ACHIEVEMENT_EVENT_EZ_SCHISM"
	"ACHIEVEMENT_EVENT_EZ_SLUCK"
	"ACHIEVEMENT_EVENT_EZ_SEATER"
	"ACHIEVEMENT_EVENT_EZ_DEXPLOIT"
	"ACHIEVEMENT_EVENT_EZ_KCOP"
	"ACHIEVEMENT_EVENT_EZ_VDT"
	"ACHIEVEMENT_EVENT_EZ_SALIVE"
	"ACHIEVEMENT_EVENT_EZ_MGUN"
	"ACHIEVEMENT_EVENT_EZ_BSJOB"
	"ACHIEVEMENT_EVENT_EZ_SOLO"
	"ACHIEVEMENT_EVENT_EZ_OUTBREAK"
	"ACHIEVEMENT_EVENT_EZ_VSOUL"
	"ACHIEVEMENT_EVENT_EZ_OICE"
	"ACHIEVEMENT_EVENT_EZ_PE"
	"ACHIEVEMENT_EVENT_EZ_START_NOPLAYERDEATHS"
	"ACHIEVEMENT_EVENT_EZ_STOP_NOPLAYERDEATH"
	"EZ_START_MODE_EASY"
	"EZ_STOP_MODE_EASY"

	"EZ_START_MODE_NORMAL"
	"EZ_STOP_MODE_NORMAL"

	"EZ_START_MODE_HARD"
	"EZ_STOP_MODE_HARD"


*/


// Allows map logic to send achievement related events to the achievement system.
class CLogicAchievement : public CLogicalEntity
{
public:
	DECLARE_CLASS( CLogicAchievement, CLogicalEntity );

	CLogicAchievement();

protected:

	// Inputs
	void InputFireEvent( inputdata_t &inputdata );
	void InputEnable( inputdata_t &inputdata );
	void InputDisable( inputdata_t &inputdata );
	void InputToggle( inputdata_t &inputdata );
	
	bool			m_bDisabled;
	string_t		m_iszAchievementEventID;				// Which achievement event this entity marks

	COutputEvent	m_OnFired;

	DECLARE_DATADESC();
};


LINK_ENTITY_TO_CLASS( logic_achievement, CLogicAchievement );


BEGIN_DATADESC( CLogicAchievement )

	DEFINE_KEYFIELD( m_bDisabled, FIELD_BOOLEAN, "StartDisabled" ),
	DEFINE_KEYFIELD( m_iszAchievementEventID, FIELD_STRING, "AchievementEvent" ),

	// Inputs
	DEFINE_INPUTFUNC( FIELD_VOID, "FireEvent", InputFireEvent ),
	DEFINE_INPUTFUNC( FIELD_VOID, "Enable", InputEnable ),
	DEFINE_INPUTFUNC( FIELD_VOID, "Disable", InputDisable ),
	DEFINE_INPUTFUNC( FIELD_VOID, "Toggle", InputToggle ),

	// Outputs
	DEFINE_OUTPUT( m_OnFired, "OnFired" ),

END_DATADESC()



//-----------------------------------------------------------------------------
// Purpose: Constructor.
//-----------------------------------------------------------------------------
CLogicAchievement::CLogicAchievement(void)
{
	m_iszAchievementEventID		= NULL_STRING;
}

#define ACHIEVEMENT_PREFIX	"ACHIEVEMENT_EVENT_"

//-----------------------------------------------------------------------------
// Purpose: Sends the achievement event to the achievement marking system.
//-----------------------------------------------------------------------------
void CLogicAchievement::InputFireEvent( inputdata_t &inputdata )
{
	// If we're active, and our string matched a valid achievement ID
	if ( !m_bDisabled  && m_iszAchievementEventID != NULL_STRING)
	{
		m_OnFired.FireOutput( inputdata.pActivator, this );

		char const *pchName = STRING( m_iszAchievementEventID );

		int nPrefixLen = Q_strlen( ACHIEVEMENT_PREFIX );
		if ( !Q_strnicmp( pchName, ACHIEVEMENT_PREFIX, nPrefixLen ) )
		{
			// Skip the prefix
			pchName += nPrefixLen;
			if ( pchName && *pchName )
			{
				CBroadcastRecipientFilter filter;
				g_pGameRules->MarkAchievement( filter, pchName );
			}
		}
	}
}

//------------------------------------------------------------------------------
// Purpose: Turns on the relay, allowing it to fire outputs.
//------------------------------------------------------------------------------
void CLogicAchievement::InputEnable( inputdata_t &inputdata )
{
	m_bDisabled = false;
}

//------------------------------------------------------------------------------
// Purpose: Turns off the relay, preventing it from firing outputs.
//------------------------------------------------------------------------------
void CLogicAchievement::InputDisable( inputdata_t &inputdata )
{ 
	m_bDisabled = true;
}


//------------------------------------------------------------------------------
// Purpose: Toggles the enabled/disabled state of the relay.
//------------------------------------------------------------------------------
void CLogicAchievement::InputToggle( inputdata_t &inputdata )
{ 
	m_bDisabled = !m_bDisabled;
}