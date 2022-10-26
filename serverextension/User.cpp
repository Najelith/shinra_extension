#include <windows.h>

#include "StdAfx.h"
#include "User.h"
#include <map>
#include "pktHelpers.h"
#include <osrng.h>
//sqlstuff

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include <comdef.h>
#include <vector>
#include "./include/gsodbc.h"


#include "Hook.h"
#include "Item.h"
#include "MyDatabase.h"


//defenitions
std::map<void*, User*>* User::userMap; //DO NOT REMOVE! THE LINKER WILL COME FOR YOUR FIRSTBORN IF YOU DO!
#define PRINTLINE(buff,size) \
	for(int ___i = 0; ___i < size; ___i++){ \
		printf("%02X",buff[___i]); \
	} \
	printf("\n"); 

#ifdef RAUBAN_DEBUG
/*void printLine(BYTE* buff, int size){
	for(int i = 0; i < size; i++){
		printf("%02X",buff[i]);
	}
	printf("\n");
}*/
#endif
User::User(BYTE* realUserPointer)
{
	this->realUser = realUserPointer;
	this->plastnpc = 0;
	this->key = 0;
	this->keySize = 0;
	this->stepCounter = 0;
	this->gtw = 0; 
	this->srtime = 0;
	this->dbindex= 0;
	this->spdhk= 0;

	memset(this->iASpecialAttackDelay, 0, 30 * sizeof(int));
}



User::~User(void)
{

}

User* User::getExtentionUserFromRealUser(void* realUser)
{
	if(userMap == NULL)
	{
		userMap = new std::map<void*, User*>();
	}

	std::map<void*, User*>::iterator itt = userMap->find(realUser);
	User* returnUser = NULL;

	if(itt == userMap->end())
	{ //ExtentionUser does not exist, let's create!
		returnUser = new User(reinterpret_cast<BYTE*>(realUser));
		userMap->insert(std::pair<void*, User*>(realUser,returnUser));
	}
	else
	{
		returnUser = reinterpret_cast<User*>(itt->second);
	}

	return returnUser;
}

void User::parseVersionResult(BYTE* buffer)
{
#ifndef _DEBUG

	DWORD realUser; // esi@1
	DWORD clientVersion; // ebp@1
	DWORD offset; // [sp+10h] [bp-4h]@1
	BYTE unknown; // [sp+18h] [bp+4h]@1

	realUser = reinterpret_cast<DWORD>(this->realUser);
	offset = 0;
	clientVersion = GetDWORD(buffer, &offset);
	unknown = GetByte(buffer, &offset);
	printf("checking version\n");
	if ( clientVersion == 0x4B1 )
	{
		printf("version ok\n");
		if ( *reinterpret_cast<DWORD*>(0x509E64) && unknown != *reinterpret_cast<DWORD*>(0x509E64) )
		{
			offset = 0;
			SetByte(reinterpret_cast<BYTE*>(realUser + 18616), 0xFDu, &offset);
			SetByte(reinterpret_cast<BYTE*>(realUser + 18616), 2u, &offset);
			this->Send(offset, reinterpret_cast<BYTE*>(realUser + 18616), 1);
			*reinterpret_cast<DWORD*>(realUser + 8212) = 0;
		}
		else
		{
			offset = 0;
			BYTE* outBuffer = reinterpret_cast<BYTE*>(realUser + 18616);
			SetByte(outBuffer, 0xFDu, &offset);
			SetByte(outBuffer, 1u, &offset);
			BYTE keySize = 16;

			BYTE* key = new BYTE[keySize];

			// Construction
			CryptoPP::AutoSeededRandomPool rng;

			// Random Block
			rng.GenerateBlock( key, keySize );

			this->setEncryptionKey(key,keySize);
			
			SetByte(outBuffer, keySize, &offset);
			//set key
			for(int i= 0; i < keySize; i++){
				SetByte(outBuffer,key[i],&offset);
			}
			/*
			SetDWord(outBuffer, *reinterpret_cast<DWORD*>(0x5092C0),&offset);
			SetDWord(outBuffer, *reinterpret_cast<DWORD*>(0x5092C4),&offset);
			SetDWord(outBuffer, *reinterpret_cast<DWORD*>(realUser + 28864),&offset);
			SetDWord(outBuffer, *reinterpret_cast<DWORD*>(realUser + 28868),&offset);*/

			this->Send(offset, reinterpret_cast<BYTE*>(realUser + 18616), 1);
			*reinterpret_cast<DWORD*>(realUser + 8216) = 0;
			*reinterpret_cast<DWORD*>(realUser + 8212) = 1;
		}
	}
	else
	{
		offset = 0;
		SetByte(reinterpret_cast<BYTE*>(realUser + 18616), 0xFDu, &offset);
		SetByte(reinterpret_cast<BYTE*>(realUser + 18616), 2u, &offset);
		this->Send(offset, reinterpret_cast<BYTE*>(realUser + 18616), 1);
		*reinterpret_cast<DWORD*>(realUser + 8212) = 0;
	}

#endif

}

void User::Send(DWORD size, BYTE* pktToSend,BOOL sendRaw){
		void (__thiscall *Send)(DWORD realUserPointer, DWORD size, BYTE* pktToSend, BOOL sendRaw) = ((void (__thiscall *)(DWORD, DWORD, BYTE*, BOOL))0x42BED0);
		Send(reinterpret_cast<DWORD>(this->realUser), size,pktToSend,sendRaw);
}

void User::ENCODE_DECODE(int size, BYTE *src, BYTE *dst)
{
#ifndef _DEBUG
	if(size <= 0){
		return;
	}
	CryptoPP::Salsa20::Encryption enc(this->key,this->keySize,this->key);
	enc.ProcessString(dst,src,size);
#ifdef RAUBAN_DEBUG
		printf("encrypt/decrypt using key:\n");
		PRINTLINE(this->key,16);
		printf("src:\n");
		PRINTLINE(src,size);
		printf("dst:\n");
		PRINTLINE(dst,size);
		printf("size: %d\n",size);
#endif

#endif
}
void User::setEncryptionKey(BYTE* key, int size){
	if(this->key != NULL){
		delete this->key;
	}
	this->key = key;
	this->keySize = size;
}

void User::TakeBackItem(BYTE* bypData)
{
    void(__thiscall * _TakeBackItem)(DWORD realUser, BYTE* bypData) = ((void(__thiscall*)(DWORD, BYTE*))0x45e280);

    _TakeBackItem(reinterpret_cast<DWORD>(this->realUser), bypData);
}

void User::parseTakeBackItem(BYTE* buffer)
{
	//void (__thiscall *parseVersionResult)(DWORD realUserPointer, BYTE* buffer) = ((void (__thiscall *)(DWORD, BYTE*))0x45e280);

	if(isWithinRange(&lastWH))
    {
       // parseVersionResult(reinterpret_cast<DWORD>(this->realUser), buffer);

        TakeBackItem(buffer);
        return;
	}

	logcheat(6); //log instead of kick
	//KickOut(0);
	
	/*
	BYTE* realUserPointer; // ebp@1
  int isTrading; // eax@1
  signed int amount; // eax@3
  signed int index; // edi@3
  int amount2; // esi@3
  int itemPointer2; // ebx@7
  int itemPointer3; // eax@13
  int stashItems; // edx@13
  int v10; // ebx@13
  int v11; // eax@23
  int v12; // ecx@23
  int v13; // ecx@23
  int v14; // eax@24
  int v15; // eax@24
  int v16; // ecx@24
  int v17; // edx@28
  int v18; // eax@30
  int v19; // edx@30
  int v20; // edi@30
  int v21; // eax@31
  int v22; // esi@31
  int v23; // ST44_4@31
  int itemPointer4; // ebx@41
  int v25; // eax@42
  int v26; // edi@45
  __int16 v27; // ax@48
  char v28; // kr00_1@48
  int v29; // edi@50
  char v30; // zf@51
  time_t v31; // ST3C_8@52
  __int16 v32; // [sp-8h] [bp-84h]@46
  int v33; // [sp-4h] [bp-80h]@18
  int *v34; // [sp-4h] [bp-80h]@46
  DWORD offset; // [sp+10h] [bp-6Ch]@1
  int itemPointer; // [sp+14h] [bp-68h]@7
  char v37; // [sp+18h] [bp-64h]@18
  int pushedSucccessful; // [sp+80h] [bp+4h]@20
  __int16 *v39; // [sp+80h] [bp+4h]@50

  realUserPointer = this->realUser;
  isTrading = *reinterpret_cast<DWORD*>(realUserPointer + 0x745C);
  offset = 0;
  if ( isTrading )
  {
    offset = 0;
failure:
    SetByte((BYTE *)(realUserPointer + 18616), 0x78u, &offset);
    SetShort(realUserPointer + 18616, -1, &offset);
	this->Send( offset, (byte *)(realUserPointer + 18616), 1);
    return;
  }
  index = GetShort(buffer, &offset);
  amount = GetShort(buffer, &offset);
  amount2 = amount;
  if ( amount < 1 || amount > 29999 || index < 0 || index >= 80 )
  {
    offset = 0;
    goto failure2;
  }
  itemPointer = *reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(realUserPointer + 0x70E0) + 4 * index);
  itemPointer2 = itemPointer;
  if ( !itemPointer )
  {
failure3:
    offset = 0;
    goto failure;
  }
  this->sendChangeWgt();
  if ( *reinterpret_cast<BYTE*>(*reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(realUserPointer + 0x70E0) + 4 * index) + 18) <= 8u )// if stackable item
  {
    if ( *reinterpret_cast<DWORD*>(realUserPointer + 0x7218) + (signed int)*reinterpret_cast<WORD*>(itemPointer2 + 54) > getMaxWgt() )
    {
		this->sendChatMessage("<<< Failed to take out the item : you're exceding your bagweight limit. >>>");
      offset = 0;
failure2:
      SetByte((BYTE *)(realUserPointer + 18616), 0x78u, (int)&offset);
      SetShort(realUserPointer + 18616, -1, &offset);
      Send(offset, (byte *)(realUserPointer + 18616), 1);
      return;
    }
  }
  else
  {
    if ( *reinterpret_cast<DWORD*>(realUserPointer + 29208) + amount2 * *reinterpret_cast<WORD*>(itemPointer2 + 54) > getMaxWgt() )
    {
      sendChatMessage("<<< Failed to take out the item : you're exceding your bagweight limit. >>>");
      goto failure3;
    }
  }
  stashItems = *reinterpret_cast<DWORD*>(realUserPointer + 0x70E0);
  v10 = 0;
  itemPointer3 = *reinterpret_cast<DWORD*>(stashItems + 4 * index);
  if ( *reinterpret_cast<BYTE*>(itemPointer3 + 18) <= 8u )
  {
    v33 = *reinterpret_cast<DWORD*>(stashItems + 4 * index);
  }
  else
  {
    if (*reinterpret_cast<WORD*>(itemPointer3 + 52) < amount2 )
    {
      offset = 0;
      goto failure2;
    }
    v10 = Item_NewItem(realUserPointer);
    if ( !Item_CopyTableItem(*(_WORD *)(*(_DWORD *)(*(_DWORD *)(realUserPointer + 28896) + 4 * index) + 16)) )
    {
      offset = 0;
      SetByte((BYTE *)(realUserPointer + 18616), 0x78u, (int)&offset);
      SetShort(realUserPointer + 18616, -1, &offset);
      Send(offset, (byte *)(realUserPointer + 18616), 1);
      Item_DeleteItem(realUserPointer, v10);
      return;
    }
    Item_FillItemData(&v37);
    sub_409780(&v37, -1, 0, 0);
    *(_WORD *)(v10 + 52) = amount2;
    v33 = v10;
  }
  pushedSucccessful = User_PushItemInventory(v33);
  if ( pushedSucccessful == -1 )
  {
    sendChatMessage("<<< You have no more space in your inventory >>>");
    offset = 0;
    SetByte((BYTE *)(realUserPointer + 18616), 0x78u, (int)&offset);
    SetShort(realUserPointer + 18616, -1, &offset);
    Send( offset, (byte *)(realUserPointer + 18616), 1);
    if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(realUserPointer + 28896) + 4 * index) + 18) > 8u )
      Item_DeleteItem(realUserPointer, v10);
  }
  else
  {
    v13 = *(_DWORD *)(realUserPointer + 28896);
    v11 = *(_DWORD *)(v13 + 4 * index);
    v12 = v13 + 4 * index;
    if ( *(_BYTE *)(v11 + 18) <= 8u )
    {
      *(_DWORD *)v12 = 0;
    }
    else
    {
      Item_PlusItemDur((void *)realUserPointer, v11, -amount2);
      v15 = *(_DWORD *)(realUserPointer + 28896);
      v16 = *(_DWORD *)(v15 + 4 * index);
      v14 = v15 + 4 * index;
      if ( *(_WORD *)(v16 + 52) < 1 )
        *(_DWORD *)v14 = 0;
    }
    if ( !User_UpdateStorageIndex(index) )
    {
      v17 = *(_DWORD *)(realUserPointer + 28896);
      if ( !*(_DWORD *)(v17 + 4 * index) )
        *(_DWORD *)(v17 + 4 * index) = itemPointer;
      v19 = *(_DWORD *)(realUserPointer + 28896);
      v18 = *(_DWORD *)(v19 + 4 * index);
      v20 = v19 + 4 * index;
      if ( *(_BYTE *)(v18 + 18) <= 8u )
      {
        v22 = pushedSucccessful;
        *(_DWORD *)v20 = *(_DWORD *)(*(_DWORD *)(realUserPointer + 28876) + 4 * pushedSucccessful);
        *(_DWORD *)(*(_DWORD *)(realUserPointer + 28876) + 4 * pushedSucccessful) = 0;
      }
      else
      {
        Item_PlusItemDur((void *)realUserPointer, v18, amount2);
        v23 = -amount2;
        v22 = pushedSucccessful;
        Item_PlusItemDur(
          (void *)realUserPointer,
          *(_DWORD *)(*(_DWORD *)(realUserPointer + 28876) + 4 * pushedSucccessful),
          v23);
        v21 = *(_DWORD *)(realUserPointer + 28876) + 4 * pushedSucccessful;
        if ( *(_WORD *)(*(_DWORD *)v21 + 52) < 1 )
        {
          if ( !v10 )
          {
            *(_DWORD *)v21 = 0;
            Item_DeleteItem(realUserPointer, 0);
          }
        }
      }
      User_UpdateItemIndex(v22);
      goto failure3;
    }
    if ( *(_BYTE *)(itemPointer + 18) > 8u )
    {
      if ( *(_WORD *)(itemPointer + 52) < 1 )
        Item_DeleteItem(realUserPointer, itemPointer);
    }
    itemPointer4 = *(_DWORD *)(*(_DWORD *)(realUserPointer + 28876) + 4 * pushedSucccessful);
    if ( itemPointer4 )
    {
      v25 = *(_WORD *)(itemPointer4 + 16);
      itemPointer = *(_WORD *)(itemPointer4 + 16);
      if ( v25 >= 0 )
      {
        if ( v25 < dword_509DA0 )
        {
          if ( *(_DWORD *)(dword_509D9C + 4 * v25) )
          {
            offset = 0;
            SetByte((BYTE *)(realUserPointer + 18616), 0x78u, (int)&offset);
            SetShort(realUserPointer + 18616, index, &offset);
            v26 = *(_DWORD *)(*(_DWORD *)(realUserPointer + 28896) + 4 * index);
            if ( v26 )
            {
              v34 = (int *)&offset;
              v32 = *(_WORD *)(v26 + 52);
            }
            else
            {
              v34 = (int *)&offset;
              v32 = 0;
            }
            SetShort(realUserPointer + 18616, v32, v34);
            SetShort(realUserPointer + 18616, pushedSucccessful, &offset);
            SetByte((BYTE *)(realUserPointer + 18616), *(_BYTE *)(itemPointer4 + 18), (int)&offset);
            SetByte((BYTE *)(realUserPointer + 18616), *(_BYTE *)(itemPointer4 + 19), (int)&offset);
            v27 = User_GetItemClass(*(_WORD *)(itemPointer4 + 16));
            SetShort(realUserPointer + 18616, v27, &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 22), &offset);
            SetByte((BYTE *)(realUserPointer + 18616), *(_BYTE *)(itemPointer4 + 20), (int)&offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 24), &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 26), &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 54), &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 56), &offset);
            SetInt(realUserPointer + 18616, *(_DWORD *)(itemPointer4 + 104), &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 28), &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 30), &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 32), &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 34), &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 48), &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 50), &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 52), &offset);
            SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 92), &offset);
            SetShort(realUserPointer + 18616, *(_DWORD *)(*(_DWORD *)(dword_509D9C + 4 * itemPointer) + 40), &offset);
            v28 = strlen((const char *)(itemPointer4 + 108));
            SetByte((BYTE *)(realUserPointer + 18616), v28 - 1, (int)&offset);
            SetString(realUserPointer + 18616, itemPointer4 + 108, (unsigned __int8)(v28 - 1), &offset);
            SetByte((BYTE *)(realUserPointer + 18616), *(_BYTE *)(itemPointer4 + 94), (int)&offset);
            if ( Item_CheckPlusSpecial(itemPointer4) )
            {
              v29 = itemPointer4 + 74;
              v39 = (__int16 *)(itemPointer4 + 66);
              itemPointer = 3;
              do
              {
                SetShort(realUserPointer + 18616, *v39, &offset);
                SetShort(realUserPointer + 18616, *(_WORD *)(v29 - 2), &offset);
                SetShort(realUserPointer + 18616, *(_WORD *)v29, &offset);
                SetShort(realUserPointer + 18616, *(_WORD *)(v29 + 2), &offset);
                v29 += 6;
                v30 = itemPointer == 1;
                ++v39;
                --itemPointer;
              }
              while ( !v30 );
            }
            else
            {
              SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 58), &offset);
              SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 60), &offset);
              SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 62), &offset);
              SetShort(realUserPointer + 18616, *(_WORD *)(itemPointer4 + 64), &offset);
              SetShort(realUserPointer + 18616, 0, &offset);
              SetShort(realUserPointer + 18616, 0, &offset);
              SetShort(realUserPointer + 18616, 0, &offset);
              SetShort(realUserPointer + 18616, 0, &offset);
              SetShort(realUserPointer + 18616, 0, &offset);
              SetShort(realUserPointer + 18616, 0, &offset);
              SetShort(realUserPointer + 18616, 0, &offset);
              SetShort(realUserPointer + 18616, 0, &offset);
            }
            User_Send(realUserPointer, offset, (byte *)(realUserPointer + 18616), 1);
            User_SendChangeWgt(realUserPointer);
            HIDWORD(v31) = 25;
            LODWORD(v31) = itemPointer4;
            Item_User_WriteItemLog(v31, 0);
          }
        }
      }
    }
  }*/

}

void User::parseSaveItem(BYTE* buffer){
	void (__thiscall *parseSaveItem)(DWORD realUserPointer,BYTE* buffer) = ((void (__thiscall *)(DWORD,BYTE*))0x45d930);
	if(isWithinRange(&lastWH)){
		return parseSaveItem(reinterpret_cast<DWORD>(this->realUser),buffer);
	}
	logcheat(7); //log instead of kick
	//KickOut(0);
}
void User::parseSaveMoney(BYTE* buffer){
	void (__thiscall *parseSaveMoney)(DWORD realUserPointer,BYTE* buffer) = ((void (__thiscall *)(DWORD,BYTE*))0x45e9e0);
	if(isWithinRange(&lastWH)){
		return parseSaveMoney(reinterpret_cast<DWORD>(this->realUser),buffer);
	}
	logcheat(8); //log instead of kick
	//KickOut(0);
}
void User::parseTakeBackMoney(BYTE* buffer){
	void (__thiscall *parseTakeBackMoney)(DWORD realUserPointer,BYTE* buffer) = ((void (__thiscall *)(DWORD,BYTE*))0x45eaa0);
	if(isWithinRange(&lastWH)){
		return parseTakeBackMoney(reinterpret_cast<DWORD>(this->realUser),buffer);
	}
	logcheat(9); //log instead of kick
	//KickOut(0);
}
void User::sendChangeWgt(){
	void (__thiscall *sendChangeWgt)(DWORD realUserPointer) = ((void (__thiscall *)(DWORD))0x452150);
	sendChangeWgt(reinterpret_cast<DWORD>(this->realUser));
}
int User::checkRemainMagic(int unknown){
	int (__thiscall *checkRemainMagic)(DWORD realUserPointer,int unknown) = ((int (__thiscall *)(DWORD,int))0x46a1e0);
	return checkRemainMagic(reinterpret_cast<DWORD>(this->realUser),unknown);
}
int User::checkRemainSpecialAttack(int unknown){
	int (__thiscall *checkRemainSpecialAttack)(DWORD realUserPointer,int unknown) = ((int (__thiscall *)(DWORD,int))0x4815a0);
	return checkRemainSpecialAttack(reinterpret_cast<DWORD>(this->realUser),unknown);
}
bool User::checkDistByPoint(int x, int y, int distance){
	bool (__thiscall *checkDistByPoint)(DWORD realUserPointer,int x,int y, int distance) = ((bool (__thiscall *)(DWORD,int,int,int))0x4603A0);
	return checkDistByPoint(reinterpret_cast<DWORD>(this->realUser),x,y,distance);
}
int User::move(int x, int y, int gw1, int gw2){
//	int (__thiscall *move)(DWORD realUserPointer,int x,int y) = ((int (__thiscall *)(DWORD,int,int))0x432E50);
//	return move(reinterpret_cast<DWORD>(this->realUser),x,y);
	 DWORD uP; // esi@1
  int v4; // ebx@4
  int *v5; // edi@4
  int v6; // eax@4
  signed int v7; // eax@6
  char v8; // zf@9
  signed int result; // eax@13
  SOMA_LOC serverX; // [sp+4h] [bp-8h]@1
  int serverY; // [sp+8h] [bp-4h]@2
  DWORD mapPointer;

  uP = reinterpret_cast<DWORD>(this->realUser);
 ConvertToServer(reinterpret_cast<POINT*>(&serverX), x, y, -1);

 if ( serverX.x != -1 && serverX.y != -1  && IsMovable_S( serverX.x, serverX.y) )
  {

	  		mapPointer = *(DWORD *)(*(DWORD *)(0x509E34) + 4 * getZoneIndex());
	

    *(DWORD *)(*(DWORD *)(*(DWORD *)(mapPointer + 20) + 4 * getX()) + 12 * getY() + 4) = -1;

	*(DWORD *)(*(DWORD *)(*(DWORD *)(mapPointer + 20) + 4 * (DWORD)serverX.x) + 12 * (DWORD)serverX.y + 4) = getUserServerID();
    
	CheckRangeAbility();
	v6 = serverX.y;
	*(DWORD *)(uP + 0x7260) = serverX.x;
    *(DWORD *)(uP + 0x7264) = v6;
    CheckRangeAbility();
    v4 = 1;
    v5 = (int*)0x509E6C;

	//	 printf("%s->move gw1:%d gw2:%d \n",this->getName(), gw1,gw2);
	/*	 if (!this->gtw){ // check for custom war been set or not
    while ( !isMapRange( *v5) )
	{
      v7 = -1;
      ++v5;
      ++v4;

      if ( (signed int)v5 >= (signed int)0x509E74 )
        goto LABEL_11;
    }
    if ( CheckGuildTown( v4) || (v8 = CheckGuildTownAlly(v4) == 0, v7 = 2, !v8) )
      v7 = 1;
LABEL_11:
    if ( v7 != *(DWORD *)(uP + 0x7B4C) )
    {
      *(DWORD *)(uP + 0x7B4C) = v7;
     SendMyInfo( 4, 1u);
    }

 }*/ // my if
		 if(!this->gtw){	
			 v7 = -1;
	//	 if(gw1 > 0 || gw2 > 0){ // custom war
			 if(gw1 > 0){
				 if(isMapRange(112)){
				 v7 = 2;//set war to 2
				 
				 }
			 }

			 if(gw2 > 0){
				 if(isMapRange(113)){
				 v7 = 2;//set war to 2
				 }
			 }

			 if(isMapRange(106)){ // gw human
				 if ( CheckGuildTown(1) || CheckGuildTownAlly(1)){
				 v7 = 1;
				 }
				 else { v7= 2;}
			 }

			 	 if(isMapRange(108)){ // gw devil
				 if ( CheckGuildTown(2) || CheckGuildTownAlly(2)){
				 v7 = 1;
				 }
				 else { v7= 2;}
			 }
				 if( v7 !=*(DWORD *)(uP + 0x7B4C)){
					 warguild(v7);
				 }

		// }// end of custom war thing
	}

    result = 1;
 }
  else
  {
    result = 0;
  }
return result;

} 


DWORD User::CheckDemon(DWORD a1) 
{
    DWORD(__thiscall * CheckDemon)(DWORD realUser, DWORD a1) = ((DWORD(__thiscall*)(DWORD, DWORD))0x456e60);
    return CheckDemon(reinterpret_cast<DWORD>(this->realUser), a1);
}


DWORD User::CheckMonster(DWORD a1) 
{
    DWORD(__thiscall * CheckMonster)(DWORD realUser, DWORD a1) = ((DWORD(__thiscall*)(DWORD, DWORD))0x456e40);
    return CheckMonster(reinterpret_cast<DWORD>(this->realUser), a1);
}

int User::getStm(){
	int (__thiscall *getStm)(DWORD realUserPointer) = ((int (__thiscall *)(DWORD))0x44e6d0);
	return getStm(reinterpret_cast<DWORD>(this->realUser));
}
bool User::isMapRange(int range){
	bool (__thiscall *isMapRange)(DWORD realUserPointer,int range) = ((bool (__thiscall *)(DWORD,int))0x47b260);
	return isMapRange(reinterpret_cast<DWORD>(this->realUser),range);
}
void User::sendChatMessage(const char* text){
	void (__thiscall *sendChatMessage)(DWORD realUserPointer, const char* text) = ((void (__thiscall *)(DWORD,const char*))0x469f60);
	sendChatMessage(reinterpret_cast<DWORD>(this->realUser),text);
}
// userpointer, guild,string pointer,0

void User::sendguildtxt(const char* text){
	void (__thiscall *sendguildtxt)(DWORD realUserPointer,DWORD, const char* text,DWORD) = ((void (__thiscall *)(DWORD,DWORD,const char*,DWORD))0x473360);
	sendguildtxt(reinterpret_cast<DWORD>(this->realUser),this->getGuildId(),text,0);
}
void User::sendGuildChatMessage(const char* text){
	void (__thiscall *sendGuildChatMessage)(DWORD realUserPointer, const char* text) = ((void (__thiscall *)(DWORD,const char*))0x473340);
	sendGuildChatMessage(reinterpret_cast<DWORD>(this->realUser),text);
}
void User::sendInsight(unsigned int size, const void *buff){
	void (__thiscall *sendInsight)(DWORD realUserPointer, unsigned int size ,const void * buff) = ((void (__thiscall *)(DWORD,unsigned int,const void *))0x42d9d0);
	sendInsight(reinterpret_cast<DWORD>(this->realUser),size,buff);
}
void User::sightRecalc(){
	void (__thiscall *sendInsight)(DWORD realUserPointer) = ((void (__thiscall *)(DWORD))0x474820);
	sendInsight(reinterpret_cast<DWORD>(this->realUser));
}
void User::guildTownWarStart(){
	void (__thiscall *guildTownWarStart)(DWORD realUserPointer) = ((void (__thiscall *)(DWORD))0x48a3a0);
	guildTownWarStart(reinterpret_cast<DWORD>(this->realUser));
}
void User::guildTownWarEnd(){
	void (__thiscall *guildTownWarEnd)(DWORD realUserPointer) = ((void (__thiscall *)(DWORD))0x48a970);
	guildTownWarEnd(reinterpret_cast<DWORD>(this->realUser));
}
void User::classWarStart(){
	void (__thiscall *classWarStart)(DWORD realUserPointer) = ((void (__thiscall *)(DWORD))0x48bbf0);
	classWarStart(reinterpret_cast<DWORD>(this->realUser));
}
void User::classWarEnd(){
	void (__thiscall *classWarEnd)(DWORD realUserPointer) = ((void (__thiscall *)(DWORD))0x48bd10);
	classWarEnd(reinterpret_cast<DWORD>(this->realUser));
}
int User::getMaxStm(){
	int (__thiscall *getMaxStm)(DWORD realUserPointer) = ((int (__thiscall *)(DWORD))0x4834d0);
	return getMaxStm(reinterpret_cast<DWORD>(this->realUser));
}
int User::isMovable_C(int x, int y){
	int (__thiscall *isMovable_C)(DWORD realUserPointer,int x, int y) = ((int (__thiscall *)(DWORD,int,int))0x432c20);
	return isMovable_C(reinterpret_cast<DWORD>(this->realUser),x,y);
}
int User::decStm(){
	int (__thiscall *decStm)(DWORD realUserPointer) = ((int (__thiscall *)(DWORD))0x44e843);
	return decStm(reinterpret_cast<DWORD>(this->realUser));
}

int User::getItemRangeChange(int notUsed){
	int (__thiscall *getItemRangeChange)(DWORD realUserPointer,int notUsed) = ((int (__thiscall *)(DWORD,int))0x483940);
	return getItemRangeChange(reinterpret_cast<DWORD>(this->realUser),notUsed);
}
void User::checkSpeedHack(int useless){
	void (__thiscall *checkSpeedHack)(DWORD realUserPointer,int useless) = ((void (__thiscall *)(DWORD, int))0x459d40);
	checkSpeedHack(reinterpret_cast<DWORD>(this->realUser),useless);
}
int User::getMaxWgt(){
	int (__thiscall *getMaxWgt)(DWORD realUserPointer) = ((int (__thiscall *)(DWORD))0x483490);
	return getMaxWgt(reinterpret_cast<DWORD>(this->realUser));
}
void User::storageOpen(int unknown){
	convertToClient(reinterpret_cast<POINT*>(&lastWH),getX(),getY(),-1);
	lastWH.z = getZone();
	void (__thiscall *storageOpen_)(DWORD realUserPointer,int random) = ((void (__thiscall *)(DWORD,int))0x45d4d0);
	storageOpen_(reinterpret_cast<DWORD>(this->realUser),unknown);
}
POINT* User::convertToClient(POINT* point, DWORD x, DWORD y,int zone)
{
	POINT* (__thiscall *ConvertToClient)(DWORD realUser, POINT* rtn, DWORD x, DWORD y,DWORD zone) = ((POINT* (__thiscall *)(DWORD, POINT*, DWORD, DWORD, DWORD))0x442850);

	return ConvertToClient(reinterpret_cast<DWORD>(this->realUser), point,x,y,zone);
	
}

bool User::isWithinRange(SOMA_LOC* location){
	if(location->z == getZone()){
		POINT current;
		convertToClient(&current,getX(),getY(),-1);
		int dx = location->x - current.x;
		int dy = location->y - current.y;
		if( dx * dx + dy * dy < 6*6){
			return true;
		}	
	}
	return false;
}

void User::logcheat(int type){
  CGOdbcConnect cCon;
    try
    {
        cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);

    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return;
    }

    //printf("Driver: %s\n", cCon.getDriver());

	char szQuery[91];
	
	 sprintf(szQuery,"{call proc_cheatlog ('%s',%d)}",this->getName(), type);
	 
	 //printf("%s Has been caught cheating, type %d",this->getName(), type);
    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
		    //printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        printf("Insert Error\n%s\n", pE->getMsg());
        return;
    }  
           
		   

    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();
}



int User::getsrEvent(){
  CGOdbcConnect cCon;
    try
    {
        cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);

    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return 0;
    }

    //printf("Driver: %s\n", cCon.getDriver());

	char szQuery[91];
	
	 sprintf(szQuery,"{call getsrevent ('%s')}",this->getName());
	 
	// printf("%s Has been caught cheating, type %d",this->getName());
    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
		    //printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        printf("Insert Error\n%s\n", pE->getMsg());
        return 0;
    }  
           
	  	  try
    {
        if (!pCur->bindAuto())
        {
            printf("cursor doesn't contain resultset\n");
            return 0;
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("binding error\n%s\n", pE->getMsg());
        return 0;
    }

  //  int totalcount;
	int rem;
     //  char strmessage[91];
	//   const char *pBuff;
	try
    {
        bool bRC;
        for (bRC = pCur->first(); bRC; bRC = pCur->next())
        {
			//totalcount = pCur->getInt("usid");
			rem = pCur->getInt("status");


        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("load cursor error\n%s\n", pE->getMsg());
        return 0;
    }
        

    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();

	this->srtime= rem;

	return 1;
}

int User::setsrEvent(){
  CGOdbcConnect cCon;
    try
    {

        cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);

    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return 0;
    }

    //printf("Driver: %s\n", cCon.getDriver());

	char szQuery[91];
	
	sprintf(szQuery,"{call setsrevent ('%s',%d)}",this->getName(), this->srtime);
	 
	// printf("%s Has been caught cheating, type %d",this->getName(), type);
    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
		//    printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        //printf("Insert Error\n%s\n", pE->getMsg());
        return 0;
    }  
           
	  	  try
    {
        if (!pCur->bindAuto())
        {
            printf("cursor doesn't contain resultset\n");
            return 0;
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("binding error\n%s\n", pE->getMsg());
        return 0;
    }

   // int totalcount;
	int rem;
   //    char strmessage[91];
	//   const char *pBuff;
	try
    {
        bool bRC;
        for (bRC = pCur->first(); bRC; bRC = pCur->next())
        {
		//	totalcount = pCur->getInt("usid");
			rem = pCur->getInt("status");


        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("load cursor error\n%s\n", pE->getMsg());
        return 0;
    }


    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();
	
return rem;

}



//guild

void User::parseGuildSaveItem(BYTE* buffer){
	void (__thiscall *parseGuildSaveItem)(DWORD realUserPointer,BYTE* buffer) = ((void (__thiscall *)(DWORD,BYTE*))0x478c30);
	if(isWithinRange(&lastGuildOpen)||isWithinRange(&lastGuildStoneOpen)){
		return parseGuildSaveItem(reinterpret_cast<DWORD>(this->realUser),buffer);
	}
	logcheat(1); //log instead of kick
//	KickOut(0);
}
void User::parseGuildTakeBackItem(BYTE* buffer){
	void (__thiscall *parseGuildTakeBackItem)(DWORD realUserPointer,BYTE* buffer) = ((void (__thiscall *)(DWORD,BYTE*))0x479590);
	if(isWithinRange(&lastGuildOpen)||isWithinRange(&lastGuildStoneOpen)){
		
		return parseGuildTakeBackItem(reinterpret_cast<DWORD>(this->realUser),buffer);
	}
	logcheat(2); //log instead of kick
	//KickOut(0);
}
void User::parseGuildContribution(BYTE* buffer){
	void (__thiscall *parseGuildContribution)(DWORD realUserPointer,BYTE* buffer) = ((void (__thiscall *)(DWORD,BYTE*))0x47A500);
	if(isWithinRange(&lastGuildOpen)||isWithinRange(&lastGuildStoneOpen)){
		return parseGuildContribution(reinterpret_cast<DWORD>(this->realUser),buffer);
	}
	logcheat(3); //log instead of kick
	//KickOut(0);
}
void User::repairItemOpen(){
	convertToClient(reinterpret_cast<POINT*>(&lastRepairOpen),getX(),getY(),-1);
	lastRepairOpen.z = getZone();
	void (__thiscall *repairItemOpen)(DWORD realUserPointer) = ((void (__thiscall *)(DWORD))0x4545d0);
	return repairItemOpen(reinterpret_cast<DWORD>(this->realUser));
}
void User::parseRepairItem(BYTE* buffer){
	void (__thiscall *parseRepairItem)(DWORD realUserPointer,BYTE* buffer) = ((void (__thiscall *)(DWORD,BYTE*))0x454610);
	if(isWithinRange(&lastRepairOpen)){
		return parseRepairItem(reinterpret_cast<DWORD>(this->realUser),buffer);
	}
	logcheat(4); //log instead of kick
	//KickOut(0);
}
void User::openGuildTownStone(short unknown){
	convertToClient(reinterpret_cast<POINT*>(&lastGuildStoneOpen),getX(),getY(),-1);
	lastGuildStoneOpen.z = getZone();
	void (__thiscall *openGuildTownStone)(DWORD realUserPointer,short random) = ((void (__thiscall *)(DWORD,short))0x488F90);
	openGuildTownStone(reinterpret_cast<DWORD>(this->realUser),unknown);
}

void User::guildOpen(){
	convertToClient(reinterpret_cast<POINT*>(&lastGuildOpen),getX(),getY(),-1);
	lastGuildOpen.z = getZone();
        void (__thiscall *guildOpen)(DWORD realUserPointer) = ((void (__thiscall *)(DWORD))0x46A790);
	guildOpen(reinterpret_cast<DWORD>(this->realUser));
}

void User::parseSpecialMove(BYTE* buffer){
	void (__thiscall *parseSpecialMove)(DWORD realUserPointer,BYTE* buffer) = ((void (__thiscall *)(DWORD,BYTE*))0x488690);
	if(isWithinRange(&lastGuildStoneOpen)){
		return parseSpecialMove(reinterpret_cast<DWORD>(this->realUser),buffer);
	}
	logcheat(5); //log instead of kick
	//KickOut(0);
}
void User::parseMoveReq(BYTE* packetBuffer){
/*	for using original 1p1 function instead
	void (__thiscall *parseMove)(DWORD realUserPointer,BYTE* buffer) = ((void (__thiscall *)(DWORD,BYTE*))0x432F90);
	return parseMove(reinterpret_cast<DWORD>(this->realUser),buffer);*/
	int inX; // ebx@5
	int inY; // ebp@5
	BYTE* pktBuff; // edi@5
	int x; // ebx@10
	int y; // ebp@10
	POINT v9; // eax@10

	int v11; // edi@15
	__int16 v12; // [sp-8h] [bp-24h]@11
	__int16 v13; // [sp-8h] [bp-24h]@19


	DWORD offset; // [sp+10h] [bp-Ch]@5
	int currentStamina; // [sp+14h] [bp-8h]@5
	int direction; // [sp+20h] [bp+4h]@5

	BYTE* realUser = this->realUser;
	if ( checkRemainMagic(16) || isWarping() || checkRemainSpecialAttack(12) || checkRemainSpecialAttack(13) ){
		goto NO_MOVE;
	}
	pktBuff = packetBuffer;
	currentStamina = *(DWORD *)(realUser + 0x7210);
	offset = 0;
	inX = GetShort(packetBuffer, &offset);
	inY = GetShort(packetBuffer, &offset);
	direction = GetShort(packetBuffer, &offset);
	DWORD discarded = GetDWORD(pktBuff, &offset);
	if( inX == -1 || inY == -1 || !checkDistByPoint(inX, inY, 1)){
		goto NO_MOVE;
	}
	getStm();
	DWORD currentTime = GetTickCount();
	if(stepCounter >1){
		int average = (currentTime - stepTimes[stepCounter%2])/2;
		/* char string[50];
		sprintf_s(string,"Your average move speed is %d ms",average);
		sendChatMessage(string);*/
		if(average < 600){
		//	goto NO_MOVE;//instead of kickout, will just stop the move
			 //printf("%s (move)-> speed: %d  \n",this->getName(),average);
			this->spdhk++;
			if(this->spdhk > 2){
			KickOut(0);
			}
			
	
		} else{this->spdhk=0;}
	}

	if ( !move(inX, inY) )
	{
		*(DWORD *)(realUser + 0x7210) = currentStamina;
NO_MOVE:
		convertToClient(&v9, *(DWORD *)(realUser + 0x7260), *(DWORD *)(realUser + 0x7264), -1);
		x = v9.x;
		y = v9.y;
		offset = 0;
		SetByte((BYTE *)(realUser + 0x48B8), 4u, &offset);
		SetByte((BYTE *)(realUser + 0x48B8), 2u, &offset);
		SetInt(realUser + 0x48B8, *(DWORD *)(realUser + 8308), &offset);
		if ( isMapRange(110) )
		{
			v12 = (short)*reinterpret_cast<DWORD*>(0X509EBC);
		}else
		{
			v12 = -1;
		}
		SetShort(realUser + 0x48B8, v12, &offset);
		SetShort(realUser + 0x48B8, x, &offset);
		SetShort(realUser + 0x48B8, y, &offset);
		SetShort(realUser + 0x48B8, *(DWORD *)(realUser + 29200), &offset);
		SetShort(realUser + 0x48B8, *(DWORD *)(realUser + 30520), &offset);
		sendInsight( offset, (const void *)(realUser + 0x48B8));
		return;
	}
	//Move successful?? yes, save current time
	
	
	stepTimes[stepCounter++%2] = currentTime;

	int v10 = 100;
	if ( getRangeAbility() == 101 )
	{
		v10 = getRangeEffect1() + getItemRangeChange(101);
	}
	if ( !getRunMode())
	{
		v11 = v10 / 100 + getCurrentStamina();
		if ( v11 <= getMaxStm() ){
			*(DWORD *)(realUser + 29200) = v11;
		} else
		{
			*(DWORD *)(realUser + 0x7210) = getMaxStm();
		}
	}
	*(DWORD *)(realUser + 29716) = 0;
	*(DWORD *)(realUser + 0x7418) = GetTickCount();
	*(DWORD *)(realUser + 0x7738) = direction;
	checkSpeedHack( 5000);
	offset = 0;
	SetByte((BYTE *)(realUser + 18616), 4u, &offset);
	SetByte((BYTE *)(realUser + 18616), 1u, &offset);
	SetInt(realUser + 18616, getUserServerID(), &offset);
	if ( isMapRange(110) )
	{
		v13 = (short)*reinterpret_cast<DWORD*>(0x509EBC);
	}else
	{
		v13 = -1;
	}
	SetShort(realUser + 18616, v13, &offset);
	SetShort(realUser + 18616, inX, &offset);
	SetShort(realUser + 18616, inY, &offset);
	SetShort(realUser + 18616, getCurrentStamina(), &offset);
	SetShort(realUser + 18616, getDirection(), &offset);
	sendInsight( offset, (const void *)(realUser + 18616));
	if ( !*(DWORD *)(realUser + 8232) )
	{
		*(DWORD *)(realUser + 8228) = 0;
	}
	sightRecalc();
	guildTownWarStart();
	guildTownWarEnd();
	classWarStart();
	classWarEnd();
}
void User::parseRunReq(BYTE* packetBuffer){
  int x2; // ebx@5
  int y2; // ebp@5
  BYTE *v6; // edi@5
  int x1; // edi@6
  POINT* v8; // eax@19
  __int16 v9; // [sp-8h] [bp-2Ch]@13
  __int16 v10; // [sp-8h] [bp-2Ch]@20
  DWORD offset; // [sp+10h] [bp-14h]@5
  int dstX; // [sp+1Ch] [bp-8h]@5
  int dstY; // [sp+20h] [bp-4h]@19
  int y1; // [sp+28h] [bp+4h]@5

  if ( isInGuildWar() && getGuildRank() == 1  || checkRemainMagic(16)   || isWarping() )
  {
    x2 = (WORD)packetBuffer;
    y2 = (WORD)packetBuffer;
  }
  else
  {
    v6 = packetBuffer;
    offset = 0;
    x1 = GetShort(packetBuffer, &offset);
    y1 = GetShort(packetBuffer, &offset);
    x2 = GetShort(v6, &offset);
    y2 = GetShort(v6, &offset);
    dstX = GetShort(v6, &offset);
    GetDWORD(v6, &offset);

	DWORD currentTime = GetTickCount();
	if(stepCounter >1){
		int average = (currentTime - stepTimes[stepCounter%2])/2;
		/* char string[50];
		sprintf_s(string,"Your average move speed is %d ms",average);
		sendChatMessage(string);*/
		if(average < 300){
			//goto RUN_FAIL;//instead of kickout, will just stop the move
			//printf("%s (run)-> speed: %d  \n",this->getName(),average);
					this->spdhk++;
			if(this->spdhk > 2){
			KickOut(0);
			}
		} else{this->spdhk=0;}
	}

    if ( getStm() > 0 )
    {
      if ( isMovable_C(x1, y1) )
      {
		  stepTimes[stepCounter++%2] = currentTime;
        if ( checkDistByPoint( x2, y2, 2) && move( x2, y2) ){
			stepTimes[stepCounter++%2] = currentTime;
			goto LABEL_12;
		}
          
        if (checkDistByPoint(x1, y1, 1) && move( x1, y1) )
        {
			x2 = -1;
			y2 = -1;

LABEL_12:
		
			decStm();
			*reinterpret_cast<DWORD *>(realUser + 0x7418) = GetTickCount();
			*reinterpret_cast<DWORD *>(realUser + 0x7738) = dstX;
			checkSpeedHack( 5000);
			offset = 0;
			SetByte((BYTE *)(realUser + 0x48B8), 0x16u, &offset);
			SetByte((BYTE *)(realUser + 0x48B8), 1u, &offset);
			SetInt(realUser + 0x48B8, getUserServerID(), &offset);
			if ( isMapRange( 110) )
			{
				v9 = (short)*reinterpret_cast<DWORD *>(0x509EBC);
			}else
			{
				v9 = -1;
			}
			SetShort(realUser + 0x48B8, v9, &offset);
			SetShort(realUser + 0x48B8, x1, &offset);
			SetShort(realUser + 0x48B8, y1, &offset);
			SetShort(realUser + 0x48B8, x2, &offset);
			SetShort(realUser + 0x48B8, y2, &offset);
			SetShort(realUser + 0x48B8, getCurrentStamina(), &offset);
			SetShort(realUser + 0x48B8, getDirection(), &offset);
			sendInsight(offset, (const void *)(realUser + 0x48B8));
			if ( !isPreMagicCasted() )
			*reinterpret_cast<DWORD *>(realUser + 0x2024) = 0; //MagicCasted = 0
			sightRecalc();
			return;
			}
		}
    }
  }
  RUN_FAIL:
  v8 = convertToClient(reinterpret_cast<POINT *>(&x1), getX(), getY(), -1);
  dstX = *reinterpret_cast<DWORD *>(v8);
  dstY = *reinterpret_cast<DWORD *>(v8 + 4);
  offset = 0;
  SetByte((BYTE *)(realUser + 0x48B8), 0x16u, &offset);
  SetByte((BYTE *)(realUser + 0x48B8), 2u, &offset);
  SetInt(realUser + 0x48B8, getUserServerID(), &offset);
  if ( isMapRange( 110) )
  {
    v10 = (short)*reinterpret_cast<DWORD *>(0x509EBC);
  }
  else
  {
    v10 = -1;
  }
  SetShort(realUser + 0x48B8, v10, &offset);
  SetShort(realUser + 0x48B8, dstX, &offset);
  SetShort(realUser + 0x48B8, dstY, &offset);
  SetShort(realUser + 0x48B8, x2, &offset);
  SetShort(realUser + 0x48B8, y2, &offset);
  SetShort(realUser + 0x48B8, getCurrentStamina(), &offset);
  SetShort(realUser + 0x48B8, getDirection(), &offset);
  sendInsight(offset, (const void *)(realUser + 0x48B8));
}

void User::parseRunFirst(BYTE* packetBuffer){
  int v4; // ebx@5
  int v5; // ebp@5
  int v6; // edi@5
  int v7; // edi@6
  DWORD v8; // eax@12
  int v9; // edx@12
  int v10; // eax@19
  __int16 v11; // [sp-8h] [bp-34h]@13
  __int16 v12; // [sp-8h] [bp-34h]@20
  int *v13; // [sp-4h] [bp-30h]@13
  int *v14; // [sp-4h] [bp-30h]@20
  DWORD offset; // [sp+10h] [bp-1Ch]@5
  int v16; // [sp+14h] [bp-18h]@5
  int v17; // [sp+18h] [bp-14h]@5
  int v18; // [sp+1Ch] [bp-10h]@5
  POINT coords;
  int v19; // [sp+24h] [bp-8h]@5
  int v20; // [sp+28h] [bp-4h]@19
  int v21; // [sp+30h] [bp+4h]@5

 
  if ( *reinterpret_cast<DWORD *>(realUser + 0x7790) && *reinterpret_cast<DWORD *>(realUser + 0x734C) == 1
    || checkRemainMagic( 16)
    || *reinterpret_cast<DWORD *>(realUser + 0x7750) )
  {
    //LOWORD(v4) = (_WORD)packetBuffer;
    //LOWORD(v5) = (_WORD)packetBuffer;
  }
  else
  {

    offset = 0;
    v18 = GetShort(packetBuffer, &offset);
    v19 = GetShort(packetBuffer, &offset);
    v16 = GetShort(packetBuffer, &offset);
    v21 = GetShort(packetBuffer, &offset);
    v4 = GetShort(packetBuffer, &offset);
    v5 = GetShort(packetBuffer, &offset);
    v17 = GetShort(packetBuffer, &offset);
    GetDWORD(packetBuffer, &offset);

	DWORD currentTime = GetTickCount();
	if(stepCounter >1){
		int average = (currentTime - stepTimes[stepCounter%2])/2;
		/* char string[50];
		sprintf_s(string,"Your average move speed is %d ms",average);
		sendChatMessage(string);*/
		if(average < 300){
			//goto RUN_FAIL;//instead of kickout, will just stop the move
			//printf("%s (run)-> speed: %d  \n",this->getName(),average);
				this->spdhk++;
			if(this->spdhk > 2){
			KickOut(0);
			}
			
		} else{this->spdhk=0;}
	}
    if ( getStm() > 0 )
    {
      v7 = v16;
      if ( isMovable_C(v16, v21) )
      {
		stepTimes[stepCounter++%2] = currentTime;
        if ( checkDistByPoint(v4, v5, 2) && move( v4, v5) )
			stepTimes[stepCounter++%2] = currentTime;
          goto LABEL_12;
        if ( checkDistByPoint(v7, v21, 1) && move(v7, v21) )
        {
          v4 = -1;
          v5 = -1;
LABEL_12:
          decStm();
          v8 = GetTickCount();
          v9 = v17;
          *reinterpret_cast<DWORD *>(realUser + 0x7418) = v8;
          *reinterpret_cast<DWORD *>(realUser + 0x7738) = v9;
          checkSpeedHack(5000);
          offset = 0;
          SetByte((realUser + 0x48B8), 0x15u, &offset);
          SetByte((realUser + 0x48B8), 1u, &offset);
          SetInt(realUser + 0x48B8, *reinterpret_cast<DWORD *>(realUser + 0x2074), &offset);
          if ( isMapRange( 110) )
          {
            v11 = *reinterpret_cast<DWORD *>(0x509EBC);
          }
          else
          {
            v11 = -1;
          }
          SetShort(realUser + 0x48B8, v11, &offset);
          SetShort(realUser + 0x48B8, v18, &offset);
          SetShort(realUser + 0x48B8, v19, &offset);
          SetShort(realUser + 0x48B8, v16, &offset);
          SetShort(realUser + 0x48B8, v21, &offset);
          SetShort(realUser + 0x48B8, v4, &offset);
          SetShort(realUser + 0x48B8, v5, &offset);
          SetShort(realUser + 0x48B8, *reinterpret_cast<DWORD *>(realUser + 0x7210), &offset);
          SetShort(realUser + 0x48B8, *reinterpret_cast<DWORD *>(realUser + 0x7738), &offset);
          sendInsight( offset, (const void *)(realUser + 0x48B8));
          if ( !*reinterpret_cast<DWORD *>(realUser + 0x2028) )
            *reinterpret_cast<DWORD *>(realUser + 0x2024) = 0;
          sightRecalc();
          return;
        }
      }
    }
  }
RUN_FAIL:
  convertToClient(&coords, *reinterpret_cast<DWORD *>(realUser + 0x7260), *reinterpret_cast<DWORD *>(realUser + 0x7264), -1);
  v19 = coords.x;
  v20 = coords.y;
  offset = 0;
  SetByte((BYTE *)(realUser + 0x48B8), 0x15u, &offset);
  SetByte((BYTE *)(realUser + 0x48B8), 2u, &offset);
  SetInt(realUser + 0x48B8, *reinterpret_cast<DWORD *>(realUser + 0x2074), &offset);
  if ( isMapRange(110) )
  {
    v12 = *reinterpret_cast<DWORD *>(0x509EBC);
  }
  else
  {
    v12 = -1;
  }
  
  SetShort(realUser + 0x48B8, v12, &offset);
  SetShort(realUser + 0x48B8, v19, &offset);
  SetShort(realUser + 0x48B8, v20, &offset);
  SetShort(realUser + 0x48B8, v4, &offset);
  SetShort(realUser + 0x48B8, v5, &offset);
  SetShort(realUser + 0x48B8, *reinterpret_cast<DWORD *>(realUser + 0x7210), &offset);
  SetShort(realUser + 0x48B8, *reinterpret_cast<DWORD *>(realUser + 0x7738), &offset);
  sendInsight(offset, (const void *)(realUser + 0x48B8));

}

POINT* User::ConvertToServer(POINT* point,DWORD ClientX,DWORD ClientY,int zone){
POINT* (__thiscall  *ConvertToServer)(DWORD realUser,POINT* point,signed int ClientX,signed int ClientY,int zone) = ((POINT*(__thiscall  *)(DWORD,POINT*,signed int,signed int,int ))0x442770);
return ConvertToServer(reinterpret_cast<DWORD>(this->realUser),point,ClientX,ClientY,zone); 
}

signed int User::IsMovable_S(int x,int y){
signed int (__thiscall  *IsMovable_S)(DWORD realUser,int x,int y) = ((signed int(__thiscall  *)(DWORD,int,int ))0x432a50);
return IsMovable_S(reinterpret_cast<DWORD>(this->realUser),x,y);}

void User::CheckRangeAbility(){
void (__thiscall  *CheckRangeAbility)(DWORD realUser) = ((void(__thiscall  *)(DWORD))0x483500);
CheckRangeAbility(reinterpret_cast<DWORD>(this->realUser));}

int User::CheckGuildTown(int townnum)
{
    int (__thiscall  *CheckGuildTown)(DWORD realUser,int townnum) = ((int(__thiscall  *)(DWORD, int ))0x481e40);
    return CheckGuildTown(reinterpret_cast<DWORD>(this->realUser),townnum);
}

int User::CheckGuildTownAlly(int townnum)
{
    int (__thiscall  *CheckGuildTownAlly)(DWORD realUser,int townnum) = ((int(__thiscall  *)(DWORD,int ))0x481ea0);

    return CheckGuildTownAlly(reinterpret_cast<DWORD>(this->realUser),townnum);
}

int User::CheckPlusType(void* CMagicPtr, int a1)
{
//47b120	public: int __thiscall USER::CheckPlusType(class CMagic*, int)

	int(__thiscall * User_CheckPlusType)(DWORD realUser, void* CMagicPtr, int a1) = ((signed int(__thiscall*)(DWORD, void*, int))0x47b120);

	return User_CheckPlusType(reinterpret_cast<DWORD>(this->realUser), CMagicPtr, a1);
}

void User::SendMyInfo(char a2,BYTE a3){
void (__thiscall  *SendMyInfo)(DWORD realUser,char a2,BYTE a3) = ((void(__thiscall  *)(DWORD,char,BYTE ))0x42dc70);
SendMyInfo(reinterpret_cast<DWORD>(this->realUser),a2,a3);}


void User::LogOut(BYTE* packetBuffer){

void (__thiscall  *LogOut)(DWORD realUser,int packetBuffer) = ((void(__thiscall  *)(DWORD,int ))0x42fe90);
LogOut(reinterpret_cast<DWORD>(this->realUser),int(packetBuffer));
}

void User::user_diritem(int x1, int y1, int x2, int y2)
{
    //reset show timer
    this->setUserTimer(1);

    void (__thiscall  *call_User_DirItem)(DWORD realUser,BYTE a2,int x18,int y1a,int x3c,int y3e) = ((void(__thiscall  *)(DWORD,BYTE,int,int,int,int ))0x466540);
    call_User_DirItem(reinterpret_cast<DWORD>(this->realUser), this->getUserTimer(), x1, y1, x1, y2);
}

void User::ShowMagic(int num,int unkn){
	
		void (__thiscall *showmagic)(DWORD realUserPointer, int mnum, int unk) = ((void (__thiscall *)(DWORD, int,int))0x468FE0);
		showmagic(reinterpret_cast<DWORD>(this->realUser), num,unkn);
}

void User::Open_Guild_Store(int num){
		void (__thiscall *ogstore)(DWORD realUserPointer, int gnum) = ((void (__thiscall *)(DWORD, int))0x4891A0);
		ogstore(reinterpret_cast<DWORD>(this->realUser), num);
}

void User::Open_Guild_Store_Reg(int num){
		void (__thiscall *ogstore)(DWORD realUserPointer, int gnum) = ((void (__thiscall *)(DWORD, int))0x489140);
		ogstore(reinterpret_cast<DWORD>(this->realUser), num);
}

/*
bool User::GiveItem(int sNum,int sAmmount){
	
	DWORD uP = reinterpret_cast<DWORD>(this->realUser);
    DWORD iP;

	iP = item.NewItem(uP);
	item.CopyTableItem((void *)iP, sNum);
	//printf("inv 0x%X\n",getInventoryItemData());
	//printf("CurrentWeight: %d ItemWeight: %d MaxWeight: %d\n",getCurrentWeight(),item.getsWgt(iP),getMaxWgt());
	if (getCurrentWeight() + item.getsWgt(iP) > getMaxWgt()){
        sendChatMessage("<<< You can't give that item : It will exceed the bagweight limit. >>>");
        return false;
    }

	if(!CheckInvSlot()){
         sendChatMessage("<<< You have no more space in your inventory >>>");
         return false;
	}
  
	void (__thiscall  *GiveItem)(DWORD realUser,int sNum,int sAmmount) = ((void(__thiscall  *)(DWORD,int,int))0x00467190);
	GiveItem(reinterpret_cast<DWORD>(this->realUser),sNum,sAmmount);
	char strMsg[50];

	sprintf(strMsg,"<<< You have received: %s >>>",item.getstrName(iP));
	sendChatMessage(strMsg);
	return true;
}
*/
int User::selmsg(unsigned int a2){

int (__thiscall  *selmesffs)(DWORD realUser,unsigned int val) = ((int(__thiscall  *)(DWORD,unsigned int))0x00466B60);
return selmesffs(reinterpret_cast<DWORD>(this->realUser),a2);}

int User::LiveNPC(int sSid, int sNum, signed int X, signed int Y){
	//printf("LiveNPC -> sSid: %d Ammount: %d X: %d Y: %d\n",sSid,sNum,X,Y);

int (__thiscall  *LiveNPC)(DWORD realUser,int sSid, int sNum, signed int X, signed int Y) = ((int(__thiscall  *)(DWORD,int, int,signed int,signed int))0x00481D20);
return LiveNPC(reinterpret_cast<DWORD>(this->realUser),sSid,sNum,X,Y);}

void User::dirpoint(int x, int y, int x2, int y2){

void (__thiscall  *User__diritem_wrapper)(DWORD userPointer, BYTE a2, int a3, int a4, int a5, int a6) = ((void(__thiscall  *)(DWORD userPointer, BYTE , int , int , int , int))0x00466540);
User__diritem_wrapper( reinterpret_cast<DWORD>(this->realUser),  1,  x,  y,  x2,  y2);

}

void User::SendAll(unsigned int a2, const void *a3)
{
    void (__thiscall  *User__diritem_wrapper)(DWORD userPointer, unsigned int i1, const void* p2) = ((void(__thiscall  *)(DWORD userPointer, unsigned int, const void*))0x0042DBA0);
    User__diritem_wrapper( reinterpret_cast<DWORD>(this->realUser),  a2,a3);
}


#pragma region EVERYTHING HERE NEEDS TO BE REVIEWED

void User::RunEventByNum(int eventnum){

void (__thiscall  *User__runeventbynum_wrapper)(DWORD userPointer, int num) = ((void(__thiscall  *)(DWORD userPointer, int))0x00468A40);
User__runeventbynum_wrapper( reinterpret_cast<DWORD>(this->realUser),  eventnum);

}

signed int User::RunExtEvent(int userpointer, int npcpointer, int evtnum, int zone, EventManager *EvtMngr)
{
	
    int v27 = 0;

    User* susr = User::getExtentionUserFromRealUser((void*)userpointer);

    bool ORlogic = true; // default
	bool ORlogicinit = true;
    if((int)evtnum >0){
    // event manager look up test
          //  printf("EVENT MANAGER LOOK UP\n");

         //   printf("EVENT %d on ZONE %d :\n",(int)evtnum,(int)zone);
            if(evtmngr != NULL)
            {
				printf("reee %d \n",evtnum);
                EventData* evt = EvtMngr->GetEventData((int)zone,(int)evtnum);
                    if(evt)
                    { // not null

				printf("debug evtid: %d \n",evt->eventid);

				for(int i = 0; i< evt->instructions.size();i++){
					printf("debug type: %d  command: %d \n",evt->instructions[i].eventtype,evt->instructions[i].eventenum);
					printf("params: ");
					for(int j=0;j< evt->instructions[i].params.size();j++){
						printf(" %d",evt->instructions[i].params[j]);
					}
					printf("\n");
				}


                        // first check logic
                        for(int i=0; i< evt->instructions.size();i++){


                               if(evt->instructions[i].eventtype == 0){ // A and
                                   if(!RunExtEventSection(userpointer, npcpointer,evt,i,zone,EvtMngr)){
                                      return 0;
                                   }
                                 }
                              else if(evt->instructions[i].eventtype == 1){ //O or
								  	if(ORlogicinit){
								      ORlogic = false;
									  ORlogicinit = false;
								     }
                                   ORlogic = ((RunExtEventSection(userpointer,npcpointer,evt,i,zone,EvtMngr) > 0 ) || ORlogic);

                                 }
                              else if(evt->instructions[i].eventtype == 2){ // E execution
                                           // do nothing
                                           continue;
                                       }
                              else{
                                   printf("Unknown Logic Gate in Event num:%d zone:%d line:%d\n",evt->eventid,this->getZone(),i);

                                 }

                        }

                        if(!ORlogic){
                            return 0; // failed or logic
                        }

                        // now execute

                        for(int i=0; i< evt->instructions.size();i++){

                            if(evt->instructions[i].eventtype == 0){ // A and
                                // do nothing
                                continue;

                              }
                           else if(evt->instructions[i].eventtype == 1){ //O or
                            // do nothing
                             continue;

                              }
                           else if(evt->instructions[i].eventtype == 2){ // E execution
                                        // execute
                                       RunExtEventSection(userpointer,npcpointer,evt,i,zone,EvtMngr);
                                    }
                           else{
                                printf("Unknown Logic Gate in Event num:%d zone:%d line:%d\n",evt->eventid,this->getZone(),i);

                              }

                        }
                     }
                     else{
                    printf("EVENT %d on ZONE %d NOT FOUND!\n",evtnum,(int)susr->getZone());
                     return 0;
                     }

            }
            else
            {
               printf("EVENT Manager NOT INITILIZED!\n");
               return 0;
            }

    }

    return 0;
}

signed int User::RunExtEventSection(int userpointer, int npcpointer, EventData *evt, int index, int zone, EventManager *EvtMngr)
{
    int v27 = 0;
	
//	struct  {
	//	BYTE m_Exec;
	      int EXEC[20];
		 unsigned int a2;//[10];
	//} * EXEC;

		 const char * msg[5];


	
    if(evt)
    {
        if(index < evt->instructions.size())
        {
			printf("run ext event section event: %d enum: %d zone: %d \n",evt->eventid,evt->instructions[index].eventenum,zone);
            switch(evt->instructions[index].eventenum)
            {
            // E Executoin
            case 1u:
                 if(evt->instructions[index].params.size() > 2)
                 {
                   this->LinkToOtherZone(evt->instructions[index].params[2],evt->instructions[index].params[0],evt->instructions[index].params[1]);
                  return 1;
                 }
                 else{
                   return 0;
                 }
               case 2u:    
                 if(evt->instructions[index].params.size() > 0){
                   this->SendNpcSay(npcpointer,evt->instructions[index].params[0]);
                  return 1;
                 }
                 else{
                   return 0;
                 }
               case 3u:
                 if(evt->instructions[index].params.size() > 3){
                   this->SendStoreOpen(evt->instructions[index].params[0],evt->instructions[index].params[1],evt->instructions[index].params[2],evt->instructions[index].params[3]);
                  return 1;
                 }
                 else{
                   return 0;
                 }
               case 4u:
                if(evt->instructions[index].params.size() > 1){
                  this->GiveItem(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 5u:
                if(evt->instructions[index].params.size() > 1){
                  this->RobItem(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 6u: 
                 if(evt->instructions[index].params.size() > 0){
                   this->GiveMagic(evt->instructions[index].params[0]);
                  return 1;
                 }
                 else{
                   return 0;
                 }
               case 7u:
                if(evt->instructions[index].params.size() > 0){
                  this->RobMagic(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 8u:
                if(evt->instructions[index].params.size() > 1){
                  this->BBSOpen(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else if(evt->instructions[index].params.size() > 0){ // overload
                    this->BBSOpen(evt->instructions[index].params[0],0);
                   return 1;
                }
                else{
                  return 0;
                }
               case 14u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeHP(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 15u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeMP(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 16u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeSTR(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 17u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeDEX(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 18u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeINT(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 19u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeWIS(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 20u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeCHA(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 21u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeCON(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 35u:
                if(evt->instructions[index].params.size() > 1){
                  this->ShowMagic(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else if(evt->instructions[index].params.size() > 0){ // overload
                    this->ShowMagic(evt->instructions[index].params[0],0);
                   return 1;
                }
                else{
                  return 0;
                }
               case 36u:
                 if(evt->instructions[index].params.size() > 5){
                   this->MakerOpen(evt->instructions[index].params[0],evt->instructions[index].params[1],evt->instructions[index].params[2]
                             ,evt->instructions[index].params[3]
                             ,evt->instructions[index].params[4]
                             ,evt->instructions[index].params[5]
                             );
                  return 1;
                 }
                 else{
                   return 0;
                 }
               case 37u:
                if(evt->instructions[index].params.size() > 0){
                  this->storageOpen(evt->instructions[index].params[0]);
                 return 1;
                }
                else{ //overload
                    this->storageOpen(1);
                  return 1;
                }
               case 38u:
                if(evt->instructions[index].params.size() > 0){
                  this->AuctionSellOpen(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 39u:
                if(evt->instructions[index].params.size() > 0){
                  this->AuctionBuyOpen(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 40u:
                if(evt->instructions[index].params.size() > 8){

    			  // set up last npc pointer for recv sel msg
			this->plastnpc = npcpointer;
				// construct old EXEC struct 	

	                  a2 = (unsigned int)&EXEC;
					  *(DWORD *)(a2 + 8) = (DWORD)evt->instructions[index].params[0];
    			      *(DWORD *)(a2 + 0xC) = (DWORD)evt->instructions[index].params[1];
    			      *(DWORD *)(a2 + 0x10) = evt->instructions[index].params[2];
    			      *(DWORD *)(a2 + 0x14) = (DWORD)evt->instructions[index].params[3];
    			      *(DWORD *)(a2 + 0x18) = evt->instructions[index].params[4];
    			      *(DWORD *)(a2 + 0x1C) = (DWORD)evt->instructions[index].params[5];
    			      *(DWORD *)(a2 + 0x20) = evt->instructions[index].params[6];
    			      *(DWORD *)(a2 + 0x24) = (DWORD)evt->instructions[index].params[7];
    			      *(DWORD *)(a2 + 0x28) = evt->instructions[index].params[8];

					 this->selmsg((unsigned int)EXEC);
					 

					/*
				   	// new ext function
					
					   this->Selectmsg(evt->instructions[index].params[0], // intro
                            evt->instructions[index].params[1],   // msg1
                           evt->instructions[index].params[2],   // evt1
                            evt->instructions[index].params[3],   // msg2 
                            evt->instructions[index].params[4],    //evt2 
                            evt->instructions[index].params[5],  //msg3
                            evt->instructions[index].params[6],  //evt3
                            evt->instructions[index].params[7],   //msg4 
                            evt->instructions[index].params[8]   //evt4
                            );

					       
					*/		
							
                 return 1;
                }
                else{
                  return 0;
                }
               case 41u:
                if(evt->instructions[index].params.size() > 0){
                  this->MessageOK(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 42u:
                if(evt->instructions[index].params.size() > 0){
                  this->MessageNONE(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 43u:
                if(evt->instructions[index].params.size() > 0){
                  this->GiveGold(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 44u:
                if(evt->instructions[index].params.size() > 0){
                  this->RobGold(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 45u: // recursion
                if(evt->instructions[index].params.size() > 0){
					this->RunExtEvent(userpointer,npcpointer,(int)evt->instructions[index].params.at(0),zone,EvtMngr);
                 return 1;
                }
                else{
                  return 0;
                }
               case 46u:
                if(evt->instructions[index].params.size() > 0){
                  this->AddEvent(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 47u:
                if(evt->instructions[index].params.size() > 0){
                  this->AddEvent(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 48u:
                 if(evt->instructions[index].params.size() > 0){
                    srand(time(NULL)); //rng seed
                   this->SendNpcSay(npcpointer,evt->instructions[index].params[rand() % evt->instructions[index].params.size()]);
                  return 1;
                 }
                 else{
                   return 0;
                 }
               case 49u:
                 return 0;
               case 50u:
                if(evt->instructions[index].params.size() > 0){
                  this->ChangeMageType(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 51u:
                 this->guildOpen();
                 return 1;
               case 52u:
                 this->repairItemOpen();
                 return 1;
               case 53u:
                if(evt->instructions[index].params.size() > 0){
                  this->GiveSpecialAttack(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 54u:
                 this->KillNpc();
                 return 1;
               case 55u:
                if(evt->instructions[index].params.size() > 1){
                  this->PlusMoral(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 56u:
                if(evt->instructions[index].params.size() > 0){
                  this->OpenContribution(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 57u:
                if(evt->instructions[index].params.size() > 0){
                  this->ChangeStorageType(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 64u:
                if(evt->instructions[index].params.size() > 2){
                  this->WarpGate(evt->instructions[index].params[0],evt->instructions[index].params[1],evt->instructions[index].params[2]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 65u:
                if(evt->instructions[index].params.size() > 0){
                  this->AuctionDrawNOBID(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 66u:
                if(evt->instructions[index].params.size() > 0){
                  this->AuctionDrawNOBUY(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 67u:
                if(evt->instructions[index].params.size() > 0){
                  this->AuctionBuyItem(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 68u:
                if(evt->instructions[index].params.size() > 0){
                  this->AuctionGetMoney(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 69u:
                 this->AuctionDeleteBadlist();
                 return 1;
               case 70u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeMaxHp(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 71u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeMaxMP(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 72u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeMaxSTM(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 73u:
                if(evt->instructions[index].params.size() > 1){
                  this->ChangeMaxWGT(evt->instructions[index].params[0],evt->instructions[index].params[1]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 80u:
                if(evt->instructions[index].params.size() > 3){
                  this->OpenHairShop(evt->instructions[index].params[0],evt->instructions[index].params[1],evt->instructions[index].params[2]
                            ,evt->instructions[index].params[3]
                            );
                 return 1;
                }
                else{
                  return 0;
                }
               case 81u:
                if(evt->instructions[index].params.size() > 3){
                  this->LiveNPC(evt->instructions[index].params[0],evt->instructions[index].params[1],evt->instructions[index].params[2]
                            ,evt->instructions[index].params[3]
                            );
                 return 1;
                }
                else{
                  return 0;
                }
               case 82u:
                if(evt->instructions[index].params.size() > 0){
                  this->AddServerEvent(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 83u:
                if(evt->instructions[index].params.size() > 0){
                  this->DelServerEvent(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 84u:
                if(evt->instructions[index].params.size() > 0){
                  this->GiveMakeSkill(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 85u:
                if(evt->instructions[index].params.size() > 0){
                  this->OpenSpecialMakeSkill(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 86u:
                if(evt->instructions[index].params.size() > 0){
                  this->openGuildTownStone(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 87u:
                if(evt->instructions[index].params.size() > 0){
                  this->OpenGuildTownTaxRate(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 88u:
                if(evt->instructions[index].params.size() > 0){
                  this->Open_Guild_Store_Reg(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 89u:
                if(evt->instructions[index].params.size() > 0){
                  this->Open_Guild_Store(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 96u:
                if(evt->instructions[index].params.size() > 0){
                  this->RunMagic(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 97u:
                if(evt->instructions[index].params.size() > 0){
                  this->RunSattack(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 98u:
                if(evt->instructions[index].params.size() > 5){
                  this->OpenTrader(evt->instructions[index].params[0],evt->instructions[index].params[1],evt->instructions[index].params[2]
                            ,evt->instructions[index].params[3]
                            ,evt->instructions[index].params[4]
                            ,evt->instructions[index].params[5]
                            );
                 return 1;
                }
                else{
                  return 0;
                }
               case 99u:
                 this->OpenChangeItem();
                 return 1;
               case 100u:
                if(evt->instructions[index].params.size() > 2){
                  this->CounterStart(evt->instructions[index].params[0],evt->instructions[index].params[1],evt->instructions[index].params[2]
                            );
                 return 1;
                }
                else{
                  return 0;
                }
               case 101u:
                 this->CounterInit();
                 return 1;
               case 102u:
                 this->OpenMonsterSelect();
                 return 1;
               case 103u:
                this->TimerStart();
                 return 1;
               case 104u:
                this->TimerInit();
                 return 1;
               case 105u:
                if(evt->instructions[index].params.size() > 0){
                  this->SetEventCount(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 112u:
                 this->SetEventCount(-1);
                 return 1;
               case 113u:
                if(evt->instructions[index].params.size() > 0){
                  this->OpenClassPointStore(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 114u:
                 this->OpenMonsterZone();
                 return 1;
               case 115u:
                 this->XmasPointUser();
                 return 1;
               case 116u:
                 this->XmasPointGuild();
                 return 1;
               case 117u:
                if(evt->instructions[index].params.size() > 0){
                  this->ChangePKMode(evt->instructions[index].params[0]);
                 return 1;
                }
                else{
                  return 0;
                }
               case 118u:
                 this->GivePosFromPosItem();
                 return 1;
               case 119u:
                if(evt->instructions[index].params.size() > 3){
                  this->user_diritem(evt->instructions[index].params[0],evt->instructions[index].params[1],evt->instructions[index].params[2]
                            ,evt->instructions[index].params[3]
                            );
							
                 return 1;
                }
                else{
                  return 0;
                }
               case 120u:  //rain
                if(evt->instructions[index].params.size() > 0){
                  this->setRain(evt->instructions[index].params[0]);
				  
                 return 1;
                }
                else { // overload toggle
                  this->setRain(-1);
                  return 1;
                }

            // O/A Logic   ext O/A commands have +1000 added to them
            case 1001u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getLevel() >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getLevel() <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1002u:
                if(evt->instructions[index].params.size() > 0){
                  if( (this->getGender() == evt->instructions[index].params[0] )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1003u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getAge() >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getAge() <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1004u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getHP() >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getHP() <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1005u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getMP() >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getMP() <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1006u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getStr() / 1000000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getStr() / 1000000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1007u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getDex() / 10000000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getDex() / 10000000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1008u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getInt() / 1000000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getInt() / 1000000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1009u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getWis() / 10000000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getWis() / 10000000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1010u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getCha() / 10000000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getCha() / 10000000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1011u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getCon() / 1000000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getCon() / 1000000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1012u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getDMagic() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getDMagic() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1013u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getWMagic() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getWMagic() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1014u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getBMagic() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getBMagic() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1015u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getSword() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getSword() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1016u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getSpear() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getSpear() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1017u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getAxe() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getAxe() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1018u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getBow() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getBow() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1019u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getKnuckle() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getKnuckle() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1020u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getWeaponCraft() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getWeaponCraft() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1021u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getArmorCraft() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getArmorCraft() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1022u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getAccCraft() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getAccCraft() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1023u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getPotionCraft() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getPotionCraft() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1024u:
                if(evt->instructions[index].params.size() > 1){
                  if( (this->getCookingCraft() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                       &&
                     (this->getCookingCraft() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1025u:
                if(evt->instructions[index].params.size() > 1){
                  if( this->ExistItem( evt->instructions[index].params[0], evt->instructions[index].params[1] )
                       >= evt->instructions[index].params[1]
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1026u:
                if(evt->instructions[index].params.size() > 0){
                  if( !AbsentItem( evt->instructions[index].params[0] ) ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1027u:
                if(evt->instructions[index].params.size() > 1){
                  if( this->ExistItemType( evt->instructions[index].params[0], evt->instructions[index].params[1] )
                       >= evt->instructions[index].params[1]
                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1028u:
                if(evt->instructions[index].params.size() > 0){
                  if( !AbsentItemType( evt->instructions[index].params[0] ) ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1029u:
                if(evt->instructions[index].params.size() > 0){
                  if( FindMagic( evt->instructions[index].params[0] ) ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1030u:
                if(evt->instructions[index].params.size() > 0){
                  if( !FindMagic( evt->instructions[index].params[0] ) ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1031u:
                if(evt->instructions[index].params.size() > 0){
                  if( FindEvent( evt->instructions[index].params[0] ) ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1032u:
                if(evt->instructions[index].params.size() > 0){
                  if( !FindEvent( evt->instructions[index].params[0] ) ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1033u:
                if(evt->instructions[index].params.size() > 1){
                  if( this->CheckTime( evt->instructions[index].params[0], evt->instructions[index].params[1] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1034u:
                if(evt->instructions[index].params.size() > 0){
                  if( this->RNGRand( evt->instructions[index].params[0] ) ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1035u:
                if(evt->instructions[index].params.size() > 1){
                  if( this->CheckGold( evt->instructions[index].params[0], evt->instructions[index].params[1] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1036u:
                if(evt->instructions[index].params.size() > 3){
                  if( this->CheckGameTime( evt->instructions[index].params[0], evt->instructions[index].params[1], evt->instructions[index].params[2], evt->instructions[index].params[3] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1037u:
                if(evt->instructions[index].params.size() > 2){
                  if( this->CheckGameDay( evt->instructions[index].params[0], evt->instructions[index].params[1], evt->instructions[index].params[2] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1038u:
                if(evt->instructions[index].params.size() > 1){
                  if( this->CheckGameMonth( evt->instructions[index].params[0], evt->instructions[index].params[1] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1039u:
                if(evt->instructions[index].params.size() > 2){
                  if( this->HowMuchItem( evt->instructions[index].params[0], evt->instructions[index].params[1], evt->instructions[index].params[2] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1040u:
                if(evt->instructions[index].params.size() > 1){
                  if( this->Moral( evt->instructions[index].params[0], evt->instructions[index].params[1] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1041u:
                if(evt->instructions[index].params.size() > 1){
                  if( this->CheckMageType( evt->instructions[index].params[0], evt->instructions[index].params[1] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1048u:
                if(evt->instructions[index].params.size() > 10){
                  if( this->CheckWeight( evt->instructions[index].params[0], evt->instructions[index].params[1] ,
                                         evt->instructions[index].params[2], evt->instructions[index].params[3] ,
                                         evt->instructions[index].params[4], evt->instructions[index].params[5] ,
                                         evt->instructions[index].params[6], evt->instructions[index].params[7] ,
                                         evt->instructions[index].params[8], evt->instructions[index].params[9] ,
                                         evt->instructions[index].params[10]

                                         )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1049u:
                if(evt->instructions[index].params.size() > 0){
                  if( this->CheckRank( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1050u:
                if(evt->instructions[index].params.size() > 10){
                  if( this->CheckItemSlot( evt->instructions[index].params[0], evt->instructions[index].params[1] ,
                                         evt->instructions[index].params[2], evt->instructions[index].params[3] ,
                                         evt->instructions[index].params[4], evt->instructions[index].params[5] ,
                                         evt->instructions[index].params[6], evt->instructions[index].params[7] ,
                                         evt->instructions[index].params[8], evt->instructions[index].params[9] ,
                                         evt->instructions[index].params[10]

                                         )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1051u:
                if(evt->instructions[index].params.size() > 4){
                  if( this->CheckPosition( evt->instructions[index].params[0], evt->instructions[index].params[1] ,
                                         evt->instructions[index].params[2], evt->instructions[index].params[3] ,
                                         evt->instructions[index].params[4]

                                         )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1052u:
               if ( this->CheckFirstClick()){
                  return 1;
               }
               else{
                   return 0;
               }

             case 1053u:
                if(evt->instructions[index].params.size() > 0){
                  if( this->CheckStorageType( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1054u:
               if ( this->CheckAuctionBadList(&v27) ){
                  return 1;
               }
               else{
                   return 0;
               }

             case 1055u:
                if(evt->instructions[index].params.size() > 0){
                  if( this->CheckAuctionState( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1056u:
                if(evt->instructions[index].params.size() > 0){
                  if( FindSpecialAttack( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1057u:
                if(evt->instructions[index].params.size() > 0){
                  if( !FindSpecialAttack( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1064u:
                if(evt->instructions[index].params.size() > 0){
                  if( MageType( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1065u:
                if(evt->instructions[index].params.size() > 0){
                  if( !MageType( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1066u:                
                if(evt->instructions[index].params.size() > 1){
                  if( CheckAliveNpc( evt->instructions[index].params[0],evt->instructions[index].params[1] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1067u:
                if(evt->instructions[index].params.size() > 0){
                  if( FindMakeSkill( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1068u:
                if(evt->instructions[index].params.size() > 0){
                  if( !FindMakeSkill( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1069u:
                if(evt->instructions[index].params.size() > 0){
                  if( this->CheckGuildTown( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1070u:
                if(evt->instructions[index].params.size() > 0){
                  if( this->CheckGuildRank( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1071u: // aka do nothing
                if(evt->instructions[index].params.size() > 6){
                  if( this->CompareBasicValue( evt->instructions[index].params[0], evt->instructions[index].params[1] ,
                                         evt->instructions[index].params[2], evt->instructions[index].params[3] ,
                                         evt->instructions[index].params[4], evt->instructions[index].params[5] ,
                                         evt->instructions[index].params[6]
                                         )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1072u:
                if(evt->instructions[index].params.size() > 0){
                  if( this->CheckMyJob( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1073u:
                if(evt->instructions[index].params.size() > 0){
                  if( this->CheckGuildTownAlly( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1080u:
                if(evt->instructions[index].params.size() > 0){
                  if( this->CheckGuildTownWar( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1081u:
                if(evt->instructions[index].params.size() > 1){
                  if( CheckGuildTownLevel( evt->instructions[index].params[0],evt->instructions[index].params[1] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1082u:
                   if(evt->instructions[index].params.size() > 1){
                     if( (this->getStaff() / 100000 >= evt->instructions[index].params[0] || evt->instructions[index].params[0] < 0 ) //overload for -1 being unbound
                          &&
                        (this->getStaff() / 100000 <= evt->instructions[index].params[1] || evt->instructions[index].params[1] < 0 )
                          ){
                              return 1;
                           }
                      else{  // failed check
                              return 0;
                          }
                   }
                   else { // fail not enough args
                     return 0;
                   }
             case 1083u:
               if ( !CheckDemon(getClass()) && !CheckMonster(getClass()) ){
                return 1;
               }
               else{
                   return 0;
               }

               break;
             case 1084u:
               if ( CheckDemon(getClass()) ){
                   return 1;
               }
               else{
                   return 0;
               }

             case 1085u:
               if ( CheckMonster(getClass()) ){
                   return 1;
               }
               else{
                   return 0;
               }

             case 1086u:
                if(evt->instructions[index].params.size() > 1){
                  if( this->CheckCounter( evt->instructions[index].params[0], evt->instructions[index].params[1] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1087u:
                if(evt->instructions[index].params.size() > 1){
                  if( this->CheckTimer( evt->instructions[index].params[0], evt->instructions[index].params[1] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1088u:
                if(evt->instructions[index].params.size() > 1){
                  if( this->CheckEventCount( evt->instructions[index].params[0], evt->instructions[index].params[1] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1089u:
                if(evt->instructions[index].params.size() > 0){
                  if( this->CheckPayType( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1096u:
                if( this->CheckClassTown()){
                         return 1;
                      }
                 else{  // failed check
                         return 0;
                     }
             case 1097u:
                if( this->CheckClassTownWar()){
                         return 1;
                      }
                 else{  // failed check
                         return 0;
                     }
             case 1098u:
                if( this->CheckHaveEventBook()){
                         return 1;
                      }
                 else{  // failed check
                         return 0;
                     }
             case 1099u:
                if( this->CheckEventBook()){
                         return 1;
                      }
                 else{  // failed check
                         return 0;
                     }
             case 1100u:
                if(evt->instructions[index].params.size() > 0){
                  if( this->CheckPkMode( evt->instructions[index].params[0] )

                       ){
                           return 1;
                        }
                   else{  // failed check
                           return 0;
                       }
                }
                else { // fail not enough args
                  return 0;
                }
             case 1101u:
                if( this->CheckPayAccount()){
                         return 1;
                      }
                 else{  // failed check
                         return 0;
                     }
             case 1102u:
                if( this->PayAccount()){
                         return 1;
                      }
                 else{  // failed check
                         return 0;
                     }
             default:
                printf("Unknown Instruction in Event num:%d zone:%d line:%d\n",evt->eventid,this->getZone(),index);
               return 0;
            }
        }
        else{
            // invalid index
                printf("Invalid Instruction Index in Event num:%d zone:%d line:%d\n",evt->eventid,this->getZone(),index);
            return 0;
        }

    }
    else{
        // invalid evt data
               printf("Fetal! Invalid Event data while executing Instructions. \n");
         return 0;
    }


    }

    signed int User::LinkToOtherZone(int zone, int x, int y)
    {
        signed int (__thiscall  *LTOZ)(DWORD realUser,int a1,int a2,int a3) = ((signed int(__thiscall  *)(DWORD,int,int,int ))0x0043EFC0);
        return LTOZ(reinterpret_cast<DWORD>(this->realUser),zone,x,y);
    }

    void User::SendNpcSay(int npcpointer, int npcchat)
    {
        void (__thiscall  *User__SendNpcSay_wrapper)(DWORD userPointer,DWORD npc, int id) = ((void(__thiscall  *)(DWORD , DWORD, int))0x0044E5D0);
        User__SendNpcSay_wrapper( reinterpret_cast<DWORD>(this->realUser),npcpointer, npcchat);

    }

    void User::RobItem(int itemnum, int ammount)
    {
        void (__thiscall  *User__RobItem_wrapper)(DWORD userPointer, int id, int count) = ((void(__thiscall  *)(DWORD , int, int))0x00467570);
        User__RobItem_wrapper( reinterpret_cast<DWORD>(this->realUser),itemnum, ammount);
    }

    void User::GiveMagic(int num)
    {
        void (__thiscall  *User__GiveMagic_wrapper)(DWORD userPointer, int count) = ((void(__thiscall  *)(DWORD , int))0x0045FEE0);
        User__GiveMagic_wrapper( reinterpret_cast<DWORD>(this->realUser), num);
    }

    void User::RobMagic(int num)
    {
        void (__thiscall  *User__RobMagic_wrapper)(DWORD userPointer, int count) = ((void(__thiscall  *)(DWORD , int))0x00460120);
        User__RobMagic_wrapper( reinterpret_cast<DWORD>(this->realUser), num);
    }

    void User::BBSOpen(int num, int mode)
    {
       if (mode < 0 || mode > 4){
        mode = 1;
       }

      this->setBBSMode(mode);

        void (__thiscall  *User__BBSOpen_wrapper)(DWORD userPointer, int id) = ((void(__thiscall  *)(DWORD , int))0x00450E70);
        User__BBSOpen_wrapper( reinterpret_cast<DWORD>(this->realUser), num);
    }

    void User::ChangeHP(int type, int amount)
    {
        void (__thiscall  *User__ChangeHP_wrapper)(DWORD userPointer, int mode, int num) = ((void(__thiscall  *)(DWORD , int,int))0x00468AC0);
        User__ChangeHP_wrapper( reinterpret_cast<DWORD>(this->realUser), type,amount);
    }

    void User::ChangeMP(int type, int amount)
    {
        void (__thiscall  *User__ChangeHP_wrapper)(DWORD userPointer, int mode, int num) = ((void(__thiscall  *)(DWORD , int,int))0x00468B40);
        User__ChangeHP_wrapper( reinterpret_cast<DWORD>(this->realUser), type,amount);
    }

    void User::ChangeSTR(int type, int amount)
    {
        void (__thiscall  *User__ChangeHP_wrapper)(DWORD userPointer, int mode, int num) = ((void(__thiscall  *)(DWORD , int,int))0x00468E00);
        User__ChangeHP_wrapper( reinterpret_cast<DWORD>(this->realUser), type,amount);
    }

    void User::ChangeDEX(int type, int amount)
    {
        void (__thiscall  *User__ChangeHP_wrapper)(DWORD userPointer, int mode, int num) = ((void(__thiscall  *)(DWORD , int,int))0x00468D00);
        User__ChangeHP_wrapper( reinterpret_cast<DWORD>(this->realUser), type,amount);
    }

    void User::ChangeINT(int type, int amount)
    {
        void (__thiscall  *User__ChangeHP_wrapper)(DWORD userPointer, int mode, int num) = ((void(__thiscall  *)(DWORD , int,int))0x00468C70);
        User__ChangeHP_wrapper( reinterpret_cast<DWORD>(this->realUser), type,amount);
    }

    void User::ChangeWIS(int type, int amount)
    {
        void (__thiscall  *User__ChangeHP_wrapper)(DWORD userPointer, int mode, int num) = ((void(__thiscall  *)(DWORD , int,int))0x00468D80);
        User__ChangeHP_wrapper( reinterpret_cast<DWORD>(this->realUser), type,amount);
    }

    void User::ChangeCHA(int type, int amount)
    {
        void (__thiscall  *User__ChangeHP_wrapper)(DWORD userPointer, int mode, int num) = ((void(__thiscall  *)(DWORD , int,int))0x00468E90);
        User__ChangeHP_wrapper( reinterpret_cast<DWORD>(this->realUser), type,amount);
    }

    void User::ChangeCON(int type, int amount)
    {
        void (__thiscall  *User__ChangeHP_wrapper)(DWORD userPointer, int mode, int num) = ((void(__thiscall  *)(DWORD , int,int))0x00468F10);
        User__ChangeHP_wrapper( reinterpret_cast<DWORD>(this->realUser), type,amount);
    }

    void User::MakerOpen(int a1, int a2, int a3, int a4, int a5, int a6)
    {
        *(DWORD *)(this->realUser + 0x7B30) = -1; //wtf?

        void (__thiscall  *User__MakerOpen_wrapper)(DWORD userPointer, int num1, int num2, int num3, int num4, int num5, int num6) = ((void(__thiscall  *)(DWORD , int,int, int,int, int,int))0x00451FB0);
        User__MakerOpen_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,  a2,  a3,  a4,  a5,  a6);
    }

    void User::AuctionSellOpen(int a1)
    {

        void (__thiscall  *User__AuctionSellOpen_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00461810);
                User__AuctionSellOpen_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::AuctionBuyOpen(int a1)
    {
        void (__thiscall  *User__AuctionBuyOpen_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00463560);
                User__AuctionBuyOpen_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::MessageOK(int a1)
    {
        void (__thiscall  *User__MessageOK_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00466ED0);
                User__MessageOK_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::MessageNONE(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00466F50);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::GiveGold(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00467610);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::RobGold(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00467650);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::AddEvent(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x004676E0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);

    }

    void User::DelEvent(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00467760);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::ChangeMageType(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00469150);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::GiveSpecialAttack(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x0047BDA0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::KillNpc()
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((void(__thiscall  *)(DWORD))0x00481CE0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    void User::PlusMoral(int a1, int a2)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2) = ((void(__thiscall  *)(DWORD , int,int))0x00481C50);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2);
    }

    void User::OpenContribution(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00482720);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    int User::ChangeStorageType(int a1)
    {
         int (__thiscall  *LTOZ)(DWORD realUser,int num1) = (( int(__thiscall  *)(DWORD,int))0x00454CC0);
         return LTOZ(reinterpret_cast<DWORD>(this->realUser),a1);
    }

    void User::AuctionDrawNOBID(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00464480);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::AuctionDrawNOBUY(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x004645F0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::AuctionBuyItem(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x004641A0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::AuctionGetMoney(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00464760);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::AuctionDeleteBadlist()
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((void(__thiscall  *)(DWORD ))0x00464840);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    void User::ChangeMaxHp(int a1, int a2)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2) = ((void(__thiscall  *)(DWORD , int,int))0x00468BB0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2);
    }

    void User::ChangeMaxMP(int a1, int a2)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2) = ((void(__thiscall  *)(DWORD , int,int))0x00468BE0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2);
    }

    void User::ChangeMaxSTM(int a1, int a2)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2) = ((void(__thiscall  *)(DWORD , int,int))0x00468C10);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2);
    }

    void User::ChangeMaxWGT(int a1, int a2)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2) = ((void(__thiscall  *)(DWORD , int,int))0x00468C40);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2);
    }

    void User::OpenHairShop(int a1, int a2, int a3, int a4)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2,int num3, int num4) = ((void(__thiscall  *)(DWORD , int,int, int,int))0x00483BC0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2,a3,a4);
    }

    int User::AddServerEvent(int a1)
    {
        int (__thiscall  *LTOZ)(DWORD realUser,int num1) = (( int(__thiscall  *)(DWORD,int))0x004677F0);
        return LTOZ(reinterpret_cast<DWORD>(this->realUser),a1);
    }

    int User::DelServerEvent(int a1)
    {
        int (__thiscall  *LTOZ)(DWORD realUser,int num1) = (( int(__thiscall  *)(DWORD,int))0x00467830);
        return LTOZ(reinterpret_cast<DWORD>(this->realUser),a1);
    }

    void User::GiveMakeSkill(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x0047BC90);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::OpenSpecialMakeSkill(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00483D40);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::RunMagic(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00456590);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::RunSattack(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x00456A90);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::OpenTrader(int a1, int a2, int a3, int a4, int a5, int a6)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2,int num3, int num4,int num5, int num6) = ((void(__thiscall  *)(DWORD , int,int , int,int, int,int))0x00457760);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2,a3,a4,a5,a6);
    }

    int User::OpenChangeItem()
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((int(__thiscall  *)(DWORD ))0x004573D0);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    int User::CounterStart(int a1, int a2, int a3)
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2,int num3) = ((int(__thiscall  *)(DWORD , int,int , int))0x0045A510);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2,a3);
    }

    signed int User::CounterInit()
    {
        signed int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((signed int(__thiscall  *)(DWORD ))0x0045A540);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    void User::OpenMonsterSelect()
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((void(__thiscall  *)(DWORD ))0x0045A8C0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    signed int User::TimerStart()
    {
        signed int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((signed int(__thiscall  *)(DWORD ))0x0045AD10);
            return    User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    void User::TimerInit()
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((void(__thiscall  *)(DWORD ))0x0045AD30);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    void User::SetEventCount(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x0045ADC0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::OpenClassPointStore(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x0045B8A0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::OpenMonsterZone()
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((void(__thiscall  *)(DWORD ))0x0045A630);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    void User::XmasPointUser()
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((void(__thiscall  *)(DWORD ))0x0045C890);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    void User::XmasPointGuild()
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((void(__thiscall  *)(DWORD ))0x0045C980);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    void User::ChangePKMode(int a1)
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((void(__thiscall  *)(DWORD , int))0x0045CE90);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    void User::GivePosFromPosItem()
    {
        void (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((void(__thiscall  *)(DWORD ))0x0045D3B0);
                User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    void User::setRain(int mode)
    {
        if(mode < 0){
            if (*(DWORD *)0x509E44)
            {
              *(DWORD *)0x509E44 = 0;
              *(DWORD *)0x509E4C = 0;
            }
            else
            {
            *(DWORD *)0x509E44 = 1;
            *(DWORD *)0x509E4C = 1;
            }
        }
        else{
            *(DWORD *)0x509E44 = mode;
            *(DWORD *)0x509E4C = mode;
        }

           time_t Time[2];

            Time[0] = 0;

            DWORD offset = 0;

            int val = (*(DWORD*)0x509E48) - 6;
            int num = abs(val);

            DWORD *uP = reinterpret_cast<DWORD*>(this->realUser);
            bool v32;
            int v33;

			DWORD* dontcrashbro = (DWORD*)0x509EDC;

			
			SetByte((BYTE *)uP + 0x48B8, 0x29u, (DWORD *)Time);// &offset);
            SetShort((BYTE *)uP + 0x122E, *(DWORD *)0x509ED0, (DWORD *)Time); //&offset);
            SetShort((BYTE*)uP + 0x122E, *(DWORD *)0x509ED4, (DWORD *)Time);// &offset);
            SetShort((BYTE*)uP + 0x122E, *(DWORD *)0x509ED8, (DWORD *)Time); //&offset);
            SetShort((BYTE*)uP + 0x122E, *dontcrashbro,  (DWORD *)Time);//&offset);
            SetShort((BYTE*)uP + 0x122E, *(DWORD *)0x509EE0,  (DWORD *)Time);//&offset);
            SetByte((BYTE *)uP + 0x48B8, *(DWORD *)0x509E4C, (DWORD *)Time);// &offset);
            SetByte((BYTE *)uP + 0x48B8, val, (DWORD *)Time);//  &offset);
			
            if ( *dontcrashbro < 3 )
            {
              v32 = *dontcrashbro == 21;
            }
            else
            {
              v32 = *dontcrashbro == 21;
              if ( *dontcrashbro < 21 )
              {
                SetByte((BYTE *)uP + 0x48B8, 4u,  (DWORD *)Time);// &offset);
                v33 = this->getRainVal();
                if ( v33 > 0 )
                  SetInt((BYTE*)uP + 0x122E, v33 / 600 + 1, (DWORD *)Time);//  &offset);
                else
                  SetInt((BYTE*)uP + 0x122E, v33, (DWORD *)Time);//  &offset);
                this->SendAll(Time[0], (void*)(uP + 0x122E));
              }
            } 
            if ( v32 )
            {
              SetByte((BYTE *)uP + 0x48B8, 1u,  (DWORD *)Time);// &offset);
            }
            else if ( *(DWORD *)0x509EDC == 2 )
            {
              SetByte((BYTE *)uP + 0x48B8, 3u,  (DWORD *)Time);// &offset);
            }
            else
            {
              SetByte((BYTE *)uP + 0x48B8, 2u, (DWORD *)Time);//  &offset);
            }
			v33 = this->getRainVal();
            if ( v33 > 0 )
              SetInt((BYTE*)uP + 0x122E, v33 / 600 + 1,  (DWORD *)Time);// &offset);
            else
              SetInt((BYTE*)uP + 0x122E, v33,  (DWORD *)Time);// &offset);
            this->SendAll(Time[0], (void*)(uP + 0x122E));
    }

    int User::ExistItem(int a1, int a2)
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2) = ((int(__thiscall  *)(DWORD , int,int ))0x00450AE0);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2);
    }

    int User::AbsentItem(int a1)
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((int(__thiscall  *)(DWORD , int ))0x00450AB0);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    int User::ExistItemType(int a1, int a2)
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2) = ((int(__thiscall  *)(DWORD , int,int ))0x00450B60);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2);
    }

    int User::AbsentItemType(int a1)
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((int(__thiscall  *)(DWORD , int ))0x00450B30);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    int User::FindMagic(int a1)
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((int(__thiscall  *)(DWORD , int ))0x00450BB0);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    int User::CheckTime(int a1, int a2)
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2) = ((int(__thiscall  *)(DWORD, int,int ))0x00450C80);
                return   User__MessageNONE_wrapper(reinterpret_cast<DWORD>(this->realUser), a1, a2);
    }

    int User::RNGRand(int a1)
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((int(__thiscall  *)(DWORD,int ))0x00450E50);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    signed int User::CheckGold(int a1, int a2)
    {
      signed  int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2) = ((signed int(__thiscall  *)(DWORD , int,int ))0x00468560);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2);
    }

    int User::CheckGameDay(int a1, int a2, int a3)
    {
        int (__thiscall  *User__checkgametime_wrapper)(DWORD userPointer, int month,int startday, int endday) = ((int(__thiscall  *)(DWORD, int, int,int))0x00450D90);
        return User__checkgametime_wrapper(reinterpret_cast<DWORD>(this->realUser), a1, a2,  a3);
    }

    bool User::CheckGameMonth(int a1, int a2)
    {
        bool (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2) = ((bool(__thiscall  *)( DWORD,int,int ))0x00450E00);
                return   User__MessageNONE_wrapper(reinterpret_cast<DWORD>(this->realUser),  a1,a2);
    }

    int User::HowMuchItem(int a1, int a2, int a3)
    {//USER::CheckItemNum(int,int,int)
        int (__thiscall  *User__CheckItemNum)(DWORD userPointer, int month,int startday, int endday) = ((int(__thiscall  *)(DWORD userPointer, int, int,int))0x00450A50);
        return User__CheckItemNum( reinterpret_cast<DWORD>(this->realUser), a1, a2,  a3);
    }

    int User::Moral(int a1, int a2)
    { //  int __thiscall USER::CheckMoral(int,int) 
        int (__thiscall  *User__CheckMoral)(DWORD userPointer, int num1,int num2) = ((int(__thiscall  *)(DWORD userPointer, int, int))0x00468FA0);
        return User__CheckMoral( reinterpret_cast<DWORD>(this->realUser), a1, a2);
    }

    int User::CheckMageType(int a1, int a2)
    { // int __thiscall USER::CheckMageType(int,int)
        int (__thiscall  *User__CheckMageType)(DWORD userPointer, int num1,int num2) = ((int(__thiscall  *)(DWORD userPointer, int, int))0x004691A0);
        return User__CheckMageType( reinterpret_cast<DWORD>(this->realUser), a1, a2);
    }

    const char *User::CheckWeight(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11)
    {
        const char * (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2,int num3, int num4,int num5, int num6, int num7, int num8, int num9, int num10, int num11) = ((const char *(__thiscall  *)(DWORD , int,int , int,int, int,int, int,int, int,int,int))0x004691E0);
                return  User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);
    }

    signed int User::CheckRank(int a1)
    {
        signed  int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((signed int(__thiscall  *)(DWORD , int ))0x0046A490);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    signed int User::CheckItemSlot(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11)
    {
        signed int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2,int num3, int num4,int num5, int num6, int num7, int num8, int num9, int num10, int num11) = ((signed int(__thiscall  *)(DWORD , int,int , int,int, int,int, int,int, int,int,int))0x0046A4F0);
                return  User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);
    }

    signed int User::CheckPosition(int a1, int a2, int a3, int a4, int a5)
    {
        signed int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2,int num3, int num4,int num5) = ((signed int(__thiscall  *)(DWORD , int,int , int,int, int))0x00477C30);
                return  User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2,a3,a4,a5);
    }

    signed int User::CheckFirstClick()
    {
        signed int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((signed int(__thiscall  *)(DWORD ))0x00482080);
                return  User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    signed int User::CheckStorageType(int a1)
    {
        signed  int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((signed int(__thiscall  *)(DWORD , int ))0x00454B70);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    bool User::CheckAuctionBadList(int *a1)
    {
        bool (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int*) = ((bool(__thiscall  *)(DWORD , int* ))0x00464950);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    bool User::CheckAuctionState(int a1)
    {
        bool (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int) = ((bool(__thiscall  *)(DWORD , int ))0x00464930);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    int User::FindSpecialAttack(int a1)
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((int(__thiscall  *)(DWORD , int ))0x0047BEB0);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    int User::MageType(int a1)
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((int(__thiscall  *)(DWORD , int ))0x00450BF0);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    bool User::CheckAliveNpc(int a1 ,int a2)
    {
        bool (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1, int num2) = ((bool(__thiscall  *)(DWORD, int,int ))0x00481FB0);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser),a1,a2);
    }

    int User::FindMakeSkill(int a1)
    {
        int (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int num1) = ((int(__thiscall  *)(DWORD , int ))0x00450C40);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    bool User::CheckGuildRank(int a1)
    {
        bool (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int) = ((bool(__thiscall  *)(DWORD , int ))0x00481F90);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    signed int User::CompareBasicValue(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
    {
        signed int (__thiscall  *User__MessageNONE_wrapper)( DWORD userPointer,int num1, int num2,int num3, int num4,int num5, int num6, int num7) = ((signed int(__thiscall  *)(DWORD ,int,int , int,int, int,int, int))0x004572D0);
                return  User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1,a2,a3,a4,a5,a6,a7);
    }

    bool User::CheckMyJob(int a1)
    {
        bool (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int) = ((bool(__thiscall  *)(DWORD , int ))0x00456E80);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    signed int User::CheckGuildTownLevel(int a1, int a2)
    {
        signed int (__thiscall  *User__MessageNONE_wrapper)( DWORD userPointer,int num1, int num2) = ((signed int(__thiscall  *)( DWORD,int,int ))0x00481F30);
                return   User__MessageNONE_wrapper(reinterpret_cast<DWORD>(this->realUser), a1,a2);
    }

    signed int User::CheckCounter(int a1, int a2)
    {
        signed int (__thiscall  *User__checkgametime_wrapper)(DWORD userPointer, int num1,int num2) = ((signed int(__thiscall  *)(DWORD userPointer, int, int))0x0045A560);
        return User__checkgametime_wrapper( reinterpret_cast<DWORD>(this->realUser), a1, a2);
    }

    signed int User::CheckTimer(int a1, int a2)
    {
        signed int (__thiscall  *User__checkgametime_wrapper)(DWORD userPointer, int num1,int num2) = ((signed int(__thiscall  *)(DWORD userPointer, int, int))0x0045AD40);
        return User__checkgametime_wrapper( reinterpret_cast<DWORD>(this->realUser), a1, a2);
    }

    signed int User::CheckEventCount(int a1, int a2)
    {
        signed int (__thiscall  *User__checkgametime_wrapper)(DWORD userPointer, int num1,int num2) = ((signed int(__thiscall  *)(DWORD userPointer, int, int))0x0045ADF0);
        return User__checkgametime_wrapper( reinterpret_cast<DWORD>(this->realUser), a1, a2);
    }

    signed int User::CheckPayType(int a1)
    {
        signed int (__thiscall  *User__checkgametime_wrapper)(DWORD userPointer, int num1) = ((signed int(__thiscall  *)(DWORD userPointer, int))0x0045C250);
        return User__checkgametime_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    bool User::CheckClassTown()
    {
        bool (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((bool(__thiscall  *)(DWORD  ))0x0045C2C0);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    bool User::CheckClassTownWar()
    {
        bool (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer) = ((bool(__thiscall  *)(DWORD ) )0x0045C310);
        return   User__MessageNONE_wrapper(reinterpret_cast<DWORD>(this->realUser) );
    }

    signed int User::CheckHaveEventBook()
    {
        signed int (__thiscall  *User__checkgametime_wrapper)(DWORD userPointer) = ((signed int(__thiscall  *)(DWORD userPointer))0x0045C3F0);
        return User__checkgametime_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    signed int User::CheckEventBook()
    {
        signed int (__thiscall  *User__checkgametime_wrapper)(DWORD userPointer) = ((signed int(__thiscall  *)(DWORD userPointer))0x0045C4E0);
        return User__checkgametime_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    bool User::CheckPkMode(int a1)
    {
        bool (__thiscall  *User__MessageNONE_wrapper)(DWORD userPointer, int) = ((bool(__thiscall  *)(DWORD , int ))0x0045CE60);
                return   User__MessageNONE_wrapper( reinterpret_cast<DWORD>(this->realUser), a1);
    }

    int User::CheckPayAccount()
    {
         int (__thiscall  *User__checkgametime_wrapper)(DWORD userPointer) = (( int(__thiscall  *)(DWORD userPointer))0x0048C810);
         return User__checkgametime_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

    int User::PayAccount()
    {
        int (__thiscall  *User__checkgametime_wrapper)(DWORD userPointer) = (( int(__thiscall  *)(DWORD userPointer))0x0048C930);
        return User__checkgametime_wrapper( reinterpret_cast<DWORD>(this->realUser));
    }

#pragma endregion

    int User::getNpcChatByID(int id)
    {
		if(id == -1)
			return 0;

         int (__thiscall  *NpcChatByID)(DWORD userPointer, int a) = (( int(__thiscall  *)(DWORD, int ))0x00466DA0);
        return NpcChatByID(reinterpret_cast<DWORD>(this->realUser), id);
    }

int User::Selectmsg(int intro, int msg1, int opt1evt, int msg2, int opt2evt, int msg3, int opt3evt, int msg4, int opt4evt)
{

int up = (int)this->realUser; //user pointer
  int result = 0;    // return value
  const char * strintro;
  const char * strmsg1;
  const char * strmsg2;
  const char * strmsg3;
  const char * strmsg4;
  unsigned int a2; //EXEC struct
  unsigned int introlenght;
  unsigned int msg1lenght;
    unsigned int msg2lenght;
	  unsigned int msg3lenght;
	    unsigned int msg4lenght;
  /*
    a2 =0;
  *(DWORD *)(&a2 + 8) = (DWORD)&intro;
  *(DWORD *)(&a2 + 0xC) = (DWORD)&msg1;
      *(DWORD *)(&a2 + 0x10) = evt1;
	  *(DWORD *)(&a2 + 0x14) = (DWORD)&msg2;
      *(DWORD *)(&a2 + 0x18) = evt2;
	  *(DWORD *)(&a2 + 0x1C) = (DWORD)&msg3;
      *(DWORD *)(&a2 + 0x20) = evt3;
	  *(DWORD *)(&a2 + 0x24) = (DWORD)&msg4;
      *(DWORD *)(&a2 + 0x28) = evt4;
*/

if( msg1 != -1 && msg2 != -1){ // only display if there are 2 option messages

	// Handel Intro message
	strintro = (const char*) this->getNpcChatByID(intro);
	a2 =0;
	SetByte((BYTE *)(up + 0x48B8), 0x92u, (DWORD *)&a2);
	if(strintro){
		introlenght = strlen(strintro) +1;
		SetShort((BYTE *)(up + 0x48B8), introlenght , (DWORD *)&a2);
        SetString((BYTE*)((BYTE*)up + 0x48B8), strintro, introlenght , (int*)&a2);
	}
	else{
        SetShort((BYTE *)(up + 0x48B8), 0, (DWORD *)&a2);
	}
	// Handel First option's Message
	strmsg1 = (const char*) this->getNpcChatByID(msg1);
	if(strmsg1){
		msg1lenght = strlen(strmsg1) +1;
        SetShort((BYTE *)(up + 0x48B8), msg1lenght , (DWORD *)&a2);
        SetString((BYTE*)((BYTE*)up + 0x48B8), strmsg1, msg1lenght , (int*)&a2);
	}
	else{
	    SetShort((BYTE *)(up + 0x48B8), 0, (DWORD *)&a2);
	}
	// Handel second option's Message
	strmsg2 = (const char*) this->getNpcChatByID(msg2);
	if(strmsg2){
		msg2lenght = strlen(strmsg2) +1;
        SetShort((BYTE *)(up + 0x48B8), msg2lenght , (DWORD *)&a2);
        SetString((BYTE*)((BYTE*)up + 0x48B8), strmsg2, msg2lenght , (int*)&a2);
	}
	else{
	    SetShort((BYTE *)(up + 0x48B8), 0, (DWORD *)&a2);
	}
	// Handel third option's Message
	strmsg3 = (const char*) this->getNpcChatByID(msg3);
	if(strmsg3){
		msg3lenght = strlen(strmsg3) +1;
        SetShort((BYTE *)(up + 0x48B8), msg3lenght , (DWORD *)&a2);
        SetString((BYTE*)((BYTE*)up + 0x48B8), strmsg3, msg3lenght , (int*)&a2);
	}
	else{
	    SetShort((BYTE *)(up + 0x48B8), 0, (DWORD *)&a2);
	}
	// Handel fouth option's Message
	strmsg4 = (const char*) this->getNpcChatByID(msg4);
	if(strmsg4){
		msg4lenght = strlen(strmsg4) +1;
        SetShort((BYTE *)(up + 0x48B8), msg4lenght , (DWORD *)&a2);
        SetString((BYTE*)((BYTE*)up + 0x48B8), strmsg4, msg4lenght , (int*)&a2);
	}
	else{
	    SetShort((BYTE *)(up + 0x48B8), 0, (DWORD *)&a2);
	}
	Send( a2, (byte *)(up + 0x48B8), 1);
    *(DWORD *)(up + 0x7710) = opt1evt; //*(DWORD *)(v5 + 0x10);
    *(DWORD *)(up + 0x7714) = opt2evt; //result;
    *(DWORD *)(up + 0x7718) = opt3evt; //*(DWORD *)(v5 + 0x20);
    *(DWORD *)(up + 0x771C) = opt4evt; //*(DWORD *)(v5 + 0x28);

	result = (int)strmsg1;
}
 
return result;

}

int User::Selectmsg(const char * intro,const char * msg1,const char * msg2,const char * msg3,const char * msg4,int evt1,int evt2,int evt3,int evt4)
{
  int result; // eax@1
  int v3; // ecx@1
  int up; // ebx@1
  //unsigned int v5; // ebp@1
  unsigned int a2; // wtf
  const char *v6; // edi@3
  unsigned int v7; // kr00_4@4
  const char *v8; // eax@6
  unsigned int v9; // kr04_4@7
  const char *v10; // eax@9
  unsigned int v11; // kr08_4@10
  const char *v12; // eax@12
  unsigned int v13; // kr0C_4@13
  const char *v14; // eax@15
  unsigned int v15; // kr10_4@16
  const void *v16; // [sp+Ch] [bp-14h]@3
  const void *v17; // [sp+Ch] [bp-14h]@6
  const void *v18; // [sp+Ch] [bp-14h]@9
  const void *v19; // [sp+Ch] [bp-14h]@12
  const void *v20; // [sp+Ch] [bp-14h]@15
 // int v21; // [sp+10h] [bp-10h]@1
 // int v22; // [sp+14h] [bp-Ch]@1
 // int v23; // [sp+18h] [bp-8h]@1
 // int v24; // [sp+1Ch] [bp-4h]@1

 // v5 = 0;
  a2 =0;
  *(DWORD *)(&a2 + 8) = (DWORD)&intro;
  *(DWORD *)(&a2 + 0xC) = (DWORD)&msg1;
      *(DWORD *)(&a2 + 0x10) = evt1;
	  *(DWORD *)(&a2 + 0x14) = (DWORD)&msg2;
      *(DWORD *)(&a2 + 0x18) = evt2;
	  *(DWORD *)(&a2 + 0x1C) = (DWORD)&msg3;
      *(DWORD *)(&a2 + 0x20) = evt3;
	  *(DWORD *)(&a2 + 0x24) = (DWORD)&msg4;
      *(DWORD *)(&a2 + 0x28) = evt4;
    

  up = (int)this->realUser;
 // result = intro;//*(DWORD *)(a2 + 0xC);
 // v3 = *(DWORD *)(a2 + 8);
 // v23 = *(DWORD *)(a2 + 0x1C);
  //v21 = result;
  //v22 = *(DWORD *)(a2 + 0x14);
  //v24 = *(DWORD *)(a2 + 0x24);
 if ( msg1 )
  {
    if ( intro )
    {
      a2 = 0;
      v6 = intro;
      v16 = v6;
      SetByte((BYTE *)(up + 0x48B8), 0x92u, (DWORD *)&a2);
      if ( v6 )
      {
        v7 = strlen(v6);
        SetShort((BYTE *)(up + 0x48B8), v7 , (DWORD *)&a2);
        SetString((BYTE*)((BYTE*)up + 0x48B8), v16, v7 , (int*)&a2);
      }
      else
      {
        SetShort((BYTE *)(up + 0x48B8), 0, (DWORD *)&a2);
      }
      v8 = msg1;
      v17 = v8;
      if ( v8 )
      {
        v9 = strlen(v8);
        SetShort((BYTE *)(up + 0x48B8), v9 , (DWORD *)&a2);
        SetString((BYTE*)((BYTE*)up + 0x48B8), v17, v9 , (int*)&a2);
      }
      else
      {
        SetShort((BYTE *)(up + 0x48B8), 0, (DWORD *)&a2);
      }
      v10 = msg2;//(const char *)sub_466DA0(v22);
      v18 = v10;
      if ( v10 )
      {
        v11 = strlen(v10);
        SetShort((BYTE *)(up + 0x48B8), v11 , (DWORD *)&a2);
        SetString((BYTE*)((BYTE*)up + 0x48B8), v18, v11 , (int*)&a2);
      }
      else
      {
        SetShort((BYTE *)(up + 0x48B8), 0, (DWORD *)&a2);
      }
      v12 = msg3;//(const char *)sub_466DA0(v23);
      v19 = v12;
      if ( v12 )
      {
        v13 = strlen(v12);
        SetShort((BYTE *)(up + 0x48B8), v13 , (DWORD *)&a2);
        SetString((BYTE*)((BYTE*)up + 0x48B8), v19, v13 , (int*)&a2);
      }
      else
      {
        SetShort((BYTE *)(up + 0x48B8), 0, (DWORD *)&a2);
      }
      v14 = msg4; //(const char *)sub_466DA0(v24);
      v20 = v14;
      if ( v14 )
      {
        v15 = strlen(v14);
        SetShort((BYTE *)up + 0x48B8, v15 , (DWORD *)&a2);
        SetString((BYTE*)((BYTE*)up + 0x48B8), v20, v15 , (int*)&a2);
      }
      else
      {
        SetShort((BYTE *)(up + 0x48B8), 0, (DWORD *)&a2);
      }
      Send( a2, (byte *)(up + 0x48B8), 1);
      *(DWORD *)(up + 0x7710) = evt1; //*(DWORD *)(v5 + 0x10);
      *(DWORD *)(up + 0x7714) = evt2; //result;
      *(DWORD *)(up + 0x7718) = evt3; //*(DWORD *)(v5 + 0x20);
      *(DWORD *)(up + 0x771C) = evt4; //*(DWORD *)(v5 + 0x28);
    }
  }
  return result;
}

signed int User::FindEvent(int eventnum)
{
//returns 0 if not found, 1 if found
signed int (__thiscall  *FindEvent)(DWORD realUser,int a2) = ((signed int(__thiscall  *)(DWORD,int ))0x468520);
return FindEvent(reinterpret_cast<DWORD>(this->realUser),eventnum);
}


void User::DisplayErrorMsg(void* a1)
{
    void(__thiscall * _DisplayErrorMsg)(DWORD realUser, void* a1) = ((void(__thiscall*)(DWORD, void*))0x42d840);

    _DisplayErrorMsg(reinterpret_cast<DWORD>(this->realUser), a1);
}

void User::WarpGate(DWORD zone, int x, int y){

void (__thiscall  *User__warpgate_wrapper)(DWORD userPointer,DWORD zone, int x, int y) = ((void(__thiscall  *)(DWORD userPointer, DWORD, int, int))0x00482B80);
User__warpgate_wrapper( reinterpret_cast<DWORD>(this->realUser), zone, x, y);

}


int User::UpdateMemUserAll()
{
    int(__thiscall * _UpdateMemUserAll)(DWORD realUser) = ((int(__thiscall*)(DWORD))0x458e40);

    return _UpdateMemUserAll(reinterpret_cast<DWORD>(this->realUser));
}

/*int User::UpdateMemItemAll()
{
    int(__thiscall * _UpdateMemItemAll)(DWORD realUser) = ((int(__thiscall*)(DWORD))0x4594a0);

   return _UpdateMemItemAll(reinterpret_cast<DWORD>(this->realUser));
}*/

/*int User::UpdateMemItemIndex(int nSlot)
{
    int(__thiscall * _UpdateMemItemIndex)(DWORD realUser, int nSlot) = ((int(__thiscall*)(DWORD, int))0x459740);

    return _UpdateMemItemIndex(reinterpret_cast<DWORD>(this->realUser), nSlot);
}*/

int User::CheckGameTime(int month,int day, int starthour, int endhour){

    int(__thiscall  *User__checkgametime_wrapper)(DWORD userPointer, int month,int day, int starthour, int endhour) = ((int(__thiscall  *)(DWORD,  int, int,int,int))0x00450d00);
return User__checkgametime_wrapper(reinterpret_cast<DWORD>(this->realUser), month, day,  starthour,  endhour);

}

void User::SendStoreOpen(int shopid,signed int sellrate,signed int buyrate,int townnum){
void (__thiscall  *SendStoreOpen)(DWORD realUser,int a2,signed int a3,signed int a4,int a5) = ((void(__thiscall  *)(DWORD,int,signed int,signed int,int ))0x44d290);
SendStoreOpen(reinterpret_cast<DWORD>(this->realUser),shopid,sellrate,buyrate,townnum);}

void User::OpenGuildTownTaxRate(int guildnum){
void (__thiscall  *OpenGuildTownTaxRate)(DWORD realUser,int a2) = ((void(__thiscall  *)(DWORD,int ))0x488AF0);
OpenGuildTownTaxRate(reinterpret_cast<DWORD>(this->realUser),guildnum);}

void User::SendAllMessage(const char* txt){
void (__thiscall  *SendAllMessage)(DWORD realUser,const char* txt) = ((void(__thiscall  *)(DWORD,const char* ))0x48b0c0);
SendAllMessage(reinterpret_cast<DWORD>(this->realUser),txt);}

bool User::CheckInvSlot(){

	DWORD sOffset = getInventoryItemData()+40;
	DWORD count=0;
	int var;
	while(true){
	
	    if(count>39)
		   break;
		
		if(*(DWORD*)(sOffset + (count * 4)) == 0){
			//printf("found %d\n",count);
			return true;
		}
		// printf("Index: %d 0x%X \n",count,*(DWORD*)(sOffset + (count * 4)));
		count++;
	}
	//printf("not found %d\n",count);
	return false;
}

bool User::GiveItem(int sNum,int sAmmount){
	
	DWORD uP = reinterpret_cast<DWORD>(this->realUser);
    DWORD iP;
	Item item;
	iP = item.NewItem(uP);
	item.CopyTableItem((void *)iP, sNum);
	
	//printf("inv 0x%X\n",getInventoryItemData());
	//printf("CurrentWeight: %d ItemWeight: %d MaxWeight: %d\n",getCurrentWeight(),item.getsWgt(iP),getMaxWgt());
	if (getCurrentWeight() + item.getsWgt(iP) > getMaxWgt()){
        sendChatMessage("<<< You can't give that item : It will exceed the bagweight limit. >>>");
        return false;
    }

	if(!CheckInvSlot()){
         sendChatMessage("<<< You have no more space in your inventory >>>");
         return false;
	}
  
	void (__thiscall  *GiveItem)(DWORD realUser,int sNum,int sAmmount) = ((void(__thiscall  *)(DWORD,int,int))0x00467190);
	GiveItem(reinterpret_cast<DWORD>(this->realUser),sNum,sAmmount);
	char strMsg[50];

	this->ShowMagic(300,0);
	sprintf(strMsg,"<<< You have received: %s >>>",item.getstrName(iP));
	sendChatMessage(strMsg);
	return true;
}

bool User::LoadSavedItemTable(){
	CGOdbcConnect cCon; 

	try{
	
         cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);
    }
    catch(CGOdbcEx *pE){
        printf("connection error\n%s\n", pE->getMsg());
        return false;
    }
	
	CGOdbcStmt *pCur;

    pCur = cCon.createStatement();

	char szQuery[300];
	

	sprintf(szQuery, "select * from saveitem where iindex = %d",this->dbindex);


    try{
		pCur->execute(szQuery);
    }
    catch(...)
    {
		printf("Query error\n");
        return false;
    }
	
	try{
		 if (!pCur->bindAuto()){
	         printf("cursor doesn't contain resultset\n");
			 return false;
		 }
	   }
	   catch(CGOdbcEx *pE){
			printf("binding error\n%s\n", pE->getMsg());
			return false;
	   }

        bool bRC;

		   try{
			   	for (bRC = pCur->first(); bRC; bRC = pCur->next()){}
					
			//	this->tblsNum = new int[pCur->getRowCount()];


				this->sRowCount = pCur->getRowCount();

				int count=0;
				for (bRC = pCur->first(); bRC; bRC = pCur->next())
				{
					//this->tblsNum[count]= pCur->getInt("itemnum");

					uitems.insert(uitems.begin(),pCur->getInt("itemnum"));

					count++;
				}

		    }
		    catch(CGOdbcEx *pE){
				cCon.freeStatement(pCur);
                printf("load cursor error\n%s\n", pE->getMsg());
				return false;
	       }
		   
	sprintf(szQuery, "DELETE from saveitem where iindex =%d",this->dbindex);

	cCon.freeStatement(pCur);
    pCur = cCon.createStatement();

    try{
		pCur->execute(szQuery);
    }
    catch(...)
    {
		printf("Query error\n");
        return false;
    }

	


	cCon.freeStatement(pCur);
    cCon.commit();
    cCon.setTransMode(true);
    cCon.close();
	return true;
	
}


bool User::StoreSavedItemTable(){
	CGOdbcConnect cCon; 

	try{
		 cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);
    }
    catch(CGOdbcEx *pE){
        printf("connection error\n%s\n", pE->getMsg());
        return false;
    }
	
	CGOdbcStmt *pCur;

    pCur = cCon.createStatement();

	char szQuery[300];
	

	//sprintf(szQuery, "select * from saveitem where iindex =%d",this->dbindex);
				std::vector<int>::iterator i;
			int j = 0;
	 for ( i =uitems.begin(); i<uitems.end(); i++){
		// for(int v=0;v<sRowCount;v++){

		sprintf(szQuery, "Insert into saveitem (iindex,itemnum) values ('%d','%d')",this->dbindex,uitems[j]);

			  try{
		pCur->execute(szQuery);
    }
    catch(...)
    {
		printf("Query error\n");
        return false;
    }
	uitems.erase(uitems.begin()+j);

		cCon.freeStatement(pCur);

		pCur = cCon.createStatement();

		j++;

	 }

   


	cCon.freeStatement(pCur);
    cCon.commit();
    cCon.setTransMode(true);
    cCon.close();
	return true;
}

void User::checkitemwaitlist(){
	
			std::vector<int>::iterator i;
		int j = 0;
	 for ( i =uitems.begin(); i<uitems.end(); i++){ // give waiting reward
		 if(this->GiveItem(uitems[j],1)){
		 // item successfully delivered, remove from waiting list
			uitems.erase(uitems.begin()+j); //deletes the ith element
		 }
		 else{
			 // item not delivered inventory/bag full so break
			 break;}
	j++;
	 } 

}


// Getters

DWORD User::GetPlusDex()
{
	DWORD(__thiscall * GetPlusDex)(DWORD realUser) = ((DWORD(__thiscall*)(DWORD))0x46a0c0);

	return GetPlusDex(reinterpret_cast<DWORD>(this->realUser));
}

void* User::GetNpcNID(int npcid)
{
	void*(__thiscall * User_GetNpcNID)(DWORD realUser, int npcid) = ((void*(__thiscall*)(DWORD, int))0x447E30);

	return User_GetNpcNID(reinterpret_cast<DWORD>(this->realUser), npcid);
}


// status

void User::PlusStr(int a1)
{
    void(__thiscall * User_PlusStr)(DWORD realUser, int a1) = ((void(__thiscall*)(DWORD, int))0x476710);

	User_PlusStr(reinterpret_cast<DWORD>(this->realUser), a1);
}

void User::PlusDex(int a1)
{
    void(__thiscall * User_PlusDex)(DWORD realUser, int a1) = ((void(__thiscall*)(DWORD, int))0x476820);

	User_PlusDex(reinterpret_cast<DWORD>(this->realUser), a1);
}

void User::PlusIntel(int a1)
{
    void(__thiscall * User_PlusIntel)(DWORD realUser, int a1) = ((void(__thiscall*)(DWORD, int))0x476930);

	User_PlusIntel(reinterpret_cast<DWORD>(this->realUser), a1);
}

void User::PlusCon(int a1)
{
    void(__thiscall * User_PlusCon)(DWORD realUser, int a1) = ((void(__thiscall*)(DWORD, int))0x476B50);

	User_PlusCon(reinterpret_cast<DWORD>(this->realUser), a1);
}

void User::PlusWis(int a1)
{
    void(__thiscall * User_PlusWis)(DWORD realUser, int a1) = ((void(__thiscall*)(DWORD, int))0x476C60);

	User_PlusWis(reinterpret_cast<DWORD>(this->realUser), a1);
}


// item


void User::SendItemInfoChange(unsigned char bBelt, int itemSlot, unsigned char bFlag)
{
	void(__thiscall * User_SendItemInfoChange)(DWORD realUser, unsigned char bBelt, int itemSlot, unsigned char bFlag) = ((void(__thiscall*)(DWORD, unsigned char, int, unsigned char))0x4423c0);

	User_SendItemInfoChange(reinterpret_cast<DWORD>(this->realUser), bBelt, itemSlot, bFlag);
}

// USER.obj

int User::GetItemClass(int sNum)
{
	int(__thiscall * GetItemClass)(DWORD realUser, int sNum) = ((int(__thiscall*)(DWORD, int))0x45c2a0);

	return GetItemClass(reinterpret_cast<DWORD>(this->realUser), sNum);
}

int User::PushItemInventory(void* itemPtr)
{
    int(__thiscall * _PushItemInventory)(DWORD realUser, void* itemPtr) = ((int(__thiscall*)(DWORD, void*))0x43fb60);

    return _PushItemInventory(reinterpret_cast<DWORD>(this->realUser), itemPtr);
}

int User::RecalcWgt()
{
    int(__thiscall * _RecalcWgt)(DWORD realUser) = ((int(__thiscall*)(DWORD))0x4520d0);

    return _RecalcWgt(reinterpret_cast<DWORD>(this->realUser));
}

int User::UpdateItemIndex(int itemSlot)
{
	int(__thiscall * UpdateItemIndex)(DWORD realUser, int itemSlot) = ((int(__thiscall*)(DWORD, int))0x447e60);

	return UpdateItemIndex(reinterpret_cast<DWORD>(this->realUser), itemSlot);
}

void  User::Item_WriteItemLog(DWORD itemPtr, int a3, char* a4)
{
	void(__thiscall * Item_WriteItemLog)(DWORD realUser, DWORD itemPtr, int a3, char* a4) = ((void(__thiscall*)(DWORD, DWORD, int, char*))0x459b90);

	Item_WriteItemLog(reinterpret_cast<DWORD>(this->realUser), itemPtr, a3, a4);
}

// USER_NEW.OBJ


void User::deleteItem(DWORD itemPtr)
{
	void(__thiscall * deleteItem)(DWORD realUser, DWORD itemPtr) = ((void(__thiscall*)(DWORD, DWORD))0x483a80);

	deleteItem(reinterpret_cast<DWORD>(this->realUser), itemPtr);
}

void User::SendDeleteItem(unsigned char unk, int slot)
{
	void(__thiscall * SendDeleteItem)(DWORD realUser, unsigned char unk, int slot) = ((void(__thiscall*)(DWORD, unsigned char, int))0x4664e0);

	SendDeleteItem(reinterpret_cast<DWORD>(this->realUser), unk, slot);
}


void User::Item_PlusItemDur(DWORD invItemPtr, int a1)
{
	void(__thiscall * Item_PlusItemDur)(DWORD realUser, DWORD invItemPtr, int a1) = ((void(__thiscall*)(DWORD, DWORD, int))0x45f470);

	Item_PlusItemDur(reinterpret_cast<DWORD>(this->realUser), invItemPtr, a1);
}

int User::GetMyMaxMakeExp(int a1)
{
	int(__thiscall * GetMyMaxMakeExp)(DWORD realUser, int a1) = ((int(__thiscall*)(DWORD, int))0x4840a0);

	return GetMyMaxMakeExp(reinterpret_cast<DWORD>(this->realUser), a1);
}

int User::CheckSuccessSpecialMakeSkill(int a1, int a2)
{
	int(__thiscall * CheckSuccessSpecialMakeSkill)(DWORD realUser, int a1, int a2) = ((int(__thiscall*)(DWORD, int, int))0x483f00);

	return CheckSuccessSpecialMakeSkill(reinterpret_cast<DWORD>(this->realUser), a1,  a2);
}


// etc


DWORD User::PlusFromItem(DWORD a1)
{
	DWORD(__thiscall * PlusFromItem)(DWORD realUser, DWORD a1) = ((DWORD(__thiscall*)(DWORD, DWORD))0x477ce0);

	return PlusFromItem(reinterpret_cast<DWORD>(this->realUser), a1);
}

void User::SendCharData(unsigned char bValue, unsigned char unk)
{
	void(__thiscall * User_SendCharData)(DWORD realUser, unsigned char bValue, unsigned char unk) = ((void(__thiscall*)(DWORD, unsigned char, unsigned char))0x42E4E0);

	User_SendCharData(reinterpret_cast<DWORD>(this->realUser), bValue, unk);
}


void User::SendDevMessage(const char* a1)
{
	void(__thiscall * SendDevMessage)(DWORD realUser, const char* a1) = ((void(__thiscall*)(DWORD, const char*))0x48b140);

	SendDevMessage(reinterpret_cast<DWORD>(this->realUser), a1);
}


int User::CheckGuildTownWar(int a1)
{
        signed int(__thiscall * _CheckGuildTownWar)(DWORD realUser, int a1) = ((signed int(__thiscall*)(DWORD, int))0x481f10);

        return _CheckGuildTownWar(reinterpret_cast<DWORD>(this->realUser), a1);
}
