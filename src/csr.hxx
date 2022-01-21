#pragma once
#include <vector>
#include <algorithm>
#include "_main.hxx"

using std::vector;
using std::transform;




// SOURCE-OFFSETS
// --------------

template <class G, class J>
auto sourceOffsets(const G& x, const J& ks) {
  using K = typename G::key_type;
  K i = 0; vector<K> a;
  a.reserve(x.order()+1);
  for (auto u : ks) {
    a.push_back(i);
    i += x.degree(u);
  }
  a.push_back(i);
  return a;
}

template <class G>
auto sourceOffsets(const G& x) {
  return sourceOffsets(x, x.vertexKeys());
}




// DESTINATION-INDICES
// -------------------

template <class G, class J, class F>
auto destinationIndices(const G& x, const J& ks, F fp) {
  using K = typename G::key_type; vector<K> a;
  auto ids = indices(ks);
  for (auto u : ks) {
    copyAppend(x.edgeKeys(u), a);
    auto ie = a.end(), ib = ie-x.degree(u);
    fp(ib, ie); transform(ib, ie, ib, [&](K v) { return ids[v]; });
  }
  return a;
}

template <class G, class J>
auto destinationIndices(const G& x, const J& ks) {
  return destinationIndices(x, ks, [](auto ib, auto ie) {});
}

template <class G>
auto destinationIndices(const G& x) {
  return destinationIndices(x, x.vertexKeys());
}
