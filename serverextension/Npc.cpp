#include "stdafx.h"
#include "Npc.h"


Npc::Npc(void* npcPointer)
{
	this->npcPtr = (BYTE*)npcPointer;

}

int Npc::IsDetecter()
{
	//415670	public: int __thiscall CNpc::IsDetecter(void)
//bool __thiscall Npc_IsDetecter_GUARD(DWORD npcPointer)

	int(__thiscall * NPC_IsDetecter)(DWORD npcPtr) = ((int(__thiscall*)(DWORD))0x415670);

	return NPC_IsDetecter(reinterpret_cast<DWORD>(this->npcPtr));
}

int Npc::IsStone()
{
	//4156b0	public: int __thiscall CNpc::IsStone(void)
	//bool __thiscall Npc_IsStone(DWORD npcPointer)

	int(__thiscall * NPC_IsStone)(DWORD npcPtr) = ((int(__thiscall*)(DWORD))0x4156B0);

	return NPC_IsStone(reinterpret_cast<DWORD>(this->npcPtr));
}

int Npc::CheckAIType(int a1)
{
	//416d60	public: int __thiscall CNpc::CheckAIType(int)
	//bool __thiscall Npc_CheckAIType(int DWORD, int a2)

	int(__thiscall * NPC_CheckAIType)(DWORD npcPtr, int a1) = ((int(__thiscall*)(DWORD, int))0x416D60);

	return NPC_CheckAIType(reinterpret_cast<DWORD>(this->npcPtr), a1);
}