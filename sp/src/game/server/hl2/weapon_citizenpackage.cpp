//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "weapon_citizenpackage.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_SERVERCLASS_ST(CWeaponCitizenPackage, DT_WeaponCitizenPackage)
END_SEND_TABLE()

BEGIN_DATADESC( CWeaponCitizenPackage )
END_DATADESC()

LINK_ENTITY_TO_CLASS( weapon_citizenpackage, CWeaponCitizenPackage );
PRECACHE_WEAPON_REGISTER(weapon_citizenpackage);

acttable_t	CWeaponCitizenPackage::m_acttable[] = 
{
	{ ACT_IDLE,						ACT_IDLE_PACKAGE,					false },
	{ ACT_WALK,						ACT_WALK_PACKAGE,					false },
};
IMPLEMENT_ACTTABLE(CWeaponCitizenPackage);

classtable_t CWeaponCitizenPackage::m_classtable[] =
{
	{ PLC_PLAYER, true },
	{ PLC_CITIZEN, true },
	{ PLC_REBEL, true },
	{ PLC_MANHACK, false },
	{ PLC_METROPOLICE, true },
	{ PLC_COMBINE_GUARD, false },
	{ PLC_COMBINE_SOLDIER, false },
	{ PLC_COMBINE_ELITE, false },
	{ PLC_STALKER, false },
	{ PLC_ZOMBIE, false },
	{ PLC_ZOMBIE_POISON, false },
	{ PLC_ZOMBIE_FAST, false },
	{ PLC_ZOMBIE_COMBINE, false }
};

IMPLEMENT_CLASSTABLE(CWeaponCitizenPackage);

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponCitizenPackage::ItemPostFrame( void )
{
	// Do nothing
}

//-----------------------------------------------------------------------------
// Purpose: Remove the citizen package if it's ever dropped
//-----------------------------------------------------------------------------
void CWeaponCitizenPackage::Drop( const Vector &vecVelocity )
{
	BaseClass::Drop( vecVelocity );
	UTIL_Remove( this );
}



//-----------------------------------------------------------------------------
// Purpose: Citizen suitcase
//-----------------------------------------------------------------------------
class CWeaponCitizenSuitcase : public CWeaponCitizenPackage
{
	DECLARE_CLASS( CWeaponCitizenSuitcase, CWeaponCitizenPackage );
public:
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();	
	DECLARE_ACTTABLE();
	DECLARE_CLASSTABLE();
};

IMPLEMENT_SERVERCLASS_ST(CWeaponCitizenSuitcase, DT_WeaponCitizenSuitcase)
END_SEND_TABLE()

BEGIN_DATADESC( CWeaponCitizenSuitcase )
END_DATADESC()

LINK_ENTITY_TO_CLASS( weapon_citizensuitcase, CWeaponCitizenSuitcase );
PRECACHE_WEAPON_REGISTER(weapon_citizensuitcase);

acttable_t	CWeaponCitizenSuitcase::m_acttable[] = 
{
	{ ACT_IDLE,						ACT_IDLE_SUITCASE,					false },
	{ ACT_WALK,						ACT_WALK_SUITCASE,					false },
};
IMPLEMENT_ACTTABLE(CWeaponCitizenSuitcase);

classtable_t CWeaponCitizenSuitcase::m_classtable[] =
{
	{ PLC_PLAYER, true },
	{ PLC_CITIZEN, true },
	{ PLC_REBEL, true },
	{ PLC_MANHACK, false },
	{ PLC_METROPOLICE, true },
	{ PLC_COMBINE_GUARD, false },
	{ PLC_COMBINE_SOLDIER, false },
	{ PLC_COMBINE_ELITE, false },
	{ PLC_STALKER, false },
	{ PLC_ZOMBIE, false },
	{ PLC_ZOMBIE_POISON, false },
	{ PLC_ZOMBIE_FAST, false },
	{ PLC_ZOMBIE_COMBINE, false }
};

IMPLEMENT_CLASSTABLE(CWeaponCitizenSuitcase);
