#include "TemplateCase.h"
#include <iostream>

template<typename T>
class TemplTest
{
public:
	TemplTest(T& param) 
		:m_member(std::forward<T>(param))
	{
		std::cout << "TemplTest(T&& param) " << std::endl;
	}

private:
	T m_member;
};

class Base
{
public:
	Base() {
		std::cout << "Base()" << std::endl;
	}
	Base(const Base& rhs) {
		std::cout << "Base(const Base& rhs)" << std::endl;
	}
	Base(Base&& rhs) {
		std::cout << "Base(Base&& rhs)" << std::endl;
	}

	Base& operator=(const Base& rhs) {
		std::cout << "Base& operator=(const Base& rhs)" << std::endl;
		return *this;
	}
	Base& operator=(Base&& rhs) {
		std::cout << "Base& operator=(Base&& rhs)" << std::endl;
		return *this;
	}

	~Base() {
		std::cout << "~Base()" << std::endl;
	}

private:
	int m_member = 0;
};

void TemplateCase::Run()
{
	std::cout << "TemplateCase::Run()" << std::endl;
	Base base;
	TemplTest<Base> templ(base);

	TemplTest<Base> templ2(std::move(base));
	

}

