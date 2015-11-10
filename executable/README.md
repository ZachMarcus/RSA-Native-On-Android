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
Compiling the code will generate a `crypto-rsa-gmp` binary
* To build it, run `ndk-build` in the `jni` directory
* You'll find the binary in `libs/armeabi/`
* We need to move this and some other components onto the android device
* Move that binary to `/data/local/tmp/`
* Move the two shared object libraries 
           (`libgmp.so` and `libgmpxx.so`, located in `jni`) to `/data/local/tmp`
* Move the kernel files onto Android: `/sdcard/RSA/`
* `adb shell` into the android device and cd to `/data/local/tmp`
* run `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/data/local/tmp/`
* For longer operations you'd like to leave running, you'll need nohup
* `nohup ./crypto-rsa-gmp &`
* You can find the output in `/sdcard/RSA/_________`
* Where ______ is something like `GMPMainOutput.txt`, `cMainOutput.txt`, or `clMainOutput.txt`

###Modifying the code
This is still under development. Other standard running operations will be added in.
Command line arguments will soon be added.
If it's necessary, more options can be added in `jni/crypto.cpp`



