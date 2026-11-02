# Keep saves as memory card folders with unchanged contents

The Native port stores each memory card directory as a folder (for example `%APPDATA%\sotc\memcard0\BASCUS-97472nico\`) holding files byte-identical to what the PS2 writes. That keeps saves movable to and from PCSX2 memory cards with a simple tool, and lets the Ico-save bonus work by finding an Ico save folder in the same place. A new PC-only save format was rejected because it would cut players off from their existing saves for no gain.
