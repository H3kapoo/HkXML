set -xe
CXX=$(which g++-14) cmake -B artifacts -GNinja .
cmake --build artifacts -j8
mv debug/xmlParser .
rm -rf debug
