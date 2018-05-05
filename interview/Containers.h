#pragma once

#include "ITestCase.h"

class Containers : public ITestCase
{
public:
	Containers() = default;
	~Containers() = default;

	virtual void Run() override;
};

