savedcmd_/home/rps/MAY/May21/simple_char_driver2/kernel_char.mod := printf '%s\n'   kernel_char.o | awk '!x[$$0]++ { print("/home/rps/MAY/May21/simple_char_driver2/"$$0) }' > /home/rps/MAY/May21/simple_char_driver2/kernel_char.mod
