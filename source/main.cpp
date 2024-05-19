#include <iostream>
#include <fstream>
#include <FreeImage.h>
#include <json.hpp>

using json = nlohmann::json;

float calculateBrightness(uint8_t red, uint8_t green, uint8_t blue) {
    return 0.299f * red + 0.587f * green + 0.114f * blue;
}

int main(int argc, char* argv[]) {

    
    std::string inputFilename;
    std::string outputFilename;
    std::cout << "¬ведите название bmp файла и его путь: ";
    std::cin >> inputFilename;
    std::cout << "¬ведите название json файла и его путь: ";
    std::cin >> outputFilename;

    FreeImage_Initialise();
    FIBITMAP* bitmap = FreeImage_Load(FIF_BMP, inputFilename.c_str(), BMP_DEFAULT);
    if (!bitmap) {
        std::cerr << "Could not load BMP file: " << inputFilename << std::endl;
        FreeImage_DeInitialise();
        return 1;
    }

    int width = FreeImage_GetWidth(bitmap);
    int height = FreeImage_GetHeight(bitmap);
    int bpp = FreeImage_GetBPP(bitmap);

    if (bpp != 8) {
        std::cerr << "This example only supports 8-bit BMP files." << std::endl;
        FreeImage_Unload(bitmap);
        FreeImage_DeInitialise();
        return 1;
    }

    std::ofstream outputFile(outputFilename, std::ios::out | std::ios::trunc);
    if (!outputFile) {
        std::cerr << "Could not open output JSON file: " << outputFilename << std::endl;
        FreeImage_Unload(bitmap);
        FreeImage_DeInitialise();
        return 1;
    }

    outputFile << "{\n";
    outputFile << "  \"width\": " << width << ",\n";
    outputFile << "  \"height\": " << height << ",\n";
    outputFile << "  \"pixels\": [\n";

    const int pixelCount = width * height;

    bool firstPixel = true;
    int pixelProgress = 0;
    double progress = 0;
    RGBQUAD* palette = FreeImage_GetPalette(bitmap);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x, ++pixelProgress) {
            uint8_t index;
            FreeImage_GetPixelIndex(bitmap, x, y, &index);
            RGBQUAD color = palette[index];
            float brightness = calculateBrightness(color.rgbRed, color.rgbGreen, color.rgbBlue);

            if (!firstPixel) {
                outputFile << ",\n";
            }
            firstPixel = false;

            outputFile << "    {\"x\": " << x << ", \"y\": " << y << ", \"red\": " << (int)color.rgbRed << ", \"green\": " << (int)color.rgbGreen << ", \"blue\": " << (int)color.rgbBlue << ", \"brightness\": " << brightness << "}";
        }
        progress = ((double)pixelProgress / pixelCount) * 100.0;
        std::cout << progress << "\n";
    }

    outputFile << "\n  ]\n";
    outputFile << "}\n";

    outputFile.close();
    FreeImage_Unload(bitmap);
    FreeImage_DeInitialise();

    return 0;
}