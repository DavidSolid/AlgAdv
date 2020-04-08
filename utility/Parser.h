//
// Created by Alessandro on 04/04/2020.
//

#ifndef ALGADV_PARSER_H
#define ALGADV_PARSER_H

#include <vector>
#include <fstream>
#include <sstream>

class Parser {
public:
    explicit Parser();
    std::vector<std::vector<int>> parse(const std::filesystem::path& filename) const;
    void parse(const std::filesystem::path& filename, std::vector<std::vector<int>>& data) const;
};

/*public methods*/

Parser::Parser()= default;

std::vector<std::vector<int>> Parser::parse(const std::filesystem::path& filename) const{

    std::ifstream ifs (filename, std::ifstream::in);

    if(ifs.good()) {
        std::vector<std::vector<int>> data;

        std::string line;

        while (std::getline(ifs, line)) {
            std::vector<int> lineData;
            std::stringstream lineStream(line);
            int value;
            while (lineStream >> value) {
                lineData.push_back(value);
            }
            data.push_back(lineData);
        }
        ifs.close();

        // change all id{1...n} to id-1{0...n-1}
        for(int i = 0; i < data[0][1]; ++i){
            data[i+1][0] -= 1;
            data[i+1][1] -= 1;
        }

        return data;
    }else{
        return std::vector<std::vector<int>>({{0}});
    }
}

void Parser::parse(const std::filesystem::path& filename, std::vector<std::vector<int>> &data)const {
    std::ifstream ifs (filename, std::ifstream::in);
    if(ifs.good() && data.empty()) {

        std::string line;

        while (std::getline(ifs, line)) {
            std::vector<int> lineData;
            std::stringstream lineStream(line);
            int value;
            while (lineStream >> value) {
                lineData.push_back(value);
            }
            data.push_back(lineData);
        }
        ifs.close();
    }

    // change all id{1...n} to id-1{0...n-1}
    for(int i = 0; i < data[0][1]; ++i){
        data[i+1][0] -= 1;
        data[i+1][1] -= 1;
    }
}

#endif //ALGADV_PARSER_H
