## C++ functions that accurately sum a sequence (vector) of numbers.

### Overview
[sum.h](sum.h) provides templated functions to accurately compute the sum of a
vector of numbers by avoiding round-off and cancellation errors

### Details
- The `condensed_summation` function implements the algorithm described by
  William Kahan. It avoids common round-off errors but can fail when there is
  cancellation.
- The `modified_deflation` function implements the algorithm described by I.
  J. Anderson. It is slower than `condensed_summation` but handles
  cancellation.  It is difficult to do better than this algorithm without
  increasing the precision. I modified the part of the algorithm that handles
  potentially infinite loops as the algorithm in the paper did not always work in
  my tests.  I believe my correction may not handle some edge cases but have not
  found any (nor tried hard to find them).
- The three test files provide the results of applying the above two algorithms
  and ordinary addition to various sequence of numbers. The differences in the
  results demonstrate how the various strategies handle round-off and cancellation
  errors.
