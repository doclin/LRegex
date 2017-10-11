#ifndef _REGEX_H_
#define _REGEX_H_

#include <stack>

/*
flag:
0-127:  single character
1000:   characters
1001:   .
1002:   \d
1003:   \D
1004:   \s
1005:   \S
1006:   \w
1007:   \W
1100:   e
*/
struct State
{
    int flag;
    char* chs;
    State* next1;
    State* next2;
    State() : flag(1100), chs(NULL), next1(NULL), next2(NULL) {}
    State(int f) : flag(f), chs(NULL), next1(NULL), next2(NULL) {}
    State(int f, char* c) : flag(f), chs(c), next1(NULL), next2(NULL) {}
    ~State()
    {
        if(chs != NULL)
            delete [] chs;
    }
};

class Regex
{
public:
    Regex();
    Regex(const char* r);
    bool match(const char* str);
    ~Regex();
private:
    const char* regex;
    State* DFA;
    State** current;
    size_t index;
    bool re_compile;
    void compile();
    void speDFA();
    void charsDFA();
    void groupDFA();
    void singleCharDFA();
    void questionDFA(State** t);
    void starDFA(State** t);
    void plusDFA(State** t);

};



#endif