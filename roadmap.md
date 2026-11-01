# Roadmap

Last reviewed: 2026-10-18.

Planned work before 1.0 lives here. Keep this file current as plans change and
work lands. Community requests come in as feature-request issues on GitHub
and stay there; this roadmap can link to them when relevant. Discovered bugs
also get issues. Planned build tasks do not need individual issues. Unchecked items are future
work, not a release-date or feature commitment.

## Completed foundations

- [x] Verify the original NTSC-U executable hash.
- [x] Split the loader ELF with splat and rebuild its loaded bytes exactly.
- [x] Reverse the XFF module format and reproduce module sections and relocations.
- [x] Rebuild all three complete XFF files byte-for-byte, retaining original
  table-layout and loader metadata from the user's disc files.
- [x] Identify Sony ee-gcc 2.96 with `-O2 -G0` and its original assembler, and
  establish the matching-C compile, splice and verification workflow.
- [x] Run Python lint, format checks and synthetic tool tests in PR CI.

## Current phase: matching decompilation

The loader rebuilds from assembly; the game modules are only partly recovered
as matching C. The native PC port has not started. See the [README](README.md#status)
for merged function counts and [binary findings](docs/findings.md) for evidence.
CI has no disc files or PS2 toolchain, so passing CI alone does not prove matching.

- [ ] Recover the remaining game functions as matching C, including their data,
  constants, original interfaces and source-file groupings.
- [ ] Recover remaining loader code and identify linked Sony SDK routines by
  signature rather than decompiling library code by hand.
- [ ] Continue small sound-slot, sprite-menu, geometry, motion, ambient, weak-point
  fade and flag helper batches.
- [ ] Finish GAMECORE `sword.c`, including `nico_swordstart`, collision callbacks
  `T_000C1D80` / `T_000C2620`, and `DispWithSwordBlur` / `DispWithTorchBlur`.
- [ ] Match `GetStageContext` and `createWormCtrlWork` resource initialization.
- [ ] Match KERNEL `Sg2SmfpSetParam` and the timed pan/volume setters
  `Sg2SlotSetTimePanParam` / `Sg2SlotSetTimeVolParam`.
- [ ] Resolve register allocation for `nico_optBoneParentScaleUpdateScript`.
- [ ] Reach complete matching source coverage before starting the native port.

The remaining matching tasks above preserve the plans formerly tracked in
closed issues #18, #51, #52, #54, #55, #107, #208, #459, #460, #513 and #520.
Closing those planning issues did not mark their work complete. Parked
`NONMATCHING` attempts remain uncounted until independently verified with the
original compiler/assembler, full local binary checks and passing PR CI.

### Parked matching targets

Planned matching work formerly filed as individual issues. Each closed issue keeps
its investigation notes (best attempts, differing instructions, blockers); read
them before retrying a target. New matching work goes straight to a PR.

- [ ] Recover interrupt-handler registration ([#729](https://github.com/TheRealestNwah/sotc-decomp/issues/729))
- [ ] Recover camera aim-rotation update dispatch ([#760](https://github.com/TheRealestNwah/sotc-decomp/issues/760))
- [ ] Recover KERNEL loader entry initialization ([#844](https://github.com/TheRealestNwah/sotc-decomp/issues/844))
- [ ] Recover KERNEL sequence-slot initialization ([#845](https://github.com/TheRealestNwah/sotc-decomp/issues/845))
- [ ] Recover KERNEL module relocation dispatch ([#847](https://github.com/TheRealestNwah/sotc-decomp/issues/847))
- [ ] Match centered display viewport setup ([#862](https://github.com/TheRealestNwah/sotc-decomp/issues/862))
- [ ] Match manager partition configuration ([#898](https://github.com/TheRealestNwah/sotc-decomp/issues/898))
- [ ] Recover ConstructorCollisionDynamics as matching C ([#912](https://github.com/TheRealestNwah/sotc-decomp/issues/912))
- [ ] Recover FlushModifiedManagerCB as matching C ([#931](https://github.com/TheRealestNwah/sotc-decomp/issues/931))
- [ ] Recover Sg2SlotSetLfoPitchSpeed as matching C ([#936](https://github.com/TheRealestNwah/sotc-decomp/issues/936))
- [ ] Recover forced LWS camera movie end as matching C ([#940](https://github.com/TheRealestNwah/sotc-decomp/issues/940))
- [ ] Recover effect_blood_frame as matching C ([#947](https://github.com/TheRealestNwah/sotc-decomp/issues/947))
- [ ] Recover getFallenLeafSize as matching C ([#951](https://github.com/TheRealestNwah/sotc-decomp/issues/951))
- [ ] Match collision edge link database initialization ([#968](https://github.com/TheRealestNwah/sotc-decomp/issues/968))
- [ ] Match script condition for executing gaze toward player ([#987](https://github.com/TheRealestNwah/sotc-decomp/issues/987))
- [ ] Match root dynamics slide exception collision callback ([#992](https://github.com/TheRealestNwah/sotc-decomp/issues/992))
- [ ] Match motion root information sampling ([#1011](https://github.com/TheRealestNwah/sotc-decomp/issues/1011))
  - 2026-11-01: declaring `func_0003A4A8` as `(float *, void *, int, float, float, int)` (count last) fixes the argument scheduling; the best draft is 7 diffs, only an s1/s2 swap of `obj`/`data` remains.
- [ ] Match calculation object work size ([#1083](https://github.com/TheRealestNwah/sotc-decomp/issues/1083))
- [ ] Match extended ADPCM track volume percentages ([#1084](https://github.com/TheRealestNwah/sotc-decomp/issues/1084))
- [ ] Match MANAGER mcGetInfo ([#1220](https://github.com/TheRealestNwah/sotc-decomp/issues/1220))
- [ ] Match KERNEL subthread execution start ([#1230](https://github.com/TheRealestNwah/sotc-decomp/issues/1230))
- [ ] Match MANAGER mesh creation ([#1242](https://github.com/TheRealestNwah/sotc-decomp/issues/1242))
- [ ] Match MANAGER boot-parent lookup ([#1244](https://github.com/TheRealestNwah/sotc-decomp/issues/1244))
- [ ] Recover root-dynamics local offset transform as matching C ([#1261](https://github.com/TheRealestNwah/sotc-decomp/issues/1261))
- [ ] Recover character geometry preprocessing as matching C ([#1322](https://github.com/TheRealestNwah/sotc-decomp/issues/1322))
- [ ] Recover alias layout initialization as matching C ([#1325](https://github.com/TheRealestNwah/sotc-decomp/issues/1325))
- [ ] Recover character geometry dynamics reset as matching C ([#1329](https://github.com/TheRealestNwah/sotc-decomp/issues/1329))
- [ ] Recover KERNEL Sg2SlotBlock as matching C ([#1349](https://github.com/TheRealestNwah/sotc-decomp/issues/1349))
- [ ] Recover KERNEL Sg2SlotSetPitch as matching C ([#1351](https://github.com/TheRealestNwah/sotc-decomp/issues/1351))
- [ ] Recover animation-class current info with a direct motion resource ([#1353](https://github.com/TheRealestNwah/sotc-decomp/issues/1353))
- [ ] Recover character option-node motion interpolation ([#1363](https://github.com/TheRealestNwah/sotc-decomp/issues/1363))
- [ ] Recover character IK node boolean-info query ([#1365](https://github.com/TheRealestNwah/sotc-decomp/issues/1365))
- [ ] Recover character-class geometry query helpers as matching C ([#1372](https://github.com/TheRealestNwah/sotc-decomp/issues/1372))
- [ ] Recover texScaleClut as matching C ([#1394](https://github.com/TheRealestNwah/sotc-decomp/issues/1394))
- [ ] Match MANAGER glRotatex, glRotatey and glRotatez ([#1411](https://github.com/TheRealestNwah/sotc-decomp/issues/1411))
- [ ] Recover distant-light envelope type query as matching C ([#1420](https://github.com/TheRealestNwah/sotc-decomp/issues/1420))
- [ ] Recover sprite-menu layer lookup by hash as matching C ([#1422](https://github.com/TheRealestNwah/sotc-decomp/issues/1422))
- [ ] Recover maximum-gauge addition effect initialization as matching C ([#1423](https://github.com/TheRealestNwah/sotc-decomp/issues/1423))
- [ ] Recover player-one button-state query as matching C ([#1430](https://github.com/TheRealestNwah/sotc-decomp/issues/1430))
- [ ] Recover geometry virtual surface-plane query as matching C ([#1445](https://github.com/TheRealestNwah/sotc-decomp/issues/1445))
- [ ] Recover root-dynamics collision filter and result callbacks ([#1451](https://github.com/TheRealestNwah/sotc-decomp/issues/1451))
- [ ] Recover camera animation parameter lookup by name as matching C ([#1505](https://github.com/TheRealestNwah/sotc-decomp/issues/1505))
- [ ] Recover camera state nonnegative-value predicate as matching C ([#1510](https://github.com/TheRealestNwah/sotc-decomp/issues/1510))
- [ ] Recover camera animation data query as matching C ([#1512](https://github.com/TheRealestNwah/sotc-decomp/issues/1512))
- [ ] Recover main camera animation sampler as matching C ([#1517](https://github.com/TheRealestNwah/sotc-decomp/issues/1517))
- [ ] Recover camera animation boot path as matching C ([#1519](https://github.com/TheRealestNwah/sotc-decomp/issues/1519))
- [ ] Recover controlled yaw merge query as matching C ([#1523](https://github.com/TheRealestNwah/sotc-decomp/issues/1523))
- [ ] Recover additional player-demo cloth collision reset as matching C ([#1527](https://github.com/TheRealestNwah/sotc-decomp/issues/1527))
- [ ] Recover player life-bar effect dispatch as matching C ([#1528](https://github.com/TheRealestNwah/sotc-decomp/issues/1528))
- [ ] Recover LWS geometry update without parent change as matching C ([#1529](https://github.com/TheRealestNwah/sotc-decomp/issues/1529))
- [ ] Recover sprite-menu all-layer priority setter as matching C ([#1538](https://github.com/TheRealestNwah/sotc-decomp/issues/1538))
- [ ] Recover camera context construction as matching C ([#1539](https://github.com/TheRealestNwah/sotc-decomp/issues/1539))
- [ ] Recover AI vector-to-yaw quaternion helper as matching C ([#1555](https://github.com/TheRealestNwah/sotc-decomp/issues/1555))
- [ ] Recover user-thread creation as matching C ([#1576](https://github.com/TheRealestNwah/sotc-decomp/issues/1576))
- [ ] Recover system object group pool initialization as matching C ([#1584](https://github.com/TheRealestNwah/sotc-decomp/issues/1584))
- [ ] Recover packed color to float-vector conversion as matching C ([#1585](https://github.com/TheRealestNwah/sotc-decomp/issues/1585))
- [ ] Recover vibration request dispatcher as matching C ([#1586](https://github.com/TheRealestNwah/sotc-decomp/issues/1586))
- [ ] Recover group-scoped module resolution as matching C ([#1587](https://github.com/TheRealestNwah/sotc-decomp/issues/1587))
- [ ] Recover stable yaw quaternion output helper as matching C ([#1592](https://github.com/TheRealestNwah/sotc-decomp/issues/1592))
- [ ] Recover executable module read dispatch as matching C ([#1593](https://github.com/TheRealestNwah/sotc-decomp/issues/1593))
- [ ] Recover automatic BGM start slot allocation as matching C ([#1596](https://github.com/TheRealestNwah/sotc-decomp/issues/1596))
- [ ] Recover particle alpha blend packet emission as matching C ([#1597](https://github.com/TheRealestNwah/sotc-decomp/issues/1597))
- [ ] Recover graphics processor thread startup as matching C ([#1598](https://github.com/TheRealestNwah/sotc-decomp/issues/1598))
- [ ] Recover extended PCM output opening as matching C ([#1634](https://github.com/TheRealestNwah/sotc-decomp/issues/1634))
- [ ] Recover diagnostic existing-file open and record lifecycle as matching C ([#1638](https://github.com/TheRealestNwah/sotc-decomp/issues/1638))
- [ ] Recover camera reverb selection from global lighting as matching C ([#1640](https://github.com/TheRealestNwah/sotc-decomp/issues/1640))
- [ ] Recover direct PCM output filter setup as matching C ([#1641](https://github.com/TheRealestNwah/sotc-decomp/issues/1641))
- [ ] Recover parent character collision attribute query as matching C ([#1645](https://github.com/TheRealestNwah/sotc-decomp/issues/1645))
- [ ] Recover particle work recycling into the free list as matching C ([#1647](https://github.com/TheRealestNwah/sotc-decomp/issues/1647))
- [ ] Recover extended user-path work initialization as matching C ([#1649](https://github.com/TheRealestNwah/sotc-decomp/issues/1649))
- [ ] Recover boss-death effect parameter setup as matching C ([#1680](https://github.com/TheRealestNwah/sotc-decomp/issues/1680))
- [ ] Recover direct-resource animation state frame update ([#1698](https://github.com/TheRealestNwah/sotc-decomp/issues/1698))
- [ ] Recover isysGroupForNextForce iterator as matching C ([#1733](https://github.com/TheRealestNwah/sotc-decomp/issues/1733))
- [ ] Recover angle movement time calculation as matching C ([#1736](https://github.com/TheRealestNwah/sotc-decomp/issues/1736))
- [ ] Recover path connection-point lookup as matching C ([#1738](https://github.com/TheRealestNwah/sotc-decomp/issues/1738))
- [ ] Recover module relocation-element disposal as matching C ([#1740](https://github.com/TheRealestNwah/sotc-decomp/issues/1740))
- [ ] Recover distance crossing coefficient roots as matching C ([#1765](https://github.com/TheRealestNwah/sotc-decomp/issues/1765))
- [ ] Recover st_WaitGPFinish as matching C ([#1791](https://github.com/TheRealestNwah/sotc-decomp/issues/1791))
- [ ] Recover iosWaitGPFinish as matching C ([#1792](https://github.com/TheRealestNwah/sotc-decomp/issues/1792))
- [ ] Recover playerlifebar_effect as matching C ([#1793](https://github.com/TheRealestNwah/sotc-decomp/issues/1793))
- [ ] Recover SpriteMenuSetLayer as matching C ([#1795](https://github.com/TheRealestNwah/sotc-decomp/issues/1795))
- [ ] Recover GetMotionResourceTime as matching C ([#1797](https://github.com/TheRealestNwah/sotc-decomp/issues/1797))
- [ ] Recover GAMEUTIL_is_between_yaw_and_yaw as matching C ([#1798](https://github.com/TheRealestNwah/sotc-decomp/issues/1798))
- [ ] Recover get_merge_yaw_nico_yaw_pitch_cntrl as matching C ([#1835](https://github.com/TheRealestNwah/sotc-decomp/issues/1835))
- [ ] Recover SpriteMenuSetLayerPriorityAllLayer as matching C ([#1836](https://github.com/TheRealestNwah/sotc-decomp/issues/1836))
- [ ] Recover constructor_camera_context as matching C ([#1838](https://github.com/TheRealestNwah/sotc-decomp/issues/1838))
- [ ] Recover stagemanager_refleshCurrentArea as matching C ([#1840](https://github.com/TheRealestNwah/sotc-decomp/issues/1840))
- [ ] Recover ScriptAnimationObjCheckPositionInsideOfJudgeVolumeObject as matching C ([#1843](https://github.com/TheRealestNwah/sotc-decomp/issues/1843))
- [ ] Recover CopyQuatPos as matching C ([#1856](https://github.com/TheRealestNwah/sotc-decomp/issues/1856))
- [ ] Recover GetScriptAnimationObjResourcePlayTime as matching C ([#1858](https://github.com/TheRealestNwah/sotc-decomp/issues/1858))
- [ ] Recover iosLoaderFOpen as matching C ([#1864](https://github.com/TheRealestNwah/sotc-decomp/issues/1864))
- [ ] Recover Sg2ExStAdpcmOpenFake as matching C ([#1865](https://github.com/TheRealestNwah/sotc-decomp/issues/1865))
- [ ] Recover SCRSetLWSGeometryWithNoParentChange as matching C ([#1873](https://github.com/TheRealestNwah/sotc-decomp/issues/1873))
- [ ] Recover SCRFuncResetAcceleParamWormCtrlParam as matching C ([#1875](https://github.com/TheRealestNwah/sotc-decomp/issues/1875))
- [ ] Recover SCRGetCollision as matching C ([#1878](https://github.com/TheRealestNwah/sotc-decomp/issues/1878))
- [ ] Recover charrootdyn_setVColFindFlag as matching C ([#1879](https://github.com/TheRealestNwah/sotc-decomp/issues/1879))
- [ ] Recover DebugDispManualEdgeCollisionFinder as matching C ([#1881](https://github.com/TheRealestNwah/sotc-decomp/issues/1881))
- [ ] Recover CreateWindowObj as matching C ([#1882](https://github.com/TheRealestNwah/sotc-decomp/issues/1882))
- [ ] Recover getStageLayout as matching C ([#1887](https://github.com/TheRealestNwah/sotc-decomp/issues/1887))
- [ ] Recover FlushCollisionWork as matching C ([#1898](https://github.com/TheRealestNwah/sotc-decomp/issues/1898))
- [ ] Recover ClipCollisionFinder4D as matching C ([#1960](https://github.com/TheRealestNwah/sotc-decomp/issues/1960))
- [ ] Recover ClipCollisionFinderFarPlane as matching C ([#1961](https://github.com/TheRealestNwah/sotc-decomp/issues/1961))
- [ ] Recover ClipCollisionFinderFarPlaneWithKeep as matching C ([#1966](https://github.com/TheRealestNwah/sotc-decomp/issues/1966))
- [ ] Recover ClipCollisionFinderFarPlaneWithKeep4D as matching C ([#1967](https://github.com/TheRealestNwah/sotc-decomp/issues/1967))
- [ ] Recover func_000AE618 as matching C ([#1972](https://github.com/TheRealestNwah/sotc-decomp/issues/1972))
- [ ] Recover ClipCollisionFinderWithVariableKeepCB as matching C ([#1973](https://github.com/TheRealestNwah/sotc-decomp/issues/1973))
- [ ] Recover ClipCollisionFinderWithVariableKeep4DCB as matching C ([#1979](https://github.com/TheRealestNwah/sotc-decomp/issues/1979))
- [ ] Recover updateParticleDissolveGeo as matching C ([#1983](https://github.com/TheRealestNwah/sotc-decomp/issues/1983))
- [ ] Recover get_particle_parameter_blend_disp as matching C ([#1984](https://github.com/TheRealestNwah/sotc-decomp/issues/1984))
- [ ] Recover func_000CAA40 as matching C ([#1985](https://github.com/TheRealestNwah/sotc-decomp/issues/1985))
- [ ] Recover func_000CA9E0 as matching C ([#1986](https://github.com/TheRealestNwah/sotc-decomp/issues/1986))
- [ ] Recover sheetMgrAllReqWait as matching C ([#1988](https://github.com/TheRealestNwah/sotc-decomp/issues/1988))
- [ ] Recover doit_camera_target_visible_angle_manager as matching C ([#1989](https://github.com/TheRealestNwah/sotc-decomp/issues/1989))
- [ ] Recover adpcmPlay as matching C ([#1991](https://github.com/TheRealestNwah/sotc-decomp/issues/1991))
- [ ] Recover adpcmMgrInit as matching C ([#1992](https://github.com/TheRealestNwah/sotc-decomp/issues/1992))
- [ ] Recover DebugDispVolumeAllColor as matching C ([#1994](https://github.com/TheRealestNwah/sotc-decomp/issues/1994))
- [ ] Recover DebugDispVolumeAll as matching C ([#1995](https://github.com/TheRealestNwah/sotc-decomp/issues/1995))
- [ ] Recover EntryScriptAnimationObjJudgeVolumeGroup as matching C ([#1996](https://github.com/TheRealestNwah/sotc-decomp/issues/1996))
- [ ] Recover charrootdyn_checkUnderWater as matching C ([#1998](https://github.com/TheRealestNwah/sotc-decomp/issues/1998))
- [ ] Recover doit_camera_place_status as matching C ([#2038](https://github.com/TheRealestNwah/sotc-decomp/issues/2038))
- [ ] Recover func_000F2700 as matching C ([#2040](https://github.com/TheRealestNwah/sotc-decomp/issues/2040))
- [ ] Recover is_base_default_dir_attr_change_game_camera_param_manager as matching C ([#2041](https://github.com/TheRealestNwah/sotc-decomp/issues/2041))
- [ ] Recover doit_neck_turn as matching C ([#2042](https://github.com/TheRealestNwah/sotc-decomp/issues/2042))
- [ ] Recover globalLightCalcLightNum as matching C ([#2044](https://github.com/TheRealestNwah/sotc-decomp/issues/2044))
- [ ] Recover ClipEdgeLinkDBFinder as matching C ([#2046](https://github.com/TheRealestNwah/sotc-decomp/issues/2046))
- [ ] Recover FlushJudgeVolumeObjImmediate as matching C ([#2048](https://github.com/TheRealestNwah/sotc-decomp/issues/2048))
- [ ] Recover CollisionObjectJudgeCallbackExceptDescendPluralObj as matching C ([#2049](https://github.com/TheRealestNwah/sotc-decomp/issues/2049))
- [ ] Recover mouseInit as matching C ([#2050](https://github.com/TheRealestNwah/sotc-decomp/issues/2050))
- [ ] Recover usbdevAddCallbackFunc as matching C ([#2052](https://github.com/TheRealestNwah/sotc-decomp/issues/2052))
- [ ] Recover nico_player_avoid_ControlRootY as matching C ([#2053](https://github.com/TheRealestNwah/sotc-decomp/issues/2053))
- [ ] Recover initAmbientLightObj as matching C ([#2056](https://github.com/TheRealestNwah/sotc-decomp/issues/2056))
- [ ] Recover createYesNoDialog as matching C ([#2058](https://github.com/TheRealestNwah/sotc-decomp/issues/2058))
- [ ] Recover createStringInputDialog as matching C ([#2060](https://github.com/TheRealestNwah/sotc-decomp/issues/2060))
- [ ] Recover createSheetMenu as matching C ([#2062](https://github.com/TheRealestNwah/sotc-decomp/issues/2062))
- [ ] Recover bgmDemoPackagePlay as matching C ([#2064](https://github.com/TheRealestNwah/sotc-decomp/issues/2064))
- [ ] Recover bgmStandby as matching C ([#2065](https://github.com/TheRealestNwah/sotc-decomp/issues/2065))
- [ ] Recover SetStageManagerAreaPreload as matching C ([#2067](https://github.com/TheRealestNwah/sotc-decomp/issues/2067))
- [ ] Recover ResetAnimeFrameTableInfo as matching C ([#2068](https://github.com/TheRealestNwah/sotc-decomp/issues/2068))
- [ ] Recover DebugControl as matching C ([#2069](https://github.com/TheRealestNwah/sotc-decomp/issues/2069))
- [ ] Recover get_animation_designer_node_quater_motion_ik_base as matching C ([#2070](https://github.com/TheRealestNwah/sotc-decomp/issues/2070))
- [ ] Recover get_animation_designer_node_rotXYZ_motion_ik_base as matching C ([#2071](https://github.com/TheRealestNwah/sotc-decomp/issues/2071))
- [ ] Recover SequenceKickParticle as matching C ([#2073](https://github.com/TheRealestNwah/sotc-decomp/issues/2073))
- [ ] Recover GetAnimationEffectDefByName as matching C ([#2074](https://github.com/TheRealestNwah/sotc-decomp/issues/2074))
- [ ] Recover graphFrameInit as matching C ([#2075](https://github.com/TheRealestNwah/sotc-decomp/issues/2075))
- [ ] Recover SpriteMenuGetPartsDefByHash as matching C ([#2076](https://github.com/TheRealestNwah/sotc-decomp/issues/2076))
- [ ] Recover _initstage as matching C ([#2078](https://github.com/TheRealestNwah/sotc-decomp/issues/2078))
- [ ] Recover SearchJudgeVolumeByName as matching C ([#2079](https://github.com/TheRealestNwah/sotc-decomp/issues/2079))
- [ ] Recover graphFrameFinish as matching C ([#2080](https://github.com/TheRealestNwah/sotc-decomp/issues/2080))
- [ ] Recover get_particle_effect_id_by_name as matching C ([#2081](https://github.com/TheRealestNwah/sotc-decomp/issues/2081))
- [ ] Recover get_camera_region_resource_id_by_name as matching C ([#2083](https://github.com/TheRealestNwah/sotc-decomp/issues/2083))
- [ ] Recover get_wind_effect_data as matching C ([#2084](https://github.com/TheRealestNwah/sotc-decomp/issues/2084))
- [ ] Recover getPosPQSAnimIntFrame as matching C ([#2085](https://github.com/TheRealestNwah/sotc-decomp/issues/2085))
- [ ] Recover sheetMgrSpecialFsEnd as matching C ([#2086](https://github.com/TheRealestNwah/sotc-decomp/issues/2086))
- [ ] Recover graphInit as matching C ([#2088](https://github.com/TheRealestNwah/sotc-decomp/issues/2088))
- [ ] Recover graphFrameBufferReInitialize as matching C ([#2089](https://github.com/TheRealestNwah/sotc-decomp/issues/2089))
- [ ] Recover CreateLightColMan as matching C ([#2090](https://github.com/TheRealestNwah/sotc-decomp/issues/2090))
- [ ] Recover GetCollisionDBAttributeAdr as matching C ([#2091](https://github.com/TheRealestNwah/sotc-decomp/issues/2091))
- [ ] Recover GetCollisionDBAttribute as matching C ([#2093](https://github.com/TheRealestNwah/sotc-decomp/issues/2093))
- [ ] Recover GetCollisionDBVertexPoint as matching C ([#2094](https://github.com/TheRealestNwah/sotc-decomp/issues/2094))
- [ ] Recover GetCollisionDBEdgeVertexPoint as matching C ([#2095](https://github.com/TheRealestNwah/sotc-decomp/issues/2095))
- [ ] Recover GetCollisionEdgePointerOtherSideCollisionEdge as matching C ([#2097](https://github.com/TheRealestNwah/sotc-decomp/issues/2097))
- [ ] Recover GetCollisionWorkSize as matching C ([#2098](https://github.com/TheRealestNwah/sotc-decomp/issues/2098))
- [ ] Recover player_setWeaponScriptSwitch as matching C ([#2099](https://github.com/TheRealestNwah/sotc-decomp/issues/2099))
- [ ] Recover gameflowJumpOp2DemoSkip as matching C ([#2100](https://github.com/TheRealestNwah/sotc-decomp/issues/2100))
- [ ] Recover FinishCharacterObjAllAdditionMotion as matching C ([#2101](https://github.com/TheRealestNwah/sotc-decomp/issues/2101))
- [ ] Recover InitJudgeVolumeClass as matching C ([#2103](https://github.com/TheRealestNwah/sotc-decomp/issues/2103))
- [ ] Recover DEBUG_get_cur_using_anb_file_name as matching C ([#2104](https://github.com/TheRealestNwah/sotc-decomp/issues/2104))
- [ ] Recover func_000D5CA8 as matching C ([#2106](https://github.com/TheRealestNwah/sotc-decomp/issues/2106))

## Future phase: native PC port

- [ ] Build a native platform layer for graphics, audio and input after the
  matching decompilation is complete.
- [ ] Support loading the required assets from the user's own game copy; do not
  distribute original game binaries or assets.
- [ ] Investigate original error-path contracts before porting and address
  confirmed defects deliberately, with regression coverage. Current tracked
  concerns include the [sheet lookup missing-header read (#492)](https://github.com/TheRealestNwah/sotc-decomp/issues/492),
  [AI damage checks reading before a null guard (#490)](https://github.com/TheRealestNwah/sotc-decomp/issues/490),
  and [sequence stop using uncaptured interrupt state (#708)](https://github.com/TheRealestNwah/sotc-decomp/issues/708).
  Preserve exact original behavior during the matching phase.
- [ ] Define and validate supported platforms, packaging and runtime acceptance
  criteria before declaring a native 1.0 release ready.

### Community proposals awaiting scope decisions

[Feature request #498](https://github.com/TheRealestNwah/sotc-decomp/issues/498)
asks for Xbox-style controls, keyboard/mouse input, improved textures and
anti-aliasing, FSR, uncapped frame rates, and a launcher section for patches and
mods. These remain proposals to evaluate during port planning; they are not
accepted 1.0 requirements.

A release or tag still requires explicit maintainer permission.
