#include <bits/stdc++.h>

/*
 * Segment tree 提供數組的區段的性質。
 * 例如： v = {1,2,3}, 以性質 max 來說， max(v) = 3。
 * 類似的性質有 min / max / sum / gcd / lcm / xor / 區間計數。
 * 取得性質的效率是 O(log n)，正常是用 O(n)。
 *
 * 對於數組的區段的更新，使用 lazy propagation 能夠緩存 "計算"，讓更新變 O(log
 * n)，正常是 O(n)。
 * 原理是通過父節點維護正確的區間性質，而子節點僅緩存計算而不遞迴，直到使用該節點才更新。
 *
 * 基本上是空間換時間，空間從 n 變為 4n 或 8n(lazy propagation)。
 *
 * 0 = 沒被移除
 * 1 = 移除
 * 區段和 = 區段移除的數量
 * 把任何在意的屬性抽象成 bool +
 * 線段樹區段和，就能快速查詢區間上有多少元素持有屬性了。
 *
 * 節點使用 node 代表他在數組樹的索引，節點維護 l,r 代表他的區段，節點維護
 * tree[node] 代表他的資料。
 * node, l, r 是遞迴變量。
 */

class St_help
{
protected:
  inline bool
  is_intersect (auto&& l1, auto&& r1, auto&& l2, auto&& r2)
  {
    return r2 >= l1 && r1 >= l2;
  }
  inline bool
  is_include (auto&& l1, auto&& r1, auto&& l2, auto&& r2)
  {
    return l1 >= l2 && r2 >= r1;
  }

  inline int
  left (int& node)
  {
    return node * 2;
  }
  inline int
  right (int node)
  {
    return node * 2 + 1;
  }
  inline bool
  is_leaf (int& l, int& r)
  {
    return l == r;
  }
};

/*
 * @brief 1-index segment tree for interval add and query.
 *
 * Using lazy propagation for update, so complexity O(log n).
 */
class Max_st : St_help
{
public:
  int n;
  std::vector<int> tree;
  std::vector<int> lazy;

public:
  // empty construct
  Max_st (auto&& n) : n (n), tree (4 * n, 0), lazy (4 * n, 0) {}
  Max_st (std::vector<int>& v)
      : n (v.size () - 1), tree (4 * n, 0), lazy (4 * n, 0)
  {
    build (v, 1, 0, n);
  }

  void
  cout ()
  {
    for (int i = 1; i < (int)tree.size (); i++)
    {
      if (tree[i] != 0)
        std::cout << tree[i] << " ";
    }
    std::cout << "\n";
  }

  void
  add_interval (auto&& rl, auto&& rr, auto&& val)
  {
    if (rr < rl)
    {
      std::cout << "error: rr <  rl\n";
      return;
    }
    if (n < rr)
    {
      std::cout << "error: rr out of range\n";
      return;
    }
    update (1, 0, n, rl, rr, val);
  }

  int
  query (int ql, int qr)
  {
    return query (1, 0, n, ql, qr);
  }

  void
  build (std::vector<int>& v, auto&& node, auto&& l, auto&& r)
  {
    // std::cout << "Build " << l << " to " << r << "\n";
    if (is_leaf (l, r))
    {
      // std::cout << "Set node " << node << " = v[" << l << "]\n";
      tree[node] = v[l];
      return;
    }
    build (v, left (node), l, (l + r) / 2);
    build (v, right (node), (l + r) / 2 + 1, r);

    // After child finished, update parent
    tree[node] = std::max (tree[left (node)], tree[right (node)]);
  }

private:
  void
  try_update_lazy (int node, int l, int r)
  {
    if (lazy[node] != 0)
    {
      tree[node] += lazy[node];
      // Has leaf
      if (!is_leaf (l, r))
      {
        lazy[left (node)] += lazy[node];
        lazy[right (node)] += lazy[node];
      }
      lazy[node] = 0;
    }
  }

  /**
   * @brief 區間更新 (Lazy Propagation)
   *
   * 對區間 [i, j] 內的所有元素加上 val。
   * 使用 lazy propagation 技術來避免重複下推，保證 O(log n) 更新時間(better
   * than O(n))。
   *
   * @param node Node ifx
   * @param l Node left endpoint
   * @param r Node right endpoint
   * @param rl Left endpoint of update interval
   * @param rr Right endpoint of update interval
   * @param val 欲加上的值
   *
   * 演算法流程：
   * 1. 若當前節點有 lazy 標記，先將其套用到 tree[node]，
   *    並將標記下推到子節點，再清空自己的 lazy。
   * 2. 若當前區間 [l,r] 與更新區間 [i,j] 無交集，直接返回。
   * 3. 若當前區間 [l,r] 完全包含於 [i,j]，更新 tree[node]，
   *    並將更新值存入子節點的 lazy 標記，返回。
   * 4. 否則，表示部分重疊，遞迴更新左右子區間。
   */
  void
  add_interval (auto node, auto l, auto r, auto&& rl, auto&& rr, auto&& val)
  {
    std::cout << "At node " << node << "\n";
    try_update_lazy (node, l, r);

    if (!is_intersect (l, r, rl, rr))
      return;
    if (is_include (l, r, rl, rr))
    {
      tree[node] += val;
      // Has leaf
      if (l != r)
      {
        lazy[node * 2] += val;
        lazy[node * 2 + 1] += val;
      }
      return;
    }
    update (left (node), l, (l + r) / 2, rl, rr, val);
    update (right (node), (l + r) / 2 + 1, r, rl, rr, val);
  }

  int
  query (int node, int l, int r, int ql, int qr)
  {
    // std::cout << "At node " << node << "\n";
    if (!is_intersect (l, r, ql, qr))
      return -INT_MAX;
    try_update_lazy (node, l, r);
    if (is_include (l, r, ql, qr))
      return tree[node];
    int ql_num = query (left (node), l, (l + r) / 2, ql, qr);
    int qr_num = query (right (node), (l + r) / 2 + 1, r, ql, qr);
    return std::max (ql_num, qr_num);
  }
};

/*
 * @brief 1-index segment tree
 */
class Sum_st : St_help
{
private:
  int n;
  std::vector<int> tree;

  void
  build (std::vector<int>& v, int node, int l, int r)
  {
    if (is_leaf (l, r))
    {
      tree[node] = v[l];
      return;
    }
    build (v, left (node), l, (l + r) / 2);
    build (v, right (node), (l + r) / 2 + 1, r);
  }

  /*
   * @brief update 的內部遞迴實現。
   */
  void
  add_node (const int& idx, const int& val, int node, int l, int r)
  {
    if (is_leaf (l, r))
    {
      tree[node] += val;
      return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid)
      // Go to eft child
      add_node (idx, val, left (node), l, mid);
    else
      // Go to right child
      add_node (idx, val, right (node), mid + 1, r);

    tree[node] = tree[left (node)] + tree[right (node)];
  }
  /*
   * @param ql Query left
   * @param qr Query right
   * @param node Node idx
   * @param l Node left
   * @param r Node right
   */
  int
  query (int ql, int qr, int node, int l, int r)
  {
    if (!is_intersect (l, r, ql, qr))
      return 0;
    if (is_include (l, r, ql, qr))
      return tree[node];
    int mid = (l + r) / 2;
    // Partial include, let left child and right child answer the question
    return query (ql, qr, left (node), l, mid)
           + query (ql, qr, right (node), mid + 1, r);
  }

public:
  // empty construct
  Sum_st (auto&& n) : n (n), tree (4 * n, 0) {}
  Sum_st (std::vector<int>& v)
  {
    build (v, 1, 0, v.size () - 1);
  }

  /*
   * @brief  更新一個 leaf `idx` = `val` 和 `idx` 的 dfs 線。
   */
  void
  add_node (const int& idx, const int& val)
  {
    add_node (idx, val, 1, 0, n - 1);
  }

  /*
   * @brief Query the max value in segment [l, r]
   */
  int
  query (int ql, int qr)
  {
    return query (ql, qr, 1, 0, n - 1);
  }
};

int
main ()
{
  std::ios_base::sync_with_stdio (false);
  std::cin.tie (NULL);
  int n;
  std::cin >> n;
  std::vector<int> v (n);
  for (int i = 0; i < n; ++i)
  {
    std::cin >> v[i];
  }
  Max_st st (v);
  std::cin >> n;
  for (int i = 0; i < n; ++i)
  {
    int a, b;
    std::cin >> a >> b;
    if (a > b)
    {
      std::swap (a, b);
    }
    std::cout << st.query (a - 1, b - 1) << "\n";
  }
}
