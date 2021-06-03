#include <Windows.h>
#include <iostream>

#include "Serializetion_methods.h"

#define delay 250

static SerializedQueue *queue;

void Add(Item *item);
void Remove(Item *item);
void Clear();

static enum Function {
	ADD,
	REMOVE,
	CLEAR,
	END,
	NONE
};

void Menu_handler(SerializedQueue *_queue) {
	queue = _queue;
	
	std::string Actions[] = { //4
		"Add",
		"Remove",
		"Clear",
		"Close"
	};
	std::string SelectionMessage = "Select next action:\n";
	for (int i = 0; i < 4; i++) {
		SelectionMessage += "		" + Actions[i];
	}
	SelectionMessage += "\n";
	std::string SelectedAction;
	////////////////////////////////////////////////////////////////////////////////////////
	bool cls = true;
	while (cls) {
		std::cout << SelectionMessage;
		bool bb = true;
		do {
			std::getline(std::cin, SelectedAction);
			if (SelectedAction != "")
				bb = false;
		} while (bb);
		Function func = NONE;
		for (int i = 0; i < 4; i++) {
			if (SelectedAction == Actions[i]) {
				func = Function(i);
				break;
			}
		}
		switch (func) {
		case(ADD): {
			unsigned int count;
			float price;
			bool b = true;
			do {
				std::cout << "\nQuantity: ";
				std::cin >> count;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::printf("Incorrect value\n");
					Sleep(delay);
					b = true;
				}
				else {
					b = false;
					std::cin.ignore(32767, '\n');
				}
			} while (b);
			b = true;
			do {
				std::cout << "Price: ";
				std::cin >> price;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::printf("Incorrect value\n");
					Sleep(delay);
					b = true;
				}
				else {
					b = false;
					std::cin.ignore(32767, '\n');
				}
				if (price <= 0.0f)
				{
					std::cin.clear();
					std::printf("Incorrect value\n");
					Sleep(delay);
					b = true;
				}
			} while (b);
			char Origin[ORIGIN_CHAR_ARRAY_SIZE];
			b = true;
			do {
				std::cout << "Origin: ";
				std::cin >> Origin;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::printf("Unacceptable string\n");
					Sleep(delay);
					b = true;
				}
				else {
					b = false;
					std::cin.ignore(32767, '\n');
				}
			} while (b);
			std::string Name;
			std::cout << "Name: ";
			std::cin >> Name;
			Add(new Item(count, price, Origin, Name));
			break;
		}
		case(REMOVE): {
			unsigned int count;
			float price;
			bool b = true;
			do {
				std::cout << "\nQuantity: ";
				std::cin >> count;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::printf("Incorrect value\n");
					Sleep(delay);
					b = true;
				}
				else {
					b = false;
					std::cin.ignore(32767, '\n');
				}
			} while (b);
			b = true;
			do {
				std::cout << "Price: ";
				std::cin >> price;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::printf("Incorrect value\n");
					Sleep(delay);
					b = true;
				}
				else {
					b = false;
					std::cin.ignore(32767, '\n');
				}
				if (price <= 0.0f)
				{
					std::cin.clear();
					std::printf("Incorrect value\n");
					Sleep(delay);
					b = true;
				}
			} while (b);
			char Origin[ORIGIN_CHAR_ARRAY_SIZE];
			b = true;
			do {
				std::cout << "Origin: ";
				std::cin >> Origin;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::printf("Unacceptable string\n");
					Sleep(delay);
					b = true;
				}
				else {
					b = false;
					std::cin.ignore(32767, '\n');
				}
			} while (b);
			std::string Name;
			std::cout << "Name: ";
			std::cin >> Name;
			Remove(new Item(count, price, Origin, Name));
			break;
		}
		case(CLEAR): {
			Clear();
			break;
		}
		case(END): {
			cls = false;
			printf("Storage program is closing now\n");
			Sleep(delay);
			break;
		}
		default: {
			printf("Cannot procceed inputed function\n");
			Sleep(delay);
		}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////

}

std::string GetItemDescription(Item *item) {
	std::string ret = "";
	if (item)
		ret += item->Name + " " + item->Origin + " x" + std::to_string(item->count) + " " + std::to_string(item->price);
	return ret;
}

void Add(Item *item) {
	if (!item) return;
	unsigned int size;
	char* byte_str = getByteArray(&size, item);
	queue->Enqueue(byte_str, &size);
	std::cout << GetItemDescription(item) << " was added to queue\n";
}

void Remove(Item *item) {
	if (!item) return;
	bool b = false;
	SerializedQueue *t_queue = new SerializedQueue();
	unsigned int t_size;
	unsigned int sizeR;
	char* dataR = getByteArray(&sizeR, item);
	while (queue->Back(&t_size)) {
		unsigned int sizeL;
		char* dataL = queue->Dequeue(&sizeL);
		if (isByteStringsEqual(dataR, &sizeR, dataL, &sizeL)) {
			b = true;
			continue;
		}
		t_queue->Enqueue(dataL, &sizeL);
	}
	while (t_queue->Back(&t_size)) {
		unsigned int size;
		char *data = t_queue->Dequeue(&size);
		queue->Enqueue(data, &size);
	}
	delete t_queue;
	t_queue = nullptr;
	if (b)
		std::cout << GetItemDescription(item) << " was removed from queue\n";
	else
		std::cout << "Cannot find " << GetItemDescription(item) << " in queue\n";
	Sleep(delay);
}

void Clear() {
	unsigned int t_size;
	while (queue->Back(&t_size)) {
		unsigned int size;
		char* data = queue->Dequeue(&size);
		Item *item = getItem(data, &size);
		if (!item) continue;
		std::cout << GetItemDescription(item) << " was removed from queue\n";
		Sleep(delay / 10);
	}
	printf("Queue was cleared\n");
	Sleep(delay);
}