#include "alluneed.h"
#define LST n << 1
#define RST n << 1 | 1
#define LRST n << 1, l, (l + r) >> 1
#define RRST n << 1 | 1, ((l + r) >> 1) + 1, r // right range
#define IS_INT(la, ra, lb, rb) ((rb) >= (la) && (ra) >= (lb))
#define IS_INC(la, ra, lb, rb) ((la) >= (lb) && (rb) >= (ra))
/* @brief Segment tree(max) support lazy propagation
 * get(a,b) and add(a,b,v) b included, 0-index
 * O(8n) space, O(n) init, O(log n) add get
 * M for modify, ex: sum st
 * t[n]=t[LST]+t[RST]; for M1 M2
 * return get(ql,qr,LRST)+get(ql,qr,RRST); for M3 */
struct St {
  int n;
  vi t, lz;
  St(int n): n(n), t(4 * n), lz(4 * n) {}
  St(vi& v): n(SZ(v) - 1), t(4 * n), lz(4 * n) { build(v, 1, 0, n); }
  void build(vi& v, int n, int l, int r) {
    if(l == r) {
      t[n]= v[l];
      return;
    }
    build(v, LRST);
    build(v, RRST);
    t[n]= max(t[LST], t[RST]); // M
  }
  void lazy(int n, int l, int r) {
    if(lz[n]) {
      t[n]+= lz[n];
      if(l != r) {
        lz[LST]+= lz[n];
        lz[RST]+= lz[n];
      }
      lz[n]= 0;
    }
  }
  void add(int ql, int qr, int val) {
    if(qr < ql || n < qr) return;
    add(ql, qr, val, 1, 0, n);
  }
  void add(int ql, int qr, int val, int n, int l, int r) {
    lazy(n, l, r);
    if(!IS_INT(l, r, ql, qr)) return;
    if(IS_INC(l, r, ql, qr)) {
      t[n]+= val;
      if(l != r) {
        lz[LST]+= val;
        lz[RST]+= val;
      }
      return;
    }
    add(ql, qr, val, LRST);
    add(ql, qr, val, RRST);
    t[n]= max(t[LST], t[RST]); // M
  }
  int get(int ql, int qr) { return get(ql, qr, 1, 0, n); }
  int get(int ql, int qr, int n, int l, int r) {
    if(!IS_INT(l, r, ql, qr)) return -INT_MAX;
    lazy(n, l, r);
    if(IS_INC(l, r, ql, qr)) return t[n];
    return max(get(ql, qr, LRST), get(ql, qr, RRST)); // M
  }
  void print() {
    cout << get(0, 0);
    forr(i, 1, n + 1) cout << " " << get(i, i);
    cout << "\n";
  }
};
