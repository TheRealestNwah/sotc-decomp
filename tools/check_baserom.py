"""Verify that the user-supplied game executable matches the expected build.

The decomp only works against one exact build of the game. This script hashes
the file at the configured path and compares it to the SHA-1 in
config/baserom.json, so mismatched dumps are caught before splitting/building.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_CONFIG = REPO_ROOT / "config" / "baserom.json"


def sha1_of(path: Path) -> str:
    digest = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            digest.update(chunk)
    return digest.hexdigest()


def load_config(config_path: Path) -> dict:
    with config_path.open("r", encoding="utf-8") as f:
        return json.load(f)


def check(config_path: Path, root: Path) -> tuple[bool, str]:
    config = load_config(config_path)
    rom_path = root / config["path"]
    expected = config.get("sha1")

    if not rom_path.is_file():
        return False, (
            f"Missing {config['path']}. Copy {config['elf_name']} from your own "
            "disc into the baserom/ folder."
        )

    actual = sha1_of(rom_path)
    if not expected:
        return False, (
            f"No expected SHA-1 set in config. Your file hashes to {actual}; "
            "once verified against a known-good dump, record it in config/baserom.json."
        )
    if actual.lower() != expected.lower():
        return False, f"SHA-1 mismatch: expected {expected}, got {actual}."
    return True, f"{config['path']} OK ({actual})."


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config", type=Path, default=DEFAULT_CONFIG)
    parser.add_argument("--root", type=Path, default=REPO_ROOT)
    args = parser.parse_args(argv)

    ok, message = check(args.config, args.root)
    print(message)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
