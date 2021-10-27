# Dwmblocks
Modular status bar for dwm written in c.
# Usage
To use dwmblocks first run 'make' and then install it with 'sudo make install'.
After that you can put dwmblocks in your xinitrc or other startup script to have it start with dwm.
# Modifying blocks
The statusbar is made from text output from commandline programs.
Blocks are added and removed by editing the blocks.h header file.
# Signaling
You can update blocks by their update signal. Add 34 to signal number of block.
```sh
rtmin_plus=$((34 + 'signal number of block'))
kill -$rtmin_plus $(pidof dwmblocks)
```
