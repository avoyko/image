#ifndef CPP_HSE_GRAYSCALE_H
#define CPP_HSE_GRAYSCALE_H

#include "base_filter.h"


class Grayscale : public Filters {
public:
    /// Class functions
    void Apply(const std::vector<std::string>& parameters, Image& image) override;

    /// Class functions
    const double red_const_ = 0.299;
    const double green_const_ = 0.587;
    const double blue_const_ = 0.114;
};

#endif