#pragma once
#include<cstdio>
#include<Windows.h>
#include<cstdlib>

using namespace std;

class Binary
{
public:
	int length;
	char* value;
	
	Binary(int _length);

	Binary(const Binary& _binary);

	Binary& operator=(const Binary& _binary);

	~Binary();

	void print();
};

