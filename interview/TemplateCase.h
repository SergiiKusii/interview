#pragma once
#include "ITestCase.h"
class TemplateCase : public ITestCase
{
public:
	TemplateCase() = default;
	virtual ~TemplateCase() = default;
	virtual void Run() override;
};

