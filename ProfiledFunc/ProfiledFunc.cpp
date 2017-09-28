// ProfiledFunc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

using namespace std;

class Tracker
{
public:
	static int n;
	static const char** funcs;
	static int** counts;
	static void Stats()
	{
		for (int i = 0; i < n; ++i)
		{
			cout << funcs[i] << " was called " << *counts[i] << " times." << endl;
		}
	}
};

int Tracker::n = 0;
const char** Tracker::funcs = new const char*[256];
int** Tracker::counts = new int*[256];

class Register
{
public:
	Register()
	{

	}

	Register(const char* name, int* count)
	{
		Tracker::funcs[Tracker::n] = name;
		Tracker::counts[Tracker::n] = count;
		Tracker::n++;
	}
};

int main();

#ifndef PROFILED_FUNC
#define PROFILED_FUNC(foo) int foo##impl (int a, int b); \
int g_##foo##_calls = 0;\
Register g_##foo##_Reg (#foo, &g_##foo##_calls);\
int foo (int a, int b) \
{ \
g_##foo##_calls++;\
return foo##impl(a, b);\
} \
int foo##impl (int a, int b)
#endif

PROFILED_FUNC(sum)
{
	return a + b;
}

PROFILED_FUNC(mult)
{
	return a * b;
}

int main()
{
	sum(3, 5);
	sum(1, 2);
	mult(7, 8);
	mult(3, 2);
	sum(1, 1);
	Tracker::Stats();
}

