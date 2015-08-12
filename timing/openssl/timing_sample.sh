#!/bin/bash

# Write a file header
echo cyphertext,time_ns > out.csv

i=1
while [ $i -le 16384 ]
do
# Generate a random, 32 character plaintext consisting of uppercase and lowercase letters and numbers
plaintext=`cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1`
# Write the plaintext to a file
echo $plaintext > plaintext
# Get the value of the plaintext in hex (optional)
#plaintext_hex=`cat plaintext | hexdump -e '16/1 "%02x"'; printf "\n"`

# Encrypt the plaintext, writing the output to a file
./openssl-0.9.8_modified_src/apps/openssl rsautl -in plaintext -out cyphertext -inkey public.pem -pubin -encrypt
# Get the hex value of the cyphertext
cyphertext_hex=`cat cyphertext | hexdump -e '16/1 "%02x"'; printf "\n"`

# Decrypt the cryphertext and write the output to a file, recording the time taken
time=`./openssl-0.9.8_modified_src/apps/openssl rsautl -in cyphertext -out decrypted -inkey private.pem -decrypt`

# Write the data to out data file
echo $cyphertext_hex,$time >> out.csv

# Print the number of samples that have been taken
printf "\rSamples Compete: $i"

i=$[$i+1]
done

printf "\n"
