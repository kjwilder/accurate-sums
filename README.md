## Accurately sum a sequence (array) of numbers.

### Overview
[sum.h](sum.h) provides templated functions to accurately compute the sum of a
vector of numbers by avoiding Round-off and cancellation errors

### Details
- The `condensed_summation` function implements the algorithm described by
  William Kahan. It avoids common round-off errors but can fail when there is
  cancellation.
- The `modified_deflation` function aimplements the algorithm described by I.
  J. Anderson. It is slower than `condensed_summation` but handles
  cancellation.  It is difficult to do better than this algorithm without
  increasing the precision. I modified The part of the algorithm that handles
  potentially infinite loops as the algorithm in the paper did not always work in
  my tests.  I believe my correction may not handle some edge cases but have not
  found any (nor tried hard to find them).
