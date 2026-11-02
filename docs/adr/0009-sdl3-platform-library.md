# Use SDL3 and SDL_GPU under the Native port

The Platform layer is built on SDL3: windowing, input, audio output and file dialogs, with SDL_GPU for the Render translator's drawing. SDL_GPU covers D3D12, Vulkan and Metal behind one API, so the Linux and macOS targets in ADR 0006 need no second renderer. Writing against D3D12 or Vulkan directly would give more control at the cost of one backend per platform; OpenGL was rejected as a dead end on macOS.
