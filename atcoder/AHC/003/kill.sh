#!/bin/bash

for ((i=49208; i < 49330; i++)); do
  declare res=$(ps -a | grep ${i} | grep build_run.sh)
  if [ "${res}" != "" ]; then
    kill ${i}
  fi
done
