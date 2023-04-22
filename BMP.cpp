#include <cmath>
#include "BMP.h"

void BMP::Exit(std::string exit_output) {
    throw Exception(exit_output);
}

void BMP::LoadBMP() {
    std::fstream fin;
    fin.open(bmp_file_input_name_, std::ios_base::in | std::ios_base::binary);
    if (!fin.is_open()) {
        Exit("File is not found: please try again");
        return;
    }
    StreamLoadBMP(fin);
    fin.close();
}

void BMP::StreamLoadBMP(std::istream& fin) {

    fin.read(reinterpret_cast<char*>(&bmp_file_header_), sizeof(bmp_file_header_));
    fin.read(reinterpret_cast<char*>(&bmp_info_header_), sizeof(bmp_info_header_));

    if (bmp_file_header_.file_type != default_file_type) {
        throw Exception("Wrong file format: try again");
    }

    if (bmp_info_header_.bits_per_pixel != default_bits_per_pixel_) {
        throw Exception("Wrong file format: try again");
    }

    const std::streamsize padding = (4 - (bmp_info_header_.pixel_width * 3) % 4) % 4;

    CreatePixelData(bmp_info_header_.pixel_height, bmp_info_header_.pixel_width);
    for (size_t i = 0; i < pixel_data_.size(); ++i) {
        for (size_t j = 0; j < pixel_data_[i].size(); ++j) {
            Pixel pixel = {};
            fin.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
            pixel_data_[bmp_info_header_.pixel_height - i - 1][j] = pixel;
        }
        fin.ignore(padding);
    }
}

void BMP::SaveBMP(Image& image) {
    std::ofstream fout;
    fout.open(bmp_file_output_name_, std::ios_base::out | std::ios_base::binary);
    if (!fout.is_open()) {
        Exit("File is not found: please try again");
        return;
    }
    bmp_info_header_.pixel_width = image.GetWidth();
    bmp_info_header_.pixel_height = image.GetHeight();
    this->pixel_data_ = image.data_;
    StreamSaveBMP(fout);
    fout.close();
}

void BMP::StreamSaveBMP(std::ostream& fout) {

    fout.write(reinterpret_cast<char*>(&bmp_file_header_), sizeof(bmp_file_header_));
    fout.write(reinterpret_cast<char*>(&bmp_info_header_), sizeof(bmp_info_header_));

    const std::streamsize padding = (4 - (bmp_info_header_.pixel_width * 3) % 4) % 4;
    for (size_t i = 0; i < pixel_data_.size(); ++i) {
        for (size_t j = 0; j < pixel_data_[i].size(); ++j) {
            fout.write(reinterpret_cast<char*>(&pixel_data_[bmp_info_header_.pixel_height - i - 1][j]),
                       sizeof(pixel_data_[i][j]));
        }

        char garbage[padding + 1];
        fout.write(reinterpret_cast<const char*>(&garbage), padding);
    }
}

void BMP::CreatePixelData(const size_t height, const size_t width) {
    for (size_t i = 0; i < height; ++i) {
        pixel_data_.push_back({});
        for (size_t j = 0; j < width; ++j) {
            Pixel container = {.b = 0, .g = 0, .r = 0};
            pixel_data_[i].push_back(container);
        }
    }
}

void Image::Resize(size_t new_height, size_t new_width) {
    data_.resize(new_height);

    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i].resize(new_width);
    }
}

size_t Image::GetWidth() const {
    return data_[0].size();
}

size_t Image::GetHeight() const {
    return data_.size();
}

void Image::SetHeight(size_t new_height) {
    height_ = new_height;
}

void Image::SetWidth(size_t new_width) {
    width_ = new_width;
}

std::vector<Pixel> Image::GenerateNeighbours(int current_y, int current_x) {
    std::vector<std::pair<int, int>> candidates = {{current_y - 1, current_x - 1}, {current_y - 1, current_x},
                                                   {current_y - 1, current_x + 1},

                                                   {current_y, current_x - 1},     {current_y, current_x},
                                                   {current_y, current_x + 1},

                                                   {current_y + 1, current_x - 1}, {current_y + 1, current_x},
                                                   {current_y + 1, current_x + 1}

    };

    std::vector<Pixel> pixel_neighbours;

    for (size_t i = 0; i < candidates.size(); ++i) {

        int x_coord = candidates[i].second;
        int y_coord = candidates[i].first;
        int height = static_cast<int>(this->GetHeight());
        int width = static_cast<int>(this->GetWidth());

        if (0 <= x_coord && x_coord < width && 0 <= y_coord && y_coord < height) {
            pixel_neighbours.push_back(data_[y_coord][x_coord]);
        } else {
            pixel_neighbours.push_back(data_[current_y][current_x]);
        }
    }
    return pixel_neighbours;
}
