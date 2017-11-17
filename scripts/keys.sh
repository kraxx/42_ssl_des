#!/bin/bash

# $1 = key
openssl des-ecb -K $1 -nopad -in testo -out sys_en
./ft_ssl des-ecb -k $1 -i testo -o me_en
echo "Diffing keys & encryption"
diff sys_en me_en

openssl des-ecb -K $1 -nopad -in sys_en -out sys_de -d
./ft_ssl des-ecb -k $1 -i sys_en -o me_de -d
echo "Diffing keys & decryption"
diff sys_de me_de

#des-ecb base64
openssl des-ecb -K $1 -base64 -nopad -in testo -out sys_en
./ft_ssl des-ecb -k $1 -a -i testo -o me_en
echo "Diffing base64 & encryption"
diff sys_en me_en

openssl des-ecb -K $1 -base64 -nopad -in sys_en -out sys_de -d
./ft_ssl des-ecb -k $1 -a -i sys_en -o me_de -d
echo "Diffing base64 & decryption"
diff sys_de me_de

rm sys_en me_en sys_de me_de