#include <algorithm>
#include "src/main.hxx"
#include "setups.hxx"
#include "tests.hxx"

using namespace std;




void runProperties(const char *pth) {
  auto x  = readMtx(pth); println(x);
  auto xt = transposeWithDegree(x); print(xt); printf(" (transposeWithDegree)\n");
  if (x.order()==0) return;
  auto odegs = degrees(x); auto idegs = degrees(xt);
  printf("out-degree: min: %d max: %d avg: %d\n", minValue(odegs), maxValue(odegs), avgValue(odegs));
  printf("in-degree:  min: %d max: %d avg: %d\n", minValue(idegs), maxValue(idegs), avgValue(idegs));
}

int main(int argc, char **argv) {
  setupAll();
  testAll();
}
