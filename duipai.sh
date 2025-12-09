#!/bin/bash

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# 1. 编译所有 C++ 程序
echo "🔨 Compiling all targets..."
make -s all
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi

# 2. 定义对拍函数
run_judge() {
    PROG_NAME=$1
    CASE_DIR="./test_cases/$1"
    
    echo "========================================"
    echo "Testing Problem: $PROG_NAME"
    echo "========================================"

    if [ ! -d "$CASE_DIR" ]; then
        echo "No test cases found. Run 'python3 judge.py' first."
        return
    fi

    total=0
    pass=0
    
    # 遍历所有 .in 文件 (按数字顺序排序)
    for input_file in $(ls $CASE_DIR/*.in | sort -V); do
        ((total++))
        case_id=$(basename "$input_file" .in)
        output_file="$CASE_DIR/${case_id}.out"
        
        # 读取输入参数
        args=$(cat "$input_file")
        
        # 运行用户程序 -> user.tmp
        ./$PROG_NAME $args > user.tmp 2>&1
        
        # 比对 (-w 忽略空格, -B 忽略空行)
        diff -w -B user.tmp "$output_file" > diff.log
        
        if [ $? -eq 0 ]; then
            echo -e "Case $case_id: ${GREEN}AC${NC}"
            ((pass++))
        else
            echo -e "Case $case_id: ${RED}WA${NC}"
            echo "   [Input]: ./$PROG_NAME $args"
            echo "   [Yours]:"
            cat user.tmp
            echo "   [Expct]:"
            cat "$output_file"
        fi
    done
    
    echo "----------------------------------------"
    echo -e "Result: ${GREEN}$pass${NC} / $total passed."
    rm -f user.tmp diff.log
}

# 3. 检查数据是否存在，不存在则生成
if [ ! -d "./test_cases" ]; then
    echo "⚠️  Test data not found. Generating..."
    python3 judge.py
fi

# 4. 依次运行三个题目的测试
run_judge "mixplus"
run_judge "cnt"
run_judge "check"