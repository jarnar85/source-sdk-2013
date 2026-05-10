//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: This is a panel which is rendered image on top of an entity
//
// $Revision: $
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#pragma warning (disable: 4514)

#include "vgui_databutton.h"
#include <KeyValues.h>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CDataButton::CDataButton(vgui::Panel *pParent, const char *pName, const char *pText) :
BaseClass(pParent, pName, pText)
{
}

CDataButton::~CDataButton()
{
}


//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
bool CDataButton::Init(KeyValues* pInitData)
{
	 // Unimplemented
	 Assert(0);
	 return true;
}


//-----------------------------------------------------------------------------
// initialization from build-mode dialog style .res files
//-----------------------------------------------------------------------------
void CDataButton::ApplySettings(KeyValues *inResourceData)
{
	 BaseClass::ApplySettings(inResourceData);

	 if (m_eDataType == BUTTON_DATATYPE_NONE) {
		  const char *labelData = inResourceData->GetString("labelData", NULL);
		  if (*labelData)
		  {
				if (strcmp(labelData, "player") == 0)
					 m_eDataType = BUTTON_DATATYPE_PLAYER;
		  }
	 }
	 
	 if (m_eDataVar == BUTTON_PLAYERVARIABLE_NONE && m_eDataType == BUTTON_DATATYPE_PLAYER){
		  const char *labelVars = inResourceData->GetString("labelVars", NULL);
		  if (*labelVars)
		  {
				const char* token = strtok(const_cast<char*>(labelVars), ",");
				int position = 0;

				while (token != nullptr && position < 4) {
					 std::string item(token);

					 if (item == "name")
						  m_eDataVar |= BUTTON_PLAYERVARIABLE_NAME << (position * 4);
					 if (item == "id")
						  m_eDataVar |= BUTTON_PLAYERVARIABLE_CITIZENID << (position * 4);
					 else if (item == "unit")
						  m_eDataVar |= BUTTON_PLAYERVARIABLE_UNIT << (position * 4);
					 else if (item == "city")
						  m_eDataVar |= BUTTON_PLAYERVARIABLE_CITY << (position * 4);
					 else if (item == "credits")
						  m_eDataVar |= BUTTON_PLAYERVARIABLE_CREDITS << (position * 4);
					 else if (item == "rank")
						  m_eDataVar |= BUTTON_PLAYERVARIABLE_RANK << (position * 4);
					 else if (item == "loyalty")
						  m_eDataVar |= BUTTON_PLAYERVARIABLE_LOYALTY << (position * 4);
					 else if (item == "rations")
						  m_eDataVar |= BUTTON_PLAYERVARIABLE_RATIONS << (position * 4);

					 position++;
					 token = strtok(nullptr, ",");
				}
		  }
	 }

	 m_sLabelFormat = inResourceData->GetString("labelFormat", NULL);
	 UpdateData();
}

void CDataButton::UpdateData() {

	if (*m_sLabelFormat && m_eDataType == BUTTON_DATATYPE_PLAYER && m_eDataVar != BUTTON_PLAYERVARIABLE_NONE) {

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

const char* CDataButton::GetPlayerVariable(uint position){
	 // Use a bitmask (0xF) to extract the rightmost 4 bits after shifting
	 ButtonPlayerVariable_t extract_Variable = static_cast<ButtonPlayerVariable_t>((m_eDataVar >> (position * 4)) & 0xF);
	 C_BasePlayer *pPlayer = C_BasePlayer::GetLocalPlayer();

	 char* text = new char[256];

	 if (pPlayer) {
		  switch (extract_Variable) {
		  case BUTTON_PLAYERVARIABLE_NAME:
				return pPlayer->GetPlayerName();
				break;
		  case BUTTON_PLAYERVARIABLE_CITIZENID:
				return pPlayer->GetCitizenId();
				break;
		  case BUTTON_PLAYERVARIABLE_MEMREPLACEMENTS:
				V_snprintf(text, 256, "%d", pPlayer->m_iMemRepl);
				break;
		  case BUTTON_PLAYERVARIABLE_MEMORY:
				V_snprintf(text, 256, "%d", pPlayer->m_iMemory);
				break;
		  case BUTTON_PLAYERVARIABLE_JOB:
				return C_BaseEntity::GetJob(pPlayer->m_Job);
				break;
		  case BUTTON_PLAYERVARIABLE_SQUAD:
				V_snprintf(text, 256, "%d", pPlayer->m_iSquad);
				break;
		  case BUTTON_PLAYERVARIABLE_CITY:
				V_snprintf(text, 256, "%d", pPlayer->m_iCity);
				break;
		  case BUTTON_PLAYERVARIABLE_CREDITS:
				V_snprintf(text, 256, "%d", pPlayer->m_iCredits);
				break;
		  case BUTTON_PLAYERVARIABLE_RANK:
				V_snprintf(text, 256, "%d", pPlayer->m_iRank);
				break;
		  case BUTTON_PLAYERVARIABLE_RATIONS:
				V_snprintf(text, 256, "%d", pPlayer->m_iRation);
				break;
		  case BUTTON_PLAYERVARIABLE_RESIN:
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


