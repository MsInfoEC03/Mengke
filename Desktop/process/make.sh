#!/bin/bash

# 编译某个c文件为可执行文件./make.sh path xxx.c
# 编译当前目录下所有c文件，并链接成一个可执行文件./make.sh path all
# 清除所有的编译临时文件 .o /make.sh path clean

name=$2
path=$1

if [ ${name#*.} == $name ]
then
    if [ $name == "clean" ]
    then
        rm -f $path/*.o
    else
	for file in `ls | find $path -name '*.c'`
	do
	    nume_o=$(basename $file .c) 
	    gcc -c $file -o ${nume_o}.o	  
            sum_o="${nume_o}.o $sum_o"
	done
        gcc $sum_o -o $name
    fi  
else
    if [ ${name#*.} == "c" ]
    then
    #    echo $name
        num=$(basename $name .c) 
        gcc $path/$name -o $num -lpthread
   fi
fi
 
