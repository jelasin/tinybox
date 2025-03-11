# TinyBox

a tiny shell to run commands on remote machines.

## Usage

``` bash
# REMOTE:
$ tinyboxd -P 0.0.0.0:8000
# LOCAL:
$ tinybox REMOTE_IP:8000
$ tinybox$
```
## Supported commands

- ls            --ok
    ==> ls -lA
- cd            --ok
- pwd           --ok
- mkdir
- rm            --ok
    ==> rm -rf
- mv
- cp            --ok
    ==> cp -rL
- cat
- touch
- echo
- exit          --ok
- help          --ok
- quit          --ok
- exec
    to run ELF executables. such as: `tinybox$ exec ./a.out arg1 arg2`
- wget
    ==> wget http://example.com/file.txt ./file.txt
- ifconfig
- ping
- whoami
- clear
- `>`
- `>>`
- `|`
