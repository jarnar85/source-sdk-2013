//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef BASEENTITY_SHARED_H
#define BASEENTITY_SHARED_H
#ifdef _WIN32
#pragma once
#endif

#include <map>

extern ConVar hl2_episodic;

// Simple shared header file for common base entities

// entity capabilities
// These are caps bits to indicate what an object's capabilities (currently used for +USE, save/restore and level transitions)
#define		FCAP_MUST_SPAWN				0x00000001		// Spawn after restore
#define		FCAP_ACROSS_TRANSITION		0x00000002		// should transfer between transitions 
// UNDONE: This will ignore transition volumes (trigger_transition), but not the PVS!!!
#define		FCAP_FORCE_TRANSITION		0x00000004		// ALWAYS goes across transitions
#define		FCAP_NOTIFY_ON_TRANSITION	0x00000008		// Entity will receive Inside/Outside transition inputs when a transition occurs

#define		FCAP_IMPULSE_USE			0x00000010		// can be used by the player
#define		FCAP_CONTINUOUS_USE			0x00000020		// can be used by the player
#define		FCAP_ONOFF_USE				0x00000040		// can be used by the player
#define		FCAP_DIRECTIONAL_USE		0x00000080		// Player sends +/- 1 when using (currently only tracktrains)
// NOTE: Normally +USE only works in direct line of sight.  Add these caps for additional searches
#define		FCAP_USE_ONGROUND			0x00000100
#define		FCAP_USE_IN_RADIUS			0x00000200
#define		FCAP_SAVE_NON_NETWORKABLE	0x00000400

#define		FCAP_MASTER					0x10000000		// Can be used to "master" other entities (like multisource)
#define		FCAP_WCEDIT_POSITION		0x40000000		// Can change position and update Hammer in edit mode
#define		FCAP_DONT_SAVE				0x80000000		// Don't save this


// How many bits are used to transmit parent attachment indices?
#define NUM_PARENTATTACHMENT_BITS	6

// Maximum number of vphysics objects per entity
#define VPHYSICS_MAX_OBJECT_LIST_COUNT	1024


// For CLASSIFY
enum Class_T
{
	// ALL
	CLASS_NONE = 0,
	CLASS_PLAYER,
	CLASS_PLAYER_ALLY,

	
	// HL2 + INVASION
	CLASS_PLAYER_ALLY_VITAL,
	CLASS_ANTLION,
	CLASS_BARNACLE,
	CLASS_BULLSEYE,
	CLASS_BULLSQUID,	
	CLASS_CITIZEN_PASSIVE,
	CLASS_CITIZEN_REBEL,
	CLASS_COMBINE,
	CLASS_COMBINE_GUNSHIP,
	CLASS_CONSCRIPT,
	CLASS_HEADCRAB,
	CLASS_HOUNDEYE,
	CLASS_MANHACK,
	CLASS_METROPOLICE,
	CLASS_MILITARY,
	CLASS_SCANNER,
	CLASS_STALKER,
	CLASS_VORTIGAUNT,
	CLASS_ZOMBIE,
	CLASS_PROTOSNIPER,
	CLASS_MISSILE,
	CLASS_FLARE,
	CLASS_EARTH_FAUNA,
	CLASS_HACKED_ROLLERMINE,
	CLASS_COMBINE_HUNTER,

	// HL1
	CLASS_MACHINE,
	CLASS_HUMAN_PASSIVE,
	CLASS_HUMAN_MILITARY,
	CLASS_ALIEN_MILITARY,
	CLASS_ALIEN_MONSTER,
	CLASS_ALIEN_PREY,
	CLASS_ALIEN_PREDATOR,
	CLASS_INSECT,
	CLASS_PLAYER_BIOWEAPON,
	CLASS_ALIEN_BIOWEAPON,

	// Logical additions 
	CLASS_HECU,
	CLASS_POLICE,
	CLASS_SCIENTIST,


	NUM_AI_CLASSES
};

enum PlayerClass_T
{
	PLC_NONE = 0,
	PLC_PLAYER,
	PLC_CITIZEN,
	PLC_MEDIC,
	PLC_POLICE,
	PLC_SCIENTIST,
	PLC_SOLDIER,
	PLC_REBEL,
	PLC_REBEL_MEDIC,
	PLC_MANHACK,
	PLC_METROPOLICE,
	PLC_CONSCRIPT,
	PLC_COMBINE_CHARGER,
	PLC_COMBINE_ELITE,
	PLC_COMBINE_GRUNT,
	PLC_COMBINE_HEAVY,
	PLC_COMBINE_MEDIC,
	PLC_COMBINE_ORDINAL,
	PLC_COMBINE_PRISONGUARD,
	PLC_COMBINE_PRISONHEAVY,
	PLC_COMBINE_SOLDIER,
	PLC_COMBINE_SUPPRESSOR,
	PLC_COMBINE_WORKER,
	PLC_COMBINE_WORKER_HAZMAT,
	PLC_STALKER,
	PLC_ZOMBIE,
	PLC_ZOMBIE_POISON,
	PLC_ZOMBIE_FAST,
	PLC_ZOMBIE_COMBINE,

	NUM_PC_CLASSES
};

enum Job_T
{
	JOB_NONE = 0,
	JOB_BRUTE,
	JOB_DISINFECTOR,
	JOB_ENGINEER,
	JOB_GUARD,
	JOB_HEAVY,
	JOB_MEDIC,
	JOB_OFFICER,
	JOB_PILOT,
	JOB_SCIENTIST,
	JOB_SNIPER,
	JOB_SOLDIER,
	JOB_WORKER,

	NUM_JOB_CLASSES
};


const std::map<const char *, Class_T> Class_M = {
	{ "CLASS_NONE",					CLASS_NONE},
	{ "CLASS_PLAYER",				CLASS_PLAYER},
	{ "CLASS_PLAYER_ALLY",			CLASS_PLAYER_ALLY},
	{ "CLASS_PLAYER_ALLY_VITAL",	CLASS_PLAYER_ALLY_VITAL},
	{ "CLASS_ANTLION",				CLASS_ANTLION},
	{ "CLASS_BARNACLE",				CLASS_BARNACLE},
	{ "CLASS_BULLSEYE",				CLASS_BULLSEYE},
	{ "CLASS_BULLSQUID",			CLASS_BULLSQUID},
	{ "CLASS_CITIZEN_PASSIVE",		CLASS_CITIZEN_PASSIVE},
	{ "CLASS_CITIZEN_REBEL",		CLASS_CITIZEN_REBEL },
	{ "CLASS_COMBINE",				CLASS_COMBINE},
	{ "CLASS_COMBINE_GUNSHIP",		CLASS_COMBINE_GUNSHIP},
	{ "CLASS_CONSCRIPT",			CLASS_CONSCRIPT},
	{ "CLASS_HEADCRAB",				CLASS_HEADCRAB},
	{ "CLASS_HOUNDEYE",				CLASS_HOUNDEYE},
	{ "CLASS_MANHACK",				CLASS_MANHACK},
	{ "CLASS_METROPOLICE",			CLASS_METROPOLICE},
	{ "CLASS_MILITARY",				CLASS_MILITARY},
	{ "CLASS_SCANNER",				CLASS_SCANNER},
	{ "CLASS_STALKER",				CLASS_STALKER},
	{ "CLASS_VORTIGAUNT",			CLASS_VORTIGAUNT},
	{ "CLASS_ZOMBIE",				CLASS_ZOMBIE},
	{ "CLASS_PROTOSNIPER",			CLASS_PROTOSNIPER},
	{ "CLASS_MISSILE",				CLASS_MISSILE},
	{ "CLASS_FLARE",				CLASS_FLARE},
	{ "CLASS_EARTH_FAUNA",			CLASS_EARTH_FAUNA},
	{ "CLASS_HACKED_ROLLERMINE",	CLASS_HACKED_ROLLERMINE},
	{ "CLASS_COMBINE_HUNTER",		CLASS_COMBINE_HUNTER},
	{ "CLASS_MACHINE",				CLASS_MACHINE},
	{ "CLASS_HUMAN_PASSIVE",		CLASS_HUMAN_PASSIVE},
	{ "CLASS_HUMAN_MILITARY",		CLASS_HUMAN_MILITARY},
	{ "CLASS_ALIEN_MILITARY",		CLASS_ALIEN_MILITARY},
	{ "CLASS_ALIEN_MONSTER",		CLASS_ALIEN_MONSTER},
	{ "CLASS_ALIEN_PREY",			CLASS_ALIEN_PREY},
	{ "CLASS_ALIEN_PREDATOR",		CLASS_ALIEN_PREDATOR},
	{ "CLASS_INSECT",				CLASS_INSECT},
	{ "CLASS_PLAYER_BIOWEAPON",		CLASS_PLAYER_BIOWEAPON},
	{ "CLASS_ALIEN_BIOWEAPON",		CLASS_ALIEN_BIOWEAPON },
	{ "CLASS_HECU",					CLASS_HECU },
	{ "CLASS_POLICE",				CLASS_POLICE },
	{ "CLASS_SCIENTIST",			CLASS_SCIENTIST }
};

const std::map<const char*, PlayerClass_T> PlayerClass_M = {
	{ "PLC_NONE",					PLC_NONE},
	{ "PLC_PLAYER",					PLC_PLAYER},
	{ "PLC_CITIZEN",				PLC_CITIZEN},
	{ "PLC_SOLDIER",				PLC_SOLDIER },
	{ "PLC_MEDIC",					PLC_MEDIC },
	{ "PLC_POLICE",					PLC_POLICE },
	{ "PLC_SCIENTIST",				PLC_SCIENTIST },
	{ "PLC_REBEL",					PLC_REBEL},
	{ "PLC_REBEL_MEDIC",			PLC_REBEL_MEDIC},
	{ "PLC_MANHACK",				PLC_MANHACK},
	{ "PLC_CONSCRIPT",				PLC_CONSCRIPT },
	{ "PLC_METROPOLICE",			PLC_METROPOLICE },
	{ "PLC_COMBINE_CHARGER",		PLC_COMBINE_CHARGER },
	{ "PLC_COMBINE_ELITE",			PLC_COMBINE_ELITE },
	{ "PLC_COMBINE_GRUNT",			PLC_COMBINE_GRUNT },
	{ "PLC_COMBINE_HEAVY",			PLC_COMBINE_HEAVY },
	{ "PLC_COMBINE_MEDIC",			PLC_COMBINE_MEDIC },
	{ "PLC_COMBINE_ORDINAL",		PLC_COMBINE_ORDINAL },
	{ "PLC_COMBINE_PRISONGUARD",	PLC_COMBINE_PRISONGUARD },
	{ "PLC_COMBINE_PRISONHEAVY",	PLC_COMBINE_PRISONHEAVY },
	{ "PLC_COMBINE_SOLDIER",		PLC_COMBINE_SOLDIER },
	{ "PLC_COMBINE_SUPPRESSOR",		PLC_COMBINE_SUPPRESSOR },
	{ "PLC_COMBINE_WORKER",			PLC_COMBINE_WORKER },
	{ "PLC_COMBINE_WORKER_HAZMAT",	PLC_COMBINE_WORKER_HAZMAT },
	{ "PLC_STALKER",				PLC_STALKER},
	{ "PLC_ZOMBIE",					PLC_ZOMBIE},
	{ "PLC_ZOMBIE_POISON",			PLC_ZOMBIE_POISON},
	{ "PLC_ZOMBIE_FAST",			PLC_ZOMBIE_FAST},
	{ "PLC_ZOMBIE_COMBINE",			PLC_ZOMBIE_COMBINE}
};

const std::map<const char*, Job_T> Job_M = {
	{"JOB_NONE",		JOB_NONE},
	{"JOB_BRUTE",		JOB_BRUTE },
	{"JOB_DISINFECTOR",	JOB_DISINFECTOR },
	{"JOB_ENGINEER",	JOB_ENGINEER },
	{"JOB_GUARD",		JOB_GUARD },
	{"JOB_HEAVY",		JOB_HEAVY },
	{"JOB_MEDIC",		JOB_MEDIC},
	{"JOB_OFFICER",		JOB_OFFICER},
	{"JOB_SCIENTIST",	JOB_SCIENTIST},
	{"JOB_SNIPER",		JOB_SNIPER },
	{"JOB_SOLDIER",		JOB_SOLDIER },
	{"JOB_WORKER",		JOB_WORKER }
};


//-----------------------------------------------------------------------------
// For invalidate physics recursive
//-----------------------------------------------------------------------------
enum InvalidatePhysicsBits_t
{
	POSITION_CHANGED	= 0x1,
	ANGLES_CHANGED		= 0x2,
	VELOCITY_CHANGED	= 0x4,
	ANIMATION_CHANGED	= 0x8,
};


#if defined( CLIENT_DLL )
#include "c_baseentity.h"
#include "c_baseanimating.h"
#else
#include "baseentity.h"

#ifdef HL2_EPISODIC
	#include "info_darknessmode_lightsource.h"
#endif // HL2_EPISODIC

#endif

#if !defined( NO_ENTITY_PREDICTION )
// CBaseEntity inlines
inline bool CBaseEntity::IsPlayerSimulated( void ) const
{
	return m_bIsPlayerSimulated;
}

inline CBasePlayer *CBaseEntity::GetSimulatingPlayer( void )
{
	return m_hPlayerSimulationOwner;
}
#endif

inline MoveType_t CBaseEntity::GetMoveType() const
{
	return (MoveType_t)(unsigned char)m_MoveType;
}

inline MoveCollide_t CBaseEntity::GetMoveCollide() const
{
	return (MoveCollide_t)(unsigned char)m_MoveCollide;
}

//-----------------------------------------------------------------------------
// Collision group accessors
//-----------------------------------------------------------------------------
inline int CBaseEntity::GetCollisionGroup() const
{
	return m_CollisionGroup;
}

inline int	CBaseEntity::GetFlags( void ) const
{
	return m_fFlags;
}

inline bool CBaseEntity::IsAlive( void )
{
	return m_lifeState == LIFE_ALIVE; 
}

inline CBaseEntity	*CBaseEntity::GetOwnerEntity() const
{
	return m_hOwnerEntity.Get();
}

inline CBaseEntity	*CBaseEntity::GetEffectEntity() const
{
	return m_hEffectEntity.Get();
}

inline int CBaseEntity::GetPredictionRandomSeed( void )
{
	return m_nPredictionRandomSeed;
}

inline CBasePlayer *CBaseEntity::GetPredictionPlayer( void )
{
	return m_pPredictionPlayer;
}

inline void CBaseEntity::SetPredictionPlayer( CBasePlayer *player )
{
	m_pPredictionPlayer = player;
}


inline bool CBaseEntity::IsSimulatedEveryTick() const
{
	return m_bSimulatedEveryTick;
}

inline bool CBaseEntity::IsAnimatedEveryTick() const
{
	return m_bAnimatedEveryTick;
}

inline void CBaseEntity::SetSimulatedEveryTick( bool sim )
{
	if ( m_bSimulatedEveryTick != sim )
	{
		m_bSimulatedEveryTick = sim;
#ifdef CLIENT_DLL
		Interp_UpdateInterpolationAmounts( GetVarMapping() );
#endif
	}
}

inline void CBaseEntity::SetAnimatedEveryTick( bool anim )
{
	if ( m_bAnimatedEveryTick != anim )
	{
		m_bAnimatedEveryTick = anim;
#ifdef CLIENT_DLL
		Interp_UpdateInterpolationAmounts( GetVarMapping() );
#endif
	}
}

inline float CBaseEntity::GetAnimTime() const
{
	return m_flAnimTime;
}

inline float CBaseEntity::GetSimulationTime() const
{
	return m_flSimulationTime;
}

inline void CBaseEntity::SetAnimTime( float at )
{
	m_flAnimTime = at;
}

inline void CBaseEntity::SetSimulationTime( float st )
{
	m_flSimulationTime = st;
}

inline int CBaseEntity::GetEffects( void ) const
{ 
	return m_fEffects; 
}

inline void CBaseEntity::RemoveEffects( int nEffects ) 
{ 
#if !defined( CLIENT_DLL )
#ifdef HL2_EPISODIC
	if ( nEffects & (EF_BRIGHTLIGHT|EF_DIMLIGHT) )
	{
		// Hack for now, to avoid player emitting radius with his flashlight
		if ( !IsPlayer() )
		{
			RemoveEntityFromDarknessCheck( this );
		}
	}
#endif // HL2_EPISODIC
#endif // !CLIENT_DLL

	m_fEffects &= ~nEffects;
	if ( nEffects & EF_NODRAW )
	{
#ifndef CLIENT_DLL
		NetworkProp()->MarkPVSInformationDirty();
		DispatchUpdateTransmitState();
#else
		UpdateVisibility();
#endif
	}
}

inline void CBaseEntity::ClearEffects( void ) 
{ 
#if !defined( CLIENT_DLL )
#ifdef HL2_EPISODIC
	if ( m_fEffects & (EF_BRIGHTLIGHT|EF_DIMLIGHT) )
	{
		// Hack for now, to avoid player emitting radius with his flashlight
		if ( !IsPlayer() )
		{
			RemoveEntityFromDarknessCheck( this );
		}
	}
#endif // HL2_EPISODIC
#endif // !CLIENT_DLL

	m_fEffects = 0;
#ifndef CLIENT_DLL
		DispatchUpdateTransmitState();
#else
		UpdateVisibility();
#endif
}

inline bool CBaseEntity::IsEffectActive( int nEffects ) const
{ 
	return (m_fEffects & nEffects) != 0; 
}

// Shared EntityMessage between game and client .dlls
#define BASEENTITY_MSG_REMOVE_DECALS	1

extern float k_flMaxEntityPosCoord;
extern float k_flMaxEntityEulerAngle;
extern float k_flMaxEntitySpeed;
extern float k_flMaxEntitySpinRate;

inline bool IsEntityCoordinateReasonable ( const vec_t c )
{
	float r = k_flMaxEntityPosCoord;
	return c > -r && c < r;
}

inline bool IsEntityPositionReasonable( const Vector &v )
{
	float r = k_flMaxEntityPosCoord;
	return
		v.x > -r && v.x < r &&
		v.y > -r && v.y < r &&
		v.z > -r && v.z < r;
}

// Returns:
//   -1 - velocity is really, REALLY bad and probably should be rejected.
//   0  - velocity was suspicious and clamped.
//   1  - velocity was OK and not modified
extern int CheckEntityVelocity( Vector &v );

inline bool IsEntityQAngleReasonable( const QAngle &q )
{
	float r = k_flMaxEntityEulerAngle;
	return
		q.x > -r && q.x < r &&
		q.y > -r && q.y < r &&
		q.z > -r && q.z < r;
}

// Angular velocity in exponential map form
inline bool IsEntityAngularVelocityReasonable( const Vector &q )
{
	float r = k_flMaxEntitySpinRate;
	return
		q.x > -r && q.x < r &&
		q.y > -r && q.y < r &&
		q.z > -r && q.z < r;
}

// Angular velocity of each Euler angle.
inline bool IsEntityQAngleVelReasonable( const QAngle &q )
{
	float r = k_flMaxEntitySpinRate;
	return
		q.x > -r && q.x < r &&
		q.y > -r && q.y < r &&
		q.z > -r && q.z < r;
}

extern bool CheckEmitReasonablePhysicsSpew();


#endif // BASEENTITY_SHARED_H
