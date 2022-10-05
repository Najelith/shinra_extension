#include "stdafx.h"

#include "PE_Hook.h"
#include "Hook.h"
#include "PacketDef.h"
#include "Npc.h"

#include "ServerHookInterface.h"
#include "UserItem.h"
#include "Item.h"


int random_1p1(int a1, int a2)
{
	int(__cdecl * random1p1)(int, int) = ((int(__cdecl*)(int, int))0x407700);

	return random1p1(a1, a2);
}

void* alloc_1p1(int size)
{
	void*(__cdecl * alloc1p1)(int) = ((void*(__cdecl*)(int))0x4A7E29);

	return alloc1p1(size);
}



void SetHooks()
{

	// Disable the disabling of auras when using magic / other aura
	FillWithNop(0x43888B, 16); // MagicArrow
	FillWithNop(0x43A571, 16); // MagicRail
	FillWithNop(0x43C0D3, 16); // MagicCircle
	FillWithNop(0x47D134, 16); // SpecialAttackArrow
	FillWithNop(0x47E169, 16); // SpecialAttackRail
	FillWithNop(0x47FC21, 16); // SpecialAttackCircle
	FillWithNop(0x4818DF, 16); // CheckSuccessSpecialAttack

}



void SetSQL()
{
	*(DWORD*)0x404787 = *(DWORD*)(&cfg->sqlstr);
	*(DWORD*)0x40F97C = *(DWORD*)(&cfg->sqlstr);
	*(DWORD*)0x40F988 = *(DWORD*)(&cfg->sqlstr);
	*(DWORD*)0x40F9CE = *(DWORD*)(&cfg->sqlstr);
	*(DWORD*)0x40F9DA = *(DWORD*)(&cfg->sqlstr);
	*(DWORD*)0x40FAD8 = *(DWORD*)(&cfg->sqlstr);
	*(DWORD*)0x40FAF1 = *(DWORD*)(&cfg->sqlstr);
	*(DWORD*)0x40FC39 = *(DWORD*)(&cfg->sqlstr);
	*(DWORD*)0x40FC45 = *(DWORD*)(&cfg->sqlstr);
	*(DWORD*)0x41B00B = *(DWORD*)(&cfg->sqlstr);

	//00404786 | .  68 30524C00   PUSH OFFSET aOdbcDsnSomaU_0; / Arg1 = ASCII "ODBC;DSN=soma;UID=soma;PWD=soma"
	//0040F97B | .  68 346A4C00 | PUSH OFFSET aOdbcDsnSomaUid; ASCII "ODBC;DSN=soma;UID=soma;PWD=soma"
	//0040F987 | .  68 30524C00 | PUSH OFFSET aOdbcDsnSomaU_0; ASCII "ODBC;DSN=soma;UID=soma;PWD=soma"
	//0040F9CD | .  68 346A4C00 | PUSH OFFSET aOdbcDsnSomaUid; ASCII "ODBC;DSN=soma;UID=soma;PWD=soma"
	//0040F9D9 | .  68 30524C00 | PUSH OFFSET aOdbcDsnSomaU_0; ASCII "ODBC;DSN=soma;UID=soma;PWD=soma"
	//0040FAD7 | .  68 346A4C00   PUSH OFFSET aOdbcDsnSomaUid; ASCII "ODBC;DSN=soma;UID=soma;PWD=soma"
	//0040FAF0 | .  68 30524C00   PUSH OFFSET aOdbcDsnSomaU_0; ASCII "ODBC;DSN=soma;UID=soma;PWD=soma"
	//0040FC38 | .  68 346A4C00   PUSH OFFSET aOdbcDsnSomaUid; ASCII "ODBC;DSN=soma;UID=soma;PWD=soma"
	//0040FC44 | .  68 30524C00   PUSH OFFSET aOdbcDsnSomaU_0; ASCII "ODBC;DSN=soma;UID=soma;PWD=soma"
	//0041B00A | .  68 346A4C00   PUSH OFFSET aOdbcDsnSomaUid; / Format = "ODBC;DSN=soma;UID=soma;PWD=soma"



}