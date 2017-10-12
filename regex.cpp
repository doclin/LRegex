#include "regex.h"


Regex::Regex(const char* r)
    : regex(r), DFA(NULL), current(NULL), index(0), re_compile(true)
{
    compile();
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
        else
            singleCharDFA();
        index++;
    }
    if(!re_compile)
        return;
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
        else
            singleCharDFA();
        index++;
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







void Regex::questionDFA(State** t)
{
    State* tmp = *t;
    *t = new State();
    (*t) -> next1 = tmp;
    (*t) -> next2 = *current = new State();
    current = &((*current) -> next1);
}

void Regex::starDFA(State** t)
{
    State* tmp = *t;
    *t = new State();
    (*t) -> next1 = tmp;
    *current = *t;
    current = &((*t) -> next2);
}

void Regex::plusDFA(State** t)
{
    *current = new State();
    (*current) -> next1 = *t;
    current = &((*current) -> next2);
}