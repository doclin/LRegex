#ifndef _REGEX_H_
#define _REGEX_H_

#include <iostream>

const size_t MAX_OR = 16;
const size_t MAX_STATE = 512;

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
777:    ACCEPT
*/
struct State
{
    int flag;
    char* chs;
    State* next1;
    State* next2;
    int visit;
    State() : flag(1100), chs(NULL), next1(NULL), next2(NULL), visit(0) {}
    State(int f) : flag(f), chs(NULL), next1(NULL), next2(NULL), visit(0) {}
    State(int f, char* c) : flag(f), chs(c), next1(NULL), next2(NULL), visit(0) {}
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
    bool slow_match(const char* str);
    bool is_success() { return re_compile; };
    ~Regex();
private:
    const char* regex;
    State* DFA;
    State** current;
    size_t index;
    bool re_compile;
    void traversal(State* s);
    void traversal(State* s, State** a, size_t& i);
    void traversal(State* s, const char* str, size_t i, bool& r);
    //
    void compile();
    void speDFA();
    void charsDFA();
    void groupDFA();
    void splitDFA(State** head, State*** end, size_t& end_count);
    void singleCharDFA();
    void questionDFA(State** t);
    void starDFA(State** t);
    void plusDFA(State** t);
    bool is_escape(char ch);
    //
    void addState(State* s, State** p, size_t& i, int r);
    bool is_match(char c, State* s);

};



#endif