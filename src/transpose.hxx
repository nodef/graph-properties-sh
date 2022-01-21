#pragma once
#include "Graph.hxx"




// TRANSPOSE
// ---------

template <class H, class G>
void transpose(H& a, const G& x) {
  for (auto u : x.vertexKeys())
    a.addVertex(u, x.vertexValue(u));
  for (auto u : x.vertexKeys()) {
    for (auto v : x.edgeKeys(u))
      a.addEdge(v, u, x.edgeValue(u, v));
  }
}

template <class G>
auto transpose(const G& x) {
  G a; transpose(a, x);
  return a;
}




// TRANSPOSE-WITH-DEGREE
// ---------------------

template <class H, class G>
void transposeWithDegree(H& a, const G& x) {
  for (auto u : x.vertexKeys())
    a.addVertex(u, x.degree(u));
  for (auto u : x.vertexKeys()) {
    for (auto v : x.edgeKeys(u))
      a.addEdge(v, u, x.edgeValue(u, v));
  }
}

template <class G>
auto transposeWithDegree(const G& x) {
  using K = typename G::key_type;
  using E = typename G::edge_value_type;
  DiGraph<K, K, E> a; transposeWithDegree(a, x);
  return a;
}
