#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

std::vector<std::string> findFiles(const std::string& path, const std::vector<std::string>& extensions) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
        if (entry.is_regular_file()) {
            for (const auto& ext : extensions) {
                if (entry.path().extension() == ext) {
                    files.push_back(entry.path().string());
                    break;
                }
            }
        }
    }
    return files;
}

void build_cpm_project(std::string sourceDirectory, std::string configFileName, std::string outputDirectory) {
    std::ifstream configFileStream(configFileName);
    if (!configFileStream.is_open()) {
        std::cerr << "Failed to open " << configFileName << std::endl;
        return;
    }

    nlohmann::json config;
    configFileStream >> config;
    std::vector<std::string> extensions = config["extensions"].get<std::vector<std::string>>();
    configFileStream.close();

    std::vector<std::string> files = findFiles(sourceDirectory, extensions);

    for (const auto& file : files) {
        std::cout << file << std::endl;
    }
    std::cout << std::filesystem::create_directory(std::filesystem::path(outputDirectory)) << std::endl;
    std::cout << "Total files: " << files.size() << std::endl;
}