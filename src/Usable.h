#pragma once

#include "matrix.h"
#include "EasyBMP.h"
#include <assert.h>

/**
 * @file
 * @author Mikhail Agranovskiy, 321, cs msu
 */

/**
 * Calulate grayscale image.
 * @param img source image
 * @return grayscale matrix
 */
Matrix<double> grayscale(BMP &img);

/**
 * Functor to be used in unary_map tp implement custom filter
 */
class ConvolutionOp
{
    /// kernel of convolution
    Matrix<double> kernel_;
public:
    /// size of kernel
    uint radius = 0;
    /// fix for use inary_map
    uint &vert_radius = radius, &hor_radius = radius;
    /// constructur, yeah
    ConvolutionOp(const Matrix<double> &kernel);
    /// function as is
    double operator()(const Matrix<double> &neighbourhood) const;
};

/**
 * Implementation of convolution filter
 * @param src_image src image
 * @param kernel convolution kernel
 * @return result of usage of the filter
 */
template <typename T>
Matrix<T> custom(Matrix<T> src_image, const Matrix<double> &kernel)
{
    assert(kernel.n_rows == kernel.n_cols);
    return src_image.unary_map(ConvolutionOp{kernel});
}

/// Sobel for x
Matrix<double> sobel_x(const Matrix<double> &src_image);

/// Sobel for y
Matrix<double> sobel_y(const Matrix<double> &src_image);

/**
 * Перед разбиением на клетки изображение расширяется так, чтобы поделиться нацело. Ввыброно дополнение константой (конкретно, нулем) -- чтобы вклад краев не превосходил вклад других клеток.
 * @param src
 * @param newNRows
 * @param newNCols
 * @return
 */
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