#include<string>
#include<stdio.h>
#include"SerializedQueue.h"

Item *getItem(char *_data, unsigned int *_size) {
	if (!_size || !_data) return nullptr;
	if (*_size < 13) return nullptr;
	unsigned int count = *reinterpret_cast<unsigned int*>(_data);
	float price = *reinterpret_cast<float*>(_data + 4);
	char *origin = new char[4];
	origin[0] = *reinterpret_cast<char*>(_data + 8);
	origin[1] = *reinterpret_cast<char*>(_data + 9);
	origin[2] = *reinterpret_cast<char*>(_data + 10);
	origin[3] = *reinterpret_cast<char*>(_data + 11);
	std::string name;
	char* cursor = _data + 12;
	while (*cursor != 0) {
		name += *cursor++;
	}
	return new Item(count, price, origin, name);
}

/*
unsigned int count;
float price;
char Origin[ORIGIN_CHAR_ARRAY_SIZE];
std::string Name;
*/
char* getByteArray(unsigned int *size_ptr, Item *_item) {
	if (!size_ptr || !_item) return nullptr;
	unsigned int size = 12 + _item->Name.size() + 1;
	*size_ptr = size;
	char *output = new char[size];
	char *cursor = reinterpret_cast<char*>(_item);
	int shift = 0;
	for (int i = 0; i < sizeof(int); i++) {
		*(output + shift++) = *cursor++;
	}
	for (int i = 0; i < sizeof(float); i++) {
		*(output + shift++) = *cursor++;
	}
	for (int i = 0; i < sizeof(char[ORIGIN_CHAR_ARRAY_SIZE]); i++) {
		*(output + shift++) = *reinterpret_cast<char*>((*_item).Origin + i);
	}
	for (cursor = &_item->Name[0]; *cursor != 0; cursor++) {
		*(output + shift++) = *cursor;
	}
	*(output + shift) = 0;
	return output;
}

bool isByteStringsEqual(char* R, unsigned int *size_R, char* L, unsigned int *size_L) {
	if (!R || !L) return false;
	if (*size_R != *size_L) return false;
	for (int i = 0; i < *size_R; i++)
	{
		if (*(R + i) != *(L + i)) {
			return false;
		}
	}
	return true;
}