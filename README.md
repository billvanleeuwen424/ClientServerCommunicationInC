# Basic Client-Server File Transfer Using Web Sockets (local machine only)

## Description
This repository contains 2 C files, a client and a server. The client will transfer a specified file to the servers directory.

## Usage

**This code will only run on Unix based systems!**

1. Compile the code using gcc
    ```bash
    gcc server.c -o server
    gcc client.c -o client
    ```

2. Move the binaries into the folder which you want to transfer the file (the client can be anywhere if wanted, this is just for ease of explaination).
   
3. Run the server
   ```bash
   ./server
   ```
4. In a seperate teminal window Run the client, pass the file path of your chosen file into it.
    ```bash
    ./client /home/user/Documents/someFile
    ```

## What I learned
- C Programming
- Systems Programming on UNIX with C
- Web Sockets
- TCP Communication