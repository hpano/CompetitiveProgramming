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
        url_pre=${url_pre%%_beginner*}
        url_pre+="_"
      fi
      tmp_status=$(curl -Ls ${url_pre}a -o /dev/null -w '%{http_code}\n')
    fi
    if [ ${tmp_status} -eq 404 ]; then
      declare url_in
      url_pre="${url_pre%\/*}/"
      read -p "URL? > ${url_pre}" url_in
      if [ "${url_in: -1}" != "_" ]; then
        if [[ "${url_in: -2}" =~ _[a-z] ]]; then
          url_in=${url_in%_*}
        fi
        url_in+="_"
      fi
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
      if "${rflag}"; then
        rm ${name}.in
      else
        echo "[add] ${name}.in already exists"
        continue
      fi
    fi

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
          echo ${line} >> ${name}.in
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
  declare url_pre="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id="
  if [ ${path[1]} = "course" ]; then
    url_pre+="${path[2]}_"
  elif [ ${path[1]} = "contest" ]; then
    echo "[add] Not supported"
    exit 1
  fi

  for name in ${argv[@]}; do
    if [ -f ${name}.in ]; then
      if "${rflag}"; then
        rm ${name}.in
      else
        echo "[add] ${name}.in already exists"
        continue
      fi
    fi

    declare url=${url_pre}
    url+=$(echo ${name} | tr "[a-z]" "[A-Z]")
    declare status=$(curl -Ls ${url} -o /dev/null -w '%{http_code}\n')
    if [ ${status} -ne 200 ]; then
      echo "[add] Cannot recieve contents from ${url} (code: ${status})"
      continue
    fi

    declare data=$(curl -Lso- ${url})
    data=${data#*<[hH]1>}
    data=${data%%<h3 style="color:#aaa">Note</h3>*}
    declare inflag1=false
    declare inflag2=false
    declare outflag1=false
    declare outflag2=false
    touch ${name}.in
  
    echo "[add] Get from ${url}"
    while read line; do
      line=`echo ${line} | tr -d "\r"`
      if "${inflag1}"; then
        if [[ ${line} =~ "<pre>" ]]; then
          inflag1=false
          inflag2=true
        fi
      elif "${inflag2}"; then
        if [[ ${line} =~ "</pre>" ]]; then
          inflag2=false
          echo "</in>" >> ${name}.in
        else
          echo ${line} >> ${name}.in
        fi
      elif "${outflag1}"; then
        if [[ ${line} =~ "<pre>" ]]; then
          outflag1=false
          outflag2=true
        fi
      elif "${outflag2}"; then
        if [[ ${line} =~ "</pre>" ]]; then
          outflag2=false
          echo "</out>" >> ${name}.in
        else
          echo ${line} >> ${name}.in
        fi
      elif [[ ${line} =~ "2>Sample Input" ]] || [[ ${line} =~ "3>入力例" ]]; then
        echo "<in>" >> ${name}.in
        inflag1=true
      elif [[ ${line} =~ "2>Sample Output" ]] || [[ ${line} =~ "3>出力例" ]] || [[ ${line} =~ "2>Output for the Sample Input" ]]; then
        echo "<out>" >> ${name}.in
        outflag1=true
      fi
    done << END
    ${data}
END

    echo "[add] Added ${name}.in"
  done
}

function get_yukicoder() {
  declare url_pre="https://yukicoder.me/problems/no/"

  for name in ${argv[@]}; do
    if [ -f ${name}.in ]; then
      if "${rflag}"; then
        rm ${name}.in
      else
        echo "[add] ${name}.in already exists"
        continue
      fi
    fi

    declare url=${url_pre}
    url+=${name}
    declare status=$(curl -Ls ${url} -o /dev/null -w '%{http_code}\n')
    if [ ${status} -ne 200 ]; then
      echo "[add] Cannot recieve contents from ${url} (code: ${status})"
      continue
    fi

    declare data=$(curl -Lso- ${url})
    data=${data#*<h4 class=\"shadow\">サンプル</h4>}
    data=${data%%<input type=\"hidden\" name=\"csrf_token\"*}
    declare inflag=false
    declare outflag=false
    touch ${name}.in
  
    echo "[add] Get from ${url}"
    while read line; do
      line=`echo ${line} | tr -d "\r"`
      if "${inflag}"; then
        if [[ ${line} =~ "<pre>" ]]; then
          if [[ ${line} =~ "</pre>" ]]; then
            inflag=false
          fi
          line=$(echo "${line#*<pre>}" | sed s/\<br\ \\/\>/\\$'\n'/g | sed "s/<\\/pre>//g")
          echo "${line}" >> ${name}.in
          if !("${inflag}"); then
            echo "</in>" >> ${name}.in
          fi
        elif [[ ${line} =~ "</pre>" ]]; then
          inflag=false
          echo "</in>" >> ${name}.in
        else
          echo ${line} >> ${name}.in
        fi
      elif "${outflag}"; then
        if [[ ${line} =~ "<pre>" ]]; then
          if [[ ${line} =~ "</pre>" ]]; then
            outflag=false
          fi
          line=$(echo "${line#*<pre>}" | sed s/\<br\ \\/\>/\\$'\n'/g | sed "s/<\\/pre>//g")
          echo "${line}" >> ${name}.in
          if !("${outflag}"); then
            echo "</out>" >> ${name}.in
          fi
        elif [[ ${line} =~ "</pre>" ]]; then
          outflag=false
          echo "</out>" >> ${name}.in
        else
          echo ${line} >> ${name}.in
        fi
      elif [[ ${line} =~ "<h6>入力</h6>" ]]; then
        echo "<in>" >> ${name}.in
        inflag=true
      elif [[ ${line} =~ "<h6>出力</h6>" ]]; then
        echo "<out>" >> ${name}.in
        outflag=true
      fi
    done << END
    ${data}
END

    echo "[add] Added ${name}.in"
  done
}


declare -i argc=0
declare -a argv=()
declare rflag=false
while test "$1" != ""; do
  case $1 in
    -*)
      if [[ "$1" =~ 'r' ]] || [[ "$1" =~ '-remove' ]]; then
        rflag=true
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
  "AOJ")
    get_aoj
    ;;
  "yukicoder")
    get_yukicoder
    ;;
  *)
    echo "[add] ${path[0]} is unsupported"
    exit 1
    ;;
esac
