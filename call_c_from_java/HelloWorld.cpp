#include <jni.h>
#include <iostream>
#include "HelloWorld.h"
using namespace std;
 
JNIEXPORT void JNICALL 
Java_HelloWorld_print(JNIEnv *, jobject){
    cout << "Hello, JNI!\n";
    return;
}

/*jni.h path: echo $JAVA_HOME
export JAVA_HOME="$(/usr/libexec/java_home -v 9.0)"
gcc -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/darwin/" -o libjniexample.jnilib -shared HelloWorld.cpp
*/
