#pragma once
#include "../Components/dfComponent.h"
#include <map>
#include <typeinfo>
#include <typeindex>
#include "STDUNC.h"

//template < typename T >
extern std::map< std::type_index , dfComponent* > dfComponentMap;

void AddComponentToMap(dfComponent* dfc);

void RemoveComponentFromMap(dfComponent* dfc);