#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

typedef unsigned long long ULL;

bool isHex(const std::string& s) {
    // 正则匹配题目要求的 hex 格式：0[xX][0-9a-fA-F]+
    static const std::regex hexPattern("^0[xX][0-9a-fA-F]+$");
    return std::regex_match(s, hexPattern);
}

bool isDec(const std::string& s) {
    // 十进制格式：纯数字
    static const std::regex decPattern("^[0-9]+$");
    return std::regex_match(s, decPattern);
}

// 转换函数，失败抛出异常
ULL parseString(const std::string& s) {
    if (isHex(s)) {
        return std::stoull(s, nullptr, 16);
    } else if (isDec(s)) {
        return std::stoull(s, nullptr, 10);
    }
    throw std::invalid_argument("Invalid format");
}

int main(int argc, char* argv[]) {
    // 题目要求：假设两个输入。如果参数个数不是3 (程序名 + 2个参数)，则报错
    if (argc != 3) {
        std::cout << "ERROR" << std::endl;
        return 0;
    }

    std::string arg1 = argv[1];
    std::string arg2 = argv[2];

    // 长度检查 
    if (arg1.length() > 15 || arg2.length() > 15) {
        std::cout << "ERROR" << std::endl;
        return 0;
    }

    try {
        ULL num1 = parseString(arg1);
        ULL num2 = parseString(arg2);
        ULL sum = num1 + num2;

        // 输出: 0xHex Dec
        std::cout << "0x" << std::hex << std::uppercase << sum << " " 
                  << std::dec << sum << std::endl;

    } catch (...) {
        // 捕获所有转换异常
        std::cout << "ERROR" << std::endl;
    }

    return 0;
}