//Term Project
//Mandelbrot.cpp

#include "Mandelbrot.h"
#include "ThreadPool.h"
#include <algorithm>

namespace TermProject{
	Mandelbrot::Mandelbrot(std::string p, int w, int h, int _maxIteration, double _xMin, double _yMin, double _xMax, double _yMax)
		: Image(p, w, h), maxIteration(_maxIteration), xMin(_xMin), yMin(_yMin), xMax(_xMax), yMax(_yMax){
		interationCounts.resize(w * h);
		pixels.resize(w * h);
	}

	void Mandelbrot::Calculate(int row){
		for (int j = 0; j < width; j++){
			double x0 = xMin + (xMax - xMin)* row / (width - 1);
			double y0 = yMin + (yMax - yMin)* j / (height - 1);
			double x = 0;
			double y = 0;
			int iteration = 0;
			while (x * x + y * y < 2 * 2 && iteration < maxIteration){
				double xTemp = x * x - y * y + x0;
				double yTemp = 2 * x * y + y0;
				x = xTemp;
				y = yTemp;
				iteration = iteration + 1;
			}
			interationCounts[row * width + j] = iteration;
		}
	}

	void Mandelbrot::TransformIntoPixel(int row){
		std::transform(interationCounts.begin() + row * width, interationCounts.begin() + (row + 1) * width, pixels.begin() + row * width,
			[&](int iter) -> Pixel {
			Pixel p;
			p.pix32 = (double)iter / (double)maxIteration * (1u << 24);
			p.pixComponents.red = p.pix32 & 0xff;
			p.pixComponents.green = (p.pix32 >> 8) & 0xff;
			p.pixComponents.blue = (p.pix32 >> 16) & 0xff;
			return p;
		}
		);

	}

	void Mandelbrot::CalculateThreaded(int row){
		Calculate(row);
		TransformIntoPixel(row);
	}

	void Mandelbrot::CalculateThreadPool(){
		ThreadPool pool(std::thread::hardware_concurrency());
		for (int i = 0; i < height; i++){
			std::function<void()> f = std::bind(&Mandelbrot::CalculateThreaded, this, i);
			pool.addJob(f);
		}
	}
}