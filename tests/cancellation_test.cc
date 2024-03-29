#include <algorithm>
#include <numeric>
#include <vector>
#include "sum.h"
#include "gtest/gtest.h"

vector<double> get_values() {
  // {1, 1, 1, ..., 1e30, -1e30}
  const int size = 20;
  vector<double> d(size);
  fill(d.begin(), d.end() - 2, 1);
  *(d.end() - 2) = 1e30;
  *(d.end() - 1) = -1e30;
  return d;
}

TEST(Cancellation, Accumulate) {
  auto v = get_values();
  auto res = accumulate(v.begin(), v.end(), 0.0);
  ASSERT_EQ(res, 0.0);  // Incorrect
}

TEST(Cancellation, CondensedSummation) {
  auto v = get_values();
  auto res = condensed_summation(v);
  ASSERT_EQ(res, 0.0);  // Incorrect
}

TEST(Cancellation, ModifiedDeflation) {
  auto v = get_values();
  auto res = modified_deflation(v);
  ASSERT_EQ(res, v.size() - 2);  // Correct
}
