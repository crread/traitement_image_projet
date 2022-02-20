#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include <string>
#include <vector>

#include <sys/stat.h>

#include "FileReader.hpp"
#include "ImageManager.hpp"

class Main {

	int _argc;
	bool saveData;
	char** _argv;
	FileReader fileReader;
	ImageManager imageManager;

public:

	// constructor
	Main(int argc, char** argv) : _argc(argc), _argv(argv) 
	{
		saveData = false;
	}

	// deconstructor
	~Main() {};

	void start();
};

#endif // !_MAIN_H_