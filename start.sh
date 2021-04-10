if [ ! -d "debug" ]
then
    mkdir debug
fi

if [ ! -d "release" ]
then
    mkdir release
fi

echo "Cmake starts for debug"
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ../src/
cd ../release
echo "Cmake starts for release"
cmake ../src/
cd ..

echo "Cmake finished. Make starts for debug"
cd debug
make
cd ../release
echo "Make starts for release"
make
echo "Make finished"
cd ..