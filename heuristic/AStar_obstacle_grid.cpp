#include "../alluneed.h"
/*
 * AStar obstacle manhattan grid path searching
 * Support search
 */
struct AStar {
  struct Node {
    int x, y, g, h, f;
    Node* p;
    Node(int x, int y, int g, int h, Node* p= NUL): x(x), y(y), g(g), h(h), f(g + h), p(p) {}
  };
  struct Cmp_min {
    bool operator()(Node* a, Node* b) { return a->f > b->f; }
  };
  vvi grid;
  int n, m;
  pii s, e;
  int heuristic(int x, int y) { return abs(x - e.first) + abs(y - e.second); }
  vector<pii> dirs= { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
  AStar(vvi grid, pii s, pii e): grid(grid), n(SZ(grid)), m(SZ(grid[0])), s(s), e(e) {}
  vector<pii> search() {
    priority_queue<Node*, vector<Node*>, Cmp_min> cand;
    vvi g_score(n, vi(m, INT_MAX));
    Node* sNode= new Node(s.first, s.second, 0, heuristic(s.first, s.second));
    cand.push(sNode);
    g_score[s.first][s.second]= 0;
    while(!cand.empty()) {
      Node* cur= cand.top();
      cand.pop();
      // cur == e
      if(cur->x == e.first && cur->y == e.second) {
        vector<pii> path;
        while(cur) {
          path.pb({ cur->x, cur->y });
          cur= cur->p;
        }
        reverse(path.begin(), path.end());
        return path;
      }
      // to neighbor
      for(auto [dx, dy]: dirs) {
        int nx= cur->x + dx, ny= cur->y + dy;
        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if(grid[nx][ny] == 1) continue;
        int ng= cur->g + 1;
        if(ng < g_score[nx][ny]) {
          Node* k= new Node(nx, ny, ng, heuristic(nx, ny), cur);
          cand.push(k);
          g_score[nx][ny]= ng;
        }
      }
    }
    return {};
  }
};

