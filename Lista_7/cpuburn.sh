#!/bin/bash

[ $# -eq 0 ] && {
    echo "usage: "$0" num_procs"  
    exit
}

function count_infinitely() {
    var=0
    while [[ $var%2=0 || $var%2=1 ]]
    do
        ((var++))
    done
    return var
}

for (( i=0; i<$1; i++))
do
    count_infinitely &
done