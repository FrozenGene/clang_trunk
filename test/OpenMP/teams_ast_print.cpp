// RUN: %clang_cc1 -verify -fopenmp -ast-print %s | FileCheck %s
// RUN: %clang_cc1 -fopenmp -x c++ -std=c++11 -emit-pch -o %t %s
// RUN: %clang_cc1 -fopenmp -std=c++11 -include-pch %t -fsyntax-only -verify %s -ast-print | FileCheck %s
// expected-no-diagnostics

#ifndef HEADER
#define HEADER

void foo() {}

int main (int argc, char **argv) {
  int b = argc, c, d, e, f, g;
  static int a;
// CHECK: static int a;
#pragma omp target
#pragma omp teams
// CHECK:      #pragma omp target
// CHECK-NEXT: #pragma omp teams
  a=2;
// CHECK-NEXT: a = 2;
#pragma omp target
#pragma omp teams num_teams(a), thread_limit(c), default(none), private(argc,b),firstprivate(argv, c),shared(d,f),reduction(+:e) reduction(min : g)
// CHECK:      #pragma omp target
// CHECK-NEXT: #pragma omp teams num_teams(a) thread_limit(c) default(none) private(argc,b) firstprivate(argv,c) shared(d,f) reduction(+: e) reduction(min: g)
  foo();
// CHECK-NEXT: foo();
  return (0);
}

#endif
