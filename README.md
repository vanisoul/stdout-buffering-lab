# 建立一個 c 測試 fwrite 測試其預設行為

### 預設 標準輸出 為行緩衝

- ./output_numbers

### 預設 檔案輸出 為 N 大小緩衝

- ./output_numbers > output.txt

### 透過 stdbuf 指令 影響 fwrite 預設輸出

- stdbuf -o 4096 ./output_numbers

# 實際應用至 grep 指令

### 輸出標準輸出 所以是行緩衝

- ./number.sh | grep "###"

### 一樣透過 stdbuf 可改變其緩衝大小

- ./number.sh | stdbuf -o 4096 grep "###"

### 同樣輸出至檔案 預期為 N 大小緩衝 依然可以透過 stdbuf 設定非常小的緩衝

- ./number.sh | stdbuf -o 1 grep "###" > output.txt

# 另外說明一下 grep --line-buffered 參數

### git clone https://git.savannah.gnu.org/git/grep.git

--line-buffered 參數與上述緩衝架構的設定完全無關
實際上就是在原始碼中根據如果有此參數就強制 fflush

- L1350

```
if (line_buffered)
  fflush_errno ();
```

- L478

```
fflush_errno (void)
{
  if (fflush (stdout) != 0)
    stdout_errno = errno;
}
```
