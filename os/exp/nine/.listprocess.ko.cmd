savedcmd_/home/rongrong/os_exp/nine/listprocess.ko := ld -r -m elf_x86_64 -z noexecstack --no-warn-rwx-segments --build-id=sha1  -T scripts/module.lds -o /home/rongrong/os_exp/nine/listprocess.ko /home/rongrong/os_exp/nine/listprocess.o /home/rongrong/os_exp/nine/listprocess.mod.o;  make -f ./arch/x86/Makefile.postlink /home/rongrong/os_exp/nine/listprocess.ko
