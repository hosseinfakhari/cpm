#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

#include "tmpls.h"

class ArgParser {
private:
    std::string command;
    std::map<std::string, std::string> args;

public:
    ArgParser(int& argc, char** argv) {
        if (argc < 2) {
            return;
        }

        command = argv[1];

        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            size_t pos = arg.find("=");
            if (pos != std::string::npos) {
                std::string key = arg.substr(0, pos);
                std::string value = arg.substr(pos + 1);
                args[key] = value;
            }
        }
    }

    std::string getCommand() const {
        return command;
    }

    std::string get(const std::string& argName, const std::string& defaultValue = "") const {
        return args.count(argName) ? args.at(argName) : defaultValue;
    }

    bool exists(const std::string& argName) const {
        return args.count(argName) > 0;
    }
};

void writeFileFromEmbeddedData(const unsigned char app[],std::string fileName) {
    std::ofstream out(fileName);
    if(out) {
        out << app;
    }
}

void init_cpm_project(std::string filePath, std::string fileName) {
    nlohmann::ordered_json j;
    j["name"] = "project_name";
    j["version"] = "0.0.1";
    j["description"] = "project description";
    j["compiler"] = "clang++";
    j["extensions"] = {".cpp", ".h", ".hpp"};
    j["excludes"] = {"cpm_output", "deps", "build", ".build", "CMakeFiles"};

    std::cout << "initializing cpm project at: " << filePath << std::endl;
    std::ofstream file(filePath + "/" + fileName);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file for writing!" << std::endl;
        return;
    }

    file << j.dump(4);
    std::cout << std::filesystem::create_directory(std::filesystem::path("src")) << std::endl;
    writeFileFromEmbeddedData(main_app, "./src/main.cpp");
    std::cout << std::filesystem::create_directory(std::filesystem::path("lib")) << std::endl;
    writeFileFromEmbeddedData(utils_h, "./lib/utils.h");
    std::cout << std::filesystem::create_directory(std::filesystem::path("deps")) << std::endl;

    file.close();
}