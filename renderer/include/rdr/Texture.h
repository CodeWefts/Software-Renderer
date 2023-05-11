#pragma once
#include "std_image/std_image.h"
#include "ToolBox/Vector3.hpp"

#include <vector>
class Texture
{
public:


	Texture();
	Texture(const char* const filepath);
	~Texture();
	Vector3 Sample(const float x, const float y) const;

private:
	int width;
	int height;
	std::vector<Vector3> mPixels;
};