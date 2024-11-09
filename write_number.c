#include <unistd.h>   // 使用 usleep 和 write 函數
#include <string.h>   // 使用 strlen 函數
#include <stdio.h>    // 使用 snprintf 函數

int main() {
    for (int i = 1; i <= 50; i++) {
        char buffer[12];                      // 用於存放數字的字串，足夠存放 "50\n" 和結尾符號
        int length = snprintf(buffer, sizeof(buffer), "%d\n", i); // 將數字格式化為字串存入 buffer 中

        write(STDOUT_FILENO, buffer, length); // 使用 write 將字串直接寫入標準輸出
        usleep(100000);                       // 停 0.1 秒 (100,000 微秒)
    }

    return 0;
}
