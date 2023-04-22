#ifndef CPP_HSE_SOBEL_H
#define CPP_HSE_SOBEL_H

#include "base_filter.h"
#include "grayscale.h"


class Sobel : public Grayscale {
public:
    /// Class functions
    void Apply(const std::vector<std::string>& parameters, Image& image) override;

    /// Class constants
    const std::vector<int> horizontal_matrix_ = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    const std::vector<int> vertical_matrix_ = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
};

#endif