#pragma once
#include "../alluneed.h"
/* @brief Adjacency list weighted
 * For each v, save all edge that v has.
 * O(1) add_v add_e add_ue O(|V|+|E|) rm_v query O(|E|) rm_e
 */
template<typename W, typename V> struct Adj_list_w {
  unordered_map<V, vector<pair<W, V>>> g;
  Adj_list_w() {}
  Adj_list_w(int n) {
    rep(i, n) {
      vector<pair<W, V>> t;
      g[i]= t; }}
  void add_e(W w, V u, V v) {
    g[u].eb(w, v);
    g[v].eb(w, u); }
  void add_ue(W w, V u, V v) { g[u].emplace_back(w, v); }
  Adj_list_w<W, V> get_adj_list() const { return g; }
  void print() {
    for(auto& u: g) {
      cout << u.first << ":";
      for(auto& v: u.second) { cout << v.second << "," << v.first << " "; }
      cout << "\n"; }}
  /* @brief The min cost of minimum spanning tree of `g` start from `s_v`
   */
  W mst_prim_w(V s_v) {
    priority_queue<pair<W, V>, vector<pair<W, V>>, greater<pair<W, V>>> min_heap;
    vector<bool> visited(SZ(g), false);
    W min_cost= 0;
    min_heap.push({ 0, s_v });
    while(!min_heap.empty()) {
      auto [w, s]= min_heap.top();
      min_heap.pop();
      if(visited[s]) continue;
      min_cost+= w;
      visited[s]= true;
      for(auto& [w, e]: g.at(s)) {
        if(!visited[e]) { min_heap.push({ w, e }); }}}
    return min_cost; }
  /* @brief Minimum spanning tree of `g`
   */
  unordered_map<V, vector<pair<W, V>>> mst_prim(V s_v) {
    unordered_map<V, vector<pair<W, V>>> mst;
    priority_queue<tuple<W, V, V>, vector<tuple<W, V, V>>, greater<tuple<W, V, V>>> min_heap;
    vector<bool> visited(SZ(g), false);
    bool first= true;
    min_heap.push({ -1, s_v, -1 });
    while(!min_heap.empty()) {
      auto [w, s, e]= min_heap.top();
      min_heap.pop();
      if(visited[s]) continue;
      // 將要選擇此點，並加入他的鄰點
      if(first == false) {
        mst[e].push_back({ w, s });
        mst[s].push_back({ w, e }); }
      first= false;
      visited[s]= 1;
      for(auto& [nw, ne]: g.at(s)) {
        if(visited[ne]) continue;
        min_heap.push(make_tuple(nw, ne, s)); }}
    return mst; }
};
/*
 * @brief Adjacency matrix weighted
 * matrix idx is [from][to]
 * O(|V^2|) add_v em_v
 * O(1) add_e rm_e query
 */
template<typename W, typename V> struct Adj_mat_w {
  vector<vector<pair<W, V>>> g;
  Adj_mat_w(int n) {
    rep(i, n) {
      vector<pair<W, V>> t;
      g.eb(t);
    }
  }
  void add_e(W w, V u, V v) {
    g[u].eb(w, v);
    g[v].eb(w, u);
  }
  void add_ue(W w, V u, V v) { g[u].emplace_back(w, v); }
  unordered_map<V, vector<pair<W, V>>> get_adj_list() const {
    unordered_map<V, vector<pair<W, V>>> lst;
    for(size_t u= 0; u < g.size(); ++u) { lst[u]= g[u]; }
    return lst;
  }
  // vector<vector<pair<W, V>>> g;
  void print() {
    rep(i, SZ(g)) {
      cout << i << ":";
      rep(j, SZ(g[i])) { cout << g[i][j].second << "," << g[i][j].first << " "; }
      cout << "\n";
    }
  }
};
