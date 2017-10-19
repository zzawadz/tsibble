#include <Rcpp.h>
using namespace Rcpp;
using namespace std;

// Find the lowest positive value

// [[Rcpp::export]]
double minp(NumericVector x) {
  NumericVector::iterator it;
  double z = 0;

  for(it = x.begin(); it != x.end(); ++it) {
    if (*it > 0 && (*it < z || z == 0)) {
      z = *it;
    }
  }

  return z;
}

// Equivalent to any(x != c)

// [[Rcpp::export]]
bool any_not_equal_to_c(NumericVector x, double c) {
  NumericVector::iterator it;

  for(it = x.begin(); it != x.end(); ++it) {
    if (*it != c) {
      return true;
    }
  };
  return false;
}

// Sliding window function

// [[Rcpp::export]]
List slide_cpp(NumericVector x, Function f, int size, List fill) {
  int n = x.size();
  NumericVector y(size);
  List z(n);

  int na_obs = size - 1;
  for (int i = 0; i < n; ++i) {
    if (i < na_obs) {
      z[i] = fill;
    } else {
      for (int j = 0; j < size; ++j) {
        y[j] = x[i + j - na_obs];
      }
      z[i] = f(y);
    }
  }

  return(z);
}
