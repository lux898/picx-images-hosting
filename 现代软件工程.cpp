#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 字符统计函数
int count_chars(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("错误：无法打开文件 %s\n", filename);
        exit(1); // 异常退出
    }

    int count = 0;
    int ch;
    // 逐个读取字符（fgetc返回EOF表示文件结束）
    while ((ch = fgetc(fp)) != EOF) {
        count++; // 所有字符（空格、制表符、换行符）均计数
    }

    fclose(fp);
    return count;
}

// 单词统计函数（空格/逗号分隔）
int count_words(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("错误：无法打开文件 %s\n", filename);
        exit(1);
    }

    int count = 0;
    int ch;
    int in_word = 0; // 标记是否处于单词中（0：否，1：是）

    while ((ch = fgetc(fp)) != EOF) {
        // 判断当前字符是否为分隔符（空格、逗号、制表符、换行符）
        if (ch == ' ' || ch == ',' || ch == '\t' || ch == '\n') {
            in_word = 0; // 遇到分隔符，退出单词状态
        } else if (!in_word) {
            in_word = 1; // 进入单词状态
            count++;     // 单词数+1
        }
    }

    fclose(fp);
    return count;
}

int main(int argc, char *argv[]) {
    // 校验命令行参数数量（必须是3个：程序名 + 参数 + 文件名）
    if (argc != 3) {
        printf("用法：%s [-c|-w] 文件名\n", argv[0]);
        printf("示例：%s -c input.txt （统计字符数）\n", argv[0]);
        printf("      %s -w input.txt （统计单词数）\n", argv[0]);
        return 1;
    }

    int result;
    // 解析控制参数，执行对应统计
    if (strcmp(argv[1], "-c") == 0) {
        result = count_chars(argv[2]);
        printf("字符数：%d\n", result);
    } else if (strcmp(argv[1], "-w") == 0) {
        result = count_words(argv[2]);
        printf("单词数：%d\n", result);
    } else {
        printf("错误：无效参数 %s\n", argv[1]);
        printf("请使用 -c（统计字符数）或 -w（统计单词数）\n");
        return 1;
    }

    return 0;
}