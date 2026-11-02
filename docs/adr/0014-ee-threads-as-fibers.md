# Run the game's EE threads as fibers on one OS thread

The game uses several EE threads with priority scheduling and a vsync interrupt. The Native port runs them as fibers on a single OS thread, switching only where the EE would switch, so a run with the same inputs always behaves the same. Mapping them to real OS threads would be simpler to write but nondeterministic, which would make Reference runs (ADR 0016) impossible to compare.
