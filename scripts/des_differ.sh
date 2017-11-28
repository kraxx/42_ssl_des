#!/bin/bash
# https://github.com/kraxx

TEST_ONE="openssl"
TEST_TWO="./ft_ssl"

NOPAD="" #"-nopad"
NOPAD_ME="" #"-n"

REDTXT="[31m"
GREENTXT="[32m"
MAGENTATXT="[35m"
LGREENTXT="[92m"
BLUETXT="[34m"
CYANTXT="[36m"
ENDTXT="[0m"

SYS_ENC="sys_en"
SYS_DEC="sys_de"
MY_ENC="my_en"
MY_DEC="my_de"

DIFF_ENC="diff $SYS_ENC $MY_ENC"
DIFF_DEC="diff $SYS_DEC $MY_DEC"

BIG_FILE_PATH=~/Desktop/biblep10.txt # replace with path to your preferred massive file
BIG_FILE_SYS_ENC="bigfile_sys_en"
BIG_FILE_SYS_DEC="bigfile_sys_de"
BIG_FILE_MY_ENC="bigfile_me_en"
BIG_FILE_MY_DEC="bigfile_me_de"

BIG_FILE_DIFF_ENC="diff $BIG_FILE_SYS_ENC $BIG_FILE_MY_ENC"
BIG_FILE_DIFF_DEC="diff $BIG_FILE_SYS_DEC $BIG_FILE_MY_DEC"

# Arguments:
# $1 = input msg
# $2 = key
# $3 = initial vector
if [ -z $1 ]
	then
		echo "${REDTXT}Please supply a message as argument${ENDTXT}"
		echo "${REDTXT}./differ.sh [msg] [key (opt)] [iv (opt)]${ENDTXT}"
		exit 1
fi
if [ -z $2 ]
	then
		KEY="0123456789FEDCBA"
	else
		KEY=$2
fi
if [ -z $3 ]
	then
		IV="69FEFE45123ABC69"
	else
		IV=$3
fi

dcheck() {
	if [ "$2" == "silent" ]
		then
			$1 >/dev/null
		else
			$1
	fi
	if [ $? -eq 0 ]
		then
			echo "${GREENTXT}Good job :)${ENDTXT}"
		else
			echo "${REDTXT}:(${ENDTXT}"
	fi
}

echo $'\n'
echo $"${LGREENTXT}*************************************${ENDTXT}"
echo $"${LGREENTXT}*   FT_SSL TESTING SUITE BY KRAXX   *${ENDTXT}"
echo $"${LGREENTXT}*       follow @ github.com/kraxx   *${ENDTXT}"
echo $"${LGREENTXT}*************************************${ENDTXT}"
echo $'\n'

echo "Key: ${CYANTXT}${KEY}${ENDTXT}"
echo "IV:  ${CYANTXT}${IV}${ENDTXT}"

echo -e "\n\n${MAGENTATXT}Tests against base64/openssl:${ENDTXT}"

echo "Diffing base64 encryption:"
echo $1 | base64 -o $SYS_ENC
echo $1 | $TEST_TWO base64 -o $MY_ENC
dcheck "$DIFF_ENC"

echo "Diffing base64 decryption:"
base64 -D $SYS_ENC -o $SYS_DEC
$TEST_TWO base64 -d $SYS_ENC -o $MY_DEC
dcheck "$DIFF_DEC"

echo -n "" > $SYS_ENC > $SYS_DEC > $MY_ENC > $MY_DEC

echo "Diffing des-ecb encryption:"
echo $1 | $TEST_ONE des-ecb -K $KEY $NOPAD -out $SYS_ENC
echo $1 | $TEST_TWO des-ecb -k $KEY $NOPAD_ME -o $MY_ENC
dcheck "$DIFF_ENC"

echo "Diffing des-ecb decryption:"
$TEST_ONE des-ecb -d -K $KEY $NOPAD -in $SYS_ENC -out $SYS_DEC
$TEST_TWO des-ecb -d -k $KEY -i $SYS_ENC -o $MY_DEC
dcheck "$DIFF_DEC"

echo -n "" > $SYS_ENC > $SYS_DEC > $MY_ENC > $MY_DEC

echo "Diffing des-ecb b64 encryption:"
echo $1 | $TEST_ONE des-ecb -K $KEY -a $NOPAD -out $SYS_ENC
echo $1 | $TEST_TWO des-ecb -k $KEY -a -o $MY_ENC
dcheck "$DIFF_ENC"

echo "Diffing des-ecb b64 decryption:"
$TEST_ONE des-ecb -d -K $KEY -a $NOPAD -in $SYS_ENC -out $SYS_DEC
$TEST_TWO des-ecb -d -k $KEY -a -i $SYS_ENC -o $MY_DEC
dcheck "$DIFF_DEC"

echo -n "" > $SYS_ENC > $SYS_DEC > $MY_ENC > $MY_DEC

echo "Diffing des-cbc encryption:"
echo $1 | $TEST_ONE des-cbc -K $KEY -iv $IV $NOPAD -out $SYS_ENC
echo $1 | $TEST_TWO des-cbc -k $KEY -v $IV -o $MY_ENC
dcheck "$DIFF_ENC"

echo "Diffing des-cbc decryption:"
$TEST_ONE des-cbc -d -K $KEY -iv $IV $NOPAD -in $SYS_ENC -out $SYS_DEC
$TEST_TWO des-cbc -d -k $KEY -v $IV -i $SYS_ENC -o $MY_DEC
dcheck "$DIFF_DEC"

echo -n "" > $SYS_ENC > $SYS_DEC > $MY_ENC > $MY_DEC

echo "Diffing des-cbc b64 encryption:"
echo $1 | $TEST_ONE des-cbc -K $KEY -iv $IV $NOPAD -out $SYS_ENC -a
echo $1 | $TEST_TWO des-cbc -k $KEY -v $IV -o $MY_ENC -a
dcheck "$DIFF_ENC"

echo "Diffing des-cbc b64 decryption:"
$TEST_ONE des-cbc -d -K $KEY -iv $IV $NOPAD -in $SYS_ENC -out $SYS_DEC -a
$TEST_TWO des-cbc -d -k $KEY -v $IV -i $SYS_ENC -o $MY_DEC -a
dcheck "$DIFF_DEC"

echo -n "" > $SYS_ENC > $SYS_DEC > $MY_ENC > $MY_DEC

echo "Diffing des3-cbc encryption:"
echo $1 | $TEST_ONE des3 -K $KEY -iv $IV $NOPAD -out $SYS_ENC
echo $1 | $TEST_TWO des3 -k $KEY -v $IV -o $MY_ENC
dcheck "$DIFF_ENC"

echo "Diffing des3-cbc decryption:"
$TEST_ONE des3 -d -K $KEY -iv $IV $NOPAD -in $SYS_ENC -out $SYS_DEC
$TEST_TWO des3 -d -k $KEY -v $IV -i $SYS_ENC -o $MY_DEC
dcheck "$DIFF_DEC"

echo -n "" > $SYS_ENC > $SYS_DEC > $MY_ENC > $MY_DEC

echo "Diffing des3-cbc b64 encryption:"
echo $1 | $TEST_ONE des3 -K $KEY -iv $IV $NOPAD -out $SYS_ENC -a
echo $1 | $TEST_TWO des3 -k $KEY -v $IV -o $MY_ENC -a
dcheck "$DIFF_ENC"

echo "Diffing des3-cbc b64 decryption:"
$TEST_ONE des3 -d -K $KEY -iv $IV $NOPAD -in $SYS_ENC -out $SYS_DEC -a
$TEST_TWO des3 -d -k $KEY -v $IV -i $SYS_ENC -o $MY_DEC -a
dcheck "$DIFF_DEC"

rm $SYS_ENC $SYS_DEC $MY_ENC $MY_DEC


echo -e "\n\n${MAGENTATXT}I/O Self-Piping Tests:${ENDTXT}"

echo "Base64:"
echo $1 | base64 | $TEST_TWO base64 -d | $TEST_TWO base64 | base64 -D

echo $'\ndes-ecb'
echo $1 | $TEST_TWO des-ecb -k $KEY | $TEST_TWO des-ecb -k $KEY -d | $TEST_TWO des-ecb -k $KEY | $TEST_TWO des-ecb -k $KEY -d

echo -n "" > $SYS_ENC $SYS_DEC $MY_ENC $MY_DEC
echo $'\ndes-ecb base64'
echo $1 | $TEST_TWO des-ecb -k $KEY -a | $TEST_TWO des-ecb -k $KEY -d -a | $TEST_TWO des-ecb -k $KEY -a | $TEST_TWO des-ecb -k $KEY -d -a

echo $'\ndes-cbc'
echo $1 | $TEST_TWO des-cbc -k $KEY -v $IV | $TEST_TWO des-cbc -k $KEY -v $IV -d | $TEST_TWO des-cbc -k $KEY -v $IV | $TEST_TWO des-cbc -k $KEY -v $IV -d
echo $'\ndes-cbc base64'
echo $1 | $TEST_TWO des-cbc -k $KEY -v $IV -a | $TEST_TWO des-cbc -k $KEY -v $IV -d -a | $TEST_TWO des-cbc -k $KEY -v $IV -a | $TEST_TWO des-cbc -k $KEY -v $IV -d -a


echo -e "\n\n${MAGENTATXT}BIGFILE tests:${ENDTXT}"

echo "Diffing base64 for ${MAGENTATXT}BIGFILE:${ENDTXT}"
base64 -i $BIG_FILE_PATH -o $BIG_FILE_SYS_ENC
$TEST_TWO base64 -i $BIG_FILE_PATH -o $BIG_FILE_MY_ENC
dcheck "$BIG_FILE_DIFF_ENC" "silent"

echo "Diffing base64 for ${MAGENTATXT}BIGFILE:${ENDTXT}"
base64 -i $BIG_FILE_SYS_ENC -o $BIG_FILE_SYS_DEC -D
$TEST_TWO base64 -i $BIG_FILE_SYS_ENC -o $BIG_FILE_MY_ENC -d
dcheck "$BIG_FILE_DIFF_DEC" "silent"

echo -n "" > $BIG_FILE_SYS_ENC > $BIG_FILE_SYS_DEC > $BIG_FILE_MY_ENC > $BIG_FILE_MY_DEC

echo "Diffing des-ecb encryption for ${MAGENTATXT}BIGFILE:${ENDTXT}"
openssl des-ecb -K $KEY -in $BIG_FILE_PATH -out $BIG_FILE_SYS_ENC
$TEST_TWO des-ecb -k $KEY -i $BIG_FILE_PATH -o $BIG_FILE_MY_ENC
dcheck "$BIG_FILE_DIFF_ENC" "silent"

echo "Diffing des-ecb decryption for ${MAGENTATXT}BIGFILE:${ENDTXT}"
openssl des-ecb -K $KEY -in $BIG_FILE_SYS_ENC -out $BIG_FILE_SYS_DEC -d
$TEST_TWO des-ecb -k $KEY -i $BIG_FILE_SYS_ENC -o $BIG_FILE_MY_DEC -d
dcheck "$BIG_FILE_DIFF_DEC" "silent"

echo -n "" > $BIG_FILE_SYS_ENC > $BIG_FILE_SYS_DEC > $BIG_FILE_MY_ENC > $BIG_FILE_MY_DEC

echo "Diffing des-cbc encryption for ${MAGENTATXT}BIGFILE:${ENDTXT}"
openssl des-cbc -K $KEY -iv $IV -in $BIG_FILE_PATH -out $BIG_FILE_SYS_ENC
$TEST_TWO des-cbc -k $KEY -v $IV -i $BIG_FILE_PATH -o $BIG_FILE_MY_ENC
dcheck "$BIG_FILE_DIFF_ENC" "silent"

echo "Diffing des-cbc decryption for ${MAGENTATXT}BIGFILE:${ENDTXT}"
openssl des-cbc -k $KEY -iv $IV -in $BIG_FILE_SYS_ENC -out $BIG_FILE_SYS_DEC -d
$TEST_TWO des-cbc -k $KEY -v $IV -i $BIG_FILE_SYS_ENC -o $BIG_FILE_MY_DEC -d
dcheck "$BIG_FILE_DIFF_DEC" "silent"

echo -n "" > $BIG_FILE_SYS_ENC > $BIG_FILE_SYS_DEC > $BIG_FILE_MY_ENC > $BIG_FILE_MY_DEC

echo "Diffing des3 encryption for ${MAGENTATXT}BIGFILE:${ENDTXT}"
openssl des3 -K $KEY -iv $IV -in $BIG_FILE_PATH -out $BIG_FILE_SYS_ENC -d
$TEST_TWO des3 -k $KEY -v $IV -i $BIG_FILE_PATH -o $BIG_FILE_MY_ENC -d
dcheck "$BIG_FILE_DIFF_ENC" "silent"

echo "Diffing des3 decryption for ${MAGENTATXT}BIGFILE:${ENDTXT}"
openssl des3 -k $KEY -iv $IV -in $BIG_FILE_SYS_ENC -out $BIG_FILE_SYS_DEC -d
$TEST_TWO des3 -k $KEY -v $IV -i $BIG_FILE_SYS_ENC -o $BIG_FILE_MY_DEC -d
dcheck "$BIG_FILE_DIFF_DEC" "silent"

rm $BIG_FILE_SYS_ENC $BIG_FILE_SYS_DEC $BIG_FILE_MY_ENC $BIG_FILE_MY_DEC
