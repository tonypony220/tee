#!/bin/bash

case="ONE ARGUMENT case"
echo "1234" | ./te file > coutput 2>&1
my_res=$?
echo "1234" | tee testfile > output 2>&1
bad_res=$?
if [ $my_res -ne $bad_res ]
then
	printf "\n: $case different return result, my \e[1;31m$my_res\e[0m and orig \e[1;32m$bad_res\e[0m !\n"
	exit 1
fi
diff -y --suppress-common-lines coutput output
if [ $? -ne 0 ]
then
	printf "\e[1;31m: $case difference in output, coutput is orig, output my and the example is in example_ !\e[0m\n"
	exit 2
fi
diff -y --suppress-common-lines file testfile
if [ $? -ne 0 ]
then
	printf "\e[1;31m: $case difference in output, coutput is orig, output my and the example is in example_ !\e[0m\n"
	exit 2
fi

case="-a ARGUMENT case"

echo "1234" | ./te -a file > coutput 2>&1
my_res=$?
echo "1234" | tee -a testfile > output 2>&1
bad_res=$?
if [ $my_res -ne $bad_res ]
then
	printf "\n: $case different return result, tee \e[1;31m$my_res\e[0m and te \e[1;32m$bad_res\e[0m !\n"
	exit 1
fi
diff -y --suppress-common-lines coutput output
if [ $? -ne 0 ]
then
	printf "\e[1;31m: $case difference in output, coutput is orig, output my and the example is in example_ !\e[0m\n"
	exit 2
fi
diff -y --suppress-common-lines file testfile
if [ $? -ne 0 ]
then
	printf "\e[1;31m: $case difference in output, coutput is orig, output my and the example is in example_ !\e[0m\n"
	exit 2
fi


case="BAD FILE case"
touch badfile
chmod 100 badfile
echo "1234" | ./te -a badfile > coutput 2>&1
my_res=$?
echo "1234" | tee -a badfile > output 2>&1
bad_res=$?
if [ $my_res -ne $bad_res ]
then
	printf "\n: $case different return result, tee \e[1;31m$my_res\e[0m and te \e[1;32m$bad_res\e[0m !\n"
	exit 1
fi

case="FEW ARGUMENT case"
echo "1234" | ./te file file2 file3 > coutput 2>&1
my_res=$?
echo "1234" | tee testfile testfile2 testfile3 > output 2>&1
bad_res=$?
if [ $my_res -ne $bad_res ]
then
	printf "\n: $case different return result, tee \e[1;31m$my_res\e[0m and te \e[1;32m$bad_res\e[0m !\n"
	exit 1
fi
diff -y --suppress-common-lines coutput output
if [ $? -ne 0 ]
then
	printf "\e[1;31m: $case difference in output, coutput is orig, output my and the example is in example_ !\e[0m\n"
	exit 2
fi
diff -y --suppress-common-lines file testfile
if [ $? -ne 0 ]
then
	printf "\e[1;31m: $case difference in output, coutput is orig, output my and the example is in example_ !\e[0m\n"
	exit 2
fi

diff -y --suppress-common-lines file2 testfile2
if [ $? -ne 0 ]
then
	printf "\e[1;31m: $case difference in output, coutput is orig, output my and the example is in example_ !\e[0m\n"
	exit 2
fi

diff -y --suppress-common-lines file3 testfile3
if [ $? -ne 0 ]
then
	printf "\e[1;31m: $case difference in output, coutput is orig, output my and the example is in example_ !\e[0m\n"
	exit 2
fi
rm -rf badfile *file* coutput output
printf "\e[1;32mOK\e[0m \n"
