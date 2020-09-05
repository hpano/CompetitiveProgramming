#/bin/bash

function write2bash_profile() {
  local bashpro=$(cat ~/.bash_profile)
  if [[ !(${bashpro} =~ "# competitive programing by hpano") ]]; then
    local yn
    read -p "[setting] Write PATHs to ~/.bash_profile now? [y/n]: " yn
    while [[ ${yn} != "y" ]] && [[ ${yn} != "n" ]]; do
      read -p "Answer only y or n [y/n]: " yn
    done
    if [[ ${yn} == "y" ]]; then
      echo "# competitive programing by hpano" >> ~/.bash_profile
      echo "export PATH=\$PATH:${dirpath}" >> ~/.bash_profile
      source ~/.bash_profile
      echo "[setting] Wrote PATHs to ~/.bash_profile"
    fi
  fi
}

function write2bashrc() {
  local bashrc=$(cat ~/.bashrc)
  if [[ !(${bashrc} =~ "# competitive programing by hpano") ]]; then
    local yn
    read -p "[setting] Write functions to ~/.bashrc now? [y/n]: " yn
    while [[ ${yn} != "y" ]] && [[ ${yn} != "n" ]]; do
      read -p "Answer only y or n [y/n]: " yn
    done
    if [[ ${yn} == "y" ]]; then
      echo "# competitive programing by hpano" >> ~/.bashrc
      echo "compp(){" >> ~/.bashrc
      echo "    . compp.sh $@" >> ~/.bashrc
      echo "}" >> ~/.bashrc
      source ~/.bashrc
      echo "[setting] Wrote functions to ~/.bashrc"
    fi
  fi
}

declare dirpath=$(dirname $0)

write2bash_profile
write2bashrc
chmod +x ${dirpath}/setting.sh
chmod +x ${dirpath}/add.sh
chmod +x ${dirpath}/compile.sh
chmod +x ${dirpath}/compp.sh
chmod +x ${dirpath}/remove.sh
chmod +x ${dirpath}/run.sh

echo "[setting] Finish setting"
