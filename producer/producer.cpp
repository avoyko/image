#include "producer.h"

void Producer::Run() {
    BMP bmp(input_file_, output_file_);
    Image image(bmp.pixel_data_);
    this->Produce(filters_map_, image);
    bmp.SaveBMP(image);
}

void Producer::Produce(FiltersMap& filter_map, Image& image) {

    Crop crop;
    Grayscale grayscale;
    Negative negative;
    Sharpening sharpening;
    EdgeDetection edge;
    GaussianBlur gaussian_blur;
    Sobel sobel;

    std::map<std::string, Filters*> possible_filters = {
        {"-gs", &grayscale},       {"-crop", &crop}, {"-neg", &negative}, {"-sharp", &sharpening},
        {"-blur", &gaussian_blur}, {"-edge", &edge}, {"-sobel", &sobel}};

    if (!filter_map.empty()) {
        for (const std::pair<std::string, std::vector<std::string>>& pair : filter_map) {

            std::string filter_name = pair.first;
            const std::vector<std::string> filter_parameters = pair.second;

            if (!CheckCorrectFilter(filter_name)) {
                throw Exception("Incorrect filter name: please try again");
            }

            for (std::pair<std::string, Filters*> name_filter : possible_filters) {
                if (filter_name == name_filter.first) {
                    Filters* filter = name_filter.second;
                    filter->Apply(filter_parameters, image);
                }
            }
        }
    }
}

bool Producer::CheckCorrectFilter(std::string& filter_name) {
    std::set<std::string> filters = {"-gs", "-crop", "-neg", "-edge", "-sobel", "-sharp", "-blur"};
    if (filters.find(filter_name) != filters.end()) {
        return true;
    }
    return false;
}
