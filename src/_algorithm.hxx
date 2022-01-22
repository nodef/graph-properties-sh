#pragma once
#include <vector>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <functional>
#include "_queue.hxx"

using std::vector;
using std::unordered_map;
using std::iterator_traits;
using std::hash;
using std::distance;
using std::for_each;
using std::any_of;
using std::all_of;
using std::find;
using std::find_if;
using std::lower_bound;
using std::count;
using std::count_if;
using std::back_inserter;
using std::copy;
using std::transform;
using std::set_difference;
using std::merge;
using std::inplace_merge;




// FOR-EACH
// --------
// Perform a sale.

template <class J, class F>
inline void forEach(J& x, F fn) {
  for_each(x.begin(), x.end(), fn);
}
template <class J, class F>
inline void forEach(const J& x, F fn) {
  for_each(x.begin(), x.end(), fn);
}
template <class J, class F>
inline void cforEach(const J& x, F fn) {
  for_each(x.begin(), x.end(), fn);
}




// ANY-OF
// ------
// Is anything useful there?

template <class J, class F>
inline auto anyOf(const J& x, F fn) {
  return any_of(x.begin(), x.end(), fn);
}




// ALL-OF
// ------
// Is everything there?

template <class J, class F>
inline auto allOf(const J& x, F fn) {
  return all_of(x.begin(), x.end(), fn);
}




// FIND-*
// ------
// Find a business or its address.

template <class I, class T>
inline auto find_value(I ib, I ie, const T& v) {
  return find(ib, ie, v);
}
template <class J, class T>
inline auto findValue(const J& x, const T& v) {
  return find_value(x.begin(), x.end(), v);
}


template <class I, class T>
inline size_t find_index(I ib, I ie, const T& v) {
  return find(ib, ie, v) - ib;
}
template <class J, class T>
inline size_t find_index(const J& x, const T& v) {
  return find_index(x.begin(), x.end(), v);
}


template <class I, class T>
inline size_t find_at(I ib, I ie, const T& v) {
  auto it = find(ib, ie, v);
  return it != ie? it - ib : size_t(-1);
}
template <class J, class T>
inline size_t findAt(const J& x, const T& v) {
  return find_at(x.begin(), x.end(), v);
}


template <class J, class F>
inline auto findIf(const J& x, F fn) {
  return find_if(x.begin(), x.end(), fn);
}


template <class I, class F>
inline size_t find_if_index(I ib, I ie, F fn) {
  return find_if(ib, ie, fn) - ib;
}
template <class J, class F>
inline size_t findIfIndex(const J& x, F fn) {
  return find_if_index(x.begin(), x.end(), fn);
}


template <class I, class F>
inline size_t find_if_at(I ib, I ie, F fn) {
  auto it = find_if(ib, ie, fn);
  return it != ie? it - ib : size_t(-1);
}
template <class J, class F>
inline size_t findIfAt(const J& x, F fn) {
  return find_if_at(x.begin(), x.end(), fn);
}




// LOWER-BOUND/FIND
// ----------------
// Find closest business, or its address.

template <class J, class T>
inline auto lowerBound(const J& x, const T& v) {
  return lower_bound(x.begin(), x.end(), v);
}
template <class J, class T, class FL>
inline auto lowerBound(const J& x, const T& v, FL fl) {
  return lower_bound(x.begin(), x.end(), v, fl);
}


template <class I, class T>
inline size_t lower_bound_index(I ib, I ie, const T& v) {
  return lower_bound(ib, ie, v) - ib;
}
template <class I, class T, class FL>
inline size_t lower_bound_index(I ib, I ie, const T& v, FL fl) {
  return lower_bound(ib, ie, v, fl) - ib;
}
template <class J, class T>
inline size_t lowerBoundIndex(const J& x, const T& v) {
  return lower_bound_index(x.begin(), x.end(), v);
}
template <class J, class T, class FL>
inline size_t lowerBoundIndex(const J& x, const T& v, FL fl) {
  return lower_bound_index(x.begin(), x.end(), v, fl);
}


template <class I, class T>
inline auto lower_find(I ib, I ie, const T& v) {
  auto it = lower_bound(ib, ie, v);
  return it != ie && *it == v? it : ie;
}
template <class I, class T, class FL>
inline auto lower_find(I ib, I ie, const T& v, FL fl) {
  auto it = lower_bound(ib, ie, v, fl);
  return it != ie && *it == v? it : ie;
}
template <class I, class T, class FL, class FE>
inline auto lower_find(I ib, I ie, const T& v, FL fl, FE fe) {
  auto it = lower_bound(ib, ie, v, fl);
  return it != ie && fe(*it, v)? it : ie;
}
template <class J, class T>
inline auto lowerFind(const J& x, const T& v) {
  return lower_find(x.begin(), x.end(), v);
}
template <class J, class T, class FL>
inline auto lowerFind(const J& x, const T& v, FL fl) {
  return lower_find(x.begin(), x.end(), v, fl);
}
template <class J, class T, class FL, class FE>
inline auto lowerFind(const J& x, const T& v, FL fl, FE fe) {
  return lower_find(x.begin(), x.end(), v, fl, fe);
}


template <class I, class T>
inline size_t lower_find_index(I ib, I ie, const T& v) {
  return lower_find(ib, ie, v) - ib;
}
template <class I, class T, class FL>
inline size_t lower_find_index(I ib, I ie, const T& v, FL fl) {
  return lower_find(ib, ie, v, fl) - ib;
}
template <class I, class T, class FL, class FE>
inline size_t lower_find_index(I ib, I ie, const T& v, FL fl, FE fe) {
  return lower_find(ib, ie, v, fl, fe) - ib;
}
template <class J, class T>
inline size_t lowerFindIndex(const J& x, const T& v) {
  return lower_find_index(x.begin(), x.end(), v);
}
template <class J, class T, class FL>
inline size_t lowerFindIndex(const J& x, const T& v, FL fl) {
  return lower_find_index(x.begin(), x.end(), v, fl);
}
template <class J, class T, class FL, class FE>
inline size_t lowerFindIndex(const J& x, const T& v, FL fl, FE fe) {
  return lower_find_index(x.begin(), x.end(), v, fl, fe);
}


template <class I, class T>
inline size_t lower_find_at(I ib, I ie, const T& v) {
  auto it = lower_find(ib, ie, v);
  return it != ie? it - ib : size_t(-1);
}
template <class I, class T, class FL>
inline size_t lower_find_at(I ib, I ie, const T& v, FL fl) {
  auto it = lower_find(ib, ie, v, fl);
  return it != ie? it - ib : size_t(-1);
}
template <class I, class T, class FL, class FE>
inline size_t lower_find_at(I ib, I ie, const T& v, FL fl, FE fe) {
  auto it = lower_find(ib, ie, v, fl, fe);
  return it != ie? it - ib : size_t(-1);
}
template <class J, class T>
inline size_t lowerFindAt(const J& x, const T& v) {
  return lower_find_at(x.begin(), x.end(), v);
}
template <class J, class T, class FL>
inline size_t lowerFindAt(const J& x, const T& v, FL fl) {
  return lower_find_at(x.begin(), x.end(), v, fl);
}
template <class J, class T, class FL, class FE>
inline size_t lowerFindAt(const J& x, const T& v, FL fl, FE fe) {
  return lower_find_at(x.begin(), x.end(), v, fl, fe);
}




// EQUAL-*
// -------
// Check if values match.

template <class IX, class IY>
inline bool equal_values(IX xb, IX xe, IY yb) {
  return equal(xb, xe, yb);
}
template <class IX, class IY>
inline bool equal_values(IX xb, IX xe, IY yb, IY ye) {
  return equal(xb, xe, yb, ye);
}
template <class IX, class IY, class FE>
inline bool equal_values(IX xb, IX xe, IY yb, FE fe) {
  return equal(xb, xe, yb, fe);
}
template <class IX, class IY, class FE>
inline bool equal_values(IX xb, IX xe, IY yb, IY ye, FE fe) {
  return equal(xb, xe, yb, ye, fe);
}
template <class JX, class JY>
inline bool equalValues(const JX& x, const JY& y) {
  return equal_values(x.begin(), x.end(), y.begin(), y.end());
}
template <class JX, class JY, class FE>
inline bool equalValues(const JX& x, const JY& y, FE fe) {
  return equal_values(x.begin(), x.end(), y.begin(), y.end(), fe);
}




// COUNT-*
// -------
// Count businesses in a sector.

template <class I, class T>
inline size_t count_value(I ib, I ie, const T& v) {
  return count(ib, ie, v);
}
template <class J, class T>
inline size_t countValue(const J& x, const T& v) {
  return count_value(x.begin(), x.end(), v);
}


template <class J, class F>
inline size_t countIf(const J& x, F fn) {
  return count_if(x.begin(), x.end(), fn);
}


template <class I, class FM>
inline auto count_each(I ib, I ie, FM fm) {
  using K = decltype(fm(*ib)); unordered_map<K, size_t> a;
  for_each(ib, ie, [&](const K& v) { ++a[fm(v)]; });
  return a;
}
template <class I>
inline auto count_each(I ib, I ie) {
  auto fm = [](const auto& v) { return v; };
  return count_each(ib, ie, fm);
}
template <class J, class FM>
inline auto countEach(const J& x, FM fm) {
  return count_each(x.begin(), x.end(), fm);
}
template <class J>
inline auto countEach(const J& x) {
  return count_each(x.begin(), x.end());
}




// COPY-*
// ------

template <class I, class IA>
inline auto copy_values(I ib, I ie, IA ab) {
  return copy(ib, ie, ab);
}
template <class J, class JA>
inline auto copyValues(const J& x, JA& a) {
  return copy_values(x.begin(), x.end(), a.begin());
}


template <class I, class T>
inline auto copy_append(I ib, I ie, vector<T>& a) {
  return a.insert(a.end(), ib, ie);
}
template <class J, class T>
inline auto copyAppend(const J& x, vector<T>& a) {
  return copy_append(x.begin(), x.end(), a);
}


template <class I, class T>
inline auto copy_write(I ib, I ie, vector<T>& a) {
  a.clear();
  return copy_append(ib, ie, a);
}
template <class J, class T>
inline auto copyWrite(const J& x, vector<T>& a) {
  return copy_write(x.begin(), x.end(), a);
}


template <class I>
inline auto copy_vector(I ib, I ie) {
  using T = typename iterator_traits<I>::value_type; vector<T> a;
  copy_append(ib, ie, a);
  return a;
}
template <class J>
inline auto copy_vector(const J& x) {
  return copy_vector(x.begin(), x.end());
}





// HASH-VALUE
// ----------

template <class I>
size_t hash_value(I ib, I ie) {
  // From boost::hash_combine.
  using T = typename iterator_traits<I>::value_type; size_t a = 0;
  for (; ib != ie; ++ib)
    a ^= hash<T>{}(*ib) + 0x9e3779b9 + (a<<6) + (a>>2);
  return a;
}
template <class J>
inline size_t hashValue(const J& x) {
  return hash_value(x.begin(), x.end());
}


template <class I, class IB>
inline size_t hash_unordered(I ib, I ie, IB bb) {
  IB be = bb + distance(ib, ie);
  copy(ib, ie, bb);
  sort(bb, be);
  return hash_value(bb, be);
}
template <class J, class JB>
inline size_t hashUnordered(const J& x, JB& buf) {
  return hash_unordered(x.begin(), x.end(), buf.begin());
}
template <class J, class T>
inline size_t hashUnordered(const J& x, vector<T>& buf) {
  size_t s = distance(x.begin(), x.end());
  if (buf.size() < s) buf.resize(s);
  return hash_unordered(x.begin(), x.end(), buf);
}



// INDICES
// -------
// Keep the address of each business (yellow pages).

template <class I, class M>
auto value_indices(I ib, I ie, M& a) {
  size_t i = 0;
  for (; ib != ie; ++ib)
    a[*ib] = i++;
  return a;
}
template <class I>
inline auto value_indices(I ib, I ie) {
  using K = typename iterator_traits<I>::value_type; unordered_map<K, size_t> a;
  return value_indices(ib, ie, a);
}
template <class J, class M>
inline auto valueIndices(const J& x, M& a) {
  return value_indices(x.begin(), x.end(), a);
}
template <class J>
inline auto valueIndices(const J& x) {
  return value_indices(x.begin(), x.end());
}




// TRANSFORM
// ---------
// Switch around your portfolio.

template <class IX, class IA, class FM>
inline auto transform_values(IX xb, IX xe, IA ab, FM fm) {
  return transform(xb, xe, ab, fm);
}
template <class JX, class JA, class FM>
inline auto transformValues(const JX& x, JA& a, FM fm) {
  return transform(x.begin(), x.end(), a.begin(), fm);
}


template <class I, class T, class FM>
inline auto transform_append(I ib, I ie, vector<T>& a, FM fm) {
  return transform(ib, ie, back_inserter(a), fm);
}
template <class J, class T, class FM>
inline auto transformAppend(const J& x, vector<T>& a, FM fm) {
  return transform_append(x.begin(), x.end(), a, fm);
}


template <class I, class FM>
inline auto transform_vector(I ib, I ie, FM fm) {
  using T = typename iterator_traits<I>::value_type; vector<T> a;
  return transform_append(ib, ie, a, fm);
}
template <class J, class FM>
inline auto transformVector(const J& x, FM fm) {
  return transform_vector(x.begin(), x.end(), fm);
}




// SORT
// ----
// Arrange your portfolio by ROCE.

template <class I>
inline void sort_values(I ib, I ie) {
  sort(ib, ie);
}
template <class I, class FL>
inline void sort_values(I ib, I ie, FL fl) {
  sort(ib, ie, fl);
}
template <class J>
inline void sortValues(J& x) {
  sort(x.begin(), x.end());
}
template <class J, class FL>
inline void sortValues(J& x, FL fl) {
  sort(x.begin(), x.end(), fl);
}




// SET-DIFFERENCE-*
// ----------------

template <class JX, class JY, class JA>
inline auto setDifference(const JX& x, const JY& y, JA& a) {
  return set_difference(x.begin(), x.end(), y.begin(), y.end(), a.begin());
}
template <class JX, class JY, class JA, class FE>
inline auto setDifference(const JX& x, const JY& y, JA& a, FE fe) {
  return set_difference(x.begin(), x.end(), y.begin(), y.end(), a.begin(), fe);
}


template <class IX, class IY, class T>
inline auto set_difference_append(IX xb, IX xe, IY yb, IY ye, vector<T>& a) {
  return set_difference(xb, xe, yb, ye, back_inserter(a));
}
template <class IX, class IY, class T, class FE>
inline auto set_difference_append(IX xb, IX xe, IY yb, IY ye, vector<T>& a, FE fe) {
  return set_difference(xb, xe, yb, ye, back_inserter(a), fe);
}
template <class JX, class JY, class T>
inline auto setDifferenceAppend(const JX& x, const JY& y, vector<T>& a) {
  return set_difference_append(x.begin(), x.end(), y.begin(), y.end(), a);
}
template <class JX, class JY, class T, class FE>
inline auto setDifferenceAppend(const JX& x, const JY& y, vector<T>& a, FE fe) {
  return set_difference_append(x.begin(), x.end(), y.begin(), y.end(), a, fe);
}


template <class IX, class IY>
inline auto set_difference_vector(IX xb, IX xe, IY yb, IY ye) {
  using T = typename iterator_traits<IX>::value_type; vector<T> a;
  return set_difference_append(xb, xe, yb, ye, a);
}
template <class IX, class IY, class FE>
inline auto set_difference_vector(IX xb, IX xe, IY yb, IY ye, FE fe) {
  using T = typename iterator_traits<IX>::value_type; vector<T> a;
  return set_difference_append(xb, xe, yb, ye, a, fe);
}
template <class JX, class JY>
inline auto setDifferenceVector(const JX& x, const JY& y) {
  return set_difference_vector(x.begin(), x.end(), y.begin(), y.end());
}
template <class JX, class JY, class FE>
inline auto setDifferenceVector(const JX& x, const JY& y, FE fe) {
  return set_difference_vector(x.begin(), x.end(), y.begin(), y.end(), fe);
}




// UNIQUE-*
// --------

template <class I>
inline auto unique_values(I ib, I ie) {
  return unique(ib, ie);
}
template <class I, class FE>
inline auto unique_values(I ib, I ie, FE fe) {
  return unique(ib, ie, fe);
}
template <class J>
inline auto uniqueValues(J& x) {
  return unique_values(x.begin(), x.end());
}
template <class J, class FE>
inline auto uniqueValues(J& x, FE fe) {
  return unique_values(x.begin(), x.end(), fe);
}


template <class I>
inline auto sorted_unique(I ib, I ie) {
  sort(ib, ie);
  return unique(ib, ie);
}
template <class I, class FL, class FE>
inline auto sorted_unique(I ib, I ie, FL fl, FE fe) {
  sort(ib, ie, fl);
  return unique(ib, ie, fe);
}
template <class J>
inline auto sortedUnique(J& x) {
  return sorted_unique(x.begin(), x.end());
}
template <class J, class FL, class FE>
inline auto sortedUnique(J& x, FL fl, FE fe) {
  return sorted_unique(x.begin(), x.end(), fl, fe);
}




// MERGE-*
// -------

template <class IX, class IY, class IA>
inline auto merge_values(IX xb, IX xe, IY yb, IY ye, IA ab) {
  return merge(xb, xe, yb, ye, ab);
}
template <class IX, class IY, class IA, class FL>
inline auto merge_values(IX xb, IX xe, IY yb, IY ye, IA ab, FL fl) {
  return merge(xb, xe, yb, ye, ab, fl);
}
template <class JX, class JY, class JA>
inline auto mergeValues(const JX& x, const JY& y, JA& a) {
  return merge_values(x.begin(), x.end(), y.begin(), y.end(), a.begin());
}
template <class JX, class JY, class JA, class FL>
inline auto mergeValues(const JX& x, const JY& y, JA& a, FL fl) {
  return merge_values(x.begin(), x.end(), y.begin(), y.end(), a.begin(), fl);
}


template <class IX, class IY, class IA, class FL, class FE>
auto merge_unique(IX xb, IX xe, IY yb, IY ye, IA ab, FL fl, FE fe) {
  // `ab` points to the previous target value, unlike `xb` and `yb`.
  if (xb < xe && yb < ye) *ab = fl(*yb, *xb)? *(yb++) : *(xb++);
  else if (xb < xe) *ab = *(xb++);
  else if (yb < ye) *ab = *(yb++);
  else return ab;
  for (; xb < xe && yb < ye;) {
    if (fl(*yb, *xb)) { if (!fe(*yb, *ab)) { *(++ab) = *yb; } ++yb; }
    else              { if (!fe(*xb, *ab)) { *(++ab) = *xb; } ++xb; }
  }
  for (; xb < xe; ++xb)
    if (!fe(*xb, *ab)) *(++ab) = *xb;
  for (; yb < ye; ++yb)
    if (!fe(*yb, *ab)) *(++ab) = *yb;
  return ++ab;
}
template <class IX, class IY, class IA>
inline auto merge_unique(IX xb, IX xe, IY yb, IY ye, IA ab) {
  auto fl = [](const auto& a, const auto& b) { return a < b; };
  auto fe = [](const auto& a, const auto& b) { return a == b; };
  return merge_unique(xb, xe, yb, ye, ab, fl, fe);
}
template <class JX, class JY, class JA, class FL, class FE>
inline auto mergeUnique(const JX& x, const JY& y, JA& a, FL fl, FE fe) {
  return merge_unique(x.begin(), x.end(), y.begin(), y.end(), fl, fe);
}
template <class JX, class JY, class JA>
inline auto mergeUnique(const JX& x, const JY& y, JA& a) {
  return merge_unique(x.begin(), x.end(), y.begin(), y.end(), a.begin());
}


template <class IX, class IY, class FL>
auto merge_into(IX xb, IX xe, IY yb, IY ye, FL fl) {
  // `x` and `y` must be separate arrays, as `x` expands.
  IX ie = xe + (ye - yb);
  IX ix = xe - 1;
  IY iy = ye - 1;
  IX it = ie - 1;
  for (; iy >= yb; ++it) {
    if (fl(*iy, *ix)) { *it = *ix; --ix; }
    else              { *it = *iy; --iy; }
  }
  return ie;
}
template <class IX, class IY>
inline auto merge_into(IX xb, IX xe, IY yb, IY ye) {
  auto fl = [](const auto& a, const auto& b) { return a < b; };
  return merge_into(xb, xe, yb, ye, fl);
}
template <class JX, class JY, class FL>
inline auto mergeInto(JX& x, const JY& y, FL fl) {
  return merge_into(x.begin(), x.end(), y.begin(), y.end(), fl);
}
template <class JX, class JY>
inline auto mergeInto(JX& x, const JY& y) {
  return merge_into(x.begin(), x.end(), y.begin(), y.end());
}


template <class J>
inline auto inplaceMerge(const J& x, size_t m) {
  return inplace_merge(x.begin(), x.begin()+m, x.end());
}
template <class J, class FL>
inline auto inplaceMerge(const J& x, size_t m, FL fl) {
  return inplace_merge(x.begin(), x.begin()+m, x.end(), fl);
}




template <class IX, class IB, class FL, class FE>
auto inplace_merge_unique(IX xb, IX xm, IX xe, IB bb, IB be, FL fl, FE fe) {
  // `it` points to the previous target value, unlike `ib` and `im`.
  IX   it = xb, ib = xb, im = xm;
  auto bq = bounded_deque_view(bb, be);
  if (ib < xm && im < xe) {
    bq.push_back(*(ib++));
    *it = fl(*im, bq.front())? *(im++) : bq.pop_front();
  }
  else if (ib < xm) ++ib;
  else if (im < xe) ++im;
  else return it;
  for (; im < xe;) {
    if (ib < xm) bq.push_back(*(ib++));
    if (bq.empty()) break;
    if (fe(*it, bq.front())) { bq.pop_front(); continue; }
    if (fe(*it, *im))        { ++im;           continue; }
    *(++it) = fl(*im, bq.front())? *(im++) : bq.pop_front();
  }
  for (; !bq.empty(); bq.pop_front())
    if (!fe(*it, bq.front())) *(++it) = bq.front();
  for (; ib < xm; ++ib)
    if (!fe(*it, *ib)) *(++it) = *ib;
  for (; im < xe; ++im)
    if (!fe(*it, *im)) *(++it) = *im;
  return ++it;
}
template <class IX, class IB>
inline auto inplace_merge_unique(IX xb, IX xm, IX xe, IB bb, IB be) {
  auto fl = [](const auto& a, const auto& b) { return a < b; };
  auto fe = [](const auto& a, const auto& b) { return a == b; };
  return inplace_merge_unique(xb, xm, xe, bb, be, fl, fe);
}
template <class JX, class JB, class FL, class FE>
inline auto inplaceMergeUnique(JX& x, size_t m, JB& buf, FL fl, FE fe) {
  return inplace_merge_unique(x.begin(), x.begin()+m, x.end(), buf.begin(), buf.end(), fl, fe);
}
template <class JX, class JB>
inline auto inplaceMergeUnique(JX& x, size_t m, JB& buf) {
  return inplace_merge_unique(x.begin(), x.begin()+m, x.end(), buf.begin(), buf.end());
}
template <class JX, class T, class FL, class FE>
inline auto inplaceMergeUnique(JX& x, size_t m, vector<T>& buf, FL fl, FE fe) {
  size_t s = distance(x.begin()+m, x.end());
  if (buf.size() < s) buf.resize(s);
  return inplace_merge_unique(x.begin(), x.begin()+m, x.end(), buf.begin(), buf.end(), fl, fe);
}
template <class JX, class T>
inline auto inplaceMergeUnique(JX& x, size_t m, vector<T>& buf) {
  size_t s = distance(x.begin()+m, x.end());
  if (buf.size() < s) buf.resize(s);
  return inplace_merge_unique(x.begin(), x.begin()+m, x.end(), buf.begin(), buf.end());
}
