# Build the Native port in this repo, from the same source as the matching build

The Native port lives in this repository and compiles the same Game code as the matching build. Platform-specific code sits in its own directory, and Game code differs between the two builds only behind a build macro (`TARGET_PC` or similar). The matching build stays a checked target for good, so any change made for the port can be proven not to alter the PS2 behaviour. A fork would have been simpler to start, but the two copies would drift and every later naming or cleanup change would have to be made twice.
