#!/bin/bash

executable="/data/local/tmp/rsac"
#executable="./rsac"

# Key values calculated by another script
p=239
q=241
e=56897
d=47891
n=57599

echo value,clock_ticks,time > out.csv

t=1
while [ $t -le 10000 ]; do
	val=""
        i=1
        while [ $i -le 16 ]; do
		val=$val$(($RANDOM%2))
                let i=i+1
	done
	time=`$executable $d $n $val`

	echo $val,$time	>> out.csv
        #printf "\rSamples Complete: $t"
        echo "\rSamples Complete: $t"
        let t=t+1
done

