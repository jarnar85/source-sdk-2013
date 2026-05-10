//=============================================================================//
//
// Purpose: This is a panel which is rendered image on top of an entity
//
// $Revision: $
// $NoKeywords: $
//=============================================================================//

#ifndef VGUI_DATALABEL_H
#define VGUI_DATALABEL_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Label.h>

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
class KeyValues;

//-----------------------------------------------------------------------------
// A button that renders images instead of standard vgui stuff...
//-----------------------------------------------------------------------------
class CDataLabel : public vgui::Label
{
	 typedef vgui::Label BaseClass;

public:
	 enum LabelDataType_t
	 {
		  LABEL_DATATYPE_NONE,
		  LABEL_DATATYPE_PLAYER,

		  LABEL_DATATYPE_COUNT
	 };

	 enum LabelPlayerVariable_t
	 {
		  LABEL_PLAYERVARIABLE_NONE		 = 0x0,

		  // Identification
		  LABEL_PLAYERVARIABLE_NAME			  = 0x1,
		  LABEL_PLAYERVARIABLE_CITIZENID	  = 0x2,

		  // Characteristics
		  LABEL_PLAYERVARIABLE_MEMREPLACEMENTS  = 0x3,
		  LABEL_PLAYERVARIABLE_MEMORY			  = 0x4,

		  // Type
		  LABEL_PLAYERVARIABLE_CLASS		 = 0x5,
		  LABEL_PLAYERVARIABLE_FACTION	 = 0x6,
		  LABEL_PLAYERVARIABLE_JOB		 = 0x7,
		  LABEL_PLAYERVARIABLE_SQUAD		 = 0x8,
		  LABEL_PLAYERVARIABLE_UNIT		 = 0x9,

		  // Location
		  LABEL_PLAYERVARIABLE_CITY		 = 0xa,

		  // Points
		  LABEL_PLAYERVARIABLE_CREDITS	 = 0xb,
		  LABEL_PLAYERVARIABLE_RANK		 = 0xc,
		  LABEL_PLAYERVARIABLE_LOYALTY	 = 0xd,

		  // Inventory
		  LABEL_PLAYERVARIABLE_RATIONS	  = 0xe,
		  LABEL_PLAYERVARIABLE_RESIN		  = 0xf,

		  LABEL_PLAYERVARIABLE_COUNT	 = 0x10
	 };
	 
	 // constructor
	 CDataLabel(vgui::Panel *pParent, const char *pName, const char *pText);
	 ~CDataLabel();

	 // initialization
	 bool Init(KeyValues* pInitData);

	 // initialization from build-mode dialog style .res files
	 virtual void ApplySettings(KeyValues* inResourceData);
	 void UpdateData();

protected:
	 LabelDataType_t m_eDataType = LABEL_DATATYPE_NONE;
	 uint m_eDataVar = 0x0;
	 const char* m_sLabelFormat;

	 const char* GetPlayerVariable(uint pos);
};

#endif
