//=============================================================================//
//
// Purpose: This is a panel which is rendered image on top of an entity
//
// $Revision: $
// $NoKeywords: $
//=============================================================================//

#ifndef VGUI_DATABUTTON_H
#define VGUI_DATABUTTON_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Button.h>

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
class KeyValues;

//-----------------------------------------------------------------------------
// A button that renders images instead of standard vgui stuff...
//-----------------------------------------------------------------------------
class CDataButton : public vgui::Button
{
	 typedef vgui::Button BaseClass;

public:
	 enum ButtonDataType_t
	 {
		  BUTTON_DATATYPE_NONE,
		  BUTTON_DATATYPE_PLAYER,

		  BUTTON_DATATYPE_COUNT
	 };

	 enum ButtonPlayerVariable_t
	 {
		  BUTTON_PLAYERVARIABLE_NONE		 = 0x0,

		  // Identification
		  BUTTON_PLAYERVARIABLE_NAME			  = 0x1,
		  BUTTON_PLAYERVARIABLE_CITIZENID	  = 0x2,

		  // Characteristics
		  BUTTON_PLAYERVARIABLE_MEMREPLACEMENTS  = 0x3,
		  BUTTON_PLAYERVARIABLE_MEMORY			  = 0x4,

		  // Type
		  BUTTON_PLAYERVARIABLE_CLASS		 = 0x5,
		  BUTTON_PLAYERVARIABLE_FACTION	 = 0x6,
		  BUTTON_PLAYERVARIABLE_JOB		 = 0x7,
		  BUTTON_PLAYERVARIABLE_SQUAD		 = 0x8,
		  BUTTON_PLAYERVARIABLE_UNIT		 = 0x9,

		  // Location
		  BUTTON_PLAYERVARIABLE_CITY		 = 0xa,

		  // Points
		  BUTTON_PLAYERVARIABLE_CREDITS	 = 0xb,
		  BUTTON_PLAYERVARIABLE_RANK		 = 0xc,
		  BUTTON_PLAYERVARIABLE_LOYALTY	 = 0xd,

		  // Inventory
		  BUTTON_PLAYERVARIABLE_RATIONS	  = 0xe,
		  BUTTON_PLAYERVARIABLE_RESIN		  = 0xf,

		  BUTTON_PLAYERVARIABLE_COUNT	 = 0x10
	 };

// pPlayer->m_iRation, pPlayer->m_iRank, pPlayer->m_iCredits, pPlayer->m_iMemRepl, pPlayer->m_iMemory);
	 // constructor
	 CDataButton(vgui::Panel *pParent, const char *pName, const char *pText);
	 ~CDataButton();

	 // initialization
	 bool Init(KeyValues* pInitData);

	 // initialization from build-mode dialog style .res files
	 virtual void ApplySettings(KeyValues* inResourceData);
	 void UpdateData();

protected:
	ButtonDataType_t m_eDataType = BUTTON_DATATYPE_NONE;
	uint m_eDataVar = 0x0;
	const char* m_sLabelFormat;

	const char* GetPlayerVariable(uint pos);
};

#endif
