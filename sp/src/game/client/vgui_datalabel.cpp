//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: This is a panel which is rendered image on top of an entity
//
// $Revision: $
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#pragma warning (disable: 4514)

#include "vgui_datalabel.h"
#include <KeyValues.h>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CDataLabel::CDataLabel(vgui::Panel *pParent, const char *pName, const char *pText) :
BaseClass(pParent, pName, pText)
{
}

CDataLabel::~CDataLabel()
{
}


//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
bool CDataLabel::Init(KeyValues* pInitData)
{
	 // Unimplemented
	 Assert(0);
	 return true;
}


//-----------------------------------------------------------------------------
// initialization from build-mode dialog style .res files
//-----------------------------------------------------------------------------
void CDataLabel::ApplySettings(KeyValues *inResourceData)
{
	BaseClass::ApplySettings(inResourceData);

	 if (m_eDataType == LABEL_DATATYPE_NONE) {
		  const char *labelData = inResourceData->GetString("labelData", NULL);
		  if (*labelData)
		  {
				if (strcmp(labelData, "player") == 0)
					 m_eDataType = LABEL_DATATYPE_PLAYER;
		  }
	 }
	 
	 if (m_eDataVar == LABEL_PLAYERVARIABLE_NONE && m_eDataType == LABEL_DATATYPE_PLAYER){
		  const char *labelVars = inResourceData->GetString("labelVars", NULL);
		  if (*labelVars)
		  {
				const char* token = strtok(const_cast<char*>(labelVars), ",");
				int position = 0;

				while (token != nullptr && position < 4) {
					 std::string item(token);

					 if (item == "name")
						  m_eDataVar |= LABEL_PLAYERVARIABLE_NAME << (position * 4);
					 if (item == "id")
						  m_eDataVar |= LABEL_PLAYERVARIABLE_CITIZENID << (position * 4);
					 else if (item == "conversions")
						 m_eDataVar |= LABEL_PLAYERVARIABLE_MEMREPLACEMENTS << (position * 4);
					 else if (item == "memory")
						 m_eDataVar |= LABEL_PLAYERVARIABLE_MEMORY << (position * 4);
					 else if (item == "class")
						 m_eDataVar |= LABEL_PLAYERVARIABLE_CLASS << (position * 4);
					 else if (item == "faction") // TODO
						 m_eDataVar |= LABEL_PLAYERVARIABLE_FACTION << (position * 4);
					 else if (item == "job")
						 m_eDataVar |= LABEL_PLAYERVARIABLE_JOB << (position * 4);
					 else if (item == "squad")
						 m_eDataVar |= LABEL_PLAYERVARIABLE_SQUAD << (position * 4);
					 else if (item == "unit") // TODO
						  m_eDataVar |= LABEL_PLAYERVARIABLE_UNIT << (position * 4);
					 else if (item == "city")
						  m_eDataVar |= LABEL_PLAYERVARIABLE_CITY << (position * 4);
					 else if (item == "credits")
						  m_eDataVar |= LABEL_PLAYERVARIABLE_CREDITS << (position * 4);
					 else if (item == "rank")
						  m_eDataVar |= LABEL_PLAYERVARIABLE_RANK << (position * 4);
					 else if (item == "loyalty") // TODO
						  m_eDataVar |= LABEL_PLAYERVARIABLE_LOYALTY << (position * 4);
					 else if (item == "rations")
						 m_eDataVar |= LABEL_PLAYERVARIABLE_RATIONS << (position * 4);
					 else if (item == "resin") // TODO
						 m_eDataVar |= LABEL_PLAYERVARIABLE_RESIN << (position * 4);

					 position++;
					 token = strtok(nullptr, ",");
				}
		  }
	 }

	 m_sLabelFormat = inResourceData->GetString("labelFormat", NULL);
	 UpdateData();
}

void CDataLabel::UpdateData() {
	if (*m_sLabelFormat && m_eDataType == LABEL_DATATYPE_PLAYER && m_eDataVar != LABEL_PLAYERVARIABLE_NONE) {

		char text[256];

		if (m_eDataVar > 0xF00) {
			V_snprintf(text, 256, m_sLabelFormat, GetPlayerVariable(0), GetPlayerVariable(1), GetPlayerVariable(2), GetPlayerVariable(3));
		}
		else if (m_eDataVar > 0xF0) {
			V_snprintf(text, 256, m_sLabelFormat, GetPlayerVariable(0), GetPlayerVariable(1), GetPlayerVariable(2));
		}
		else if (m_eDataVar > 0xF) {
			V_snprintf(text, 256, m_sLabelFormat, GetPlayerVariable(0), GetPlayerVariable(1));
		}
		else {
			V_snprintf(text, 256, m_sLabelFormat, GetPlayerVariable(0));
		}

		SetText(GetPlayerVariable(0));
	}
}

const char* CDataLabel::GetPlayerVariable(uint position){
	 // Use a bitmask (0xF) to extract the rightmost 4 bits after shifting
	 LabelPlayerVariable_t extract_Variable = static_cast<LabelPlayerVariable_t>((m_eDataVar >> (position * 4)) & 0xF);
	 C_BasePlayer *pPlayer = C_BasePlayer::GetLocalPlayer();

	 char* text = new char[256];

	 if (pPlayer) {
		  switch (extract_Variable) {
		  case LABEL_PLAYERVARIABLE_NAME:
				return pPlayer->GetPlayerName();
				break;
		  case LABEL_PLAYERVARIABLE_CITIZENID:
				return pPlayer->GetCitizenId();
				break;
		  case LABEL_PLAYERVARIABLE_MEMREPLACEMENTS:
				V_snprintf(text, 256, "%d", pPlayer->m_iMemRepl);
				break;
		  case LABEL_PLAYERVARIABLE_MEMORY:
			  V_snprintf(text, 256, "%d", pPlayer->m_iMemory);
			  break;
		  case LABEL_PLAYERVARIABLE_CLASS:
			  V_snprintf(text, 256, "%d", CBasePlayer::GetPlayerClass(pPlayer->m_Class));
			  break;
		  case LABEL_PLAYERVARIABLE_FACTION:	// TODO
				// V_snprintf(text, 256, "%d", pPlayer->m_Faction);
				break;
		  case LABEL_PLAYERVARIABLE_JOB:
				return C_BaseEntity::GetJob(pPlayer->m_Job);
				break;
		  case LABEL_PLAYERVARIABLE_SQUAD:
				V_snprintf(text, 256, "%d", pPlayer->m_iSquad);
				break;
		  case LABEL_PLAYERVARIABLE_UNIT:	// TODO
				// V_snprintf(text, 256, "%d", pPlayer->);
				break;
		  case LABEL_PLAYERVARIABLE_CITY:
				V_snprintf(text, 256, "%d", pPlayer->m_iCity);
				break;
		  case LABEL_PLAYERVARIABLE_CREDITS:
				V_snprintf(text, 256, "%d", pPlayer->m_iCredits);
				break;
		  case LABEL_PLAYERVARIABLE_RANK:
				V_snprintf(text, 256, "%d", pPlayer->m_iRank);
				break;
		  case LABEL_PLAYERVARIABLE_LOYALTY:	// TODO
				// V_snprintf(text, 256, "%d", pPlayer->);
				break;
		  case LABEL_PLAYERVARIABLE_RATIONS:
				V_snprintf(text, 256, "%d", pPlayer->m_iRation);
				break;
		  case LABEL_PLAYERVARIABLE_RESIN:	// TODO
				// V_snprintf(text, 256, "%d", pPlayer->m_iResin);
				break;
		  default:
				return "";
		  }
		  
		  return text;
	 }
	 else
	 {
		  return "";
	 }


}


