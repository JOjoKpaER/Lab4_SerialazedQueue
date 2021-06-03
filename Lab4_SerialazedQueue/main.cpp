#include<stdio.h>
#include<iostream>
#include<string>
#include"SerializedQueue.h"
#include"FileLoader.h"
/*
Item *getItem(char *_data, unsigned int *_size);
char* getByteArray(unsigned int *size_ptr, Item *_item);
bool isByteStringsEqual(char* R, unsigned int *size_R, char* L, unsigned int *size_L);
*/
void Menu_handler(SerializedQueue *_queue);
/*
static std::string name_array[] = { //15
	"Ball",
	"Candy",
	"Pen",
	"Flash card",
	"Book",
	"Apple",
	"Flower",
	"Laptop",
	"Bun",
	"Cell phone",
	"Magazine",
	"Cup",
	"Hare",
	"Watch",
	"Car"
};

static std::string origin_array[] = { //7
	"RUS",
	"CHN",
	"DEU",
	"USA",
	"POL",
	"KAZ",
	"GBR"
};

SerializedQueue* generateQueue() {
	SerializedQueue* queue = new SerializedQueue();
	int stackLimit = std::rand() % 1000;
	for (int i = 0; i < stackLimit; i++) {
		std::string name = name_array[std::rand() % 15];
		char *origin = new char[4];
		std::string origin_str = origin_array[std::rand() % 7];
		origin[0] = origin_str[0];
		origin[1] = origin_str[1];
		origin[2] = origin_str[2];
		origin[3] = origin_str[3];
		int count = rand() % 50 - 1 + 2;
		float price = ((float)(rand()) / (float)RAND_MAX) * 1000.0f + 0.1f;
		Item *item = new Item(count, price, origin, name);
		unsigned int size;
		char *data = getByteArray(&size, item);
		queue->Enqueue(data, &size);
	}
	return queue;
}
*/
int main(){
	SerializedQueue queue = SerializedQueue();
	FileLoader fl =  FileLoader(&queue, "Input.bin", "Output.bin");
	fl.openFileInput();
	fl.readFile();
	Menu_handler(&queue);
	fl.openFileOutput();
	fl.wtiteFile();
	return 0;
}

/*
	char origin[] = "ABC";
	std::string name = "Aboba";
	Item a = Item(4,4.0f, origin, name);
	unsigned int size;
	char* cur = getByteArray(&size, &a);
	char* byte_array = cur;
	Item *b = getItem(byte_array, &size);
	unsigned int sizeB;
	while (!isByteStringsEqual(cur, &size, getByteArray(&sizeB, b), &sizeB)) b = getItem(byte_array, &size);
	std::cout << b->count << " " << b->price << " " << b->Origin << " " << b->Name << "\n";
	SerializedQueue queue = SerializedQueue();
	queue.Enqueue(byte_array, &size);
	unsigned int sizeC;
	char *c = queue.Dequeue(&sizeC);
	Item *C = getItem(c, &sizeC);
	std::cout << C->count << " " << C->price << " " << C->Origin << " " << C->Name << "\n";
*/