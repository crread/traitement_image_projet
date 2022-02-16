#include "Main.h"

void Main::start()
{
	if (_argc <= 1)
	{
		std::cout << "no path given..." << std::endl;
		return;
	}

	std::string path(_argv[1]);

	if (fileReader.isDirectory(path))
	{
		auto listpaths = fileReader.getImagesPathList(path);

		if (listpaths.size() <= 0)
		{
			std::cout << "no image in the given directory..." << std::endl;
			return;
		}

		imageManager.setImages(listpaths);
	}
	else
	{
		std::cout << "is not a directory" << std::endl;
		return;
	}
}