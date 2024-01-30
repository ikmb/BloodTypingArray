#!/bin/bash

if [ $# -ne 1 ]
then
echo provide exactly one parameter. The name of the new class ...
exit -1
fi


cp CTemplate.h ${1}.h
cp CTemplate.cpp ${1}.cpp


sed -i "s/CTemplate/${1}/g" ${1}.*
