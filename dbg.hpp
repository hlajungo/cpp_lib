#pragma once
#include <cassert>
#include <iostream>
#include <vector>

#ifdef DEBUG
#define DOUT std::cout
#else
#define DOUT 0 && std::cout
#endif

template <typename T>
void
DOUT_array_1d (std::vector<T>& v)
{
  for (const auto& i : v)
  {
    DOUT << i << ' ';
  }
  DOUT << '\n';
}

template <typename T, typename Func>
void
DOUT_array_1d (const std::vector<T>& v, Func f)
{
  for (const auto& i : v)
  {
    f (i);
  }
  DOUT << '\n';
}

template <typename T>
void
DOUT_array_2d (std::vector<std::vector<T> >& vec)
{
  for (const auto& a_1d : vec)
  {
    for (const auto& v : a_1d)
    {
      DOUT << v << ' ';
    }
  }
  DOUT << '\n';
}

template <typename T>
void
DOUT_array_3d (std::vector<std::vector<std::vector<T> > >& vec)
{
  for (const auto& a_2d : vec)
  {
    for (const auto& a_1d : a_2d)
    {
      for (const auto& v : a_1d)
      {
        DOUT << v << ' ';
      }
    }
  }
  DOUT << '\n';
}

template <typename T>
void
DOUT_array_1d_pair (std::vector<T>& v)
{
  for (auto& i : v)
  {
    DOUT << i.first << ' ' << i.second << '\n';
  }
}

// 用來展開 tuple 的 helper function
template <typename Tuple, size_t... Is>
void
DOUT_tuple_impl (const Tuple& t, std::index_sequence<Is...>)
{
  ((DOUT << (Is == 0 ? "" : " ") << std::get<Is> (t)), ...);
  DOUT << '\n';
}

// 萬能轉發接口：列印任意型別的 tuple
template <typename... Args>
void
DOUT_tuple (const std::tuple<Args...>& t)
{
  DOUT_tuple_impl (t, std::index_sequence_for<Args...>{});
}

// 印出 vector<tuple<...>> 的函式
template <typename... Args>
void
DOUT_array_1d_tuple (const std::vector<std::tuple<Args...> >& vec)
{
  for (const auto& t : vec)
  {
    DOUT_tuple (t);
  }
}
