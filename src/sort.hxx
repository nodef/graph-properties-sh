#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include "_main.hxx"
#include "vertices.hxx"
#include "edges.hxx"
#include "degree.hxx"
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
  x.forEachVertexKey([&](auto u) {
    if (!vis[u]) dfsEndTo(a, vis, x, u);
  });
  reverse(a.begin(), a.end());
  return a;
}




// LEVELWISE-SORT
// --------------
// Arrange vertices in dependency and level order.
// Top level vertices always come first.

template <class H, class F>
void levelwiseSortDo(vector<bool>& visx, vector<bool>& vis, const H& xt, F fn) {
  xt.forEachVertexKey([&](auto u) {
    if (vis[u] || allEdgesVisited(xt, u, vis)) visx[u] = true;
    if (vis[u] != visx[u]) fn(u);
  });
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


template <class G, class K, class F>
void levelwiseFrontierDo(const G& x, const vector<K>& frnt, vector<K>& ideg, F fn) {
  for (auto u : frnt)
    x.forEachEdgeKey(u, [&](auto v) { if (--ideg[v] == 0) fn(v); });
}

template <class G, class H, class F>
void levelwiseFrontiersDo(const G& x, const H& xt, F fn) {
  using  K = typename G::key_type;
  vector<K> frnt, frnu, a;
  auto ideg = degreesDo(xt, [&](auto u, auto d) {
    if (d == 0) frnt.push_back(u);
  });
  while (!frnt.empty()) {
    fn(frnt);
    frnu.clear();
    levelwiseFrontierDo(x, frnt, ideg, [&](auto v) { frnu.push_back(v); });
    swap(frnu, frnt);
  }
}

template <class G, class H>
auto levelwiseSortFrontier(const G& x, const H& xt) {
  using K = typename G::key_type; vector<K> a;
  levelwiseFrontiersDo(x, xt, [&](const auto& frnt) { copyAppend(frnt, a); });
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
  vector<K> a(xt.span()); K i = 0;
  auto fn   = [&](auto u) { a[u] = i; };
  auto vis  = createContainer(xt, bool());
  auto visx = createContainer(xt, bool());
  for (; a.size() < xt.order(); i++)
    levelwiseSortDo(visx, vis, xt, fn);
  return a;
}


template <class G, class H>
auto levelwiseGroupsFrontier(const G& x, const H& xt) {
  using K = typename G::key_type; vector2d<K> a;
  levelwiseFrontiersDo(x, xt, [&](const auto& frnt) { a.push_back(frnt); });
  return a;
}

template <class G, class H>
auto levelwiseGroupIndicesFrontier(const G& x, const H& xt) {
  using K = typename G::key_type;
  vector<K> a(x.span()); K i = 0;
  levelwiseFrontiersDo(x, xt, [&](const auto& frnt) {
    fillValueAt(a, frnt, i++);
  });
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
  return copyAtVector(cs, bks);
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
  return copyAtVector(cs, bks);
}

template <class G, class H>
auto levelwiseComponents(const G& x, const H& xt) {
  auto cs = components(x, xt);
  auto b  = blockgraph(x, cs);
  auto bt = transpose(x);
  levelwiseComponentsTo(cs, bt);
  return cs;
}


template <class G, class H, class K>
void levelwiseComponentsFrontierTo(vector2d<K>& cs, const G& b, const H& bt) {
  auto bks = levelwiseSortFrontier(b, bt);
  reorderDirty(cs, bks);
}

template <class G, class H, class K>
auto levelwiseComponentsFrontierFrom(const vector2d<K>& cs, const G& b, const H& bt) {
  auto bks = levelwiseSortFrontier(b, bt);
  return copyAtVector(cs, bks);
}

template <class G, class H>
auto levelwiseComponentsFrontier(const G& x, const H& xt) {
  auto cs = components(x, xt);
  auto b  = blockgraph(x, cs);
  auto bt = transpose(x);
  levelwiseComponentsFrontierTo(cs, b, bt);
  return cs;
}




// LEVELWISE-GROUPED-COMPONENTS
// ----------------------------

template <class H, class K>
auto levelwiseGroupedComponentsFrom(const vector2d<K>& cs, const H& bt) {
  vector2d<K> a;
  auto bgs = levelwiseGroups(bt);
  for (const auto& g : bgs)
    a.push_back(joinAtVector(cs, g));
  return a;
}

template <class G, class H>
auto levelwiseGroupedComponents(const G& x, const H& xt) {
  auto cs = components(x, xt);
  auto b  = blockgraph(x, cs);
  auto bt = transpose(b);
  return levelwiseGroupedComponentsFrom(cs, bt);
}


template <class G, class H, class K>
auto levelwiseGroupedComponentsFrontierFrom(const vector2d<K>& cs, const G& b, const H& bt) {
  vector2d<K> a;
  auto bgs = levelwiseGroupsFrontier(b, bt);
  for (const auto& g : bgs)
    a.push_back(joinAtVector(cs, g));
  return a;
}

template <class G, class H>
auto levelwiseGroupedComponentsFrontier(const G& x, const H& xt) {
  auto cs = components(x, xt);
  auto b  = blockgraph(x, cs);
  auto bt = transpose(b);
  return levelwiseGroupedComponentsFrontierFrom(cs, b, bt);
}
