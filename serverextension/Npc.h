#pragma once

#include <Windows.h>


class Npc
{
private:
	BYTE* npcPtr;

public:

	Npc(void* npcPointer);

	//void* (__thiscall* getnpcnid)(DWORD sourcePointer, int) = ((void* (__thiscall*)(DWORD, int))0x00447E30);

	int IsDetecter();

	int IsStone();

	int CheckAIType(int);

	void* getPtr()
	{
		return npcPtr;
	}

	DWORD inline  getMaxExp()
	{
		return *reinterpret_cast<DWORD*>(npcPtr + 0x244);
	}

	DWORD inline  getStr()
	{
		return *reinterpret_cast<DWORD*>(npcPtr + 0x248);
	}

	DWORD inline  getWStr()
	{
		return *reinterpret_cast<DWORD*>(npcPtr + 0x24C);
	}

	DWORD inline  getAStr()
	{
		return *reinterpret_cast<DWORD*>(npcPtr + 0x250);
	}

	DWORD inline  getInt()
	{
		return *reinterpret_cast<DWORD*>(npcPtr + 0x25C);
	}

	DWORD inline  getMaxHP()
	{
		return *reinterpret_cast<DWORD*>(npcPtr + 0x270);
	}

};