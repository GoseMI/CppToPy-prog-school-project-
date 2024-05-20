#pragma once
#include <vector>
#include <string>

void unite_operators(std::vector<std::string>& arg) {
    bool unite = false;
    int size = arg.size() - 1;
    for (int i = 0; i < size; i++) {
        if (arg[i] == "=" && arg[i + 1] == "=") unite = true;
        else if (arg[i] == "!" && arg[i + 1] == "=") unite = true;
        else if (arg[i] == "<" && arg[i + 1] == "=") unite = true;
        else if (arg[i] == ">" && arg[i + 1] == "=") unite = true;
        else if (arg[i] == ">" && arg[i + 1] == ">") unite = true;
        else if (arg[i] == "<" && arg[i + 1] == "<") unite = true;
        else if (arg[i] == "-" && arg[i + 1] == ">") unite = true;
        else if (arg[i] == "+" && arg[i + 1] == "+") unite = true;
        else if (arg[i] == "-" && arg[i + 1] == "-") unite = true;
        else if (arg[i] == "|" && arg[i + 1] == "|") unite = true;
        else if (arg[i] == "&" && arg[i + 1] == "&") unite = true;
        else if (arg[i] == ":" && arg[i + 1] == ":") unite = true;
        else if (arg[i] == "-" && arg[i + 1] == "=") unite = true;
        else if (arg[i] == "+" && arg[i + 1] == "=") unite = true;
        else if (arg[i] == "/" && arg[i + 1] == "=") unite = true;
        else if (arg[i] == "*" && arg[i + 1] == "=") unite = true;
        else if (arg[i] == "%" && arg[i + 1] == "=") unite = true;


        if (unite) {
            arg[i] += arg[i + 1];
            size--;
            for (int j = i + 1; j < arg.size() - 1; j++)
                arg[j] = arg[j + 1];
            unite = false;
        }
    }
    for (int i = arg.size(); i > size + 1; i--) {
       arg.pop_back();
    }
}

bool in(const std::string& str,const std::vector<std::string>& V) {
    for (auto s : V)
        if (str == s)
            return true;
    return false;
}

bool in_s(const char& seq, const std::string& str) {
    for (auto c : str)
        if (seq == c)
            return true;
    return false;
}
std::string clear_number(const std::string &arg) {
    std::string result;
    for (int i = 0; i < arg.size(); i++) {
        if(in_s(arg[i], "0123456789")) {
            result += arg[i];
        }
    }
    return result;
}

char begin_s(const std::string& arg) {
    return arg[0];
}

std::string cpp_to_py_nesting(const int& num) {
    std::string result;
    for (int i = 0; i < num; i++)
        result += "//";
    return result;
}