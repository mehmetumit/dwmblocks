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
# Patches
Here are some patches to dwmblocks that add features that I either don't want to merge in, or that require a dwm patch to work.
<br>
<a href=https://gist.github.com/IGeraGera/e4a5583b91b3eec2e81fdceb44dea717>dwmblocks-statuscmd-b6b0be4.diff</a>
