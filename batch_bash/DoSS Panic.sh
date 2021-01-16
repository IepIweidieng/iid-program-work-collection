#! /bin/bash

function doScriptPanic(){  ##(void)->(void)
    for ((a=1; a<=4; ++a)); do
        pkill -u "$(whoami)" "DoS Simulator" >/dev/null 2>&1
    done

    return
}

#main  ##(str[])->(int)
    if [[ "$1" != "" ]]; then doScriptPanic; exit 0; fi
    "$0" SP &
    pkill -u "$(whoami)" "DoS Simulator" >/dev/null 2>&1

    exit 0