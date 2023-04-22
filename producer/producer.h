#ifndef CPP_HSE_PRODUCER_H
#define CPP_HSE_PRODUCER_H

#include "../bmp_image/BMP.h"
#include "../cmd/cmd_reader.h"
#include "../filters_module/sharp.h"
#include "../filters_module/crop.h"
#include "../filters_module/gauss_blur.h"
#include "../filters_module/grayscale.h"
#include "../filters_module/sobel.h"
#include "../filters_module/edge_detection.h"
#include "../filters_module/negative.h"


class Producer {
public:
    /// Class constructor
    Producer(int argc, char** argv) {
        Request request(argc, argv);
        filters_map_ = request.GetFilters();
        input_file_ = request.GetInputFile();
        output_file_ = request.GetOutputFile();
    }

    /// Class functions
    void Produce(FiltersMap& filter_map, Image& image);

    void Run();

    bool CheckCorrectFilter(std::string& filter_name);

protected:
    /// Class fields
    std::string input_file_;
    std::string output_file_;
    FiltersMap filters_map_;
    Vector pixel_data_;
};

#endif  // CPP_HSE_PRODUCER_H
