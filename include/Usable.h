#pragma once

#include "matrix.h"
#include "EasyBMP.h"
#include <assert.h>

Matrix<double> grayscale(BMP &img);

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

// convolution filter
template <typename T>
Matrix<T> custom(Matrix<T> src_image, const Matrix<double> &kernel)
{
    assert(kernel.n_rows == kernel.n_cols);
    return src_image.unary_map(ConvolutionOp<double>{kernel});
}

Matrix<double> sobel_x(const Matrix<double> &src_image);

Matrix<double> sobel_y(const Matrix<double> &src_image);


//std::vector<std::pair<std::vector<double>, int>>
//histogram(const Matrix<double> &img_matrix,
//          const Matrix<double> &abs,
//          const Matrix<double> &dirs,

template <typename ResT, typename SrcT>
ResT normalizeNumber(SrcT src,
                     ResT min=std::numeric_limits<ResT>::min(),
                     ResT max=std::numeric_limits<ResT>::max())
{
    if (max < min) {
        throw std::string{"normalizeNumber: max < min"};
    }
    if (src < min) {
        return min;
    }
    if (src > max) {
        return max;
    }
    return static_cast<ResT>(src);
}

template <typename T>
ConvolutionOp<T>::ConvolutionOp(const Matrix<double> &kernel) : kernel_(kernel),
                                                                radius(kernel.n_rows) {}

template <typename T>
T ConvolutionOp<T>::operator()(const Matrix<T> &neighbourhood) const
{
    // matrices "multiplication"
    assert(neighbourhood.n_cols == neighbourhood.n_rows);
    assert(radius == (neighbourhood.n_cols - 1) / 2);

    double sum = 0;
    for (size_t i = 0; i < radius; i++) {
        for (size_t j = 0; j < radius; j++) {
            sum += neighbourhood(i, j) * kernel_(i, j);
        }
    }
    return normalizeNumber(sum, T(0), std::numeric_limits<T>::max());
}