#!/usr/bin/python
from pwn import *

context(terminal=["tmux","splitw","-h"])

pin = "7777"
backdoor = '\xf5\x0a'

#p = process("./bank")
p = gdb.debug("./bank",'''
        break backdoor
        continue
        ''')
print(p.sendlineafter("> ",pin))
print("About to send backdoor value: %s" % backdoor)
raw_input()
print(p.sendafter("> ",backdoor))
p.interactive()


