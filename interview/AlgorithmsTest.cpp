#include "AlgorithmsTest.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>  

class Int 
{
public:
	Int(const int _val)
		: val(_val)
	{
		std::cout << "Int(const int _val)" << std::endl;
	}

	Int(const Int& _val)
		: val(_val.val)
	{
		std::cout << "Int(const Int& _val)" << std::endl;
	}

	Int& operator=(const int _val)
	{
		val = _val;
		std::cout << "Int& operator=(const int _val)" << std::endl;
		return *this;
	}

	Int& operator=(const Int& _val)
	{
		val = _val.val;
		std::cout << "Int& operator=(const Int& _val)" << std::endl;
		return *this;
	}

	Int& operator=(const Int&& _val)
	{
		val = _val.val;
		std::cout << "Int& operator=(const Int&& _val)" << std::endl;
		return *this;
	}

	bool operator==(const Int& _val)
	{
		std::cout << "operator==(const Int& _val)" << std::endl;
		return val == _val.val;
	}


	bool operator<(const Int& _val)
	{
		std::cout << "operator<(const Int& _val)" << std::endl;
		return val < _val.val;
	}


	//friend std::ostream& operator<<(std::ostream& os, const Int& dt);

	int val = 0;
};

std::ostream& operator<<(std::ostream& os, const Int& val)
{
	os << val.val;
	return os;
}

template<typename T>
void cout_cont(const std::string& sHeader,const T& vec) {
	std::cout << sHeader << "={ ";
	
	for (auto& val : vec) {
		std::cout << val << " ";
	}
	std::cout << "}" << std::endl;
}

void AlgorithmsTest::Run()
{
	std::cout << "AlgorithmsTest::Run()" << std::endl;

	int arr[] = { 1, 2, 3, 4, 5, 5, 4, 4, 3, 3 };

	std::vector<Int> v1(arr, arr + (sizeof(arr)/sizeof(arr[0])));// = { 1, 2, 3, 4, 5, 5, 4, 4, 3, 3 };
	cout_cont("v1", v1);
	std::cout << "std::copy_if unique" << std::endl;
	std::vector<Int> v2;
	std::copy_if(v1.begin(), v1.end(), back_inserter(v2), [&v2](const Int& val) {
		return std::count(v2.begin(), v2.end(), val) == 0;
	}
	);
	cout_cont("v2", v2);
	std::cout << "std::copy" << std::endl;
	v2.clear();
	std::copy(v1.begin(), v1.end(), back_inserter(v2));
	
	std::cout << "std::sort" << std::endl;
	std::sort(v2.begin(), v2.end());
	cout_cont("v2", v2);

	std::cout << "std::unique_copy" << std::endl;
	std::vector<Int> v3;

	std::unique_copy(v2.begin(), v2.end(), back_inserter(v3));
	cout_cont("v3", v3);

	std::cout << "std::unique" << std::endl;
	auto it = std::unique(v2.begin(), v2.end());
	while (it != v2.end()) {
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
	cout_cont("v2", v2);

	std::cout << "std::remove 4" << std::endl;
	it = std::remove(v2.begin(), v2.end(), 4);
	std::cout << std::endl;
	cout_cont("v2", v2);
	std::cout << "v2.erase 4" << std::endl;
	v2.erase(it, v2.end());
	cout_cont("v2", v2);
}


