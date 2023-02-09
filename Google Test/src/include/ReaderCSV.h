#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <iostream>

class ReaderCSV {
private:
    std::string fileName;
    std::unordered_map<int, std::vector<std::string>> table;
    std::vector<int> keysForPrint;
    std::vector<std::string> SplitStringToVector(std::string& string, char delimiter = ',') const;
    void CheckKey(const std::string& key) const;
    void CheckHeaderColsDuplicate(const std::string& line) const;
    void CheckKeyOnDuplicate(int number) const;
    void CheckValueOnTemplate(const std::string& row, const std::string& col, const std::string& value) const;
    void ParsingLineToTable(std::string& line, bool isFirstLine = false);
    int GetNumColumn(const std::string& nameCeil) const;
    void UnparseFormula(std::string& line, std::string& firstColumn, std::string& secondColumn, std::string& firstRow,
        std::string& secondRow, char& operation);
    std::string GetValueFromCeil(int row, int col, std::string& path);

public:
    explicit ReaderCSV(std::string _fileName);
    std::string GetFileName() const;
    void ReadFile();
    void PrintTable();
    void CalculateCeils();
};
