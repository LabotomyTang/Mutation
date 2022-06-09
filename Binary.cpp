#include "Binary.h"

Binary::Binary(int _length) :
	length(_length)
{
	value = new char[length];
	for (int i = 0; i < length; ++i) {
		value[i] = '0';
	}
}

Binary::Binary(const Binary& _binary) :
	length(_binary.length)
{
	value = new char[length];
	for (int i = 0; i < length; ++i) {
		value[i] = _binary.value[i];
	}
}

Binary& Binary::operator=(const Binary& _binary) {
	if (value) {
		delete[] value;
		value = nullptr;
	}
	length = _binary.length;
	value = new char[length];
	for (int i = 0; i < length; ++i) {
		value[i] = _binary.value[i];
	}
	return *this;
}

Binary::~Binary() {
	if (value) {
		delete[] value;
		value = nullptr;
	}
}

void Binary::print() {
	for (int i = 0; i < length; ++i) {
		printf("%c", value[i]);
	}
	printf("\n");
}