#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include <string>
#include <vector>

#include "FileReader.h"
#include "ImageManager.h"

class Main {

	int _argc;
	char** _argv;
	FileReader fileReader;
	ImageManager imageManager;

public:

	// constructor
	Main(int argc, char** argv) : _argc(argc), _argv(argv) 
	{
		fileReader = FileReader();
		imageManager = ImageManager();
	}

	// deconstructor
	~Main() {};

	void start();
};

#endif // !_MAIN_H_