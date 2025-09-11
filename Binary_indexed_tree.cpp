#include <iostream>
#include <vector>
using namespace std;

/*
 * BIT(Binary indexed tree) 又名 Fenwick Tree，由 蘇聯人 Boris Ryabko
 * 發明，Fenwick 推廣。
 *
 * BIT 是數組 tree，它偷了 binary 的抽象概念來構件邏輯樹。
 * 他是加速器，用途之一是加速計算前綴合。
 *
 * Parent 規則
 * node `idx` flip LSB = parent idx
 * 例如：idx 1000(8) 的 parent = 0000
 *
 * 這也暗示了最大遞迴 child 數量是 2^{LSB 右邊的 0 數量}。
 * 例如: idx 1000(8) 1 右邊有三個 0, 它最多能有 2^3 個遞迴 child。
 *
 * Interval Rule
 * node `idx` 維護區間 [idx - LSB[idx], idx-1]
 * 例如: 7(111) 維護區間 [111-LSB(111),111-1] = [111-1,110] = [110,110] = [6,6]
 * 例如: 6(110) 維護區間 [100,101] = [4,5]
 *
 * 即使不同 BIT 的儲存值不同，但 node 維護的區間會是相同的。
 *
 * Query Rule
 * Query [0,idx], get node `idx+1`and add to parent until root
 * 例如: Query [0,5] = node `6`([4,5]) + node `4`([0,3])
 *
 * Get parent Rule
 * idx -= (idx & -idx);
 * 例如: 1000 -= (1000 & 1000) = 0000, 0000 是 1000 的 parent
 *
 * Get next update rule
 * idx += -idx & idx
 * 例如:
 * 0001(1[0,0])
 * 0001 += 1111 & 0001 = 0001 + 0001 = 0011(2[0,1])
 * 0010 += 1110 & 0010 = 0010 + 0010 = 0100(4[0,3])
 * 0100 += 1100 & 0100 = 0100 + 0100 = 1000(8[0,7])
 *
 * 你可以觀察到，這公式使你來到更大但包含你的區間。
 *
 * 0011(3[2,2])
 * 0011 += 1101 & 0011 = 0011 + 0001 = 0100(4[0,3])
 * 然後又是 4 的更新老路 8, 16,...
 *
 * BIT 不需要指針，它偷了 binary 性質，達成
 * "移動到包含自己的更大區間"，"移動到父親" 兩操作。
 *
 * 所以除了 prefix sum, 它也能算 max, min, 頻率表。
 * 他的優點是空間只用 O(n)，而 st 需要 O(4n)，缺點是只能做 prefix 型運算，st
 * 更通用。
 *
 * ref:
 * 印度老哥
 * https://www.youtube.com/watch?v=CWDQJGaN1gY
 *
 * 圖片好看
 * https://hackmd.io/@wiwiho/cp-note/%2F%40wiwiho%2FCPN-binary-indexed-tree
 */

/*
 * @brief Binary indexed tree
 * 區間和，單點更新
 */
class Sum_BIT
{
private:
  int n;                  // tree size
  vector<long long> tree; // 1-based array tree

public:
  Sum_BIT (int n) : n (n), tree (n + 1, 0) {}

  /*
   * @brief
   * @complexity O(n log n)
   */
  Sum_BIT (const vector<int>& arr)
  {
    n = arr.size ();
    tree.assign (n + 1, 0);
    for (int i = 0; i < n; i++)
    {
      node_add (i, arr[i]);
    }
  }

  /*
   * @brief node `idx` += val
   * @compelxity O(log n)
   */
  void
  node_add (int i, long long val)
  {
    i++; // 0-based -> 1-based
    while (i <= n)
    {
      tree[i] += val;
      i += (i & -i); // Get next(會包含此區間，但範圍更大，來自binary性質)
    }
  }

  /*
   * @brief node `l` to `r` += `val`
   */
  void
  range_node_add (int l, int r, int val)
  {
    node_add (l, val);
    if (r + 1 <= n)
      node_add (r + 1, -val);
  }

  /*
   * @brief Query prefix sum
   * @complexity O(log n)
   */
  long long
  query (int i) const
  {
    ++i; // from 0-based to 1-based
    long long res = 0;
    while (i > 0)
    {
      res += tree[i];
      i -= (i & -i); // Get father
    }
    return res;
  }

  /*
   * @brief Query range prefix sum
   * @complexity O(log n)
   */
  long long
  range_query (int l, int r) const
  {
    return query (r) - query (l - 1);
  }
};

int
main ()
{
  vector<int> arr = { 3, 2, -1, 6, 5, 4, -3, 3, 7, 2, 3 };
  Sum_BIT bit (arr);

  std::cout << bit.query (3) << "\n";          // 10
  std::cout << bit.range_query (2, 5) << "\n"; // 14
  bit.node_add (2, 2);                         // A[2]+=2
  std::cout << bit.query (3) << "\n";          // 12

  return 0;
}
