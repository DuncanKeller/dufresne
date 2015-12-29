#include "DFCman.h"

void AddComponentToMap(dfComponent* dfc)
{
	std::type_index infer = typeid(*dfc);
	dfComponent* comp = dfComponentMap[typeid(*dfc)];

	if(comp)
	{
		dfComponent* prev = 0;
		while(comp != 0)
		{
			prev = comp;
			comp = comp->nextInList;
		}
		prev->nextInList = dfc;
		dfc->nextInList = 0;
	}
	else
	{
		dfComponentMap[typeid(*dfc)] = dfc;
		dfc->nextInList = 0;
	}
}


void RemoveComponentFromMap(dfComponent* dfc)
{
	dfComponent* current = dfComponentMap[typeid(*dfc)];
	dfComponent* prev = 0;

	if(!current)
		return;

	while(current != dfc)
	{
		prev = current;
		current = current->nextInList;

		if(!current)
		{
			dfLog("Component does not exist in DFC map");
			return;
		}
	}

	if(current == dfComponentMap[typeid(*dfc)])
	{
		if(current->nextInList != 0)
			dfComponentMap[typeid(*dfc)] = current->nextInList;
		else
			dfComponentMap[typeid(*dfc)] = 0;
	}
	else
	{
		if(current->nextInList != 0)
			prev->nextInList = current->nextInList;
		else
			prev->nextInList = 0;
		
	}

	
}