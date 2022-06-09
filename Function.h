#pragma once
#include<cstdio>
#include<Windows.h>
#include<cstdlib>
#include<stack>

using namespace std;

int randlr(int l, int r);

double rand01();

void error(const char* msg);

void toStr(int _num, char* strPtr, int* _length);