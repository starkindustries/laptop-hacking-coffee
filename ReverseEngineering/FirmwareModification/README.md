# Firmware Modification

## Reverse Engineering: 150 Points

## Challenge

I've been trying to get shell access to my router for a while but I can't guess the password. I have a firmware file and just need you to extract the /etc/passwd file and send me the contents.

[ [DAP-1325_REVA_FIRMWARE_1.02_MIDDLE.BIN](DAP-1325_REVA_FIRMWARE_1.02_MIDDLE.BIN) ]

## Solution

https://embeddedbits.org/reverse-engineering-router-firmware-with-binwalk/
https://unix.stackexchange.com/questions/113827/how-to-extract-files-from-uimage
https://en.wikipedia.org/wiki/Cpio
https://www.geeksforgeeks.org/cpio-command-in-linux-with-examples/
https://www.linuxquestions.org/questions/debian-26/how-to-use-cpio-to-extract-a-cpio-archive-333913/

File
```
$ file DAP-1325_REVA_FIRMWARE_1.02_MIDDLE.BIN
DAP-1325_REVA_FIRMWARE_1.02_MIDDLE.BIN: u-boot legacy uImage, Linux Kernel Image, Linux/MIPS, OS Kernel Image (lzma), 5624411 bytes, Tue May 15 03:47:31 2018, Load Address: 0x80000000, Entry Point: 0x8000C150, Header CRC: 0xEC98BC2B, Data CRC: 0x4EC58100
```

Binwalk
```
$ binwalk DAP-1325_REVA_FIRMWARE_1.02_MIDDLE.BIN 

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
0             0x0             uImage header, header size: 64 bytes, header CRC: 0xEC98BC2B, created: 2018-05-15 03:47:31, image size: 5624411 bytes, Data Address: 0x80000000, Entry Point: 0x8000C150, data CRC: 0x4EC58100, OS: Linux, CPU: MIPS, image type: OS Kernel Image, compression type: lzma, image name: "Linux Kernel Image"
64            0x40            LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 8386616 bytes
```

Extract the lzma compressed data portion:
```
$ tail -c+65 < DAP-1325_REVA_FIRMWARE_1.02_MIDDLE.BIN > dap-firmware.lzma
$ file dap-firmware.lzma 
dap-firmware.lzma: LZMA compressed data, non-streamed, size 8386616
```

Decompress the lzma: 
```
$ lzma -d dap-firmware.lzma
$ file dap-firmware
dap-firmware: data
```

Binwalk
```
$ binwalk dap-firmware
DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
799370        0xC328A         PGP RSA encrypted session key - keyid: 801000 202242C RSA Encrypt-Only 1024b
3375192       0x338058        Linux kernel version 2.6.36
3375352       0x3380F8        CRC32 polynomial table, little endian
3424244       0x343FF4        SHA256 hash constants, little endian
3535416       0x35F238        Unix path: /var/run/udhcpc.pid
3535616       0x35F300        Unix path: /var/run/status_monitor.pid
3651040       0x37B5E0        Unix path: /etc/Wireless/RT2860/RT2860.dat
3683472       0x383490        Unix path: /etc/Wireless/RT2860AP/RT2860AP.dat
3692248       0x3856D8        XML document, version: "1.0"
3731288       0x38EF58        Neighborly text, "NeighborSolicits6InDatagrams"
3731308       0x38EF6C        Neighborly text, "NeighborAdvertisementsorts"
3732439       0x38F3D7        Neighborly text, "neighbor %.2x%.2x.%pM lost sysctl."
3975744       0x3CAA40        CRC32 polynomial table, little endian
4304896       0x41B000        LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 16165376 bytes
```

Extract the LZMA compressed data starting at `0x41B000`:
```
$ dd bs=1 if=dap-firmware of=data.lzma skip=4304896
4081720+0 records in
4081720+0 records out
4081720 bytes (4.1 MB, 3.9 MiB) copied, 8.6802 s, 470 kB/s
```

Decompress the LZMA file:
```
$ lzma -d data.lzma
$ file data
data: cpio archive

$ mkdir archive
$ cd archive
$ cpio -id < ../data
```

You're in:
```
$ ls
bin  dev  etc  etc_ro  home  init  lib  media  mnt  proc  sbin  sys  tmp  usr  var
$ cat etc/passwd
LHC{ezpzlemonsqueezy}
```