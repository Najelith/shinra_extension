#pragma once
#include "CodeModifier.h"
class ServerCodeModifier :
	public CodeModifier
{
public:
	int a[3];
	int k;
	ServerCodeModifier(void);
	virtual void installHooks(void);
	void installAllBloodyEncodeDecodeHooks(void);
	virtual ~ServerCodeModifier(void);
};

