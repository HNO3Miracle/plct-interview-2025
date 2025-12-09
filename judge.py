import os
import random
import string

# 配置：生成多少组数据
NUM_CASES = 20
BASE_DIR = "./test_cases"

def ensure_dir(path):
    if not os.path.exists(path):
        os.makedirs(path)

def write_file(path, content):
    with open(path, "w") as f:
        f.write(content)

# ==========================================
# 题目 1: MixPlus (进制加法)
# ==========================================
def solve_mixplus(arg1, arg2):
    try:
        # 兼容 0x 开头和普通 10 进制
        v1 = int(arg1, 16) if arg1.lower().startswith("0x") else int(arg1, 10)
        v2 = int(arg2, 16) if arg2.lower().startswith("0x") else int(arg2, 10)
        res = v1 + v2
        # 输出格式: 0xHEX DEC (HEX大写)
        return f"0x{res:X} {res}"
    except:
        return "ERROR"

def gen_mixplus():
    work_dir = os.path.join(BASE_DIR, "mixplus")
    ensure_dir(work_dir)
    print(f"Generating MixPlus cases in {work_dir}...")
    
    for i in range(1, NUM_CASES + 1):
        # 随机生成 Hex 或 Dec
        is_hex1 = random.choice([True, False])
        is_hex2 = random.choice([True, False])
        
        # 限制在 unsigned long long 范围内
        arg1 = f"0x{random.randint(1, 0xFFFFF):x}" if is_hex1 else str(random.randint(1, 100000))
        arg2 = f"0x{random.randint(1, 0xFFFFF):x}" if is_hex2 else str(random.randint(1, 100000))
        
        # 写入 .in 和 .out
        write_file(os.path.join(work_dir, f"{i}.in"), f"{arg1} {arg2}")
        write_file(os.path.join(work_dir, f"{i}.out"), solve_mixplus(arg1, arg2) + "\n")

# ==========================================
# 题目 2: Cnt (字符串统计)
# ==========================================
def solve_cnt(s):
    s = s.lower()
    counts = {}
    
    # 统计 Pairs
    if len(s) >= 2:
        for i in range(len(s) - 1):
            sub = s[i:i+2]
            counts[sub] = counts.get(sub, 0) + 1
            
    # 统计 Triplets
    if len(s) >= 3:
        for i in range(len(s) - 2):
            sub = s[i:i+3]
            counts[sub] = counts.get(sub, 0) + 1
            
    # 按字典序排序输出 (对应 C++ std::map)
    lines = []
    for k in sorted(counts.keys()):
        lines.append(f"{k} {counts[k]}")
    
    return "\n".join(lines)

def gen_cnt():
    work_dir = os.path.join(BASE_DIR, "cnt")
    ensure_dir(work_dir)
    print(f"Generating Cnt cases in {work_dir}...")
    
    for i in range(1, NUM_CASES + 1):
        length = random.randint(1, 20)
        s = "".join(random.choice(string.ascii_letters) for _ in range(length))
        
        write_file(os.path.join(work_dir, f"{i}.in"), s)
        out_content = solve_cnt(s)
        if out_content: out_content += "\n"
        write_file(os.path.join(work_dir, f"{i}.out"), out_content)

# ==========================================
# 题目 3: Check (几何逻辑 - 修复版)
# ==========================================
def on_segment(p, a, b):
    """判断共线点 p 是否在线段 ab 上 (利用矩形范围判断)"""
    return min(a[0], b[0]) <= p[0] <= max(a[0], b[0]) and \
           min(a[1], b[1]) <= p[1] <= max(a[1], b[1])

def solve_check(coords):
    p1, p2 = (coords[0], coords[1]), (coords[2], coords[3])
    p3, p4 = (coords[4], coords[5]), (coords[6], coords[7])
    
    def cross_product(o, a, b):
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

    # 1. 快速排斥实验 (Bounding Box)
    if (max(p1[0], p2[0]) < min(p3[0], p4[0]) or 
        max(p3[0], p4[0]) < min(p1[0], p2[0]) or 
        max(p1[1], p2[1]) < min(p3[1], p4[1]) or 
        max(p3[1], p4[1]) < min(p1[1], p2[1])):
        return "FALSE"
    
    # 2. 跨立实验 (Cross Product)
    cp1 = cross_product(p1, p2, p3)
    cp2 = cross_product(p1, p2, p4)
    cp3 = cross_product(p3, p4, p1)
    cp4 = cross_product(p3, p4, p2)
    
    # 严格跨立
    if (((cp1 > 1e-9 and cp2 < -1e-9) or (cp1 < -1e-9 and cp2 > 1e-9)) and
        ((cp3 > 1e-9 and cp4 < -1e-9) or (cp3 < -1e-9 and cp4 > 1e-9))):
        return "TRUE"
        
    # 3. 特殊情况：端点接触或重合
    if abs(cp1) < 1e-9 and on_segment(p3, p1, p2): return "TRUE"
    if abs(cp2) < 1e-9 and on_segment(p4, p1, p2): return "TRUE"
    if abs(cp3) < 1e-9 and on_segment(p1, p3, p4): return "TRUE"
    if abs(cp4) < 1e-9 and on_segment(p2, p3, p4): return "TRUE"
    
    return "FALSE"

def gen_check():
    work_dir = os.path.join(BASE_DIR, "check")
    ensure_dir(work_dir)
    print(f"Generating Check cases in {work_dir}...")
    
    for i in range(1, NUM_CASES + 1):
        # 随机生成坐标 (-10 到 10 之间，增加碰撞概率)
        nums = [random.randint(0, 10) for _ in range(8)]
        
        # 强制生成一些必然相交的特殊情况 (每3个生成一个)
        if i % 3 == 0:
            # 十字交叉
            nums = [0, 5, 10, 5, 5, 0, 5, 10]
        elif i % 3 == 1:
            # T型接触 (之前报错的情况)
            nums = [0, 0, 4, 0, 2, 0, 2, 2]

        input_str = " ".join(map(str, nums))
        write_file(os.path.join(work_dir, f"{i}.in"), input_str)
        write_file(os.path.join(work_dir, f"{i}.out"), solve_check(nums) + "\n")

# ==========================================
# 主程序
# ==========================================
if __name__ == "__main__":
    gen_mixplus()
    gen_cnt()
    gen_check()
    print("✅ 所有题目 (.in / .out) 数据生成完毕！")