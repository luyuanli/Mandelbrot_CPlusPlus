//Term Project
//Image.h

#pragma once
#include <string>
#include <vector>

namespace TermProject{
	union Pixel{
		unsigned __int32 pix32;
		struct{
			unsigned __int8 red;
			unsigned __int8 green;
			unsigned __int8 blue;
		} pixComponents;
	};

	class Image{
	protected:
		int width;
		int height;
		std::string path;
		std::vector<Pixel> pixels;
	public:
		Image(std::string, int, int);
		void exportPixelDataToFile();
	};


	std::ofstream& operator<<(std::ofstream&, const Pixel&);
}