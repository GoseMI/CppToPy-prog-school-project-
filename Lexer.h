#pragma once
#include "utils.h"
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>
#include <fstream>



// Function to tokenize a C++ expression
std::vector<std::string> tokenizer(const std::string& expression) {
    std::vector<std::string> tokens;

    // Regular expression for C++ tokens
    std::regex tokenRegex(R"([{}[\]()<>.,;:+\-*/%=!&|^~()]|\b\w+\b|\n|\"(?:[^\"\\]|\\.)*\"|'(?:[^'\\]|\\.)*')");
    std::sregex_iterator it(expression.begin(), expression.end(), tokenRegex);
    std::sregex_iterator end;

    while (it != end) {
        tokens.push_back(it->str());
        ++it;
    }
    unite_operators(tokens);
    tokens.push_back("\n");
    tokens.push_back("\n");
    tokens.push_back("\n");
    return tokens;
}

//std::string test_tokenizer(const std::string& arg) {
//    std::vector<std::string> v = tokenizer(arg);
//    std::string res;
//    for (auto i : v)
//        res += i + '\n';
//    return res;
//}