#pragma once
#include "ITestCase.h"
class CryptoppTest :
	public ITestCase
{
public:
	CryptoppTest() = default;
	virtual ~CryptoppTest() = default;
	virtual void Run() override;
};

