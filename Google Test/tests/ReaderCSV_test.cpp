#include <gtest/gtest.h>
#include "ReaderCSV.h"

static const std::string pathToFiles = "..//..//test_files_csv//";

TEST(ReaderCSVTests, can_open_file) {
    ReaderCSV reader(pathToFiles + "1_table.csv");
    EXPECT_NO_THROW(reader.ReadFile());
}

TEST(ReaderCSVTests, cant_open_file_with_wrong_path) {
    ReaderCSV reader("asdf");
    EXPECT_ANY_THROW(reader.ReadFile(););
}

TEST(ReaderCSVTests, throw_when_left_up_element_no_empty) {
    ReaderCSV reader1(pathToFiles + "2_table.csv");
    ReaderCSV reader2(pathToFiles + "2_table.csv");
    const std::string expected = "[Error] bad header : left-up angle must be empty";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_header_row_consist_name_212asdf) {
    ReaderCSV reader1(pathToFiles + "3_table.csv");
    ReaderCSV reader2(pathToFiles + "3_table.csv");
    const std::string expected = "[Error] bad header rows: header \"212asdf\" must be contains only numbers";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_header_row_consist_name_asdf212) {
    ReaderCSV reader1(pathToFiles + "4_table.csv");
    ReaderCSV reader2(pathToFiles + "4_table.csv");
    const std::string expected = "[Error] bad header rows: header \"asdf212\" must be contains only numbers";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_last_header_row_empty) {
    ReaderCSV reader1(pathToFiles + "5_table.csv");
    ReaderCSV reader2(pathToFiles + "5_table.csv");
    const std::string expected = "[Error] bad header cols: header last column name empty";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_last_element_in_row_empty) {
    ReaderCSV reader1(pathToFiles + "6_table.csv");
    ReaderCSV reader2(pathToFiles + "6_table.csv");
    const std::string expected = "[Error] bad element: last element in rows \"212\" is empty";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}


TEST(ReaderCSVTests, throw_when_ceil_is_empty) {
    ReaderCSV reader1(pathToFiles + "7_table.csv");
    ReaderCSV reader2(pathToFiles + "7_table.csv");
    const std::string expected = "[Error] bad value in table: [212:A] \"\" does not match template";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_header_col_consist_not_only_alphabet_sybmol) {
    ReaderCSV reader1(pathToFiles + "8_table.csv");
    ReaderCSV reader2(pathToFiles + "8_table.csv");
    const std::string expected = "[Error] bad header cols: header \"B123\" must be contains only alphabet symbols";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_header_col_consist_duplicate) {
    ReaderCSV reader1(pathToFiles + "9_table.csv");
    ReaderCSV reader2(pathToFiles + "9_table.csv");
    const std::string expected = "[Error] bad header cols: \"A\" define in cols 2 or more times";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_header_row_consist_duplicate) {
    ReaderCSV reader1(pathToFiles + "10_table.csv");
    ReaderCSV reader2(pathToFiles + "10_table.csv");
    const std::string expected = "[Error] bad header rows: \"1\" define in rows 2 or more times";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_header_row_consist_negative_num) {
    ReaderCSV reader1(pathToFiles + "11_table.csv");
    ReaderCSV reader2(pathToFiles + "11_table.csv");
    const std::string expected = "[Error] bad header rows: header \"-212\" must be positive";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_header_row_consist_num_bigger_than_max_int) {
    ReaderCSV reader1(pathToFiles + "12_table.csv");
    ReaderCSV reader2(pathToFiles + "12_table.csv");
    const std::string expected = "[Error] bad header rows: header \"999999999999\" too big number, out of range MaxInt";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_ceil_consist_num_bigger_than_max_int) {
    ReaderCSV reader1(pathToFiles + "13_table.csv");
    ReaderCSV reader2(pathToFiles + "13_table.csv");
    const std::string expected = "[Error] bad value in table: [212:B] \"999999999999\" fall out of the range int";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_ceil_consist_not_template_expression) {
    ReaderCSV reader1(pathToFiles + "14_table.csv");
    ReaderCSV reader2(pathToFiles + "14_table.csv");
    const std::string expected = "[Error] bad value in table: [212:A] \"12ad2\" does not match template";
    std::string actual;
    try {
        reader1.ReadFile();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.ReadFile());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_formula_contains_wrong_col) {
    ReaderCSV reader1(pathToFiles + "15_table.csv");
    ReaderCSV reader2(pathToFiles + "15_table.csv");
    const std::string expected = "[Error] Calcutate formula: cant find \"Cell\" in header table";
    std::string actual;
    try {
        reader1.ReadFile();
        reader2.ReadFile();
        reader1.CalculateCeils();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.CalculateCeils());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_get_recursive_from_formula_left_args) {
    ReaderCSV reader1(pathToFiles + "16_table.csv");
    ReaderCSV reader2(pathToFiles + "16_table.csv");
    const std::string expected = "[Error] Get recursive when calculate formula: ->212B->1B->212B";
    std::string actual;
    try {
        reader1.ReadFile();
        reader2.ReadFile();
        reader1.CalculateCeils();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.CalculateCeils());
    EXPECT_EQ(expected, actual);
}


TEST(ReaderCSVTests, throw_when_get_recursive_from_formula_right_args) {
    ReaderCSV reader1(pathToFiles + "17_table.csv");
    ReaderCSV reader2(pathToFiles + "17_table.csv");
    const std::string expected = "[Error] Get recursive when calculate formula: ->1B->1C->->1B";
    std::string actual;
    try {
        reader1.ReadFile();
        reader2.ReadFile();
        reader1.CalculateCeils();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.CalculateCeils());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_formula_contains_wrong_row_on_left_operand) {
    ReaderCSV reader1(pathToFiles + "18_table.csv");
    ReaderCSV reader2(pathToFiles + "18_table.csv");
    const std::string expected = "[Error] Calcutate formula: ceil=B2+C1: cant find 2 in header row";
    std::string actual;
    try {
        reader1.ReadFile();
        reader2.ReadFile();
        reader1.CalculateCeils();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.CalculateCeils());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_formula_contains_wrong_row_on_right_operand) {
    ReaderCSV reader1(pathToFiles + "19_table.csv");
    ReaderCSV reader2(pathToFiles + "19_table.csv");
    const std::string expected = "[Error] Calcutate formula: ceil=B1+C3: cant find 3 in header row";
    std::string actual;
    try {
        reader1.ReadFile();
        reader2.ReadFile();
        reader1.CalculateCeils();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.CalculateCeils());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, throw_when_in_formula_divide_by_zero) {
    ReaderCSV reader1(pathToFiles + "20_table.csv");
    ReaderCSV reader2(pathToFiles + "20_table.csv");
    const std::string expected = "[Error] Divide by zero in ceil 2B";
    std::string actual;
    try {
        reader1.ReadFile();
        reader2.ReadFile();
        reader1.CalculateCeils();
    }
    catch (const std::string& exception) {
        actual = exception;
    }
    EXPECT_ANY_THROW(reader2.CalculateCeils());
    EXPECT_EQ(expected, actual);
}

TEST(ReaderCSVTests, no_throw_good_table) {
    ReaderCSV reader1(pathToFiles + "21_table.csv");
    EXPECT_NO_THROW(reader1.ReadFile());
    EXPECT_NO_THROW(reader1.CalculateCeils());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}