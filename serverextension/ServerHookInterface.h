#pragma once
#include "EventManager.h"

class ServerHookInterface
{
public:
	ServerHookInterface(void);
	virtual ~ServerHookInterface(void);


	static __int16 __cdecl ENCODE_DECODE_replacement(void*, unsigned int, int, BYTE*, BYTE*);
	static void __stdcall User__version_wrapper(void* , BYTE* );
	//user init
	static void __stdcall User__LoginReq_wrapper(void* sourcePointer,void* unknown);
	static void __stdcall 	User__load_user_data_wrapper(void* sourcePointer,void* unknown);

	static void __stdcall User__Init_wrapper(void*);
	static void __stdcall User__GETDATA_wrapper(void* unknown1,void* unknown);
    static void __stdcall User__LOADDATA_wrapper(void* sourcePointer,void* unknown);

	// send my info
	static void __stdcall User__Send_My_Info_wrapper(void* sourcePointer,void* unknown);

	// reload events
	static void __stdcall User__ReloadEvent_wrapper(void* unknown,void* unknown2,void* unknown3);

	// new char
	
    static void __stdcall User__NEWHERO_wrapper(void* sourcePointer,void* unknown);
    static void __stdcall User__EXISTCHAR_wrapper(void* sourcePointer,void* unknown);

	// check monster
	static void __stdcall User__check_monster_wrapper(void* sourcePointer, void*unkown);

		//command '/'
	static void __stdcall User__Copt_wrapper(DWORD,DWORD);
	// pkpos thing
	static void __stdcall User__Pkpos_wrapper(void* , short);
		static void __stdcall User__Pkpos_wrapper1(void* , short);
			static void __stdcall User__Pkpos_wrapper2(void* , short);
    //plusmoralbynpc
			static void __stdcall User__pmoral_wrapper(void* , short,void*);
	//npcdead
			static void __stdcall User__npcdead_wrapper(void* ,void*);
	//npcrunevent
			static void __stdcall User__npcevent_wrapper(void*, void*, int);

		//client event
			static void __stdcall User__cevent_wrapper(void* ,void*);

	    //runeventbynum
			static void __stdcall User__runeventbynum_wrapper(void*,int);


	//warehouse
	static void __stdcall User__takeBackItem_wrapper(void* , BYTE* );
	static void __stdcall User__saveItem_wrapper(void* , BYTE* );
	static void __stdcall User__takeBackMoney_wrapper(void* , BYTE* );
	static void __stdcall User__saveMoney_wrapper(void* , BYTE* );
	static void __stdcall User__StorageOpen_wrapper(void* , int );
	//guild
	static void __stdcall User__GuildSaveItem_wrapper(void* , BYTE* );
	static void __stdcall User__GuildTakeBackItem_wrapper(void* , BYTE* );
	static void __stdcall User__GuildContribution_wrapper(void* , BYTE* );
	static void __stdcall User__OpenGuildTownStone_wrapper(void*,short unknown);
	static void __stdcall User__GuildOpen_wrapper(void*);
	//moves
	static void __stdcall User__SpecialMove_wrapper(void* , BYTE* );
	static void __stdcall User__MoveReq_wrapper(void* , BYTE* );
	static void __stdcall User__Move_wrapper(void*,int,int);
	static void __stdcall User__RunReq_wrapper(void* , BYTE* );
	static void __stdcall User__RunFirst_wrapper(void* , BYTE* );

	static void __stdcall User__RepairItemOpen_wrapper(void*);
	static void __stdcall User__RepairItem_wrapper(void* , BYTE* );
	//db entry
	static int pklog(const char*,const char*,int,int);
	static int pkposget(int,int,int,int);
	static char* setguildmess(int,const char*,const char*);
	static int getusershopid(const char*);
	static int setguildpos(int,const char*,int);
	static char* getguildmess(int);	

	// do pictures
	// static void __stdcall Guild__npcreset(void*,int);

	//LogOut
	static void __stdcall User__LogOut_wrapper(void*,BYTE*);

	//OnePerOneDLG
	static void __stdcall OnePerOneDlg__CheckGameTime_wrapper(void* userPointer);

	//diritem
//	static void __stdcall User__diritem_wrapper(void* userPointer, BYTE a2, int a3, int a4, int a5, int a6);
	static void __stdcall User__diritem_wrapper(void* userPointer, int a2);

	//select message
	static void __stdcall User__slmsg_wrapper(void* userPointer, int addr);

	//end town war
	static void __stdcall Guild__town_war_end(int guildnum);

	//check guild war army
	static signed int __stdcall checkgwa_wrapper(void * sourcePointer,void* targetPointer);

	//check gray
	static signed int __stdcall User__cgray_wrapper(void * sourcePointer,void* targetPointer);

	//check pk
	static signed int __stdcall User__cpk_wrapper(void * sourcePointer,void* targetPointer);


	

	// check special attack delay
	static signed int __stdcall User__checkspecialattackdelay_wrapper(void* userPointer, void* sSpecial);


	
	

	
};

