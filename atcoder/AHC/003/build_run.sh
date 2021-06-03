#!/bin/bash
set -eu

declare pg="b"

function exec() {
  declare file="0000${1}"
  unset out
  eval "$( (cd tools; cargo run --release --bin tester in/${file: -4}.txt ../${pg}.out) \
      2> >(out=$(cat); declare -p out) \
      1> ./tools/out/${file: -4}.txt )"

  # scores[${1}]=${out##*Score\ =\ }
  echo ${out##*Score\ =\ } > pipe${1}
}

declare -i size=100
declare -a scores=()
declare -i total_score=0
declare -i min_score=2312311000
declare -i max_score=0
declare -i min_case=0
declare -i max_case=0
declare file="0000.txt"

set +u
if [ ${1} ]; then
  size=${1}
fi
set -u

compile.sh ${pg}
echo "Run 0-$((-1+${size})) case"
for ((i=0; i < ${size}; i++)); do
  if [ -e pipe${i} ]; then
    rm pipe${i}
  fi
  mkfifo pipe${i}
  exec ${i} &
done

for ((i=0; i < ${size}; i++)); do
  # echo ${i}
  declare -i score=`cat pipe${i}`
  # echo ${score}
  total_score+=${score}
  if [ ${score} -lt ${min_score} ]; then
    min_score=${score}
    min_case=${i}
  fi
  if [ ${score} -gt ${max_score} ]; then
    max_score=${score}
    max_case=${i}
  fi
  rm pipe${i}
done

declare -i ave=$((${total_score} / ${size}))
declare msg="total: $(printf "%13d" ${total_score}), ave: $(printf "%10d" ${ave}), min: $(printf "%10d" ${min_score}) (case $(printf "%4d" ${min_case})), max: $(printf "%10d" ${max_score}) (case $(printf "%4d" ${max_case}))"
declare high_score=$(<high_score.txt)
high=${high_score##*ave:\ }
high=${high%%,\ min*}
echo "high   ${high_score}"
if [ ${ave} -gt ${high} ]; then
  echo -e "\033[0;32mRenew high score! ${high}->${ave}\033[0;39m"
  echo "${msg}" > high_score.txt
fi
echo "recent ${msg}"