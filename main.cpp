#include <iostream>
#include "regex.h"

using namespace std;

int main()
{
    const char* a = "a";
    const char* b = "ab";
    const char* c = "a*b";
    const char* d = "a?b";
    const char* e = "a+b";
    const char* f = "a|b";
    const char* g = "(a|b)*c";
    const char* h = "[b-fxb]+(B|\\))";
    const char* i = "\\d\\D\\W*\\\\?";
    const char* j = "\\d|[a-z4-8]*|bc?";
    const char* k = "a()c";
    const char* l = "(((a)b)*c)+";
    const char* m = "||||||||";
    const char* n = "\\c";
    const char* o = "a[]c";
    const char* p = "a()*c";
    const char* q = "a[\\d]c";
    const char* r = "a[z-a]v";
    const char* s = "abc[";
    const char* t = "abc(";
    const char* u = "abc)";

    Regex ra(a);
    Regex rb(b);
    Regex rc(c);
    Regex rd(d);
    Regex re(e);
    Regex rf(f);
    Regex rg(g);
    Regex rh(h);
    Regex ri(i);
    Regex rj(j);
    Regex rk(k);
    Regex rl(l);
    Regex rm(m);
    Regex rn(n);
    Regex ro(o);
    Regex rp(p);
    Regex rq(q);
    Regex rr(r);
    Regex rs(s);
    Regex rt(t);
    Regex ru(u);

    cout << ra.is_success() << endl;
    cout << rb.is_success() << endl;
    cout << rc.is_success() << endl;
    cout << rd.is_success() << endl;
    cout << re.is_success() << endl;
    cout << rf.is_success() << endl;
    cout << rg.is_success() << endl;
    cout << rh.is_success() << endl;
    cout << ri.is_success() << endl;
    cout << rj.is_success() << endl;
    cout << rk.is_success() << endl;
    cout << rl.is_success() << endl;
    cout << rm.is_success() << endl;
    cout << rn.is_success() << endl;
    cout << ro.is_success() << endl;
    cout << rp.is_success() << endl;
    cout << rq.is_success() << endl;
    cout << rr.is_success() << endl;
    cout << rs.is_success() << endl;
    cout << rt.is_success() << endl;
    cout << ru.is_success() << endl;

    return 0;
}