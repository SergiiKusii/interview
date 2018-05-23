#include "Inheritance.h"
#include <iostream>
#include <memory>

class Base
{
public:
	Base() {
		std::cout << "Base::Base()" << std::endl;
	};
	virtual ~Base() {
		std::cout << "Base::~Base()" << std::endl;
	};
	virtual void run() {
		std::cout << "Base::run()" << std::endl;
	};
};

class Deriv1 : public Base
{
public:
	Deriv1() {};
	~Deriv1() {};

private: 
	virtual void run() override
	{
		std::cout << "Deriv1::run()" << std::endl;
	}
};

class Deriv2 : Base
{
public:
	Deriv2() {};
	~Deriv2() {};
};


void Inheritance::Run()
{
	std::cout << "START Inheritance::Run()" << std::endl;

	std::cout << "END Inheritance::Run()" << std::endl;
}