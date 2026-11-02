# Keep game memory in a 4 GB arena with 32-bit offset pointers

On the 64-bit Native port (ADR 0006), all game heap and asset memory lives in one reserved 4 GB arena. Pointers stored inside asset data and the structures that mirror it are 32-bit offsets into that arena, declared through a macro type that is a plain pointer on the Matching build. Converting every asset into native 64-bit structures at load time was rejected because it requires fully understanding every asset format before the game can boot, and then keeping two layouts of each structure in sync.
