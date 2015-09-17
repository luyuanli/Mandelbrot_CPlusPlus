//Term Project
//Timer.cpp

#include "Mandelbrot.h"
#include "Timer.h"
#include <iostream>
#include <thread>
#include <vector>

int main(int argc, char** argv){
	TermProject::Mandelbrot mandelbrot(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), std::stof(argv[5]),
		std::stof(argv[6]), std::stof(argv[7]), std::stof(argv[8]));

	Timer total;
	total.Start();
	mandelbrot.CalculateThreadPool();

	total.Stop();
	std::cout << "The time used to draw the mandelbrot picture is : " << total.nsecs() / pow(10, 9) << " second." << std::endl;
	mandelbrot.exportPixelDataToFile();

	return 0;
}