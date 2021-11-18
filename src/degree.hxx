#pragma once
#include <utility>

using std::make_pair;



// MIN/MAX
// -------

template <class G>
int minDegree(const G& x) {
  int dmin = x.order();
  for (int u : x.vertices()) {
    int d = x.degree(u);
    if (d<dmin) dmin = d;
  }
  return dmin;
}

template <class G>
int maxDegree(const G& x) {
  int dmax = x.order();
  for (int u : x.vertices()) {
    int d = x.degree(u);
    if (d>dmax) dmax = d;
  }
  return dmax;
}

template <class G>
auto minMaxDegree(const G& x) {
  int dmin = x.order(), dmax = 0;
  for (int u : x.vertices()) {
    int d = x.degree(u);
    if (d<dmin) dmin = d;
    if (d>dmax) dmax = d;
  }
  return make_pair(dmin, dmax);
}




// AVG
// ---

template <class G>
float avgDegree(const G& x) {
  return float(x.size())/x.order();
}
