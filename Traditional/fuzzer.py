#!/usr/bin/python
from pwn import *
import sys

context(terminal=["tmux","splitw", "-h"])
context.delete_corefiles = True
context.log_level = 'error'

def locate_offset(binary):

    offset = 0
    buff_sz = 1

    l = log.progress("Beginning fuzzing...",level=40)

    while offset <= 0:

        p = process(binary.path)
        payload = cyclic(buff_sz)

        p.recvuntil(": ")
        l.status("Fuzzing with %d bytes" % buff_sz)

        p.sendline(payload)
        p.wait()

        try:
            core = p.corefile
            rsp = core.rsp
            offset = core.read(rsp, 4)
            offset = cyclic_find(offset)
        except:
            pass

        p.close()
        buff_sz += 1

    l.success("offset at %s bytes" % offset)
    p = gdb.debug(binary.path,'c')
    p.recvuntil(": ")
    payload = cyclic(offset + 8)
    p.sendline(payload)
    raw_input()
    return offset


if __name__ == '__main__':

    if len(sys.argv) == 2:
        elf = ELF(sys.argv[1])
        offset = locate_offset(elf)

        context.log_level = "info"
        log.success("Offset located at %d bytes" % offset)
    else:
        print("Usage: %s <binary>" % sys.argv[0])
