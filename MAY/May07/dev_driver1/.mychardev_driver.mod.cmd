savedcmd_/home/rps/MAY/Mychardev/mychardev_driver.mod := printf '%s\n'   mychardev_driver.o | awk '!x[$$0]++ { print("/home/rps/MAY/Mychardev/"$$0) }' > /home/rps/MAY/Mychardev/mychardev_driver.mod
