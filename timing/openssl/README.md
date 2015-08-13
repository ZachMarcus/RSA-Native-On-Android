###Intro
OpenSSL's RSA toolkit is capable of generating arbitrary length RSA keys and running encryptions/decryptions of arbitrary length data with those keys.

###Generate an RSA Keypair
1. Generate a private key
`openssl genrsa -out [private_out] [key_size]`
* [private_out] is a .pem file output location (ex. private.pem)
* [key_size] is the bitsize of the private key (ex. 4096)
2. Generate the corresponding public key
`openssl rsa -pubout -in [private_key_file] -out [public_out]`
* [private_key_file] is the .pem key file generated in the last step
* [public_out] is the output location of the public key (ex. public.pem)
3. Verify the key was generated correctly
`openssl rsa -text -in [private_key_file]`
* [private_key_file] is the .pem key file generated in step 1

###Encrypt Data (public key)
`openssl rsautl -in [plaintext_file] -out [cyphertext_file] -inkey [public_key_file] -pubin -encrypt`
* [plaintext_file] is a plaintext file to be encrypted
* [cyphertext_file] is the output file to write encrypted cyphertext to
* [public_key_file] is the public key (in .pem format) with which to encrypt the data

###Decrypt Data (private key)
`openssl rsautl -in [cyphertext_file] -out [plaintext_file] -inkey [private_key_file] -decrypt`
* [cyphertext_file] is a file consisting of cyphertext to decrypt
* [plaintext_file] is the output file to write decrypted plaintext to
* [private_key_file] is the private key (in .pem format) with which to decrypt the data

---

###Modified Source Code
The OpenSSL source code in `openssl-0.9.8_modified_src` has been modified to write the time taken by the decryption function, in nano seconds, to stdout. The script `timing_sample.sh` will run 16384 decryptions on random cyphertext, writing the timing data and cyphertext decrypted to a file (out.csv). This script uses a 2048 bit private key `private,pem` and it's corresponding public key `public.pem` with a public exponent of 65537 (`0x10000000000000001`) - this is the default public exponent selected by OpenSSL.

###Notes for running on Android
Follow the direction given here: https://wiki.openssl.org/index.php/Android to install the directory, noting that to do so, you must modify the `Setenv-android.sh` to contain the correct ANDROID_NDK Directory. 
Then, go into `openssl-1.0.2d_modified_src/test`.
Enter in:

    `arm-linux-androideabi-gcc --sysroot="$ANDROID_SYSROOT" -I/usr/local/ssl/android-19/include -pie -fPIE     ideatest.c -o     ideatest.exe /usr/local/ssl/android-19/lib/libcrypto.a`
    
The resulting binary will only run on an Android device





