//Term Project
//Mandelbrot.h

#pragma once
#include "Image.h"
#include <vector>

namespace TermProject{
	class Mandelbrot : public Image{
		double xMin, yMin, xMax, yMax;
		int maxIteration;
		std::vector<int> interationCounts;
	public:
		Mandelbrot(std::string, int, int, int, double, double, double, double);
		void Calculate(int);
		void TransformIntoPixel(int);
		void CalculateThreaded(int);
		void CalculateThreadPool();
	};
}