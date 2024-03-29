#ifndef SUM_H_
#define SUM_H_

#include <cmath>
#include <vector>

using std::vector;

//========================================================================
// The condensed summation algorithm of Kahan.  Avoids common round-off
// errors in computing the sum of a sequence of numbers.  It works well
// for most cases, but can fail badly when there is cancellation.  The
// slower modified_deflation algorithm below does better in those cases.

template <class T>
T condensed_summation(const vector<T>& v) {
  T a, b, sum = 0, error = 0;
  for (const auto i : v) {
    a = sum;
    b = i + error;
    sum = a + b;
    error = (a - sum) + b;
  }
  return sum;
}

//========================================================================
// The modified deflation algorithm of Anderson.  It is reasonably fast
// and should give the correct result when possible. It is difficult
// to do better without increasing the precision of the variables.  The
// portion of the algorithm that handles potentially infinite loops has
// been modified as the original version did not always work in my tests.
// I believe the failures were due to errors in g++ optimizations and
// also believe that my code still has an error.

template <class T>
T modified_deflation(const vector<T>& v) {
  if (v.size() < 3) {
    return condensed_summation(v);
  }

  // Set up several vectors with reasonable capacities
  vector<T> vp, vn, e;
  vp.reserve(v.size());
  vn.reserve(v.size());
  e.reserve(v.size());

  // Initialize vectors of negative and positive elements of v
  for (const auto i : v) {
    if (i < 0) {
      vn.push_back(i);
    } else if (i > 0) {
      vp.push_back(i);
    }
  }

  T a, b, sum, error, sp, sn;
  bool well_conditioned = false;
  while (!well_conditioned) {
    // Deflate the last elements of vp and vn.
    while (!vp.empty() && !vn.empty()) {
      a = vp.back(); vp.pop_back();
      b = vn.back(); vn.pop_back();
      sum = a + b;
      error = (a - sum) + b;
      if (sum == a) {  // |a| >> |b|
        T tmp1 = a / 2.0;
        T tmp2 = a - tmp1;
        vp.push_back(tmp2);
        vp.push_back(tmp1);
        vn.push_back(b);
      } else if (sum == b) {  // |b| >> |a|
        T tmp1 = b / 2.0;
        T tmp2 = b - tmp1;
        vp.push_back(a);
        vn.push_back(tmp2);
        vn.push_back(tmp1);
      } else {
        if (sum < 0) {
          vn.push_back(sum);
        } else if (sum > 0) {
          vp.push_back(sum);
        }
        if (error != 0) {
          e.push_back(error);
        }
      }
    }

    // Put the error terms back in the vp and vn arrays.
    for (const auto i : e) {
      if (i < 0) {
        vn.push_back(i);
      } else if (i > 0) {
        vp.push_back(i);
      }
    }
    e.clear();

    // Check that the sums in vp and vn are well-condtioned.
    sp = condensed_summation(vp);
    sn = condensed_summation(vn);
    well_conditioned = (fabs((sp + sn) / (sp - sn)) == 1.0);
  }

  vector<T> vnew;
  vnew.reserve(vp.size() + vn.size());
  vnew.insert(vnew.end(), vp.begin(), vp.end());
  vnew.insert(vnew.end(), vn.begin(), vn.end());
  return condensed_summation(vnew);
}

#endif  // SUM_H_
