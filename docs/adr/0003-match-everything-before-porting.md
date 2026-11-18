# Finish matching before porting, and keep original bugs until then

No Game code is ported until all Game code is made of Matched functions. Until then, matching C reproduces the Original's behaviour exactly, including known defects such as #490, #492 and #708: a "fix" would change the bytes, and an early port would fork the source before its structure and names have settled. Confirmed defects are fixed deliberately during the port, with regression coverage.

Amended 2026-11-17: Platform layer work runs in parallel with matching. That covers the disc reader, the Render translator, Reference run tooling, the runtime core (memory arena, fibers, SDL3 window and input) and the Sound driver. None of it compiles the game's own C, so it can't fork the source. The ban above applies only to porting Game code.
