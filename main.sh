src="graph-properties"
out="/home/resources/Documents/subhajit/$src.log"
ulimit -s unlimited
printf "" > "$out"

# Download program
rm -rf $src
git clone https://github.com/puzzlef/$src
cd $src

# Run
g++ -O3 main.cxx
stdbuf --output=L ./a.out                              2>&1 | tee -a "$out"
