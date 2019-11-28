#pragma once

template <typename T> class Singleton
{
public:
	Singleton()
	{
		Instance = static_cast<T*>(this);
	};
	~Singleton()
	{
		Instance = nullptr;
	};
	static T* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new T();
		}

		return Instance;
	}

protected:
	static T* Instance;
};
