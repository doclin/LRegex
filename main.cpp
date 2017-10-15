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
    const char* super = "a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?aaaaaaaaaaaaaaaaaaaaaa";
    const char* super1 = "a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?aaaaaaaaaaaaaaaaaaaaaaaaaaaaa";


    const char* mgt = "abaabbac";
    const char* mgf = "abacc";
    const char* mht = "cdex)";
    const char* mhf = "B";
    const char* mit = "3s#*&\\\\\\\\\\";
    const char* mif = "3ss\\\\";
    const char* mjt = "bcccc555srf";
    const char* mjf = "";
    const char* mlt = "ababccabc";
    const char* mlf = "cabbc";
    const char* msuper = "aaaaaaaaaaaaaaaaaaaaaa";
    const char* msuper1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa";


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
    Regex rsuper(super);
    Regex rsuper1(super1);

    cout << ra.is_success();
    cout << rb.is_success();
    cout << rc.is_success();
    cout << rd.is_success();
    cout << re.is_success();
    cout << rf.is_success();
    cout << rg.is_success();
    cout << rh.is_success();
    cout << ri.is_success();
    cout << rj.is_success();
    cout << rk.is_success();
    cout << rl.is_success();
    cout << rm.is_success();
    cout << rn.is_success();
    cout << ro.is_success();
    cout << rp.is_success();
    cout << rq.is_success();
    cout << rr.is_success();
    cout << rs.is_success();
    cout << rt.is_success();
    cout << ru.is_success();
    cout << rsuper.is_success();
    cout << rsuper1.is_success() << endl;

    cout << rg.match(mgt);
    cout << rg.match(mgf);
    cout << rh.match(mht);
    cout << rh.match(mhf);
    cout << ri.match(mit);
    cout << ri.match(mif);
    cout << rj.match(mjt);
    cout << rj.match(mjf);
    cout << rl.match(mlt);
    cout << rl.match(mlf);
    cout << rsuper.match(msuper);
    cout << rsuper1.match(msuper1) << endl;         // ~n ms

    cout << rg.slow_match(mgt);
    cout << rg.slow_match(mgf);
    cout << rh.slow_match(mht);
    cout << rh.slow_match(mhf);
    cout << ri.slow_match(mit);
    cout << ri.slow_match(mif);
    cout << rj.slow_match(mjt);
    cout << rj.slow_match(mjf);
    cout << rl.slow_match(mlt);
    cout << rl.slow_match(mlf);
    cout << rsuper.slow_match(msuper);              // ~5 s
    cout << rsuper1.slow_match(msuper1) << endl;    // ~2 min


    /*
    out:
    11111111111100000000011
    101010101011
    101010101011
    */

    return 0;
}