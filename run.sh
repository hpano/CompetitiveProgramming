#!/bin/bash

function usage() {
  echo "Usage: $0 [OPTIONS] FILE"
  echo
  echo "Options:"
  echo "  -h, --help           Display available options."
  echo "  -c, --compile        Compile the FILE."
  echo "  -d. --debug          Compile as debug mode."
  echo "  -i, --input INPUT    Specify input file as INPUT."
  echo "  -n, --norun          Not run code test."
  echo "  -r, --remove         Remove the existing executable file."
  echo
  exit 1
}

declare -i argc=0
declare -a argv=()
declare hflag=false
declare cflag=false
declare dflag=false
declare iflag=false
declare nflag=false
declare rflag=false
declare in_file

while test "$1" != ""; do
  case $1 in
    -*)
      if [[ "$1" =~ 'h' ]] || [[ "$1" =~ '-help' ]]; then
        hflag=true
      fi
      if [[ "$1" =~ 'c' ]] || [[ "$1" =~ '-compile' ]]; then
        cflag=true
      fi
      if [[ "$1" =~ 'd' ]] || [[ "$1" =~ '-debug' ]]; then
        dflag=true
      fi
      if [[ "$1" =~ 'n' ]] || [[ "$1" =~ '-norun' ]]; then
        nflag=true
      fi
      if [[ "$1" =~ 'r' ]] || [[ "$1" =~ '-remove' ]]; then
        rflag=true
      fi
      if [[ "$1" =~ 'i' ]] || [[ "$1" =~ '-input' ]]; then
        iflag=true
        in_file=$2
        shift
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

for i in ${argv[@]}; do
  declare eval cmissflag_${i}=false
done

if "${hflag}"; then
  usage
  exit
fi
if "${rflag}"; then
  $(dirname $0)/remove.sh ${argv[@]}
fi
if "${cflag}"; then
  for i in ${argv[@]}; do
    if "${dflag}"; then
      $(dirname $0)/compile.sh -d ${i} || eval cmissflag_${i}=true
    else
      $(dirname $0)/compile.sh ${i} || eval cmissflag_${i}=true
    fi
  done
fi
if "${nflag}"; then
  exit
fi

for i in ${argv[@]}; do
  if eval '$cmissflag_'${i}; then
    continue
  fi
  if ! "${iflag}"; then
    in_file=${i}.in
  fi

  declare -a input=()
  declare -a output=()
  declare inflag=false
  declare outflag=false
  declare case_count=0
  declare ac_count=0
  declare wa_count=0
  declare slowest_time=0
  declare slowest_case

  echo "[run] Run ${i}.out < ${in_file}"
  # echo

  while read line; do
    if [ "${line}" == "<in>" ]; then
      inflag=true
      continue
    elif [ "${line}" == "</in>" ]; then
      inflag=false
      continue
    elif [ "${line}" == "<out>" ]; then
      outflag=true
      continue
    elif [ "${line}" == "</out>" ]; then
      outflag=false
      output[${case_count}]=`echo -e "${output[${case_count}]}"`
      case_count=$(( case_count + 1 ))
      continue
    fi

    if "${inflag}"; then
      input[${case_count}]+="${line}"" "
    elif "${outflag}"; then
      output[${case_count}]+="${line}""\n"
    fi
  done < ./${in_file}

  for j in `seq 0 $(( case_count - 1))`; do
    echo "[run] *** case `expr ${j} + 1` ***"
    # echo "[run] input:"
    # echo -e "${input[${j}]}"
    # echo "[run] output:"
    # echo -e "${output[${j}]}"

    declare start_time=`gdate +%s.%6N`
    declare result=$(./${i}.out << EOT
    ${input[${j}]}
EOT
    )
    declare end_time=`gdate +%s.%6N`
    declare process_time=`echo "scale=6; (${end_time} - ${start_time})" | bc`
    if [ `echo "${process_time} > ${slowest_time}" | bc` == 1 ]; then
      slowest_time=${process_time}
      slowest_case=$(( j + 1 ))
    fi

    echo "[run] time: ${process_time} sec"
    if [ "${output[${j}]}" = "${result}" ]; then
      ac_count=$(( ac_count + 1 ))
      echo -e "[run] \033[0;37;42m AC \033[0;39m"
    else
      wa_count=$(( wa_count + 1 ))
      echo -e "[run] \033[0;37;43m WA \033[0;39m"
      echo "output:"
      echo -e "${result}"
      echo "expected:"
      echo -e "${output[${j}]}"
    fi
  done

  echo "[run] slowest: ${slowest_time} sec  (case ${slowest_case})"
  echo "[run] AC rate: ${ac_count} / $(( ac_count + wa_count )) (AC / cases)"
done
