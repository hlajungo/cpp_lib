#include "alluneed.h"
/* @brief Big num support negative add sub mul di */
struct Bn {
  string n;
  Bn(string s): n(s) {}
  Bn(ll x) { n= to_string(x); }
  bool neg() const { return n[0] == '-'; }
  Bn abs() const { Bn b= *this;
    if(b.neg()) b.n.erase(b.n.begin());
    return b; }
  Bn flip() { if(neg())n.erase(n.begin());
    else n.insert(n.begin(), '-');
    return *this; }
  Bn trim() { Bn b= *this;
    while(SZ(b.n) > 1 && b.n[0] == '0') b.n.erase(b.n.begin());
    return b; }
  bool operator==(const Bn& o) const { return n == o.n; }
  bool operator<(const Bn& o) const { if(neg() != o.neg()) return neg();
    Bn a= abs().trim(), b= o.abs().trim();
    if(SZ(a.n) != SZ(b.n)) return neg() ? SZ(a.n) > SZ(b.n) : SZ(a.n) < SZ(b.n);
    return neg() ? a.n > b.n : a.n < b.n; }
  bool operator>(const Bn& o) const { return o < *this; }
  bool operator>=(const Bn& o) const { return !(*this < o); }
  Bn add(Bn o) { if(neg() && o.neg()) return abs().add(o.abs()).flip();
    if(neg()) return o.sub(abs());
    if(o.neg()) return sub(o.abs());
    string a= n, b= o.n;
    while(SZ(a) < SZ(b)) a= "0" + a;
    while(SZ(b) < SZ(a)) b= "0" + b;
    int c= 0;
    string r= "";
    rrep(i, SZ(a)) {
      int s= (a[i] - 48) + (b[i] - 48) + c;
      c= s / 10;
      r= char(s % 10 + 48) + r; }
    if(c) r= "1" + r;
    return Bn(r).trim(); }
  Bn sub(Bn o) { if(o.neg()) return add(o.abs());
    if(*this < o) return o.sub(*this).flip();
    string a= n, b= o.n;
    while(SZ(b) < SZ(a)) b= "0" + b;
    int c= 0;
    string r= "";
    rrep(i, SZ(a)) {
      int s= (a[i] - 48) - (b[i] - 48) - c;
      c= 0;
      if(s < 0) {
        s+= 10;
        c= 1; }
      r= char(s + 48) + r; }
    return Bn(r).trim(); }
  Bn mul(Bn o) { if(neg() != o.neg()) return abs().mul(o.abs()).flip();
    Bn a= abs(), b= o.abs();
    int s= SZ(a.n), m= SZ(b.n);
    vi v(s + m);
    rrep(i, s) rrep(j, m) v[i + j + 1]+= (a.n[i] - 48) * (b.n[j] - 48);
    rrep(i, s + m) if(v[i] > 9) {
      v[i - 1]+= v[i] / 10;
      v[i]%= 10; }
    string r= "";
    rep(i, s + m) r+= char(v[i] + 48);
    return Bn(r).trim(); }
  Bn div(Bn o) { Bn a= abs(), b= o.abs(), q= 0, one= 1;
    bool s= neg() != o.neg();
    while(a >= b) {
      a= a.sub(b);
      q= q.add(one); }
    if(s) q.flip();
    return q; }};
