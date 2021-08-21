#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <algorithm>
#include "sum.h"

using namespace std;

int main(int argc, char** argv)
{
  int size = 20;
  if (argc > 1)
    size = atoi(argv[1]);

  double res;
  vector<double> d(size);
  fill(d.begin(), d.end() - 2, 1);
  *(d.end()-2) = 1e30;
  *(d.end()-1) = -1e30;

  cout.precision(8);

  //===========================================================
  cout << "\n1 + 1 + ... + 1 + 1e30 - 1e30:\n";
  cout << "\n=============================:\n";

  res = accumulate(d.begin(), d.end(), 0.0);
  cout << "The recursive summation is " << res << endl;

  res = condensed_summation(d);
  cout << "The condensed summation is " << res << endl;

  res = modified_deflation(d);
  cout << "The deflated sum is        " << res << endl;

  cout << endl;

  return 1;
}

