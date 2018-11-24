#pragma once
#include "DiContainer.h"

template<typename ResultT>
ResultT* constructingFunction(const DiContainer& cont)
{
	return new ResultT();
}

template<typename FirstDependencyT, typename ResultT>
ResultT* constructingFunction(const DiContainer& cont)
{
	return new ResultT(cont.get<FirstDependencyT>());
}

template<typename FirstDependencyT, typename SecondDependencyT, typename ResultT>
ResultT* constructingFunction(const DiContainer& cont)
{
	return new ResultT(cont.get<FirstDependencyT>(), cont.get<SecondDependencyT>());
}

template<typename FirstDependencyT, typename SecondDependencyT, typename ThirdDependencyT, typename ResultT>
ResultT* constructingFunction(const DiContainer& cont)
{
	return new ResultT(cont.get<FirstDependencyT>(), cont.get<SecondDependencyT>(), cont.get<ThirdDependencyT>());
}

template<typename FirstDependencyT, typename SecondDependencyT, typename ThirdDependencyT, typename ForthDependencyT, typename ResultT>
ResultT* constructingFunction(const DiContainer& cont)
{
	return new ResultT(cont.get<FirstDependencyT>(), cont.get<SecondDependencyT>(), cont.get<ThirdDependencyT>(), cont.get<ForthDependencyT>());
}