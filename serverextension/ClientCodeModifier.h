#pragma once
#include "codemodifier.h"
class ClientCodeModifier :
	public CodeModifier
{
public:
	ClientCodeModifier(void);
	void install_SocketMng_EncodeDecode_Hook();
	virtual void installHooks();
	virtual ~ClientCodeModifier(void);
};

