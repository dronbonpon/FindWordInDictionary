configFilePath=$1

if [ ! -d "build" ]
then
    mkdir build
fi

cd build
echo "Cmake starts"
cmake -DCMAKE_BUILD_TYPE=Debug ../src/
echo "Cmake finished. Make starts"
make
echo "Make finished. Program starts"

./main ${configFilePath}