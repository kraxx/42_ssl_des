# 42_ssl_des
Recreation of OpenSSL's implementation of DES (Data Encryption Standard).
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
## Using the testing suite
Run the included script "differ.sh" to test the output of ft_ssl against openssl's.
```
./scripts/differ.sh [plain/cipher text] [key] [initialization vector]
```
