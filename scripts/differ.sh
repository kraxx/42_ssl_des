#!/bin/bash
# https://github.com/kraxx

# $1 = msg $2 = key $3 = initial vector
if [ -z $2 ]
	then
		echo "NO KEY SUPPLIED"
		KEY="0123456789FEDCBA"
	else
		KEY=$2
fi
if [ -z $3 ]
	then
		echo "NO IV SUPPLIED"
		IV="6969abcabc8a5e1f"
	else
		IV=$3
fi

echo $1 | base64 > sys_en
echo $1 | ./ft_ssl base64 > me_en
echo "Diffing base64 encryption:"
diff sys_en me_en
base64 -D me_en > sys_de
./ft_ssl base64 -d me_en > me_de
echo "Diffing base64 decryption:"
diff sys_de me_de

echo $1 | openssl des-ecb -K $KEY -nopad -out sys_en
echo $1 | ./ft_ssl des-ecb -k $KEY -o me_en
echo "Diffing des-ecb encryption:"
diff sys_en me_en

openssl des-ecb -d -K $KEY -nopad -in sys_en -out sys_de
./ft_ssl des-ecb -d -k $KEY -i sys_en -o me_de
echo "Diffing des-ecb decryption:"
diff sys_de me_de

echo $1 | openssl des-ecb -K $KEY -a -nopad -out sys_en
echo $1 | ./ft_ssl des-ecb -k $KEY -a -o me_en
echo "Diffing des-ecb b64 encryption:"
diff sys_en me_en

openssl des-ecb -d -K $KEY -a -nopad -in sys_en -out sys_de
./ft_ssl des-ecb -d -k $KEY -a -i sys_en -o me_de
echo "Diffing des-ecb b64 decryption:"
diff sys_de me_de

echo $1 | openssl des-cbc -K $KEY -iv $IV -nopad -out sys_en
echo $1 | ./ft_ssl des-cbc -k $KEY -v $IV  -o me_en
echo "Diffing des-cbc encryption:"
diff sys_en me_en

openssl des-cbc -d -K $KEY -iv $IV -nopad -in sys_en -out sys_de
./ft_ssl des-cbc -d -k $KEY -v $IV -i sys_en -o me_de
echo "Diffing des-cbc decryption:"
diff sys_de me_de

echo $1 | openssl des-cbc -K $KEY -iv $IV -nopad -out sys_en -a
echo $1 | ./ft_ssl des-cbc -k $KEY -v $IV  -o me_en -a
echo "Diffing des-cbc b64 encryption:"
diff sys_en me_en

openssl des-cbc -d -K $KEY -iv $IV -nopad -in sys_en -out sys_de -a
./ft_ssl des-cbc -d -k $KEY -v $IV -i sys_en -o me_de -a
echo "Diffing des-cbc b64 decryption:"
diff sys_de me_de

rm sys_en me_en sys_de me_de