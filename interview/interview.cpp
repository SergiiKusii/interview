// interview.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Containers.h"

int main()
{
	std::vector<std::unique_ptr<ITestCase>> vTestCases;
	vTestCases.push_back(std::make_unique<Containers>());

	for (auto& pTestCase : vTestCases) {
		if (pTestCase) {
			pTestCase->Run();
		}
	}

	int a;
	std::cin >> a;
    return 0;
}

