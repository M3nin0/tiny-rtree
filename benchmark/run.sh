#!/bin/bash

set -e 

cmake .
make
clear

echo "Executando os testes"
sleep 5
./trtree_benchmark
