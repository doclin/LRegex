# LRegex C++简易正则表达式引擎
by WHU Doclin

## 支持语法
```
X?          X, once or not at all
X*          X, zero or more times
X+          X, one or more times
XY          X followed by Y
X|Y         Either X or Y
(X)         X, as a group
[ac]        a or c(simple character, \d is illegal here)
[a-z0-9]    character range([z-a] is illegal)
```
## 预定义字符与转义符
```
.           any character
\d          [0-9]
\D          ^\d
\s          [\t\n\r ]
\S          ^\s
\w          [a-zA-Z_0-9]
\W          ^\w

\.          .
\?          ?
\*          *
\+          +
\(          (
\)          )
\|          |
\[          [
\]          ]
\-          -
\\          \
```
## 实现细节
LRegex正则引擎的实现主要参考了Russ Cox一篇关于Thompson's algorithm实现的文章和梨梨喵的知乎专栏。  
Regex类首先根据正规式构建NFA。NFA中的的状态节点如下
```
struct State
{
    int flag;       //用于标识状态类型
    char* chs;      //存储字符集合类节点中的匹配字符
    State* next1;   //指向下一状态节点
    State* next2;   //指向下一状态节点
    int visit;      //图遍历时作标识位
};
```
compile()私有方法逐字符读取正规式，递归调用一系列函数完成NFA的构建，最终得到有环图形式的NFA。这种数据结构形式比较直观。实际上，如果将构造过程中动态new State指针赋值改为提前申请线性内存池并用数组下标代替指针链接各个状态，可以得到vector形式的NFA。更进一步抽象就可以转为字节码序列，得到虚拟机形式。总体上讲，算法差异不大，但实现效率有一定提升。Russ Cox文中也有提到

>Thompson introduced the multiple-state simulation approach in his 1968 paper. In his formulation, the states of the NFA were represented by small machine-code sequences, and the list of possible states was just a sequence of function call instructions. In essence, Thompson compiled the regular expression into clever machine code. Forty years later, computers are much faster and the machine code approach is not as necessary. 

完成NFA的构建后，当匹配字符串时，match()函数使用Thompson的multiple-state simulation approach。实际上是将遍历所有可能的路径转为在每个输入上遍历所有可能的状态，将O(2^n)降为O(n^2)，也可以看作动态将NFA转为DFA。提供的另一个slow_match()匹配函数采用递归回溯的方法，在main.cpp中对两种方法做了测试对比。

Ref:  
Engineering a Compiler - Keith D. Cooper  
https://zhuanlan.zhihu.com/p/24458116  
https://swtch.com/~rsc/regexp/regexp1.html  