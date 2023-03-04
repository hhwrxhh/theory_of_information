#include <iostream>
#include <vector>
#include <array>

#include "../external/bitmap/bitmap_image.hpp"

int main()
{
    std::vector<long double> probability;
    std::vector<long double> probability_log;
    std::vector<long double> mul_result;

    bitmap_image image("../other/output_grayscale.bmp");

    if (!image)
    {
        std::cerr << "Error - Failed to open output_grayscale.bmp" << std::endl;
        return 1;
    }

    const unsigned int height = image.height();
    const unsigned int width = image.width();

    for (int i = 0; i < 255; ++i)
    {
        int count = 0;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                rgb_t colour;
                image.get_pixel(x, y, colour);
                
                if (i == static_cast<int>(colour.green))
                    count++;
            }
        }
        probability.emplace_back(count / (static_cast<double>(height) * width));
    }

    for (int i = 0; i < probability.size(); ++i)
    {
        if (probability[i] == 0)
            probability_log.push_back(0);
        else
            probability_log.push_back(log2(probability[i]));
    }

    for (int i = 0; i < probability.size(); ++i)
        mul_result.push_back(probability[i] * probability_log[i]);

    long double sum = 0;
    for (int i = 0; i < mul_result.size(); ++i)
        sum += mul_result[i];

    std::cout << "Entropy of photo: " << -sum  << std::endl;
}



