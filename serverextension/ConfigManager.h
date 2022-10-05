#pragma once

class ConfigManager
{

public:

	char DSN[128];
	char UID[128];
	char PWD[128];

	char* sqlstr;

	ConfigManager();
	~ConfigManager();

	void LoadSQLInfo();



};