/*
  <#pragma unroll> trip count limit test
  Ensure that "#pragma unroll" completely unrolls a loop with trip count 0xFFFE
*/
/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-cunrolli-details -fdump-rtl-loop2_unroll-details" } */

/*
  It takes ~5min to run on an Intel N200 processor.
  Request 4x time in case it runs slow.
*/
/* { dg-timeout-factor 4 } */
/* { dg-require-effective-target run_expensive_tests } */

extern void bar (int);

int j;

void test (void)
{
  /*
    USHRT_MAX - 1 >= 0xFFFE
    0xFFFE == 65534
  */
  #pragma unroll
  for (unsigned long i = 1; i <= 0xFFFE; ++i)
    bar(i);
  /* { dg-final { scan-tree-dump "26:.*: loop with 65534 iterations completely unrolled" "cunrolli" } } */
}
