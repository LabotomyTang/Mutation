#include "Mutation.h"

Mutation::Mutation() :
	startBinary(Binary(2)),
	currBinary(Binary(2)),
	targetBinary(Binary(2))
{
	binaryLength = 4;
	keyPoolSize = 2;
	keyPool = new char[keyPoolSize];
	keyPool[0] = '0';
	keyPool[1] = '1';
	mutationRate = new double* [keyPoolSize];
	for (int i = 0; i < keyPoolSize; ++i) {
		mutationRate[i] = new double[keyPoolSize];
		for (int j = 0; j < keyPoolSize; ++j) {
			mutationRate[i][j] = 1 / (double)(keyPoolSize);
		}
	}
	copyMultiple = 2;
	startBinary = Binary(binaryLength);
	currBinary = startBinary;
	targetBinary = startBinary;
}

Mutation::Mutation(int _binaryLength, int _keyPoolSize, char* _keyPool) :
	startBinary(Binary(2)),
	currBinary(Binary(2)),
	targetBinary(Binary(2))
{
	binaryLength = _binaryLength;
	keyPoolSize = _keyPoolSize;
	keyPool = new char[keyPoolSize];
	mutationRate = new double* [keyPoolSize];
	for (int i = 0; i < keyPoolSize; ++i) {
		keyPool[i] = _keyPool[i];
		mutationRate[i] = new double[keyPoolSize];
		for (int j = 0; j < keyPoolSize; ++j) {
			mutationRate[i][j] = 1 / (double)(keyPoolSize);
		}
	}
	copyMultiple = 2;
	startBinary = Binary(binaryLength);
	currBinary = startBinary;
	targetBinary = startBinary;
}

Mutation::~Mutation() {
	if (keyPool) {
		delete[] keyPool;
		keyPool = nullptr;
	}
	if (mutationRate) {
		for (int i = 0; i < keyPoolSize; ++i) {
			delete[] mutationRate[i];
		}
		delete[] mutationRate;
		mutationRate = nullptr;
	}
}

int Mutation::getBinaryLength() {
	return binaryLength;
}

int Mutation::getKeyPoolSize() {
	return keyPoolSize;
}

char Mutation::getKey(int keyIndex) {
	if (keyIndex > keyPoolSize) return 0;
	return keyPool[keyIndex];
}

void Mutation::setKeyPool(char* newKeyPool) {
	for (int i = 0; i < keyPoolSize; ++i) {
		keyPool[i] = newKeyPool[i];
	}
}

void Mutation::setMutationRate(double** newRate) {
	for (int i = 0; i < keyPoolSize; ++i) {
		for (int j = 0; j < keyPoolSize; ++j) {
			mutationRate[i][j] = newRate[i][j];
		}
	}
}

void Mutation::printAll() {
	printf("\n");
	for (int i = 0; i < vectorBinary.size(); ++i) {
		vectorBinary[i].print();
	}
	printf("\n");
}

void Mutation::printParameters() {
	printf("\nBinary length: %d\n\n", binaryLength);
	printf("Key pool size: %d\n\nKey pool: \n", keyPoolSize);
	for (int i = 0; i < keyPoolSize; ++i) {
		printf("%4c", keyPool[i]);
	}
	printf("\n\nMutation rate(left to top): \n        ");
	for (int i = 0; i < keyPoolSize; ++i) {
		printf("%4c    ", keyPool[i]);
	}
	printf("\n\n");
	for (int i = 0; i < keyPoolSize; ++i) {
		printf("%4c    ", keyPool[i]);
		for (int j = 0; j < keyPoolSize; ++j) {
			printf("%.2f    ", mutationRate[i][j]);
		}
		printf("\n\n");
	}
	printf("Copy multiple: %d\n\n", copyMultiple);
	printf("Start hamming distance: %d\n\n", calculateHamming(startBinary, targetBinary));
}

void Mutation::setRandomBinary() {
	Binary tempBinary(binaryLength);
	for (int i = 0; i < binaryLength; ++i) {
		tempBinary.value[i] = keyPool[randlr(0, keyPoolSize)];
	}
	currBinary = tempBinary;
}

void Mutation::copyAll() {
	vectorBinary.clear();
	vectorBinary.emplace_back(currBinary);
	if (!vectorBinary.size()) {
		error("Error: vectorBinary is empty.\nPosition: Mutation::copy()");
		return;
	}
	int oldSize = vectorBinary.size();
	for (int i = 0; i < oldSize; ++i) {
		copy(0);
	}
}

void Mutation::copy(int index) {
	Binary oldBinary(vectorBinary[index]);
	vector<Binary>::iterator it = vectorBinary.begin();
	for (int i = 0; i < index; ++i) {
		++it;
	}
	vectorBinary.erase(it);
	Binary tempNewBinary(binaryLength);
	int keyIndex = 0;
	int i(0), j(0);
	for (i = 0; i < copyMultiple; ++i) {
		tempNewBinary = oldBinary;
		for (j = 0; j < binaryLength; ++j) {
			keyIndex = findKeyIndex(tempNewBinary.value[j]);
			tempNewBinary.value[j] = getNewKey(keyIndex);
		}
		vectorBinary.emplace_back(tempNewBinary);
	}
}

void Mutation::selectOne(const Binary& target) {
	if (!vectorBinary.size()) {
		error("Error: vector binary is empty.\nPosition: Mutation::selectOne()");
		return;
	}
	Binary bestBinary(vectorBinary[0]);
	int leastDistance = calculateHamming(bestBinary, target);
	int tempDistance = 0;
	vectorBinary.erase(vectorBinary.begin());
	while (vectorBinary.size()) {
		tempDistance = calculateHamming(vectorBinary[0], target);
		if (tempDistance < leastDistance) {
			bestBinary = vectorBinary[0];
			leastDistance = tempDistance;
		}
		vectorBinary.erase(vectorBinary.begin());
	}
	currBinary = bestBinary;
}

int Mutation::findKeyIndex(char key) {
	for (int i = 0; i < keyPoolSize; ++i) {
		if (key == keyPool[i]) return i;
	}
	error("Error: Key don't exist.\nPosition: Mutation::findKeyIndex()");
	return -1;
}

char Mutation::getNewKey(int keyIndex) {
	double rate = rand01();
	double rateSum = 0;
	int newKeyIndex = 0;
	while (rate >= rateSum && newKeyIndex != keyPoolSize) {
		rateSum += mutationRate[keyIndex][newKeyIndex];
		++newKeyIndex;
	}
	return keyPool[newKeyIndex - 1];
}

int Mutation::calculateHamming(const Binary& binary0, const Binary& binary1) {
	if (binary0.length != binary1.length) {
		error("Error: length mismatch.\nPosition: Mutation::calculateHamming()");
		return -1;
	}
	int hammingDistance = 0;
	for (int i = 0; i < binary0.length; ++i) {
		if (binary0.value[i] != binary1.value[i]) {
			++hammingDistance;
		}
	}
	return hammingDistance;
}

int Mutation::getStartHamming() {
	return calculateHamming(startBinary, targetBinary);
}

int Mutation::getCurrHamming() {
	return calculateHamming(currBinary, targetBinary);
}