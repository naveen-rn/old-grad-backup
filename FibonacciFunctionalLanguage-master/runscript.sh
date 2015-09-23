echo "Testing and Building Java code"
echo "-------------------------------"
cd Java
gradle
rm -rf build
rm -rf .clover
rm -rf .gradle
cd ..
echo "Testing and Building Scala code"
echo "-------------------------------"
cd Scala
source ./run.sh
cd ..
echo "Testing and Building Erlang code"
echo "-------------------------------"
cd Erlang
source ./run.sh
cd ..