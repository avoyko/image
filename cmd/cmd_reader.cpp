#include "cmd_reader.h"
#include "stdexcept"

void Request::RequestParameters(int argc, char** argv) {
    std::string current_filter;
    std::string current_filter_parameter;
    int cnt = -1;

    if (argc < 3 && argc != 1) {
        throw Exception("CMD Error: please correct your input");
    } else if (argc == 1) {
        PrintGuide();
    }

    input_file_ = argv[1];
    output_file_ = argv[2];

    for (int i = 3; i < argc; ++i) {
        if (!CheckNum(argv[i][0])) {
            current_filter = argv[i];
            filter_container_.push_back({current_filter, {}});
            ++cnt;
        } else {
            current_filter_parameter = argv[i];
            filter_container_.empty() ? throw Exception("Filter error: please correct your input")
                                      : filter_container_[cnt].second.push_back(current_filter_parameter);
        }
    }
}

std::string Request::GetInputFile() const {
    return input_file_;
}
std::string Request::GetOutputFile() const {
    return output_file_;
}

FiltersMap Request::GetFilters() const {
    return filter_container_;
}

bool Request::CheckNum(char arg) {
    std::vector<char> numbers = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (arg == numbers[i]) {
            return true;
        }
    }
    return false;
}

void Request::PrintGuide() {
    throw Exception(
        "______________________Guidance_______________________\n"
        "You are using Image Processor app for editing .bmp photos.\n"
        "You can run this program by just using this line: {file name} {input file} {output file} [-{filter} "
        "[parameters]...] ...\n"
        "Here are the filters you can use:\n"
        "-crop {width height}: Crop filter\n"
        "-edge {threshold}: EdgeDetection filter\n"
        "-blur {sigma}: Gaussian Blur filter\n"
        "-gs: GrayScale filter\n"
        "-neg: Negative filter\n"
        "-sharp: Sharpening filter\n"
        "-sobel: Sobel operator filter\n");
}