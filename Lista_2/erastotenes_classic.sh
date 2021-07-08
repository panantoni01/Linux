#!/bin/bash

primes=(2)
n=3
while [[ $n -le $1 ]]
do
	j=0
	while [[ ${primes[$j]}*${primes[$j]} -le $n ]]
	do
		if [[ $(( $n % ${primes[$j]} )) -eq 0 ]]
		then
			((n++))
			continue 2	
		fi
		((j++))
	done
	primes+=($n)
	((n++))
done

echo ${primes[@]}
