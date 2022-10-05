#include "stdafx.h"

#include <stdio.h>
#include <string>

#include "ConfigManager.h"

ConfigManager::ConfigManager()
{
	sqlstr = new char[1024];
}

ConfigManager::~ConfigManager()
{
	delete sqlstr;
}

void ConfigManager::LoadSQLInfo()
{
	FILE* fs;
	char _line[1024];

	fopen_s(&fs, "SQL.ini", "r");

	if (fs == NULL)
	{
		MessageBox(NULL, L"Can't read \"SQL.ini\"", L"Error : fopen", MB_OK);
	}

	while (fgets(_line, 50, fs) != NULL)
	{
		char cmd[128];
		char val[128];

		int value = 0;

		if (sscanf(_line, "%[^=]=%s", cmd, &val) == 2)
		{
			if (strncmp((const char*)cmd, "[DSN]", 5) == 0)
			{
				strncpy(this->DSN, val, 128);
			}
			else if (strncmp((const char*)cmd, "[UID]", 5) == 0)
			{
				strncpy(this->UID, val, 115);
			}
			else if (strncmp((const char*)cmd, "[PWD]", 5) == 0)
			{
				strncpy(this->PWD, val, 128);
			}
		}
	}

	fclose(fs);


	sprintf(sqlstr, "ODBC;DSN=%s;UID=%s;PWD=%s", this->DSN, this->UID, this->PWD);
}