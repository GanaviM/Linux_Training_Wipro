savedcmd_/home/rps/MAY/May9/Char_drive/char_drive.mod := printf '%s\n'   char_drive.o | awk '!x[$$0]++ { print("/home/rps/MAY/May9/Char_drive/"$$0) }' > /home/rps/MAY/May9/Char_drive/char_drive.mod
