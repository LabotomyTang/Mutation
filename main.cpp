#include<cstdio>
#include<Windows.h>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<cstring>
#include<cmath>

#include "Binary.h"
#include "Mutation.h"

using namespace std;

void test() {
	
}

void getFilename(Mutation& mutation, char filename[1024]) {
	int index = 0;
	strcpy_s(filename, 12, "result/BMM_");
	index += 11;

	char buffer[1024] = { 0 };
	int length = 0;
	toStr(mutation.getBinaryLength(), buffer, &length);

	strcpy_s(filename + index, length + 1, buffer);
	index += length;

	filename[index] = '_';
	++index;

	for (int i = 0; i < length; ++i) {
		buffer[i] = 0;
	}
	toStr(mutation.copyMultiple, buffer, &length);

	strcpy_s(filename + index, length + 1, buffer);
	index += length;

	filename[index] = '_';
	++index;

	for (int i = 0; i < length; ++i) {
		buffer[i] = 0;
	}
	toStr(round(mutation.mutationRate[0][0] * 100), buffer, &length);

	strcpy_s(filename + index, length + 1, buffer);
	index += length;

	filename[index] = '_';
	++index;

	for (int i = 0; i < length; ++i) {
		buffer[i] = 0;
	}
	toStr(mutation.getStartHamming(), buffer, &length);

	strcpy_s(filename + index, length + 1, buffer);
	index += length;

	strcpy_s(filename + index, 5, ".txt");
	index += 4;
}

void testMain(int _binaryLength, int _copyMultiple, double _inheritRate, int _hammingStart) {
	const int stepAmt = 1000;
	const int binaryLength = _binaryLength;
	const int copyMultiple = _copyMultiple;
	const double inheritRate = _inheritRate;
	const double mutationRate = (1 - inheritRate) / 3;
	const int hammingStart = _hammingStart;
	if (hammingStart > binaryLength) {
		error("Error: hammingStart too big.\nPosition: testMain()");
		return;
	}

	char keyPool[4] = { '0', '1', '2', '3' };
	Mutation mutation(binaryLength, 4, keyPool);
	double** rateParam = new double* [4];
	for (int i = 0; i < 4; ++i) {
		rateParam[i] = new double[4];
		for (int j = 0; j < 4; ++j) {
			if (i == j) rateParam[i][j] = inheritRate;
			else rateParam[i][j] = mutationRate;
		}
	}
	mutation.setKeyPool(keyPool);
	mutation.setMutationRate(rateParam);
	mutation.copyMultiple = copyMultiple;

	system("cls");
	printf("Current binary length: %d\n", binaryLength);

	Binary target(mutation.getBinaryLength());
	Binary start(mutation.getBinaryLength());
	for (int i = 0; i < mutation.getBinaryLength(); ++i) {
		target.value[i] = mutation.getKey(mutation.getKeyPoolSize() - 1);
		start.value[i] = mutation.getKey(mutation.getKeyPoolSize() - 1);
	}
	for (int i = 0; i < hammingStart; ++i) {
		start.value[i] = mutation.getKey(0);
	}
	mutation.startBinary = start;
	mutation.currBinary = start;
	mutation.targetBinary = target;

	char filename[1024] = { 0 };
	getFilename(mutation, filename);
	printf("%s\n", filename);

	ofstream ofs;
	ofs.open(filename);

	ofs << 0 << " " << hammingStart << "\n";

	for (int i = 0; i < stepAmt; ++i) {
		mutation.copyAll();
		mutation.selectOne(target);
		ofs << (i + 1) << " " << mutation.getCurrHamming() << "\n";
	}

	for (int i = 0; i < 4; ++i) {
		delete[] rateParam[i];
	}
	delete[] rateParam;
}

void testSpeed(int _binaryLength, int _copyMultiple, double _inheritRate, int _hammingStart) {
	const int stepAmt = 1000;
	const int binaryLength = _binaryLength;
	const int copyMultiple = _copyMultiple;
	const double inheritRate = _inheritRate;
	const double mutationRate = (1 - inheritRate) / 3;
	const int hammingStart = _hammingStart;
	if (hammingStart > binaryLength) {
		error("Error: hammingStart too big.\nPosition: testMain()");
		return;
	}

	char keyPool[4] = { '0', '1', '2', '3' };
	Mutation mutation(binaryLength, 4, keyPool);
	double** rateParam = new double* [4];
	for (int i = 0; i < 4; ++i) {
		rateParam[i] = new double[4];
		for (int j = 0; j < 4; ++j) {
			if (i == j) rateParam[i][j] = inheritRate;
			else rateParam[i][j] = mutationRate;
		}
	}
	mutation.setKeyPool(keyPool);
	mutation.setMutationRate(rateParam);
	mutation.copyMultiple = copyMultiple;

	system("cls");
	printf("Current binary length: %d\n", binaryLength);

	Binary target(mutation.getBinaryLength());
	Binary start(mutation.getBinaryLength());
	for (int i = 0; i < mutation.getBinaryLength(); ++i) {
		target.value[i] = mutation.getKey(mutation.getKeyPoolSize() - 1);
		start.value[i] = mutation.getKey(mutation.getKeyPoolSize() - 1);
	}
	for (int i = 0; i < hammingStart; ++i) {
		start.value[i] = mutation.getKey(0);
	}
	mutation.startBinary = start;
	mutation.currBinary = start;
	mutation.targetBinary = target;

	char filename[1024] = { 0 };
	getFilename(mutation, filename);
	printf("%s\n", filename);

	ofstream ofs;
	ofs.open(filename);

	ofs << 0 << " " << hammingStart << "\n";

	for (int i = 0; i < stepAmt; ++i) {
		mutation.copyAll();
		mutation.selectOne(target);
		ofs << (i + 1) << " " << mutation.getStartHamming() - mutation.getCurrHamming() << "\n";
		mutation.currBinary = mutation.startBinary;
	}

	for (int i = 0; i < 4; ++i) {
		delete[] rateParam[i];
	}
	delete[] rateParam;
}

void testlr() {
	int amt[7] = {0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 70000; ++i) {
		++amt[randlr(0, 7)];
	}
	for (int i = 0; i < 7; ++i) {
		printf("%d\n", amt[i]);
	}
}

int main() {
	srand((unsigned)time(NULL));
	//test();
	int binaryLength = 5;
	int copyMultiple = 2;
	double inheritRate = 0.25;
	for (binaryLength = 5; binaryLength <= 100; binaryLength += 5) {
		for (copyMultiple = 2; copyMultiple < 10; copyMultiple += 2) {
			for (inheritRate = 0.25; inheritRate < 0.98; inheritRate += 0.09) {
				testSpeed(binaryLength, copyMultiple, inheritRate, binaryLength);
			}
		}
	}
	//testlr();
	return 0;
}