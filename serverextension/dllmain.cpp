// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Extention.h"
#include "ServerCodeModifier.h"
#include "globals.h"

#include "Hook.h"
#include "ConfigManager.h"

ConfigManager* cfg;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		if(ext == NULL)
		{
			ext = new Extention(new ServerCodeModifier());
			ext->init();

			if (cfg == NULL)
			{
				//MessageBox(NULL, L"TESTE", L"TEST", MB_OK);
				cfg = new ConfigManager();
				cfg->LoadSQLInfo();
			}

			
			SetHooks();
			SetSQL();
			//Patch_User_LoadItemData_SetConst();
			printf("Thank you for using Soma EXT!\n Please visit our discord for support:\n");
			printf("https://discord.com/invite/spfzMPnHz7\n");
			printf("DSN: %s UID: %s PWD: %s\n", cfg->DSN, cfg->PWD, cfg->UID);
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

