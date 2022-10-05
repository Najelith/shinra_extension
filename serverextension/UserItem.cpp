#include "stdafx.h"

#include "UserItem.h"

st_UserItem* UserItem_UserItem(void* userItemPtr)
{
	st_UserItem* uItem = (st_UserItem*)userItemPtr;

	uItem->destructorPtr = (void*)0x4B89E8;
	uItem->sNum = 0;
	uItem->bType = 0;
	uItem->bArm = 0;
	uItem->sPicNum = 0;

	memset(uItem->stCustomItemName, 0, 16);

	uItem->sUsage = 0;
	uItem->sAb1 = 0;
	uItem->sAb2 = 0;
	uItem->sAt = 0;
	uItem->sDf = 0;
	uItem->sMP = 0;
	uItem->sDur = 0;
	uItem->sDex = 0;
	uItem->sWgt = 0;
	uItem->sSpecial = 0;
	uItem->sSpOpt1 = 0;
	uItem->sSpOpt2 = 0;
	uItem->sSpOpt3 = 0;
	uItem->unk6 = 0;
	uItem->unk7 = 0;
	uItem->unk8 = 0;
	uItem->sTime = 0;
	uItem->unk9 = 0;
	uItem->unk10 = (BYTE)0;

	// NEW STUFF

	for (int i = 0; i < 6; i++)
	{
		uItem->Specials[i].sSpecial = 0;
		uItem->Specials[i].sSpOpt1 = 0;
		uItem->Specials[i].sSpOpt2 = 0;
		uItem->Specials[i].sSpOpt3 = 0;
	}

	memset(uItem->strTest, 0, 32);

	return uItem;
}