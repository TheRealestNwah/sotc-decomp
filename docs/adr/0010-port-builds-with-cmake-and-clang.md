# Build the Native port with CMake and Clang, separately from the matching build

The Native port builds with CMake and Clang on every platform (clang-cl on Windows), while the Matching build keeps `configure.py` and ninja with the original toolchain. Clang accepts the GCC extensions and loose typing of early-2000s game C far better than MSVC, and one compiler everywhere means one set of warnings and behaviours to chase. Merging both builds into one generator was rejected: the matching build's steps (splitting, splicing, XFF rebuilding) have nothing in common with a native build.
