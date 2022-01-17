#pragma once
#include <vector>
#include <ostream>
#include <iostream>
#include "_main.hxx"

using std::vector;
using std::ostream;
using std::cout;




// DI-GRAPH
// --------

template <class K=int, class V=NONE, class E=NONE>
class DiGraph {
  public:
  using key_type          = K;
  using vertex_value_type = V;
  using edge_value_type   = E;

  private:
  vector<K>    none;
  vector<bool> vex;
  vector2d<K>  vto;
  vector<V>    vdata;
  vector2d<E>  edata;
  size_t N = 0, M = 0;

  // Cute helpers
  private:
  size_t s() const { return vto.size(); }
  K ei(K u, K v) const { return findAt(vto[u], v); }

  // Read operations
  public:
  size_t span()  const { return s(); }
  size_t order() const { return N; }
  size_t size()  const { return M; }

  bool hasVertex(K u)    const { return u < s() && vex[u]; }
  bool hasEdge(K u, K v) const { return u < s() && ei(u, v) >= 0; }
  auto edges(K u)        const { return u < s()? iterable(vto[u]) : iterable(none); }
  K degree(K u)          const { return u < s()? vto[u].size()    : 0; }
  auto vertices()    const { return filterIterable(rangeIterable(s()), [&](K u) { return  vex[u]; }); }
  auto nonVertices() const { return filterIterable(rangeIterable(s()), [&](K u) { return !vex[u]; }); }
  auto inEdges(K v)  const { return filterIterable(rangeIterable(s()), [&](K u) { return ei(u, v) >= 0; }); }
  K inDegree(K v)    const { return        countIf(rangeIterable(s()), [&](K u) { return ei(u, v) >= 0; }); }

  V vertexData(K u)   const { return hasVertex(u)? vdata[u] : V(); }
  void setVertexData(K u, V d) { if (hasVertex(u)) vdata[u] = d; }
  E edgeData(K u, K v)   const { return hasEdge(u, v)? edata[u][ei(u, v)] : E(); }
  void setEdgeData(K u, K v, E d) { if (hasEdge(u, v)) edata[u][ei(u, v)] = d; }

  // Write operations
  public:
  void addVertex(K u, V d=V()) {
    if (hasVertex(u)) return;
    if (u >= s()) {
      vex.resize(u+1);
      vto.resize(u+1);
      edata.resize(u+1);
      vdata.resize(u+1);
    }
    vex[u] = true;
    vdata[u] = d;
    N++;
  }

  void addEdge(K u, K v, E d=E()) {
    if (hasEdge(u, v)) return;
    addVertex(u);
    addVertex(v);
    vto[u].push_back(v);
    edata[u].push_back(d);
    M++;
  }

  void removeEdge(K u, K v) {
    if (!hasEdge(u, v)) return;
    K o = ei(u, v);
    eraseIndex(vto[u], o);
    eraseIndex(edata[u], o);
    M--;
  }

  void removeEdges(K u) {
    if (!hasVertex(u)) return;
    M -= degree(u);
    vto[u].clear();
    edata[u].clear();
  }

  void removeInEdges(K v) {
    if (!hasVertex(v)) return;
    for (K u : inEdges(v))
      removeEdge(u, v);
  }

  void removeVertex(K u) {
    if (!hasVertex(u)) return;
    removeEdges(u);
    removeInEdges(u);
    vex[u] = false;
    N--;
  }
};




// DI-GRAPH PRINT
// --------------

template <class V, class E>
void write(ostream& a, const DiGraph<V, E>& x, bool all=false) {
  a << "order: " << x.order() << " size: " << x.size();
  if (!all) { a << " {}"; return; }
  a << " {\n";
  for (auto u : x.vertices()) {
    a << "  " << u << " ->";
    for (auto v : x.edges(u))
      a << " " << v;
    a << "\n";
  }
  a << "}";
}

template <class V, class E>
ostream& operator<<(ostream& a, const DiGraph<V, E>& x) {
  write(a, x);
  return a;
}
