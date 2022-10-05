#ifndef __PACKET_DEF__
#define __PACKET_DEF__

// taken from client source
// 31/03/2021 - VKlafke

#define PKT_LOGIN				0X01
#define PKT_LOGOUT				0x02
#define PKT_ACOUNT_LOGIN        0XFE

#define PKT_MOVEFIRST			0X03
#define PKT_MOVEMIDDLE			0X04
#define PKT_MOVEEND				0X06

#define PKT_RUN_MOVEFIRST		0X15
#define PKT_RUN_MOVEMIDDLE		0X16
#define PKT_RUN_MOVEEND			0X17


#define PKT_CHAT				0X07

#define PKT_USERMODIFY			0X09

#define PKT_ZONECHANGE			0X0A
#define PKT_GAMESTART           0x0b
//#define PKT_GAMESTART           0xE9
#define PKT_RESTARTGAME         0x0c


#define PKT_ATTACK				0X10
#define PKT_ATTACK_ARROW		0X11  
#define PKT_ATTACK_MAGIC_RAIL	0X12  
#define PKT_MAGIC_READY         0X13  
#define PKT_MAGIC_CIRCLE        0x14  
#define PKT_STATUS_INFO			0X19  
#define PKT_POISON				0x20  

#define PKT_DEAD                0x23
#define PKT_DEAD_INFO           0x24
#define PKT_LIFE                0x25

#define PKT_MAGIC_ALL			0x26	
#define PKT_MAGIC_BELT			0x27	
#define PKT_SET_TIME			0x29 
#define PKT_SHOW_MAGIC			0x2a  

#define PKT_INV_ALL             0X30

#define PKT_CHANGE_ITEM_INDEX   0X32 
#define PKT_ITEM_INFO           0X33 
#define PKT_ITEM_THROW          0x34
#define PKT_ITEM_PICKUP         0x35
#define PKT_ITEM_FIELD_INFO     0x36

#define PKT_GETITEM             0x37  
#define PKT_OUTITEM             0x38 
#define PKT_MONEYCHANGE			0x39  

#define PKT_WEIGHT				0x3a	

#define PKT_ITEM_USE			0x3c	
#define PKT_ITEM_CHANGE_INFO	0x3d	
#define PKT_ITEM_DUMP			0x3e	

#define PKT_NEW_HERO            0x40
#define PKT_DEL_HERO            0x41

#define PKT_CHARTER_DATA        0x50  

#define PKT_CLIENTEVENT         0x60

#define PKT_SHOPOPEN            0x70

#define PKT_SELL_SHOP           0x72
#define PKT_BUY_SHOP            0x73

#define PKT_STORAGEOPEN			0x76
#define PKT_SAVEITEM			0x77
#define PKT_TAKEBACKITEM		0x78
#define PKT_SAVEMONEY			0x79
#define PKT_TAKEBACKMONEY		0x7a

#define PKT_MAKEROPEN			0x74	// ������ ����â ����
#define PKT_MAKEITEM			0x75	// ������ ���� �Ϸ�

#define PKT_TRADE_REQ			0x7b	// ���� �ŷ� ��û�� ���� ��
#define PKT_TRADE_ACK			0x7c	// ���� �ŷ� ��û �³�
#define PKT_TRADE_ADDITEM		0x7d	// ���� �ŷ��� ������ �߰�
#define PKT_TRADE_SETMONEY		0x7e	// ���� �ŷ��� �� ����
#define PKT_TRADE_OK			0x7f	// ���� �ŷ� Ȯ��
#define PKT_TRADE_CANCEL		0x80	// ���� �ŷ� ���
#define PKT_TRADE_RESULT		0x81	// ���� �ŷ� ����

#define PKT_AUCTION_SELL_OPEN	0x82	// ��� Sell ����
#define PKT_AUCTION_SELL_SEND	0x83	// ��� ������ ������
#define PKT_AUCTION_SELL_RCV	0x84	// ��� ������ ��������
#define PKT_AUCTION_BUY_OPEN	0x85	// ��� Buy ����
#define PKT_AUCTION_BUY_SEND	0x86	// ��� Buy �ø���

#define PKT_PUTITEM_BELT		0x87	// Inv->Belt ������ ����
#define PKT_PUTITEM_INV			0x88	// Belt->Inv ������ ����
#define PKT_CHANGEBELTINDEX		0x89

#define PKT_SELHOUSEPLACE		0x90	// ������ ���͸� ������ ����
#define PKT_HOUSEPLACE			0x91	// ���͸� ������.

#define PKT_EVENTSELBOX         0x92    // ���� �޼��� ����
#define PKT_EVENTOKBOX          0x93    // Ȯ�� �޼���.
#define PKT_EVENTNORMAL         0x94    // �Ϲ� �޼���.
#define PKT_HPMP_RECOVERY       0x96    // Hp, Mpȸ��.

#define PKT_REPAIR_OPEN			0x99	// ����â ����
#define PKT_REPAIR_REQ			0xa0	// ���� ��û

#define PKT_BATTLEMODE			0x18	// 0 : ���� 1�̸� ����..

#define PKT_GUILD_OPEN			0x97	// ��� �޴� ����
#define	PKT_GUILD_NEW			0x95	// ��� ����
#define PKT_GUILD_LIST			0x98	// ��� ����Ʈ
#define PKT_GUILD_INFO			0x9f	// ��� ���� ��û
#define PKT_GUILD_REQ			0x9a	// ��� ���� ��û
#define PKT_GUILD_MOVE_REQ		0x9b	// ���� ��û ó��
#define PKT_GUILD_REMOVE_REQ	0x9c	// ��� ���� ��û ���
#define PKT_GUILD_DISSOLVE		0x9d	// ��� ��ü
#define PKT_GUILD_REMOVE_USER	0x9e	// ��� Ż��/���� ����
#define PKT_GUILD_REQ_USER_INFO	0xa1	// ���� ����Ʈ
#define PKT_GUILD_MAN_LIST		0xa2	// ���� ���� ��û
#define PKT_GUILD_MOVE_REJECT	0xa3	// ����� ���� ��û ����
#define PKT_GUILD_APPLICATION_LIST	0xa4	// ��� ��û�� ����Ʈ
#define PKT_CHANGE_MEMBER		0xa5	// �������� ��ġ ����
#define PKT_CHANGE_GUILD_POS	0xa6	// ��� ���� ȣĪ ����
#define PKT_GIVE_DONATION		0xbd	// ��α�/��ü ���� ����
//#define PKT_CHANGE_GUILD_TAX	0xb6	// ��� ���� ����

// by krazi.
/////////////////////////////
#define BBS_OPEN				0x65
#define BBS_NEXT				0x66
#define BBS_READ				0x67
#define BBS_WRITE				0x68
#define BBS_EDIT				0x69
#define BBS_DELETE				0x6A
////////////////////////////////////////////////////

#define PKT_ENCRYPTION_START_RESULT     0xfd
#define PKT_EFFECT		0xAA


// New packet ids
/////////////////////////////////////////////
#define PKT_CHECKSERVERALIVE	0xfb
#define PKT_VERSION				0xfc
#define PKT_SPEEDHACK			0xde
#define PKT_MAGICPRECAST		0xdc // Pre-cast
#define PKT_CLASSPOINTBUY		0xe5
#define PKT_GUILD_EDIT_INFO_REQ	0xae
#define PKT_GUILD_EDIT_INFO		0xaf
#define PKT_GUILD_SYMBOL_CHANGE_REQ	0xb0
#define PKT_GUILD_SYMBOL_CHANGE	0xb1
#define PKT_GUILD_SYMBOL_DATA	0xd3
#define PKT_GUILD_STORAGEOPEN	0xb6
#define PKT_GUILD_STORAGECLOSE	0xb9
#define PKT_GUILD_SAVEITEM		0xb7
#define PKT_GUILD_TAKEBACKITEM	0xb8
#define PKT_GUILD_STORAGE_LIMIT_CHANGE	0xd0
#define PKT_GUILDWAR_REQ		0xb2
#define PKT_GUILDWAR_REQ_RESULT	0xb3
#define PKT_GUILDWAR_REQ_CANCEL	0xb4
#define PKT_GUILDWAR_OK			0xb5
#define PKT_GUILDWAR_ITEM		0xbb
#define PKT_GUILDWAR_MONEY		0xbc
#define PKT_CHANGEDIR			0xa7
#define PKT_TOWNPORTALREQ		0xa8
#define PKT_TOWNPORTALEND		0xa9
#define PKT_CHANGE_STORAGEIDX	0xab
#define PKT_UNABLE_DIRITEM		0xac
#define PKT_ATTACK_SPECIALARROW 0xbe // Special Skill, single target
#define PKT_ATTACK_SPECIALRAIL	0xbf // Special Skill, line target
#define PKT_ATTACK_SPECIALCIRCLE 0xc0 // Special Skill, Multi - target
#define PKT_ATTACK_SPECIALCIRCLE2 0xc1
#define PKT_GAME_PAUSE			0x0D
#define PKT_CONTRIBUTION		0xc5
#define PKT_PARTY_DENY			0xcc
#define PKT_PARTY_INVITE_RESULT	0xce
#define PKT_LIVEBROADCAST		0xCF
#define PKT_HAIRSHOPOK			0xd2
#define PKT_SKILL_ABILITY		0xd4
#define PKT_SPECIALMAKESKILLOTHER 0xd5
#define PKT_SPECIAL_MOVE		0xd6
#define PKT_GUILDTOWN_TAXRATE	0xd7
#define PKT_GUILDTOWN_STORE		0xd8
#define PKT_SETRUNMODE			0xda
#define PKT_TRADEREXCHANGE		0xdb // dsoma shop exchange things
#define PKT_GUILD_ALLY			0xdd
#define PKT_QUEST_VIEW			0xdf // 2nd byte 0x01 - Open 0x02 - Description
#define PKT_CHANGE_OTHER_ITEM	0xe1 // alernate gems etc i think
#define PKT_CHANGE_HAIR			0xe3
#define PKT_MONSTER_ZONE		0xe2
#define PKT_MONSTER_SELECT		0xe0
#define PKT_SETGRAY				0xad // gray name for pker etc
#define PKT_SPECIALATTACKCANCEL 0xc3
#define PKT_CONTRIBUTION_STATUS 0xc6
#define PKT_DUMMY_ATTACK		0xc7
#define PKT_GUILD_STORAGE_LOG	0xba
#define PKT_STORAGELOG_NEXT	0xc2
#define PKT_PARTY_INVITE		0xcd // Ldr UID - Mem UID - Ldr Name
#define PKT_GUILDTOWNSTONE_OPEN 0xd9
#define PKT_AUCTION_MESSAGE		0xc8
#define PKT_LOTTERY				0xc9
#define PKT_AREASTATE			0xca // No stam regain ... etc (Abias)
#define PKT_SHOP_ITEM_COUNT		0x71 // Tell client how much of an item there is and update the amount
#define PKT_RESURRECTION_SCROLL	0xD1 // Something to do with the ressurection scroll
#define PKT_PARTY_LOCATION		0xE8 // Location of party members so they can be drawn on the map
#define PKT_SACRED_STONE_TOTALS	0xEA // Location of party members so they can be drawn on the map

#define PKT_RESTED				0x08 // UNKNOWN / PRETTY SURE ITS RESTED EXP!!

#define PKT_MOBHP				0x0e // UNKNOWN / PRETTY SURE ITS MOB HP!! 
#define PKT_PENALTY				0x0f // UNKNOWN / PRETTY SURE ITS MOB HP!! 
/////////////////////////////////////////////

/*0x6f PKT_SAFETYZONE - i think :S
0x71 something to do with buying an item :S
0xc4 PKT_CONTRIBUTION_OPEN
0xc8 PKT_PARTY - some party packet hmm // Something to do with the auction (auction message)
0xc9 PKT_LOTTERY
0xca PKT_AREASTATE
0xcb PKT_ALLCHAT_STATUS
0xd1 exists but dont know what it is
0xe6 PKT_DELETE_OTHER_CLASS
-----------------------------
0x08 UNKNOWN / PRETTY SURE ITS RESTED EXP!!

0x0e UNKNOWN / PRETTY SURE ITS MOB HP!!

0xDE SPEEDHACK/ maybe rested exp??





*/

#endif