#pragma once

#include "matrix.h"
#include "EasyBMP.h"
#include <assert.h>

Matrix<double> grayscale(BMP &img);

Matrix<std::tuple<uint, uint, uint>> origin(BMP &img);

template <typename T>
class ConvolutionOp
{
    Matrix<double> kernel_;
public:
    uint radius = 0;
    uint &vert_radius = radius, &hor_radius = radius;
    ConvolutionOp(const Matrix<double> &kernel);
    T operator()(const Matrix<T> &neighbourhood) const;
};

template <typename T>
class CompareOp
{
public:
    uint radius = 1;
    uint &vert_radius = radius, &hor_radius = radius;
    uint8_t operator()(const Matrix<T> &neighbourhood) const;
};

template <typename T>
uint8_t CompareOp<T>::operator()(const Matrix<T> &neighbourhood) const
{
    // matrices "multiplication"
    assert(neighbourhood.n_cols == neighbourhood.n_rows);
    assert(radius == 1);

    uint8_t sum = 0;
    for (uint i = 0; i < 3 ; i++) {
        for (uint j = 0; j < 3; j++) {
            if (i != 1 && j != 1) {
                sum <<= 1;
                sum += (neighbourhood(1, 1) <= neighbourhood(i, j));
            }
        }
    }
    return sum;
}

// convolution filter
template <typename T>
Matrix<T> custom(Matrix<T> src_image, const Matrix<double> &kernel)
{
    assert(kernel.n_rows == kernel.n_cols);
    return src_image.unary_map(ConvolutionOp<double>{kernel});
}

Matrix<double> sobel_x(const Matrix<double> &src_image);

Matrix<double> sobel_y(const Matrix<double> &src_image);

template <typename T>
ConvolutionOp<T>::ConvolutionOp(const Matrix<double> &kernel) : kernel_(kernel),
                                                                radius((kernel.n_rows - 1) / 2) {}

template <typename T>
T ConvolutionOp<T>::operator()(const Matrix<T> &neighbourhood) const
{
    // matrices "multiplication"
    assert(neighbourhood.n_cols == neighbourhood.n_rows);
    assert(radius == (neighbourhood.n_cols - 1) / 2);

    T sum = 0;
    for (size_t i = 0; i < 2 * radius + 1 ; i++) {
        for (size_t j = 0; j < 2 * radius + 1; j++) {
            sum += neighbourhood(i, j) * kernel_(i, j);
        }
    }
    return sum;
}

template <typename T>
Matrix<T> extraMatrix(const Matrix<T> &src, uint newNRows, uint newNCols)
{
    Matrix<T> ans(newNRows, newNCols);
    for (uint i = 0; i < ans.n_rows; i++) {
        for (uint j = 0; j < ans.n_cols; j++) {
            if (i < src.n_rows && j < src.n_cols) {
                ans(i, j) = src(i, j);
            } else {
                ans(i, j) = T{};
            }
        }
    }
    return ans;
}