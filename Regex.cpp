

Regex::Regex() {}


Regex::Regex(const char* r)
    : regex(r), DFA(NULL), current(NULL), index(0), re_compile(true)
{
    compile();
}


void Regex::compile()
{
    DFA = new State();
    current = &(DFA -> next1);

    while(regex[index] != '\0')
    {
        if(regex[index] == '\\')
            speDFA();
        else if(regex[index] == '[')
            charsDFA();
        else if(regex[index] == '(')
            groupDFA();
        else if(regex[index] == '|')
            splitDFA();
        else
            singleCharDFA();
    }
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