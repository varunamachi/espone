#!/bin/bash

if [ $# -eq 0 ] || [ "$1" = "set" ] ; then
    echo "Asking git to IGNORE changes to src/SecretsImpl.h"
    # git update-index --assume-unchanged src/Secrets.cpp
    git update-index --skip-worktree src/SecretsImpl.h
elif [ "$1" = "unset" ] ; then
    echo "Asking git to CONSIDER changes to src/SecretsImpl.cpp"
    # git update-index --no-assume-unchanged src/Secrets.cpp
    git update-index --no-skip-worktree src/SecretsImpl.cpp
fi