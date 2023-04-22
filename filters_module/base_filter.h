#ifndef CPP_HSE_BASE_FILTER_H
#define CPP_HSE_BASE_FILTER_H


#include "../bmp_image/BMP.h"
#include "cmath"


class Filters {
public:
    /// Class constructor (virtual)
    virtual void Apply(const std::vector<std::string>& parameters, Image& image) {
    }

    /// Class functions
    double ApplyMatrixMain(const std::vector<Pixel>& pixel_matrix, const std::vector<int>& filter_matrix,
                           std::string base_color) const;

    double ConvertToDouble(uint8_t color) const;

    uint8_t ConvertToChar(double color) const;

protected:
    /// Class constants
    const double max_size = 255.0;
};

#endif
