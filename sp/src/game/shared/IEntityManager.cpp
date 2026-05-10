#include "cbase.h"
#include "IEntityManager.h"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Loading entity data from an external file
bool IEntityManager::LoadEntityFromFile(const std::string& path)
{
	HEntityData entity;
	
	// auto data = toml::parse(path);
	
	// entity.szModel		 = static_cast<char *>(toml::find(data, "Model.Body"));
	// entity.szArms		 = static_cast<char *>(toml::find_or(data, "Model.Arms", "models/weapons/v_hands.mdl"));
	// entity.szNpcAi		 = static_cast<char *>(toml::find(data, "NPC.ai"));
	
	// entity.iMaxHealth	 = static_cast<int>(toml::find_or(data, "Health", 100));
	
	// entity.lWeapons = toml::get<CUtlVector::vector<char *>>(toml::find(data "Weapons"));



	return false;
}