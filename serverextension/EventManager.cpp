#include "StdAfx.h"
#include "EventManager.h"

#include <share.h>
#include <fcntl.h>
#include <io.h>

EventManager::EventManager(void)
{
	// initalize
	this->LoadEvents(); //load events into memory
}


EventManager::~EventManager(void)
{
	//clean up
	std::map<std::pair<int,int>,EventData*>::iterator it;

	for (it =this->EventMap.begin(); it !=this->EventMap.end(); it++ ){
	 delete	it->second; // destroy
	}
	this->EventMap.clear();

}


void EventManager::LoadEvents(void)
{
	printf("clearing event manager data...\n");
		//clean up (for reload call)
	std::map<std::pair<int,int>,EventData*>::iterator it;
	if(this->EventMap.size() > 0){
   	  for (it =this->EventMap.begin(); it !=this->EventMap.end(); it++ ){
	     delete	it->second; // destroy
	  }
	  
	}
	this->EventMap.clear();
	

printf("loading event manager data...\n");

	// go through extention folder and load the valid files in that directory.
	   DIR *dir;
   struct dirent *ent;
   if ((dir = opendir (".\\extEvent\\")) != NULL) {
     // print all the files and directories within directory 
     while ((ent = readdir (dir)) != NULL) {
      // printf ("%s\n", ent->d_name);
         int d =-1;
         int ret = sscanf(ent->d_name,"%d.evt",&d);

         char cmpname[128];
         sprintf(cmpname,"%d.evt",d);
         //strcmp(ent->d_name,cmpname) == 0
		 if(strcmp(ent->d_name,cmpname) == 0){ //valid format
			 // call function to read and parse file
			 printf("valid file: %s compare name: %s \n",ent->d_name,cmpname);
			 this->ParseFile(ent->d_name,d);
		 }
		 else{ // invalid format skipping
			 continue;
		 }

	 }
     closedir (dir);
   } else {
     // could not open directory
    printf("Could not open extention Event directory\n");
   }
   


   printf("finished event manager data!\n");
return;
}

int EventManager::GetExecType(const char* ch)
{
	if(strcmp(ch,"E") == 0){
		return 2;
	}
	if(strcmp(ch,"A") == 0){
		return 0;
	}
	if(strcmp(ch,"O") == 0){
		return 1;
	}
	printf("unknown logic!: %s\n",ch);
	return -1;
}

int EventManager::GetCommandType(const char* ch)
{

        if(!strcmp(ch,"LINK")){
                return LINK;
        }
        if(!strcmp(ch,"SAY")){
                return SAY;
        }
        if(!strcmp(ch,"STORE_OPEN")){
                return STORE_OPEN;
        }
        if(!strcmp(ch,"GIVE_ITEM")){
                return GIVE_ITEM;
        }
        if(!strcmp(ch,"ROB_ITEM")){
                return ROB_ITEM;
        }
        if(!strcmp(ch,"GIVE_MAGIC")){
                return GIVE_MAGIC;
        }
        if(!strcmp(ch,"ROB_MAGIC")){
                return ROB_MAGIC;
        }
        if(!strcmp(ch,"BBS_OPEN")){
                return BBS_OPEN;
        }
        if(!strcmp(ch,"DISAPPEAR")){
                return DISAPPEAR;
        }
        if(!strcmp(ch,"RUN_MAGIC")){
                return RUN_MAGIC;
        }
        if(!strcmp(ch,"DEAD")){
                return DEAD;
        }
        if(!strcmp(ch,"CHANGE_LEVEL")){
                return CHANGE_LEVEL;
        }
        if(!strcmp(ch,"CHANGE_GENDER")){
                return CHANGE_GENDER;
        }
        if(!strcmp(ch,"CHANGE_HP")){
                return CHANGE_HP;
        }
        if(!strcmp(ch,"CHANGE_MP")){
                return CHANGE_MP;
        }
        if(!strcmp(ch,"CHANGE_STR")){
                return CHANGE_STR;
        }
        if(!strcmp(ch,"CHANGE_DEX")){
                return CHANGE_DEX;
        }
        if(!strcmp(ch,"CHANGE_INT")){
                return CHANGE_INT;
        }
        if(!strcmp(ch,"CHANGE_WIS")){
                return CHANGE_WIS;
        }
        if(!strcmp(ch,"CHANGE_CHA")){
                return CHANGE_CHA;
        }
        if(!strcmp(ch,"CHANGE_CON")){
                return CHANGE_CON;
        }
        if(!strcmp(ch,"CHANGE_DMAGIC")){
                return CHANGE_DMAGIC;
        }
        if(!strcmp(ch,"CHANGE_WMAGIC")){
                return CHANGE_WMAGIC;
        }
        if(!strcmp(ch,"CHANGE_BMAGIC")){
                return CHANGE_BMAGIC;
        }
        if(!strcmp(ch,"CHANGE_SWORD")){
                return CHANGE_SWORD;
        }
        if(!strcmp(ch,"CHANGE_SPEAR")){
                return CHANGE_SPEAR;
        }
        if(!strcmp(ch,"CHANGE_AXE")){
                return CHANGE_AXE;
        }
        if(!strcmp(ch,"CHANGE_BOW")){
                return CHANGE_BOW;
        }
        if(!strcmp(ch,"CHANGE_KNUCKLE")){
                return CHANGE_KNUCKLE;
        }
        if(!strcmp(ch,"CHANGE_WEAPONMAKE")){
                return CHANGE_WEAPONMAKE;
        }
        if(!strcmp(ch,"CHANGE_ARMORMAKE")){
                return CHANGE_ARMORMAKE;
        }
        if(!strcmp(ch,"CHANGE_ACCMAKE")){
                return CHANGE_ACCMAKE;
        }
        if(!strcmp(ch,"CHANGE_POTIONMAKE")){
                return CHANGE_POTIONMAKE;
        }
        if(!strcmp(ch,"CHANGE_COOKING")){
                return CHANGE_COOKING;
        }
        if(!strcmp(ch,"SHOW_MAGIC")){
                return SHOW_MAGIC;
        }
        if(!strcmp(ch,"MAKER_OPEN")){
                return MAKER_OPEN;
        }
        if(!strcmp(ch,"STORAGE_OPEN")){
                return STORAGE_OPEN;
        }
        if(!strcmp(ch,"AUCTION_SELL_OPEN")){
                return AUCTION_SELL_OPEN;
        }
        if(!strcmp(ch,"AUCTION_BUY_OPEN")){
                return AUCTION_BUY_OPEN;
        }
        if(!strcmp(ch,"SELECT_MSG")){
                return SELECT_MSG;
        }
        if(!strcmp(ch,"MESSAGE_OK")){
                return MESSAGE_OK;
        }
        if(!strcmp(ch,"MESSAGE_NONE")){
                return MESSAGE_NONE;
        }
        if(!strcmp(ch,"GIVE_GOLD")){
                return GIVE_GOLD;
        }
        if(!strcmp(ch,"ROB_GOLD")){
                return ROB_GOLD;
        }
        if(!strcmp(ch,"RUN_EVENT")){
                return RUN_EVENT;
        }
        if(!strcmp(ch,"ADD_EVENT")){
                return ADD_EVENT;
        }
        if(!strcmp(ch,"DEL_EVENT")){
                return DEL_EVENT;
        }
        if(!strcmp(ch,"RAND_SAY")){
                return RAND_SAY;
        }
        if(!strcmp(ch,"RETURN")){
                return RETURN;
        }
        if(!strcmp(ch,"CHANGE_MAGETYPE")){
                return CHANGE_MAGETYPE;
        }
        if(!strcmp(ch,"GUILD_OPEN")){
                return GUILD_OPEN;
        }
        if(!strcmp(ch,"REPAIR_ITEM_OPEN")){
                return REPAIR_ITEM_OPEN;
        }
        if(!strcmp(ch,"GIVE_SPECIAL_ATTACK")){
                return GIVE_SPECIAL_ATTACK;
        }
        if(!strcmp(ch,"KILL_NPC")){
                return KILL_NPC;
        }
        if(!strcmp(ch,"PLUS_MORAL")){
                return PLUS_MORAL;
        }
        if(!strcmp(ch,"OPEN_CONTRIBUTION")){
                return OPEN_CONTRIBUTION;
        }
        if(!strcmp(ch,"CHANGE_STORAGE_TYPE")){
                return CHANGE_STORAGE_TYPE;
        }

        if(!strcmp(ch,"WARP_GATE")){
                return WARP_GATE;
        }
        if(!strcmp(ch,"AUCTION_DRAW_NOBID")){
                return AUCTION_DRAW_NOBID;
        }
        if(!strcmp(ch,"AUCTION_DRAW_NOBUY")){
                return AUCTION_DRAW_NOBUY;
        }
        if(!strcmp(ch,"AUCTION_BUY_ITEM")){
                return AUCTION_BUY_ITEM;
        }
        if(!strcmp(ch,"AUCTION_GET_MONEY")){
                return AUCTION_GET_MONEY;
        }
        if(!strcmp(ch,"AUCTION_DELETE_BADLIST")){
                return AUCTION_DELETE_BADLIST;
        }
        if(!strcmp(ch,"CHANGE_MAX_HP")){
                return CHANGE_MAX_HP;
        }
        if(!strcmp(ch,"CHANGE_MAX_MP")){
                return CHANGE_MAX_MP;
        }
        if(!strcmp(ch,"CHANGE_MAX_STM")){
                return CHANGE_MAX_STM;
        }
        if(!strcmp(ch,"CHANGE_MAX_WGT")){
                return CHANGE_MAX_WGT;
        }

        if(!strcmp(ch,"OPEN_HAIRSHOP")){
                return OPEN_HAIRSHOP;
        }
        if(!strcmp(ch,"LIVE_NPC")){
                return LIVE_NPC;
        }
        if(!strcmp(ch,"ADD_SERVER_EVENT")){
                return ADD_SERVER_EVENT;
        }
        if(!strcmp(ch,"DEL_SERVER_EVENT")){
                return DEL_SERVER_EVENT;
        }
        if(!strcmp(ch,"GIVE_MAKE_SKILL")){
                return GIVE_MAKE_SKILL;
        }
        if(!strcmp(ch,"OPEN_SPECIAL_MAKESKILL")){
                return OPEN_SPECIAL_MAKESKILL;
        }
        if(!strcmp(ch,"OPEN_GUILDTOWN_STONE")){
                return OPEN_GUILDTOWN_STONE;
        }
        if(!strcmp(ch,"GUILDTOWN_TAXRATE")){
                return GUILDTOWN_TAXRATE;
        }
        if(!strcmp(ch,"OPEN_GUILDTOWN_STORE_REG")){
                return OPEN_GUILDTOWN_STORE_REG;
        }
        if(!strcmp(ch,"OPEN_GUILDTOWN_STORE")){
                return OPEN_GUILDTOWN_STORE;
        }

        if(!strcmp(ch,"MAGIC")){
                return MAGIC;
        }
        if(!strcmp(ch,"SPECIAL_ATTACK")){
                return SPECIAL_ATTACK;
        }
        if(!strcmp(ch,"OPEN_TRADER")){
                return OPEN_TRADER;
        }
        if(!strcmp(ch,"OPEN_CHANGE_ITEM")){
                return OPEN_CHANGE_ITEM;
        }
        if(!strcmp(ch,"COUNTER_START")){
                return COUNTER_START;
        }
        if(!strcmp(ch,"COUNTER_INIT")){
                return COUNTER_INIT;
        }
        if(!strcmp(ch,"OPEN_MONSTER_SELECT")){
                return OPEN_MONSTER_SELECT;
        }
        if(!strcmp(ch,"TIMER_START")){
                return TIMER_START;
        }
        if(!strcmp(ch,"TIMER_INIT")){
                return TIMER_INIT;
        }

        if(!strcmp(ch,"SET_EVENTCOUNT")){
                return SET_EVENTCOUNT;
        }

        if(!strcmp(ch,"RESET_EVENTCOUNT")){
                return RESET_EVENTCOUNT;
        }

        if(!strcmp(ch,"CLASSPOINT_STORE_OPEN")){
                return CLASSPOINT_STORE_OPEN;
        }

        if(!strcmp(ch,"OPEN_MONSTER_ZONE")){
                return OPEN_MONSTER_ZONE;
        }
        if(!strcmp(ch,"XMASPOINT_USER")){
                return XMASPOINT_USER;
        }
        if(!strcmp(ch,"XMASPOINT_GUILD")){
                return XMASPOINT_GUILD;
        }
        if(!strcmp(ch,"CHANGE_PKMODE")){
                return CHANGE_PKMODE;
        }
        if(!strcmp(ch,"GET_POSITEM")){
                return GET_POSITEM;
        }

		if(!strcmp(ch,"RETURN")){
                return RETURN;
        }

		if(!strcmp(ch,"RAIN")){
                return RAIN;
        }

		if(!strcmp(ch,"SHOW_DIR")){
                return SHOW_DIR;
        }

// A/O commands add 1000
        if(!strcmp(ch,"LEVEL")){
                return 1000+ EVT_LEVEL;
        }
        if(!strcmp(ch,"GENDER")){
                return 1000+ EVT_GENDER;
        }
        if(!strcmp(ch,"AGE")){
                return 1000+ EVT_AGE;
        }
        if(!strcmp(ch,"HP")){
                return 1000+ EVT_HP;
        }
        if(!strcmp(ch,"MP")){
                return 1000+ EVT_MP;
        }
        if(!strcmp(ch,"STR")){
                return 1000+ EVT_STR;
        }
        if(!strcmp(ch,"DEX")){
                return 1000+ EVT_DEX;
        }
        if(!strcmp(ch,"INT")){
                return 1000+ EVT_INT;
        }
        if(!strcmp(ch,"WIS")){
                return 1000+ EVT_WIS;
        }
        if(!strcmp(ch,"CHA")){
                return 1000+ EVT_CHA;
        }
        if(!strcmp(ch,"CON")){
                return 1000+ EVT_CON;
        }
        if(!strcmp(ch,"DMAGIC")){
                return 1000+ EVT_DMAGIC;
        }
        if(!strcmp(ch,"WMAGIC")){
                return 1000+ EVT_WMAGIC;
        }
        if(!strcmp(ch,"BMAGIC")){
                return 1000+ EVT_BMAGIC;
        }
        if(!strcmp(ch,"SWORD")){
                return 1000+ EVT_SWORD;
        }
        if(!strcmp(ch,"SPEAR")){
                return 1000+ EVT_SPEAR;
        }
        if(!strcmp(ch,"AXE")){
                return 1000+ EVT_AXE;
        }
        if(!strcmp(ch,"BOW")){
                return 1000+ EVT_BOW;
        }
        if(!strcmp(ch,"KNUCKLE")){
                return 1000+ EVT_KNUCKLE;
        }
        if(!strcmp(ch,"STAFF")){
                return 1000+ EVT_STAFF;
        }
        if(!strcmp(ch,"WEAPONMAKE")){
                return 1000+ EVT_WEAPONMAKE;
        }
        if(!strcmp(ch,"ARMORMAKE")){
                return 1000+ EVT_ARMORMAKE;
        }
        if(!strcmp(ch,"ACCMAKE")){
                return 1000+ EVT_ACCMAKE;
        }
        if(!strcmp(ch,"POTIONMAKE")){
                return 1000+ EVT_POTIONMAKE;
        }
        if(!strcmp(ch,"COOKING")){
                return 1000+ EVT_COOKING;
        }
        if(!strcmp(ch,"EXIST_ITEM")){
                return 1000+ EVT_EXIST_ITEM;
        }
        if(!strcmp(ch,"ABSENT_ITEM")){
                return 1000+ EVT_ABSENT_ITEM;
        }
        if(!strcmp(ch,"EXIST_ITEM_TYPE")){
                return 1000+ EVT_EXIST_ITEM_TYPE;
        }
        if(!strcmp(ch,"ABSENT_ITEM_TYPE")){
                return 1000+ EVT_ABSENT_ITEM_TYPE;
        }
        if(!strcmp(ch,"EXIST_MAGIC")){
                return 1000+ EVT_EXIST_MAGIC;
        }
        if(!strcmp(ch,"ABSENT_MAGIC")){
                return 1000+ EVT_ABSENT_MAGIC;
        }
        if(!strcmp(ch,"EXIST_MAGETYPE")){
                return 1000+ EVT_EXIST_MAGETYPE;
        }
        if(!strcmp(ch,"ABSENT_MAGETYPE")){
                return 1000+ EVT_ABSENT_MAGETYPE;
        }
        if(!strcmp(ch,"EXIST_SPECIAL_ATTACK")){
                return 1000+ EVT_EXIST_SPECIAL_ATTACK;
        }
        if(!strcmp(ch,"ABSENT_SPECIAL_ATTACK")){
                return 1000+ EVT_ABSENT_SPECIAL_ATTACK;
        }
        if(!strcmp(ch,"EXIST_MAKE_SKILL")){
                return 1000+ EVT_EXIST_MAKE_SKILL;
        }
        if(!strcmp(ch,"ABSENT_MAKE_SKILL")){
                return 1000+ EVT_ABSENT_MAKE_SKILL;
        }
        if(!strcmp(ch,"EXIST_EVENT")){
                return 1000+ EVT_EXIST_EVENT;
        }
        if(!strcmp(ch,"ABSENT_EVENT")){
                return 1000+ EVT_ABSENT_EVENT;
        }
        if(!strcmp(ch,"TIME")){
                return 1000+ EVT_TIME;
        }
        if(!strcmp(ch,"RAND")){
                return 1000+ EVT_RAND;
        }
        if(!strcmp(ch,"GOLD")){
                return 1000+ EVT_GOLD;
        }
        if(!strcmp(ch,"GAME_TIME")){
                return 1000+ EVT_GAME_TIME;
        }
        if(!strcmp(ch,"GAME_DAY")){
                return 1000+ EVT_GAME_DAY;
        }
        if(!strcmp(ch,"GAME_MONTH")){
                return 1000+ EVT_GAME_MONTH;
        }
        if(!strcmp(ch,"HOWMUCH_ITEM")){
                return 1000+ EVT_HOWMUCH_ITEM;
        }
        if(!strcmp(ch,"MORAL")){
                return 1000+ EVT_MORAL;
        }
        if(!strcmp(ch,"STORAGE_TYPE")){
                return 1000+ EVT_STORAGE_TYPE;
        }
        if(!strcmp(ch,"MAGETYPE")){
                return 1000+ EVT_MAGETYPE;
        }
        if(!strcmp(ch,"WEIGHT")){
                return 1000+ EVT_WEIGHT;
        }
        if(!strcmp(ch,"RANK")){
                return 1000+ EVT_RANK;
        }
        if(!strcmp(ch,"CHECK_ITEMSLOT")){
                return 1000+ EVT_CHECK_ITEMSLOT;
        }
        if(!strcmp(ch,"CHECK_POSITION")){
                return 1000+ EVT_CHECK_POSITION;
        }
        if(!strcmp(ch,"CHECK_FIRST_CLICK")){
                return 1000+ EVT_CHECK_FIRST_CLICK;
        }
        if(!strcmp(ch,"CHECK_AUCTION_BADLIST")){
                return 1000+ EVT_CHECK_AUCTION_BADLIST;
        }
        if(!strcmp(ch,"CHECK_AUCTION_STATE")){
                return 1000+ EVT_CHECK_AUCTION_STATE;
        }
        if(!strcmp(ch,"CHECK_ALIVE_NPC")){
                return 1000+ EVT_CHECK_ALIVE_NPC;
        }
        if(!strcmp(ch,"CHECK_GUILD_TOWN")){
                return 1000+ EVT_CHECK_GUILD_TOWN;
        }
        if(!strcmp(ch,"CHECK_GUILD_TOWN_ALLY")){
                return 1000+ EVT_CHECK_GUILD_TOWN_ALLY;
        }
        if(!strcmp(ch,"CHECK_GUILD_TOWN_WAR")){
                return 1000+ EVT_CHECK_GUILD_TOWN_WAR;
        }
        if(!strcmp(ch,"CHECK_GUILD_TOWN_LEVEL")){
                return 1000+ EVT_CHECK_GUILD_TOWN_LEVEL;
        }
        if(!strcmp(ch,"CHECK_GUILD_RANK")){
                return 1000+ EVT_CHECK_GUILD_RANK;
        }
        if(!strcmp(ch,"COMPARE_BASIC_VALUE")){
                return 1000+ EVT_COMPARE_BASIC_VALUE;
        }
        if(!strcmp(ch,"CHECK_JOB")){
                return 1000+ EVT_CHECK_JOB;
        }
        if(!strcmp(ch,"CHECK_HUMAN")){
                return 1000+ EVT_CHECK_HUMAN;
        }
        if(!strcmp(ch,"CHECK_DEMON")){
                return 1000+ EVT_CHECK_DEMON;
        }
        if(!strcmp(ch,"CHECK_MONSTER")){
                return 1000+ EVT_CHECK_MONSTER;
        }
        if(!strcmp(ch,"CHECK_COUNTER")){
                return 1000+ EVT_CHECK_COUNTER;
        }
        if(!strcmp(ch,"CHECK_TIMER")){
                return 1000+ EVT_CHECK_TIMER;
        }
        if(!strcmp(ch,"CHECK_EVENTCOUNT")){
                return 1000+ EVT_CHECK_EVENTCOUNT;
        }
        if(!strcmp(ch,"CHECK_PAYTYPE")){
                return 1000+ EVT_CHECK_PAYTYPE;
        }
        if(!strcmp(ch,"CHECK_CLASS_TOWN")){
                return 1000+ EVT_CHECK_CLASS_TOWN;
        }
        if(!strcmp(ch,"CHECK_CLASS_TOWN_WAR")){
                return 1000+ EVT_CHECK_CLASS_TOWN_WAR;
        }
        if(!strcmp(ch,"CHECK_HAVE_EVENTBOOK")){
                return 1000+ EVT_CHECK_HAVE_EVENTBOOK;
        }
        if(!strcmp(ch,"CHECK_EVENTBOOK")){
                return 1000+ EVT_CHECK_EVENTBOOK;
        }
        if(!strcmp(ch,"CHECK_PKMODE")){
                return 1000+ EVT_CHECK_PKMODE;
        }
        if(!strcmp(ch,"CHECK_PAYACCOUNT")){
                return 1000+ EVT_CHECK_PAYACCOUNT;
        }
        if(!strcmp(ch,"PAYACCOUNT")){
                   return 1000+ EVT_PAYACCOUNT;
           }

		printf("unknown command!: %s\n",ch);
	return -1;
}

EventData* EventManager::GetEventData(int zone, int eventnum){
	std::pair<int,int> key(zone,eventnum);
				if(this->EventMap.find(key) != this->EventMap.end()){ // does it exist?
					
					return this->EventMap[key];
				}
				else{
					// error event not found!
					return NULL;
				}
}

void EventManager::ParseFile( char* FileName,int zone)
{
	// read file in to memory buffer


        //printf("filename: %s zone: %d \n",FileName,zone);
	// maybe don't hard code this later
         char * dirPath =".\\extEvent\\";
		 char * FullPath = (char*) malloc(sizeof(char)*(strlen(dirPath)+strlen(FileName))+1);
		 strcpy(FullPath,dirPath);
		 strcat(FullPath,FileName);
       //  sprintf(FullPath,".\\extEvent\\%s",FileName);


		         //ifstream file("File1");
		ifstream file(FullPath);
        string line;
    	int midevent =0;
    	EventData *evt = new EventData();//NULL;
		int linenum = 0;
    	
    while (getline(file, line))
    {
		linenum++;

		if(!(line.size() > 0) )
		   continue;
        if(line[0] == ';' || line[0] == '/' || line[0] == '#') // comment 
           continue;
        stringstream linestream(line);
        string token;
        
        if(getline(linestream, token, ' ')){ // check first token
        
			if(strcmp(token.c_str(),"EVENT") == 0 && !midevent){ // new event
         				// new event! start new event data.
				evt = new EventData();
				midevent =1;
				int d =-1;
				evt->eventid = -1;
				
				if (getline(linestream, token, ' ')) // get event id
				{	 

					 int ret = sscanf(token.c_str(),"%d",&d);
					 evt->eventid = d; // add check later for missing or invalid event id
				}
				else{
				   printf("Fatal Error! Event declared with out id in zone:%d line:%d\n",zone,linenum);   
				}
                
         }
         else if(strcmp(token.c_str(),"EVENT") == 0 && midevent){ // mid event
        			// error event declared before ending old event
				// skip this command
                printf("Fatal Error! Event declared before ending old event block %d in zone:%d line:%d\n",evt->eventid,zone,linenum);        
         }
         else if(strcmp(token.c_str(),"END") == 0 )	{

		    if( midevent && evt){
			// we can end this event data and push it back on to the map
				//prepair pair
				std::pair<int,int> key(zone,evt->eventid);
				if(this->EventMap.find(key) != this->EventMap.end())
				{ // does it exist?
					//error event already defined! skipping
                    printf("Fatal Error! Event declared twice! event block %d in zone:%d line:%d\n",evt->eventid,zone,linenum);
					//reset event
					midevent =0;
				}
				else
				{
					// enter record
					this->EventMap[key] = evt;
					//reset event
					midevent =0;
				}
			}
			else{              
			    if(evt)
			       printf("Fatal Error! how did we get here end block with no midevent block %d in zone:%d line:%d\n",evt->eventid,zone,linenum);

			    if(midevent)
					printf("Fatal Error! how did we get here end block with no evt block !!in zone:%d line:%d\n",zone,linenum);

					//reset event
					midevent =0;
			}
		}
		else { // A O E etc type events 
				commands c;
				//get command type
				c.eventtype = this->GetExecType(token.c_str()); /// -1 == unknown command type

				//get command enum 
				if (c.eventtype > -1) 
				{	
					
					if (getline(linestream, token, ' ')) // check again 
				    {
						             if(!(token.size() > 0) ){
										 printf("Warning! missing Command in event block %d in zone:%d line:%d\n",evt->eventid,zone,linenum);
			   								continue;								 
									 }
									 else if(token[0] == ';' || token[0] == '/' || token[0] == '#'){
									      printf("Warning! commented Command in event block %d in zone:%d line:%d\n",evt->eventid,zone,linenum);
				                              continue;
				                             
			                           }  
									 else{
									  c.eventenum = this->GetCommandType(token.c_str()); /// -1 == unknown command

									              if(evt && c.eventenum < 0)
                                                               printf("Warning! Unknown Command type in event block %d in zone:%d line:%d\n",evt->eventid,zone,linenum);
									 }
					   
					}
					else
                    {
                     //   if(evt)
                             printf("Warning! Missing Command type in event block %d in zone:%d line:%d\n",evt->eventid,zone,linenum);
			      	}
				}
				else
                {
				//errror unknown command type or missing command type
					// just skip for now
                    
                   //  if(evt)
                         printf("Warning! Unknown Command type or missing type in event block %d in zone:%d line:%d\n",evt->eventid,zone,linenum);
				}

				while (getline(linestream, token, ' ')) // get other params
				{
					if(!(token.size() > 0) ){
					
			   				continue;								 
					}
				    if(token[0] == ';' || token[0] == '/' || token[0] == '#'){
						 //printf("Warning! commented Command in event block %d in zone:%d\n",evt->eventid,zone);
				         break;
				    }
					int p = -25555; // parameter
					sscanf(token.c_str(),"%d",&p);
					//p = atoi(token);
					if( p > -25555) // sentinal:
					    c.params.push_back(p); // add param
					
				}
			// are we mid event? then add 
				if(midevent && evt)
                {
					evt->instructions.push_back(c);
				}
				else
                {// error stray logic command
                    printf("Fetal Error! Stray Logic Command in zone:%d line:%d\n",zone,linenum);
				}

			}
		
        }
        
    }

		 
//printf("reading full pathfile: %s\n",FullPath);
/*
	//ms way
	int fd;
	long file_size;
	char *buffer;
 
	_sopen_s(&fd, FullPath, _O_RDONLY, _SH_DENYRW, _S_IREAD);
	if (fd == -1) 
	{
	  // Handle error
		printf("File Descripter Error. While Reading File: %s\n",FileName);
		return;
	}
 
	file_size = _filelength(fd);
	if (file_size == -1) {
	  // Handle error 
		printf("File Descripter Error: negative file size! While Reading File: %s\n",FileName);
		return;
	}
	 printf("requesting buffer of size: %d\n",file_size);

	buffer = (char*)malloc(sizeof(char)*(file_size));
	if (buffer == NULL)
	{
	  // Handle error 
		printf("Memory Error: buffer is NULL. While Reading File: %s\n",FileName);
		return;
	}


int result = _read( fd, buffer, file_size );
   // if (result != file_size) {

   //    printf("Read in: %d Bytes of file: %s\n  filesize",result,FileName);
     //   return;
//	}
	//   free(buffer);
      _close( fd );
	//  return;
	*/
/* sensable way 
	FILE *Filep;
    Filep = fopen(FullPath, "rb");
	if(Filep == NULL){
	printf("fuckyoums");
	}
    long Fsize;
    char *buffer;
    size_t result;

    // get file size
    fseek(Filep, 0, SEEK_END);
    Fsize = ftell(Filep);
    rewind(Filep);

    // allocate memory to contain the whole file:
    buffer = (char *)malloc(sizeof(char)*Fsize);
    if (buffer == NULL) {

         printf("Memory Error: buffer is NULL. While Reading File: %s",FileName);
        
        return;
     
    }

    // copy the file into the buffer:
    result = fread(buffer, 1, Fsize, Filep);
    if (result != Fsize) {

       printf("Read Error: unable to read file: %s",FileName);
        return;
      
    }
fclose(Filep);

*/
/*
	// now start parsing EVT script

    // get first line
    char *end_buff;
    char *line = strtok_s(buffer, "\n", &end_buff);
	int skip =0; // incase we need to do nothing for comments or error
	int midevent =0; // are we in a middle of event block?

	EventData *evt = new EventData();//NULL;

    while (line != NULL)
    {
		if(line[0] == ';' || line[0] == '/'){ // is it a comment? then skip
			skip =1;
			//continue;
		}
		else 
		{ // we're not in a comment section
	        char *end_token;
	        
	        char *token = strtok_s(line, " ", &end_token); //get first token
         if(token != NULL)
		 {
			 if(token[0] == ';' || token[0] == '/'){
				// continue;
				 skip=1;
			 }  
			else if(strcmp(token,"EVENT") == 0 && !midevent)
			{
				// new event! start new event data.
				evt = new EventData();
				midevent =1;
				int d =-1;
				evt->eventid = -1;

				if (token != NULL) // get event
				{	 

					
					 token = strtok_s(NULL, " ", &end_token);
					 int ret = sscanf(token,"%d",&d);
					 evt->eventid = d; // add check later for missing or invalid event id
				}
				
			}
			else if(strcmp(token,"EVENT") == 0 && midevent && evt)
			{
			// error event declared before ending old event
				// skip this command
                printf("Fatal Error! Event declared before ending old event block %d in zone:%d\n", evt->eventid, zone);
			}
			else if(strcmp(token,"END") == 0 )
			{

		    if( midevent && evt){
			// we can end this event data and push it back on to the map
				//prepair pair
				std::pair<int,int> key(zone,evt->eventid);
				if(this->EventMap.find(key) != this->EventMap.end())
				{ // does it exist?
					//error event already defined! skipping
                    printf("Fatal Error! Event declared twice! event block %d in zone:%d\n",evt->eventid,zone);
					//reset event
					midevent =0;
				}
				else
				{
					// enter record
					this->EventMap[key] = evt;
					//reset event
					midevent =0;
				}
			}
			else{               if(evt)
			                    printf("Fatal Error! how did we get here end block with no midevent block %d in zone:%d\n",evt->eventid,zone);

			          if(midevent)
						  printf("Fatal Error! how did we get here end block with no evt block !!in zone:%d\n",zone);

					//reset event
					midevent =0;
			}
			}
			else
            { // A O E etc type events 
				commands c;
				//get command type
				c.eventtype = this->GetExecType(token); /// -1 == unknown command type

				//get command enum 
				if (token != NULL && c.eventtype > -1) 
				{	
					token = strtok_s(NULL, " ", &end_token);
					if (token != NULL) // check again 
				    {
									 if(token[0] == ';' || token[0] == '/'){
				                             // continue;
				                             skip=1;
			                           }  
									 else{
									  c.eventenum = this->GetCommandType(token); /// -1 == unknown command

									             // if(evt && c.eventenum > 0)
                                                           //    printf("Warning! Unknown Command type in event block %d in zone:%d\n",evt->eventid,zone);
									 }
					   
					}
					else
                    {
                     //   if(evt)
                        //     printf("Warning! Missing Command type in event block %d in zone:%d\n",evt->eventid,zone);
			      		}
				}
				else
                {
				//errror unknown command type or missing command type
					// just skip for now
                    
                   //  if(evt)
                   //      printf("Warning! Unknown Command type or missing type in event block %d in zone:%d\n",evt->eventid,zone);
				}

				while (token != NULL) // get other params
				{
					//printf("b = %s\n", token);
					token = strtok_s(NULL, " ", &end_token);

					if(token != NULL)
                    {
					int p = -25555; // parameter
					sscanf(token,"%d",&p);
					//p = atoi(token);
					if( p > -25555) // sentinal:
					c.params.push_back(p); // add param
					}
				}
			// are we mid event? then add 
				if(midevent && evt)
                {
					evt->instructions.push_back(c);
				}
				else
                {// error stray logic command
                    printf("Fetal Error! Stray Logic Command in zone:%d\n",zone);
				}

			}

		 }  /// null token v

		}
		
        line = strtok_s(NULL, "\n", &end_buff);
		
		skip = 0; // reset skip
    }

//done with everything so free buffer
	free(buffer);
	*/
	free(FullPath);

}
