SATHOME=$(pwd)

sudo apt install gcc -y
sudo apt install build-essential -y

echo
echo Compiling kissat_gb...
cd $SATHOME/kissat_gb
./configure && make test

echo
echo Compiling kissat_MAB...
cd $SATHOME/kissat-MAB-1.0.3-79d8d8f2
./configure && make test

echo
echo Compiling lstech_maple...
cd $SATHOME/lstech_maple/core
make

echo $SATHOME
echo
echo Compiling brute_force...
cd $SATHOME/brute_force
make