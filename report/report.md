# datalab 报告

姓名：赵修齐

学号：2025201723

| 总分 | bitAnd | bitXor | samesign | logtwo | byteSwap | reverse | logicalShift | leftBitCount | float_i2f | floatScale2 | float64_f2i | floatPower2 |
|------|--------|--------|----------|--------|----------|---------|--------------|--------------|-----------|-------------|-------------|-------------|
| 35.00 |  1.00 |  1.00  |   2.00   |  4.00  |   4.00   |  3.00   |     3.00     |     4.00     |    4.00   |    4.00     |    3.00     |     4.00    |


test 截图：


<!-- TODO: 用一个通过的截图，本地图片，放到 imgs 文件夹下，不要用这个 github，pandoc 解析可能有问题 -->

## 解题报告

### 亮点

1.logtwo：采用分段二分定位最高有效位，运算次数少，避免逐位循环。
2.leftBitCount：先对原数取反，再通过 16、8、4、2、1 位分组判断前导零数量。

### logtwo
int logtwo(int v) {
    int result;
    int shift;

    result = (v > 0xFFFF) << 4;
    v = v >> result;

    shift = (v > 0xFF) << 3;
    result = result | shift;
    v = v >> shift;

    shift = (v > 0xF) << 2;
    result = result | shift;
    v = v >> shift;

    shift = (v > 0x3) << 1;
    result = result | shift;
    v = v >> shift;

    result = result | (v >> 1);
    return result;
}
对于正整数，logtwo(v) 等于其二进制最高有效位的编号。本实现采用类似二分查找的方法，依次判断最高位是否跨过 16、8、4、2、1 位。比较表达式产生 0 或 1，再通过左移分别生成 16、8、4、2。每次将已经确定的高位范围移走，使下一次只需在更小范围内继续判断。
这些位移量分别占据不同的二进制位，因此可使用按位或 | 合并。例如 16 与 8 按位或的结果为 24，与两者相加相同。该方法不需要循环，能够在固定次数内得到结果。



### leftBitCount
int leftBitCount(int x) {
    int n = ~x;
    int r1 = (!(n >> 16)) << 4;
    int r2;
    int r3;
    int r4;
    int r5;
    int r6;

    n = n << r1;
    r2 = (!(n >> 24)) << 3;
    n = n << r2;
    r3 = (!(n >> 28)) << 2;
    n = n << r3;
    r4 = (!(n >> 30)) << 1;
    n = n << r4;
    r5 = !(n >> 31);
    n = n << r5;
    r6 = !(n >> 31);

    return r1 + r2 + r3 + r4 + r5 + r6;
}
int leftBitCount(int x) {
    int n = ~x;
    int r1 = (!(n >> 16)) << 4;
    int r2;
    int r3;
    int r4;
    int r5;
    int r6;

    n = n << r1;
    r2 = (!(n >> 24)) << 3;
    n = n << r2;
    r3 = (!(n >> 28)) << 2;
    n = n << r3;
    r4 = (!(n >> 30)) << 1;
    n = n << r4;
    r5 = !(n >> 31);
    n = n << r5;
    r6 = !(n >> 31);

    return r1 + r2 + r3 + r4 + r5 + r6;
}


## 反馈/收获/感悟/总结


## 参考的重要资料

