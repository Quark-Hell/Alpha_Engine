#pragma once

template<typename T>
class MemoryManager {
public:
	MemoryManager();
	~MemoryManager();
	 
	static void AvoidDelete(T* value);
	static void DeletePointer(T* value);
	static void DeleteValue(T* value);
};

template<typename T>
MemoryManager<T>::MemoryManager()
{

}

template<typename T>
MemoryManager<T>::~MemoryManager()
{
}


template<typename T>
void MemoryManager<T>::AvoidDelete(T* value)
{
	T* newLight = new std::remove_pointer<decltype(value)>::type;
	(*newLight) = (*value);

	value->Delete();
}

template<typename T>
void MemoryManager<T>::DeletePointer(T* value)
{
	value->Delete();
	delete value;
}

template<typename T>
inline void MemoryManager<T>::DeleteValue(T* value)
{
	value->Delete();
}