#pragma once
#include "ITestCase.h"
class Inheritance :
	public ITestCase
{
public:
	Inheritance() = default;
	virtual ~Inheritance() = default;
	virtual void Run() override;
};

