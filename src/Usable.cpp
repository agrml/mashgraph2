#include "Usable.h"
#include <assert.h>

/**
 * @file
 * @author Mikhail Agranovskiy, 321, cs msu
 */

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

Matrix<std::tuple<uint, uint, uint>> origin(BMP &img)
{
    Matrix<std::tuple<uint, uint, uint>> imgMatrix(static_cast<uint>(img.TellHeight()),
                                                   static_cast<uint>(img.TellWidth()));
    for (uint i = 0; i < imgMatrix.n_rows; ++i) {
        for (uint j = 0; j < imgMatrix.n_cols; ++j) {
            RGBApixel *p = img(j, i);
            imgMatrix(i, j) = std::make_tuple(p->Red, p->Green, p->Blue);
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

ConvolutionOp::ConvolutionOp(const Matrix<double> &kernel) : kernel_(kernel),
                                                                radius((kernel.n_rows - 1) / 2) {}

/**
 * Прокаченная версия оператора свертки.
 *
 * Note: работает только с матрицами 3*3
 * @param neighbourhood матрица-сосед, с элементами которой мы перемножаем
 * @return сумма произведений
 */
double ConvolutionOp::operator()(const Matrix<double> &neighbourhood) const
{
    // matrices "multiplication"
    assert(neighbourhood.n_cols == neighbourhood.n_rows);
    assert(radius == 1);

    auto sum = _mm_setzero_pd();
    __m128d m1, m2;
    auto f = [&](uint i1, uint j1, uint i2, uint j2) {
        m1 = _mm_setr_pd(neighbourhood(i1, j1), neighbourhood(i2, j2));
        m2 = _mm_setr_pd(kernel_(i1, j1), kernel_(i2, j2));
        sum = _mm_add_pd(sum, _mm_mul_pd(m1, m2));
    };
    f(0, 0, 0, 1);
    f(1, 0, 1, 1);
    f(2, 0, 2, 1);
    f(0, 2, 1, 2);

    double summ[2];
    _mm_storeu_pd(summ, sum);
    return summ[0] + summ[1] + neighbourhood(2,2) * kernel_(2, 2);
}

//// old
//double ConvolutionOp::operator()(const Matrix<double> &neighbourhood) const
//{
//    // matrices "multiplication"
//    assert(neighbourhood.n_cols == neighbourhood.n_rows);
//    assert(radius == (neighbourhood.n_cols - 1) / 2);
//
//    double sum = 0;
//    for (size_t i = 0; i < 2 * radius + 1 ; i++) {
//        for (size_t j = 0; j < 2 * radius + 1; j++) {
//            sum += neighbourhood(i, j) * kernel_(i, j);
//        }
//    }
//    return sum;
//}