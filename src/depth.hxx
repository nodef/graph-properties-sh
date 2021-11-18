#pragma once
#include <utility>
#include "dfs.hxx"
#include "deadEnds.hxx"

using std::make_pair;




// DEPTH
// -----

template <class G>
int depth(const G& x, int u) {
  int a = 0; if (x.order()==0) return 0;
  dfsDepthDo(x, u, 0, [&](int v, int d) { if (d>a) a=d; });
  return ++a;
}




// MIN/MAX DEPTH
// -------------

template <class G, class H>
int minDepth(const G& x, const H& xt) {
  int dmin = x.order();
  deadEndsForEach(xt, [&](int u) {
    int d = depth(x, u);
    if (d<dmin) dmin = d;
  });
  return dmin;
}

template <class G, class H>
int maxDepth(const G& x, const H& xt) {
  int dmax = 0;
  deadEndsForEach(xt, [&](int u) {
    int d = depth(x, u);
    if (d>dmax) dmax = d;
  });
  return dmax;
}

template <class G, class H>
auto minMaxDepth(const G& x, const H& xt) {
  int dmin = x.order(), dmax = 0;
  deadEndsForEach(xt, [&](int u) {
    int d = depth(x, u);
    if (d<dmin) dmin = d;
    if (d>dmax) dmax = d;
  });
  return make_pair(dmin, dmax);
}




// AVG DEPTH
// ---------

template <class G, class H>
float avgDepth(const G& x, const H& xt) {
  int ds = 0, D = 0;
  deadEndsForEach(xt, [&](int u) {
    int d = depth(x, u);
    ds += d; ++D;
  });
  return ds/float(D);
}
