#pragma once
#include <vector>

	struct commands
	{
	int eventenum; // command code
	int eventtype; // logical AND 0, OR 1, EXECUTE 2 etc...
	std::vector<int> params; // perameters
	};

class EventData
{
public:
	EventData(void);
	virtual ~EventData(void);
	int eventid;
    std::vector<commands> instructions;
	
	
};

