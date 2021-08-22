#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <algorithm>
#include "./sum.h"

using std::vector;
using std::cout;
using std::endl;
using std::abs;

// Add a bunch of random numbers in different ways.

// The results are messed up when compiled with
// gcc and optimization.

int main(int argc, char** argv) {
  int size = 1000000;
  if (argc > 1)
    size = atoi(argv[1]);

  unsigned int seed = 0;
  if (argc > 2)
    seed = atoi(argv[2]);
  // srand(seed);

  double res;
  float resf;
  vector<double> d(size);
  vector<float> f(size);

  for (uint i = 0; i < d.size(); ++i)
    d[i] = 100 * ((1.0 * rand_r(&seed)) / RAND_MAX - .5);

  cout.precision(8);

  //=============================================================
  cout << "\nOriginal Double Precision Computations:\n";

  res = accumulate(d.begin(), d.end(), 0.0);
  cout << "The recursive summation is " << res << endl;

  res = condensed_summation(d);
  cout << "The condensed summation is " << res << endl;

  res = modified_deflation(d);
  cout << "The deflated sum is        " << res << endl;

  //=============================================================
  cout << "\nModified Double Precision Computations:\n";
  cout << "(About what the single precision result should be)\n";

  copy(d.begin(), d.end(), f.begin());
  copy(f.begin(), f.end(), d.begin());

  res = accumulate(d.begin(), d.end(), 0.0);
  cout << "The recursive summation is " << res << endl;

  //=============================================================
  cout << "\nSingle Precision Computations, with errors:\n";

  resf = accumulate(f.begin(), f.end(), 0.0f);
  cout << "The recursive summation is " << resf
          << "  (" << resf - res << ")\n";


  resf = condensed_summation(f);
  cout << "The condensed summation is " << resf
          << "  (" << resf - res << ")\n";

  resf = modified_deflation(f);
  cout << "The deflated sum is        " << resf
          << "  (" << resf - res << ")\n";

  cout << endl;

  return 1;
}

