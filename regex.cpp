#include "regex.h"

Regex::Regex() : regex(NULL), DFA(NULL), current(NULL), index(0), re_compile(false) {}

Regex::Regex(const char* r)
    : regex(r), DFA(NULL), current(NULL), index(0), re_compile(true)
{
    compile();
}


bool Regex::match(const char* str)
{
    int rounds = 1;
    size_t stri = 0;
    State* storage1[256];
    State* storage2[256];
    State** p1 = storage1;
    State** p2 = storage2;
    size_t i1 = 0;
    size_t i2 = 0;

    addState(DFA, p1, i1, rounds);
    rounds++;
    while(str[stri] != '\0')
    {
        for(int i=0; i<i1; i++)
        {
            if(is_match(str[stri], p1[i]))
            {
                if(p1[i]->next1 != NULL)
                    addState(p1[i]->next1, p2, i2, rounds);
                if(p1[i]->next2 != NULL)
                    addState(p1[i]->next2, p2, i2, rounds);
            }
        }
        if(i2 == 0)
            return false;
        
        
        
    }
}


void Regex::addState(State* s, State** p, size_t& i, int r)
{
    if(s->flag == 1100)
    {
        if(s->next1 != NULL)
            addState(s->next1, p, i, r);
        if(s->next2 != NULL)
            addState(s->next2, p, i, r);
    }
    else
    {
        if(s->visit != r)
        {
            s->visit = r;
            p[i] = s;
            i++;
        }
    }
}

bool Regex::is_match(char c, State* s)
{
    int flag = s->flag;
    char* chs = s->chs;
    if(flag < 128){
        if(c == flag)
            return true;
    }
    else if(flag == 1000){
        size_t i = 0;
        while(chs[i] != '\0')
        {
            if(c==chs[i])
                return true;
            i++;
        }
    }
    else if(flag == 1001)
        return true;
    else if(flag == 1002){
        if(c>='0' && c<='9')
            return true;
    }
    else if(flag == 1003){
        if(c<'0' || c>'9')
            return true;
    }
    else if(flag == 1004){
        if(c=='\t' || c=='\r' || c=='\n' || c==' ')
            return true;
    }
    else if(flag == 1005){
        if(c!='\t' && c!='\r' && c!='\n' && c!=' ')
            return true;
    }
    else if(flag == 1006){
        if((c>='0' && c<='9') || (c>='a' && c<='z') || (c>='A' && c<='Z') || (c=='_'))
            return true;
    }
    else if(flag == 1007){
        if(!((c>='0' && c<='9') || (c>='a' && c<='z') || (c>='A' && c<='Z') || (c=='_')))
            return true;
    }
    return false;
}







Regex::~Regex()
{
    State* delete_array[256];
    size_t num = 0;
}

void Regex::compile()
{
    DFA = new State();
    current = &(DFA -> next1);
    State** head = current;
    State** end[MAX_OR];
    size_t end_count = 0;

    while(regex[index] != '\0' && re_compile)
    {
        if(regex[index] == '\\')
            speDFA();
        else if(regex[index] == '[')
            charsDFA();
        else if(regex[index] == '(')
            groupDFA();
        else if(regex[index] == '|')
            splitDFA(head, end, end_count);
        else if(regex[index]==')' || regex[index]=='*' || regex[index]=='+' || regex[index]=='-' || regex[index]=='?' || regex[index]==']')
            re_compile = false;
        else
            singleCharDFA();
        index++;
    }
    if(!re_compile)
        return;
    if(end_count != 0)
    {
        *current = new State();
        for(int i=0; i<end_count; i++)
            *end[i] = *current;
        current = &((*current) -> next1);
    }
    *current = new State(777);
}

void Regex::speDFA()
{
    State** tmp = current;
    index++;
    switch(regex[index])
    {
        case 'd': *current = new State(1002); current = &((*current) -> next1); break;
        case 'D': *current = new State(1003); current = &((*current) -> next1); break;
        case 's': *current = new State(1004); current = &((*current) -> next1); break;
        case 'S': *current = new State(1005); current = &((*current) -> next1); break;
        case 'w': *current = new State(1006); current = &((*current) -> next1); break;
        case 'W': *current = new State(1007); current = &((*current) -> next1); break;
        case '.': *current = new State('.'); current = &((*current) -> next1); break;
        case '?': *current = new State('?'); current = &((*current) -> next1); break;
        case '*': *current = new State('*'); current = &((*current) -> next1); break;
        case '+': *current = new State('+'); current = &((*current) -> next1); break;
        case '(': *current = new State('('); current = &((*current) -> next1); break;
        case ')': *current = new State(')'); current = &((*current) -> next1); break;
        case '[': *current = new State('['); current = &((*current) -> next1); break;
        case ']': *current = new State(']'); current = &((*current) -> next1); break;
        case '-': *current = new State('-'); current = &((*current) -> next1); break;
        case '|': *current = new State('|'); current = &((*current) -> next1); break;
        case '\\': *current = new State('\\'); current = &((*current) -> next1); break;
        default: re_compile = false; return;
    }
    index++;
    switch(regex[index])
    {
        case '?': questionDFA(tmp); break;
        case '*': starDFA(tmp); break;
        case '+': plusDFA(tmp); break;
        default: index--;
    }
}

void Regex::charsDFA()
{
    State** tmp = current;
    char* chs = new char[128];
    size_t itmp = 0;

    index++;
    while(regex[index] != '\0' && re_compile)
    {
        if(regex[index] == '\\' || !is_escape(regex[index]))
        {
            char begin, end;

            if(regex[index] == '\\')
            {
                index++;
                if(is_escape(regex[index]))
                    begin = regex[index];
                else
                    { re_compile = false; break; }
            }
            else
                begin = regex[index];

            if(regex[index+1] == '-')
            {
                if(regex[index+2] == '\\')
                {
                    if(is_escape(regex[index+3]))
                    {
                        end = regex[index+3];
                        index += 3;
                    }
                    else
                        { re_compile = false; break; }
                }
                else if(is_escape(regex[index+2]))
                    { re_compile = false; break; }
                else
                {
                    end = regex[index+2];
                    index += 2;
                }

                if(end >= begin && itmp + end - begin < 127)
                {
                    for(int i=begin; i<=end; i++)
                    {
                        chs[itmp] = (char)i;
                        itmp++;
                    }
                }
                else
                    { re_compile = false; break; }
            }
            else
            {
                chs[itmp] = begin;
                itmp++;
            }
        }
        else if(regex[index] == ']')
            break;
        else
            re_compile = false;
        index++;
    }
    if(!re_compile || regex[index]!=']' || itmp==0)
    {
        delete [] chs;
        re_compile = false;
        return;
    }
    chs[itmp] = '\0';
    *current = new State(1000, chs);
    current = &((*current) -> next1);
    index++;
    switch(regex[index])
    {
        case '?': questionDFA(tmp); break;
        case '*': starDFA(tmp); break;
        case '+': plusDFA(tmp); break;
        default: index--;
    }
}

void Regex::groupDFA()
{
    State** head = current;
    State** end[MAX_OR];
    size_t end_count = 0;

    index++;
    while(regex[index] != '\0' && re_compile)
    {
        if(regex[index] == '\\')
            speDFA();
        else if(regex[index] == '[')
            charsDFA();
        else if(regex[index] == '(')
            groupDFA();
        else if(regex[index] == ')')
            break;
        else if(regex[index] == '|')
            splitDFA(head, end, end_count);
        else if(regex[index]=='*' || regex[index]=='+' || regex[index]=='-' || regex[index]=='?' || regex[index]==']')
            re_compile = false;
        else
            singleCharDFA();
        index++;
    }
    if(!re_compile)
        return;
    if(regex[index] != ')')
    {
        re_compile = false;
        return;
    }
    if(end_count != 0)
    {
        *current = new State();
        for(int i=0; i<end_count; i++)
            *end[i] = *current;
        current = &((*current) -> next1);
    }
    index++;
    switch(regex[index])
    {
        case '?': questionDFA(head); break;
        case '*': starDFA(head); break;
        case '+': plusDFA(head); break;
        default: index--;
    }
}

void Regex::splitDFA(State** head, State*** end, size_t& end_count)
{
    if(end_count == MAX_OR)
    {
        re_compile = false;
        return;
    }
    State* tmp = *head;
    *head = new State();
    (*head) -> next1 = tmp;
    end[end_count] = current;
    end_count++;
    current = &((*head) -> next2);
}

void Regex::singleCharDFA()
{
    State** tmp = current;
    if(regex[index] == '.')
        *current = new State(1001);
    else
        *current = new State(regex[index]);
    current = &((*current) -> next1);

    index++;
    switch(regex[index])
    {
        case '?': questionDFA(tmp); break;
        case '*': starDFA(tmp); break;
        case '+': plusDFA(tmp); break;
        default: index--;
    } 
}

void Regex::questionDFA(State** t)
{
    if(t == current)
    {
        re_compile = false;
        return;
    }
    State* tmp = *t;
    *t = new State();
    (*t) -> next1 = tmp;
    (*t) -> next2 = *current = new State();
    current = &((*current) -> next1);
}

void Regex::starDFA(State** t)
{
    if(t == current)
    {
        re_compile = false;
        return;
    }
    State* tmp = *t;
    *t = new State();
    (*t) -> next1 = tmp;
    *current = *t;
    current = &((*t) -> next2);
}

void Regex::plusDFA(State** t)
{
    if(t == current)
    {
        re_compile = false;
        return;
    }
    *current = new State();
    (*current) -> next1 = *t;
    current = &((*current) -> next2);
}

bool Regex::is_escape(char ch)
{
    if(ch=='.' || ch=='?' || ch=='*' || ch=='+' || ch=='(' || ch==')')
        return true;
    if(ch=='|' || ch=='[' || ch==']' || ch=='-' || ch=='\\')
        return true;
    return false;
}