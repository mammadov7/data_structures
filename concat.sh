#!/bin/bash
cp concat $1
cd $1
mkdir -p all_strips
for i in $(ls $1)
  do 
	if [[ $i == *.bmp && $i != concat.bmp ]];then 
		cp $i concat.bmp
		mv $i all_strips
		break
	fi
  done
for i in $(ls $1)
  do 
	if [[ $i == *.bmp && $i != concat.bmp ]];then 
		./concat $i concat.bmp
		mv $i all_strips
	fi
  done
rm $1/concat
