#!/bin/bash

declare -i argc=0
declare -a argv=()
declare cflags="-Wall -Wextra -O2 -std=c++17 -fsanitize=undefined -Wshadow -Wconversion -Wduplicated-cond -Wno-unknown-pragmas -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC"
declare dflag=false

while test "$1" != ""; do
  case ${1} in
    -*)
      if [[ "$1" =~ 'd' ]] || [[ "$1" =~ '-debug' ]]; then
        dflag=true
      fi
      shift
      ;;
    *)
      ((++argc))
      argv=("${argv[@]}" "${1%.cpp}")
      shift
      ;;
  esac
done

if "${dflag}"; then
  cflags+=" -D_DEBUG"
fi

if [ $argc -gt 0 ]; then
  for i in ${argv[@]}; do
    g++-11 ${cflags} ${i}.cpp -o ${i}.out && echo "[compile] Compiled ${i}.cpp to ${i}.out"
  done
fi
