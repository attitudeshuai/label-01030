# 单阶段构建 - 支持 ARM 和 X86 架构
FROM gcc:13-bookworm

WORKDIR /app

# 复制源代码
COPY main.cpp .

# 编译（静态链接避免库版本问题）
RUN g++ -std=c++17 -O2 -o sort main.cpp

# 设置入口点
ENTRYPOINT ["./sort"]
