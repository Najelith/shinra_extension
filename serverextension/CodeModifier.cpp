#include "StdAfx.h"
#include "CodeModifier.h"

CodeModifier::CodeModifier(void)
{
}


CodeModifier::~CodeModifier(void)
{
}

void CodeModifier::patchCall(void* callInstruction, void* addressOfFuctionToCall){
	int* p;
	DWORD old;
	p = reinterpret_cast<int*>( reinterpret_cast<DWORD>(callInstruction) + 1); // +1 for the E8 byte 
	VirtualProtect(callInstruction,5,PAGE_EXECUTE_READWRITE,&old);
	//*p is now the old calldestination. TODO:: let's save that ey?
	*p = (reinterpret_cast<int>(addressOfFuctionToCall) - reinterpret_cast<int>(p + 1)); // +1 means + 1 int == +4 //and 4 more for the address to skip
	VirtualProtect(callInstruction,5,old,NULL);
	FlushInstructionCache(GetCurrentProcess(),(LPCVOID)callInstruction,5);
}

