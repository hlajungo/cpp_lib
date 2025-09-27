#include <bits/stdc++.h>
using namespace std;
#include "graph.hpp"

int
main ()
{
  ios_base::sync_with_stdio (false);
  cin.tie (NULL);
  Adj_list_w<int, int> lst (5);
  lst.add_e(1, 3, 4);
  lst.add_e(1, 5, 4);

  Adj_mat_w<int, int> mat(5);
  mat.add_e(1, 2, 3);
  mat.add_e(1, 3, 4);

  Adj_list_w<int, int> ret;
  ret.g = lst.mst_prim(3);
  cout << "ret\n";
  ret.print();
  cout << "\n";
}
