#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include "_main.hxx"
#include "vertices.hxx"
#include "edges.hxx"
#include "dfs.hxx"
#include "components.hxx"

using std::vector;
using std::unordered_map;
using std::reverse;
using std::swap;




// TOPOLOGICAL-SORT
// ----------------
// Arrrange vertices in dependency order.
// Top level vertices may not always come first.

template <class G>
auto topologicalSort(const G& x) {
  using K = typename G::key_type; vector<K> a;
  auto vis = createContainer(x, bool());
  for (auto u : x.vertices())
    if (!vis[u]) dfsEndLoop(a, vis, x, u);
  reverse(a.begin(), a.end());
  return a;
}




// LEVELWISE-SORT
// --------------
// Arrange vertices in dependency and level order.
// Top level vertices always come first.

template <class H, class F>
void levelwiseSortDo(vector<bool>& visx, vector<bool>& vis, const H& xt, F fn) {
  for (auto u : xt.vertices()) {
    if (vis[u] || allEdgesVisited(xt, u, vis)) visx[u] = true;
    if (vis[u] != visx[u]) fn(u);
  }
  swap(visx, vis);
}
template <class H>
auto levelwiseSort(const H& xt) {
  using K = typename H::key_type; vector<K> a;
  auto fn   = [&](auto u) { a.push_back(u); };
  auto vis  = createContainer(xt, bool());
  auto visx = createContainer(xt, bool());
  while (a.size() < xt.order())
    levelwiseSortDo(visx, vis, xt, fn);
  return a;
}




// LEVELWISE-GROUPS
// ----------------
// Arrange groups of vertices in dependency and level order.
// Vertices belonging to the same level come in a group.

template <class H>
auto levelwiseGroups(const H& xt) {
  using K = typename H::key_type;
  vector2d<K> a; size_t N = 0;
  auto fn   = [&](auto u) { a.back().push_back(u); };
  auto vis  = createContainer(xt, bool());
  auto visx = createContainer(xt, bool());
  while (N < xt.order()) {
    a.push_back({});
    levelwiseSortDo(visx, vis, xt, fn);
    N += a.back().size();
  }
  return a;
}


template <class H>
auto levelwiseGroupIndices(const H& xt) {
  using K = typename H::key_type;
  unordered_map<K, K> a; K i = 0;
  auto fn   = [&](auto u) { a[u] = i; };
  auto vis  = createContainer(xt, bool());
  auto visx = createContainer(xt, bool());
  for (; a.size() < xt.order(); i++)
    levelwiseSortDo(visx, vis, xt, fn);
  return a;
}




// TOPOLOGICAL-COMPONENTS
// ----------------------
// Get components in topological order.

template <class G, class K>
void topologicalComponentsTo(vector2d<K>& cs, const G& b) {
  auto bks = topologicalSort(b);
  reorderDirty(cs, bks);
}

template <class G, class K>
auto topologicalComponentsFrom(const vector2d<K>& cs, const G& b) {
  auto bks = topologicalSort(b);
  return copyAt(cs, bks);
}

template <class G, class H>
auto topologicalComponents(const G& x, const H& xt) {
  auto cs = components(x, xt);
  auto b  = blockgraph(x, cs);
  topologicalComponentsTo(cs, b);
  return cs;
}




// LEVELWISE-COMPONENTS
// --------------------

template <class H, class K>
void levelwiseComponentsTo(vector2d<K>& cs, const H& bt) {
  auto bks = levelwiseSort(bt);
  reorderDirty(cs, bks);
}

template <class H, class K>
auto levelwiseComponentsFrom(const vector2d<K>& cs, const H& bt) {
  auto bks = levelwiseSort(bt);
  return copyAt(cs, bks);
}

template <class G, class H>
auto levelwiseComponents(const G& x, const H& xt) {
  auto cs = components(x, xt);
  auto b  = blockgraph(x, cs);
  auto bt = transpose(x);
  levelwiseComponentsTo(cs, bt);
  return cs;
}




// LEVELWISE-GROUPED-COMPONENTS
// ----------------------------

template <class H, class K>
auto levelwiseGroupedComponentsFrom(const vector2d<K>& cs, const H& bt) {
  vector2d<K> a;
  auto bgs = levelwiseGroups(bt);
  for (const auto& g : bgs)
    a.push_back(joinAt<K>(cs, g));
  return a;
}

template <class G, class H>
auto levelwiseGroupedComponents(const G& x, const H& xt) {
  auto cs = components(x, xt);
  auto b  = blockgraph(x, cs);
  auto bt = transpose(b);
  return levelwiseGroupedComponentsFrom(cs, bt);
}
