# Concurrent Claude and Codex workflow

Claude coordinates assignments and integration. Codex implements independent
work items in isolated Git worktrees. Both follow AGENTS.md and CLAUDE.md.

## Ownership and communication

- File and label an issue before starting each item. Use one branch and PR per
  item. Record the agent, branch, worktree, exact function/file scope and status
  in the issue before editing. Check existing claims and PRs first.
- Claude assigns work and resolves overlapping claims. A worker may reserve an
  unclaimed independent issue when Claude is unavailable, recording that the
  reservation awaits coordinator acknowledgement.
- Claude owns shared headers, build configuration, compiler settings, symbol
  definitions, README totals, docs/findings.md and docs/handoff.md. Workers
  propose required changes in their issue/PR instead of editing these files
  concurrently. Ownership may be explicitly delegated for a particular issue.
- Assign complete original translation units/function groups where known;
  separate function names alone do not guarantee independent static data.
- GitHub issue and PR comments are the shared communication record. Separate
  agent chats do not share context. Update the issue at claim, blocker and
  handoff; include evidence and exact commands in the PR.
- Claude alone merges concurrent work after validation, updates progress totals
  and deletes merged branches. Workers must not enable auto-merge themselves.
  This delegates the user's standing merge authorization to the coordinator.
- No releases or tags without explicit user permission.

## Worktree isolation

Keep the existing maintainer/Claude checkout intact. Never stash, reset, clean,
switch branches or commit another agent's unfinished changes there.

Create worker checkouts from current origin/main, under an ignored `.worktrees/`
directory or another approved location. Use `git -C <worktree>` or explicitly set
the working directory for every command. Do not switch branches in a shared
checkout. Read the instructions in the worker checkout before starting work.

Each worktree needs its own asm/, build/, build.ninja, Ninja state and permuter
output. Copy the user's ignored iso/ inputs locally, or configure a read-only
input arrangement; never commit disc data. Do not share writable generated
directories. External compiler installations may be shared read-only. The
existing compiler wrappers use unique temporary directories for WSL invocations.

Use an existing Python environment by absolute path for a worker checkout if
its dependencies match requirements.txt; otherwise create a dedicated venv.
Run configure.py inside the worker checkout to generate its own build files.
Keep permuter worker counts modest while both agents are compiling.

## Handoff and integration

Workers provide the issue, branch, PR, changed functions/files, original compiler
comparison results, full local matching result, pytest/Ruff result, CI status,
remaining limitations and suggested progress-note changes.

CI runs Python lint/format and synthetic tests. It has no game files or PS2
toolchain. A matching claim additionally requires the original ee-gcc 2.96
with -O2 -G0, code/data/relocation validation and a full local ninja check.
Park nonmatching attempts in draft PRs and do not count them as decompiled.

Claude serializes merges. If main changes, update the next branch without
force-pushing, resolve conflicts and repeat affected local checks and CI before
merging. Then delete its remote branch and remove the clean worker worktree.
Retain uncommitted experiments and required ignored evidence before cleanup.

## Initial handoff (2026-10-14)

Setup issue: #204. The original checkout is reserved for Claude, including its
unfinished issues #192, #195, #196, #199, #200, #201 and #202. Codex must not
include those local changes in its branches. Existing parked sword, stage-context
and display-list getter PRs are also reserved until Claude reassigns them.

Codex setup branch: codex/204-coordination. The initial local worker path is
`.worktrees/codex-coordination`. Subsequent tasks get separate branches/worktrees.
Claude Code must be authenticated before an automated coordinator session can
start. An existing interactive Claude session should read this file and the
setup PR, acknowledge outstanding worker claims, and own integration thereafter.
