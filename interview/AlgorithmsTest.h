#pragma once
#include "ITestCase.h"
class AlgorithmsTest :
	public ITestCase
{
public:
	AlgorithmsTest() = default;
	virtual ~AlgorithmsTest() = default;
	virtual void Run() override;
};

