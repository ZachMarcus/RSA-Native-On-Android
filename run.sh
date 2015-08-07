#!/bin/bash
t=1
while [ $t -le 100 ]; do
    ./rsaandroid
    let t=t+1
done
