#!/bin/bash

if [ $# -eq 0 ] || [ "$1" = "set" ] ; then
    echo "Asking git to IGNORE changes to src/Secrets.cpp"
    git update-index --assume-unchanged src/Secrets.cpp
elif [ "$1" = "unset" ] ; then
    echo "Asking git to CONSIDER changes to src/Secrets.cpp"
    git update-index --no-assume-unchanged src/Secrets.cpp
fi