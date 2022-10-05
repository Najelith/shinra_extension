#include "stdafx.h"

#include "MyDatabase.h"


void* CMyDatabase_GetDB(DWORD dbPtr, int* a1)
{
	//40fa50	public: class CDatabase * __thiscall CMyDatabase::GetDB(int &) 

	void*(__thiscall * _CMyDatabase_GetDB)(DWORD dbPtr, int* a1) = ((void*(__thiscall*)(DWORD, int*))0x40fa50);

	return _CMyDatabase_GetDB(dbPtr, a1);
}

void CMyDatabase_ReleaseDB(DWORD dbPtr, int a1)
{
	//40fbc0	public: void __thiscall CMyDatabase::ReleaseDB(int);

	void(__thiscall * _CMyDatabase_ReleaseDB)(DWORD dbPtr, int a1) = ((void(__thiscall*)(DWORD, int))0x40fbc0);

	_CMyDatabase_ReleaseDB(dbPtr, a1);

}
