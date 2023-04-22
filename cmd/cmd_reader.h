#ifndef CPP_HSE_CMD_READER_H
#define CPP_HSE_CMD_READER_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "exceptions.h"

using FiltersMap = std::vector<std::pair<std::string, std::vector<std::string>>>;

class Request {
public:
    /// Class constructor
    explicit Request(int argc, char** argv) {
        RequestParameters(argc, argv);
    }

    /// Class functions
    std::string GetInputFile() const;

    std::string GetOutputFile() const;

    FiltersMap GetFilters() const;

    void RequestParameters(int argc, char** argv);

    void PrintGuide();

    /// Class fields
    std::string input_file_;
    std::string output_file_;
    FiltersMap filter_container_;

protected:
    bool CheckNum(char arg);
};

#endif