savedcmd_/home/rps/MAY/May29/kernel_interrupt/kinterrupt.ko := ld -r -m elf_x86_64 -z noexecstack --build-id=sha1  -T scripts/module.lds -o /home/rps/MAY/May29/kernel_interrupt/kinterrupt.ko /home/rps/MAY/May29/kernel_interrupt/kinterrupt.o /home/rps/MAY/May29/kernel_interrupt/kinterrupt.mod.o;  make -f ./arch/x86/Makefile.postlink /home/rps/MAY/May29/kernel_interrupt/kinterrupt.ko