# Target 64-bit Windows first

The first Native port target is Windows x64, followed by Linux and then macOS. The game's data embeds 32-bit pointers that it fixes up in place at load time, and a 32-bit x86 build would have run that data unchanged. It was rejected because macOS and Linux distributions no longer support 32-bit programs, so the pointer-size work can only be postponed, not avoided, and a 32-bit first port would be redone.
