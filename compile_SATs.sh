PWD=$(pwd)

sudo apt install gcc -y
sudo apt install build-essential -y

cd $PWD/kissat_gb
./configure && make test

cd $PWD/kissat-MAB-1.0.3-79d8d8f2
./configure && make test

cd $PWD/lstech_maple/core
make
