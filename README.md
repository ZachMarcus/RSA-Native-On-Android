# RSA-Native-On-Android
Code to run an OpenCL implementation of RSA encryption on android arm processors.

To get this running, do the following:

In Dependencies/lib/
There is one file called 
    libOpenCL.so
It may or may not work for your android device; if not, replace it with the version from your device.
I found mine in:
    /system/vendor/lib


    make
    adb push rsa.cl /data/local/tmp
    adb push rsaandroid /data/local/tmp
    adb shell
    chmod 555 /data/local/tmp/rsaandroid
    /data/local/tmp/rsaandroid
