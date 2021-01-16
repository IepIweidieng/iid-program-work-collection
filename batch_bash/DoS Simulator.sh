#! /bin/bash

LIMIT=10

#main  ##(str[])->(int)
    n=$1
    : $((++n))

    if (($n < $LIMIT)); then
        "$0" $n | "$0" $n
    elif (($n == $LIMIT)); then
        read -n1 -rp "Press any key to continue..." key
    fi

    exit 0