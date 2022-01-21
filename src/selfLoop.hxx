#pragma once
#include "duplicate.hxx"




// HAS SELF-LOOP
// -------------

template <class G, class K>
bool hasSelfLoop(const G& x, K u) {
  return x.hasEdge(u, u);
}




// SELF-LOOPS
// ----------

template <class G, class F>
void selfLoopForEach(const G& x, F fn) {
  x.forEachVertexKey([&](auto u) { if (x.hasEdge(u, u)) fn(u); });
}


template <class G>
auto selfLoops(const G& x) {
  using K = typename G::key_type; vector<K> a;
  selfLoopForEach(x, [&](auto u) { a.push_back(u); });
  return a;
}

template <class G>
auto selfLoopCount(const G& x) {
  using K = typename G::key_type; K a = 0;
  selfLoopForEach(x, [&](auto u) { ++a; });
  return a;
}




// SELF-LOOPS
// ----------

template <class G, class F>
void selfLoopTo(G& a, F fn) {
  a.forEachVertexKey([&](auto u) { if (fn(u)) a.addEdge(u, u); });
}

template <class G, class F>
auto selfLoop(const G& x, F fn) {
  auto a = duplicate(x); selfLoopTo(a, fn);
  return a;
}
