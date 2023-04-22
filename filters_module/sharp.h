#ifndef CPP_HSE_SHARP_H
#define CPP_HSE_SHARP_H

#include "base_filter.h"

class Sharpening : public Filters {
public:
    /// Class functions
    void Apply(const std::vector<std::string>& parameters, Image& image) override;

    /// Class constants
    const std::vector<int> sharp_matrix_ = {0, -1, 0, -1, 5, -1, 0, -1, 0};
};

#endif
