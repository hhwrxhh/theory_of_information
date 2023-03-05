#include <iostream>
#include <vector>
#include <array>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "../external/stbi_image/stbi_image.h"
#include "../external/bitmap/bitmap_image.hpp"

using namespace cv;

bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int& y)
{
    int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 4);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y * 4);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

int main(int argc, char** argv)
{

    //std::array<int, 255> counter_array;
    //counter_array.fill(0);

    //std::vector<long double> probability;
    //std::vector<long double> probability_log;
    //std::vector<long double> mul_result;

    ////std::string filename = "../other/output_grayscale.png";
    //std::string filename = "../other/orange.png";

    //int width, height;
    //std::vector<unsigned char> image;
    //bool success = load_image(image, filename, width, height);
    //if (!success)
    //{
    //    std::cout << "Error loading image: " << filename << std::endl;
    //    return 1;
    //}

    //std::cout << "Image width = " << width << '\n';
    //std::cout << "Image height = " << height << '\n';

    //const int RGBA = 4;
    //int index = 0;

    //for (int y = 0; y < height; ++y)
    //{
    //    for (int x = 0; x < width; ++x)
    //    {
    //        index = RGBA * (y * width + x);
    //        int red = static_cast<int>(image[index]);

    //        for (int i = 0; i < 255; ++i)
    //        {
    //            if (i == red)
    //            {
    //                ++counter_array[i];
    //                break;
    //            }
    //        }
    //    }
    //}

    //for (int i = 0; i < counter_array.size(); ++i)
    //    probability.emplace_back(counter_array[i] / (static_cast<double>(height) * width));

    //for (int i = 0; i < probability.size(); ++i)
    //{
    //    if (probability[i] == 0)
    //        probability_log.push_back(0);
    //    else
    //        probability_log.push_back(log2(probability[i]));

    //    mul_result.push_back(probability[i] * probability_log[i]);
    //}

    //long double sum = 0;
    //for (int i = 0; i < mul_result.size(); ++i)
    //    sum += mul_result[i];
    //
    //std::cout << "Entropy of photo " << filename  << ": " << -sum << std::endl;


    Mat img = cv::imread("../other/output_grayscale.png", IMREAD_COLOR);

    /// Establish the number of bins
    int histSize = 256;
    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true; bool accumulate = false;
    /// Compute the histograms:
    Mat hist;
    calcHist(&img, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);
    hist /= img.total();
    hist += 1e-4; //prevent 0

    Mat logP;
    cv::log(hist, logP);

    float entropy = -1 * sum(hist.mul(logP)).val[0];

    std::cout << entropy << std::endl;
}

