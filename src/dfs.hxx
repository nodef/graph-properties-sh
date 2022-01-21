#pragma once
#include <utility>
#include <vector>
#include "vertices.hxx"

using std::pair;
using std::vector;




// DFS
// ---
// Traverses nodes in depth-first manner, listing on entry.

template <class G, class K, class F>
void dfsDoLoop(vector<bool>& vis, const G& x, K u, F fn) {
  if (vis[u]) return;  // dont visit if done already!
  vis[u] = true; fn(u);
  for (auto v : x.edgeKeys(u))
    if (!vis[v]) dfsDoLoop(vis, x, v, fn);
}

template <class G, class K, class F>
void dfsDo(const G& x, K u, F fn) {
  auto vis = createContainer(x, bool());
  dfsDoLoop(vis, x, u, fn);
}


template <class G, class K>
void dfsLoop(vector<K>& a, vector<bool>& vis, const G& x, K u) {
  dfsDoLoop(vis, x, u, [&](auto u) { a.push_back(u); });
}

template <class G, class K>
auto dfs(const G& x, K u) {
  vector<K> a;
  auto vis = createContainer(x, bool());
  dfsLoop(a, vis, x, u);
  return a;
}




// DFS-END
// -------
// Traverses nodes in depth-first manner, listing on exit.

template <class G, class K, class F>
void dfsEndDoLoop(vector<bool>& vis, const G& x, K u, F fn) {
  if (vis[u]) return;  // dont visit if done already!
  vis[u] = true;
  for (auto v : x.edgeKeys(u))
    if (!vis[v]) dfsEndDoLoop(vis, x, v, fn);
  fn(u);
}

template <class G, class K, class F>
void dfsEndDo(const G& x, K u, F fn) {
  auto vis = createContainer(x, bool());
  dfsEndDoLoop(vis, x, u, fn);
}


template <class G, class K>
void dfsEndLoop(vector<K>& a, vector<bool>& vis, const G& x, K u) {
  dfsEndDoLoop(vis, x, u, [&](auto v) { a.push_back(v); });
}

template <class G, class K>
auto dfsEnd(const G& x, K u) {
  vector<K> a;
  auto vis = createContainer(x, bool());
  dfsEndLoop(a, vis, x, u);
  return a;
}




// DFS DEPTH
// ---------
// Traverses nodes in depth-first manner, listing on entry.

template <class G, class K, class F>
void dfsDepthDoLoop(vector<bool>& vis, const G& x, K u, K d, F fn) {
  if (vis[u]) return;  // dont visit if done already!
  vis[u] = true; fn(u, d++);
  for (auto v : x.edgeKeys(u))
    if (!vis[v]) dfsDepthDoLoop(vis, x, v, d, fn);
}

template <class G, class K, class F>
void dfsDepthDo(const G& x, K u, K d, F fn) {
  auto vis = createContainer(x, bool());
  dfsDepthDoLoop(vis, x, u, d, fn);
}


template <class G, class K>
void dfsDepthLoop(vector<pair<K, K>>& a, vector<bool>& vis, const G& x, K u, K d) {
  dfsDepthDoLoop(vis, x, u, d, [&](auto v, auto d) { a.push_back({v, d}); });
}

template <class G, class K>
auto dfsDepth(const G& x, K u, K d) {
  vector<pair<K, K>> a;
  auto vis = createContainer(x, bool());
  dfsDepthLoop(a, vis, x, u, d);
  return a;
}
