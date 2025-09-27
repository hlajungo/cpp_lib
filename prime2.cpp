#include "alluneed.h"
template<typename T> bool is_prime(T n) {
  if(n < 2) return 0;
  if(n % 2 == 0) return n == 2;
  if(n % 3 == 0) return n == 3;
  for(T i= 5; i * i <= n; i+= 6)
    if(n % i == 0 || n % (i + 2) == 0) return 0;
  return true; }
/*Compile-time sieve of Eratosthenes, O(n) space O(1) time*/
constexpr size_t N= 1e7;
bool prime[N];
template<size_t N> struct Prime {
  constexpr Prime() {
    prime[0]= prime[1]= false;
    for(size_t i= 2; i <= N; i++) prime[i]= true;
    for(size_t i= 2; i * i <= N; i++)
      if(prime[i])
        for(size_t j= i * i; j <= N; j+= i) prime[j]= false; }};
