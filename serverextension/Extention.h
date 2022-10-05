#pragma once
#include "stdafx.h"
#include "ClientCodeModifier.h"

class Extention
{
public:
	Extention(CodeModifier* );
	void init(void);
	virtual ~Extention(void);
private:
	CodeModifier* codeModifier;
	DWORD myThreadId;
	static DWORD WINAPI startExtention( void* );
	
	
};

