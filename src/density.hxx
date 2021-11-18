#pragma once




// DENSITY
// -------
// Fully connectedness fraction.

template <class G>
float density(const G& x) {
  float N = x.order();
  return x.size()/(N*N);
}
