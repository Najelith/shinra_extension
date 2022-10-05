#pragma once
class CodeModifier
{
public:
	CodeModifier(void);
	virtual void installHooks()=0;
	virtual ~CodeModifier(void);
protected:
	static void patchCall(void* , void* );
private:
	

};