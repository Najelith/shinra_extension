#pragma once
#include "StdAfx.h"





//Setters
void inline SetByte(BYTE* buffer, BYTE byteTOPut, DWORD* offset){
	buffer[(*offset)++] = byteTOPut;
}

void inline SetWord(BYTE *buffer, WORD wordToPut, DWORD *offset)
{
  DWORD *result; // eax@1

  result = offset;
  *(WORD *)&buffer[*offset] = wordToPut;
  *offset += 2;
}

int inline SetString(BYTE* buffer, const void *text, unsigned int textLenth, int *offset)
{
  int result; // eax@1

  //printf("%s\n", text);

  result = *offset;
  memcpy((void *)(buffer + *offset), text, textLenth);
  result += textLenth;
  *offset += textLenth;
  return result;
}

void inline SetDWord(BYTE *buffer, DWORD dwordToPut, DWORD *offset)
{
  DWORD *result; // eax@1

  result = offset;
  *(DWORD *)&buffer[*offset] = dwordToPut;
  *offset += 4;
}

void inline SetShort(BYTE *buffer, DWORD wordToPut, DWORD *offset)
{
  DWORD *result; // eax@1

  result = offset;
  *(WORD *)&buffer[*offset] = (short)wordToPut;
  *offset += 2;
}
void inline SetInt(BYTE *buffer, int dwordToPut, DWORD *offset)
{
  DWORD *result; // eax@1

  result = offset;
  *(DWORD *)&buffer[*offset] = dwordToPut;
  *offset += 4;
}


static void SetUINT64(BYTE* buffer, int a1, int a2, DWORD* offset)
{
	void(__cdecl * _SetUINT64)(BYTE* buffer, int a1, int a2, DWORD* offset) = ((void(__cdecl*)(BYTE*, int, int, DWORD*))0x407450);

	_SetUINT64(buffer, a1, a2, offset);
}




// Getters

/*static void GetString(BYTE* buffer, BYTE* a1, int a2, DWORD* offset)
{
	void(__thiscall * _GetString)(BYTE* buffer, BYTE* a1, int a2, DWORD* offset) = ((void(__thiscall*)(BYTE*, BYTE*, int, DWORD*))0x4072f0);

	_GetString(buffer, a1, a2, offset);
}*/

void inline GetString(BYTE* dst, BYTE* src, int size, DWORD* offset)
{
	memcpy(dst, src + *offset, size);

	*offset += size;

	return;
}

BYTE inline GetByte(BYTE *buffer, DWORD *offset)
{
  return buffer[(*offset)++];
}

WORD inline GetWord(BYTE *buffer, DWORD *offset)
{
  DWORD posToGet; // ecx@1

  posToGet = *offset + 2;
  *offset = posToGet;
  return *(WORD*)&buffer[posToGet - 2];
}

short inline GetShort(BYTE *buffer, DWORD *offset)
{
  DWORD posToGet; // ecx@1

  posToGet = *offset + 2;
  *offset = posToGet;
  return *(short*)&buffer[posToGet - 2];
}


DWORD inline GetDWORD(BYTE *buffer, DWORD *offset)
{
  DWORD posToGet; // ecx@1

  posToGet = *offset + 4;
  *offset = posToGet;
  return *(DWORD*)&buffer[posToGet - 4];
}



//unsigned __int64 __cdecl GetUINT64(char*, int&)
static unsigned __int64 GetUINT64(BYTE* buffer, DWORD* offset)
{
	unsigned __int64(__cdecl * _GetUINT64)(BYTE* buffer, DWORD* offset) = ((unsigned __int64(__cdecl*)(BYTE*, DWORD*))0x407390);

	return _GetUINT64(buffer, offset);
}