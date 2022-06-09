#pragma once
#include<cstdio>
#include<Windows.h>
#include<cstdlib>
#include<vector>

#include "Function.h"
#include "Binary.h"

using namespace std;

class Mutation
{
	int binaryLength;
	int keyPoolSize;
	char* keyPool;

public:
	double** mutationRate;
	int copyMultiple;

	Binary startBinary;
	Binary currBinary;
	Binary targetBinary;

	vector<Binary> vectorBinary;

	Mutation();
	Mutation(int _binaryLength, int _keyPoolSize, char* _keyPool);
	~Mutation();

	int getBinaryLength();
	int getKeyPoolSize();
	char getKey(int keyIndex);
	void setKeyPool(char* newKeyPool);

	void setMutationRate(double** newRate);

	void printAll();
	void printParameters();

	void setRandomBinary();
	void copyAll();
	void copy(int index);
	void selectOne(const Binary& target);


	int findKeyIndex(char key);
	char getNewKey(int keyIndex);
	int calculateHamming(const Binary& binary0, const Binary& binary1);
	int getStartHamming();
	int getCurrHamming();
};

