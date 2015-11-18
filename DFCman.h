#pragma once
#include "dfComponent.h"
#include <map>
#include <typeinfo>
#include <typeindex>

//template < typename T >
static std::map< std::type_index , dfComponent* > dfComponentMap;

void AddComponentToMap(dfComponent* dfc);