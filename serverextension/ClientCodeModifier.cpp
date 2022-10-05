#include "StdAfx.h"
#include "ClientCodeModifier.h"
#include "wrappers.h"
#include <iostream>


ClientCodeModifier::ClientCodeModifier(void)
{
#ifdef RAUBAN_DEBUG
	if(AllocConsole()) {
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitle(L"Soma Debug Console");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		CONSOLE_SCREEN_BUFFER_INFO coninfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&coninfo);
		coninfo.dwSize.Y=1000;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coninfo.dwSize);
	}
#endif
}


ClientCodeModifier::~ClientCodeModifier(void)
{
}

void ClientCodeModifier::installHooks(){

	//hook encodeDecode
	void* hook = encodeDecodeWrapper;

	patchCall(reinterpret_cast<void*>(0x04D9A56), hook); // install_SocketMng_EncodeDecode_Hook();

	patchCall(reinterpret_cast<void*>(0x04D9C5D), hook);
	patchCall(reinterpret_cast<void*>(0x04D9EEB), hook);

	hook = encryptionStartResultWrapper;

	patchCall(reinterpret_cast<void*>(0x04CF541), hook);





}