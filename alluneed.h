#pragma once
#include <bits/stdc++.h>
using namespace std;
#define NUL nullptr
#define rep(i, n) for (int i = 0; i < (n); ++i)        // [0,n-1]
#define forr(i, a, b) for (int i = (a); i < (b); ++i)  // [a,b-1]
#define rrep(i, n) for (int i = (n) - 1; i >= 0; --i)  // [n-1,0]
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define SZ(a) ((int)(a).size())
#define vi vector<int>
#define vvi vector<vector<int>>
#ifdef DEBUG
#define DOUT cout
#else
#define DOUT 0 && cout
#endif
