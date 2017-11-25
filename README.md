# 42_ssl_des
Recreation of OpenSSL's implementation of DES (Data Encryption Standard).
Coded as part of 42 University's encryption branch.
## Getting started
From the root directory, run:
```
make
```
To run the exectuable, enter:
```
./ft_ssl [command] [options] [arguments]
```
Current available commands:
```
base64
des-ecb
des-cbc
des3-cbc
```
Options handled:
```
-e    encrypt
-d/-D decrypt
-i    input [file]
-o    ouput [file]
-a    apply base64 encryption/decryption
-k/-K key string in hex
-v    initialization vector in hex
-p    print key
-n    nopad mode (pads with zeroes)
```
If no input file is supplied, the program reads from standard input.
Likewise, if no output file is specified, the program writes to standard output.

## Using the testing suite
Run the included script "differ.sh" to test the output of ft_ssl against openssl's.
```
./scripts/des_differ.sh [plain/cipher text] [key (optional)] [initialization vector (optional)]
```
The results of each command's encryption/decryption are compared with base64/OpenSSL's results using the command line's "diff". On failure, the difference in outputs are displayed. Otherwise, all is good!
Additional in/out piping tests are performed to ensure reads from standard input are clean.
