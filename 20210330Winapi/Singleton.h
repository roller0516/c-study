//Singleton.h
// 
#pragma once
template <typename T>
class Singleton 
{
protected:
	static T* instance;// 데이터 영역 메모리 할당 -> 프로그램이 종료될때까지 

	Singleton() {};
	~Singleton() {};
public:
	static T* Getsingleton();
	void ReleaseSingleton();
};

//영역 밖에서 초기화 -> static 멤버 변수 사용전에 해야 하는 문법
template <typename T>
T* Singleton<T> ::instance = nullptr;

template<typename T>
inline T* Singleton<T>::Getsingleton()
{
	if (instance == nullptr) 
	{
		instance = new T;
	}
	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()
{
	if (instance) 
	{
		delete instance;
		instance = nullptr;
	}
}
