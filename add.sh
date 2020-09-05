#!/bin/bash

function make_cpp_file() {
  for name in ${argv[@]}; do
    if [ -f ${name}.cpp ]; then
      echo "[add] ${name}.cpp already exists"
      continue
    fi

    cp $(dirname $0)/template.cpp ${name}.cpp && \
    echo "[add] Added ${name}.cpp"
  done
}

function get_atcoder() {
  make_cpp_file

  local url_pre="https://atcoder.jp/contests/"
  # URLの前処理 企業コンなどotherの場合は特別
  if [ ${path[1]} = "other" ]; then
    url_pre+=$(echo ${path[2]} | tr "[A-Z]" "[a-z]")
    url_pre+="/tasks/"
    url_pre+=$(echo ${path[2]}_ | tr "[A-Z-]" "[a-z_]")
    local tmp_status=$(curl -Ls ${url_pre}a -o /dev/null -w '%{http_code}\n')
    if [ ${tmp_status} -eq 404 ]; then
      if [[ ${url_pre} =~ "beginner" ]]; then
        url_pre=${url_pre%%_beginner*}
        url_pre+="_"
      fi
      tmp_status=$(curl -Ls ${url_pre}a -o /dev/null -w '%{http_code}\n')
    fi
    if [ ${tmp_status} -eq 404 ]; then
      local url_in
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

  # 各問題に対してデータ取得とinファイル作成
  for name in ${argv[@]}; do
    if [ -f ${name}.in ]; then
      if "${rflag}"; then
        rm ${name}.in
      else
        echo "[add] ${name}.in already exists"
        continue
      fi
    fi

    local url=${url_pre}
    url+=${name}
    local url2=${url_pre}
    url2+=$(echo ${name} | tr "[a-f]" "[1-6]")
    local url2flag=false
    local continue_flag=false
    local status=$(curl -Ls ${url} -o /dev/null -w '%{http_code}\n')
    if [ ${status} -eq 404 ]; then
      url2flag=true
      sleep 0.5
      status=$(curl -Ls ${url2} -o /dev/null -w '%{http_code}\n')
    fi
    while [ ${status} -ne 200 ]; do
      echo "[add] Cannot recieve contents from ${url} (code: ${status})"
      read -p "Input correct URL or 'n' to give up getting: " url
      status=$(curl -Ls ${url} -o /dev/null -w '%{http_code}\n')
      url2flag=false
      if [[ ${url} == "n" ]]; then
        continue_flag=true
        break
      fi
    done
    if "${continue_flag}"; then
      continue
    fi
    if "${url2flag}"; then
      url=${url2}
    fi

    local data=$(curl -Lso- ${url})
    data=${data#*<span class=\"lang-ja\">}
    data=${data%%</span>*}
    local inflag=false
    local outflag=false
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
  make_cpp_file

  local url_pre="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id="
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

    local url=${url_pre}
    url+=$(echo ${name} | tr "[a-z]" "[A-Z]")
    local continue_flag=false
    local status=$(curl -Ls ${url} -o /dev/null -w '%{http_code}\n')
    while [ ${status} -ne 200 ]; do
      echo "[add] Cannot recieve contents from ${url} (code: ${status})"
      read -p "Input correct URL or 'n' to give up getting: " url
      status=$(curl -Ls ${url} -o /dev/null -w '%{http_code}\n')
      if [[ ${url} == "n" ]]; then
        continue_flag=true
        break
      fi
    done
    if "${continue_flag}"; then
      continue
    fi

    local data=$(curl -Lso- ${url})
    data=${data#*<[hH]1>}
    data=${data%%<h3 style="color:#aaa">Note</h3>*}
    local inflag1=false
    local inflag2=false
    local outflag1=false
    local outflag2=false
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
  make_cpp_file

  local url_pre="https://yukicoder.me/problems/no/"

  for name in ${argv[@]}; do
    if [ -f ${name}.in ]; then
      if "${rflag}"; then
        rm ${name}.in
      else
        echo "[add] ${name}.in already exists"
        continue
      fi
    fi

    local url=${url_pre}
    url+=${name}
    local continue_flag=false
    local status=$(curl -Ls ${url} -o /dev/null -w '%{http_code}\n')
    while [ ${status} -ne 200 ]; do
      echo "[add] Cannot recieve contents from ${url} (code: ${status})"
      read -p "Input correct URL or 'n' to give up getting: " url
      status=$(curl -Ls ${url} -o /dev/null -w '%{http_code}\n')
      if [[ ${url} == "n" ]]; then
        continue_flag=true
        break
      fi
    done
    if "${continue_flag}"; then
      continue
    fi

    local data=$(curl -Lso- ${url})
    data=${data#*<h4 class=\"shadow\">サンプル</h4>}
    data=${data%%<input type=\"hidden\" name=\"csrf_token\"*}
    local inflag=false
    local outflag=false
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
      argv=("${argv[@]}" "${1%.cpp}")
      shift
      ;;
  esac
done

declare path=( $(pwd | sed -e "s/.*competitive_programming//g" | tr "/" " ") )
if [[ ${path: 0: 1} == "/" ]]; then
  path=${path: 1}
fi
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
