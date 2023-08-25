#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "lib/utils.h"
#include "lib/build.h"

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

int main(int argc, char** argv) {
    std::cout << "CPM started..." << std::endl;

    ArgParser parser(argc, argv);

    char currentPath[FILENAME_MAX];

    if (GetCurrentDir(currentPath, sizeof(currentPath))) {
        std::cout << "Current Directory: " << currentPath << std::endl;
    } else {
        std::cerr << "Error retrieving current directory" << std::endl;
        return 1;
    }

    std::string configFileName = parser.get("--conf", "cpm.json");
    std::string sourceDirectory = parser.get("--src", currentPath);
    std::string outputDirectory = parser.get("--out", "cpm_build");

    if (!std::filesystem::exists(sourceDirectory) || !std::filesystem::is_directory(sourceDirectory)) {
        std::cerr << "Invalid directory path provided." << std::endl;
        return 1;
    }

    std::set<std::string> validCommands = {
        "init", "run", "build", "watch", "test", "deploy", "lint"};

    if (validCommands.count(parser.getCommand()) == 0) {
        std::cerr << "Invalid command provided. Valid commands are: init, run, build, watch, test, deploy, lint." << std::endl;
        return 1;
    }

    if (parser.getCommand() == "run") {
        std::string mode = parser.get("--mode", "default");
        std::cout << "Running in " << mode << " mode." << std::endl;
        return 0;
    } else if (parser.getCommand() == "init") {
        init_cpm_project(std::string(currentPath), configFileName);
        return 0;
    } else if (parser.getCommand() == "run") {
        return 0;
    } else if (parser.getCommand() == "build") {
        build_cpm_project(sourceDirectory, configFileName, outputDirectory);
        return 0;
    } else if (parser.getCommand() == "watch") {
        return 0;
    } else if (parser.getCommand() == "test") {
        return 0;
    } else if (parser.getCommand() == "deploy") {
        return 0;
    } else if (parser.getCommand() == "lint") {
        return 0;
    } else {
        std::cerr << "Invalid command provided. Valid commands are: init, run, build, watch, test, deploy, lint." << std::endl;
        return 1;
    }

    // =================================

    // Read extensions from config.json
    
    return 0;
}
