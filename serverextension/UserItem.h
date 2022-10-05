#pragma once


struct st_itemSpecial
{
	short sSpecial;
	short sSpOpt1;
	short sSpOpt2;
	short sSpOpt3;
};


struct st_UserItem
{ // 68 bytes in size 

#pragma pack(push, 1) // tell the compiler to not use padding in the struct
						// so it doesn't mess with the offsets

	void* destructorPtr; // 0

	short sNum; // 0x4
	BYTE bType; // 0x6
	BYTE bArm;  // 0x7
	short sPicNum; // 0x8

	/*int unk2; // 0xA
	int unk3; // 0xE
	int unk4; // 0x12
	int unk5; // 0x16*/

	char stCustomItemName[16]; // 0xA


	short sUsage; // 0x1A
	short sAb1; // 0x1C
	short sAb2; // 0x1E

	short sAt; // 0x20
	short sDf; // 0x22
	short sMP; // 0x24
	short sDur; // 0x26
	short sDex; // 0x28 


	short sWgt; // 0x2A

	short sSpecial; // 0x2C
	short sSpOpt1; // 0x2E
	short sSpOpt2; // 0x30
	short sSpOpt3; // 0x32

	short unk6; // 0x34 
	short unk7; // 0x36 
	short unk8; // 0x38

	short sTime; // 0x3A

	int unk9; // 0x3C
	int unk10; // 0x40 BYTE unk10? UserItem constructor sets 0x40 as a byte, but struct needs to be 68 bytes long, so it's an int here.

	// NEW STUFF

	st_itemSpecial Specials[6];

	char strTest[32]; // total size 148 bytes

#pragma pack(pop)
};


st_UserItem* UserItem_UserItem(void* userItemPtr);