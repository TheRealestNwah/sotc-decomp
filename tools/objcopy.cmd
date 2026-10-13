@echo off
rem Stand-in for objcopy so `splat create_config --objcopy tools\objcopy.cmd` works without binutils.
"%~dp0..\.venv\Scripts\python.exe" "%~dp0elf2rom.py" %*
