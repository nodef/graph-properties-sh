#pragma once
#include <vector>
#include <iterator>
#include <algorithm>
#include "_main.hxx"

using std::vector;
using std::transform;
using std::back_inserter;




// EDGES
// -----

template <class G, class K, class F, class D>
auto edges(const G& x, K u, F fm, D fp) {
  vector<K> a;
  copyAppend(x.edgeKeys(u), a);
  auto ie = a.end(), ib = a.begin();
  fp(ib, ie); transform(ib, ie, ib, fm);
  return a;
}

template <class G, class K, class F>
auto edges(const G& x, K u, F fm) {
  return edges(x, u, fm, [](auto ib, auto ie) {});
}

template <class G, class K>
auto edges(const G& x, K u) {
  return edges(x, u, [](auto v) { return v; });
}




// EDGE
// ----

template <class G, class K, class F>
auto edge(const G& x, K u, F fm) {
  for (auto v : x.edgeKeys(u))
    return fm(v);
  return K(-1);
}

template <class G, class K>
auto edge(const G& x, K u) {
  return edge(x, u, [](auto v) { return v; });
}




// EDGE-DATA
// ---------

template <class G, class J, class F, class D>
auto edgeData(const G& x, const J& ks, F fm, D fp) {
  using K = typename G::key_type;
  using E = decltype(fm(0, 0));
  vector<E> a; vector<K> b;
  for (auto u : ks) {
    copyWrite(x.edgeKeys(u), b);
    auto ie = b.end(), ib = b.begin();
    fp(ib, ie); transform(ib, ie, back_inserter(a), [&](auto v) { return fm(u, v); });
  }
  return a;
}

template <class G, class J, class F>
auto edgeData(const G& x, const J& ks, F fm) {
  return edgeData(x, ks, fm, [](auto ib, auto ie) {});
}

template <class G, class J>
auto edgeData(const G& x, const J& ks) {
  return edgeData(x, ks, [&](auto u, auto v) { return x.edgeData(u, v); });
}

template <class G>
auto edgeData(const G& x) {
  return edgeData(x, x.vertexKeys());
}




// EDGES-VISITED
// -------------

template <class G, class K>
bool allEdgesVisited(const G& x, K u, const vector<bool>& vis) {
  for (auto v : x.edgeKeys(u))
    if (!vis[v]) return false;
  return true;
}

template <class G, class K>
bool someEdgesVisited(const G& x, K u, const vector<bool>& vis) {
  for (auto v : x.edgeKeys(u))
    if (vis[v]) return true;
  return false;
}
