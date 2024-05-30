savedcmd_/home/rps/MAY/May22/user/kernel_program.mod := printf '%s\n'   kernel_program.o | awk '!x[$$0]++ { print("/home/rps/MAY/May22/user/"$$0) }' > /home/rps/MAY/May22/user/kernel_program.mod
