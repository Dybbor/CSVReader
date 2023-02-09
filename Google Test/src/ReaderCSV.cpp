#include "ReaderCSV.h"

ReaderCSV::ReaderCSV(std::string _fileName) {
    fileName = _fileName;
}

std::string ReaderCSV::GetFileName() const {
    return fileName;
}

std::vector<std::string> ReaderCSV::SplitStringToVector(std::string& string, char delimiter) const {
    std::stringstream ss(string);
    std::vector<std::string> res;
    std::string part;
    while (std::getline(ss, part, delimiter)) {
        res.push_back(part);
    }
    return res;
}

void ReaderCSV::CheckKey(const std::string& key) const {
    std::size_t pos;
    int keyMap;
    try {
        keyMap = std::stoi(key, &pos);
        if (key.size() != pos) {
            const std::string messageError = "[Error] bad header rows: header \"" + key + "\" must be contains only numbers";
            throw messageError;
        } else if (keyMap <= 0) {
            const std::string messageError = "[Error] bad header rows: header \"" + key + "\" must be positive";
            throw messageError;
        }
    }
    catch (std::invalid_argument) {
        const std::string messageError = "[Error] bad header rows: header \"" + key + "\" must be contains only numbers";
        throw messageError;
    } catch (std::out_of_range) {
        const std::string messageError = "[Error] bad header rows: header \"" + key + "\" too big number, out of range MaxInt";
        throw messageError;
    } catch (const std::string& exception) {
        throw exception;
    }
}

void ReaderCSV::CheckHeaderColsDuplicate(const std::string& line) const {
    std::stringstream ss(line);
    std::unordered_set<std::string> res;
    std::string partString;
    while (std::getline(ss, partString, ',')) {
        auto [iter, has_been_inserted] = res.insert(partString);
        if (!has_been_inserted) {
            std::string messageError = "[Error] bad header cols: \"" + partString + "\" define in cols 2 or more times";
            throw messageError;
        }
    }
}

void ReaderCSV::CheckKeyOnDuplicate(int number) const {
    for (const auto& el : keysForPrint) {
        if (el == number) {
            std::string messageError = "[Error] bad header rows: \"" + std::to_string(number) + "\" define in rows 2 or more times";
            throw messageError;
        }
    }
}

void ReaderCSV::CheckValueOnTemplate(const std::string& row, const std::string& col, const std::string& value) const {
    const std::regex regexNumbers("^-?[0-9]+$");
    const std::regex regexTemplate("^=[A-z]+[0-9]+[\\+\\-\\*\\/][A-z]+[0-9]+$");
    if (std::regex_match(value.begin(), value.end(), regexNumbers)) {
        try {
            int test = std::stoi(value);
        } catch (std::out_of_range ex) {
            const std::string messageError =
                "[Error] bad value in table: [" + row + ":" + col + "] \"" + value + "\" fall out of the range int";
            throw messageError;
        }

    } else if (!std::regex_match(value.begin(), value.end(), regexTemplate)) {
        const std::string messageError = "[Error] bad value in table: [" + row + ":" + col + "] \"" + value + "\" does not match template";
        throw messageError;
    }
}

void ReaderCSV::ParsingLineToTable(std::string& line, bool isFirstLine) {
    const std::regex regexTemplate("^[A-Za-z]+$");
    if (isFirstLine) {
        if (line[0] == ',') {
            if (line[line.size() - 1] == ',') {
                const std::string messageError = "[Error] bad header cols: header last column name empty";
                throw messageError;
            }
            CheckHeaderColsDuplicate(line.erase(0, 1));
            std::vector<std::string> valueMap = SplitStringToVector(line);
            for (const std::string& str : valueMap) {
                if (!std::regex_match(str.begin(), str.end(), regexTemplate)) {
                    const std::string messageError =
                        "[Error] bad header cols: header \"" + str + "\" must be contains only alphabet symbols";
                    throw messageError;
                }
            }
            table.insert(std::pair(-1, valueMap));
        } else {
            const std::string messageError = "[Error] bad header : left-up angle must be empty";
            throw messageError;
        }
    } else {
        std::vector<std::string> temp = SplitStringToVector(line);
        CheckKey(temp[0]);
        if (line[line.size() - 1] == ',') {
            const std::string messageError = "[Error] bad element: last element in rows \"" + temp[0] + "\" is empty";
            throw messageError;
        }
        size_t cols = 0;
        for (auto it = temp.begin() + 1; it != temp.end(); ++it) {
            CheckValueOnTemplate(temp[0], table[-1][cols], *it);
            cols++;
        }
        int keyMap = std::stoi(temp[0]);
        CheckKeyOnDuplicate(keyMap);
        std::vector<std::string> valueMap(temp.begin() + 1, temp.end());
        keysForPrint.push_back(keyMap);
        table.insert(std::pair(keyMap, valueMap));
    }
}

void ReaderCSV::ReadFile() {
    std::ifstream in(fileName);
    if (!in.is_open()) {
        std::string messageError = "Unable to read file " + fileName + "\n";
        throw messageError;
    }
    std::string line;
    try {
        std::getline(in, line);
        ParsingLineToTable(line, true);
        while (std::getline(in, line)) {
            ParsingLineToTable(line);
        }
    } catch (std::string& exception) {
        throw exception;
    }
}

void ReaderCSV::PrintTable() {
    std::string delimiter = ",";
    constexpr int keyColumnHeader = -1;
    std::cout << " ";
    for (const std::string& el : table[keyColumnHeader]) {
        std::cout << delimiter << el;
    }
    std::cout << std::endl;
    for (const auto& key : keysForPrint) {
        std::cout << key;
        for (const std::string& value : table[key]) {
            std::cout << delimiter << value;
        }
        std::cout << std::endl;
    }
}

int ReaderCSV::GetNumColumn(const std::string& nameColumn) const {
    int count = 0;
    for (const auto& element : table.at(-1)) {
        if (element == nameColumn) {
            return count;
        } else {
            ++count;
        }
    }
    std::string messageError = "[Error] Calcutate formula: cant find \"" + nameColumn + "\" in header table";
    throw messageError;
}

void ReaderCSV::UnparseFormula(std::string& line, std::string& firstColumn, std::string& secondColumn, std::string& firstRow,
    std::string& secondRow, char& operation) {
    bool wasOperation = false;
    for (auto& symbol : line) {
        if (!wasOperation) {
            if (std::isalpha(symbol)) {
                firstColumn += symbol;
            } else if (std::isdigit(symbol)) {
                firstRow += symbol;
            } else {
                operation = symbol;
                wasOperation = true;
            }
        } else {
            if (std::isalpha(symbol)) {
                secondColumn += symbol;
            } else if (std::isdigit(symbol)) {
                secondRow += symbol;
            }
        }
    }
}

std::string ReaderCSV::GetValueFromCeil(int row, int col, std::string& path) {
    const std::string valueCurrentCeil = table[row][col];
    const std::string addressCurrenCeil = std::to_string(row) + table[-1][col];
    path += "->" + addressCurrenCeil;

    if (valueCurrentCeil[0] != '=') {
        if (path.size() > 4) path.erase(path.end() - 4, path.end());
        return valueCurrentCeil;
    }
    std::string needToUnparse(valueCurrentCeil.begin() + 1, valueCurrentCeil.end());
    std::string firstColumn = "";
    std::string secondColumn = "";
    std::string firstRow = "";
    std::string secondRow = "";
    char operation;
    UnparseFormula(needToUnparse, firstColumn, secondColumn, firstRow, secondRow, operation);
    if (std::find(keysForPrint.begin(), keysForPrint.end(), std::stoi(firstRow)) == keysForPrint.end()) {
        std::string messageError = "[Error] Calcutate formula: ceil" + valueCurrentCeil + ": cant find " + firstRow + " in header row";
        throw messageError;
    }
    if (std::find(keysForPrint.begin(), keysForPrint.end(), std::stoi(secondRow)) == keysForPrint.end()) {
        std::string messageError = "[Error] Calcutate formula: ceil" + valueCurrentCeil + ": cant find " + secondRow + " in header row";
        throw messageError;
    }
    if (path.find(firstRow + firstColumn) != std::string::npos) {
        std::string messageError = "[Error] Get recursive when calculate formula: " + path + "->" + firstRow + firstColumn;
        throw messageError;
    }
    std::string leftValueCeil = GetValueFromCeil(std::stoi(firstRow), GetNumColumn(firstColumn), path);
    if (path.find(secondRow + secondColumn) != std::string::npos) {
        std::string messageError = "[Error] Get recursive when calculate formula: " + path + "->" + secondRow + secondColumn;
        throw messageError;
    }
    std::string rightValueCeil = GetValueFromCeil(std::stoi(secondRow), GetNumColumn(secondColumn), path);
    std::string res = "";
    switch (operation) {
        case '+': res = std ::to_string(std::stoi(leftValueCeil) + std::stoi(rightValueCeil)); break;
        case '-': res = std ::to_string(std::stoi(leftValueCeil) - std::stoi(rightValueCeil)); break;
        case '*': res = std ::to_string(std::stoi(leftValueCeil) * std::stoi(rightValueCeil)); break;
        case '/':
            if (std::stoi(rightValueCeil) == 0) {
                std::string messageError = "[Error] Divide by zero in ceil " + addressCurrenCeil;
                throw messageError;
            }
            res = std ::to_string(std::stof(leftValueCeil) / std::stof(rightValueCeil));
            break;
        default: break;
    }
    if (path.size() > 4) path.erase(path.end() - 4, path.end());
    table[row][col] = res;
    return res;
}

void ReaderCSV::CalculateCeils() {
    for (auto& [key, value] : table) {
        try {
            if (key != -1) {
                for (int col = 0; col < value.size(); ++col) {
                    std::string path = "";
                    table[key][col] = GetValueFromCeil(key, col, path);
                }
            }
        } catch (const std::string& exception) {
            throw exception;
        }
    }
}
