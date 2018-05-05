#pragma once
class ITestCase
{
public:
	ITestCase() = default;
	virtual ~ITestCase() = default;
	virtual void Run() = 0;
};

