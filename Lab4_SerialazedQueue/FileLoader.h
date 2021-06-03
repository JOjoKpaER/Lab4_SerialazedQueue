#pragma once

#include <stdio.h>
#include <fstream>
#include <Windows.h>
#include <string>

#include"SerializedQueue.h"

class FileLoader
{
private:

	std::string PathInput;
	std::string PathOutput;

	std::ifstream *FileInput;
	std::ofstream *FileOutput;

	SerializedQueue *queue;

public:

	FileLoader(SerializedQueue *_queue, std::string _PathInput, std::string _PathOutput) {
		queue = _queue;
		PathInput = _PathInput;
		PathOutput = _PathOutput;
	}

	~FileLoader() {
		if (FileInput)
			FileInput->close();
		if (FileOutput)
			FileOutput->close();
	}

	void openFileInput() {
		FileInput = new std::ifstream(PathInput);
		if (!FileInput->is_open())
		{
			printf("Cannot open file\n");
			FileInput = nullptr;
			return;
		}
	}

	void openFileOutput() {
		FileOutput = new std::ofstream(PathOutput);
		if (!FileOutput->is_open())
		{
			printf("Cannot open file\n");
			FileOutput = nullptr;
			return;
		}
	}

	bool readFile() {
		if (!FileInput) {
			printf("Cannot open cart file");
			return false;
		}
		std::string line;
		while (std::getline(*(FileInput), line)) {
			if (line.empty()) {
				continue;
			}
			unsigned int size = line.length();
			char *data = new char[size];
			for (int i = 0; i < size; i++) {
				*(data + i) = line[i];
			}
			queue->Enqueue(data, &size);
		}
		return true;
	}

	bool wtiteFile() {
		if (!FileOutput) {
			printf("Cannot write cart file\n");
			return false;
		}
		FileOutput->clear();
		do
		{
			std::string line = "";
			unsigned int size;
			char *data = queue->Dequeue(&size);
			if (!data) continue;
			for (int i = 0; i < size; i++) {
				line += *(data + i);
			}
			line += "\n";
			(*FileOutput) << line;
			if (FileOutput->fail()) {
				printf("Error has occured while writing cart file\n");
				return false;
			}
		} while (queue->Back(new unsigned int));
		return true;
	}
};


