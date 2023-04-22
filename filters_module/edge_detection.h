#ifndef CPP_HSE_EDGE_DETECTION_H
#define CPP_HSE_EDGE_DETECTION_H

#include "base_filter.h"
#include "grayscale.h"


class EdgeDetection : public Grayscale {
public:
    /// Class functions
    void Apply(const std::vector<std::string>& parameters, Image& image) override;

    void ThresholdControl(double threshold, Pixel& pixel);

    /// Class constants
    const std::vector<int> edge_matrix_ = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    const size_t default_parameters_size = 1;
};

#endif