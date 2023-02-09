#include <iostream>
#include "ReaderCSV.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Enter csvreader.exe <fileName.csv>";
        return 0;
    }
    ReaderCSV reader(argv[1]);
    try {
        reader.ReadFile();
        reader.CalculateCeils();
        reader.PrintTable();
    }
    catch (const std::string& exception){
        std::cout << exception << std::endl;
        return -1;
    }
    catch (std::exception ex){ 
        std::cout << ex.what() << std::endl;
        return -2;
    }
    return 0;
}
