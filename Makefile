# 编译器
CC = gcc

# 编译选项
# -Wall: 显示所有警告
# -Ilib: 指定 lib 目录为头文件搜索路径
CFLAGS = -Wall -Ilib

# 链接选项
# -lncurses: 链接 ncurses 库
LDFLAGS = -lncurses -lm

# 最终生成的可执行文件名
EXECUTABLE = game

# 所有的源文件 (.c)
SOURCES = src/main.c lib/game_logic.c lib/ui.c lib/background.c 

# 根据源文件自动生成目标文件 (.o) 的名字
OBJECTS = $(SOURCES:.c=.o)

# 默认执行的规则：生成最终的可执行文件
all: $(EXECUTABLE)

# 如何链接生成最终的可执行文件
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# 如何将 .c 文件编译成 .o 文件
# -c: 只编译，不链接
# $<: 代表依赖文件 (即 .c 文件)
# $@: 代表目标文件 (即 .o 文件)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理规则：删除所有编译生成的文件
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
