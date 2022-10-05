#include "StdAfx.h"
#include "Item.h"


Item::Item(void)
{
}


Item::~Item(void)
{
}

int Item::NewItem(DWORD itemP) {
	int(__thiscall * NewItem)(DWORD itemP) = ((int(__thiscall*)(DWORD))0x004839C0);
	return NewItem(itemP);
}

signed int Item::CopyTableItem(void* itemP, int _sNum) {
	signed int(__thiscall * CopyTableItem)(void* itemP, int _sNum) = ((signed int(__thiscall*)(void*, int))0x00409D00);
	return CopyTableItem(itemP, _sNum);
}

int Item::DeleteItem(DWORD userPointer, int itemPointer) {
	int(__thiscall * DeleteItem)(DWORD userPointer, int a2) = ((int(__thiscall*)(DWORD, int))0x00483A80);
	return DeleteItem(userPointer, itemPointer);
}