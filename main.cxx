#include <tuple>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "src/main.hxx"
#include "options.hxx"

using namespace std;


// void runPagerank(const string& data, int repeat) {
//   int M = countLines(data), steps = 10;
//   printf("Temporal edges: %d\n", M);
//   for (int batch=10, i=0; batch<M; batch*=i&1? 2:5, i++) {
//     int skip = max(M/steps - batch, 0);
//     printf("\n# Batch size %.0e\n", (double) batch);
//     runPagerankBatch(data, repeat, skip, batch);
//   }
// }


// SHOW
// ----

auto groupDetails(const vector2d<int>& gs) {
  int gmin = gs.empty()? 0 : gs[0].size();
  int gmax = 0, GS = gs.size(), GE = 0;
  for (const auto& g : gs) {
    int G = g.size();
    if (G<gmin) gmin = G;
    if (G>gmax) gmax = G;
    GE += G;
  }
  return make_tuple(GS, gmin, gmax, GE/float(GS));
}


template <class G>
void showBasics(const char *pre, const G& x) {
  printf("- %sorder:   %d (vertices)\n",        pre, x.order());
  printf("- %ssize:    %d (edges)\n",           pre, x.size());
  printf("- %sspan:    %d (vertex-id limit)\n", pre, x.span());
  printf("- %sdensity: %e (fully connectedness fraction)", pre, density(x));
}

template <class G, class H>
void showDegree(const char *pre, const G& x, const H& xt) {
  printf("- %sdegree-min:   %d (minimum out-degree)\n", pre, minDegree(x));
  printf("- %sdegree-max:   %d (maximum out-degree)\n", pre, maxDegree(x));
  printf("- %sdegree-avg:   %d (average out-degree)\n", pre, avgDegree(x));
  printf("- %sindegree-min: %d (minimum in-degree)\n",  pre, minDegree(xt));
  printf("- %sindegree-max: %d (maximum in-degree)\n",  pre, maxDegree(xt));
  printf("- %sindegree-avg: %d (average in-degree)\n",  pre, avgDegree(xt));
}

template <class G, class H>
void showSpecial(const char *pre, const G& x, const H& xt) {
  printf("- %sdead-ends:      %d (vertices with no outgoing edges)\n", pre, deadEndCount(x));
  printf("- %sdead-ends-rec:  %d (vertices pointing to dead ends)\n",  pre, recursiveDeadEndCount(x));
  printf("- %sbeginnings:     %d (vertices with no incoming edges)\n", pre, deadEndCount(xt));
  printf("- %sbeginnings-rec: %d (vertices pointed by beginnings)\n",  pre, recursiveDeadEndCount(xt));
  printf("- %sself-loops:     %d (vertices pointing to self)\n",       pre, selfLoopCount(x));
}

template <class G, class H>
void showDepth(const char *pre, const G& x, const H& xt) {
  printf("- %sdepth-min: %d (minimum path length from beginnings)\n", pre, minDepth(x, xt));
  printf("- %sdepth-max: %d (maximum path length from beginnings)\n", pre, maxDepth(x, xt));
  printf("- %sdepth-avg: %f (average path length from beginnings)\n", pre, avgDepth(x, xt));
}

template <class G, class H>
void showComponents(const char *pre, const G& x, const H& xt) {
  auto [cnum, cmin, cmax, cavg] = groupDetails(components(x, xt));
  printf("- %scomponents:    %d (strongly connected)\n",     pre, cnum);
  printf("- %scomponent-min: %d (minimum component size)\n", pre, cmin);
  printf("- %scomponent-max: %d (maximum component size)\n", pre, cmax);
  printf("- %scomponent-avg: %f (average component size)\n", pre, cavg);
}

template <class G, class H>
void showInIdenticals(const char *pre, const G& x, const H& xt) {
  auto [inum, imin, imax, iavg] = groupDetails(inIdenticals(x, xt));
  printf("- %sinidenticals:    %d (vertices with identical in-edges)\n", pre, inum);
  printf("- %sinidentical-min: %d (minimum in-identical size)\n", pre, imin);
  printf("- %sinidentical-max: %d (maximum in-identical size)\n", pre, imax);
  printf("- %sinidentical-avg: %f (average in-identical size)\n", pre, iavg);
}

template <class G, class H>
void showOutIdenticals(const char *pre, const G& x, const H& xt) {
  auto [inum, imin, imax, iavg] = groupDetails(inIdenticals(xt, x));
  printf("- %soutidenticals:    %d (vertices with identical out-edges)\n", pre, inum);
  printf("- %soutidentical-min: %d (minimum in-identical size)\n", pre, imin);
  printf("- %soutidentical-max: %d (maximum in-identical size)\n", pre, imax);
  printf("- %soutidentical-avg: %f (average in-identical size)\n", pre, iavg);
}

template <class G, class H>
void showChains(const char *pre, const G& x, const H& xt) {
  auto [cnum, cmin, cmax, cavg] = groupDetails(chains(xt, x));
  printf("- %schains:    %d (vertices connected in a line)\n", pre, cnum);
  printf("- %schain-min: %d (minimum in-identical size)\n", pre, cmin);
  printf("- %schain-max: %d (maximum in-identical size)\n", pre, cmax);
  printf("- %schain-avg: %f (average in-identical size)\n", pre, cavg);
}

template <class G, class H>
void showBlockgraph(const char *pre, const G& x, const H& xt) {
  auto cs = components(x, xt);
  auto b  = blockgraph(x, cs);
  auto bt = transposeWithDegree(b);
  string sf(pre); sf += "blockgraph-";
  const char *prf = sf.c_str();
  showBasics (prf, b);
  showDegree (prf, b, bt);
  showSpecial(prf, b, bt);
  showDepth  (prf, b, bt);
}




// RUN-MTX
// -------

void runMtx(const Options& o) {
  typedef GraphTransform T;
  printf("Loading graph %s ...\n", o.file.c_str());
  auto x  = readMtx(o.file.c_str()); println(x);
  switch (o.transform) {
    default: break;
    case T::IDENTITY: break;
    case T::LOOP_DEADENDS:
      selfLoopTo(x, [&](int u) { return isDeadEnd(x, u); });
      print(x); printf(" (loopDeadEnds)\n"); break;
    case T::LOOP_VERTICES:
      selfLoopTo(x, [&](int u) { return true; });
      print(x); printf(" (loopVertices)\n"); break;
  }
  auto xt = transposeWithDegree(x);
  print(xt); printf(" (transposeWithDegree)\n");
  showBasics ("", x);
  showDegree ("", x, xt);
  showSpecial("", x, xt);
  showDepth  ("", x, xt);
  if (o.components) showComponents   ("", x, xt);
  if (o.identicals) showInIdenticals ("", x, xt);
  if (o.identicals) showOutIdenticals("", x, xt);
  if (o.chains)     showChains       ("", x, xt);
  if (o.blockgraph) showBlockgraph   ("", x, xt);
}




// RUN-SNAP
// --------

void runSnap(const Options& o) {
}




// MAIN
// ----

int main(int argc, char **argv) {
  typedef FileFormat F;
  Options o = readOptions(argc, argv);
  if (o.help)           { printf("%s\n\n", helpMessage()); return 0; }
  if (!o.error.empty()) { printf("error: %s\n\n%s\n\n", o.error.c_str(), helpMessage()); return 1; }
  switch (o.format) {
    default: break;
    case F::FIXED_MTX:    runMtx(o);  break;
    case F::TEMPORAL_TXT: runSnap(o); break;
  }
  printf("\n");
  return 0;
}
