savedcmd_/home/rongrong/os_exp/nine/listprocess.mod := printf '%s\n'   listprocess.o | awk '!x[$$0]++ { print("/home/rongrong/os_exp/nine/"$$0) }' > /home/rongrong/os_exp/nine/listprocess.mod
