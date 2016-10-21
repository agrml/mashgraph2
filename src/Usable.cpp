#include "Usable.h"
#include <assert.h>

Matrix<double> grayscale(BMP &img)
{
    constexpr double R_COEF = 0.229, G_COEF = 0.587, B_COEF = 0.144;
    Matrix<double> imgMatrix(static_cast<uint>(img.TellHeight()),
                              static_cast<uint>(img.TellWidth()));
    for (uint i = 0; i < imgMatrix.n_rows; ++i) {
        for (uint j = 0; j < imgMatrix.n_cols; ++j) {
            RGBApixel *p = img(j, i);
            imgMatrix(i, j) = R_COEF * p->Red + G_COEF * p->Green + B_COEF * p->Blue;
        }
    }
    return imgMatrix;
}



Matrix<double> sobel_x(const Matrix<double> &src_image) {
    Matrix<double> kernel = {{-1, 0, 1},
                             {-2, 0, 2},
                             {-1, 0, 1}};
    return custom(src_image, kernel);
}

Matrix<double> sobel_y(const Matrix<double> &src_image) {
    Matrix<double> kernel = {{ 1,  2,  1},
                             { 0,  0,  0},
                             {-1, -2, -1}};
    return custom(src_image, kernel);
}
