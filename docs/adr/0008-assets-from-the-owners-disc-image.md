# Read assets straight from the owner's disc image

The Native port reads game files directly from the owner's Disc image, whose path is set at first launch and checked against known hashes. Nothing is extracted, cached or shipped. This mirrors how the matching build already depends on the owner's Original files and keeps all game data out of the repository and out of release builds. The cost is a read path through the image's file system for every asset access (almost everything is inside one archive, `NICO.DAT`).
