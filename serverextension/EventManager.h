#pragma once

#include <map>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dirent.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//#include <linestream>
using namespace std;
//#include <direct.h>

#include "EventData.h"

// E command ENUMs
#define LINK   1
#define SAY   2
#define STORE_OPEN  3
#define GIVE_ITEM   4
#define ROB_ITEM   5
#define GIVE_MAGIC   6
#define ROB_MAGIC   7
#define BBS_OPEN   8
#define DISAPPEAR   9
#define RUN_MAGIC   10
#define DEAD   11
#define CHANGE_LEVEL   12
#define CHANGE_GENDER   13
#define CHANGE_HP   14
#define CHANGE_MP   15
#define CHANGE_STR   16
#define CHANGE_DEX   17
#define CHANGE_INT   18
#define CHANGE_WIS   19
#define CHANGE_CHA   20
#define CHANGE_CON   21
#define CHANGE_DMAGIC   22
#define CHANGE_WMAGIC   23
#define CHANGE_BMAGIC   24
#define CHANGE_SWORD   25
#define CHANGE_SPEAR   26
#define CHANGE_AXE   27
#define CHANGE_BOW   28
#define CHANGE_KNUCKLE   29
#define CHANGE_WEAPONMAKE   30
#define CHANGE_ARMORMAKE   31
#define CHANGE_ACCMAKE   32
#define CHANGE_POTIONMAKE   33
#define CHANGE_COOKING   34
#define SHOW_MAGIC   35
#define MAKER_OPEN   36
#define STORAGE_OPEN   37
#define AUCTION_SELL_OPEN   38
#define AUCTION_BUY_OPEN   39
#define SELECT_MSG   40
#define MESSAGE_OK   41
#define MESSAGE_NONE   42
#define GIVE_GOLD   43
#define ROB_GOLD   44
#define RUN_EVENT   45
#define ADD_EVENT   46
#define DEL_EVENT   47
#define RAND_SAY   48
#define RETURN   49
#define CHANGE_MAGETYPE   50
#define GUILD_OPEN  51
#define REPAIR_ITEM_OPEN  52
#define GIVE_SPECIAL_ATTACK   53
#define KILL_NPC 54
#define PLUS_MORAL   55
#define OPEN_CONTRIBUTION   56
#define CHANGE_STORAGE_TYPE   57

#define WARP_GATE   64
#define AUCTION_DRAW_NOBID   65
#define AUCTION_DRAW_NOBUY   66
#define AUCTION_BUY_ITEM   67
#define AUCTION_GET_MONEY   68
#define AUCTION_DELETE_BADLIST   69
#define CHANGE_MAX_HP   70
#define CHANGE_MAX_MP   71
#define CHANGE_MAX_STM   72
#define CHANGE_MAX_WGT   73

#define OPEN_HAIRSHOP   80
#define LIVE_NPC   81
#define ADD_SERVER_EVENT   82
#define DEL_SERVER_EVENT   83
#define GIVE_MAKE_SKILL   84
#define OPEN_SPECIAL_MAKESKILL   85
#define OPEN_GUILDTOWN_STONE  86
#define GUILDTOWN_TAXRATE   87
#define OPEN_GUILDTOWN_STORE_REG   88
#define OPEN_GUILDTOWN_STORE   89

#define MAGIC   96
#define SPECIAL_ATTACK   97
#define OPEN_TRADER   98
#define OPEN_CHANGE_ITEM   99
#define COUNTER_START   100
#define COUNTER_INIT   101
#define OPEN_MONSTER_SELECT  102
#define TIMER_START  103
#define TIMER_INIT  104
#define SET_EVENTCOUNT   105

#define RESET_EVENTCOUNT 112
#define CLASSPOINT_STORE_OPEN   113
#define OPEN_MONSTER_ZONE 114
#define XMASPOINT_USER 115
#define XMASPOINT_GUILD 116
#define CHANGE_PKMODE   117
#define GET_POSITEM   118
#define SHOW_DIR      119
#define RAIN          120

// A/O Command ENUMs
#define EVT_LEVEL 1
#define EVT_GENDER 2
#define EVT_AGE  3 /// guess
#define EVT_HP  4 /// guess
#define EVT_MP  5  /// guess
#define EVT_STR  6 /// guess
#define EVT_DEX  7 /// guess
#define EVT_INT  8 /// guess
#define EVT_WIS  9 /// guess
#define EVT_CHA 10  /// guess
#define EVT_CON 11 /// guess
#define EVT_DMAGIC   12
#define EVT_WMAGIC  13
#define EVT_BMAGIC   14
#define EVT_SWORD    15
#define EVT_SPEAR     16
#define EVT_AXE 17  /// guess
#define EVT_BOW 18
#define EVT_KNUCKLE  19
#define EVT_STAFF 82
#define EVT_WEAPONMAKE 20
#define EVT_ARMORMAKE 21
#define EVT_ACCMAKE 22
#define EVT_POTIONMAKE 23
#define EVT_COOKING 24
#define EVT_EXIST_ITEM 25
#define EVT_ABSENT_ITEM 26
#define EVT_EXIST_ITEM_TYPE 27
#define EVT_ABSENT_ITEM_TYPE 28
#define EVT_EXIST_MAGIC 29
#define EVT_ABSENT_MAGIC 30
#define EVT_EXIST_MAGETYPE 64
#define EVT_ABSENT_MAGETYPE 65
#define EVT_EXIST_SPECIAL_ATTACK 56
#define EVT_ABSENT_SPECIAL_ATTACK 57
#define EVT_EXIST_MAKE_SKILL 67
#define EVT_ABSENT_MAKE_SKILL 68
#define EVT_EXIST_EVENT 31
#define EVT_ABSENT_EVENT 32
#define EVT_TIME 33
#define EVT_RAND 34
#define EVT_GOLD 35
#define EVT_GAME_TIME 36
#define EVT_GAME_DAY 37
#define EVT_GAME_MONTH 38
#define EVT_HOWMUCH_ITEM 39
#define EVT_MORAL  40
#define EVT_STORAGE_TYPE 53
#define EVT_MAGETYPE 41
#define EVT_WEIGHT 48
#define EVT_RANK 49
#define EVT_CHECK_ITEMSLOT  50
#define EVT_CHECK_POSITION 51
#define EVT_CHECK_FIRST_CLICK  52
#define EVT_CHECK_AUCTION_BADLIST  54
#define EVT_CHECK_AUCTION_STATE 55
#define EVT_CHECK_ALIVE_NPC 66
#define EVT_CHECK_GUILD_TOWN 69
#define EVT_CHECK_GUILD_TOWN_ALLY 73
#define EVT_CHECK_GUILD_TOWN_WAR 80
#define EVT_CHECK_GUILD_TOWN_LEVEL 81
#define EVT_CHECK_GUILD_RANK 70
#define EVT_COMPARE_BASIC_VALUE 71
#define EVT_CHECK_JOB 72
#define EVT_CHECK_HUMAN 83
#define EVT_CHECK_DEMON 84
#define EVT_CHECK_MONSTER 85
#define EVT_CHECK_COUNTER  86
#define EVT_CHECK_TIMER 87
#define EVT_CHECK_EVENTCOUNT  88
#define EVT_CHECK_PAYTYPE 89
#define EVT_CHECK_CLASS_TOWN  96
#define EVT_CHECK_CLASS_TOWN_WAR 97
#define EVT_CHECK_HAVE_EVENTBOOK 98
#define EVT_CHECK_EVENTBOOK 99
#define EVT_CHECK_PKMODE  100
#define EVT_CHECK_PAYACCOUNT 101
#define EVT_PAYACCOUNT 102


class EventManager
{
public:
	
	EventManager(void);
	virtual ~EventManager(void);

	void LoadEvents(void);
	EventData* GetEventData(int,int);

	
protected:
	std::map<std::pair<int,int>,EventData*> EventMap;  //zone , event -> eventdata
	void ParseFile(char* FileName,int zone); 
	int GetExecType(const char* ch);
	int GetCommandType(const char* ch);
};

