#pragma once
#include "graph.hpp"
#include <unordered_map>
#include <vector>
/* @brief The min cost of minimum spanning tree of `g` start from `start_v`
 */
template<typename W, typename V> W mst_prim_w(const Adj_list_w<W, V>& g, V start_v) {
  priority_queue<pair<W, V>, vector<pair<W, V>>, greater<pair<W, V>>> min_heap;
  vector<bool> visited(SZ(g.g), false);
  W min_cost= 0;
  min_heap.push({ 0, (V)start_v });
  while(!min_heap.empty()) {
    auto [w, s]= min_heap.top();
    min_heap.pop();
    if(visited[s]) continue;
    min_cost+= w;
    visited[s]= true;
    for(const auto& [w, e]: g.g.at(s)) {
      if(!visited[e]) { min_heap.push({ w, e }); }
    }
  }
  return min_cost;
}
/* @brief Minimum spanning tree of `g`
 */
template<typename W, typename V> unordered_map<V, vector<pair<W, V>>> mst_prim(const Adj_list_w<W, V>& g, const int s_v) {
  // [s][[w,e]]
  unordered_map<V, vector<pair<W, V>>> mst;
  priority_queue<tuple<W, V, V>, vector<tuple<W, V, V>>, greater<tuple<W, V, V>>> min_heap;
  vector<bool> visited(SZ(g.g), 0);
  bool first= true;
  min_heap.push({ 0, s_v, 0 });
  while(!min_heap.empty()) {
    auto [w, u, e]= min_heap.top();
    min_heap.pop();
    if(visited[u]) continue;
    // 將要選擇此點，並加入他的鄰點
    if(first == false) {
      mst[e].push_back({ w, u });
      mst[u].push_back({ w, e });
    }
    first= false;
    visited[u]= 1;
    for(const auto v: g.g.at(u)) {
      if(visited[v.second]) continue;
      min_heap.push(make_tuple(v.first, v.second, u));
    }
  }
  return mst;
}
