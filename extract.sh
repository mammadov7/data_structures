#!/bin/bash
if [[ $# < 2 ]];then
	echo -e "You have to enter 2 arguments.\nUsage: $0 size_of_strip directory_of_files"
else
	cp extractStrip $2
	cp concat.sh $2
	cp concat $2
	cd $2
	for i in $(ls $2)
		do 
	if [[ $i == stripS$1 ]];then 
		rm -r $2/stripS$1
	fi
	done
	mkdir -p stripS$1
	for i in $(ls $2)
	do 
		if [[ $i == *.bmp ]];then 
		./extractStrip -$1 $i
		fi
	done
	rm $2/extractStrip
		for i in $(ls $2)
	do 
		if [[ $i == *S$1.bmp ]];then 
		mv $i stripS$1
		fi
	done
	read -p "Dou you want concatinate all strips?(y/n): " ans
	let remainder=($1)%4
	if [[ $ans == y ]];then
		if [[ $remainder == 0 ]];then
			./concat.sh $2/stripS$1 $1
		else
			echo "Width of strips must be multiple of 4"
		fi	
	fi
		rm $2/concat.sh
		rm $2/concat
fi
