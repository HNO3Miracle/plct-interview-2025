#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

int main(int argc, char* argv[]) {
    // 错误处理 [cite: 27]
    if (argc < 2) {
        std::cout << "ERROR: Need a string." << std::endl;
        return 0;
    }

    std::string input = argv[1];
    
    // 转换为小写，实现不区分大小写 
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    std::map<std::string, int> frequencyMap;

    int len = input.length();

    // 提取成对 (Pairs)
    if (len >= 2) {
        for (int i = 0; i <= len - 2; ++i) {
            frequencyMap[input.substr(i, 2)]++;
        }
    }

    // 提取三元组 (Triplets)
    if (len >= 3) {
        for (int i = 0; i <= len - 3; ++i) {
            frequencyMap[input.substr(i, 3)]++;
        }
    }

    // 输出结果 [cite: 29-33]
    for (const auto& pair : frequencyMap) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    return 0;
}