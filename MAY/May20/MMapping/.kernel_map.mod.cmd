savedcmd_/home/rps/MAY/May20/MMapping/kernel_map.mod := printf '%s\n'   kernel_map.o | awk '!x[$$0]++ { print("/home/rps/MAY/May20/MMapping/"$$0) }' > /home/rps/MAY/May20/MMapping/kernel_map.mod
