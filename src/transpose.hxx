#pragma once
#include "DiGraph.hxx"




// TRANSPOSE
// ---------

template <class H, class G>
void transpose(H& a, const G& x) {
  for (auto u : x.vertices())
    a.addVertex(u, x.vertexData(u));
  for (auto u : x.vertices()) {
    for (auto v : x.edges(u))
      a.addEdge(v, u, x.edgeData(u, v));
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
  for (auto u : x.vertices())
    a.addVertex(u, x.degree(u));
  for (auto u : x.vertices()) {
    for (auto v : x.edges(u))
      a.addEdge(v, u, x.edgeData(u, v));
  }
}

template <class G>
auto transposeWithDegree(const G& x) {
  using K = typename G::key_type;
  using E = typename G::edge_value_type;
  DiGraph<K, K, E> a; transposeWithDegree(a, x);
  return a;
}
