//
// Created by mikhail on 28.01.17.
//

#include <gtest/gtest.h>
#include "EasyBMP.h"
#include "Usable.h"

/// source image will be splited to thet number of squares
constexpr uint8_t N_SQUARES_PER_LINE = 8;
/// size of histogram (number of sections in 2pi interval)
constexpr uint8_t HIST_SZ = 8;

TEST(Test, SSE) {
    BMP* img = new BMP();
    img->ReadFromFile("Lenna.bmp");
    auto imgMatrix = grayscale(*img);

    auto n = static_cast<uint>(img->TellHeight());
    auto m = static_cast<uint>(img->TellWidth());
    n = n + (n % N_SQUARES_PER_LINE ? N_SQUARES_PER_LINE - n % N_SQUARES_PER_LINE : 0);
    m = m + (m % N_SQUARES_PER_LINE ? N_SQUARES_PER_LINE - m % N_SQUARES_PER_LINE : 0);


    auto xProj = sobel_x(imgMatrix, false);
    auto yProj = sobel_y(imgMatrix, false);

    auto xProjSse = sobel_x(imgMatrix, true);
    auto yProjSse = sobel_y(imgMatrix, true);

    // calculate gradients
    /// gradients absolute values
    Matrix<double> abs(n, m);
    Matrix<double> absSse(n, m);
    for (uint i = 0; i < n; i++) {
        for (uint j = 0; j < m; j++) {
            abs(i, j) = std::sqrt(std::pow(xProj(i, j), 2) + std::pow(yProj(i, j), 2));
            absSse(i, j) = std::sqrt(std::pow(xProjSse(i, j), 2) + std::pow(yProjSse(i, j), 2));
        }
    }

    for (uint i = 0; i < n; i++) {
        for (uint j = 0; j < m; j++) {
            EXPECT_NEAR(abs(i, j), absSse(i, j), 0.0001);
        }
    }

    delete img;
}

/// The entry point.
/// @param argc The number of arguments passed to the program.
/// @param argv The arguemnts passed to the program.
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
