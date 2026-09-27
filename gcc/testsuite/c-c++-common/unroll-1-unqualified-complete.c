/*
  <#pragma unroll> basic tests
  taken from unroll-1.c
 */

/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-cunrolli-details -fdump-rtl-loop2_unroll-details" } */

extern void bar (int);

int j;

void test (void)
{
  #pragma unroll
  for (unsigned long i = 1; i <= 8; ++i)
    bar(i);
  /* { dg-final { scan-tree-dump "16:.*: loop with 8 iterations completely unrolled" "cunrolli" } } */

  #pragma unroll
  for (unsigned long i = 1; i <= 7; ++i)
    bar(i);
  /* { dg-final { scan-tree-dump "21:.*: loop with 7 iterations completely unrolled" "cunrolli" } } */
}
