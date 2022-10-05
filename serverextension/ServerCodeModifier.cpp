#include "StdAfx.h"
#include "ServerCodeModifier.h"
#include "ServerHookInterface.h"
#include <iostream>
#include "wrappers.h"
#include "User.h"



ServerCodeModifier::ServerCodeModifier(void)
{
#ifdef RAUBAN_DEBUG
	if(AllocConsole()) {
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitle(L"OnePerOne Debug Console");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		CONSOLE_SCREEN_BUFFER_INFO coninfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&coninfo);
		coninfo.dwSize.Y=1000;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coninfo.dwSize);
	}
#endif
	
}


ServerCodeModifier::~ServerCodeModifier(void)
{
}

void ServerCodeModifier::installHooks()
{
	//push esi 56 (+290h)moral ebx 53

	/*converting Encode_decode to send it's userpointer instead of it's key as first argument
	DWORD old;
	VirtualProtect((LPVOID)(0x401000),0x04B3934 - 0x00401000,PAGE_EXECUTE_READWRITE,&old);

	*reinterpret_cast<BYTE*>(0x00402FC1) = 0x53;

	*reinterpret_cast<BYTE*>(0x004030F6) = 0x53;

	*reinterpret_cast<BYTE*>(0x004031FD) = 0x53;

	*reinterpret_cast<BYTE*>(0x004031FD) = 0x53;

	BYTE* p = reinterpret_cast<BYTE*>(0x0042BE6C);
	*(p++) = 0x90;
	*(p++) = 0x90;
	*(p++) = 0x90;
	*(p++) = 0x90;
	*(p++) = 0x90;
	*(p++) = 0x90;

	*reinterpret_cast<BYTE*>(0x0042BF4E) = 0x53;

	*reinterpret_cast<BYTE*>(0x0042C093) = 0x53;

	*reinterpret_cast<BYTE*>(0x0042C19A) = 0x53;

	*reinterpret_cast<BYTE*>(0x0042C4E7) = 0x57;

	VirtualProtect((LPVOID)(0x401000),0x04B3934 - 0x00401000,old,NULL);
	FlushInstructionCache(GetCurrentProcess(),(LPCVOID)(0x401000),0x04B3934 - 0x00401000);
	//hooks encode_decode
	installAllBloodyEncodeDecodeHooks(); */

	//hooks versionparser
	//void* hook = User__Version_thiswrapper;
	//patchCall(reinterpret_cast<void*>(0x042C8C0), hook);

	//Warehouse deposit Item
	void* hook = User_TakeBackItem_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0042CBF8), hook);
	// classpoint check calls
	hook = User__Pkpos_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x00434DB6), hook); //edi

	hook = User__Pkpos_thiswrapper1;
	patchCall(reinterpret_cast<void*>(0x00438F6F), hook); //ebx

	hook = User__Pkpos_thiswrapper2;
	// esi
	patchCall(reinterpret_cast<void*>(0x0043B03D), hook);
	patchCall(reinterpret_cast<void*>(0x0043CBDB), hook);
	patchCall(reinterpret_cast<void*>(0x0047CB04), hook);
	patchCall(reinterpret_cast<void*>(0x0047CCD6), hook);
	patchCall(reinterpret_cast<void*>(0x0047E505), hook);
	patchCall(reinterpret_cast<void*>(0x0047E693), hook);
	patchCall(reinterpret_cast<void*>(0x0047E83A), hook);
	patchCall(reinterpret_cast<void*>(0x00480208), hook);
	patchCall(reinterpret_cast<void*>(0x004803B3), hook);
	patchCall(reinterpret_cast<void*>(0x004804F8), hook);
	patchCall(reinterpret_cast<void*>(0x00480070), hook);
	patchCall(reinterpret_cast<void*>(0x00480636), hook);
	// end of classpoint checks

	//plus moral by npc
		//push esi 56 (+290h)moral ebx 53

		///converting plusmoralbynpc to send it's npcpointer instead of class
	DWORD old;
	VirtualProtect((LPVOID)(0x401000), 0x04B3934 - 0x00401000, PAGE_EXECUTE_READWRITE, &old);

	*reinterpret_cast<BYTE*>(0x00435075) = 0x53;

	*reinterpret_cast<BYTE*>(0x00439542) = 0x53;

	*reinterpret_cast<BYTE*>(0x0043B24B) = 0x56;

	*reinterpret_cast<BYTE*>(0x0043CDA5) = 0x56;

	*reinterpret_cast<BYTE*>(0x0047D25E) = 0x53;

	*reinterpret_cast<BYTE*>(0x0047D4F4) = 0x53;

	*reinterpret_cast<BYTE*>(0x0047EB37) = 0x56;

	*reinterpret_cast<BYTE*>(0x0047ED14) = 0x56;

	*reinterpret_cast<BYTE*>(0x0047EFA0) = 0x56;

	*reinterpret_cast<BYTE*>(0x004808A0) = 0x56;

	*reinterpret_cast<BYTE*>(0x00480A7D) = 0x56;

	*reinterpret_cast<BYTE*>(0x00480C73) = 0x56;

	*reinterpret_cast<BYTE*>(0x00480E69) = 0x56;

	*reinterpret_cast<BYTE*>(0x00481043) = 0x56;

	*reinterpret_cast<BYTE*>(0x00481DAD) = 0xC9; // for livenpc function now it spawns monsters reguardless of the player's zone that called it

	//*reinterpret_cast<BYTE*>(0x0042F493) = 0x56; // for loaduserdata

	VirtualProtect((LPVOID)(0x401000), 0x04B3934 - 0x00401000, old, NULL);
	FlushInstructionCache(GetCurrentProcess(), (LPCVOID)(0x401000), 0x04B3934 - 0x00401000);

	hook = User__pmoral_thiswrapper;
	// esi

	patchCall(reinterpret_cast<void*>(0x00435079), hook);
	patchCall(reinterpret_cast<void*>(0x00439546), hook);
	patchCall(reinterpret_cast<void*>(0x0043B24E), hook);
	patchCall(reinterpret_cast<void*>(0x0043CDA9), hook);
	patchCall(reinterpret_cast<void*>(0x0047D262), hook);
	patchCall(reinterpret_cast<void*>(0x0047D4F8), hook);
	patchCall(reinterpret_cast<void*>(0x0047EB3B), hook);
	patchCall(reinterpret_cast<void*>(0x0047ED18), hook);
	patchCall(reinterpret_cast<void*>(0x0047EFA4), hook);
	patchCall(reinterpret_cast<void*>(0x004808A4), hook);
	patchCall(reinterpret_cast<void*>(0x00480A81), hook);
	patchCall(reinterpret_cast<void*>(0x00480C77), hook);
	patchCall(reinterpret_cast<void*>(0x00480E6D), hook);
	patchCall(reinterpret_cast<void*>(0x00481047), hook);
	// end of plus moral

					 //login request
	hook = User__LoginReq_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0042C868), hook);

	// original call 0042F2E0 <?LogInReq@USER@@QAEXPAD@Z>/$ 6A FF                  PUSH -0x1

	//load user data
	hook = User__load_user_data_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0042F494), hook);

	// original call 00431230 <?LoadUserData@USER@@QAEHP>/$ 81EC 140E0000          SUB ESP,0xE14

/*
	//Send My Info
		hook = User__Send_My_Info_thiswrapper;


	patchCall(reinterpret_cast<void*>(0x004271E2), hook);
	patchCall(reinterpret_cast<void*>(0x0042F772), hook);
	patchCall(reinterpret_cast<void*>(0x0043112D), hook);
	patchCall(reinterpret_cast<void*>(0x00432F76), hook);
	patchCall(reinterpret_cast<void*>(0x00434E41), hook);
	patchCall(reinterpret_cast<void*>(0x004354BE), hook);
	patchCall(reinterpret_cast<void*>(0x00438FF3), hook);
	patchCall(reinterpret_cast<void*>(0x004398C0), hook);
	patchCall(reinterpret_cast<void*>(0x0043AE54), hook);
	patchCall(reinterpret_cast<void*>(0x0043B0DD), hook);
	patchCall(reinterpret_cast<void*>(0x0043C9F5), hook);
	patchCall(reinterpret_cast<void*>(0x0043CC7B), hook);
	patchCall(reinterpret_cast<void*>(0x0043E913), hook);
	patchCall(reinterpret_cast<void*>(0x0043F017), hook);
	patchCall(reinterpret_cast<void*>(0x0043F219), hook);
	patchCall(reinterpret_cast<void*>(0x0043F23F), hook);
	patchCall(reinterpret_cast<void*>(0x0044A0FE), hook);
	patchCall(reinterpret_cast<void*>(0x0044A185), hook);
	patchCall(reinterpret_cast<void*>(0x0044AA11), hook);
	patchCall(reinterpret_cast<void*>(0x0044CE0C), hook);
	patchCall(reinterpret_cast<void*>(0x0044CE45), hook);
	patchCall(reinterpret_cast<void*>(0x00455A07), hook);
	patchCall(reinterpret_cast<void*>(0x00455CDE), hook);
	patchCall(reinterpret_cast<void*>(0x0045AA98), hook);
	patchCall(reinterpret_cast<void*>(0x0045CEAA), hook);
	patchCall(reinterpret_cast<void*>(0x0045CF20), hook);
	patchCall(reinterpret_cast<void*>(0x0045D46A), hook);
	patchCall(reinterpret_cast<void*>(0x00465E54), hook);
	patchCall(reinterpret_cast<void*>(0x00465ECB), hook);
	patchCall(reinterpret_cast<void*>(0x004689D8), hook);
	patchCall(reinterpret_cast<void*>(0x0046B79B), hook);
	patchCall(reinterpret_cast<void*>(0x0046DB44), hook);
	patchCall(reinterpret_cast<void*>(0x0046E633), hook);
	patchCall(reinterpret_cast<void*>(0x0046E764), hook);
	patchCall(reinterpret_cast<void*>(0x0046E949), hook);
	patchCall(reinterpret_cast<void*>(0x004703E2), hook);
	patchCall(reinterpret_cast<void*>(0x00471A25), hook);
	patchCall(reinterpret_cast<void*>(0x00471AEC), hook);
	patchCall(reinterpret_cast<void*>(0x00473031), hook);
	patchCall(reinterpret_cast<void*>(0x004730C4), hook);
	patchCall(reinterpret_cast<void*>(0x0047ADCE), hook);
	patchCall(reinterpret_cast<void*>(0x0047AE61), hook);
	patchCall(reinterpret_cast<void*>(0x0047CD75), hook);
	patchCall(reinterpret_cast<void*>(0x0047D896), hook);
	patchCall(reinterpret_cast<void*>(0x0047E8CD), hook);
	patchCall(reinterpret_cast<void*>(0x0047F165), hook);
	patchCall(reinterpret_cast<void*>(0x0048058B), hook);
	patchCall(reinterpret_cast<void*>(0x004806C9), hook);
	patchCall(reinterpret_cast<void*>(0x00481259), hook);
	patchCall(reinterpret_cast<void*>(0x00481C33), hook);
	patchCall(reinterpret_cast<void*>(0x00481CCF), hook);
	patchCall(reinterpret_cast<void*>(0x00483D25), hook);
	patchCall(reinterpret_cast<void*>(0x0048A79E), hook);
	patchCall(reinterpret_cast<void*>(0x0048A90B), hook);
	patchCall(reinterpret_cast<void*>(0x0048AF79), hook);
	patchCall(reinterpret_cast<void*>(0x0048B4A2), hook);
	patchCall(reinterpret_cast<void*>(0x0048B50E), hook);
	patchCall(reinterpret_cast<void*>(0x0048BA92), hook);
	patchCall(reinterpret_cast<void*>(0x0048BCD7), hook);
	patchCall(reinterpret_cast<void*>(0x0048C05C), hook);
	patchCall(reinterpret_cast<void*>(0x0048C6D7), hook);
	patchCall(reinterpret_cast<void*>(0x0048C729), hook);
/// original call 0042DC70   SUB ESP,410                               (Initial CPU selection)
*/

//load user data
	hook = User__Init_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0042F7D8), hook);
	//patchCall(reinterpret_cast<void*>(0x0044AC53), hook);
	//patchCall(reinterpret_cast<void*>(0x0044AC8D), hook);

				//load user data PROC 
	hook = User__LOADDATA_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0042F494), hook);
	// original call AT 00431230

					//load Monster soma data (get user monster data)
//	hook = User__GETDATA_thiswrapper;
	//patchCall(reinterpret_cast<void*>(0x0041C828), hook);
	// original call AT 00428780

	// load events from reload event button pressed
	// let's try to hijack entire function 00421BD0 <?OnButtonEventReload@COne> . 64:A1 00000000         MOV EAX,DWORD PTR FS:[0]
	hook = User__ReloadEvent_thiswrapper;
	//getsize cptrarray
	patchCall(reinterpret_cast<void*>(0x00421C1A), hook);
	//patchCall(reinterpret_cast<void*>(0x00421C8B), hook);
//	00421C8B   E8 602FFEFF      CALL ext(shop.00404BF0 <- original call
	// 00421C1A                             . E8 E0590800            CALL <ext(shop.?SetSize@CPtrArray>                             ; \?SetSize@CPtrArray
	//004A75FF <?SetSize@CPtrArray>       /$ 55                     PUSH EBP




	// NEW HERO
	hook = User__NEWHERO_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0042C8EE), hook);
	// original call AT 00445080

	//exists char id
	hook = User__EXISTCHAR_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x00445387), hook);
	patchCall(reinterpret_cast<void*>(0x0044CA80), hook);
	// original call AT 0044e400

			//command operator '/'
	hook = User__Copt_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0043D114), hook);

	// npcdeadevent
	hook = User__npcdead_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x00435081), hook);
	patchCall(reinterpret_cast<void*>(0x0043954E), hook);
	patchCall(reinterpret_cast<void*>(0x0043B256), hook);
	patchCall(reinterpret_cast<void*>(0x0043CDB1), hook);
	patchCall(reinterpret_cast<void*>(0x0047D26A), hook);
	patchCall(reinterpret_cast<void*>(0x0047D500), hook);
	patchCall(reinterpret_cast<void*>(0x0047EB43), hook);
	patchCall(reinterpret_cast<void*>(0x0047ED20), hook);
	patchCall(reinterpret_cast<void*>(0x0047EFAC), hook);
	patchCall(reinterpret_cast<void*>(0x004808AC), hook);
	patchCall(reinterpret_cast<void*>(0x00480A89), hook);
	patchCall(reinterpret_cast<void*>(0x00480C7F), hook);
	patchCall(reinterpret_cast<void*>(0x00480E75), hook);
	patchCall(reinterpret_cast<void*>(0x0048104F), hook);

	/*References in ext(shop:.text to <?NpcDeadEvent@USER@@QAEXPAVCNpc@@@Z 0044db80 f   USER.obj>
Address         Disassembly                               Comment
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
0x0044CE60 <ext(  SUB ESP,404                               (Initial CPU selection)
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
		CALL <ext(shop.?NpcDeadEvent@USER@@QAEXP
*/
/* clientevent*/
	hook = User__cevent_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0042CAD9), hook);
	patchCall(reinterpret_cast<void*>(0x0044CEBC), hook);

	// itemevent
	hook = User__runeventbynum_wrapper;
	patchCall(reinterpret_cast<void*>(0x00465B2C), hook);

	// runnpcevent
	hook = User__npcevent_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0043E6CE), hook);
	patchCall(reinterpret_cast<void*>(0x0044D261), hook);


	//Warehouse withdraw Item
	hook = User_SaveItem_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x042CBE5), hook);

	//Warehouse deposit Money
	hook = User_SaveMoney_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x42CC0B), hook);


	//Warehouse withdraw Money
	hook = User_TakeBackMoney_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x42CC1E), hook);



	//StorageOpen
	hook = User_StorageOpen_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0043D86E), hook);
	patchCall(reinterpret_cast<void*>(0x0043E017), hook);


	//OpenGuildTownStone
	hook = User_OpenGuildTownStone_thiswrapper;
	// old// patchCall(reinterpret_cast<void*>(0x488F90), hook);
	patchCall(reinterpret_cast<void*>(0x43DBBB), hook);
	patchCall(reinterpret_cast<void*>(0x43E501), hook);

	//GuildOpen
	hook = User_GuildOpen_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x43DB03), hook);
	patchCall(reinterpret_cast<void*>(0x43E3D1), hook);

	//GuildSaveItem
	hook = User_GuildSaveItem_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x42CF3C), hook);

	//GuildTakeBackItem
	hook = User_GuildTakeBackItem_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x42CF4F), hook);

	//GuildContribution
	hook = User_GuildContribution_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x42CF75), hook);

	//Trace/recall
	hook = User_SpecialMove_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x42D0FE), hook);
	/*
		//MoveReq
		hook = User_MoveReq_thiswrapper;
		patchCall(reinterpret_cast<void*>(0x42C9F5), hook);

		// Move
		hook = User_Move_thiswrapper;

		patchCall(reinterpret_cast<void*>(0x433050), hook);
		patchCall(reinterpret_cast<void*>(0x4333BB), hook);
		patchCall(reinterpret_cast<void*>(0x4333F7), hook);
		patchCall(reinterpret_cast<void*>(0x433730), hook);
		patchCall(reinterpret_cast<void*>(0x433AAE), hook);
		patchCall(reinterpret_cast<void*>(0x433AD6), hook);
		patchCall(reinterpret_cast<void*>(0x433E20), hook);
		patchCall(reinterpret_cast<void*>(0x433E48), hook);
		patchCall(reinterpret_cast<void*>(0x43417E), hook);
		patchCall(reinterpret_cast<void*>(0x4341AF), hook);
		patchCall(reinterpret_cast<void*>(0x43E8F3), hook);
		patchCall(reinterpret_cast<void*>(0x43E900), hook);



		//RunReq
		hook = User_RunReq_thiswrapper;
		patchCall(reinterpret_cast<void*>(0x0042CAFF), hook);

		//RunFirst
		hook = User_RunFirst_thiswrapper;
		patchCall(reinterpret_cast<void*>(0x0042CAEC), hook);

	*/
	//RepairItemOpen
	hook = User_RepairItemOpen_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0043DAF7), hook);
	patchCall(reinterpret_cast<void*>(0x0043E3E4), hook);

	//RepairItem
	hook = User_RepairItem_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0042CF9B), hook);


	//Logout

	hook = User__LogOut_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0042C8A0), hook);
	patchCall(reinterpret_cast<void*>(0x00449319), hook);
	patchCall(reinterpret_cast<void*>(0x0045C355), hook);
	patchCall(reinterpret_cast<void*>(0x0045C857), hook);
	patchCall(reinterpret_cast<void*>(0x00401A69), hook);


	//OnePerOneDLG CheckGameTime
	hook = OnePerOneDlg__CheckGameTime_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x00420B3E), hook);

	// direction item 
	//hook = User__diritem_thiswrapper;
	//patchCall(reinterpret_cast<void*>(0x00465F21),hook);

		// build house wtf is it?
	hook = User__diritem_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0042CD2F), hook);

	/* select message
	hook = User__slmsg_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0043DA67),hook);
	patchCall(reinterpret_cast<void*>(0x0043E15A),hook);
	*/

	// select message 
	hook = User__slmsg_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x0042CD42), hook);
	//	patchCall(reinterpret_cast<void*>(0x0043E15A),hook);

		// check monster
		//References in ext(shop:.text to <?CheckMonster@USER>
	hook = User__check_monster_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x004114AF), hook);
	patchCall(reinterpret_cast<void*>(0x00412716), hook);
	patchCall(reinterpret_cast<void*>(0x00412DF5), hook);
	patchCall(reinterpret_cast<void*>(0x004130D0), hook);
	patchCall(reinterpret_cast<void*>(0x00413C0E), hook);
	patchCall(reinterpret_cast<void*>(0x00416DCF), hook);
	patchCall(reinterpret_cast<void*>(0x0042B1F2), hook);
	patchCall(reinterpret_cast<void*>(0x0042B5F5), hook);
	patchCall(reinterpret_cast<void*>(0x0042B74A), hook);
	patchCall(reinterpret_cast<void*>(0x0042B9A1), hook);
	patchCall(reinterpret_cast<void*>(0x0042BAD3), hook);
	patchCall(reinterpret_cast<void*>(0x0042BAE9), hook);
	patchCall(reinterpret_cast<void*>(0x0042BC3A), hook);
	patchCall(reinterpret_cast<void*>(0x0042BC4F), hook);
	patchCall(reinterpret_cast<void*>(0x0042DDBA), hook);
	patchCall(reinterpret_cast<void*>(0x0042E621), hook);
	patchCall(reinterpret_cast<void*>(0x0042E728), hook);
	patchCall(reinterpret_cast<void*>(0x0042FAFE), hook);
	patchCall(reinterpret_cast<void*>(0x0042FCBB), hook);
	patchCall(reinterpret_cast<void*>(0x0042FD1C), hook);
	patchCall(reinterpret_cast<void*>(0x004301CD), hook);
	patchCall(reinterpret_cast<void*>(0x004313DC), hook);
	patchCall(reinterpret_cast<void*>(0x004321B6), hook);
	patchCall(reinterpret_cast<void*>(0x00432257), hook);
	patchCall(reinterpret_cast<void*>(0x004346D7), hook);
	patchCall(reinterpret_cast<void*>(0x00434952), hook);
	patchCall(reinterpret_cast<void*>(0x00434994), hook);
	patchCall(reinterpret_cast<void*>(0x004349A6), hook);
	patchCall(reinterpret_cast<void*>(0x004349D7), hook);
	patchCall(reinterpret_cast<void*>(0x004349EB), hook);
	patchCall(reinterpret_cast<void*>(0x00434A01), hook);
	patchCall(reinterpret_cast<void*>(0x00434C5D), hook);
	patchCall(reinterpret_cast<void*>(0x00435717), hook);
	patchCall(reinterpret_cast<void*>(0x00437736), hook);
	patchCall(reinterpret_cast<void*>(0x0043777C), hook);
	patchCall(reinterpret_cast<void*>(0x0043778E), hook);
	patchCall(reinterpret_cast<void*>(0x004377F6), hook);
	patchCall(reinterpret_cast<void*>(0x00437806), hook);
	patchCall(reinterpret_cast<void*>(0x00437818), hook);
	patchCall(reinterpret_cast<void*>(0x00437E9A), hook);
	patchCall(reinterpret_cast<void*>(0x00437FF6), hook);
	patchCall(reinterpret_cast<void*>(0x00438008), hook);
	patchCall(reinterpret_cast<void*>(0x0043806B), hook);
	patchCall(reinterpret_cast<void*>(0x0043807B), hook);
	patchCall(reinterpret_cast<void*>(0x0043808D), hook);
	patchCall(reinterpret_cast<void*>(0x00439E60), hook);
	patchCall(reinterpret_cast<void*>(0x00439EAE), hook);
	patchCall(reinterpret_cast<void*>(0x00439EC0), hook);
	patchCall(reinterpret_cast<void*>(0x00439F27), hook);
	patchCall(reinterpret_cast<void*>(0x00439F37), hook);
	patchCall(reinterpret_cast<void*>(0x00439F49), hook);
	patchCall(reinterpret_cast<void*>(0x0043BA12), hook);
	patchCall(reinterpret_cast<void*>(0x0043BA5C), hook);
	patchCall(reinterpret_cast<void*>(0x0043BA6E), hook);
	patchCall(reinterpret_cast<void*>(0x0043BAD1), hook);
	patchCall(reinterpret_cast<void*>(0x0043BAE1), hook);
	patchCall(reinterpret_cast<void*>(0x0043BAF3), hook);
	patchCall(reinterpret_cast<void*>(0x0043EA32), hook);
	patchCall(reinterpret_cast<void*>(0x00440818), hook);
	patchCall(reinterpret_cast<void*>(0x00442D8E), hook);
	patchCall(reinterpret_cast<void*>(0x00442D9E), hook);
	patchCall(reinterpret_cast<void*>(0x00442F3E), hook);
	patchCall(reinterpret_cast<void*>(0x00442F4E), hook);
	patchCall(reinterpret_cast<void*>(0x0044315E), hook);
	patchCall(reinterpret_cast<void*>(0x0044316E), hook);
	patchCall(reinterpret_cast<void*>(0x004436D6), hook);
	patchCall(reinterpret_cast<void*>(0x004436E2), hook);
	patchCall(reinterpret_cast<void*>(0x00443906), hook);
	patchCall(reinterpret_cast<void*>(0x00443912), hook);
	patchCall(reinterpret_cast<void*>(0x00445100), hook);
	patchCall(reinterpret_cast<void*>(0x00445240), hook);
	patchCall(reinterpret_cast<void*>(0x00445453), hook);
	patchCall(reinterpret_cast<void*>(0x00446206), hook);
	patchCall(reinterpret_cast<void*>(0x0044B417), hook);
	patchCall(reinterpret_cast<void*>(0x0044B427), hook);
	patchCall(reinterpret_cast<void*>(0x0044BCD8), hook);
	patchCall(reinterpret_cast<void*>(0x0044BCE8), hook);
	patchCall(reinterpret_cast<void*>(0x0044C052), hook);
	patchCall(reinterpret_cast<void*>(0x0044C062), hook);
	patchCall(reinterpret_cast<void*>(0x0044C689), hook);
	patchCall(reinterpret_cast<void*>(0x0044D02D), hook);
	patchCall(reinterpret_cast<void*>(0x0044D043), hook);
	patchCall(reinterpret_cast<void*>(0x0044E778), hook);
	patchCall(reinterpret_cast<void*>(0x0044E7DF), hook);
	patchCall(reinterpret_cast<void*>(0x0044E8C6), hook);
	patchCall(reinterpret_cast<void*>(0x0044F48A), hook);
	patchCall(reinterpret_cast<void*>(0x00450756), hook);
	patchCall(reinterpret_cast<void*>(0x0045078C), hook);

	patchCall(reinterpret_cast<void*>(0x00459F57), hook);
	patchCall(reinterpret_cast<void*>(0x0045A854), hook);
	patchCall(reinterpret_cast<void*>(0x0045C2CA), hook);
	patchCall(reinterpret_cast<void*>(0x00467AF0), hook);
	patchCall(reinterpret_cast<void*>(0x00467BB9), hook);
	patchCall(reinterpret_cast<void*>(0x00467E35), hook);
	patchCall(reinterpret_cast<void*>(0x00467E47), hook);
	patchCall(reinterpret_cast<void*>(0x004681C1), hook);
	patchCall(reinterpret_cast<void*>(0x004681D3), hook);
	patchCall(reinterpret_cast<void*>(0x004685D6), hook);
	patchCall(reinterpret_cast<void*>(0x004689E6), hook);
	patchCall(reinterpret_cast<void*>(0x00468A19), hook);
	patchCall(reinterpret_cast<void*>(0x004696D0), hook);
	patchCall(reinterpret_cast<void*>(0x00469CAF), hook);
	patchCall(reinterpret_cast<void*>(0x00469D09), hook);
	patchCall(reinterpret_cast<void*>(0x004741E8), hook);
	patchCall(reinterpret_cast<void*>(0x004745C6), hook);
	patchCall(reinterpret_cast<void*>(0x0047518D), hook);
	patchCall(reinterpret_cast<void*>(0x0047C8F2), hook);
	patchCall(reinterpret_cast<void*>(0x0047C904), hook);
	patchCall(reinterpret_cast<void*>(0x0047DF53), hook);
	patchCall(reinterpret_cast<void*>(0x0047DF65), hook);
	patchCall(reinterpret_cast<void*>(0x0047DFC6), hook);
	patchCall(reinterpret_cast<void*>(0x0047DFD6), hook);
	patchCall(reinterpret_cast<void*>(0x0047DFE8), hook);
	patchCall(reinterpret_cast<void*>(0x0047FA2B), hook);
	patchCall(reinterpret_cast<void*>(0x0047FA3D), hook);
	patchCall(reinterpret_cast<void*>(0x0047FA9E), hook);
	patchCall(reinterpret_cast<void*>(0x0047FAAE), hook);
	patchCall(reinterpret_cast<void*>(0x0047FAC0), hook);
	patchCall(reinterpret_cast<void*>(0x00481851), hook);
	patchCall(reinterpret_cast<void*>(0x00481861), hook);
	patchCall(reinterpret_cast<void*>(0x00481873), hook);
	patchCall(reinterpret_cast<void*>(0x004888C5), hook);
	patchCall(reinterpret_cast<void*>(0x0048C3DD), hook);
	patchCall(reinterpret_cast<void*>(0x0048C3F7), hook);
	// original call 00456E40 


		// check guild war army
	hook = checkgwa_thiswrapper;
	patchCall(reinterpret_cast<void*>(0x00434A5B), hook);
	patchCall(reinterpret_cast<void*>(0x00437853), hook);
	patchCall(reinterpret_cast<void*>(0x004380DC), hook);
	patchCall(reinterpret_cast<void*>(0x00439F9C), hook);
	patchCall(reinterpret_cast<void*>(0x0043BB46), hook);
	patchCall(reinterpret_cast<void*>(0x0047E038), hook);
	patchCall(reinterpret_cast<void*>(0x0047FB10), hook);
	patchCall(reinterpret_cast<void*>(0x004818C3), hook);

	// checkgray	
	hook = User__cgray_thiswrapper;

	patchCall(reinterpret_cast<void*>(0x00434E50), hook);
	patchCall(reinterpret_cast<void*>(0x0043911B), hook);
	patchCall(reinterpret_cast<void*>(0x0043A89C), hook);
	patchCall(reinterpret_cast<void*>(0x0043C409), hook);
	patchCall(reinterpret_cast<void*>(0x0047CDDF), hook);
	patchCall(reinterpret_cast<void*>(0x0047E8DD), hook);
	patchCall(reinterpret_cast<void*>(0x0047E94D), hook);
	patchCall(reinterpret_cast<void*>(0x0048059B), hook);
	patchCall(reinterpret_cast<void*>(0x004806D9), hook);

	// checkgray	
	hook = User__cpk_thiswrapper;

	patchCall(reinterpret_cast<void*>(0x00434C22), hook);
	patchCall(reinterpret_cast<void*>(0x00438F29), hook);
	patchCall(reinterpret_cast<void*>(0x0043A065), hook);
	patchCall(reinterpret_cast<void*>(0x0043BBFC), hook);
	patchCall(reinterpret_cast<void*>(0x0047CACE), hook);
	patchCall(reinterpret_cast<void*>(0x0047CC76), hook);
	patchCall(reinterpret_cast<void*>(0x0047CDC8), hook);
	patchCall(reinterpret_cast<void*>(0x0047E0C4), hook);
	patchCall(reinterpret_cast<void*>(0x0047FB93), hook);



	hook = User__checkspecialattackdelay_wrapper;

	patchCall(reinterpret_cast<void*>(0x47C952), hook);
	patchCall(reinterpret_cast<void*>(0x47D127), hook);
	patchCall(reinterpret_cast<void*>(0x47DB7E), hook);
	patchCall(reinterpret_cast<void*>(0x47F5E9), hook);

	

}




void ServerCodeModifier::installAllBloodyEncodeDecodeHooks(void){
	void* hook = &ServerHookInterface::ENCODE_DECODE_replacement;

	// all hooks
	patchCall(reinterpret_cast<void*>(0x0402FC2), hook);
	patchCall(reinterpret_cast<void*>(0x04030F7), hook);
	patchCall(reinterpret_cast<void*>(0x04031FE), hook);
	patchCall(reinterpret_cast<void*>(0x042BE74), hook);
	patchCall(reinterpret_cast<void*>(0x042BF4F), hook);
	patchCall(reinterpret_cast<void*>(0x042C094), hook);
	patchCall(reinterpret_cast<void*>(0x042C19B), hook);
	patchCall(reinterpret_cast<void*>(0x042C4E8), hook);

}