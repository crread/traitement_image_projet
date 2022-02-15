#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>

class Main {

	int _argc;
	char** _argv;

public:
	Main(int argc, char** argv) : _argc(argc), _argv(argv) {};
};

#endif // !_MAIN_H_