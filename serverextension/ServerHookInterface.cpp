#include <windows.h>
#include "StdAfx.h"
#include "ServerHookInterface.h"
#include <iostream>
#include <salsa.h>
#include "User.h"
//#include <SQLAPI.h> // main SQLAPI++ header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include <comdef.h>
#include <vector>
#include "./include/gsodbc.h"

#include "Npc.h"
#include "Hook.h"
#include "PacketDef.h"
#include "MyDatabase.h"
#include "Util.h"



//defenitions i guess
 std::vector<User*> uarray;

 // initalized?
 int intinit;
 // counters for guild town  wars 
 int gtw1; 
 int gtw2;
 // guild town war cool down
 int gtwc1;
 int gtwc2;
 // guild town upgrades
 int itemgt1;
 int itemgt2;
 // guild town tax
 int gt1tax;
 int gt2tax;


 // guild nums that are attacking each town
  std::vector<int> gt1;
  std::vector<int> gt2;

  int a[3];
  int k;

  //can't have nice things
  EventManager* evtmngr = 0;// = new EventManager();



ServerHookInterface::ServerHookInterface(void)
{

	intinit = 0; // not initalized
	itemgt1 = 0;
	itemgt2 = 0;
	gtw1 = 0;
	gtw2 = 0;
	gtwc1 = 0;
	gtwc2 = 0;
	gt1tax =0;
	gt2tax =0;
	
	evtmngr = NULL; //evtmngr = new EventManager();

 

}


ServerHookInterface::~ServerHookInterface(void) 
{
	// destructor 
	//printf("Destructor\n...\n...\n...\nExiting!");
}


__int16 __cdecl ServerHookInterface::ENCODE_DECODE_replacement(void* userPointer, unsigned int keyPartTwo, int size, BYTE *src, BYTE *dst){
	if(size > 0)
	{
		User* extUser = User::getExtentionUserFromRealUser(userPointer);
		extUser->ENCODE_DECODE(size,src,dst);
		/*
		BYTE key[16];
		//memset(key,0,16);
		memcpy(key,reinterpret_cast<BYTE*>(0x5092C0),8);
		memcpy(key + 8,&keyPartOne,4);
		memcpy(key + 12,&keyPartTwo,4);
		
		//key done
		//memcpy(dst,src,size);
		CryptoPP::Salsa20::Encryption enc(key,16,key);
		enc.ProcessString(dst,src,size);
#ifdef RAUBAN_DEBUG
		printf("encrypt/decrypt using key:\n");
		printLine(key,16);
		printf("src:\n");
		printLine(src,size);
		printf("dst:\n");
		printLine(dst,size);
		printf("size: %d\n",size);
#endif
		*/
	}
	return 0;
}

void __stdcall ServerHookInterface::User__version_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseVersionResult(packetToParse);
}

int ServerHookInterface::pkposget(int slv, int tlv, int spos, int tpos){
	int pos = 0;
	int lvdiff = tlv - slv;

	if(slv <= 15 || tlv <=15 || tpos == -2000){
	return pos;
	}

	switch(lvdiff){
	case 0:
		pos = 0x1F4;
	break;
		case 1:
		pos = 0x208 ;
	break;
		case 2:
		pos = 0x21C;
	break;
		case 3:
		pos = 0x230;
	break;
		case 4:
		pos = 0x244;
	break;
		case 5:
		pos = 0x258;
	break;
		case 6:
		pos = 0x26C;
	break;
		case 7:
		pos = 0x280                                ;
	break;
		case 8:
		pos = 0x294                                ;
	break;
		case 9:
		pos = 0x2A8                                ;
	break;
		case 10:
		pos = 0x2BC                                ;
	break;
		case 11:
		pos = 0x2D0                                ;
	break;
		case 12:
		pos = 0x2E4                                ;
	break;
		case 13:
		pos = 0x2F8                                ;
	break;
		case 14:
		pos = 0x30C                                ;
	break;
		case 15:
		pos = 0x320                                ;
	break;
		case 16:
		pos = 0x334                                ;
	break;
		case 17:
		pos = 0x348                                ;
	break;
		case 18:
		pos = 0x35C                                ;
	break;
		case 19:
		pos = 0x370                                ;
	break;
		case 20:
		pos = 0x384                                ;
	break;
		case 21:
		pos = 0x398                                ;
	break;
		case 22:
		pos = 0x3AC                                ;
	break;
		case 23:
		pos = 0x3C0                                ;
	break;
		case 24:
		pos = 0x3D4                                ;
	break;
		case 25:
		pos = 0x3E8                                ;
	break;
	case -1:
		pos = 0x1E0                                ;
	break;
		case -2:
		pos = 0x1CC                                ;
	break;
		case -3:
		pos = 0x1B8                                ;
	break;
		case -4:
		pos = 0x1A4                                ;
	break;
		case -5:
		pos = 0x190                                ;
	break;
		case -6:
		pos = 0x17C                                ;
	break;
		case -7:
		pos = 0x168                                ;
	break;
		case -8:
		pos = 0x154                                ;
	break;
		case -9:
		pos = 0x140                                ;
	break;
		case -10:
		pos = 0x12C                                ;
	break;
		case -11:
		pos = 0x118                                ;
	break;
		case -12:
		pos = 0x104                                ;
	break;
		case -13:
		pos = 0x0F0                                ;
	break;
		case -14:
		pos = 0x0DC                                ;
	break;
		case -15:
		pos = 0x0C8                                ;
	break;
		case -16:
		pos = 0x0B4                                ;
	break;
		case -17:
		pos = 0x0A0                                ;
	break;
		case -18:
		pos = 0x8C                                 ;
	break;
		case -19:
		pos = 0x78                                 ;
	break;
		case -20:
		pos = 0x64                                 ;
	break;
		case -21:
		pos = 0x50                                 ;
	break;
		case -22:
		pos = 0x3C                                 ;
	break;
		case -23:
		pos = 0x28;
	break;
		case -24:
		pos = 0x14;
	break;
		case -25:
		pos = 0x0A;
	break;
	default:
		pos = 0x0A;
		if(lvdiff >25){pos = 0x5DC;}
	break;
	} 
	
	tpos = tpos - pos; 
	if(tpos < -2000){
	pos = pos + tpos + 2000;
	}
		return pos;
}

int ServerHookInterface::pklog(const char* source,const char* target,int pos, int type){



	    CGOdbcConnect cCon;
    try
    {
        cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);
		
    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return 0;
    }

    //printf("Driver: %s\n", cCon.getDriver());

	char szQuery[300];
	
	//sprintf(szQuery, "Insert into pklog (sourcename, targetname, pos,type) values ('%s', '%s','%d','%d')",source,target,pos,type);

	sprintf(szQuery, "{call proc_pklog ('%s', '%s','%d','%d')}",source,target,pos,type);
	 

    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
	//	    printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        printf("Insert Error\n%s\n", pE->getMsg());
        return 0;
    }

	 	  try
    {
        if (!pCur->bindAuto())
        {
            printf("cursor doesn't contain resultset\n");
            return 0;
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("binding error\n%s\n", pE->getMsg());
        return 0;
    }

    int totalcount;
       char strmessage[91];
	try
    {
        bool bRC;
        for (bRC = pCur->first(); bRC; bRC = pCur->next())
        {
          /*  printf("%i '%s'", i = pCur->getInt("id"), pCur->getChar("name"));
            //verify long fields
            const char *pBuff;
            int iLen;
            iLen = pCur->getLength("descript");
            printf(" %i", iLen);
            pBuff = pCur->getChar("descript");
            for (j = 0; j < iLen; j++)
            {
                if (pBuff[j] == i + '0' + j % 10)
                    continue;
                else
                {
                    printf("!%i", j);
                    break;
                }
            }
            pBuff = (const char *)pCur->getPtr("binid");
            iLen = pCur->getLength("binid");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != i + j)
                {
                    printf("!%i", j);
                    break;
                }

            pBuff = (const char *)pCur->getPtr("contents");
            iLen = pCur->getLength("contents");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != j % 10 + 30 + i)
                {
                    printf("!%i", j);
                    break;
                }
            printf(" %s ", pCur->getChar("a1"));
            printf(" %s ", pCur->getChar("a2"));
            printf(" %s ", pCur->getChar("stamp"));

            printf("\n"); */
			totalcount = pCur->getInt("total");
			//printf("total kill count: %d \n",totalcount);

        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("load cursor error\n%s\n", pE->getMsg());
        return 0;
    }
        

    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();



	//	printf("\n%s has been killed by %s and lost %d pos", target ,source,pos);
	
	
	// trysql
/*	  SAConnection con; // connection object
    SACommand cmd;    // create command object

	 try
	 {
		
        // connect to database (Oracle in our example)
	
        con.Connect("snnm", "pantea", "luft56", SA_SQLServer_Client);
        // associate a command with connection 
        // connection can also be specified in SACommand constructor
        cmd.setConnection(&con);

        // create table
      //  cmd.setCommandText(
      //      "Create table test_tbl(fid integer, fvarchar20 varchar(20), fblob blob)");
      //  cmd.Execute();

        // insert value
		
		
		//std::string stmnt;
		//stmnt.Append((const CHAR*)susr->getName());
		 SAString sfu;
		//stmnt= "Insert into pklog (sourcename, targetname, pos) values ('";
		//stmnt += susr->getName();
		//stmnt += "','";
		//stmnt += tusr->getName();
		//stmnt += "','";
		//stmnt += pos;
		//stmnt += "')"; 

		 sfu.Format("Insert into pklog (sourcename, targetname, pos,type) values ('%s', '%s','%d','%d')",source,target,pos,type);
	
        cmd.setCommandText(
           sfu);// "Insert into pklog (sourcename, targetname, pos) values ('tester', 'testing','tested')");
        cmd.Execute();

        // commit changes on success
        con.Commit();
		
    
    }
    catch(SAException &x)
	{
        // SAConnection::Rollback()
        // can also throw an exception
        // (if a network error for example),
        // we will be ready
        try
        {
            // on error rollback changes
            con.Rollback();
        }
        catch(SAException &)
        {
        }
        // print error message
        printf("%s\n", (const char*)x.ErrText());
    
	
	

}*/
		return totalcount;
}



	void __stdcall ServerHookInterface::User__load_user_data_wrapper(void* sourcePointer,void* unknown){
		User* susr = User::getExtentionUserFromRealUser(sourcePointer);
//	printf("%s load user data requestT! \n",susr->getName());

	// call 1p1 function to handel the rest
void (__thiscall *userdata)(DWORD sourcePointer,DWORD unknown) = ((void (__thiscall *)(DWORD,DWORD))0x00431230); 
	userdata(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(unknown));

}

void __stdcall ServerHookInterface::User__LoginReq_wrapper(void* sourcePointer,void* unknown)
{
		User* susr = User::getExtentionUserFromRealUser(sourcePointer);
//	printf("%s LOGIN REQUEST! \n",susr->getName());

	// call 1p1 function to handel the rest
void (__thiscall *userdata)(DWORD sourcePointer,DWORD unknown) = ((void (__thiscall *)(DWORD,DWORD))0x0042F2E0); 

	userdata(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(unknown));

	//printf("%s EXIT LOGIN REQUEST! \n",susr->getName());

}



void __stdcall ServerHookInterface::User__ReloadEvent_wrapper(void* unknown,void* unknown2,void* unknown3){
		
	printf(" ->Reload Events! \n"); // remove this when debug is over
         evtmngr->LoadEvents();
	// call 1p1 function to handel the rest
   void (__thiscall *rEvent)(DWORD unknown,DWORD unkown2) = ((void (__thiscall *)(DWORD,DWORD))0x00404BF0);  
	rEvent(reinterpret_cast<DWORD>(unknown),reinterpret_cast<DWORD>(unknown2));

	//void (__thiscall *rEvent)(DWORD unknown,DWORD unkown2,DWORD unkown3) = ((void (__thiscall *)(DWORD,DWORD,DWORD))0x004A75FF);  
	//rEvent(reinterpret_cast<DWORD>(unknown),reinterpret_cast<DWORD>(unknown2),reinterpret_cast<DWORD>(unknown3));
	//printf("%s EXIT Send My Info REQUEST! \n",susr->getName()); // remove this when debug is over

}

void __stdcall ServerHookInterface::User__Send_My_Info_wrapper(void* sourcePointer,void* unknown){
		User* susr = User::getExtentionUserFromRealUser(sourcePointer);
	//printf("%s Send My Info REQUEST! \n",susr->getName()); // remove this when debug is over

	// call 1p1 function to handel the rest
void (__thiscall *userdata)(DWORD sourcePointer,DWORD unknown) = ((void (__thiscall *)(DWORD,DWORD))0x0042DC70); 
	userdata(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(unknown));

	//printf("%s EXIT Send My Info REQUEST! \n",susr->getName()); // remove this when debug is over

}


void __stdcall ServerHookInterface::User__check_monster_wrapper(void* sourcePointer,void* unknown){
	//	User* susr = User::getExtentionUserFromRealUser(sourcePointer);
//	printf("%s has triggered check monster! \n",susr->getName());

	// call 1p1 function to handel the rest
void (__thiscall *userdata)(DWORD sourcePointer,DWORD unknown) = ((void (__thiscall *)(DWORD,DWORD))0x00456E40); 
	userdata(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(unknown));

}
void __stdcall ServerHookInterface::User__NEWHERO_wrapper(void* sourcePointer,void* unknown){
		User* susr = User::getExtentionUserFromRealUser(sourcePointer);
	//printf("%s has triggered new hero! \n",susr->getName());

	// call 1p1 function to handel the rest
void (__thiscall *userdata)(DWORD sourcePointer,DWORD unknown) = ((void (__thiscall *)(DWORD,DWORD))0x00445080); 
	userdata(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(unknown));

}
void __stdcall ServerHookInterface::User__EXISTCHAR_wrapper(void* sourcePointer,void* unknown){
		User* susr = User::getExtentionUserFromRealUser(sourcePointer);
	//printf("%s has triggered existchar?! \n",susr->getName());

	// call 1p1 function to handel the rest
void (__thiscall *userdata)(DWORD sourcePointer,DWORD unknown) = ((void (__thiscall *)(DWORD,DWORD))0x0044e400); 
	userdata(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(unknown));

}

void __stdcall ServerHookInterface::User__GETDATA_wrapper(void* unknown1,void* unknown){

	//printf(" GET Monster Soma Data Table? \n");

	// call 1p1 function to handel the rest
void (__thiscall *monsterdata)(DWORD unknown1,DWORD unknown) = ((void (__thiscall *)(DWORD,DWORD))0x00428780); 
	monsterdata(reinterpret_cast<DWORD>(unknown1),reinterpret_cast<DWORD>(unknown));

}

void __stdcall ServerHookInterface::User__LOADDATA_wrapper(void* sourcePointer,void* unknown){
	User* susr = User::getExtentionUserFromRealUser(sourcePointer);
	//printf("%s has triggered load data! \n",susr->getName());

	// call 1p1 function to handel the rest
void (__thiscall *userdata)(DWORD sourcePointer,DWORD unknown) = ((void (__thiscall *)(DWORD,DWORD))0x00431230); 
	userdata(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(unknown));

}

void __stdcall ServerHookInterface::User__cevent_wrapper(void* sourcePointer,void* unknown){
	User* susr = User::getExtentionUserFromRealUser(sourcePointer);


DWORD  ievent;
ievent= *reinterpret_cast<DWORD*>((BYTE*)unknown);


//printf("%s has triggered cevent type: %x and %d\n",susr->getName(),((BYTE*)unknown)[0],(int)ievent);//(CHAR*)((BYTE*)unknown + 0x194  + 0x400));

int idx =0;
// call 1p1 function to get npc pointer?
/*
BYTE (__thiscall *getbyte)(DWORD sourcePointer,int& index) = ((BYTE (__thiscall *)(DWORD,int&))0x00407330); //getnpcnid 447e30
BYTE b = getbyte(reinterpret_cast<DWORD>(sourcePointer),idx);
*/

	BYTE b = (BYTE)(*((char*)unknown+idx));
	idx++;
	//add check here for type
//printf("getbyte emulated has returned: %x and %d\n",b,idx);//(CHAR*)((BYTE*)unknown + 0x194  + 0x400));
//see if it's destructive

    idx += 4;
	int npcref = *(int*)((char*)unknown+idx-4);
	short npcrefsh = *(short*)((char*)unknown+idx-4);
	//add check here to see if it fallsbetween user bound <= ref and ref <npc_band (10,000) 
//printf("ref as int: %d as short %d npcevent IDint: %d npcevent IDsh: %d\n",npcref, npcrefsh,npcref-10000,npcrefsh-10000);
if ( npcref < 30000 && npcref >= 10000){
// call 1p1 function to get npc pointer? assume int
void *(__thiscall *getnpcnid)(DWORD sourcePointer, int) = ((void *(__thiscall *)(DWORD,int))0x00447E30); //getnpcnid 447e30
void* cNpc = getnpcnid(reinterpret_cast<DWORD>(sourcePointer),npcref-10000);
/*
// call 1p1 function to get npc pointer? assume short
void *(__thiscall *getnpcnid)(DWORD sourcePointer, int) = ((void *(__thiscall *)(DWORD,int))0x00447E30); //getnpcnid 447e30
void* cNpc = getnpcnid(reinterpret_cast<DWORD>(sourcePointer),-10000);
*/
//printf("%s npcevent ID: %d\n ",(CHAR*)((BYTE*)cNpc + 0x194),npcref-10000);
// set npc pointer
susr->plastnpc = (int) cNpc;

//DWORD  ievent;
	ievent= *reinterpret_cast<DWORD*>((BYTE*)cNpc + 0x3A0);
	if((int)ievent >0)
	{
	// event manager look up test
	//	printf("EVENT MANAGER LOOK UP\n");
		//can't have nice things
	 // EventManager* evtmngr = new EventManager();
	//	printf("EVENT %d on ZONE %d :\n",(int)ievent,(int)susr->getZone());
		if(evtmngr != NULL)
		{
		EventData* evt = evtmngr->GetEventData((int)susr->getZone(),(int)ievent);
			if(evt)
			{ // not null



					  susr->RunExtEvent((int)sourcePointer, (int)cNpc,(int)ievent,(int)susr->getZone(),evtmngr);
					  return;
			}
			else
			{
				printf("EVENT %d on ZONE %d NOT FOUND!\n",(int)ievent,(int)susr->getZone());
			}

		}
		else{
		   printf("EVENT Manager NOT INITILIZED!\n");
		}

	}
}
// call 1p1 function to handel the rest
void (__thiscall *clientevent)(DWORD sourcePointer,DWORD npcpointer) = ((void (__thiscall *)(DWORD,DWORD))0x0044CED0); // clientevent
//void (__thiscall *clientevent)(DWORD sourcePointer,DWORD npcpointer) = ((void (__thiscall *)(DWORD,DWORD))0x00468A40); //runeventbynum
//void (__thiscall *clientevent)(DWORD sourcePointer,DWORD npcpointer) = ((void (__thiscall *)(DWORD,DWORD,DWORD))0x0043DEF0); //runevent
	clientevent(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(unknown));
}

	void __stdcall ServerHookInterface::User__runeventbynum_wrapper(void* sourcePointer, int eventnum){
	User* susr = User::getExtentionUserFromRealUser(sourcePointer);

	//printf("%s has triggered runeventbynum Eventnum: %d\n",susr->getName(),eventnum);

        if((int)eventnum >0){
        // event manager look up test
              //  printf("EVENT MANAGER LOOK UP\n");
                //can't have nice things
         // EventManager* evtmngr = new EventManager();
              //  printf("EVENT %d on ZONE %d :\n",(int)eventnum,(int)susr->getZone());
                if(evtmngr != NULL)
				{
                EventData* evt = evtmngr->GetEventData((int)susr->getZone(),(int)eventnum);
                        if(evt){ // not null
                          susr->RunExtEvent((int)sourcePointer,0,(int)eventnum,(int)susr->getZone(),evtmngr);
                          return;
                        }

                       else{
                        printf("EVENT %d on ZONE %d NOT FOUND!\n",(int)eventnum,(int)susr->getZone());
                        }

                }
                else{
                   printf("EVENT Manager NOT INITILIZED!\n");
                }

        }

// call 1p1 function to handel the rest
void (__thiscall *runnpcevent)(DWORD sourcePointer, int) = ((void (__thiscall *)(DWORD,int))0x00468A40); //runevent
runnpcevent(reinterpret_cast<DWORD>(sourcePointer),eventnum);
return;

}

void __stdcall ServerHookInterface::User__npcevent_wrapper(void* sourcePointer,void* npcPointer, int eventnum){
	User* susr = User::getExtentionUserFromRealUser(sourcePointer);

//DWORD  ievent;
//ievent= *reinterpret_cast<DWORD*>((BYTE*)npcPointer + 0x3A0);
	DWORD  ihp;
	ihp= *reinterpret_cast<DWORD*>((BYTE*)npcPointer + 0x26c);
		DWORD  icandie;
	icandie= *reinterpret_cast<DWORD*>((BYTE*)npcPointer + 0x184);
if (ihp == 0 || !(icandie == 1)){
//printf("%s has triggered %s npcevent Eventnum: %d\n",susr->getName(),(CHAR*)((BYTE*)npcPointer + 0x194),eventnum);


if((int)eventnum >0){
// event manager look up test
      //  printf("EVENT MANAGER LOOK UP\n");
        //can't have nice things
 // EventManager* evtmngr = new EventManager();
      //  printf("EVENT %d on ZONE %d :\n",(int)eventnum,(int)susr->getZone());
        if(evtmngr != NULL){
        EventData* evt = evtmngr->GetEventData((int)susr->getZone(),(int)eventnum);
                if(evt){ // not null
                  susr->RunExtEvent((int)sourcePointer, (int)npcPointer,(int)eventnum,(int)susr->getZone(),evtmngr);
                  return;
                }

               else{
                printf("EVENT %d on ZONE %d NOT FOUND!\n",(int)eventnum,(int)susr->getZone());
                }

        }
        else{
           printf("EVENT Manager NOT INITILIZED!\n");
        }

}


// call 1p1 function to handel the rest
void (__thiscall *runnpcevent)(DWORD sourcePointer,DWORD npcPointer, int) = ((void (__thiscall *)(DWORD,DWORD,int))0x0043DEF0); //runevent
runnpcevent(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(npcPointer),eventnum);
return;
}
if(ihp != 0) {
//	printf("%s has been cheating source client; hp:%d candie:%d\n",susr->getName(),ihp,icandie);
}


}



void __stdcall ServerHookInterface::User__npcdead_wrapper(void* sourcePointer,void* npcpointer){
	User* susr = User::getExtentionUserFromRealUser(sourcePointer);


DWORD  ievent;
ievent= *reinterpret_cast<DWORD*>((BYTE*)npcpointer + 0x3A0);


//printf("%s has triggered %s npcdeadevent Eventnum: %d\n",susr->getName(),(CHAR*)((BYTE*)npcpointer + 0x194),(int)ievent);

if(strncmp((CHAR*)((BYTE*)npcpointer + 0x194),"Susa ", 5) == 0 ){
	// check if war is started or not and check cool down
	if (gtwc1 <= 0 && !susr->CheckGuildTown(14) && !susr->CheckGuildTownAlly(14)){
	//start war 
		if (gtw1 <=0){
			gtw1 = 60;
		  gtwc1 = 420;
		} // init the time if it's not set
				char atkmes[100];
		sprintf(atkmes,"<<< An attack on Susa has been initiated by %s of %s guild. >>>",susr->getName(),susr->getGuildName());
		susr->SendAllMessage(atkmes);
		
	//	susr->warguild(2);

			std::vector<User*>::iterator i;
		int j = 0;
	 for ( i =uarray.begin(); i<uarray.end(); i++){
		 
		// printf("gtw1 atk->%s",uarray[j]->getName());
	
		 if(uarray[j]->CheckGuildTown(14) || uarray[j]->CheckGuildTownAlly(14)){
			//  printf(" (guild owner/ally)\n");
			 uarray[j]->gtw = 1;
			 uarray[j]->warguild(1);
		 }  // set the war status

		 if(uarray[j]->getGuildId() == susr->getGuildId() ){
			//  printf(" (attacker's guild)\n");
			 uarray[j]->gtw = 1;
			 uarray[j]->warguild(2);
		 }
			 j++;
	 }
	 gt1.insert(gt1.begin(),susr->getGuildId());
	}

	if(gtw1 <= 0){

		char atkfmes[100];

		if(susr->CheckGuildTown(14) || susr->CheckGuildTownAlly(14)){

		sprintf(atkfmes,"<<< You cannot initiate wars with allied towns >>>");
		susr->sendChatMessage(atkfmes);	
		}

		if(gtwc1 > 0 ){
			int hours=0, mins=0;
			if (gtwc1 >= 360){
			 hours = gtwc1/360;
			 mins = (gtwc1 - (hours*360))/6;
			}
			else{
			 hours = 0;
			 mins = gtwc1/6;
			}

		sprintf(atkfmes,"<<< This town cannot be attack for aprpoximately %d hours, %d mins. >>>",hours,mins);
		susr->sendChatMessage(atkfmes);	
		} 
			
	//idiot respawn!
	susr->LiveNPC(40253,-1, -1, -1);
	susr->LiveNPC(40255,-1, -1, -1);
	susr->LiveNPC(40256,-1, -1, -1);
	susr->LiveNPC(40257,-1, -1, -1);
	susr->LiveNPC(40258,-1, -1, -1);

	}


}

if(strncmp((CHAR*)((BYTE*)npcpointer + 0x194),"Dina ", 5) == 0 ){

		// check if war is started or not and check cool down
	if (gtwc2 <= 0 && !susr->CheckGuildTown(15) && !susr->CheckGuildTownAlly(15)){
	//start war 
		if (gtw2 <=0){
			gtw2 = 60;
		 gtwc2 = 420;
		} // init the time if it's not set
		char atkmes[100];
		sprintf(atkmes,"<<< An attack on Dina has been initiated by %s of %s guild. >>>",susr->getName(),susr->getGuildName());
		susr->SendAllMessage(atkmes);
		//susr->warguild(2);

			std::vector<User*>::iterator i;
		int j = 0;
	 for ( i =uarray.begin(); i<uarray.end(); i++){
		 
	   //    printf("gtw2 atk->%s",uarray[j]->getName());

		 if(uarray[j]->CheckGuildTown(15) || uarray[j]->CheckGuildTownAlly(15)){
		//	  printf(" (owner/ally)\n");
			 uarray[j]->gtw = 1;
			 uarray[j]->warguild(1);
		 }  // set the war status
		 
		 if(uarray[j]->getGuildId() == susr->getGuildId() ){
		//	  printf(" (atk guild)\n");
			 uarray[j]->gtw = 1;
			 uarray[j]->warguild(2);
		 }

			 j++;
	 }
	 gt2.insert(gt2.begin(),susr->getGuildId());
	}
	if( gtw2 <= 0){

		char atkfmes[100];

		if(susr->CheckGuildTown(15) || susr->CheckGuildTownAlly(15)){

		sprintf(atkfmes,"<<< You cannot initiate wars with allied towns >>>",susr->getName(),susr->getGuildName());
		susr->sendChatMessage(atkfmes);	
		}

		if(gtwc2 > 0){
			int hours=0, mins=0;

			if (gtwc2 >= 360){
			 hours = gtwc2/360;
			 mins = (gtwc2 - (hours*360))/6;
			}
			else{
			 hours = 0;
			 mins = gtwc2/6;
			}

		sprintf(atkfmes,"<<< This town cannot be attack for aprpoximately %d hours, %d mins. >>>",hours,mins);
		susr->sendChatMessage(atkfmes);	
		} 

	// idiot! respawn
	susr->LiveNPC(40254,-1, -1, -1);
    susr->LiveNPC(40263,-1, -1, -1);
	susr->LiveNPC(40264,-1, -1, -1);
	susr->LiveNPC(40265,-1, -1, -1);
	susr->LiveNPC(40266,-1, -1, -1);
	}

}


if(strncmp((CHAR*)((BYTE*)npcpointer + 0x194),"Shadowd", 7) == 0 ){

 CGOdbcConnect cCon;
    try
    {
        cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);
	
    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return;
    }

    //printf("Driver: %s\n", cCon.getDriver());

	char szQuery[91];
	
	 sprintf(szQuery,"{call checkevent ('%s')}",susr->getName());

      // sprintf(szQuery, "Insert into monlog (struser,strmon) values ('%s', '%s')",susr->getName(),that);
	 

    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
		    //printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        printf("Insert Error\n%s\n", pE->getMsg());
        return;
    }

	  try
    {
        if (!pCur->bindAuto())
        {
            printf("cursor doesn't contain resultset\n");
            return;
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("binding error\n%s\n", pE->getMsg());
        return;
    }

    int status;
	int hours;
	int mins;
	int sec;
       char strmessage[91];
	try
    {
        bool bRC;
        for (bRC = pCur->first(); bRC; bRC = pCur->next())
        {
          /*  printf("%i '%s'", i = pCur->getInt("id"), pCur->getChar("name"));
            //verify long fields
            const char *pBuff;
            int iLen;
            iLen = pCur->getLength("descript");
            printf(" %i", iLen);
            pBuff = pCur->getChar("descript");
            for (j = 0; j < iLen; j++)
            {
                if (pBuff[j] == i + '0' + j % 10)
                    continue;
                else
                {
                    printf("!%i", j);
                    break;
                }
            }
            pBuff = (const char *)pCur->getPtr("binid");
            iLen = pCur->getLength("binid");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != i + j)
                {
                    printf("!%i", j);
                    break;
                }

            pBuff = (const char *)pCur->getPtr("contents");
            iLen = pCur->getLength("contents");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != j % 10 + 30 + i)
                {
                    printf("!%i", j);
                    break;
                }
            printf(" %s ", pCur->getChar("a1"));
            printf(" %s ", pCur->getChar("a2"));
            printf(" %s ", pCur->getChar("stamp"));

            printf("\n"); */
			status = pCur->getInt("status");
			hours = pCur->getInt("hour");
			mins = pCur->getInt("mins");
			sec = pCur->getInt("sec");
			//printf("Event status: %d \n",status);
			
		if (!status){
		     sprintf(strmessage,"<<< You must wait %d hours, %d minutes, %d seconds (real life time) before you can continue. >>>",hours,mins,sec);
			susr->sendChatMessage(strmessage);
		}
		else
		{
		// call 1p1 function to handel the rest
			susr->srtime = 360;
			
			if((int)ievent >0)
			{
				// event manager look up test
                //  printf("EVENT MANAGER LOOK UP\n");
                                //can't have nice things
                         // EventManager* evtmngr = new EventManager();
                              //  printf("EVENT %d on ZONE %d :\n",(int)eventnum,(int)susr->getZone());
				if(evtmngr != NULL)
				{
					EventData* evt = evtmngr->GetEventData((int)susr->getZone(),(int)ievent);
					
					if(evt)
					{ // not null
						susr->RunExtEvent((int)sourcePointer, (int)npcpointer,(int)ievent,(int)susr->getZone(),evtmngr);
						return;
					}
					else
					{
						printf("EVENT %d on ZONE %d NOT FOUND!\n",(int)ievent,(int)susr->getZone());
                    }
				}
				else
				{
					printf("EVENT Manager NOT INITILIZED!\n");
				}
			}

    void (__thiscall *npcdead)(DWORD sourcePointer,DWORD npcpointer) = ((void (__thiscall *)(DWORD,DWORD))0x0044CE60);
	npcdead(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(npcpointer));
		
		}
		}
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("load cursor error\n%s\n", pE->getMsg());
        return;
    }
        
           
		   

    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();

}
else{

    if((int)ievent >0){
    // event manager look up test
          //  printf("EVENT MANAGER LOOK UP\n");
            //can't have nice things
     // EventManager* evtmngr = new EventManager();
          //  printf("EVENT %d on ZONE %d :\n",(int)eventnum,(int)susr->getZone());
            if(evtmngr != NULL){
            EventData* evt = evtmngr->GetEventData((int)susr->getZone(),(int)ievent);
                    if(evt){ // not null
                      susr->RunExtEvent((int)sourcePointer, (int)npcpointer,(int)ievent,(int)susr->getZone(),evtmngr);
                      return;
                    }

                   else{
                    printf("EVENT %d on ZONE %d NOT FOUND!\n",(int)ievent,(int)susr->getZone());
                    }

            }
            else{
               printf("EVENT Manager NOT INITILIZED!\n");
            }

    }
		// call 1p1 function to handel all other cases
    void (__thiscall *npcdead)(DWORD sourcePointer,DWORD npcpointer) = ((void (__thiscall *)(DWORD,DWORD))0x0044CE60);
	npcdead(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(npcpointer));


}
// call 1p1 function to handel the rest
//void (__thiscall *npcdead)(DWORD sourcePointer,DWORD npcpointer) = ((void (__thiscall *)(DWORD,DWORD))0x0044CE60);
//	npcdead(reinterpret_cast<DWORD>(sourcePointer),reinterpret_cast<DWORD>(npcpointer));
}


void __stdcall ServerHookInterface::User__pmoral_wrapper(void* sourcePointer, short imoral,void* npcpointer){
	User* susr = User::getExtentionUserFromRealUser(sourcePointer);

			const char *  that;
			const char *  other;

_asm
{
	mov that,EBX
    mov other,ESI
}
//	User* nusr = User::getExtentionUserFromRealUser((void*)that); //works
//	User* nnusr = User::getExtentionUserFromRealUser((void*)other);
//that=	(CHAR*)((BYTE*)that + 0x194); //works
// other= (CHAR*)((BYTE*)other + 0x194);

DWORD  iclass;
iclass= *reinterpret_cast<DWORD*>((BYTE*)npcpointer + 0x238);

  
	


//printf("%s has killed %s and gained %d moral, class:%d \n",susr->getName(),(CHAR*)((BYTE*)npcpointer + 0x194),imoral,(int)iclass);

  CGOdbcConnect cCon;
    try
    {
        cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);

    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return;
    }

  //  printf("Driver: %s\n", cCon.getDriver());

	char szQuery[91];
	
	 sprintf(szQuery,"{call proc_monlog ('%s','%s')}",susr->getName(), (CHAR*)((BYTE*)npcpointer + 0x194));

      // sprintf(szQuery, "Insert into monlog (struser,strmon) values ('%s', '%s')",susr->getName(),that);
	 

    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
		    //printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        printf("Insert Error\n%s\n", pE->getMsg());
        return;
    }

	  try
    {
        if (!pCur->bindAuto())
        {
            printf("cursor doesn't contain resultset\n");
            return;
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("binding error\n%s\n", pE->getMsg());
        return;
    }

    int totalcount;
       char strmessage[91];
	try
    {
        bool bRC;
        for (bRC = pCur->first(); bRC; bRC = pCur->next())
        {
          /*  printf("%i '%s'", i = pCur->getInt("id"), pCur->getChar("name"));
            //verify long fields
            const char *pBuff;
            int iLen;
            iLen = pCur->getLength("descript");
            printf(" %i", iLen);
            pBuff = pCur->getChar("descript");
            for (j = 0; j < iLen; j++)
            {
                if (pBuff[j] == i + '0' + j % 10)
                    continue;
                else
                {
                    printf("!%i", j);
                    break;
                }
            }
            pBuff = (const char *)pCur->getPtr("binid");
            iLen = pCur->getLength("binid");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != i + j)
                {
                    printf("!%i", j);
                    break;
                }

            pBuff = (const char *)pCur->getPtr("contents");
            iLen = pCur->getLength("contents");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != j % 10 + 30 + i)
                {
                    printf("!%i", j);
                    break;
                }
            printf(" %s ", pCur->getChar("a1"));
            printf(" %s ", pCur->getChar("a2"));
            printf(" %s ", pCur->getChar("stamp"));

            printf("\n"); */
			totalcount = pCur->getInt("total");
			//printf("total count: %d \n",totalcount);
			switch(totalcount){
			case 10:
		     sprintf(strmessage,"<<< Achivement Obtained: %d Monster Kills! >>>",totalcount);
			 susr->ShowMagic(302,0);
			susr->sendChatMessage(strmessage);
		   break;
   			case 100:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Monster Kills! >>>",totalcount);
				susr->ShowMagic(302,0);
			susr->sendChatMessage(strmessage);
		   break;
		      			case 500:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Monster Kills! >>>",totalcount);
				susr->ShowMagic(302,0);
			susr->sendChatMessage(strmessage);
		   break;
		      			case 1000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Monster Kills! >>>",totalcount);
				susr->ShowMagic(302,0);
			susr->sendChatMessage(strmessage);
		   break;
		      			case 5000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Monster Kills! >>>",totalcount);
				susr->ShowMagic(302,0);
			susr->sendChatMessage(strmessage);
		   break;

		      			case 10000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Monster Kills! >>>",totalcount);
				susr->ShowMagic(302,0);
			susr->sendChatMessage(strmessage);
		   break;

		      			case 50000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Monster Kills! >>>",totalcount);
				susr->ShowMagic(302,0);
			susr->sendChatMessage(strmessage);
		   break;
		      			case 100000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Monster Kills! >>>",totalcount);
				susr->ShowMagic(302,0);
			susr->sendChatMessage(strmessage);
		   break;
   
			}
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("load cursor error\n%s\n", pE->getMsg());
        return;
    }
        
           
		   

    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();
	

	// call 1p1 function to handel the rest
void (__thiscall *plusmoralbynpc)(DWORD sourcePointer,short imoral,short iclass) = ((void (__thiscall *)(DWORD,short,short))0x00481A30);
	plusmoralbynpc(reinterpret_cast<DWORD>(sourcePointer),imoral,(int)iclass);
}

void __stdcall ServerHookInterface::User__Copt_wrapper( DWORD userpointer, DWORD text){
	
	User* susr = User::getExtentionUserFromRealUser((void*)userpointer);
	
 //char * comptext;	
 //printf("%s -> Command: %s  \n",susr->getName(),text);


	// disable /repair during war inside war area
	if (strncmp((const char*)text, "repair", 6) == 0) 
	{
		if(susr->CheckGuildTownWar(1) && susr->isMapRange(106))
		{
			susr->sendChatMessage("<<< You can't do that during town war >>>");
			return;
		}
	}

	 if (strncmp((const char*)text,"guildmess ", 10) == 0 && susr->getGuildRank() < 10 && susr->getGuildRank() > 0 )
	 {
		 susr->sendguildtxt("Guild Notice Updated:");
		 susr->sendguildtxt(setguildmess(susr->getGuildId(),susr->getName(),(const char*)text));
		// Guild__npcreset((void*)userpointer,1);
		// susr->warguild(2);
	 }

	 // personal shops open
	  if (strncmp((const char*)text,"shop ", 5) == 0  )
	  {

		 char ames[200];
		// char uname[20] ;
		 char uuname[20];
		 char * test;
		 char c;
	 
		 // disable during war inside war area
		 if (susr->CheckGuildTownWar(1) && susr->isMapRange(106))
		 {
			 susr->sendChatMessage("<<< You can't do that during town war >>>");
			 return;
		 }

		 sscanf((const char*)text,"%*s %s",test);

		 // make the char upper
			 int a=0;
			 while (*(test + a) != '\0' ){
			 //c=uname[a];
			// uuname[a]= toupper(c);
			c= *(test + a);
			uuname[a]= toupper(c);
			 a++;
			 }
			 uuname[a]= '\0';
		 


		 		  int uonl = 0;
	  			std::vector<User*>::iterator i;
	
			int j = 0;
		 for ( i =uarray.begin(); i<uarray.end(); i++){

			 if( !strcmp(uarray[j]->getName(), uuname)){  //check if the user is online
			  uonl = 1;
			 }


				 j++;
		 }

		 if (uonl){
			 susr->Open_Guild_Store(getusershopid(uuname));
		 }
		 else{ 
			  sprintf(ames,"<<< %s is not online >>>",uuname);
			 susr->sendChatMessage(ames);}
	  }

	   // personal shops self register
	  if (strncmp((const char*)text,"myshop", 6) == 0   ){

		// char ames[200];
		// char uname[20];

		 // disable during war inside war area
		  if (susr->CheckGuildTownWar(1) && susr->isMapRange(106))
		  {
			  susr->sendChatMessage("<<< You can't do that during town war >>>");
			  return;
		  }

		 susr->Open_Guild_Store_Reg(getusershopid(susr->getName()));
			// sscanf((const char*)text,"%*s %s",uname);


	  }

	  if (strncmp((const char*)text,"reloadevent", 11) == 0   ){
		  if(susr->CheckRank(1)){
			  evtmngr->LoadEvents();
		  }
	  }

	  if (strncmp((const char*)text,"setguildtax ", 12) == 0  && susr->getGuildRank() < 10 && susr->getGuildRank() > 0 ){

		 char ames[200];
		 int tax;
	 
			 sscanf((const char*)text,"%*s %d",&tax);
			 if( tax < 0){
			 tax = 0;
			 }

		  if( susr->CheckGuildTown(14)){
			 gt1tax =  tax;
			 sprintf(ames,"Guild Town Tax Updated: %d%%",gt1tax);
			 susr->sendguildtxt(ames);
		  }
		  if( susr->CheckGuildTown(15)){
			gt2tax =  tax;
			 sprintf(ames,"Guild Town Tax Updated: %d%%",gt2tax);
			susr->sendguildtxt(ames);
		  }
		 // printf("gwar: %d gwb: %d gwn: %d gwv: %d gw: %d", susr->getGuildWar(),susr->getGuildWarb(),susr->getGuildWarNum(),susr->getGuildWarvill(),susr->isInGuildWar()); 
		//  susr->WarpGate(1,200,400);
		 // printf("event number 100: %d",susr->FindEvent(100));
		  //susr->OpenGuildTownTaxRate(13);
	  
	  }

	 else if (strncmp((const char*)text,"guildmess", 9) == 0 && susr->getGuildRank() > 0 )
	 {
		 susr->sendguildtxt(getguildmess(susr->getGuildId()));
	 }
 
	// call 1p1 function to handel the rest

void (__thiscall *usercopt)(DWORD iuser,DWORD itext) = ((void (__thiscall *)(DWORD,DWORD))0x00448580);
	 usercopt(userpointer,text);
	
}

char* ServerHookInterface::setguildmess(int guildid,const char* username,const char* mess){
	    CGOdbcConnect cCon;
    try
    {
        cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);

    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return 0;
    }

    //printf("Driver: %s\n", cCon.getDriver());

	char szQuery[300];
	/*
	std::string stripper;
	stripper= mess;

	stripper = stripper.replace(stripper.begin(),stripper.end(),"'"," "); // replace ' with '' to escape sql
	stripper = stripper.replace(stripper.begin(),stripper.end(),"}","' "); // replace } with '' to escape sql
	stripper = stripper.replace(stripper.begin(),stripper.end(),"{","' "); // replace { with '' to escape sql
	stripper = stripper.replace(stripper.begin(),stripper.end(),";","' "); // replace ; with '' to escape sql
	stripper = stripper.replace(stripper.begin(),stripper.end(),'"',' '); // replace " with '' to escape sql
	stripper = stripper.replace(stripper.begin(),stripper.end(),"("," "); // replace ( with '' to escape sql
	stripper = stripper.replace(stripper.begin(),stripper.end(),")"," "); // replace ' with '' to escape sql
	 */
	//sprintf(szQuery, "Insert into pklog (sourcename, targetname, pos,type) values ('%s', '%s','%d','%d')",source,target,pos,type);

	sprintf(szQuery, "{call proc_guildmess ('%s', '%s','%d')}",username,mess,guildid);
	 

    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
		    //printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        printf("Insert Error\n%s\n", pE->getMsg());
        return 0;
    }

	 	  try
    {
        if (!pCur->bindAuto())
        {
            printf("cursor doesn't contain resultset\n");
            return 0;
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("binding error\n%s\n", pE->getMsg());
        return 0;
    }

    int totalcount;
       char strmessage[91];
	   const char *pBuff;
	try
    {
        bool bRC;
        for (bRC = pCur->first(); bRC; bRC = pCur->next())
        {
           // printf("%i '%s'", i = pCur->getInt("id"), pCur->getChar("name"));
            //verify long fields
            
           // int iLen;
           // iLen = pCur->getLength("descript");
           // printf(" %i", iLen);
            pBuff = pCur->getChar("mess");
          /*  for (j = 0; j < iLen; j++)
            {
                if (pBuff[j] == i + '0' + j % 10)
                    continue;
                else
                {
                    printf("!%i", j);
                    break;
                }
            }
			
			
            pBuff = (const char *)pCur->getPtr("binid");
            iLen = pCur->getLength("binid");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != i + j)
                {
                    printf("!%i", j);
                    break;
                }

            pBuff = (const char *)pCur->getPtr("contents");
            iLen = pCur->getLength("contents");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != j % 10 + 30 + i)
                {
                    printf("!%i", j);
                    break;
                }
            printf(" %s ", pCur->getChar("a1"));
            printf(" %s ", pCur->getChar("a2"));
            printf(" %s ", pCur->getChar("stamp"));

            printf("\n"); */
			totalcount = pCur->getInt("gpos");
		//	printf("total kill count: %d \n",totalcount);

        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("load cursor error\n%s\n", pE->getMsg());
        return 0;
    }
        

    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();
	char guildmess[4000];
	sprintf(guildmess,"<<< %s // Guild Pos: %d >>>",pBuff,totalcount);
		return guildmess;
}

int ServerHookInterface::getusershopid(const char* username){
	    CGOdbcConnect cCon;
    try
    {
        cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);

    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return 0;
    }

    //printf("Driver: %s\n", cCon.getDriver());

	char szQuery[300];
	

	sprintf(szQuery, "{call proc_usershop ('%s')}",username);
	 

    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
		    //printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        printf("Insert Error\n%s\n", pE->getMsg());
        return 0;
    }

	 	  try
    {
        if (!pCur->bindAuto())
        {
            printf("cursor doesn't contain resultset\n");
            return 0;
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("binding error\n%s\n", pE->getMsg());
        return 0;
    }

    int totalcount;
	int res;
       char strmessage[91];
	   const char *pBuff;
	try
    {
        bool bRC;
        for (bRC = pCur->first(); bRC; bRC = pCur->next())
        {
           // printf("%i '%s'", i = pCur->getInt("id"), pCur->getChar("name"));
            //verify long fields
            
           // int iLen;
           // iLen = pCur->getLength("descript");
           // printf(" %i", iLen);
         //   pBuff = pCur->getChar("mess");
          /*  for (j = 0; j < iLen; j++)
            {
                if (pBuff[j] == i + '0' + j % 10)
                    continue;
                else
                {
                    printf("!%i", j);
                    break;
                }
            }
			
			
            pBuff = (const char *)pCur->getPtr("binid");
            iLen = pCur->getLength("binid");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != i + j)
                {
                    printf("!%i", j);
                    break;
                }

            pBuff = (const char *)pCur->getPtr("contents");
            iLen = pCur->getLength("contents");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != j % 10 + 30 + i)
                {
                    printf("!%i", j);
                    break;
                }
            printf(" %s ", pCur->getChar("a1"));
            printf(" %s ", pCur->getChar("a2"));
            printf(" %s ", pCur->getChar("stamp"));

            printf("\n"); */
			totalcount = pCur->getInt("usid");
			res = pCur->getInt("res");
		//	printf("total kill count: %d \n",totalcount);

        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("load cursor error\n%s\n", pE->getMsg());
        return 0;
    }
        

    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();

	if(res){ // uninitiated so update guildtown table
		
	void (__thiscall  *User__upgt_wrapper)() = ((void(__thiscall  *)())0x00423460);
    User__upgt_wrapper( );
	
	}

		return totalcount;
}

int ServerHookInterface::setguildpos(int guildid,const char* username,int ammount){
	    CGOdbcConnect cCon;
    try
    {
      cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);

    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return 0;
    }

    //printf("Driver: %s\n", cCon.getDriver());

	char szQuery[300];
	
	//sprintf(szQuery, "Insert into pklog (sourcename, targetname, pos,type) values ('%s', '%s','%d','%d')",source,target,pos,type);

	sprintf(szQuery, "{call proc_guildpos ('%s', '%d','%d')}",username,ammount,guildid);
	 

    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
		    //printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        printf("Insert Error\n%s\n", pE->getMsg());
        return 0;
    }

	 	  try
    {
        if (!pCur->bindAuto())
        {
            printf("cursor doesn't contain resultset\n");
            return 0;
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("binding error\n%s\n", pE->getMsg());
        return 0;
    }

    int totalcount;
       char strmessage[91];
	   const char *pBuff;
	try
    {
        bool bRC;
        for (bRC = pCur->first(); bRC; bRC = pCur->next())
        {
           // printf("%i '%s'", i = pCur->getInt("id"), pCur->getChar("name"));
            //verify long fields
            
           // int iLen;
           // iLen = pCur->getLength("descript");
           // printf(" %i", iLen);
    //        pBuff = pCur->getChar("mess");
          /*  for (j = 0; j < iLen; j++)
            {
                if (pBuff[j] == i + '0' + j % 10)
                    continue;
                else
                {
                    printf("!%i", j);
                    break;
                }
            }
			
			
            pBuff = (const char *)pCur->getPtr("binid");
            iLen = pCur->getLength("binid");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != i + j)
                {
                    printf("!%i", j);
                    break;
                }

            pBuff = (const char *)pCur->getPtr("contents");
            iLen = pCur->getLength("contents");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != j % 10 + 30 + i)
                {
                    printf("!%i", j);
                    break;
                }
            printf(" %s ", pCur->getChar("a1"));
            printf(" %s ", pCur->getChar("a2"));
            printf(" %s ", pCur->getChar("stamp"));

            printf("\n"); */
			totalcount = pCur->getInt("gpos");
		//	printf("total kill count: %d \n",totalcount);

        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("load cursor error\n%s\n", pE->getMsg());
        return 0;
    }
        

    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();
	char guildmess[4000];
	//sprintf(guildmess,"<<< %s // Guild Pos: %d >>>",pBuff,totalcount);
		return totalcount;
}

char* ServerHookInterface::getguildmess(int guildid){
	    CGOdbcConnect cCon;
    try
    {
        cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);
		//cCon.connect("soma", "soma", "soma");
		
    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return 0;
    }

    //printf("Driver: %s\n", cCon.getDriver());

	char szQuery[300];
	
	//sprintf(szQuery, "Insert into pklog (sourcename, targetname, pos,type) values ('%s', '%s','%d','%d')",source,target,pos,type);

	sprintf(szQuery, "{call proc_getguildmess ('%d')}",guildid);
	 

    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
		    //printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        printf("Insert Error\n%s\n", pE->getMsg());
        return 0;
    }

	 	  try
    {
        if (!pCur->bindAuto())
        {
            printf("cursor doesn't contain resultset\n");
            return 0;
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("binding error\n%s\n", pE->getMsg());
        return 0;
    }

    int totalcount;
       char strmessage[91];
	   const char *pBuff;
	try
    {
        bool bRC;
        for (bRC = pCur->first(); bRC; bRC = pCur->next())
        {
           // printf("%i '%s'", i = pCur->getInt("id"), pCur->getChar("name"));
            //verify long fields
            
           // int iLen;
           // iLen = pCur->getLength("descript");
           // printf(" %i", iLen);
            pBuff = pCur->getChar("mess");
          /*  for (j = 0; j < iLen; j++)
            {
                if (pBuff[j] == i + '0' + j % 10)
                    continue;
                else
                {
                    printf("!%i", j);
                    break;
                }
            }
			
			
            pBuff = (const char *)pCur->getPtr("binid");
            iLen = pCur->getLength("binid");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != i + j)
                {
                    printf("!%i", j);
                    break;
                }

            pBuff = (const char *)pCur->getPtr("contents");
            iLen = pCur->getLength("contents");
            printf(" %i", iLen);

            for (j = 0; j < iLen; j++)
                if (pBuff[j] != j % 10 + 30 + i)
                {
                    printf("!%i", j);
                    break;
                }
            printf(" %s ", pCur->getChar("a1"));
            printf(" %s ", pCur->getChar("a2"));
            printf(" %s ", pCur->getChar("stamp"));

            printf("\n"); */
			totalcount = pCur->getInt("gpos");
		//	printf("total kill count: %d \n",totalcount);

        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("load cursor error\n%s\n", pE->getMsg());
        return 0;
    }
        

    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();
	char guildmess[4000];
	sprintf(guildmess,"<<< %s // Guild Pos: %d >>>",pBuff,totalcount);
		return guildmess;
}


void __stdcall ServerHookInterface::User__Init_wrapper( void* targetpointer){
	
	User* susr = User::getExtentionUserFromRealUser(targetpointer);

	//get event counter from db
	susr->getsrEvent();

	//get id and saved items list
	susr->dbindex = getusershopid(susr->getName()) - 15;
	// load item list
	susr->LoadSavedItemTable();

	// printf("%s -> loaded (shadow realm event %d) \n",susr->getName(),susr->srtime);
	//user loaded insert pointer to user array
	uarray.insert(uarray.begin(),susr);

std::vector<int>::iterator i;
	//set guild war thingi
	if (gtw1 > 0 ){
		if(susr->CheckGuildTown(14)|| susr->CheckGuildTownAlly(14)){ susr->warguild(1); susr->gtw = 1;}
			int j = 0;
	 for ( i =gt1.begin(); i<gt1.end(); i++){
		 
	
		 if(susr->getGuildId() == gt1[j]){
			 susr->gtw = 1;
			 susr->warguild(1);
		 }  // set the war status
			 j++;
	 }

	}
	if (gtw2 > 0 ){
		if(susr->CheckGuildTown(15)|| susr->CheckGuildTownAlly(15)){ susr->warguild(1); susr->gtw = 1;}
				int j = 0;
	 for ( i =gt2.begin(); i<gt2.end(); i++){
		 
	
		 if(susr->getGuildId() == gt2[j]){
			 susr->gtw = 1;
			 susr->warguild(1);
		 }  // set the war status
			 j++;
	 }
	}


	const char * other;
	

_asm
{

	mov other,ECX

}
// see if it's initalized
/*
if (!intinit)
{
	evtmngr = new EventManager();
	susr->LiveNPC(40110,-1, -1, -1);
	susr->LiveNPC(40239,-1, -1, -1);
	susr->LiveNPC(40240,-1, -1, -1);
	susr->LiveNPC(40241,-1, -1, -1);
	susr->LiveNPC(40242,-1, -1, -1);
	susr->LiveNPC(40243,-1, -1, -1);
	susr->LiveNPC(40244,-1, -1, -1);
	susr->LiveNPC(40245,-1, -1, -1);
	susr->LiveNPC(40246,-1, -1, -1);
	susr->LiveNPC(40247,-1, -1, -1);
	susr->LiveNPC(40248,-1, -1, -1);
	susr->LiveNPC(40253,-1, -1, -1);
	susr->LiveNPC(40254,-1, -1, -1);
	susr->LiveNPC(40255,-1, -1, -1);
	susr->LiveNPC(40256,-1, -1, -1);
	susr->LiveNPC(40257,-1, -1, -1);
	susr->LiveNPC(40258,-1, -1, -1);
	susr->LiveNPC(40263,-1, -1, -1);
	susr->LiveNPC(40264,-1, -1, -1);
	susr->LiveNPC(40265,-1, -1, -1);
	susr->LiveNPC(40266,-1, -1, -1);
	 //printf("%s -> first user online, initalizing! \n",susr->getName());

	intinit = 1;
}*/

//User* susr =  User::getExtentionUserFromRealUser((void*)other);

if (!intinit)
	{
		evtmngr = new EventManager();
intinit = 1;
}
	char glognotice[100];
 printf("%s -> loaded (sending welcome message) \n",susr->getName());
	 susr->sendChatMessage("<<< Welcome To ShinRa Server! >>>");
	// susr->SendAllMessage("<<< Testing !! >>>");

	 //susr->RunEventByNum(3);
	 //susr->Selectmsg("hello","ms1","ms2","ms3","ms4",1,2,3,4);
	 //susr->dirpoint(10,20,20,10);

//  susr->sendChatMessage("<<< Welcome to eXile >>>");
	 if(susr->getGuildRank() > 0 )
	 {
		 susr->sendChatMessage(getguildmess(susr->getGuildId()));
		 sprintf(glognotice, "<<< %s Has Logged in >>>",susr->getName());
		 susr->sendguildtxt(glognotice);
	 }
	// call 1p1 function to handel the rest
void (__thiscall *userinit)(DWORD sourcePointer) = ((void (__thiscall *)(DWORD))0x00474170);
	 userinit(reinterpret_cast<DWORD>(targetpointer));
	
}

void __stdcall ServerHookInterface::User__Pkpos_wrapper(void* sourcePointer, short unkown){
	

	

	
	//User* susr = User::getExtentionUserFromRealUser(sourcePointer);
	//User* tusr = User::getExtentionUserFromRealUser(targetPointer);

	
	
	//	const char * pszString = 0;
	const char *  that;
	const char * other;
	const char * ithat;
	const char * othat;


	int pos;
	pos = 0; 
_asm
{
	mov that,EDI
	mov other,ECX
	mov ithat,ESI
	mov othat,EBX
}



//	printf(pszString);
	
	User* susr = User::getExtentionUserFromRealUser((void*)that);
	User* tusr = User::getExtentionUserFromRealUser((void*)other);
	//User* iusr = User::getExtentionUserFromRealUser((void*)ithat);
	//User* ousr = User::getExtentionUserFromRealUser((void*)othat);

//	tusr->sendChatMessage("<<< You killed kenny, You bastard! >>>");
	//printf((const char*)susr->getName()); 
	//printf((const char*)tusr->getName()); 
	//printf("pos: %d", pos);
	//printf((const char*)tusr->getName());
	//	that = (const char*)susr->getName();	
	//	ithat = (const char*)iusr->getName();
	//	othat = (const char*)ousr->getName();
	//	other = (const char*)tusr->getName();
//	printf("source moral %d sourcegraycount %d target moral %d targetgraycount %d \n",tusr->getMoral(),tusr->getGray(),susr->getMoral(),susr->getGray());
		// set kill type
		int killtype = 1; //default rvr
		if((tusr->getClass() == susr->getClass()) || (tusr->getClass() > 0 && susr->getClass() > 0)){
		
			killtype = 0;

		if((int)tusr->getGray() == 0 ){
			// it was ppk
			killtype = 2;
		}
		if((int)tusr->getGray() > 0 && (int)susr->getMoral() > -3100000){
			//it was pk
		killtype = 0;
		}
		
		}
		//killed by melee add 10
		 killtype +=10;
		
// add 100 for arena kill
		 
		 if (tusr->isMapRange(107) && susr->isMapRange(107)){
		 killtype +=100;
		 }
// add 200 for wotf kill
		  if (tusr->isMapRange(109) && susr->isMapRange(109)){
		 killtype +=200;
		 }

int killcount;
	killcount =	pklog(tusr->getName(),susr->getName(),pkposget(tusr->getLevel(),susr->getLevel(),tusr->getTotalClassPoint(),susr->getTotalClassPoint()),killtype);
	 char strmessage[100];
				switch(killcount){
			case 10: 
		     sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
			 susr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
   			case 100:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				susr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 500:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				susr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 1000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				susr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 5000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				susr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;

		      			case 10000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				susr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;

		      			case 50000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				susr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 100000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				susr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
   
			}

		char guildtext[100];
		sprintf(guildtext,"<<< %s Has killed %s >>>",tusr->getName(),susr->getName());  
		//tusr->sendGuildChatMessage(guildtext);
		tusr->sendguildtxt(guildtext);
		sprintf(guildtext,"<<< %s Has been killed by %s >>>",susr->getName(),tusr->getName());  
		susr->sendguildtxt(guildtext);

	// call 1p1 function to handel the rest
void (__thiscall *checkpkpos)(DWORD sourcePointer,short random) = ((void (__thiscall *)(DWORD,short))0x0048C3D0);
	checkpkpos(reinterpret_cast<DWORD>(sourcePointer),unkown);
}

void __stdcall ServerHookInterface::User__Pkpos_wrapper1(void* sourcePointer, short unkown){
	

	

	
	//User* susr = User::getExtentionUserFromRealUser(sourcePointer);
	//User* tusr = User::getExtentionUserFromRealUser(targetPointer);

	
	
	//	const char * pszString = 0;
	const char *  that;
	const char * other;
	const char * ithat;
	const char * othat;


	int pos;
	pos = 0; 
_asm
{
	mov that,EDI
	mov other,ECX
	mov ithat,ESI
	mov othat,EBX
}



//	printf(pszString);
	
//	User* susr = User::getExtentionUserFromRealUser((void*)that);
	User* tusr = User::getExtentionUserFromRealUser((void*)other);
//	User* iusr = User::getExtentionUserFromRealUser((void*)ithat);
	User* ousr = User::getExtentionUserFromRealUser((void*)othat);

	//printf((const char*)susr->getName()); 
	//printf((const char*)tusr->getName()); 
	//printf("pos: %d", pos);
	//printf((const char*)tusr->getName());
	//	that = (const char*)susr->getName();	
	//	ithat = (const char*)iusr->getName();
	//	othat = (const char*)ousr->getName();
	//	other = (const char*)tusr->getName();

			// set kill type
		int killtype = 1; //default rvr
		if((tusr->getClass() == ousr->getClass()) || (tusr->getClass() > 0 && ousr->getClass() > 0)){
		
			killtype = 0;

		if((int)tusr->getGray() == 0 ){
			// it was ppk
			killtype = 2;
		}
		if((int)tusr->getGray() > 0 && (int)ousr->getMoral() > -3100000){
			//it was pk
		killtype = 0;
		}
		
		}
		//killed by magic add 20
		 killtype +=20;
		
// add 100 for arena kill
		 
		 if (tusr->isMapRange(107) && ousr->isMapRange(107)){
		 killtype +=100;
		 }
// add 200 for wotf kill
		  if (tusr->isMapRange(109) && ousr->isMapRange(109)){
		 killtype +=200;
		 }

int killcount;
killcount =	pklog(tusr->getName(),ousr->getName(),pkposget(tusr->getLevel(),ousr->getLevel(),tusr->getTotalClassPoint(),ousr->getTotalClassPoint()),killtype);
//	killcount =	pklog(tusr->getName(),susr->getName(),pkposget(tusr->getLevel(),susr->getLevel(),tusr->getTotalClassPoint(),susr->getTotalClassPoint()),killtype);
	 char strmessage[100];
				switch(killcount){
			case 10: 
		     sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
			 tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
   			case 100:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 500:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 1000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 5000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;

		      			case 10000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;

		      			case 50000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 100000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
   
			}

		char guildtext[100];

		sprintf(guildtext,"<<< %s Has killed %s >>>",tusr->getName(),ousr->getName());  
		//tusr->sendGuildChatMessage(guildtext);
		tusr->sendguildtxt(guildtext);
		sprintf(guildtext,"<<< %s Has been killed by %s >>>",ousr->getName(),tusr->getName());  
		ousr->sendguildtxt(guildtext);

	// call 1p1 function to handel the rest
void (__thiscall *checkpkpos)(DWORD sourcePointer,short random) = ((void (__thiscall *)(DWORD,short))0x0048C3D0);
	checkpkpos(reinterpret_cast<DWORD>(sourcePointer),unkown);
}


void __stdcall ServerHookInterface::User__Pkpos_wrapper2(void* sourcePointer, short unkown){
	

	

	
	//User* susr = User::getExtentionUserFromRealUser(sourcePointer);
	//User* tusr = User::getExtentionUserFromRealUser(targetPointer);

	
	
	//	const char * pszString = 0;
	const char *  that;
	const char * other;
	const char * ithat;
	const char * othat;


	int pos;
	pos = 0; 
_asm
{
	mov that,EDI
	mov other,ECX
	mov ithat,ESI
	mov othat,EBX
}



//	printf(pszString);
	
	//User* susr = User::getExtentionUserFromRealUser((void*)that);
	User* tusr = User::getExtentionUserFromRealUser((void*)other);
	User* iusr = User::getExtentionUserFromRealUser((void*)ithat);
	//User* ousr = User::getExtentionUserFromRealUser((void*)othat);


			// set kill type
		int killtype = 1; //default rvr
		if((tusr->getClass() == iusr->getClass()) || (tusr->getClass() > 0 && iusr->getClass() > 0)){
		
			killtype = 0;

		if((int)tusr->getGray() == 0 ){
			// it was ppk
			killtype = 2;
		}
		if((int)tusr->getGray() > 0 && (int)iusr->getMoral() > -3100000){
			//it was pk
		killtype = 0;
		}
		
		}
		//killed by aura add 30
		 killtype +=30;
		
// add 100 for arena kill
		 
		 if (tusr->isMapRange(107) && iusr->isMapRange(107)){
		 killtype +=100;
		 }
// add 200 for wotf kill
		  if (tusr->isMapRange(109) && iusr->isMapRange(109)){
		 killtype +=200;
		 }

int killcount;
killcount = pklog(tusr->getName(),iusr->getName(),pkposget(tusr->getLevel(),iusr->getLevel(),tusr->getTotalClassPoint(),iusr->getTotalClassPoint()),killtype);
//	killcount =	pklog(tusr->getName(),susr->getName(),pkposget(tusr->getLevel(),susr->getLevel(),tusr->getTotalClassPoint(),susr->getTotalClassPoint()),killtype);
	 char strmessage[100];
				switch(killcount){
			case 10: 
		     sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
			 tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
   			case 100:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 500:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 1000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 5000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;

		      			case 10000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;

		      			case 50000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
		      			case 100000:
		        sprintf(strmessage,"<<< Achivement Obtained: %d Confirmed Kills! >>>",killcount);
				tusr->ShowMagic(302,0);
			tusr->sendChatMessage(strmessage);
		   break;
   
			}

		char guildtext[100];

		
		sprintf(guildtext,"<<< %s Has killed %s >>>",tusr->getName(),iusr->getName());  
		//tusr->sendGuildChatMessage(guildtext);
		tusr->sendguildtxt(guildtext);
		sprintf(guildtext,"<<< %s Has been killed by %s >>>",iusr->getName(),tusr->getName());  
		iusr->sendguildtxt(guildtext);

	
	// call 1p1 function to handel the rest
void (__thiscall *checkpkpos)(DWORD sourcePointer,short random) = ((void (__thiscall *)(DWORD,short))0x0048C3D0);
	checkpkpos(reinterpret_cast<DWORD>(sourcePointer),unkown);
}


void ServerHookInterface::User__takeBackItem_wrapper(void* userPointer, BYTE* packetToParse)
{
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	//usr->parseTakeBackItem(packetToParse);

	if (usr->isWithinRange(&usr->lastWH))
	{
		// parseVersionResult(reinterpret_cast<DWORD>(this->realUser), buffer);

		usr->TakeBackItem(packetToParse);
		return;
	}

	usr->logcheat(6);

}
void __stdcall ServerHookInterface::User__saveItem_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseSaveItem(packetToParse);
}
void __stdcall ServerHookInterface::User__takeBackMoney_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseTakeBackMoney(packetToParse);
}
void __stdcall ServerHookInterface::User__saveMoney_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseSaveMoney(packetToParse);
}

void ServerHookInterface::User__StorageOpen_wrapper(void* userPointer, int unknown){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->storageOpen(unknown);
}

// guildStuff

void __stdcall ServerHookInterface::User__GuildSaveItem_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseGuildSaveItem(packetToParse);
}
void __stdcall ServerHookInterface::User__GuildTakeBackItem_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseGuildTakeBackItem(packetToParse);
}
void __stdcall ServerHookInterface::User__GuildContribution_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseGuildContribution(packetToParse);
}
void ServerHookInterface::User__OpenGuildTownStone_wrapper(void* userPointer, short unknown){
	User* usr = User::getExtentionUserFromRealUser(userPointer); 
	
	
		  	usr->openGuildTownStone(unknown);
}

void ServerHookInterface::User__GuildOpen_wrapper(void* userPointer){
	User* usr = User::getExtentionUserFromRealUser(userPointer);



	//printf("\n username: %s", (const char*)usr->getName());

	usr->guildOpen();
}

void __stdcall ServerHookInterface::User__SpecialMove_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseSpecialMove(packetToParse);
}
void __stdcall ServerHookInterface::User__MoveReq_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseMoveReq(packetToParse);
}

void __stdcall ServerHookInterface::User__Move_wrapper(void* userPointer, int x, int y){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->move(x,y,gtw1,gtw2);
}


void __stdcall ServerHookInterface::User__RunReq_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseRunReq(packetToParse);
}
void __stdcall ServerHookInterface::User__RunFirst_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseRunFirst(packetToParse);
}

void __stdcall ServerHookInterface::User__RepairItemOpen_wrapper(void* userPointer){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->repairItemOpen();
}
void __stdcall ServerHookInterface::User__RepairItem_wrapper(void* userPointer, BYTE* packetToParse){
	User* usr = User::getExtentionUserFromRealUser(userPointer);
	usr->parseRepairItem(packetToParse);
}

void __stdcall ServerHookInterface::User__LogOut_wrapper(void* userPointer,BYTE* Buffer)
{
		User* usr = User::getExtentionUserFromRealUser(userPointer);


		// saving shadow event status
		usr->setsrEvent();

		// save the item table
		usr->StoreSavedItemTable();

		// accessing 

		std::vector<User*>::iterator i;
		int j = 0;

		for ( i = uarray.begin(); i < uarray.end(); i++)
		{
			if(uarray[j]->getName() == usr->getName())
			{
				// eraseing 
				i = uarray.erase(uarray.begin()+j); //deletes the ith element
				//printf("Removed->%s goodbye!\n", (const char*)usr->getName());

				break;
			}

			if (uarray.empty())
				break;
			
			j++;
		 }

	    usr->LogOut(Buffer);
}

void __stdcall ServerHookInterface::Guild__town_war_end(int guildnum){
	std::vector<User*>::iterator i;
		std::vector<int>::iterator i2;
		int j = 0;
	 for ( i =uarray.begin(); i<uarray.end(); i++){ 
		 
		//  printf("gtw(%d) end->%s\n",guildnum,uarray[j]->getName());

		//printf("time->%s \n", (const char*)uarray[j]->getName());	
		// uarray[j]->getRandomReward(uarray[j]); // call random reward function
		 if(guildnum == 1){
			 			 		if(uarray[j]->CheckGuildTown(14) || uarray[j]->CheckGuildTownAlly(14)){ uarray[j]->warguild(-1); uarray[j]->gtw = 0;}
				int p = 0;
	 for ( i2 =gt1.begin(); i2<gt1.end(); i2++){
		 
	//printf("%s->gt1 array ugid:%d gt1:%d \n",uarray[j]->getName(), uarray[j]->getGuildId(),gt1[p]);

		 if(uarray[j]->getGuildId() == gt1[p]){
			 uarray[j]->gtw = 0;
			 uarray[j]->warguild(-1);
		 }  // set the war status
			 p++;
	 }

	 	 // respawn lancers + first wall	 	
	uarray[j]->LiveNPC(40253,-1, -1, -1);
	uarray[j]->LiveNPC(40255,-1, -1, -1);
	uarray[j]->LiveNPC(40256,-1, -1, -1);
	uarray[j]->LiveNPC(40257,-1, -1, -1);
	uarray[j]->LiveNPC(40258,-1, -1, -1);



		 }

		 if(guildnum == 2){
			 		if(uarray[j]->CheckGuildTown(15) || uarray[j]->CheckGuildTownAlly(15)){ 
						uarray[j]->warguild(-1); 
						uarray[j]->gtw = 0;
					}
				int p = 0;
	 for ( i2 =gt2.begin(); i2<gt2.end(); i2++){

	//	 printf("%s->gt2 array ugid:%d gt2:%d \n",uarray[j]->getName(), uarray[j]->getGuildId(),gt2[p]);
		 
		 if(uarray[j]->getGuildId() == gt2[p]){
			 uarray[j]->gtw = 0;
			 uarray[j]->warguild(-1);
		 }  // set the war status
			 p++;
	 }

	 	 //respawn lancer + first wall
	uarray[j]->LiveNPC(40254,-1, -1, -1);
	uarray[j]->LiveNPC(40263,-1, -1, -1);
	uarray[j]->LiveNPC(40264,-1, -1, -1);
	uarray[j]->LiveNPC(40265,-1, -1, -1);
	uarray[j]->LiveNPC(40266,-1, -1, -1);

		 }
		 

			 j++;
	 }

	 if(guildnum == 1){
	 gtw1 = 0;
	 gtwc1 = 360;
	 gt1.clear();
	 uarray[0]->SendAllMessage("<<< The Battle for Susa has ended. >>>");
	 }

	 if(guildnum == 2){	 
	gtw2 = 0;
	 gtwc2 = 360;
	 gt2.clear();
	 uarray[0]->SendAllMessage("<<< The Battle for Dina has ended. >>>");
	 }
}

void __stdcall ServerHookInterface::OnePerOneDlg__CheckGameTime_wrapper(void* OnePerOneDLGPointer){
	
	if (gtw1 > 0){gtw1--; if(gtw1 <= 0 ){Guild__town_war_end(1);} }
	if (gtw2 > 0){gtw2--; if(gtw2 <= 0 ){Guild__town_war_end(2);} }
	if (gtwc1 > 0){gtwc1--;}
	if (gtwc2 > 0){gtwc2--;}
	
		 


	
		std::vector<User*>::iterator i;
	
		int j = 0;
	 for ( i =uarray.begin(); i<uarray.end(); i++){
		// printf("time->%s inguildwar:%d guildwar:%d guildwarb:%d guildvill:%d \n", (const char*)uarray[j]->getName(),uarray[j]->isInGuildWar(),uarray[j]->getGuildWar(),uarray[j]->getGuildWarb(),uarray[j]->getGuildWarvill()); 
		// printf("time->%s gtw:%d  \n", (const char*)uarray[j]->getName(),uarray[j]->getguildwardead());	
		// uarray[j]->getRandomReward(uarray[j]); // call random reward function
		 if(!uarray[j]->uitems.empty()){
			 uarray[j]->checkitemwaitlist();
		 }
		 if(uarray[j]->srtime > 0 && uarray[j]->getZone() == 28){
		  
			 uarray[j]->srtime--;
			// printf("time->%s srtime:%d  \n", (const char*)uarray[j]->getName(),uarray[j]->srtime);
			 if(uarray[j]->srtime == 180){
				 uarray[j]->sendChatMessage("<<---- You have 30 mins left in this realm! ---->>");
			 }

			 if(uarray[j]->srtime == 60){
				 uarray[j]->sendChatMessage("<<---- You have 10 mins left in this realm! ---->>");
			 }

			 if(uarray[j]->srtime == 30){
				 uarray[j]->sendChatMessage("<<---- You have 5 mins left in this realm! ---->>");
			 }

			 if(uarray[j]->srtime == 6){
				 uarray[j]->sendChatMessage("<<---- You have 1 mins left in this realm! ---->>");
			 }

			 if(uarray[j]->srtime == 3){
				 uarray[j]->sendChatMessage("<<---- You have 30 seconds left in this realm! ---->>");
			 }

			 if(uarray[j]->srtime == 1){
				 uarray[j]->sendChatMessage("<<---- You have 10 seconds left in this realm! ---->>");
			 }

		 } 
		 if(uarray[j]->srtime <= 0 && uarray[j]->getZone() == 28){
		 uarray[j]->srtime = 0;
		 uarray[j]->WarpGate(35,489,89);

		 }
			 j++;
	 }
	
	//usr->checkTimeLoop();
void (__thiscall  *OnePerOneDlg__CheckGameTime_wrapper)(void* OnePerOneDLGPointer) = ((void(__thiscall  *)(void*))0x00420B50);
OnePerOneDlg__CheckGameTime_wrapper(OnePerOneDLGPointer);

}


	
void __stdcall ServerHookInterface::User__diritem_wrapper(void* userPointer,int a2){
	// thebyte is usually 1
	User* usr = User::getExtentionUserFromRealUser(userPointer);

	//printf("dir(%s)->byte:%d a3:%d a4:%d a5:%d a6:%d \n", (const char*)usr->getName(), a2,  a3,  a4,  a5,  a6);	
	//printf("house(%s)->:%d \n", (const char*)usr->getName(), a2);
void (__thiscall  *User__diritem_wrapper)(void* userPointer, int a2) = ((void(__thiscall  *)(void* userPointer, int ))0x004652F0);
User__diritem_wrapper( userPointer,  a2 );

}

signed int __stdcall ServerHookInterface::User__cpk_wrapper(void* sourcePointer, void* targetPointer){

  bool result; // eax@2
  signed int tMoral; // ecx@9
  int uGuildnumber; // eax@14
  int tGuildNumber; // ecx@14
  int tDeathType; // eax@17
  int v11; // eax@23

  		 User* susr = User::getExtentionUserFromRealUser(sourcePointer);
		 User* tusr = User::getExtentionUserFromRealUser(targetPointer);


  if ( !targetPointer ){
    return 0;
  }
  if ( susr->CheckMonster(susr->getClass()) != tusr->CheckMonster(tusr->getClass()) ){
	  return 0;}
  if ( susr->CheckDemon(susr->getClass()) != tusr->CheckDemon(tusr->getClass()) ){
	  return 0;}
  if ( tusr->getGray() > 0 ){  // GrayCount
	  return 0;}
 
  tMoral = tusr->getMoral(); // *(_DWORD *)(targetPointer + 0x722C);
  if ( tusr->CheckDemon(tusr->getClass()) )
  {
    if ( tMoral / 100000 > 30 )
      return 0;
  }
  else
  {
    if ( tMoral / 100000 <= -31 )
      return 0;
  }
  tGuildNumber = tusr->getGuildId();
  uGuildnumber = susr->getGuildId();
  // my junk
  if(gtw1 > 0 || gtw2 > 0 ){
		//result = 0;
		if(tusr->gtw && susr->gtw){
			*(DWORD *)((DWORD)targetPointer + 0x7220) =  0x20;// DeathType
			return 0;}
		if( gtw1 > 0){

			if(tusr->gtw &&  susr->isMapRange(112) ){
				*(DWORD *)((DWORD)targetPointer + 0x7220) =  0x20;// DeathType
			return 0;}
			if( tusr->isMapRange(112) && susr->isMapRange(112) ){
				*(DWORD *)((DWORD)targetPointer + 0x7220) =  0x20;// DeathType
				return 0;}
			if( tusr->isMapRange(112) && susr->gtw ){
				*(DWORD *)((DWORD)targetPointer + 0x7220) =  0x20;// DeathType
				return 0;}

		}
		if( gtw2 > 0){
			if(tusr->gtw &&  susr->isMapRange(113) ){
				*(DWORD *)((DWORD)targetPointer + 0x7220) =  0x20;// DeathType
				return 0;}
			if( tusr->isMapRange(113) && susr->isMapRange(113) ){
				*(DWORD *)((DWORD)targetPointer + 0x7220) =  0x20;// DeathType
				return 0;}
			if( tusr->isMapRange(113) && susr->gtw ){
				*(DWORD *)((DWORD)targetPointer + 0x7220) =  0x20;// DeathType
				return 0;}

		}
		
	
	}
 // end my junk


  if ( tGuildNumber != uGuildnumber || uGuildnumber == -1 )
  {
	  tDeathType = tusr->getDeathType(); 
    if ( tDeathType & 0x20 ){
		*(DWORD *)((DWORD)targetPointer + 0x7220) = tDeathType ^ 0x20;}
	if ( tGuildNumber == uGuildnumber && susr->isInGuildWar() )// GuildWarGuildNum && bInGuildWar
    {
      if ( tusr->isInGuildWar() )
      {
		  if ( tusr->getGuildWarNum() == uGuildnumber )// GuildWarGuildNum == GuildNumber
        {      
          *(DWORD *)((DWORD)targetPointer + 0x7220) = *(DWORD *)((DWORD)targetPointer + 0x7220) | 0x20;// DeathType
        }
      }
	  
      result = 0;
    }
    else
    {
		result = (!tusr->isMapRange(107) || !susr->isMapRange(107));
    }
  }
  else
  {
    result = 0;
  }
  return result;

}

signed int __stdcall ServerHookInterface::User__cgray_wrapper(void* sourcePointer, void* targetPointer){

  signed int v6; // ecx@7
  signed int v8; // esi@15

  
  User* susr = User::getExtentionUserFromRealUser(sourcePointer);
  User* tusr = User::getExtentionUserFromRealUser(targetPointer);

  
  if ( !targetPointer ){
	  return 0; }

  if ( susr->CheckMonster(susr->getClass()) != tusr->CheckMonster(tusr->getClass()) ){
	  return 0;}
  
  if ( susr->CheckDemon(susr->getClass()) != tusr->CheckDemon(tusr->getClass()) ){
	  return 0; }
 
  v6 = tusr->getMoral(); // *(_DWORD *)(targetPointer + 0x722C);
  if ( tusr->CheckDemon(tusr->getClass()) )
  {
    if ( v6 / 100000 > 30 ){
		return 0;}
  }
  else
  {
	  if ( v6 / 100000 <= -31 ){
		  return 0;}
  } 
 

  // my junk
  if(gtw1 > 0 || gtw2 > 0 ){
		//result = 0;
		if(tusr->gtw && susr->gtw){return 0;}
		if( gtw1 > 0){

			if(tusr->gtw &&  susr->isMapRange(112) ){return 0;}
			if( tusr->isMapRange(112) && susr->isMapRange(112) ){return 0;}
			if( tusr->isMapRange(112) && susr->gtw ){return 0;}

		}
		if( gtw2 > 0){
			if(tusr->gtw &&  susr->isMapRange(113) ){return 0;}
			if( tusr->isMapRange(113) && susr->isMapRange(113) ){return 0;}
			if( tusr->isMapRange(113) && susr->gtw ){return 0;}

		}
		
	
	}
 // end my junk

  if ( !tusr->isMapRange(107) || !susr->isMapRange(107) )
  {
    v8 = 0;
    while ( !*(int *)((char *)0x509E90 + v8)
         || !tusr->isMapRange(*(int *)((char *)0x509E6C + v8))
			|| !susr->isMapRange(*(int *)((char *)0x509E6C + v8))
			|| susr->getGuildId() == 0xFFFFFFFF )  {

      v8 += 4;
      if ( v8 >= 8 )
        return 1;
    }
  } 
  return 0;

}

signed int __stdcall ServerHookInterface::checkgwa_wrapper(void* sourcePointer, void* targetPointer){

  signed int result; // eax@4
  signed int v4; // esi@8

  User* susr = User::getExtentionUserFromRealUser(sourcePointer);
  User* tusr = User::getExtentionUserFromRealUser(targetPointer);

  if ( targetPointer )
  {
	if ( tusr->getGuildId() == susr->getGuildWarNum() && susr->isInGuildWar() ) {
      result = 1;
    }
	else if(gtw1 > 0 || gtw2 > 0 ){
		result = 0;
		if(tusr->gtw && susr->gtw){result = 1;}
		if( gtw1 > 0){

			if(tusr->gtw &&  susr->isMapRange(112) ){result = 1;}
			if( tusr->isMapRange(112) && susr->isMapRange(112) ){result = 1;}
			if( tusr->isMapRange(112) && susr->gtw ){result = 1;}

		}
		if( gtw2 > 0){
			if(tusr->gtw &&  susr->isMapRange(113) ){result = 1;}
			if( tusr->isMapRange(113) && susr->isMapRange(113) ){result = 1;}
			if( tusr->isMapRange(113) && susr->gtw ){result = 1;}

		}
		
	
	}
    else
    {
		if ( !tusr->isMapRange(107) || !susr->isMapRange(107))
      {
        v4 = 0;
        while ( !*(int *)((char *)0x509E90 + v4)
			|| !tusr->isMapRange(*(int *)((char *)0x509E6C + v4))
			|| !susr->isMapRange(*(int *)((char *)0x509E6C + v4))
			|| susr->getGuildId() == 0xFFFFFFFF )
        {
          v4 += 4;
          if ( v4 >= 8 )
            goto LABEL_14;
        }
      }
      result = 1;
    }
  }
  else
  {
LABEL_14:
    result = 0;
  }
  return result;

}
  
void __stdcall ServerHookInterface::User__slmsg_wrapper(void* userPointer, int addr){
	// thebyte is usually 1
	User* usr = User::getExtentionUserFromRealUser(userPointer);

	printf("msg(%s)->1:%d 2:%d 3:%d 4:%d  \n", (const char*)usr->getName(),*(DWORD *)(addr + 0x10), *(DWORD *)(addr + 0x18), *(DWORD *)(addr + 0x20),  *(DWORD *)(addr + 0x28) );

	 
	/*

void (__thiscall  *User__slmsg_wrapper)(void* userPointer, int addr) = ((void(__thiscall  *)(void* userPointer, int))0x00466B60);
User__slmsg_wrapper( userPointer, addr);
*/
 int result;
 WORD v9[2]; 

  *(DWORD *)v9 = 0;
  result = GetShort((BYTE *)addr, (DWORD *)v9);

  result = *((DWORD *)userPointer + 0x1DC4 + result); //event selected
int rest2 = *((DWORD *)userPointer + 0x1DC5 + result); //event selected
int res3 = *((DWORD *)userPointer + 0x1DC6 + result); //event selected
int res4 = *((DWORD *)userPointer + 0x1DC7 + result); //event selected
	
  printf("msg(%s)-> eventselected:%d %d %d %d \n", (const char*)usr->getName(), result,rest2,res3,res4 );

  if (usr->getZone() == 2 && result == 65 && !usr->CheckGuildTown(14) && !usr->CheckGuildTownAlly(14) && usr->getGuildRank() > 0){
   
	  if (gtw1 > 0 && usr->gtw){ // check valid war
		  
		    CGOdbcConnect cCon;
    try
    {
        cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);
		
    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return ;
    }

    //printf("Driver: %s\n", cCon.getDriver());

	char szQuery[300];
	
	//sprintf(szQuery, "Insert into pklog (sourcename, targetname, pos,type) values ('%s', '%s','%d','%d')",source,target,pos,type);

	sprintf(szQuery, "{call proc_atkguild ('%d','%d')}",14,usr->getGuildId());
	 

    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
		    //printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        printf("Insert Error\n%s\n", pE->getMsg());
        return ;
    }

	 	  try
    {
        if (!pCur->bindAuto())
        {
            printf("cursor doesn't contain resultset\n");
            return ;
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("binding error\n%s\n", pE->getMsg());
        return ;
    }

    int pos;
	int res;
       char strmessage[91];
	   const char *pBuff;
	try
    {
        bool bRC;
        for (bRC = pCur->first(); bRC; bRC = pCur->next())
        {

            res = pCur->getInt("res");
			pos = pCur->getInt("gpos");
		//	printf("total kill count: %d \n",totalcount);

        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("load cursor error\n%s\n", pE->getMsg());
        return ;
    }
        

    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();
	char guildmess[4000];
	
	if(res){ // take over
	sprintf(guildmess,"<<< You have taken over Susa and gained %d Pos!>>>",pos);
	usr->sendguildtxt(guildmess);
		char atkmes[100];
		sprintf(atkmes,"<<< %s of %s guild has claimed Susa and gained %d Guild Pos! >>>",usr->getName(),usr->getGuildName(),pos);
		usr->SendAllMessage(atkmes);
	// update guildtown table
	void (__thiscall  *User__upgt_wrapper)() = ((void(__thiscall  *)())0x00423460);
    User__upgt_wrapper( );

	}
	else{
	          // gained pos
		sprintf(guildmess,"<<< You have sacked Susa and gained %d Pos!>>>",pos);
		usr->sendguildtxt(guildmess);
		char atkmes[100];
		sprintf(atkmes,"<<< %s of %s guild has sacked Susa and gained %d Guild Pos! >>>",usr->getName(),usr->getGuildName(),pos);
		usr->SendAllMessage(atkmes);
	}
	//reset shit
	Guild__town_war_end(1);

	  }
	  // war not valid
	  usr->sendChatMessage("<<< You cannot do that when there is no war >>>");
  }
	 // ============================================================== ========================================================

    if (usr->getZone() == 2 && result == 68 && !usr->CheckGuildTown(15) && !usr->CheckGuildTownAlly(15) && usr->getGuildRank() > 0){
   
	  if (gtw2 > 0 && usr->gtw){ // check valid war
		  
		    CGOdbcConnect cCon;
    try
    {
       cCon.connect(cfg->DSN, cfg->UID, cfg->PWD);
	
    }
    catch(CGOdbcEx *pE)
    {
        printf("connection error\n%s\n", pE->getMsg());
        return ;
    }

    //printf("Driver: %s\n", cCon.getDriver());

	char szQuery[300];
	
	//sprintf(szQuery, "Insert into pklog (sourcename, targetname, pos,type) values ('%s', '%s','%d','%d')",source,target,pos,type);

	sprintf(szQuery, "{call proc_atkguild ('%d','%d')}",15,usr->getGuildId());
	 

    CGOdbcStmt *pCur;

    pCur = cCon.createStatement();
    try
    {
		
        pCur->execute(szQuery);
		    //printf(">>row inserted!\n");
    }
     catch(CGOdbcEx *pE)
    {
        printf("Insert Error\n%s\n", pE->getMsg());
        return ;
    }

	 	  try
    {
        if (!pCur->bindAuto())
        {
            printf("cursor doesn't contain resultset\n");
            return ;
        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("binding error\n%s\n", pE->getMsg());
        return ;
    }

    int pos;
	int res;
       char strmessage[91];
	   const char *pBuff;
	try
    {
        bool bRC;
        for (bRC = pCur->first(); bRC; bRC = pCur->next())
        {

            res = pCur->getInt("res");
			pos = pCur->getInt("gpos");
		//	printf("total kill count: %d \n",totalcount);

        }
    }
    catch(CGOdbcEx *pE)
    {
        cCon.freeStatement(pCur);
        printf("load cursor error\n%s\n", pE->getMsg());
        return ;
    }
        

    cCon.freeStatement(pCur);
 cCon.commit();
    cCon.setTransMode(true);
    cCon.close();
	char guildmess[4000];
	
	if(res){ // take over
	sprintf(guildmess,"<<< You have taken over Dina and gained %d Pos!>>>",pos);
	usr->sendguildtxt(guildmess);
		char atkmes[100];
		sprintf(atkmes,"<<< %s of %s guild has claimed Dina and gained %d Guild Pos! >>>",usr->getName(),usr->getGuildName(),pos);
		usr->SendAllMessage(atkmes);
	// update guildtown table
	void (__thiscall  *User__upgt_wrapper)() = ((void(__thiscall  *)())0x00423460);
    User__upgt_wrapper( );

	}
	else{
	          // gained pos
		sprintf(guildmess,"<<< You have sacked Dina and gained %d Pos!>>>",pos);
		usr->sendguildtxt(guildmess);
		char atkmes[100];
		sprintf(atkmes,"<<< %s of %s guild has sacked Dina and gained %d Guild Pos! >>>",usr->getName(),usr->getGuildName(),pos);
		usr->SendAllMessage(atkmes);
	}
	//reset shit
	Guild__town_war_end(2);

	  }
	  // war not valid
	  usr->sendChatMessage("<<< You cannot do that when there is no war >>>");
  }
// ============================ guild town 1 upgrader ==============
    if (usr->getZone() == 2 && result == 78 && usr->CheckGuildTown(14) ){
   
	  if (gtw2 > 0 ){ // check valid war
		  usr->sendChatMessage("<<< You cannot do that during war! >>>");
	  }
	  else{
		  char itemmes[100];
		  sprintf(itemmes,"- Item Shop (lv.%d)",itemgt1);
		  if (itemgt1 <3){
			  usr->Selectmsg("Select what function you'd like to upgrade (50 guild pos each)",itemmes,"- Archer Division","- Fortify Walls","- Commander",90,91,92,93);
		  return;
		  }
		  else{
		      usr->Selectmsg("Select what function you'd like to upgrade (50 guild pos each)","- Archer Division","- Fortify Walls","- Commander","- Nevermind",91,92,93,-1);
		  return;
		  }
	  }
  }

  if (usr->getZone() == 2 && result == 90 && usr->CheckGuildTown(14) ){  // itemshop
  
	  if ( setguildpos(usr->getGuildId(),usr->getName(),50) > 0){ //check enough guild pos
	  char itemmes[100];
	      itemgt1++;
		  sprintf(itemmes,"<<< Congratulations! Item Shop is now lv.%d >>>",itemgt1);
		  usr->sendguildtxt(itemmes);
	  }
	  else{
		  usr->sendChatMessage("<<< You do not have enough Guild Pos >>>");
	  }
  }

  if (usr->getZone() == 2 && result == 91 && usr->CheckGuildTown(14) ){ // archers
  
	  if ( setguildpos(usr->getGuildId(),usr->getName(),50) > 0){ //check enough guild pos
		
		  usr->LiveNPC(40251,-1, -1, -1);

		  usr->sendguildtxt("<<< Congratulations! Archer Division have joined your ranks >>>");
	  }
	  else{
		  usr->sendChatMessage("<<< You do not have enough Guild Pos >>>");
	  }
  }

  if (usr->getZone() == 2 && result == 92 && usr->CheckGuildTown(14) ){ // extra walls
  
	  if ( setguildpos(usr->getGuildId(),usr->getName(),50) > 0){ //check enough guild pos
		
		  usr->LiveNPC(40259,-1, -1, -1);
		   usr->LiveNPC(40260,-1, -1, -1);
		    usr->LiveNPC(40261,-1, -1, -1);
			 usr->LiveNPC(40262,-1, -1, -1);

		  usr->sendguildtxt("<<< Congratulations! The town walls have been fortified >>>");
	  }
	  else{
		  usr->sendChatMessage("<<< You do not have enough Guild Pos >>>");
	  }
  }

  if (usr->getZone() == 2 && result == 93 && usr->CheckGuildTown(14) ){ // commander
  
	  if ( setguildpos(usr->getGuildId(),usr->getName(),50) > 0){ //check enough guild pos
		
		  usr->LiveNPC(40249,-1, -1, -1);

		  usr->sendguildtxt("<<< Congratulations! Commander have joined your ranks >>>");
	  }
	  else{
		  usr->sendChatMessage("<<< You do not have enough Guild Pos >>>");
	  }
  }
// ============================ guild town 2 upgrader ==============
  if (usr->getZone() == 2 && result == 79 && usr->CheckGuildTown(15) ){
   
	  if (gtw2 > 0 ){ // check valid war
		  usr->sendChatMessage("<<< You cannot do that during war! >>>");
	  }
	  else{
		  char itemmes[100];
		  sprintf(itemmes,"- Item Shop (lv.%d)",itemgt2);
		  if (itemgt2 <3){
			  usr->Selectmsg("Select what function you'd like to upgrade (50 guild pos each)",itemmes,"- Archer Division","- Fortify Walls","- Commander",86,87,88,89);
			  return;
		  }
		  else{
		      usr->Selectmsg("Select what function you'd like to upgrade (50 guild pos each)","- Archer Division","- Fortify Walls","- Commander","- Nevermind",87,88,89,-1);
		      return;
		  }
	  }
  }

  if (usr->getZone() == 2 && result == 86 && usr->CheckGuildTown(15) ){  // itemshop
  
	  if ( setguildpos(usr->getGuildId(),usr->getName(),50) > 0){ //check enough guild pos
	  char itemmes[100];
	      itemgt2++;
		  sprintf(itemmes,"<<< Congratulations! Item Shop is now lv.%d >>>",itemgt2);
		  usr->sendguildtxt(itemmes);
	  }
	  else{
		  usr->sendChatMessage("<<< You do not have enough Guild Pos >>>");
	  }
  }

  if (usr->getZone() == 2 && result == 87 && usr->CheckGuildTown(15) ){ // archers
  
	  if ( setguildpos(usr->getGuildId(),usr->getName(),50) > 0){ //check enough guild pos
		
		  usr->LiveNPC(40252,-1, -1, -1);

		  usr->sendguildtxt("<<< Congratulations! Archer Division have joined your ranks >>>");
	  }
	  else{
		  usr->sendChatMessage("<<< You do not have enough Guild Pos >>>");
	  }
  }

  if (usr->getZone() == 2 && result == 88 && usr->CheckGuildTown(15) ){ // extra walls
  
	  if ( setguildpos(usr->getGuildId(),usr->getName(),50) > 0){ //check enough guild pos
		
		  usr->LiveNPC(40267,-1, -1, -1);
		   usr->LiveNPC(40268,-1, -1, -1);
		    usr->LiveNPC(40269,-1, -1, -1);
			 usr->LiveNPC(40270,-1, -1, -1);

			 usr->sendguildtxt("<<< Congratulations! The town walls have been fortified >>>");
	  }
	  else{
		  usr->sendChatMessage("<<< You do not have enough Guild Pos >>>");
	  }
  }
  
  if (usr->getZone() == 2 && result == 89 && usr->CheckGuildTown(15) ){ // commander
  
	  if ( setguildpos(usr->getGuildId(),usr->getName(),50) > 0){ //check enough guild pos
		
		  usr->LiveNPC(40250,-1, -1, -1);

		  usr->sendguildtxt("<<< Congratulations! Commander have joined your ranks >>>");
	  }
	  else{
		  usr->sendChatMessage("<<< You do not have enough Guild Pos >>>");
	  }
  }

  if (usr->getZone() == 2 && result == 73){ // town 1 itemshop
	  usr->SendStoreOpen(40+itemgt1,100+gt1tax,80,14);
  
  }

    if (usr->getZone() == 2 && result == 75){ // town 2 itemshop
		 usr->SendStoreOpen(40+itemgt2,100+gt2tax,80,15);
  
  }
// try to handel recv message in extention
if((int)result >0)
	{
	// event manager look up test
	//	printf("EVENT MANAGER LOOK UP\n");
		//can't have nice things
	 // EventManager* evtmngr = new EventManager();
	//	printf("EVENT %d on ZONE %d :\n",(int)ievent,(int)susr->getZone());
	
		if(evtmngr != NULL)
		{
		EventData* evt = evtmngr->GetEventData((int)usr->getZone(),(int)result);
			if(evt)
			{ // not null



					  usr->RunExtEvent((int)userPointer, (int)usr->plastnpc,(int)result,(int)usr->getZone(),evtmngr);
						//reset shit?
						 *((DWORD *)userPointer + 0x1DC4) = -1;
 						 *((DWORD *)userPointer + 0x1DC5) = -1;
 						 *((DWORD *)userPointer + 0x1DC6) = -1;
  						 *((DWORD *)userPointer + 0x1DC7) = -1;
					  return ;
			}
			else
			{
				printf("EVENT %d on ZONE %d NOT FOUND!\n",(int)result,(int)usr->getZone());
			}

		}
		else{
		   printf("EVENT Manager NOT INITILIZED!\n");
		}

	}	
					//	*((DWORD *)userPointer + 0x1DC4) = -1;
 					//	 *((DWORD *)userPointer + 0x1DC5) = -1;
 					//	 *((DWORD *)userPointer + 0x1DC6) = -1;
  					//	 *((DWORD *)userPointer + 0x1DC7) = -1;
	return ;
//void (__thiscall  *User__slmsg_wrapper)(void* userPointer, int addr) = ((void(__thiscall  *)(void* userPointer, int))0x00466DF0);
//User__slmsg_wrapper( userPointer, addr);

}

		  
// Attack ?


signed int ServerHookInterface::User__checkspecialattackdelay_wrapper(void* userPointer, void* pSpecial)
{
	DWORD curTick;
	DWORD spLastUseTick;
	int iTerm;

	User* susr = User::getExtentionUserFromRealUser(userPointer);

	//uP = SpecialAttackDelay;
	curTick = GetTickCount();
	//v3 = *(_DWORD*)(uP + 0x77EC);

	int iSpSlot = (*(DWORD*)((BYTE*)pSpecial + 0x4)) - 1;

	spLastUseTick = susr->iASpecialAttackDelay[iSpSlot];

	iTerm = *(DWORD*)((BYTE*)pSpecial + 0x5C);

	if (spLastUseTick >= curTick)
	{
		if (spLastUseTick > curTick)
		{
			// 0x77EC = specialattackdelay
			//*(DWORD*)((BYTE*)susr->realUser + 0x77EC) = curTick;
			susr->iASpecialAttackDelay[iSpSlot] = curTick;
			*(DWORD*)((BYTE*)susr->realUser + 0x77F8) = iTerm;
			*(DWORD*)((BYTE*)susr->realUser + 0x77F0) = *(DWORD*)((BYTE*)pSpecial + 0x4); // sMid

			return 1;
		}
	}
	else if (curTick - spLastUseTick >= susr->getAttackDelay())//*(DWORD*)((BYTE*)susr->realUser + 0x77F8))
	{
		//*(DWORD*)(uP + 0x77EC) = curTick;
		susr->iASpecialAttackDelay[iSpSlot] = curTick;
		//v7 = *(DWORD*)(pSpecial + 4);
		*(DWORD*)((BYTE*)susr->realUser + 0x77F8) = iTerm;
		*(DWORD*)((BYTE*)susr->realUser + 0x77F0) = *(DWORD*)((BYTE*)pSpecial + 0x4);

		return 1;
	}

	return 0;
}


