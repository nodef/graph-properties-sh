#include <string>
#include <vector>
#include <iostream>
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


int main(int argc, char **argv) {
  Options o = readOptions(argc, argv);
  printf("Using graph %s ...\n", o.file);
  printf("\n");
  return 0;
}
