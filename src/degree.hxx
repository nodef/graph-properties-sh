#pragma once
#include <tuple>

using std::make_tuple;



// MIN/MAX/AVG
// -----------

template <class G>
auto minDegree(const G& x) {
  using K = typename G::key_type;
  K dmin = x.order();
  for (auto u : x.vertexKeys()) {
    auto d = x.degree(u);
    if (d<dmin) dmin = d;
  }
  return dmin;
}

template <class G>
auto maxDegree(const G& x) {
  using K = typename G::key_type;
  K dmax = 0;
  for (auto u : x.vertexKeys()) {
    auto d = x.degree(u);
    if (d>dmax) dmax = d;
  }
  return dmax;
}

template <class G>
float avgDegree(const G& x) {
  size_t N = x.order();
  return N>0? x.size()/float(N) : 0;
}


template <class G>
auto minMaxAvgDegree(const G& x) {
  using K = typename G::key_type;
  K dmin = x.order();
  K dmax = 0;
  for (auto u : x.vertexKeys()) {
    auto d = x.degree(u);
    if (d<dmin) dmin = d;
    if (d>dmax) dmax = d;
  }
  return make_tuple(dmin, dmax, avgDegree(x));
}
