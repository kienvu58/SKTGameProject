#pragma once
#include <map>
#include <vector>

template <class T>
T* GetResourceById(int id, const std::map<int, T*>& m)
{
	auto it = m.find(id);
	if (it == m.end())
	{
		return nullptr;
	}
	return it->second;
};

template <class T>
void ClearMap(std::map<int, T*>& m)
{
	for (auto it : m)
	{
		delete it.second;
	}
	m.clear();
}

template <class T1, class T2>
void ClearMap(std::map<T1, T2*>& m)
{
	for (auto it : m)
	{
		delete it.second;
	}
	m.clear();
}

template <class T, class T2>
T2* GetResourceById(T id, const std::map<T, T2*>& m)
{
	auto it = m.find(id);
	if (it == m.end())
	{
		return nullptr;
	}
	return it->second;
};

template <class T>
void RemoveFromVector(std::vector<T>& vecTor, T entity)
{
	auto it = std::find(vecTor.begin(), vecTor.end(), entity);
	if (it != vecTor.end())
	{
		std::swap(*it, vecTor.back());
		vecTor.pop_back();
	}
}
