#ifndef CPP_HSE_GAUSS_BLUR_H
#define CPP_HSE_GAUSS_BLUR_H

#include "base_filter.h"


class GaussianBlur : public Filters {
public:
    /// Class functions
    void Apply(const std::vector<std::string>& parameters, Image& image) override;

    void HorizontalBlur(Vector& pixel_data, const size_t width, const size_t height, const int ratio,
                        const double sigma);
    void VerticalBlur(Vector& pixel_data, const size_t width, const size_t height, const int ratio, const double sigma);

    /// Class constants
    const double pi = std::numbers::pi;
    const double euler = std::numbers::e;
    const double regulator = 2.15;
    const size_t default_parameters_size = 1;
};

#endif