#pragma once
#include "ITestCase.h"

class AprioritLinux : public ITestCase
{
public:
	AprioritLinux() = default;
	virtual ~AprioritLinux() = default;

	virtual void Run() override;
};

