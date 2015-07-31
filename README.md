# RSA-Native-On-Android
Code to run an OpenCL implementation of RSA encryption on android arm processors

To get this running, do the following:

    make
    adb push rsa.cl /data/local/tmp
    adb push rsaandroid /data/local/tmp
    adb shell
    chmod 555 /data/local/tmp/rsaandroid
    /data/local/tmp/rsaandroid
