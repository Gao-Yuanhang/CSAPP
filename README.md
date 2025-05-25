# CSAPP
环境 WSL20.04，使用vscode的WSL插件连接\
root密码参见D:\2024\CSAPP\notes0.md\
环境配置参考 https://zhuanlan.zhihu.com/p/505497911 的第一种方式\
第二种为docker配置，启动命令的docker原生进程..\
![alt text](./images/image.png)

注意，如果git提交时使用的邮箱与github不一致，此提交的内容可以被同步，但不会被用户界面的contribution包含
目前WSL 全局为google邮箱（与github统一），linux kernel programming仓库下局部配置为rwth邮箱

## TODO
paste-image extension 拼尽全力未能战胜，就手动复制图片吧 以后再调
## Datalab
### Requirements
Simulate higher-level operators with a limited number of bit operators.\
for integer puzzles, only **straightline** code is allowed; for floating-point(4 bytes, same as unsigned int) puzzles, control structures are allowed, but float data types & structs are not allowed.

| allowed operators | description           |
| ----------------- | --------------------- |
| !                 | 取反布尔值            |
| ~                 | 按位取反              |
| &                 | 按位与                |
| ^                 | 按位异或              |
| \|                | 按位或                |
| +                 | 普通加                |
| <<                | 左移低位补0           |
| >>                | 右移高位根据符号补0/1 |

### Puzzles
puzzle1 文档的描述好像写错了，写成了x || y
除了howmanybits puzzle，均满足max op要求
所有puzzles思路均通过注释写在代码中
以下为howmanybits puzzle的优化版本，参考https://zhuanlan.zhihu.com/p/339047608
事实上是，在max ops=90的要求下，不可能通过我这种最暴力的线性情况得到结果（因为相当于有32/31种case，90个操作符平均下来每个case只有两个，几乎什么都做不到）
通过指数求解是自然的想法
由于结果是1~32（相当于0~31）之间的一个数，也就是说我们只需要决定一个二进制数000...00xxxxx,最后这五位的0或1
b0~b16这五个变量分别对应这五个比特的值（实际是这五个比特乘上2^n权重后对应的值）

```
int howManyBits(int x) {
    int b16,b8,b4,b2,b1,b0;
    int flag=x>>31;
    x=(flag&~x)|(~flag&x); //x为非正数则不变 ,x 为负数 则相当于按位取反
    b16=!!(x>>16) <<4; //如果高16位不为0,则我们让b16=16
    x>>=b16; //如果高16位不为0 则我们右移动16位 来看高16位的情况
    //下面过程基本类似
    b8=!!(x>>8)<<3;
    x >>= b8;
    b4 = !!(x >> 4) << 2;
    x >>= b4;
    b2 = !!(x >> 2) << 1;
    x >>= b2;
    b1 = !!(x >> 1);
    x >>= b1;
    b0 = x;
  return b0+b1+b2+b4+b8+b16+1;
}
```

## Bomblab
### Requirements
获得二进制可执行文件bomb在若干阶段所期望的输入，正确输入所有字符串即可拆弹。
在线上bomb中，每一次拆弹失败都会给服务器发送消息导致总成绩的减少，离线bomb并没有这一限制，但还是需要通过打断点等方式（如在每一个phase之前断点，在判断炸弹爆炸的指令前查看条件是否满足，如果满足立刻quit）尽可能避免爆炸的后果。

使用的汇编文件同样是ATT格式，可以在objdump时设置参数指定风格，也可以指定gdb的preferred style，有一个区别在于这里的ATT格式基本没有表示数据长度的指令后缀（因为很多可以进行推测）。

使用psol.txt时，文件需要以EOF结尾。且最后一行也需要额外打印出回车（**我不知道具体的机制是什么TODO，但所有的文本文件都应如此处理**）

lab1，单纯地比较字符串相等。

lab2，主要考验对过程传参和栈帧状态转换的理解，查看phase_2的汇编可知，它是读出六个连续的int数据，需要它们之间从1开始逐个乘2才能保证炸弹不爆炸。
这里调用的read_six_numbers函数，其中调用了sscanf函数，这个sscanf共有8个参数，在这三个函数的调用过程中，$rdi一直没有变，也就是一开始的input（所以在调用sscanf时并没有重新要求读入字符串）；第二个参数是存储在内存中的常量字符串"%d %d %d %d %d %d"，表示format；剩余六个参数分别对应到上面的phase_2栈帧中的那六个int变量的地址以接受解析的结果（这里它是完全按顺序的，导致期望的input也是一个完美的等比数列，如果在汇编中打乱顺序，input中数字的顺序也可能被打乱）。最后，sscanf的ret值表示成功读入的结果数量。
```
sscanf(str, "%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
```

lab3(46min)，输入两个int值，x和y，关键在于一个间接跳转。地址基址在0x402470，8\*x表示偏移量，x的值在0-7之间，所以我们要使用x/8xg 这一命令，查看从0x402470开始，以8字节为单位的8块内存，每一块内存的值代表跳转目标指令地址，会将一个值移到eax中，最后比较eax和第二个参数y是否相等
可以不只有一个答案，只要偏移量x、对应操作指令赋给eax的值和输入y匹配即可

lab4(50min)，func_4是一个有三个参数的递归函数，但我并没有看出来它计算有什么实际意义，但实际也没有用到什么实际意义。读入两个int参数A和B，B必须是0，且要求func_4(A, 0, 14)的返回值必须是0，令A=7，可以让这个函数不走进入递归直接返回0

lab5
