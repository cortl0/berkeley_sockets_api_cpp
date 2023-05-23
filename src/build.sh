#
#   berkeley_sockets
#   created by Ilya Shishkin
#   cortl@8iter.ru
#   https://github.com/cortl0/berkeley_sockets
#   licensed by GPL v3.0
#

rm -r ./build
mkdir build
cd build
cmake ..
make
ctest --verbose
