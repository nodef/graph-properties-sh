#pragma once
#include <string>

using std::string;




struct Options {
  bool   help;
  string error;
  string file;
  string format;
  bool components;
  bool blockgraph;
  bool chains;
  bool identicals;
};




string pathExtname(const string& path) {
  auto idx = path.rfind('.');
  return idx==string::npos? "" : path.substr(idx);
}


Options readOptions(int argc, char **argv) {
  Options a;
  for (int i=1; i<argc; ++i) {
    string k = argv[i];
    if (k=="--help") a.help = true;
    else if (k=="-f" || k=="--format") a.format = argv[++i];
    else if (k=="--components") a.components = true;
    else if (k=="--blockgraph") a.blockgraph = true;
    else if (k=="--chains")     a.chains     = true;
    else if (k=="--identicals") a.identicals = true;
    else if (k[0]=='-')       { a.error = "\'"+k+"\' is not an option";            break; }
    else if (!a.file.empty()) { a.error = "\'"+k+"\' file cannot be read as well"; break; }
    else a.file = k;
  }
  if (a.file.empty()) { a.error  = "no input file specified"; return a; }
  if (a.format.empty()) a.format = pathExtname(a.file).substr(1);
  if (a.format!="mtx" || a.format!="txt") { a.error = "\'"+a.format+"\' format is not recognized"; return a; }
  return a;
}
