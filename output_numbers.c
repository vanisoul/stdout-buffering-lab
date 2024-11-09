#include <stdio.h>
#include <unistd.h>   // 使用 usleep 函數
#include <string.h>   // 使用 strlen 函數

int main() {
    FILE *fp = stdout;

    for (int i = 1; i <= 50; i++) {
        char buffer[12];                      // 用於存放數字的字串，足夠存放 "50\n" 和結尾符號
        int length = snprintf(buffer, 12, "%d\n", i); // 將數字格式化為字串存入 buffer 中

        fwrite(buffer, sizeof(char), length, fp); // 使用 fwrite 寫入字串格式
        usleep(100000);                           // 停 0.1 秒 (100,000 微秒)
    }

    return 0;
}

