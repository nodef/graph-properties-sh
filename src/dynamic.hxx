#pragma once
#include <utility>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "_main.hxx"
#include "vertices.hxx"
#include "components.hxx"

using std::vector;
using std::unordered_set;
using std::max;
using std::make_pair;




// ADJUST-RANKS
// ------------
// For calculating inital ranks for incremental/dynamic pagerank.

template <class T, class J>
void adjustRanks(vector<T>& a, const vector<T>& r, const J& ks0, const J& ks1, T radd, T rmul, T rset) {
  using I = decltype(ks0.begin());
  using K = typename iterator_traits<I>::value_type;
  unordered_set<K> kt0(ks0.begin(), ks0.end());
  unordered_set<K> kt1(ks1.begin(), ks1.end());
  for (auto k : ks0)
    if (kt1.count(k)>0)  a[k] = (r[k]+radd)*rmul;  // if vertex not removed
  for (auto k : ks1)
    if (kt0.count(k)==0) a[k] = rset;              // if vertex added
}

template <class T, class J>
auto adjustRanks(size_t N, const vector<T>& r, const J& ks0, const J& ks1, T radd, T rmul, T rset) {
  vector<T> a(N); adjustRanks(a, r, ks0, ks1, radd, rmul, rset);
  return a;
}




// CHANGED-VERTICES
// ----------------
// Find vertices with edges added/removed.

template <class G, class F>
void changedVerticesForEach(const G& x, const G& y, F fn) {
  for (auto u : y.vertexKeys())
    if (!x.hasVertex(u) || !verticesEqual(x, u, y, u)) fn(u);
}

template <class G, class H, class F>
void changedVerticesForEach(const G& x, const H& xt, const G& y, const H& yt, F fn) {
  for (auto u : y.vertexKeys())
    if (!x.hasVertex(u) || !verticesEqual(x, xt, u, y, yt, u)) fn(u);  // both ways
}

template <class G>
auto changedVertices(const G& x, const G& y) {
  using K = typename G::key_type; vector<K> a;
  changedVerticesForEach(x, y, [&](auto u) { a.push_back(u); });
  return a;
}

template <class G, class H>
auto changedVertices(const G& x, const H& xt, const G& y, const H& yt) {
  using K = typename G::key_type; vector<K> a;
  changedVerticesForEach(x, xt, y, yt, [&](auto u) { a.push_back(u); });
  return a;
}




// AFFECTED-VERTICES
// -----------------
// Find vertices reachable from changed vertices.

template <class G, class F>
void affectedVerticesForEach(const G& x, const G& y, F fn) {
  auto visx = createContainer(x, bool());
  auto visy = createContainer(y, bool());
  auto fny  = [&](auto u) { if (u>=visx.size() || !visx[u]) fn(u); };  // check bounds!
  changedVerticesForEach(x, y, [&](auto u) { if (x.hasVertex(u)) dfsDoLoop(visx, x, u, fn); });
  changedVerticesForEach(x, y, [&](auto u) { dfsDoLoop(visy, y, u, fny); });
}

template <class G, class H, class F>
void affectedVerticesForEach(const G& x, const H& xt, const G& y, const H& yt, F fn) {
  auto vis = createContainer(y, bool());
  changedVerticesForEach(x, xt, y, yt, [&](auto u) { dfsDoLoop(vis, y, u, fn); });
}

template <class G>
auto affectedVertices(const G& x, const G& y) {
  using K = typename G::key_type; vector<K> a;
  affectedVerticesForEach(x, y, [&](auto u) { a.push_back(u); });
  return a;
}

template <class G, class H>
auto affectedVertices(const G& x, const H& xt, const G& y, const H& yt) {
  using K = typename G::key_type; vector<K> a;
  affectedVerticesForEach(x, xt, y, yt, [&](auto u) { a.push_back(u); });
  return a;
}




// DYNAMIC-VERTICES
// ----------------
// Find affected, unaffected vertices (vertices, no. affected).

template <class G, class FA>
auto dynamicVerticesBy(const G& y, FA fa) {
  using K = typename G::key_type;
  vector<K> a; unordered_set<K> aff;
  fa([&](auto u) { a.push_back(u); aff.insert(u); });
  for (auto u : y.vertexKeys())
    if (aff.count(u)==0) a.push_back(u);
  return make_pair(a, aff.size());
}

template <class G>
auto dynamicVertices(const G& x, const G& y) {
  return dynamicVerticesBy(y, [&](auto fn) {
    affectedVerticesForEach(x, y, fn);
  });
}

template <class G, class H>
auto dynamicVertices(const G& x, const H& xt, const G& y, const H& yt) {
  return dynamicVerticesBy(y, [&](auto fn) {
    affectedVerticesForEach(x, xt, y, yt, fn);
  });
}




// CHANGED-COMPONENTS
// ------------------
// Find components with edges added/removed.

template <class G, class K, class F>
void changedComponentIndicesForEach(const G& x, const G& y, const vector2d<K>& cs, F fn) {
  for (size_t i=0, I=cs.size(); i<I; ++i)
    if (!componentsEqual(x, cs[i], y, cs[i])) fn(i);
}

template <class G, class H, class K, class F>
void changedComponentIndicesForEach(const G& x, const H& xt, const G& y, const H& yt, const vector2d<K>& cs, F fn) {
  for (size_t i=0, I=cs.size(); i<I; ++i)
    if (!componentsEqual(x, xt, cs[i], y, yt, cs[i])) fn(i);  // both ways
}

template <class G, class K>
auto changedComponentIndices(const G& x, const G& y, const vector2d<K>& cs) {
  vector<K> a; changedComponentIndicesForEach(x, y, cs, [&](auto u) { a.push_back(u); });
  return a;
}

template <class G, class H, class K>
auto changedComponentIndices(const G& x, const H& xt, const G& y, const H& yt, const vector2d<K>& cs) {
  vector<K> a; changedVerticesForEach(x, xt, y, yt, cs, [&](auto u) { a.push_back(u); });
  return a;
}




// AFFECTED-COMPONENTS
// -------------------
// Find components reachable from changed components.

template <class G, class K, class B, class F>
void affectedComponentIndicesForEach(const G& x, const G& y, const vector2d<K>& cs, const B& b, F fn) {
  auto vis = createContainer(b, bool());
  changedComponentIndicesForEach(x, y, cs, [&](auto u) { dfsDoLoop(vis, b, u, fn); });
}

template <class G, class H, class K, class B, class F>
void affectedComponentIndicesForEach(const G& x, const H& xt, const G& y, const H& yt, const vector2d<K>& cs, const B& b, F fn) {
  auto vis = createContainer(b, bool());
  changedComponentIndicesForEach(x, xt, y, yt, cs, [&](auto u) { dfsDoLoop(vis, b, u, fn); });
}

template <class G, class K, class B>
auto affectedComponentIndices(const G& x, const G& y, const vector2d<K>& cs, const B& b) {
  vector<K> a; affectedComponentIndicesForEach(x, y, cs, b, [&](auto u) { a.push_back(u); });
  return a;
}

template <class G, class H, class K, class B>
auto affectedComponentIndices(const G& x, const H& xt, const G& y, const H& yt, const vector2d<K>& cs, const B& b) {
  vector<K> a; affectedComponentIndicesForEach(x, xt, y, yt, cs, b, [&](auto u) { a.push_back(u); });
  return a;
}




// DYNAMIC-COMPONENTS
// ------------------
// Find affected, unaffected components (components, no. affected).

template <class G, class K, class FA>
auto dynamicComponentIndicesBy(const G& y, const vector2d<K>& cs, FA fa) {
  vector<K> a; unordered_set<K> aff;
  fa([&](auto i) { a.push_back(i); aff.insert(i); });
  for (size_t i=0, I=cs.size(); i<I; ++i)
    if (aff.count(i)==0) a.push_back(i);
  return make_pair(a, aff.size());
}

template <class G, class K, class B>
auto dynamicComponentIndices(const G& x, const G& y, const vector2d<K>& cs, const B& b) {
  return dynamicComponentIndicesBy(y, cs, [&](auto fn) {
    affectedComponentIndicesForEach(x, y, cs, b, fn);
  });
}

template <class G, class H, class K, class B>
auto dynamicComponentIndices(const G& x, const H& xt, const G& y, const H& yt, const vector2d<K>& cs, const B& b) {
  return dynamicComponentIndicesBy(y, cs, [&](auto fn) {
    affectedComponentIndicesForEach(x, xt, y, yt, cs, b, fn);
  });
}
