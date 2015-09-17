//Term Project
//Image.cpp

#include "Image.h"
#include <fstream>

namespace TermProject{
	Image::Image(std::string p, int w, int h) : path(p), width(w), height(h){}

	void Image::exportPixelDataToFile(){
		std::ofstream f(path);
		if (f){
			f << "P3\n";
			f << width << ' ' << height << '\n';
			f << "255\n";

			for (int i = 0; i < height; i++){
				for (int j = 0; j < width; j++){
					f << pixels[i * width + j];
				f << std::endl;
			}
			}
		}
		f.close();
	}

	std::ofstream& operator<<(std::ofstream& f, const Pixel& pixel){
		f << (int)pixel.pixComponents.red << ' ';
		f << (int)pixel.pixComponents.green << ' ';
		f << (int)pixel.pixComponents.blue << ' ';
		return f;
	}
}