#include "alluneed.h"
template <typename T>
bool
is_prime (T n)
{
  if (n < 2)
    return 0;
  if (n % 2 == 0)
    return n == 2;
  if (n % 3 == 0)
    return n == 3;
  for (T i = 5; i * i <= n; i += 6)
    if (n % i == 0 || n % (i + 2) == 0)
      return 0;
  return true;
}
/*Compile-time is of Eratosthenes, O(n) space O(1) time*/
template <size_t N>
bool is[N + 1];
template <size_t N>
struct Prime
{
  constexpr
  Prime ()
  {
    is<N>[0] = is<N>[1] = false;
    for (size_t i = 2; i <= N; i++)
      is<N>[i] = true;
    for (size_t i = 2; i*i  <= N; i ++)
      if (is<N>[i])
        for (size_t j = i * i; j <= N; j+=i)
          is<N>[j] = false;
  }
};

