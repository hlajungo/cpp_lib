#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include <doctest.h>

#include <doctest/doctest.h>
#include <hello.h>

//#include <iostream>
//#include <sstream>
//#include <streambuf>

#include <chrono>

#include "../../../Bn.cpp"
#include "../../../Dlst.cpp"
#include "../../../St.cpp"
#include "../../../alluneed.h"
#include "../../../heuristic/AStar_obstacle_grid.cpp"

auto get_cout = [] (auto func)
{
  ostringstream oss;
  streambuf* old_buf = cout.rdbuf (oss.rdbuf ());
  func ();
  cout.rdbuf (old_buf);
  return oss;
};

auto measure_ms = [] (auto func) -> size_t
{
  auto start = chrono::high_resolution_clock::now ();
  func ();
  auto end = chrono::high_resolution_clock::now ();
  return chrono::duration_cast<chrono::milliseconds> (end - start).count ();
};

TEST_CASE ("Bn")
{
  Bn n1 ("-10");
  Bn n2 ("-10");

  CHECK (n1.add (n2).n == "-20");
  CHECK (n1.sub (n2).n == "0");
  CHECK (n1.mul (n2).n == "100");
  CHECK (n1.div (n2).n == "1");

  Bn n3 ("987654321098765432109876543210987654321");
  Bn n4 ("1234567890123456789012345678901234567890");

  CHECK (n3.add (n4).n == "2222222211222222221122222222112222222211");
  CHECK (n3.sub (n4).n == "-246913569024691356902469135690246913569");
  CHECK(n3.mul(n4).n == "1219326311370217952261850327338667885944871208653362292333223746380111126352690");
  CHECK (n3.div (n4).n == "0");
}

TEST_CASE ("St")
{
  vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  St st (v);
  CHECK (st.get (0, SZ (v) - 1) == 9);
  CHECK (get_cout ([&] { st.print (); }).str () == "0 1 2 3 4 5 6 7 8 9\n");
  // Add 100 for all
  st.add (0, SZ (v) - 1, 100);
  CHECK (get_cout ([&] { st.print (); }).str ()
         == "100 101 102 103 104 105 106 107 108 109\n");
  // Add -100 for [5,end]
  st.add (5, SZ (v) - 1, -100);
  CHECK (get_cout ([&] { st.print (); }).str ()
         == "100 101 102 103 104 5 6 7 8 9\n");
  CHECK (st.get (4, 5) == 104);
}

TEST_CASE ("Dlst")
{
  Dlst lst;
  CHECK (get_cout ([&] { lst.print (); }).str () == "");
  lst.ins_pos (-999, Dlst::V (-1));
  lst.ins_pos (10086, 1);
  CHECK (get_cout ([&] { lst.print (); }).str () == "-1 1\n");
  lst.ins_pos (1, 2);
  CHECK (get_cout ([&] { lst.print (); }).str () == "-1 2 1\n");
  lst.ins_pos (2, 3);
  CHECK (get_cout ([&] { lst.print (); }).str () == "-1 2 3 1\n");
  lst.rm_pos (2);
  CHECK (get_cout ([&] { lst.print (); }).str () == "-1 2 1\n");
  lst.rm_pos (10086);
  CHECK (get_cout ([&] { lst.print (); }).str () == "-1 2\n");
  lst.rm_pos (-999);
  CHECK (get_cout ([&] { lst.print (); }).str () == "2\n");
}

TEST_CASE ("AStar_obstacle_grid")
{
  vector<pii> ans = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 2 }, { 2, 2 },
                      { 2, 3 }, { 2, 4 }, { 3, 4 }, { 4, 4 } };
  vvi grid = { { 0, 0, 0, 0, 0 },
               { 1, 1, 0, 1, 0 },
               { 0, 0, 0, 0, 0 },
               { 0, 1, 1, 1, 0 },
               { 0, 0, 0, 0, 0 } };
  // 右下到左上
  AStar astar (grid, { 0, 0 }, { 4, 4 });
  auto path = astar.search ();
  if (!path.empty ())
  {
    rep (i, SZ (path))
    {
      CHECK (path[i] == ans[i]);
    }
    cout << "\n";
  }
  else
  {
    FAIL ("Invaild Path");
  }
}

#include "../../../prime2.cpp"

/*
 * @code_source https://gist.github.com/rongjiecomputer/d52f34d27a21b8c9c9e82ca85b806640
 * 第一次接觸"模板變量"，不像原本的 "concept+type"，稱為 "NTTP, Non-Type Template Parameter"
 * "模板變量+constexpr" 可以完成複雜 constexpr 計算，貌似是唯一的方式。
 */
bool ans_prime[N] = { false };
TEST_CASE ("Prime")
{
  auto duration1 = measure_ms (
      [&] ()
      {
        for (size_t i = 0; i <= N; ++i)
          ans_prime[i] = is_prime (i);
      });
  cerr << "Create ans_prime use = " << duration1 << "\n";

  auto duration2 = measure_ms ([&] () { Prime<N> prime; });

  cerr << "Create Prime use = " << duration2 << "\n";

  for (size_t i = 0; i <= N; ++i)
    CHECK (prime[i] == ans_prime[i]);
}
