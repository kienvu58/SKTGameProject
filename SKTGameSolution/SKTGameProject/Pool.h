#pragma once
#include <vector>
#include <iostream>

template<class entity_type>
class Pool
{
public:
	Pool(); 
	~Pool();

	void Add(entity_type* entity);
	entity_type* GetEntity();
	void ReleaseEntity(entity_type* entity);
	void CleanUp(entity_type* entity);
private:
	std::vector<entity_type*> m_vAvailable;
	std::vector<entity_type*> m_vInUse;
};

template <class entity_type>
Pool<entity_type>::Pool()
{
}

template <class entity_type>
Pool<entity_type>::~Pool()
{
	int i;
	for (i = 0; i < m_vAvailable.size(); i++)
	{
		delete m_vAvailable[i];
	}
	m_vAvailable.clear();

	for (i = 0; i < m_vInUse.size(); i++)
	{
		delete m_vInUse[i];
	}
	m_vInUse.clear();
}

template <class entity_type>
void Pool<entity_type>::Add(entity_type* entity)
{
	if (entity != nullptr)
	{
		m_vAvailable.push_back(entity);
	}
}

template <class entity_type>
entity_type* Pool<entity_type>::GetEntity()
{
	if (m_vAvailable.size() > 0)
	{
		entity_type* entity = m_vAvailable[0];
		m_vInUse.push_back(entity);
		//m_vAvailable.erase(std::remove(m_vAvailable.begin(), m_vAvailable.end(), entity), m_vAvailable.size());
		auto it = std::find(m_vAvailable.begin(), m_vAvailable.end(), entity);
		if (it != m_vAvailable.end())
		{
			std::swap(*it, m_vAvailable.back());
			m_vAvailable.pop_back();
		}
		return entity;
	}
	else
	{
		std::cout << "Nothing in the pool yet.\n";
		return nullptr;
	}
}

template <class entity_type>
void Pool<entity_type>::ReleaseEntity(entity_type* entity)
{
	CleanUp(entity);

	m_vAvailable.push_back(entity);

	auto it = std::find(m_vInUse.begin(), m_vInUse.end(), entity);
	if (it != m_vInUse.end())
	{
		std::swap(*it, m_vInUse.back());
		m_vInUse.pop_back();
	}
}

template <class entity_type>
void Pool<entity_type>::CleanUp(entity_type* entity)
{
	//clean the entity befor add to available
}

