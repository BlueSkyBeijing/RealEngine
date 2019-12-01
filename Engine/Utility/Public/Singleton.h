#pragma once

template <typename T> class Singleton
{
public:
	Singleton()
	{
	};
	~Singleton()
	{
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
