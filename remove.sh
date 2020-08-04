#!/bin/bash

declare -i argc=0
declare -a argv=()

filename="*"
while test "$1" != ""; do
  case $1 in
    *)
      ((++argc))
      filename=${1%.cpp}
      argv=("${argv[@]}" "$filename")
      shift
      ;;
  esac
done

if [ $argc -gt 0 ]; then
  for i in ${argv[@]}; do
    rm ${i}.out && echo "[remove] Removed ${i}.out"
  done
else
  rm ${filename}.out && echo "[remove] Removed ${filename}.out"
fi
