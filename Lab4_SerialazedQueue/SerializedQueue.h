#pragma once

#include<string>
#include<stdio.h>

#define ORIGIN_CHAR_ARRAY_SIZE 4

struct Item {
	unsigned int count;
	float price;
	char *Origin = new char[ORIGIN_CHAR_ARRAY_SIZE];
	std::string Name;
	
	Item(unsigned int _count, float _price, char *_Origin, std::string _Name) {
		count = _count;
		price = _price;
		Origin = _Origin;
		Name = _Name;
	}

	bool operator==(const Item &r) {
		return this->Name == r.Name &&
			this->Origin[0] == r.Origin[0] &&
			this->Origin[1] == r.Origin[1] &&
			this->Origin[2] == r.Origin[2] &&
			this->count == r.count &&
			this->price == r.price;
	}

	bool operator!=(const Item&r) {
		return !(*this == r);
	}
};

class SerializedQueue
{
private:

	struct element
	{
		char *data;
		unsigned int size;
		element *prev;

		element() {
			data = nullptr;
			size = NULL;
			prev = nullptr;
		}

		element(char *_data, unsigned int *_size, element *_prev) {
			if (_size) {
				data = _data;
				size = *_size;
				prev = _prev;
			}
			else {
				data = nullptr;
				size = NULL;
				prev = _prev;
			}
		}

		element(element *copyFrom) {
			data = copyFrom->data;
			size = copyFrom->size;
			prev = copyFrom->prev;
		}

	};

	element *back, *front;

public:

	SerializedQueue() {
		element *t = new element();
		back = t;
		front = t;
	}

	~SerializedQueue() {
		while (front->prev != nullptr) {
			element *t = front->prev;
			delete front;
			front = t;
		}
		delete front;
		front = nullptr;
	}

	void Enqueue(char *_data, unsigned int *_size) {
		element *t = new element(_data,_size,nullptr);
		back->prev = t;
		back = t;
	}

	char* Dequeue(unsigned int *_size) {
		if (!front->prev) {
			return nullptr;
		}
		element *t = front->prev;
		char *data_ptr = t->data;
		*_size = t->size;
		delete front;
		front = t;
		return data_ptr;
	}

	char* Back(unsigned int *_size) {
		if (!front->prev) {
			return nullptr;
		}
		*_size = back->size;
		return back->data;
	}

	char* Front(unsigned int *_size) {
		if (!front->prev) {
			return nullptr;
		}
		*_size = back->size;
		return front->data;
	}

	
};

