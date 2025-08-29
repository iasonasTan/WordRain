cd $1

# compile java:
javac -h . Main.java

# compile cpp:
g++ -shared -fPIC -o libNativeLib.so -I$2/include -I$2/include/linux wordrain.cpp

# run java
java -Djava.library.path=. Main

# remove .class files
rm *.class
rm Main_WordRain.h
rm message.txt
rm libNativeLib.so