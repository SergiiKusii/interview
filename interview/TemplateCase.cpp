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

template<typename T1, typename T2>
class Spec
{
public:
	Spec() = default;
	~Spec() = default;
	T1 get1() {
		return m_1;
	}

	T1 m_1;
	T2 m_2;
private:

};

template<typename T2>
class Spec<int, T2>
{
public:
	Spec() = default;
	~Spec() = default;
	T2 get2() {
		return m_2;
	}

	int m_1;
	T2 m_2;
private:

};

template<typename T1, typename T2>
T1 doSomething(T2)
{
	std::cout << "T1 doSomething(T2)" << std::endl;
	T1 num = 1;
	return num;
}

template<typename T2>
double doSomething(T2)
{
	std::cout << "double doSomething(T2)" << std::endl;
	double num = 1;
	return num;
}

void TemplateCase::Run()
{
	std::cout << "TemplateCase::Run()" << std::endl;
	Base base;
	TemplTest<Base> templ(base);

	TemplTest<Base> templ2(std::move(base));
	
	Spec<double, float> spec1;
	spec1.get1();

	Spec<int, float> spec2;
	spec2.get2();

	spec2.m_1 = doSomething<int, float>(spec2.m_2);

	spec1.m_1 = doSomething(spec1.m_2);
}

