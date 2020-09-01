#!/bin/bash

declare -i argc=0
declare -a argv=()

cflags="-O2 -std=c++14 -fsanitize=undefined"

while test "$1" != ""; do
  case ${1} in
    *)
      ((++argc))
      argv=("${argv[@]}" "${1%.cpp}")
      shift
      ;;
  esac
done

if [ $argc -gt 0 ]; then
  for i in ${argv[@]}; do
    g++-10 ${cflags} ${i}.cpp -o ${i}.out && echo "[compile] Compiled ${i}.cpp to ${i}.out"
  done
fi
