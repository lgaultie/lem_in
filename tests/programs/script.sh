#!/bin/bash

# Path of Lem-in project
LEM_IN=".."

catch_ctrl_c()
{
	printf "\nScript terminated.\n"
	if [ -e tmp ]
	then	
		`rm tmp`
	fi
	if [ -e tmp.map ]
	then	
		`rm tmp.map`
	fi
	exit 1
}

generate_map()
{
	if [ $1 -eq 1 ]
	then
		./generator --flow-one > tmp.map
	elif [ $1 -eq 2 ]
	then
		./generator --flow-ten > tmp.map
	elif [ $1 -eq 3 ]
	then
		./generator --flow-thousand > tmp.map
	elif [ $1 -eq 4 ]
	then
		./generator --big > tmp.map
	elif [ $1 -eq 5 ]
	then
		./generator --big-superposition > tmp.map
	fi
}

single_test()
{
	LI=`$LEM_IN/lem-in -ct < tmp.map > tmp ; diff tmp tmp.map | wc -l`
	LI=`echo "($LI) - 2" | bc`
	MAP=`tail -1 tmp.map | grep "line" | cut -d ' ' -f8`
	echo "$(($LI - $MAP))"
}

arg_test()
{
	$LEM_IN/lem-in -cpt < $1 ; tail -n1 $1
	$LEM_IN/lem-in < $1 | ./verifier 1> verif_res 2> verif_err
	ERROR=`cat verif_err | wc -l`
	if [ $ERROR -gt 0 ]
	then
		printf "\033[31mERROR\033[0m\n"
		`cp $1 maps/error.map`
	else
		RES=`cat verif_res`
		printf "\033[32mOK\033[0m\t"
		printf "Number of lines: $RES\n"
	fi
}

cd "$(dirname "$0")"
if [ ! -e $LEM_IN/lem-in ]
then
	printf "lem-in not found.\n"
	exit 1
fi
if [ ! -x $LEM_IN/lem-in ]
then
	printf "lem-in is not an executable.\n"
	exit 1
fi
if [ $# -gt 1 ]
then
	printf "%-7s./script.sh\n" "usage:"
	printf "%-7s./script.sh [map file]\n"
	exit 1
elif [ $# -eq 1 ]
then
	arg_test "$1"
	exit 1
fi
trap "catch_ctrl_c" 2
clear
echo "//================================\\\\"
printf "|| Script by \033[36msregnard\033[0m \033[0m&&\033[0m \033[33mchrhuang\033[0m ||\n"
echo "\\\\================================//"
read -n 1 -s -r -p "Press any key to continue..."
clear
echo "//============================\\\\"
printf "|| [1] : \033[36m%-20s\033[0m ||\n" "flow-one"
printf "|| [2] : \033[32m%-20s\033[0m ||\n" "flow-ten"
printf "|| [3] : \033[33m%-20s\033[0m ||\n" "flow-thousand"
printf "|| [4] : \033[31m%-20s\033[0m ||\n" "big"
printf "|| [5] : \033[35m%-20s\033[0m ||\n" "big-superposition"
echo "\\\\============================//"
gen=""
while [[ ! $gen =~ ^[1-5]+$ ]]; do
	read -p "Choose your generator : " gen
done
nb_test=0
while [ $nb_test -lt 1 ]; do
	nb_test=""
	while [[ ! $nb_test =~ ^[0-9]+$ ]]; do
		read -p "Number of tests       : " nb_test
	done
done
FLAG_TIME=""
while [ "$FLAG_TIME" != "y" ] && [ "$FLAG_TIME" != "n" ]; do
	read -p "Test time ? [y][n]    : " FLAG_TIME
done
sum=0
sum_t=0
i=0
while [ $i -lt $nb_test ]
do
	printf "Generating next test... "
	generate_map "$gen"
	printf "Testing..."
	before=`date +%s`
	res=`single_test`
	after=`date +%s`
	res_t=`echo "($after) - ($before)" | bc -l`
	if [ $i -eq 0 ]
	then
		min=$res
		max=$res
		min_t=$res_t
		max_t=$res_t
	else
		`mkdir -p maps`
		if [ $res -le $min ]
		then
			min=$res
			`cp tmp.map maps/min.map`
		fi
		if [ $max -le $res ]
		then
			max=$res
			`cp tmp.map maps/max.map`
		fi
		if [ $res_t -le $min_t ]
		then
			min_t=$res_t
			`cp tmp.map maps/min_t.map`
		fi
		if [ $max_t -le $res_t ]
		then
			max_t=$res_t
			`cp tmp.map maps/max_t.map`
		fi
		`rm tmp tmp.map`
	fi
	clear
	sum=`echo "($res) + ($sum)" | bc`
	sum_t=`echo "($res_t) + ($sum_t)" | bc`
	let "i++"
	moy=`echo "($sum) / ($i)" | bc -l`
	moy_t=`echo "($sum_t) / ($i)" | bc -l`
	printf "Test no. \033[32m%s\033[0m/%s\n\n" $i $nb_test
	printf "Nb of turns :\n" $i $nb_test
	echo "//===========================\\\\"
	printf "||         Res : \033[36m%-7d\033[0m     ||\n" $res
	printf "||         Min : \033[32m%-7d\033[0m     ||\n" $min
	printf "||         Moy : \033[33m%-7.1f\033[0m     ||\n" $moy
	printf "||         Max : \033[31m%-7d\033[0m     ||\n" $max
	echo "\\\\===========================//"
	if [ "$FLAG_TIME" == "y" ]
	then
		printf "\nTime :\n" $i $nb_test
		echo "//===========================\\\\"
		printf "||         Res : \033[31m%-7d\033[0m     ||\n" $res_t
		printf "||         Min : \033[32m%-7d\033[0m     ||\n" $min_t
		printf "||         Moy : \033[33m%-7.1f\033[0m     ||\n" $moy_t
		printf "||         Max : \033[31m%-7d\033[0m     ||\n" $max_t
		echo "\\\\===========================//"
	fi
done
