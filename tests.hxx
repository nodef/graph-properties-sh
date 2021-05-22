#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include "src/main.hxx"
#include "setups.hxx"

using namespace std;




const char* testCopy() {
  DiGraph<> g;
  g.addEdge(1, 2);
  g.addEdge(2, 4);
  g.addEdge(4, 3);
  g.addEdge(3, 1);
  auto h = copy(g);

  if (!(
    h.order() == 4  &&
    h.size()  == 4  &&
    h.hasEdge(1, 2) &&
    h.hasEdge(2, 4) &&
    h.hasEdge(4, 3) &&
    h.hasEdge(3, 1)
  )) return "copy";
  return NULL;
}


const char* testTranspose() {
  DiGraph<> g;
  DiGraph<> h;
  g.addEdge(1, 2);
  g.addEdge(2, 4);
  g.addEdge(4, 3);
  g.addEdge(3, 1);
  transpose(g, h);

  if (!(
   h.order() == 4  &&
   h.size()  == 4  &&
   h.hasEdge(2, 1) &&
   h.hasEdge(4, 2) &&
   h.hasEdge(3, 4) &&
   h.hasEdge(1, 3)
  )) return "transpose";
  return NULL;
}


const char* testDfs() {
  vector<int> a {1, 2, 4, 3, 5, 6, 8, 7};
  vector<int> b {1, 2, 3, 4, 5};
  vector<int> c {1, 2, 3, 5, 4, 6};
  auto& g = MIN2C;
  auto& h = MIN2D;
  auto& i = MINNV;

  auto p = dfs(g, 1);
  auto q = dfs(h, 1);
  auto r = dfs(i, 1);
  if (p != a) return "dfsMin2c";
  if (q != b) return "dfsMin2d";
  if (r != c) return "dfsMinnv";
  return NULL;
}


const char* testComponents() {
  vector<vector<int>> a {{1, 3, 4, 2}, {5, 7, 8, 6}};
  vector<vector<int>> b {{1}, {4}, {5}, {2}, {3}};
  vector<vector<int>> c {{1, 3}, {5, 4, 6}, {2}};
  auto& g = MIN2C;
  auto& h = MIN2D;
  auto& i = MINNV;
  auto gt = transpose(g);
  auto ht = transpose(h);
  auto it = transpose(i);

  transpose(g, gt);
  transpose(h, ht);
  transpose(i, it);

  auto p = components(g, gt);
  auto q = components(h, ht);
  auto r = components(i, it);
  if (p != a) return "componentsMin2c";
  if (q != b) return "componentsMin2d";
  if (r != c) return "componentsMinnv";
  return NULL;
}


const char* testTopologicalSort() {
  vector<int> a {1, 2, 4, 5, 6, 8, 7, 3};
  vector<int> b {1, 4, 5, 2, 3};
  vector<int> c {1, 3, 5, 4, 6, 2};
  auto& g = MIN2C;
  auto& h = MIN2D;
  auto& i = MINNV;

  auto p = topologicalSort(g);
  auto q = topologicalSort(h);
  auto r = topologicalSort(i);
  if (p != a) return "topologicalSortMin2c";
  if (q != b) return "topologicalSortMin2d";
  if (r != c) return "topologicalSortMinnv";
  return NULL;
}

/*
const char* testIdenticals() {
  vector<vector<int>> a {{4, 5}, {7, 8}};
  DiGraph<> g;
  g.addEdge(1, 4);
  g.addEdge(1, 5);
  g.addEdge(2, 4);
  g.addEdge(2, 5);
  g.addEdge(3, 4);
  g.addEdge(3, 5);
  g.addEdge(3, 6);
  g.addEdge(4, 7);
  g.addEdge(4, 8);
  g.addEdge(5, 7);
  g.addEdge(5, 8);
  g.addEdge(7, 1);
  g.addEdge(8, 3);
  auto gt = transpose(g);

  auto p = inIdenticals(g, gt);
  if (p != a) return "inIdenticals";
  return NULL;
}


const char* testChains() {
  vector<vector<int>> a {{2, 3, 4}, {5, 6, 7}};
  DiGraph<> g;
  g.addEdge(1, 2);
  g.addEdge(1, 5);
  g.addEdge(2, 3);
  g.addEdge(3, 4);
  g.addEdge(5, 6);
  g.addEdge(6, 7);
  g.addEdge(4, 8);
  g.addEdge(7, 8);
  g.addEdge(8, 9);
  g.addEdge(9, 1);
  auto gt = transpose(g);

  auto p = chains(g, gt);
  if (p != a) return "chains";
  return NULL;
}
*/



void testAll() {
  vector<const char*> ts = {
    testCopy(),
    testTranspose(),
    testDfs(),
    testComponents(),
    testTopologicalSort()
  };
  int n = 0;
  for (auto& t : ts) {
    if (!t) continue;
    printf("ERROR: %s() failed!\n", t);
    n++;
  }
  printf("%d/%ld tests failed.\n", n, ts.size());
}
