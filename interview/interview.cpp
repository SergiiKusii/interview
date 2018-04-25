// interview.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <queue>
#include <set>
#include <unordered_set>
#include <tuple>
#include <array>

class Tque
{
public:
	Tque() { std::cout << "Tque" << std::endl; }
	~Tque() { std::cout << "~Tque" << std::endl; }
	Tque(const Tque& copy) {
		m_a = copy.m_a;
		m_b = copy.m_b;
		std::cout << "Tque(const Tque& copy)" << std::endl;
	};

	Tque(const Tque&& copy) {
		m_a = copy.m_a;
		m_b = copy.m_b;
		std::cout << "Tque(const Tque&& copy)" << std::endl;
	};
	Tque& operator= (const Tque & copy) {
		m_a = copy.m_a;
		m_b = copy.m_b;
		std::cout << "operator= (const Tque & copy)" << std::endl;
		return *this;
	}

	Tque& operator= (Tque && copy) {
		m_a = copy.m_a;
		m_b = copy.m_b;
		std::cout << "operator= (Tque && copy)" << std::endl;
		return *this;
	}

	int m_a = 0;
	int m_b = 0;
};



class Tset
{
public:
	Tset() { }
	~Tset() { }

	bool operator<(const Tset &other) const {
		return std::tie(m_a, m_b) < std::tie(other.m_a, other.m_b);
	}



	int m_a = 0;
	int m_b = 0;
};

class Tunset
{
public:
	Tunset() { }
	~Tunset() { }

	bool operator==(const Tunset &other) const {
		return (m_a == other.m_a && m_b == other.m_b);
	}


//private:
	int m_a = 0;
	int m_b = 0;
};

namespace std
{
	template<>
	struct hash<Tunset>
	{
		std::size_t operator()(const Tunset& k) const
		{
			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((std::hash<int>()(k.m_a) ^ (std::hash<int>()(k.m_b) << 1)));
		}
	};

};

int main()
{
	std::queue<Tque> que;
	std::unordered_set<Tunset> un_set;
	std::set<Tset> set;

	std::array<Tque, 20> myarray;

	for (size_t i = 0; i < 20; i++) {
		Tunset top;
		top.m_a = i;
		top.m_b = i + 1;
		un_set.insert(top);

		///////////////////
		Tset tset;
		tset.m_a = i;
		tset.m_b = i + 1;
		set.insert(tset);

		////////////////
		Tque tque;
		tque.m_a = i;
		tque.m_b = i + 1;
		que.push(tque);

		/////////////

		myarray[i] = tque;

	}

	std::cout << "std::unordered_set<Toperators>" << std::endl;
	for (auto& top : un_set) {
		std::cout << "{" << top.m_a << ", " << top.m_b << "}" << std::endl;
	}
	
	std::cout << "std::set<Tset>" << std::endl;
	for (auto& top : set) {
		std::cout << "{" << top.m_a << ", " << top.m_b << "}" << std::endl;
	}

	std::cout << "std::queue<Tque>" << std::endl;
	while (que.size() > 0) {
		auto& top = que.front();
		std::cout << "{" << top.m_a << ", " << top.m_b << "}" << std::endl;
		que.pop();
	}

	std::cout << "std::array<Tque, 20>" << std::endl;
	for (auto& top : myarray) {
		std::cout << "{" << top.m_a << ", " << top.m_b << "}" << std::endl;
	}

	int a;
	std::cin >> a;
    return 0;
}

