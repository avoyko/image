#ifndef CPP_HSE_NEGATIVE_H
#define CPP_HSE_NEGATIVE_H

#include "base_filter.h"


class Negative : public Filters {
public:
    /// Class functions
    void Apply(const std::vector<std::string>& parameters, Image& image) override;
};

#endif