#pragma once

#include"SerializedQueue.h"

Item *getItem(char *_data, unsigned int *_size);
char* getByteArray(unsigned int *size_ptr, Item *_item);
bool isByteStringsEqual(char* R, unsigned int *size_R, char* L, unsigned int *size_L);