//
//  main.cpp
//  WinCMD
//
//  Created by Michal Schneider on 18.03.2024.
//

#include <iostream>
#include <string>
#include <cstdlib> // Pro funkci system()
#include <filesystem>


std::string convertCommand(const std::string& windowsCommand) {
    // Oddělení příkazu a parametrů
    size_t spacePos = windowsCommand.find(' ');
    std::string command = windowsCommand.substr(0, spacePos);
    std::string params = (spacePos != std::string::npos) ? windowsCommand.substr(spacePos + 1) : "";
    
    // Převod příkazů
    if (command == "dir") {
        return "ls " + params;
    } else if (command == "type") {
        return "cat " + params;
    } else if (command == "echo") {
        return "echo " + params;
    } else if (command == "cd") {
        return "cd " + params;
    } else if (command == "rd") {
            return "rm -rf " + params;
    } else if (command == "help") {
        std::cout << "List of supported commands is on request. DM me on Github" << std::endl;
    }
    
    // Vracení výchozí hodnoty, když žádná podmínka neplatí
    return windowsCommand;
}


int main() {
    // něco na úvod
    std::cout << "=======================================" << std::endl;
    std::cout << "WinCMD - Run Windows command on Mac. Now and fast." << std::endl;
    std::cout << "=======================================" << std::endl;
    
    std::string windowsCommand;

    // Získání aktuální pracovní složky
        std::filesystem::path currentPath = std::filesystem::current_path();
    
    // Vstup uživatele
    // Vypsání aktuální pracovní složky
        std::cout << "Enter the Windows command - you are in dir: " << currentPath << std::endl;
    std::getline(std::cin, windowsCommand);

    // Převod příkazu
    std::string macCommand = convertCommand(windowsCommand);

    // Spuštění příkazu na macOS
    std::cout << "Running command on your Mac: " << macCommand << std::endl;
    int result = system(macCommand.c_str());

    // Kontrola návratové hodnoty
    if (result == 0) {
        std::cout << "Done." << std::endl;
    } else {
        std::cout << "Error. Please, create issue on Github." << std::endl;
    }

    return 0;
}
