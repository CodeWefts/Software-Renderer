#define STB_IMAGE_IMPLEMENTATION
#include "rdr/Texture.h"
#include <cmath>
#include <algorithm>



Texture::Texture()
{

}

Texture::Texture(const char* const filepath)
{
    int nbrChannels;
    unsigned char* result = stbi_load(filepath, &width, &height, &nbrChannels, 0);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            const int texOffset = (x + y * width) * 3;
            mPixels.push_back(Vector3(
                result[texOffset + 0] / 255.f,
                result[texOffset + 1] / 255.f,
                result[texOffset + 2] / 255.f
            ));
        }
    }
}

Texture::~Texture()
{
}

Vector3 Texture::Sample(const float x, const float y) const
{
    int _x = std::floor(x * width);
    int _y = std::floor(y * height);

    _x = std::clamp(_x, 0, width - 1);
    _y = std::clamp(_y, 0, height - 1);

    return mPixels[_x + _y * width];
}