# Marathon 3 near-misses (not built)

These drafts aren't in `src/`, so the build ignores them. The counts are differing words from `tools/try_compilers.py` (ee-gcc2.96 -O2 -G0) at the time they were parked.

| Function | Diffs | Notes |
| --- | --- | --- |
| doit_camera_view_angle_cntrl | 4 | Only the `exist == 1` branch differs, in the order of the `set_param` and `doit` argument loads |
| func_000BCA80 (static, called from playerlifebar_script) | 22 | Uses `bnel` where the original has `bnez` with a `lui` in the delay slot for the `__gameMode & 1` test; the final loop's registers are swapped |
| begin_and_update_get_yaw_pitch_camera_target_visible_angle_manager | 89 | Register allocation: the original keeps idx in s1, prev in s0 and next in s2 |
| nico_SmallKiteSpecialStart | 78 | The original uses 5 saved registers (its loop goes through a copy of `path`); the permuter stayed flat at 650 |
| chkAttainExecColumn | 51 | The permuter timed out at a best score of 175 |
| SCRFuncYamoriBSendKLeftStandUpLey | permuter 330 | The permuter's best output (`output-330-1/source.c`) |
| func_000ED408 (`func_000ED408_variants/`) | 6 best | The original's delay slots stay unfilled (nops) |

Delete `wip/` before any of this gets merged.
