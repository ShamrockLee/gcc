/*
  Unroll factor and trip count limit test

  Ensure that #pragma GCC unroll <USHRT_MAX - 1>
  completely unrolls a for-loop with trip count 0xFFFE
*/
/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-cunrolli-details -fdump-rtl-loop2_unroll-details" } */

/*
  It takes ~5min to run on an Intel N200 processor.
  Request 20min in case it runs slow.
*/
/* { dg-timeout-factor 4 } */
/* { dg-require-effective-target run_expensive_tests } */

#define __stringify_helper(x) #x
#define __stringify(x) __stringify_helper(x)

#define USHRT_MAX_MINUS_ONE (__SHRT_MAX__ << 1)

extern void bar (int);

int j;

void test (void)
{
  /*
    USHRT_MAX == __SHRT_MAX__ * 2 + 1
    USHRT_MAX - 1 >= 0xFFFE
    0xFFFE == 65534
  */
  _Pragma (__stringify (GCC unroll USHRT_MAX_MINUS_ONE))
  for (unsigned long i = 1; i <= 65534; ++i)
    bar(i);
  /* { dg-final { scan-tree-dump "34:.*: loop with 65534 iterations completely unrolled" "cunrolli" } } */
}
