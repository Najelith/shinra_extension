#pragma once
class Item
{
public:
	Item(void);
	~Item(void);
	int NewItem(DWORD);
	signed int CopyTableItem(void*, int);
	int DeleteItem(DWORD, int);
	DWORD inline getsNum(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x10);
	}
	DWORD inline getbType(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x12);
	}
	DWORD inline getbArm(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x13);
	}
	DWORD inline getbGender(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x14);
	}
	DWORD inline getsPicNum(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x16);
	}
	DWORD inline getsAb1(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x18);
	}
	DWORD inline getsAb2(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x1A);
	}
	DWORD inline getsNeedStr(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x1c);
	}
	DWORD inline getsNeedInt(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x1e);
	}
	DWORD inline getsNeedDex(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x20);
	}
	DWORD inline getsNeedSkill(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x22);
	}
	DWORD inline getsMagicNo(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x24);
	}
	DWORD inline getsMagicOpt(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x26);
	}
	DWORD inline getsDur(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x28);
	}
	DWORD inline getsDex(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x2a);
	}
	DWORD inline getsAt(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x2c);
	}
	DWORD inline getsDf(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x2e);
	}
	DWORD inline getsHP(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x30);
	}
	DWORD inline getsMP(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x32);
	}
	DWORD inline getsUsage(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x34);
	}
	WORD inline getsWgt(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x36);
	}
	DWORD inline getsTime(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x38);
	}
	DWORD inline getsSpecial(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x3A);
	}
	DWORD inline getsSpOpt1(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x3c);
	}
	DWORD inline getsSpOpt2(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x3e);
	}
	DWORD inline getsSpOpt3(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x40);
	}
	DWORD inline getsPlusSpecial1(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x42);
	}
	DWORD inline getsPlusSpecial2(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x44);
	}
	DWORD inline getsPlusSpecial3(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x46);
	}
	DWORD inline getsPlusSpecial1SpOpt1(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x48);
	}
	DWORD inline getsPlusSpecial1SpOpt2(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x4a);
	}
	DWORD inline getsPlusSpecial1SpOpt3(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x4c);
	}
	DWORD inline getsPlusSpecial2SpOpt1(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x4e);
	}
	DWORD inline getsPlusSpecial2SpOpt2(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x50);
	}
	DWORD inline getsPlusSpecial2SpOpt3(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x52);
	}
	DWORD inline getsPlusSpecial3SpOpt1(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x54);
	}
	DWORD inline getsPlusSpecial3SpOpt2(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x56);
	}
	DWORD inline getsPlusSpecial3SpOpt3(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x58);
	}
	DWORD inline getsMaxUsage(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x5c);
	}
	DWORD inline getsUpgradeLevel(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x5e);
	}
	DWORD inline getiItemSerial(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x60);
	}
	DWORD inline getiCost(DWORD itemPointer) {
		return *(DWORD*)(itemPointer + 0x68);
	}
	CHAR* getstrName(DWORD itemPointer) {
		return (CHAR*)(itemPointer + 0x6c);
	}

};

