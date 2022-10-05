#include "StdAfx.h"
#include "Extention.h"
#include <iostream>



Extention::Extention(CodeModifier* cm)
{
	codeModifier = cm;
}


Extention::~Extention(void)
{
}

void Extention::init(void)
{
	/*DWORD tempThreadId;
	CreateThread(NULL,0,Extention::startExtention,0,CREATE_SUSPENDED,&tempThreadId);
	this->myThreadId = tempThreadId;*/
	codeModifier->installHooks();

}

DWORD WINAPI Extention::startExtention( void* parameter){

	return NULL;
}