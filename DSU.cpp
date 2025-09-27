#include "alluneed.h"
/* @brief Disjoint set union with merge by rank, path compression */
struct DSU {
  vector<int> p;
  vector<int> r; // [i] = height of tree i
  DSU(int n): p(n), r(n) { rep(i, n) p[i]= i; }
  /* @brief Get root of x and compress path
   */
  int find(int x) {
    if(p[x] != x) p[x]= find(p[x]);
    return p[x]; }
  /* @brief Unite root of x and root of y by r
   */
  bool unite(int x, int y) {
    int root_x= find(x); int root_y= find(y);
    if(root_x == root_y) return 0;
    if(r[root_x] < r[root_y]) p[root_x]= root_y;
    else if(r[root_x] > r[root_y]) p[root_y]= root_x;
    else {
      p[root_y]= root_x;
      r[root_x]++; }
    return 1; }
  /* @brief Check x and y in same set
   */
  bool same(int x, int y) { return find(x) == find(y); }
};
int main() {
  DSU dsu(5); // 0,1,2,3,4
  dsu.unite(0, 1);
  dsu.unite(1, 2);
  cout << dsu.same(0, 2) << "\n"; // 1 (true)
  cout << dsu.same(0, 3) << "\n"; // 0 (false)
  dsu.unite(3, 4);
  dsu.unite(2, 4);
  cout << dsu.same(0, 4) << "\n"; // 1 (true)
}
