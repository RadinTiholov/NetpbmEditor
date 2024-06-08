#pragma once
#include <iostream>

class SingletonClass {
private:
	SingletonClass() {
		std::cout << "SingletonClass was created" << std::endl;
	}

	~SingletonClass() {
		std::cout << "SingletonClass was destroyed" << std::endl;
	}
public:
	static SingletonClass& getInstance() {
		static SingletonClass instance;
		return instance;
	}

	SingletonClass(const SingletonClass& other) = delete;
	SingletonClass& operator=(const SingletonClass& other) = delete;

	void doStuff() {
		std::cout << this << std::endl;
	}
};
