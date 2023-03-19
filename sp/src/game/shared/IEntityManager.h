#ifndef ENTITYDATA_H
#define ENTITYDATA_H
#ifdef _WIN32
#pragma once
#endif

// handling the basic entity data needed from an external source
struct HEntityData {
	const char *szModel;	// body model name (thirdperson/NPC)
	const char *szArms;		// arm model name (firstperson)
	const char *szNpcAi;	// AI handle for NPCs

	int iMaxHealth;
	
	Class_T nFaction;
	Job_T nJob;
	gender_t nGender;

	CUtlVector<const char *> lWeapons;
};

// This class manages additional entities loaded from external data (mod specific extensions)
class IEntityManager
{
	CUtlVector<HEntityData *> l_Entities;

	bool LoadEntityFromFile(const std::string& path);
};

#endif	// ENTITYDATA_H