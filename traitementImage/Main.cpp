#include "Main.hpp"

void Main::start()
{
	if (_argc <= 1)
	{
		std::cout << "no path given..." << std::endl;
		return;
	}

	std::string path(_argv[1]);

	if (_argc >= 3)
	{
		if (_argv[2] == "verbose")
		{
			saveData = true;
		}
	}

	if (fileReader.isDirectory(path))
	{
		auto listpaths = fileReader.getImagesPathList(path);

		if (listpaths.size() <= 0)
		{
			std::cout << "no image in the given directory..." << std::endl;
			return;
		}

		struct stat buffer;
		std::string directoryPath(path + "/files");

		if (stat(directoryPath.c_str(), &buffer) != 0)
		{
			fileReader.createDirectory(directoryPath);
		}

		fileReader.loadImages(imageManager, listpaths);

		ImageData backgroundImage = imageManager.getBackground();

		ImageData grayBackgroundImage = imageManager.getGrayScaleImage(backgroundImage);
		imageManager.removeNoise(grayBackgroundImage, 3);

		if (saveData)
		{
			fileReader.writeImage(std::string(directoryPath + "/background-gray.jpg"), grayBackgroundImage, JCS_GRAYSCALE);
		}

		for (int i = 0; i < 10; i++)
		{
			ImageData grayScaledImage = imageManager.getGrayScaleImage(imageManager.getImage(i));
			std::cout << "gray background built" << std::endl;

			imageManager.removeNoise(grayScaledImage, 3);

			std::string extensionFile(".jpg");

			if (saveData)
			{
				std::string nameFile(directoryPath + "/gray-000");
				
				fileReader.writeImage(nameFile + std::to_string(i) + extensionFile, grayScaledImage, JCS_GRAYSCALE);
			}

			ImageData mask = imageManager.getMask(grayBackgroundImage, grayScaledImage);
			std::cout << "mask built" << std::endl;

			if (saveData)
			{
				std::string maskNameFile(directoryPath + "/mask-000");
				fileReader.writeImage(maskNameFile + std::to_string(i) + extensionFile, mask, JCS_GRAYSCALE);
			}

			imageManager.fusionImages(backgroundImage, imageManager.getImage(i), mask);

			delete[] mask.data;
			delete[] grayScaledImage.data;
		}
		
		if (saveData)
		{
			fileReader.writeImage(std::string(directoryPath + "/background.jpg"), backgroundImage, JCS_RGB);
		}
		else
		{
			fileReader.writeImage(std::string(path + "/background.jpg"), backgroundImage, JCS_RGB);
		}

		delete[] grayBackgroundImage.data;
		delete[] backgroundImage.data;
	}
	else
	{
		std::cout << "is not a directory" << std::endl;
		return;
	}
}