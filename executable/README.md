###Android Executable
This section contains everything necessary to run an executable on Android through adb
It currently contains options to run something using OpenCL and GMPlib

####Requirements
* Eclipse CDT (C/C++ Development)
* Eclipse ADT (Android Development)
* Android SDK 21
* Android NDK

####Options
* RSA, singlethreaded, standard precision
* RSA, multithreaded, standard precision
* RSA, singlethreaded, arbitrary precision

####Running the executable
Compiling the code will generate a 'crypto-rsa-gmp' binary
* To build it, run 'ndk-build' in the 'jni' directory
* You'll find the binary in 'libs/armeabi/'

###Modifying the code
This is still under development. Other standard running operations will be added in.
Command line arguments will soon be added.
If it's necessary, most modifications can be made in 'jni/crypto.cpp'



