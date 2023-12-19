/*
  <#pragma unroll N> basic tests
  taken from unroll-1.c
 */

/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-cunrolli-details -fdump-rtl-loop2_unroll-details" } */

extern void bar (int);

int j;

void test (void)
{
  #pragma unroll 8
  for (unsigned long i = 1; i <= 8; ++i)
    bar(i);
  /* { dg-final { scan-tree-dump "16:.*: loop with 8 iterations completely unrolled" "cunrolli" } } */

  #pragma unroll 8
  for (unsigned long i = 1; i <= 7; ++i)
    bar(i);
  /* { dg-final { scan-tree-dump "21:.*: loop with 7 iterations completely unrolled" "cunrolli" } } */

  #pragma unroll 8
  for (unsigned long i = 1; i <= 15; ++i)
    bar(i);
  /* { dg-final { scan-rtl-dump "26:.*: optimized: loop unrolled 7 times" "loop2_unroll" } } */

  #pragma unroll 8
  for (unsigned long i = 1; i <= j; ++i)
    bar(i);
  /* { dg-final { scan-rtl-dump "31:.*: optimized: loop unrolled 7 times" "loop2_unroll" } } */

  #pragma unroll 7
  for (unsigned long i = 1; i <= j; ++i)
    bar(i);
  /* { dg-final { scan-rtl-dump "36:.*: optimized: loop unrolled 3 times" "loop2_unroll" } } */

  unsigned long i = 0;
  #pragma unroll 3
  do {
    bar(i);
  } while (++i < 9);
  /* { dg-final { scan-rtl-dump "4\[24\]:.*: optimized: loop unrolled 2 times" "loop2_unroll" } } */
}
