#/bin/bash

dirpath=$(pwd)
echo "# competitive programing" >> ~/.bash_profile
echo "export PATH=\$PATH:${dirpath}" >> ~/.bash_profile
source ~/.bash_profile

chmod +x setting.sh
chmod +x add.sh
chmod +x compile.sh
chmod +x compp.sh
chmod +x remove.sh
chmod +x run.sh
