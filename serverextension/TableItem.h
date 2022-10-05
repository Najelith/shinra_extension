#pragma once

#include <Windows.h>

struct st_CTableItem
{
	int unk; // 0x0
	
	int bArm; // 0x4	
	int bGender; // 0x8	
	int bType; // 0xC
	
	int iCost; // 0x10
	
	int sAb1; // 0x14
	int sAb2; // 0x18
	int sAt; // 0x1C
	int sDur; // 0x20
	int sDf; // 0x24
	
	int unk2; // 0x28
	
	int sHP; // 0x2C
	int sDex; // 0x30
	int sMagicNo; // 0x34
	
	int unk3; // 0x38
	
	int sNeedSkill; // 0x3C
	int sMP; // 0x40
	int sNeedInt; // 0x44
	int sNeedStr; // 0x48
	int sNeedDex; // 0x4C
	
	int unk4; // 0x50
	
	int sPicNum; // 0x54
	
	int unk5; // 0x58
	int unk6; // 0x5C
	
	int sSpecial; // 0x60
	int sSpOpt1; // 0x64
	int sSpOpt2; // 0x68
	int sSpOpt3; // 0x6C
	
	int sMagicOpt; // 0x70
	int sTime; // 0x74
	
	char strName[52]; // 0x78 52 bytes? (0xB0 - 31 * sizeof(int))
	
	int sWgt; // 0xAC
};

/*
class TableItem
{
public:
	TableItem();
	virtual ~TableItem();

public:
	BOOL GetData(TCHAR* pBuf, int& index);
	int	m_Num;
	int	m_Arm;
	int	m_UseLevel;
	int	m_UseType;
	int	m_PicNum;
	int	m_Wg;
	int	m_Dur;
	int	m_MaxAt;
	int	m_AtDelay;
	int	m_DmgX;
	int	m_DmgY;
	int	m_DmgZ;
	int	m_Df;
	int	m_At;
	int	m_Crit;
	int	m_Range;
	int	m_Out;
	int	m_BullNum;
	int	m_BullType;
	int	m_StErr;
	int	m_StDf;
	int	m_StCure;
	int	m_HP;
	int	m_PP;
	int	m_SP;

	DWORD			m_Cost;	
	char			m_Name[ITEM_NAME_LENGTH];
};*/