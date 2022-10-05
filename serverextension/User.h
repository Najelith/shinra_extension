#pragma once
#include <windows.h>
#include <map>
#include <salsa.h>
#include "pktHelpers.h"
#include "EventManager.h"
#include <stdlib.h>
#include <time.h>


extern EventManager* evtmngr;


typedef struct SomaLocation
{
    LONG  x;
    LONG  y;
	LONG  z;
} SOMA_LOC;

class User
{
private:
	BYTE* key;
	DWORD keySize;

	//for wh / guildstash and trace/recall checks
	
	SOMA_LOC lastGuildOpen;
	SOMA_LOC lastGuildStoneOpen;
	SOMA_LOC lastRepairOpen;

	//for speedhack checks
	DWORD stepCounter;
	DWORD stepTimes[2];


	static std::map<void*, User*>* userMap; // used to map real 1p1 userpointer to extention userpointer
public:
	BYTE* realUser;

	SOMA_LOC lastWH;

	std::vector<int> uitems;

	// shadow realm timer
	int srtime;
	// db index
	int dbindex;

	// saved items junk
	 int *tblrType;
	 int *tblsNum;
	 int *tblsRand;
	 int *tblsList;
	 int sRowCount;

	 // speed hack counter
	  int spdhk;

	  // Aura timers
	  int iASpecialAttackDelay[30];

	// guild town wars
	int gtw; // 0 is not in war 1 is in war

	User(BYTE* );
	virtual ~User(void);
	static User* getExtentionUserFromRealUser(void* );
	void setEncryptionKey(BYTE*,int);

	//logcheats
	void logcheat(int type);



	//shadow realm event
	int getsrEvent();
	int setsrEvent();

// load saved items
bool LoadSavedItemTable();
// save the table
bool StoreSavedItemTable();
// distribute items
void checkitemwaitlist();

	bool isWithinRange(SOMA_LOC* location);
	//parse
	void parseVersionResult(BYTE*);
	void parseTakeBackItem(BYTE*);
	void parseSaveItem(BYTE*);
	void parseTakeBackMoney(BYTE*);
	void parseSaveMoney(BYTE*);
	void parseSpecialMove(BYTE*);
	void parseMoveReq(BYTE*);
	void parseRunReq(BYTE*);
	void parseRunFirst(BYTE*);
	void parseRepairItem(BYTE*);

	//guild
	void parseGuildSaveItem(BYTE*);
	void parseGuildTakeBackItem(BYTE*);
	void parseGuildContribution(BYTE*);
	void openGuildTownStone(short);
	void guildOpen();
	void repairItemOpen();
	void sendguildtxt(const char* text);
	//void warguild(int guildnum);

	//logout
	void LogOut(BYTE*);

        // yellow arrow if this doesn't work change to __int16
        void user_diritem(int x1,int y1,int x2,int y2);

	// evt stuff
	int LiveNPC(int, int,signed int,signed int);
	//bool GiveItem(int,int);
	int Selectmsg(const char *,const char *,const char *,const char *,const char *,int,int,int,int);
	int Selectmsg(int intro, int msg1, int opt1evt, int msg2, int opt2evt, int msg3, int opt3evt, int msg4, int opt4evt);
	int selmsg(unsigned int a2);
	//run event by num
	void RunEventByNum(int);

        signed int RunExtEvent(int userpointer, int npcpointer, int evtnum, int zone, EventManager *EvtMngr);
        signed int RunExtEventSection(int userpointer, int npcpointer, EventData* evt, int index, int zone, EventManager *EvtMngr);

        signed int LinkToOtherZone(int zone, int x, int y);
        void SendNpcSay(int npcpointer, int npcchat);
        void RobItem(int itemnum, int ammount);
        void GiveMagic(int num);
        void RobMagic(int num);
        void BBSOpen(int num, int mode);
        void ChangeHP(int type, int amount);
        void ChangeMP(int type, int amount);
        void ChangeSTR(int type, int amount);
        void ChangeDEX(int type, int amount);
        void ChangeINT(int type, int amount);
        void ChangeWIS(int type, int amount);
        void ChangeCHA(int type, int amount);
        void ChangeCON(int type, int amount);
        void MakerOpen(int a1,int a2,int a3,int a4,int a5,int a6);
        void AuctionSellOpen(int a1);
        void AuctionBuyOpen(int a1);
        void MessageOK(int a1);
        void MessageNONE(int a1);
        void GiveGold(int a1);
        void RobGold(int a1);
        void AddEvent(int a1);
        void DelEvent(int a1);
        void ChangeMageType(int a1);
        void GiveSpecialAttack(int a1);
        void KillNpc();
        void PlusMoral(int a1,int a2);
        void OpenContribution(int a1);
        int ChangeStorageType(int a1);
        void AuctionDrawNOBID(int a1);
        void AuctionDrawNOBUY(int a1);
        void AuctionBuyItem(int a1);
        void AuctionGetMoney(int a1);
        void AuctionDeleteBadlist();
        void ChangeMaxHp(int a1, int a2);
        void ChangeMaxMP(int a1, int a2);
        void ChangeMaxSTM(int a1, int a2);
        void ChangeMaxWGT(int a1, int a2);
        void OpenHairShop(int a1, int a2, int a3, int a4);
        int AddServerEvent(int a1);
        int DelServerEvent(int a1);
        void GiveMakeSkill(int a1);
        void OpenSpecialMakeSkill(int a1);
        void RunMagic(int a1);
        void RunSattack(int a1);
        void OpenTrader(int a1, int a2, int a3, int a4, int a5, int a6);
        int OpenChangeItem();
        int CounterStart(int a1, int a2, int a3);
        signed int CounterInit();
        void OpenMonsterSelect();
        signed int TimerStart();
        void TimerInit();
        void SetEventCount(int a1);
        void OpenClassPointStore(int a1);
        void OpenMonsterZone();
        void XmasPointUser();
        void XmasPointGuild();
        void ChangePKMode(int a1);
        void GivePosFromPosItem();
        void setRain(int mode);
        int ExistItem(int a1, int a2);
        int AbsentItem(int a1);
        int ExistItemType(int a1,int a2);
        int AbsentItemType(int a1);
        int FindMagic(int a1);
        int CheckTime(int a1, int a2);
        int RNGRand(int a1);
        signed int CheckGold(int a1,int a2);
        int CheckGameDay (int a1, int a2, int a3);
        bool CheckGameMonth(int a1, int a2);
        int HowMuchItem(int a1, int a2, int a3);
        int Moral(int a1, int a2);
        int CheckMageType( int a1,int a2);
        const char* CheckWeight(int a1, int a2, int a3,
                                int a4, int a5, int a6,
                                int a7, int a8, int a9,
                                int a10, int a11);
        signed int CheckRank(int a1);
       signed int CheckItemSlot(int a1, int a2, int a3,
                                int a4, int a5, int a6,
                                int a7, int a8, int a9,
                                int a10, int a11);
       signed int CheckPosition(int a1, int a2, int a3, int a4, int a5);
       signed int CheckFirstClick();
       signed int CheckStorageType(int a1);
       bool CheckAuctionBadList(int *a1);
       bool CheckAuctionState(int a1);
       int FindSpecialAttack(int a1);
       int MageType(int a1);
       bool CheckAliveNpc(int a1, int a2);
       int FindMakeSkill(int a1);
       bool CheckGuildRank(int a1);
       signed int CompareBasicValue(int a1, int a2, int a3, int a4, int a5, int a6, int a7);
       bool CheckMyJob(int a1);
       signed int CheckGuildTownLevel(int a1, int a2);
       signed int CheckCounter(int a1, int a2);
       signed int CheckTimer(int a1, int a2);
       signed int CheckEventCount(int a1, int a2);
       signed int CheckPayType(int a1);
       bool CheckClassTown();
       bool CheckClassTownWar();
       signed int CheckHaveEventBook();
       signed int CheckEventBook();
       bool CheckPkMode(int a1);
       int CheckPayAccount();
       int PayAccount();



        int getNpcChatByID(int id);

	// check game time 
	/*
	A GAME_TIME [month] [day] [starthour] [endhour]
Checks on the time ingame.

examples:
; checks if time is from 5 to 0 (5 6 7 8 9... 23 0)
A GAME_TIME -1 -1 5 0

; checks if time is from 0 to 23 month 2 and day 10 (so it checks basically if it's day 10 of month 2)
A GAME_TIME 2 10 0 23
	*/
	int CheckGameTime(int month,int day, int starthour, int endhour); //450d00
	// find event
	signed int FindEvent(int);

	// warp gate
	void WarpGate(DWORD,int,int);

	int CheckGuildTown(int );
    int CheckGuildTownAlly(int );
	int CheckGuildTownWar(int a1);

	void OpenGuildTownTaxRate(int);

	void SendStoreOpen(int ,signed int ,signed int ,int );

	// show magic
	void ShowMagic(int,int);
	// give item
	bool GiveItem(int,int);
	// opens shop
	void Open_Guild_Store(int);
	void Open_Guild_Store_Reg(int);
	//direction item
	void dirpoint(int,int,int,int);

        //send all
        void SendAll(unsigned int a2,const void* a3);

	// send global message
	void SendAllMessage(const char* txt);

	bool CheckInvSlot();

	int checkRemainMagic(int unknown);
	int checkRemainSpecialAttack(int unknown);
	bool checkDistByPoint(int x, int y, int distance);
	int move(int x, int y, int gw1 =0, int gw2=0);
	int getStm();
	bool isMapRange(int range);
	void sightRecalc();
	void guildTownWarStart();
	void guildTownWarEnd();
	void classWarStart();
	void classWarEnd();
	void checkSpeedHack(int useless);
	int getItemRangeChange(int notUsed);
	int isMovable_C(int x,int y);
	int decStm();

	// etc

	DWORD PlusFromItem(DWORD a1);

	//other stuffs
	POINT* ConvertToServer(POINT*,DWORD,DWORD,int);
	signed int IsMovable_S(int x,int y);
	void CheckRangeAbility();
	void SendMyInfo(char a2,BYTE a3);

    DWORD CheckDemon(DWORD a1);

    DWORD CheckMonster(DWORD a1);

	
	void sendInsight(unsigned int size, const void *buff);
	void inline Send(DWORD,BYTE*,BOOL);
	void ENCODE_DECODE(int , BYTE*, BYTE*);
	
	DWORD inline KickOut(DWORD);
	void inline warguild(int);
	POINT* convertToClient(POINT* point, DWORD x, DWORD y,int zone);
	
	void sendChangeWgt();
	void sendChatMessage(const char* text);
	void sendGuildChatMessage(const char* text);
	int getMaxWgt();
	int getMaxStm();
	void storageOpen(int unknown);

	// USER.obj


	void DisplayErrorMsg(void* a1);

	int GetItemClass(int sNum);

	int PushItemInventory(void* itemPtr);

	int RecalcWgt();

	int UpdateItemIndex(int itemSlot);
	//int UpdateItemAll(int a2, int a3);
	int UpdateMemUserAll();
	//int UpdateMemItemAll();

	//int UpdateMemItemIndex(int nSlot);

	

	void  Item_WriteItemLog(DWORD itemPtr, int a3, char* a4);

	// USER_NEW.OBJ

	int CheckSuccessSpecialMakeSkill(int a1, int a2);
	

	void deleteItem(DWORD itemPtr);
	int GetMyMaxMakeExp(int a1);
	

	void Item_PlusItemDur(DWORD invItemPtr, int a1);
	void SendDeleteItem(unsigned char unk, int slot);

	void TakeBackItem(BYTE* bypData);

	

	// etc


	void SendCharData(unsigned char bValue, unsigned char unk);

	void SendDevMessage(const char* a1);

	int CheckPlusType(void* CMagicPtr, int a2);

	// stats

	void PlusStr(int a1);
	void PlusDex(int a1);
	void PlusIntel(int a1);
	void PlusCon(int a1);
	void PlusWis(int a1);

	// Item

	void SendItemInfoChange(unsigned char a1, int a2, unsigned char a3);

	// a ton of getters
	
	DWORD GetPlusDex();

	void* GetNpcNID(int npcid);

	BYTE inline getState() 
	{
		return *(BYTE*)(this->realUser + 0x2078);
	}
	
	DWORD inline getIsTrading(){
		return *reinterpret_cast<DWORD*>(this->realUser + 0x745C);
	}

		DWORD inline getRainVal(){
		return *reinterpret_cast<DWORD*>(this->realUser + 0x1CAD);
	}
			DWORD inline getRainVal2(){
		return *reinterpret_cast<DWORD*>(this->realUser + 0x48B8);
	}
					DWORD inline getRainVal3(){
		return *reinterpret_cast<DWORD*>(this->realUser + 0x122E);
	}
        DWORD inline getZone(){
                return *reinterpret_cast<DWORD*>(realUser + 0x725C);
        }
        DWORD inline getDMagic(){
                return *reinterpret_cast<DWORD*>(realUser + 0x728C);
        }
        DWORD inline getWMagic(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7290);
        }
        DWORD inline getBMagic(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7294);
        }
        DWORD inline getSword(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7274);
        }
        DWORD inline getSpear(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7278);
        }
        DWORD inline getAxe(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7280);
        }
        DWORD inline getBow(){
                return *reinterpret_cast<DWORD*>(realUser + 0x727C);
        }
        DWORD inline getKnuckle(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7284);
        }
        DWORD inline getStaff(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7288);
        }
        DWORD inline getWeaponCraft(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7298);
        }
        DWORD inline getArmorCraft(){
                return *reinterpret_cast<DWORD*>(realUser + 0x729C);
        }
        DWORD inline getAccCraft(){
                return *reinterpret_cast<DWORD*>(realUser + 0x72A0);
        }
        DWORD inline getPotionCraft(){
                return *reinterpret_cast<DWORD*>(realUser + 0x72A4);
        }
        DWORD inline getCookingCraft(){
                return *reinterpret_cast<DWORD*>(realUser + 0x72A8);
        }

	// new ones

	CHAR*  getName(){
		return (CHAR*)(realUser + 0x7334);
	}

	DWORD inline  getZoneIndex(){
		return *reinterpret_cast<DWORD*>(realUser + 0x7394);
	}
	
	DWORD inline  getMoral(){
		return *reinterpret_cast<DWORD*>(realUser + 0x722C);
	}

	DWORD inline  getFame() 
	{
		return *reinterpret_cast<DWORD*>(realUser + 0x7248);
	}

	DWORD inline  getGray(){
		return *reinterpret_cast<DWORD*>(realUser + 0x72B0);
	}


	DWORD inline  getClass(){
		return *reinterpret_cast<DWORD*>(realUser + 0x719C);
	}

	DWORD inline  getLevel(){
		return *reinterpret_cast<DWORD*>(realUser + 0x71A0);
	}

	DWORD inline getGuildId(){
		return *(DWORD*)(realUser + 0x7240);
	}

	CHAR*  getGuildName(){
		return (CHAR*)(realUser + 0x7354);
	}

	DWORD inline getClassPoint(){
		return *(DWORD*)(realUser + 0x726C);
	}

	DWORD inline getTotalClassPoint(){
		return *(DWORD*)(realUser + 0x7270);
	}

	DWORD inline getDeathType(){
		return *(DWORD*)(realUser + 0x7220);
	}

	double inline getUnk() 
	{
		return *(double*)(realUser + 0x79E0);
	}

	void inline setUnk(double val)
	{
		*(double*)(realUser + 0x79E0) = val;
	}



	DWORD inline getEventnpcid(){
		return *(DWORD*)(realUser + 0x79EC);
	}
	
	DWORD inline getguildwardead(){
		return *(DWORD*)(realUser + 0x7798);
	}

	DWORD inline getCurrentWeight(){
		return *(DWORD *)(realUser + 0x7218);
	}

	DWORD inline getInventoryItemData(){
		return *(DWORD *)(realUser + 0x70CC);
	}

        BYTE inline getUserTimer(){
                return *(BYTE *)(realUser + 0x7758);
        }

        void inline setUserTimer(BYTE val)
        {
            *(BYTE *)(realUser + 0x7758) = val;
        }

        BYTE inline GetBBSMode(){
                return *(BYTE *)(realUser + 0x201C);
        }

        void inline setBBSMode(BYTE val)
        {
            *(BYTE *)(realUser + 0x201C) = val;
        }

        DWORD inline getGender(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7230);
        }

        DWORD inline getAge(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7224);
        }
        DWORD inline getHP(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7200);
        }

        DWORD inline getMP(){
                return *reinterpret_cast<DWORD*>(realUser + 0x7208);
        }
        DWORD inline getMaxMP(){
                return *reinterpret_cast<DWORD*>(realUser + 0x720C);
        }

	// end of new ones
	DWORD inline getX(){
		return *reinterpret_cast<DWORD*>(realUser + 0x7260);
	}
	DWORD inline getY(){
		return *reinterpret_cast<DWORD*>(realUser + 0x7264);
	}
	DWORD inline getUserServerID(){
		return *reinterpret_cast<DWORD*>(realUser + 0x2074);
	}
	DWORD inline isWarping(){
		return *(DWORD *)(realUser + 0x7750);
	}
	DWORD inline getRunMode(){
		return *(DWORD *)(realUser + 0x7B48);
	}
	DWORD inline getRangeAbility(){
		return *(DWORD *)(realUser + 0x79F4);
	}
	DWORD inline getRangeEffect1(){
		return *(DWORD *)(realUser + 0x79F8);
	}
	DWORD inline getCurrentStamina(){
		return *(DWORD *)(realUser + 0x7210);
	}
	DWORD inline getDirection(){
		return *(DWORD *)(realUser + 0x7738);
	}
	DWORD inline isInGuildWar(){
		return *(DWORD *)(realUser + 0x7790);
	}
		DWORD inline getGuildWar(){
		return *(DWORD *)(realUser + 0x778C);
	}
		DWORD inline getGuildWarNum(){
		return *(DWORD *)(realUser + 0x7794);
	}
		DWORD inline getGuildWarb(){
		return *(DWORD *)(realUser + 0x779C);
	}
		DWORD inline getGuildWarvill(){
		return *(DWORD *)(realUser + 0x7B4C);
	}

	DWORD inline getGuildRank(){
		return *(DWORD *)(realUser + 0x734C);
	}
	DWORD inline isPreMagicCasted (){
		return *(DWORD *)(realUser + 0x2028);
	}


	DWORD inline getStr()
	{
		return *(DWORD*)(realUser + 0x71B8);
	}

	DWORD inline getStrInc()
	{
		return *(DWORD*)(realUser + 0x71BC);
	}

	DWORD inline getDex()
	{
		return *(DWORD*)(realUser + 0x71C0);
	}

	DWORD inline getDexInc()
	{
		return *(DWORD*)(realUser + 0x71C4);
	}

	DWORD inline getInt()
	{
		return *(DWORD*)(realUser + 0x71C8);
	}

        DWORD inline getCha()
        {
                return *(DWORD*)(realUser + 0x71D0);
        }
        DWORD inline getWis()
        {
                return *(DWORD*)(realUser + 0x71D8);
        }


	DWORD inline getIntInc()
	{
		return *(DWORD*)(realUser + 0x71CC);
	}

	DWORD inline getWisInc()
	{
		return *(DWORD*)(realUser + 0x71DC);
	}

	DWORD inline getCon()
	{
		return *(DWORD*)(realUser + 0x71E0);
	}

	DWORD inline getConInc()
	{
		return *(DWORD*)(realUser + 0x71E4);
	}

	DWORD inline getMaxHP()
	{
		return *(DWORD*)(realUser + 0x7204);
	}

	DWORD inline getAttackDelay()
	{
		return *(DWORD*)(realUser + 0x77F8);
	}

	DWORD inline getDexUnk()
	{
		return *(DWORD*)(realUser + 0x7BC8);
	}

	DWORD inline getDexUnk2()
	{
		return *(DWORD*)(realUser + 0x7BCC);
	}

	DWORD inline getASUnk() // CheckAttackSuccess
	{
		return *(DWORD*)(realUser + 0x7954);
	}	
};


void User::warguild(int guildnum){

	//DWORD gvwpointer = *reinterpret_cast<DWORD*>(this->realUser + 0x7B4C);

	// guildnum guide, 1 = defender, 2 = attacker, -1 = not in war

		DWORD offset = 0;
		DWORD nval = guildnum;
		SetInt(realUser + 0x7B4C, nval, &offset);
    SendMyInfo( 4, 1u);
		//offset =0;
	//	SetInt(realUser + 0x779c, 0, &offset);
	//	_asm{
	//		mov DWORD PTR DS:[gvwpointer],nval
	
	//	}


	/*	BYTE* p = reinterpret_cast<BYTE*>(this->realUser);
		p += 0x7B4C;
		*p= guildnum;
				BYTE* pq = reinterpret_cast<BYTE*>(this->realUser);
		pq += 0x779c;
		*pq= guildnum;

						BYTE* ppq = reinterpret_cast<BYTE*>(this->realUser);
		ppq += 0x7794;
		*ppq= guildnum;
		
								BYTE* pqq = reinterpret_cast<BYTE*>(this->realUser);
		pqq += 0x7798;
		*pqq= 0;//0;

						BYTE* p1q = reinterpret_cast<BYTE*>(this->realUser);
		p1q += 0x778c;
		*p1q= guildnum;

							BYTE* p2q = reinterpret_cast<BYTE*>(this->realUser);
		p2q += 0x7790;
		*p2q= guildnum; */
		//nval = 1;
/*		offset = 0;
		SetInt(realUser + 0x7790, 0, &offset);

		offset = 0;
		SetInt(realUser + 0x778c, 0, &offset);

		//nval = 1;
		offset = 0;
		SetInt(realUser + 0x7790,1, &offset);

		//nval = 2;
		offset = 0;
		SetInt(realUser + 0x7794, 2, &offset);
		*/
}



DWORD User::KickOut(DWORD type){
	void (__thiscall *LogOut)(DWORD realUser, DWORD type) = ((void (__thiscall *)(DWORD, DWORD))0x42FE90);
		LogOut(reinterpret_cast<DWORD>(realUser), type);
		
		DWORD socketPointer = *reinterpret_cast<DWORD*>(this->realUser + 0x2070);
		DWORD rtn = 0;
		_asm{
			mov edx,socketPointer
			push edx
			call DWORD PTR DS:[4B75ECh] ; closesocket
			mov rtn,eax
		}
		BYTE* p = reinterpret_cast<BYTE*>(this->realUser);
		p += 0x2078;
		*p= 3;
		return rtn;
}



/*
struct st_CUser
{
	int SpecialAttackValues[20]; // 0x78EC
};*/