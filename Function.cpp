#include "Function.h"

int randlr(int l, int r) {
	int size = r - l;
	if (size > 32768) {
		error("Error: size exceeds.\nPosition : randlr()");
	}
	int randSize = 32768 / size * size;
	int member = rand();
	while (member >= size) {
		member = rand();
	}
	return member % size;
}

double rand01() {
	int member = (rand() << 15) + rand();
	return (double)member / 32768.0 / 32768.0;
}

void error(const char* msg) {
	printf("\n%s\n", msg);
	system("pause");
}

void toStr(int _num, char* strPtr, int* _length) {
	stack<char> reverse;
	bool fu = (_num < 0) ? true : false;
	int abs = fu ? -_num : _num;
	int temp = abs;
	while (temp) {
		reverse.push('0' + temp % 10);
		temp /= 10;
	}
	if (!abs) {
		reverse.push('0');
	}
	if (fu) {
		reverse.push('-');
	}
	int length = reverse.size();
	for (int i = 0; i < length; ++i) {
		strPtr[i] = reverse.top();
		reverse.pop();
	}
	if (_length) {
		*_length = length;
	}
}