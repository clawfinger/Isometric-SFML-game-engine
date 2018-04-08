#pragma once
#include "stdafx.h"

class DiContainer;

template<typename ResultT>
ResultT* constructingFunction(const DiContainer& cont)
{
	return new ResultT();
}

template<typename FirstDependencyT, typename ResultT>
ResultT* constructingFunction(const DiContainer& cont)
{
	return new ResultT(cont.resolve<FirstDependencyT>());
}

template<typename FirstDependencyT, typename SecondDependencyT, typename ResultT>
ResultT* constructingFunction(const DiContainer& cont)
{
	return new ResultT(cont.resolve<FirstDependencyT>(), cont.resolve<SecondDependencyT>());
}

template<typename FirstDependencyT, typename SecondDependencyT, typename ThirdDependencyT, typename ResultT>
ResultT* constructingFunction(const DiContainer& cont)
{
	return new ResultT(cont.resolve<FirstDependencyT>(), cont.resolve<SecondDependencyT>(), cont.resolve<ThirdDependencyT>());
}