#include "DFCman.h"

//std::map< std::type_index , dfComponent* > dfComponentMap;


void AddComponentToMap(dfComponent* dfc)
{
	dfComponent* comp = dfComponentMap[typeid(dfc)];

	if(comp)
	{
		dfComponent* prev = 0;
		while(comp == 0)
		{
			prev = comp;
			comp = comp->nextInList;
		}
		prev->nextInList = dfc;
		dfc->nextInList = 0;
	}
	else
	{
		dfComponentMap[typeid(dfc)] = dfc;
		dfc->nextInList = 0;
	}
}