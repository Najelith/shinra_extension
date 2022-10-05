#pragma once
#include "ServerHookInterface.h"

//Asm wrappers for avoiding issues with thiscall.
// thiscall to stdcall wrapper! ;D
#define DefineThisToSTD(funcName,funcToWrap) \
void __declspec(naked) funcName(void){ \
		__asm mov eax, [esp] \
		__asm mov [esp],ecx \
		__asm push eax \
		__asm jmp funcToWrap \
}

#ifdef RAUBAN_DEBUG
void printLine(BYTE* buff, int size){
	for(int i = 0; i < size; i++){
		printf("%02X",buff[i]);
	}
	printf("\n");
}
#endif


DefineThisToSTD(User__Version_thiswrapper,ServerHookInterface::User__version_wrapper);
//player init
DefineThisToSTD(User__LoginReq_thiswrapper,ServerHookInterface::User__LoginReq_wrapper);

DefineThisToSTD(User__load_user_data_thiswrapper,ServerHookInterface::User__load_user_data_wrapper);

DefineThisToSTD(User__Init_thiswrapper,ServerHookInterface::User__Init_wrapper);
DefineThisToSTD(User__LOADDATA_thiswrapper,ServerHookInterface::User__LOADDATA_wrapper);
DefineThisToSTD(User__GETDATA_thiswrapper,ServerHookInterface::User__GETDATA_wrapper);

//send my info
DefineThisToSTD(User__Send_My_Info_thiswrapper,ServerHookInterface::User__Send_My_Info_wrapper);

//reload events

DefineThisToSTD(User__ReloadEvent_thiswrapper,ServerHookInterface::User__ReloadEvent_wrapper);

//new char

DefineThisToSTD(User__NEWHERO_thiswrapper,ServerHookInterface::User__NEWHERO_wrapper);
DefineThisToSTD(User__EXISTCHAR_thiswrapper,ServerHookInterface::User__EXISTCHAR_wrapper);

// check monster
DefineThisToSTD(User__check_monster_thiswrapper,ServerHookInterface::User__check_monster_wrapper);


//command opt '/'
DefineThisToSTD(User__Copt_thiswrapper,ServerHookInterface::User__Copt_wrapper);
//pk pos thing
DefineThisToSTD(User__Pkpos_thiswrapper,ServerHookInterface::User__Pkpos_wrapper);
DefineThisToSTD(User__Pkpos_thiswrapper1,ServerHookInterface::User__Pkpos_wrapper1);
DefineThisToSTD(User__Pkpos_thiswrapper2,ServerHookInterface::User__Pkpos_wrapper2);
// plusmoralbynpc
DefineThisToSTD(User__pmoral_thiswrapper,ServerHookInterface::User__pmoral_wrapper);
// npcdeadevent
DefineThisToSTD(User__npcdead_thiswrapper,ServerHookInterface::User__npcdead_wrapper);

// client event
DefineThisToSTD(User__cevent_thiswrapper,ServerHookInterface::User__cevent_wrapper);

// npcruneventt
DefineThisToSTD(User__npcevent_thiswrapper,ServerHookInterface::User__npcevent_wrapper);

// run event by num
DefineThisToSTD(User__runeventbynum_wrapper,ServerHookInterface::User__runeventbynum_wrapper);

//Logout
DefineThisToSTD(User__LogOut_thiswrapper,ServerHookInterface::User__LogOut_wrapper);

//direction item
DefineThisToSTD(User__diritem_thiswrapper,ServerHookInterface::User__diritem_wrapper);

//select message
DefineThisToSTD(User__slmsg_thiswrapper,ServerHookInterface::User__slmsg_wrapper);

//user check gray
DefineThisToSTD(User__cgray_thiswrapper,ServerHookInterface::User__cgray_wrapper);

//user check pk
DefineThisToSTD(User__cpk_thiswrapper,ServerHookInterface::User__cpk_wrapper);

// checkguildwararmy
DefineThisToSTD(checkgwa_thiswrapper, ServerHookInterface::checkgwa_wrapper);






// user CheckSpeaiclAttackDelay
DefineThisToSTD(User__checkspecialattackdelay_wrapper, ServerHookInterface::User__checkspecialattackdelay_wrapper);


//OnePerOneDLG
//Check Game Time
DefineThisToSTD(OnePerOneDlg__CheckGameTime_thiswrapper,ServerHookInterface::OnePerOneDlg__CheckGameTime_wrapper);

//warehouse detours
DefineThisToSTD(User_TakeBackItem_thiswrapper,ServerHookInterface::User__takeBackItem_wrapper);
DefineThisToSTD(User_SaveItem_thiswrapper,ServerHookInterface::User__saveItem_wrapper);
DefineThisToSTD(User_TakeBackMoney_thiswrapper,ServerHookInterface::User__takeBackMoney_wrapper);
DefineThisToSTD(User_SaveMoney_thiswrapper,ServerHookInterface::User__saveMoney_wrapper);
DefineThisToSTD(User_StorageOpen_thiswrapper,ServerHookInterface::User__StorageOpen_wrapper);
//guild detours
DefineThisToSTD(User_GuildSaveItem_thiswrapper,ServerHookInterface::User__GuildSaveItem_wrapper);
DefineThisToSTD(User_GuildTakeBackItem_thiswrapper,ServerHookInterface::User__GuildTakeBackItem_wrapper);
DefineThisToSTD(User_GuildContribution_thiswrapper,ServerHookInterface::User__GuildContribution_wrapper);
DefineThisToSTD(User_OpenGuildTownStone_thiswrapper,ServerHookInterface::User__OpenGuildTownStone_wrapper);
DefineThisToSTD(User_GuildOpen_thiswrapper,ServerHookInterface::User__GuildOpen_wrapper);
//proxy recall/trace prevention
DefineThisToSTD(User_SpecialMove_thiswrapper,ServerHookInterface::User__SpecialMove_wrapper);
//speedhack prevention
DefineThisToSTD(User_MoveReq_thiswrapper,ServerHookInterface::User__MoveReq_wrapper);
DefineThisToSTD(User_Move_thiswrapper,ServerHookInterface::User__Move_wrapper);
DefineThisToSTD(User_RunReq_thiswrapper,ServerHookInterface::User__RunReq_wrapper);
DefineThisToSTD(User_RunFirst_thiswrapper,ServerHookInterface::User__RunFirst_wrapper);
//proxy repair prevention
DefineThisToSTD(User_RepairItemOpen_thiswrapper,ServerHookInterface::User__RepairItemOpen_wrapper);
DefineThisToSTD(User_RepairItem_thiswrapper,ServerHookInterface::User__RepairItem_wrapper);