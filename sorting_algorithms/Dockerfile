# 单阶段构建 - 支持 ARM 和 X86 架构
FROM gcc:13-bookworm

WORKDIR /app

# 复制源代码
COPY main.cpp .
COPY include/ ./include/

# 编译
RUN g++ -std=c++17 -I include -O2 -o sort main.cpp

# 设置入口点
ENTRYPOINT ["./sort"]
