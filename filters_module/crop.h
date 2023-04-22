#ifndef CPP_HSE_BASE_FILTER_H
#define CPP_HSE_BASE_FILTER_H

#include "base_filter.h"

class Crop : public Filters {
public:
    /// Class functions
    void Apply(const std::vector<std::string>& parameters, Image& image) override;

    /// Class constants
    const size_t default_parameters_size = 2;
};

#endif