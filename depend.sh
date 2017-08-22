#!/bin/sh
DIR=$(sed -e "s@^src/@build/@" <<< $1)
shift 1
gcc -MM -MG "$@" |
sed -e "s@^\(.*\)\.o:@$DIR/\1.d \
$DIR/\1.o:@"
