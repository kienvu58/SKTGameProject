#pragma once

template <class T>
class Singleton
{
public:
	static T* GetInstance();
	static void CreateInstance();
	static void DestroyInstance();
private:
	Singleton();
	~Singleton();
	Singleton(Singleton const&);           
	Singleton& operator=(Singleton const&);

	static T* s_pInstance;
};

template <class T> 
T* Singleton<T>::s_pInstance = nullptr;

template <class T>
T* Singleton<T>::GetInstance() 
{
	return s_pInstance;
}


template <class T>
void Singleton<T>::CreateInstance()
{
	if (!s_pInstance)
	{
		s_pInstance = new T;
	}
}


template <class T>
void Singleton<T>::DestroyInstance()
{
	if (s_pInstance)
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}
}