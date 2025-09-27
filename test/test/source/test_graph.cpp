#include "../../../alluneed.h"
#include "../../../graph/graph.hpp"
#include <doctest/doctest.h>

TEST_CASE ("prim")
{
  Adj_list_w<int, int> g (5);
  g.add_e (1, 3, 4);
  g.add_e (1, 5, 4);
  auto min_w = g.mst_prim_w (4);
  CHECK (min_w == 2);

  auto min_g = g.mst_prim (4);
  decltype (g.g) ans_g = { { 3, { { 1, 4 } } },
                           { 4, { { 1, 3 }, { 1, 5 } } },
                           { 5, { { 1, 4 } } } };

  CHECK(ans_g == min_g);
}
