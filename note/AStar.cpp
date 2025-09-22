#include <bits/stdc++.h>
using namespace std;
/*
 * AStar 演算法
 * Graph-based path searching algorithm, it depend on setting heuristic h(x)
 * which require consistent and admissible
 * Consistent 代表啟發值h(x) 優於等於實際成本h*(x)。
 * 它可能猜的很好，但現實很爛，但它不能猜得很爛，但現實很好。
 * 想像和終點間有一堵牆，啟發值 h(x) 告訴你就差 1 但 h*(x) 還很遠。
 * Admissible 代表邊移動優於等於起點啟發值-終點啟發值
 * 啟發行為不能超過邊移動，否則像是憑空創造而非猜測，啟發行為比實際能產出的量還多。
 *
 * 無權重+有障礙+四向圖(曼哈頓距離) 適合 Astar
 */
struct Node
{
  int x, y;    // 座標
  int g, h, f; // 代價
  Node* parent;
  Node (int x, int y, int g, int h, Node* parent = nullptr)
      : x (x), y (y), g (g), h (h), f (g + h), parent (parent)
  {
  }
};
// min heap，f 值越小優先級越高
struct Compare
{
  bool
  operator() (Node* a, Node* b)
  {
    return a->f > b->f;
  }
};
class AStar
{
private:
  vector<vector<int> > grid; // 地圖
  int n, m;                  // 尺寸
  pair<int, int> start, goal;
  // 曼哈頓距離
  int
  heuristic (int x, int y)
  {
    return abs (x - goal.first) + abs (y - goal.second);
  }
  // [+上-下][+右-左]
  vector<pair<int, int> > dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

public:
  AStar (vector<vector<int> > grid, pair<int, int> start, pair<int, int> goal)
      : grid (grid), n (grid.size ()), m (grid[0].size ()), start (start),
        goal (goal)
  {
  }
  vector<pair<int, int> >
  search ()
  {
    // open = Node pq, visited = g 分數表
    priority_queue<Node*, vector<Node*>, Compare> open;
    vector<vector<int> > visited (n, vector<int> (m, INT_MAX));
    Node* startNode = new Node (
        start.first, start.second, 0, heuristic (start.first, start.second));
    open.push (startNode);
    visited[start.first][start.second] = 0;
    while (!open.empty ())
    {
      Node* cur = open.top ();
      open.pop ();
      // cur == goal
      if (cur->x == goal.first && cur->y == goal.second)
      {
        vector<pair<int, int> > path;
        while (cur)
        {
          path.push_back ({ cur->x, cur->y });
          cur = cur->parent;
        }
        reverse (path.begin (), path.end ());
        return path;
      }
      // 展開鄰居
      for (auto [dx, dy] : dirs)
      {
        int nx = cur->x + dx, ny = cur->y + dy;
        if (nx < 0 || nx >= n || ny < 0 || ny >= m)
          continue;
        if (grid[nx][ny] == 1)
          continue; // 障礙物
        int newG = cur->g + 1;
        if (newG < visited[nx][ny])
        {
          Node* next = new Node (nx, ny, newG, heuristic (nx, ny), cur);
          open.push (next);
          visited[nx][ny] = newG;
        }
      }
    }
    return {}; // 無路徑
  }
};
int
main ()
{
  vector<vector<int> > grid = { { 0, 0, 0, 0, 0 },
                                { 1, 1, 0, 1, 0 },
                                { 0, 0, 0, 0, 0 },
                                { 0, 1, 1, 1, 0 },
                                { 0, 0, 0, 0, 0 } };
  AStar astar (grid, { 0, 0 }, { 4, 4 });
  auto path = astar.search ();
  if (!path.empty ())
  {
    cout << "找到路徑:\n";
    for (auto [x, y] : path)
      cout << "(" << x << "," << y << ") ";
    cout << endl;
  }
  else
  {
    cout << "無法到達目標\n";
  }
}
