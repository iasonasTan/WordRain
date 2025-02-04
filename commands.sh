cd ~/Documents/code/wordrain

# compile java:
javac -h . Main.java

# compile cpp:
# g++ -shared -fPIC -o libNativeLib.so -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" wordrain.cpp
g++ -shared -fPIC -o libNativeLib.so -I/opt/jdk-23/include -I/opt/jdk-23/include/linux wordrain.cpp

# run java:
./run.sh

# unknown maybe usefull
# nm -D libNativeLib.so | grep rainWord
# g++ -shared -fPIC -o libNativeLib.so -I/opt/jdk-23/include -I/opt/jdk-23/include/linux wordrain.cpp
