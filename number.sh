#!/bin/bash

for i in {1..50}; do
    if (( i % 2 == 0 )); then
        echo "### $i"
    else
        echo "$i"
    fi
    sleep 0.1
done
