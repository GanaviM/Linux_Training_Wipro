savedcmd_/home/rps/MAY/May24/Character_device_driver/my_char_dev.ko := ld -r -m elf_x86_64 -z noexecstack --build-id=sha1  -T scripts/module.lds -o /home/rps/MAY/May24/Character_device_driver/my_char_dev.ko /home/rps/MAY/May24/Character_device_driver/my_char_dev.o /home/rps/MAY/May24/Character_device_driver/my_char_dev.mod.o;  make -f ./arch/x86/Makefile.postlink /home/rps/MAY/May24/Character_device_driver/my_char_dev.ko