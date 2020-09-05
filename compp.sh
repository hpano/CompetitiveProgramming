#/bin/bash

function usage() {
  echo "Usage: . $0 [OPTIONS] FILEs"
  echo
  echo "Options:"
  echo "  -h, --help                   Display available options."
  echo "  -d, --directory DIRECTORYs   Write the directory hierarchy where the program is placed."
  echo "  -f, --file FILEs             Write the file name to create."
  echo
  exit 1
}

declare -a directorys=()
declare -a files=()
declare hflag=false
declare in_file

while test "$1" != ""; do
  case $1 in
    -*)
      if [[ "$1" =~ 'h' ]] || [[ "$1" =~ '-help' ]]; then
        hflag=true
      elif [[ "$1" =~ 'd' ]] || [[ "$1" =~ '-directory' ]]; then
        while [[ $2 != -* ]] && [[ $2 != "" ]]; do
          directorys+=($2)
          shift
        done
      elif [[ "$1" =~ 'f' ]] || [[ "$1" =~ '-file' ]]; then
        while [[ $2 != -* ]] && [[ $2 != "" ]]; do
          if [[ $2 =~ "." ]] && [[ $2 != *.cpp ]]; then
            echo "[compp] Invalid file $2 !"
            echo "        You can input *.cpp or *"
            exit 1
          fi
          files+=(${2%.cpp})
          shift
        done
      else
        echo "[compp] Invalid option $1 !"
        usage
        exit 1
      fi
      shift
      ;;
    *)
      echo "[compp] Invalid input $1 !"
      usage
      exit 1
      ;;
  esac
done

directorys=(${directorys[@]//// })

if "${hflag}"; then
  usage
  exit
fi

declare rootpath=$(which compp.sh)
if [[ ${rootpath} == "" ]]; then
  read -p "[compp] Input competitive programing directory's root path or 'n' to give up cd: " rootpath
fi
if [[ ${rootpath} == "n" ]]; then
  rootpath=$(pwd)
elif [[ ${rootpath: -3} == ".sh" ]]; then
  rootpath=${rootpath%\/*}
fi

declare yn
cd ${rootpath}
for dir in ${directorys[@]}; do
  if [[ -d ${dir} ]]; then
    cd ${dir}
  else
    read -p "[compp] Directory '${dir}' not exists. make? [y/n]: " yn
    if [[ ${yn} == "y" ]]; then
      mkdir ${dir} && cd ${dir}
    fi
  fi
done
echo "[compp] Now at $(pwd)"

declare addpath=$(which add.sh)
if [[ ${addpath} == "" ]]; then
  read -p "[compp] Input add.sh path or 'n' to give up add file: " addpath
fi
if [[ ${addpath} == "n" ]]; then
  exit 1
elif [[ ${addpath: -3} != ".sh" ]]; then
  if [[ ${addpath: -1} != "/" ]]; then
    addpath+="/"
  fi
  addpath+="add.sh"
fi

${addpath} ${files[@]}
