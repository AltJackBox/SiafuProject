#include <iostream>
#include <vector>

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
}

bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int&y)
{
    int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 1);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y /** 0*/);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

int main() {
    std::string filename = "RestHomeBathroomEntrance.png";

    int width, height;
    std::vector<unsigned char> image;
    bool success = load_image(image, filename, width, height);
    if (!success)
    {
        std::cout << "Error loading image\n";
        return 1;
    }
    
    std::cout << "Image width = " << width << '\n';
    std::cout << "Image height = " << height << '\n';
    
    const size_t RGB = 1;
    
    int x = 212;
    int y = 256;
    size_t index = RGB * (x * width + y);
    std::cout << "RGBA pixel @ (x=212, y=256): " 
              << static_cast<int>(image[index + 0]) << " "
              << static_cast<int>(image[index + 1]) << " "
              << static_cast<int>(image[index + 2]) << " "
              << static_cast<int>(image[index + 3]) << '\n';

    

    x = 250;
    y = 256;
    index =  (x * width + y);

    std::cout << "RGBA pixel @ (x=250, y=256): " 
              << static_cast<int>(image[index + 0]) << " "
              << static_cast<int>(image[index + 1]) << " "
              << static_cast<int>(image[index + 2]) << " "
              << static_cast<int>(image[index + 3]) << '\n';

    return 0;

}

