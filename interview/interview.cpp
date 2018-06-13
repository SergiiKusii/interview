// interview.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <memory>

#include "Containers.h"
#include "Inheritance.h"
#include "AprioritLinux.h"
#include "TemplateCase.h"
#include "AlgorithmsTest.h"

int main()
{
	std::vector<std::unique_ptr<ITestCase>> vTestCases;
	//vTestCases.push_back(std::make_unique<Containers>());
	//vTestCases.push_back(std::make_unique<Inheritance>());
	//vTestCases.push_back(std::make_unique<AprioritLinux>());
	//vTestCases.push_back(std::make_unique<TemplateCase>());
	vTestCases.push_back(std::make_unique<AlgorithmsTest>());

	for (auto& pTestCase : vTestCases) {
		if (pTestCase) {
			pTestCase->Run();
		}
	}

	int a;
	std::cin >> a;
    return 0;
}

