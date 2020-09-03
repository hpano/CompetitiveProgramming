#!/bin/bash

function get_atcoder() {
  declare url_pre="https://atcoder.jp/contests/"
  if [ ${path[1]} = "other" ]; then
    url_pre+=$(echo ${path[2]} | tr "[A-Z]" "[a-z]")
    url_pre+="/tasks/"
    url_pre+=$(echo ${path[2]}_ | tr "[A-Z-]" "[a-z_]")
    declare tmp_status=$(curl -Ls ${url_pre}a -o /dev/null -w '%{http_code}\n')
    if [ ${tmp_status} -eq 404 ]; then
      if [[ ${url_pre} =~ "beginner" ]]; then
        url_pre=${url_pre%%-beginner*}
        url_pre+="_"
      fi
      tmp_status=$(curl -Ls ${url_pre}a -o /dev/null -w '%{http_code}\n')
    fi
    if [ ${tmp_status} -eq 404 ]; then
      declare url_in
      url_pre="${url_pre%\/*}/"
      read -p "URL? > ${url_pre}" url_in
      url_pre+=${url_in}
    fi
  else
    url_pre+=$(echo ${path[1]} | tr "[A-Z]" "[a-z]")
    url_pre+=$(echo "${path[2]}/tasks/")
    url_pre+=$(echo ${path[1]} | tr "[A-Z]" "[a-z]")
    url_pre+=$(echo "${path[2]}_")
  fi

  for name in ${argv[@]}; do
    if [ -f ${name}.in ]; then
      # rm ${name}.in  # for debug
      echo "[add] ${name}.in already exists"
      continue
    fi

    # if [ ${name} = "test" ]; then
    #   url="https://atcoder.jp/contests/abc177/tasks/abc177_d"
    # fi
    declare url=${url_pre}
    url+=${name}
    declare url2=${url_pre}
    url2+=$(echo ${name} | tr "[a-f]" "[1-6]")
    declare url2flag=false
    declare status=$(curl -Ls ${url} -o /dev/null -w '%{http_code}\n')
    if [ ${status} -eq 404 ]; then
      url2flag=true
      sleep 0.5
      status=$(curl -Ls ${url2} -o /dev/null -w '%{http_code}\n')
    fi
    if [ ${status} -ne 200 ]; then
      echo "[add] Cannot recieve contents from ${url} (code: ${status})"
      continue
    fi
    if "${url2flag}"; then
      url=${url2}
    fi

    declare data=$(curl -Lso- ${url})
    data=${data#*<span class=\"lang-ja\">}
    data=${data%%</span>*}
    declare inflag=false
    declare outflag=false
    touch ${name}.in
    
    echo "[add] Get from ${url}"
    while read line; do
      line=`echo ${line} | tr -d "\r"`
      if "${inflag}"; then
        if [[ ${line} =~ "</pre>" ]]; then
          inflag=false
          echo "</in>" >> ${name}.in
        else
          declare tmp=${line}
          echo -e "${tmp}" >> ${name}.in
        fi
      elif "${outflag}"; then
        if [[ ${line} =~ "</pre>" ]]; then
          outflag=false
          echo "</out>" >> ${name}.in
        else
          echo ${line} >> ${name}.in
        fi
      elif [[ ${line} =~ "<h3>入力例" ]]; then
        echo "<in>" >> ${name}.in
        inflag=true
        echo ${line#*<pre>} >> ${name}.in
      elif [[ ${line} =~ "<h3>出力例" ]]; then
        echo "<out>" >> ${name}.in
        outflag=true
        echo ${line#*<pre>} >> ${name}.in
      fi
    done << END
    ${data}
END

    echo "[add] Added ${name}.in"
  done
}

function get_aoj() {
  declare url_pre="http://judge.u-aizu.ac.jp/onlinejudge/finder.jsp?course=DPL"
}


declare -i argc=0
declare -a argv=()
while test "$1" != ""; do
  case $1 in
    *)
      ((++argc))
      argv=("${argv[@]}" "${1%.cpp}")
      shift
      ;;
  esac
done

for name in ${argv[@]}; do
  if [ -f ${name}.cpp ]; then
    echo "[add] ${name}.cpp already exists"
    continue
  fi

  cp $(dirname $0)/template.cpp ${name}.cpp && \
  echo "[add] Added ${name}.cpp"
done

declare path=( $(pwd | sed -e "s/.*competitive_programming\///g" | tr "/" " ") )
case ${path[0]} in
  "atcoder")
    get_atcoder
    ;;
  *)
    echo "[add] ${path[0]} is unsupported"
    exit 1
    ;;
esac
