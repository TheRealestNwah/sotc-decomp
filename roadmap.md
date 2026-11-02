# Roadmap

Last reviewed: 2026-11-02.

Planned work before 1.0 lives here. Keep this file current as plans change and
work lands. Community requests come in as feature-request issues on GitHub
and stay there; this roadmap can link to them when relevant. Discovered bugs
also get issues. Planned build tasks do not need individual issues. Unchecked items are future
work, not a release-date or feature commitment.

## Completed foundations

- [x] Verify the hash of the Original NTSC-U Loader.
- [x] Split the Loader with splat and rebuild its loaded bytes exactly.
- [x] Reverse the xff2 format and reproduce Game module sections and relocations.
- [x] Rebuild all three complete Game modules byte-for-byte, retaining original
  table-layout and loader metadata from the owner's disc.
- [x] Identify Sony ee-gcc 2.96 with `-O2 -G0` and its original assembler, and
  establish the matching-C compile, splice and verification workflow.
- [x] Run Python lint, format checks and synthetic tool tests in PR CI.

## Current phase: matching decompilation

The Loader rebuilds from assembly; only part of the Game code in the Game modules
is Matched functions so far. The Native port has not started. See the [README](README.md#status)
for Matched function counts and [binary findings](docs/findings.md) for evidence.
CI has no disc files or PS2 toolchain, so passing CI alone does not prove matching.

- [ ] Match the remaining Game code functions, including their data,
  constants, original interfaces and Source groups.
- [ ] Match the remaining Game code in the Loader and identify linked SDK routines by
  signature rather than decompiling them by hand.
- [ ] Continue small sound-slot, sprite-menu, geometry, motion, ambient, weak-point
  fade and flag helper batches.
- [ ] Finish GAMECORE `sword.c`, including `nico_swordstart`, collision callbacks
  `T_000C1D80` / `T_000C2620`, and `DispWithSwordBlur` / `DispWithTorchBlur`.
- [ ] Match `GetStageContext` and `createWormCtrlWork` resource initialization.
- [ ] Match KERNEL `Sg2SmfpSetParam` and the timed pan/volume setters
  `Sg2SlotSetTimePanParam` / `Sg2SlotSetTimeVolParam`.
- [ ] Resolve register allocation for `nico_optBoneParentScaleUpdateScript`.
- [ ] Identify KERNEL's SDK routines by signature, and fix the README progress
  table so it counts only Game code ([#2285](https://github.com/TheRealestNwah/sotc-decomp/issues/2285)).
- [ ] Sort the Loader's 1,038 functions into SDK routines and Game code, then
  match only its Game code ([ADR 0004](docs/adr/0004-finish-line-and-source-cleanup.md)).

The remaining matching tasks above preserve the plans formerly tracked in
closed issues #18, #51, #52, #54, #55, #107, #208, #459, #460, #513 and #520.
Closing those planning issues did not mark their work complete. Parked
attempts (`NONMATCHING` C) remain uncounted until independently verified with the
original compiler/assembler, full local binary checks and passing PR CI.

### Parked matching targets

Planned matching work formerly filed as individual issues; each is a Parked attempt. Each closed issue keeps
its investigation notes (best attempts, differing instructions, blockers); read
them before retrying a target. New matching work goes straight to a PR.

- [ ] Match interrupt-handler registration ([#729](https://github.com/TheRealestNwah/sotc-decomp/issues/729))
- [ ] Match camera aim-rotation update dispatch ([#760](https://github.com/TheRealestNwah/sotc-decomp/issues/760))
- [ ] Match KERNEL loader entry initialization ([#844](https://github.com/TheRealestNwah/sotc-decomp/issues/844))
- [ ] Match KERNEL sequence-slot initialization ([#845](https://github.com/TheRealestNwah/sotc-decomp/issues/845))
- [ ] Match KERNEL module relocation dispatch ([#847](https://github.com/TheRealestNwah/sotc-decomp/issues/847))
- [ ] Match centered display viewport setup ([#862](https://github.com/TheRealestNwah/sotc-decomp/issues/862))
- [ ] Match manager partition configuration ([#898](https://github.com/TheRealestNwah/sotc-decomp/issues/898))
- [ ] Match ConstructorCollisionDynamics ([#912](https://github.com/TheRealestNwah/sotc-decomp/issues/912))
- [ ] Match FlushModifiedManagerCB ([#931](https://github.com/TheRealestNwah/sotc-decomp/issues/931))
- [ ] Match Sg2SlotSetLfoPitchSpeed ([#936](https://github.com/TheRealestNwah/sotc-decomp/issues/936))
- [ ] Match forced LWS camera movie end ([#940](https://github.com/TheRealestNwah/sotc-decomp/issues/940))
- [ ] Match effect_blood_frame ([#947](https://github.com/TheRealestNwah/sotc-decomp/issues/947))
- [ ] Match getFallenLeafSize ([#951](https://github.com/TheRealestNwah/sotc-decomp/issues/951))
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
- [ ] Match root-dynamics local offset transform ([#1261](https://github.com/TheRealestNwah/sotc-decomp/issues/1261))
- [ ] Match character geometry preprocessing ([#1322](https://github.com/TheRealestNwah/sotc-decomp/issues/1322))
- [ ] Match alias layout initialization ([#1325](https://github.com/TheRealestNwah/sotc-decomp/issues/1325))
- [ ] Match character geometry dynamics reset ([#1329](https://github.com/TheRealestNwah/sotc-decomp/issues/1329))
- [ ] Match KERNEL Sg2SlotBlock ([#1349](https://github.com/TheRealestNwah/sotc-decomp/issues/1349))
- [ ] Match KERNEL Sg2SlotSetPitch ([#1351](https://github.com/TheRealestNwah/sotc-decomp/issues/1351))
- [ ] Match animation-class current info with a direct motion resource ([#1353](https://github.com/TheRealestNwah/sotc-decomp/issues/1353))
- [ ] Match character option-node motion interpolation ([#1363](https://github.com/TheRealestNwah/sotc-decomp/issues/1363))
- [ ] Match character IK node boolean-info query ([#1365](https://github.com/TheRealestNwah/sotc-decomp/issues/1365))
- [ ] Match character-class geometry query helpers ([#1372](https://github.com/TheRealestNwah/sotc-decomp/issues/1372))
- [ ] Match texScaleClut ([#1394](https://github.com/TheRealestNwah/sotc-decomp/issues/1394))
- [ ] Match MANAGER glRotatex, glRotatey and glRotatez ([#1411](https://github.com/TheRealestNwah/sotc-decomp/issues/1411))
- [ ] Match distant-light envelope type query ([#1420](https://github.com/TheRealestNwah/sotc-decomp/issues/1420))
- [ ] Match sprite-menu layer lookup by hash ([#1422](https://github.com/TheRealestNwah/sotc-decomp/issues/1422))
- [ ] Match maximum-gauge addition effect initialization ([#1423](https://github.com/TheRealestNwah/sotc-decomp/issues/1423))
- [ ] Match player-one button-state query ([#1430](https://github.com/TheRealestNwah/sotc-decomp/issues/1430))
- [ ] Match geometry virtual surface-plane query ([#1445](https://github.com/TheRealestNwah/sotc-decomp/issues/1445))
- [ ] Match root-dynamics collision filter and result callbacks ([#1451](https://github.com/TheRealestNwah/sotc-decomp/issues/1451))
- [ ] Match camera animation parameter lookup by name ([#1505](https://github.com/TheRealestNwah/sotc-decomp/issues/1505))
- [ ] Match camera state nonnegative-value predicate ([#1510](https://github.com/TheRealestNwah/sotc-decomp/issues/1510))
- [ ] Match camera animation data query ([#1512](https://github.com/TheRealestNwah/sotc-decomp/issues/1512))
- [ ] Match main camera animation sampler ([#1517](https://github.com/TheRealestNwah/sotc-decomp/issues/1517))
- [ ] Match camera animation boot path ([#1519](https://github.com/TheRealestNwah/sotc-decomp/issues/1519))
- [ ] Match controlled yaw merge query ([#1523](https://github.com/TheRealestNwah/sotc-decomp/issues/1523))
- [ ] Match additional player-demo cloth collision reset ([#1527](https://github.com/TheRealestNwah/sotc-decomp/issues/1527))
- [ ] Match player life-bar effect dispatch ([#1528](https://github.com/TheRealestNwah/sotc-decomp/issues/1528))
- [ ] Match LWS geometry update without parent change ([#1529](https://github.com/TheRealestNwah/sotc-decomp/issues/1529))
- [ ] Match sprite-menu all-layer priority setter ([#1538](https://github.com/TheRealestNwah/sotc-decomp/issues/1538))
- [ ] Match camera context construction ([#1539](https://github.com/TheRealestNwah/sotc-decomp/issues/1539))
- [ ] Match AI vector-to-yaw quaternion helper ([#1555](https://github.com/TheRealestNwah/sotc-decomp/issues/1555))
- [ ] Match user-thread creation ([#1576](https://github.com/TheRealestNwah/sotc-decomp/issues/1576))
- [ ] Match system object group pool initialization ([#1584](https://github.com/TheRealestNwah/sotc-decomp/issues/1584))
- [ ] Match packed color to float-vector conversion ([#1585](https://github.com/TheRealestNwah/sotc-decomp/issues/1585))
- [ ] Match vibration request dispatcher ([#1586](https://github.com/TheRealestNwah/sotc-decomp/issues/1586))
- [ ] Match group-scoped module resolution ([#1587](https://github.com/TheRealestNwah/sotc-decomp/issues/1587))
- [ ] Match stable yaw quaternion output helper ([#1592](https://github.com/TheRealestNwah/sotc-decomp/issues/1592))
- [ ] Match executable module read dispatch ([#1593](https://github.com/TheRealestNwah/sotc-decomp/issues/1593))
- [ ] Match automatic BGM start slot allocation ([#1596](https://github.com/TheRealestNwah/sotc-decomp/issues/1596))
- [ ] Match particle alpha blend packet emission ([#1597](https://github.com/TheRealestNwah/sotc-decomp/issues/1597))
- [ ] Match graphics processor thread startup ([#1598](https://github.com/TheRealestNwah/sotc-decomp/issues/1598))
- [ ] Match extended PCM output opening ([#1634](https://github.com/TheRealestNwah/sotc-decomp/issues/1634))
- [ ] Match diagnostic existing-file open and record lifecycle ([#1638](https://github.com/TheRealestNwah/sotc-decomp/issues/1638))
- [ ] Match camera reverb selection from global lighting ([#1640](https://github.com/TheRealestNwah/sotc-decomp/issues/1640))
- [ ] Match direct PCM output filter setup ([#1641](https://github.com/TheRealestNwah/sotc-decomp/issues/1641))
- [ ] Match parent character collision attribute query ([#1645](https://github.com/TheRealestNwah/sotc-decomp/issues/1645))
- [ ] Match particle work recycling into the free list ([#1647](https://github.com/TheRealestNwah/sotc-decomp/issues/1647))
- [ ] Match extended user-path work initialization ([#1649](https://github.com/TheRealestNwah/sotc-decomp/issues/1649))
- [ ] Match boss-death effect parameter setup ([#1680](https://github.com/TheRealestNwah/sotc-decomp/issues/1680))
- [ ] Match direct-resource animation state frame update ([#1698](https://github.com/TheRealestNwah/sotc-decomp/issues/1698))
- [ ] Match isysGroupForNextForce iterator ([#1733](https://github.com/TheRealestNwah/sotc-decomp/issues/1733))
- [ ] Match angle movement time calculation ([#1736](https://github.com/TheRealestNwah/sotc-decomp/issues/1736))
- [ ] Match path connection-point lookup ([#1738](https://github.com/TheRealestNwah/sotc-decomp/issues/1738))
- [ ] Match module relocation-element disposal ([#1740](https://github.com/TheRealestNwah/sotc-decomp/issues/1740))
- [ ] Match distance crossing coefficient roots ([#1765](https://github.com/TheRealestNwah/sotc-decomp/issues/1765))
- [ ] Match st_WaitGPFinish ([#1791](https://github.com/TheRealestNwah/sotc-decomp/issues/1791))
- [ ] Match iosWaitGPFinish ([#1792](https://github.com/TheRealestNwah/sotc-decomp/issues/1792))
- [ ] Match playerlifebar_effect ([#1793](https://github.com/TheRealestNwah/sotc-decomp/issues/1793))
- [ ] Match SpriteMenuSetLayer ([#1795](https://github.com/TheRealestNwah/sotc-decomp/issues/1795))
- [ ] Match GetMotionResourceTime ([#1797](https://github.com/TheRealestNwah/sotc-decomp/issues/1797))
- [ ] Match GAMEUTIL_is_between_yaw_and_yaw ([#1798](https://github.com/TheRealestNwah/sotc-decomp/issues/1798))
- [ ] Match get_merge_yaw_nico_yaw_pitch_cntrl ([#1835](https://github.com/TheRealestNwah/sotc-decomp/issues/1835))
- [ ] Match SpriteMenuSetLayerPriorityAllLayer ([#1836](https://github.com/TheRealestNwah/sotc-decomp/issues/1836))
- [ ] Match constructor_camera_context ([#1838](https://github.com/TheRealestNwah/sotc-decomp/issues/1838))
- [ ] Match stagemanager_refleshCurrentArea ([#1840](https://github.com/TheRealestNwah/sotc-decomp/issues/1840))
- [ ] Match ScriptAnimationObjCheckPositionInsideOfJudgeVolumeObject ([#1843](https://github.com/TheRealestNwah/sotc-decomp/issues/1843))
- [ ] Match CopyQuatPos ([#1856](https://github.com/TheRealestNwah/sotc-decomp/issues/1856))
- [ ] Match GetScriptAnimationObjResourcePlayTime ([#1858](https://github.com/TheRealestNwah/sotc-decomp/issues/1858))
- [ ] Match iosLoaderFOpen ([#1864](https://github.com/TheRealestNwah/sotc-decomp/issues/1864))
- [ ] Match Sg2ExStAdpcmOpenFake ([#1865](https://github.com/TheRealestNwah/sotc-decomp/issues/1865))
- [ ] Match SCRSetLWSGeometryWithNoParentChange ([#1873](https://github.com/TheRealestNwah/sotc-decomp/issues/1873))
- [ ] Match SCRFuncResetAcceleParamWormCtrlParam ([#1875](https://github.com/TheRealestNwah/sotc-decomp/issues/1875))
- [ ] Match SCRGetCollision ([#1878](https://github.com/TheRealestNwah/sotc-decomp/issues/1878))
- [ ] Match charrootdyn_setVColFindFlag ([#1879](https://github.com/TheRealestNwah/sotc-decomp/issues/1879))
- [ ] Match DebugDispManualEdgeCollisionFinder ([#1881](https://github.com/TheRealestNwah/sotc-decomp/issues/1881))
- [ ] Match CreateWindowObj ([#1882](https://github.com/TheRealestNwah/sotc-decomp/issues/1882))
- [ ] Match getStageLayout ([#1887](https://github.com/TheRealestNwah/sotc-decomp/issues/1887))
- [ ] Match FlushCollisionWork ([#1898](https://github.com/TheRealestNwah/sotc-decomp/issues/1898))
- [ ] Match ClipCollisionFinder4D ([#1960](https://github.com/TheRealestNwah/sotc-decomp/issues/1960))
- [ ] Match ClipCollisionFinderFarPlane ([#1961](https://github.com/TheRealestNwah/sotc-decomp/issues/1961))
- [ ] Match ClipCollisionFinderFarPlaneWithKeep ([#1966](https://github.com/TheRealestNwah/sotc-decomp/issues/1966))
- [ ] Match ClipCollisionFinderFarPlaneWithKeep4D ([#1967](https://github.com/TheRealestNwah/sotc-decomp/issues/1967))
- [ ] Match func_000AE618 ([#1972](https://github.com/TheRealestNwah/sotc-decomp/issues/1972))
- [ ] Match ClipCollisionFinderWithVariableKeepCB ([#1973](https://github.com/TheRealestNwah/sotc-decomp/issues/1973))
- [ ] Match ClipCollisionFinderWithVariableKeep4DCB ([#1979](https://github.com/TheRealestNwah/sotc-decomp/issues/1979))
- [ ] Match updateParticleDissolveGeo ([#1983](https://github.com/TheRealestNwah/sotc-decomp/issues/1983))
- [ ] Match get_particle_parameter_blend_disp ([#1984](https://github.com/TheRealestNwah/sotc-decomp/issues/1984))
- [ ] Match func_000CAA40 ([#1985](https://github.com/TheRealestNwah/sotc-decomp/issues/1985))
- [ ] Match func_000CA9E0 ([#1986](https://github.com/TheRealestNwah/sotc-decomp/issues/1986))
- [ ] Match sheetMgrAllReqWait ([#1988](https://github.com/TheRealestNwah/sotc-decomp/issues/1988))
- [ ] Match doit_camera_target_visible_angle_manager ([#1989](https://github.com/TheRealestNwah/sotc-decomp/issues/1989))
- [ ] Match adpcmPlay ([#1991](https://github.com/TheRealestNwah/sotc-decomp/issues/1991))
- [ ] Match adpcmMgrInit ([#1992](https://github.com/TheRealestNwah/sotc-decomp/issues/1992))
- [ ] Match DebugDispVolumeAllColor ([#1994](https://github.com/TheRealestNwah/sotc-decomp/issues/1994))
- [ ] Match DebugDispVolumeAll ([#1995](https://github.com/TheRealestNwah/sotc-decomp/issues/1995))
- [ ] Match EntryScriptAnimationObjJudgeVolumeGroup ([#1996](https://github.com/TheRealestNwah/sotc-decomp/issues/1996))
- [ ] Match charrootdyn_checkUnderWater ([#1998](https://github.com/TheRealestNwah/sotc-decomp/issues/1998))
- [ ] Match doit_camera_place_status ([#2038](https://github.com/TheRealestNwah/sotc-decomp/issues/2038))
- [ ] Match func_000F2700 ([#2040](https://github.com/TheRealestNwah/sotc-decomp/issues/2040))
- [ ] Match is_base_default_dir_attr_change_game_camera_param_manager ([#2041](https://github.com/TheRealestNwah/sotc-decomp/issues/2041))
- [ ] Match doit_neck_turn ([#2042](https://github.com/TheRealestNwah/sotc-decomp/issues/2042))
- [ ] Match globalLightCalcLightNum ([#2044](https://github.com/TheRealestNwah/sotc-decomp/issues/2044))
- [ ] Match ClipEdgeLinkDBFinder ([#2046](https://github.com/TheRealestNwah/sotc-decomp/issues/2046))
- [ ] Match FlushJudgeVolumeObjImmediate ([#2048](https://github.com/TheRealestNwah/sotc-decomp/issues/2048))
- [ ] Match CollisionObjectJudgeCallbackExceptDescendPluralObj ([#2049](https://github.com/TheRealestNwah/sotc-decomp/issues/2049))
- [ ] Match mouseInit ([#2050](https://github.com/TheRealestNwah/sotc-decomp/issues/2050))
- [ ] Match usbdevAddCallbackFunc ([#2052](https://github.com/TheRealestNwah/sotc-decomp/issues/2052))
- [ ] Match nico_player_avoid_ControlRootY ([#2053](https://github.com/TheRealestNwah/sotc-decomp/issues/2053))
- [ ] Match initAmbientLightObj ([#2056](https://github.com/TheRealestNwah/sotc-decomp/issues/2056))
- [ ] Match createYesNoDialog ([#2058](https://github.com/TheRealestNwah/sotc-decomp/issues/2058))
- [ ] Match createStringInputDialog ([#2060](https://github.com/TheRealestNwah/sotc-decomp/issues/2060))
- [ ] Match createSheetMenu ([#2062](https://github.com/TheRealestNwah/sotc-decomp/issues/2062))
- [ ] Match bgmDemoPackagePlay ([#2064](https://github.com/TheRealestNwah/sotc-decomp/issues/2064))
- [ ] Match bgmStandby ([#2065](https://github.com/TheRealestNwah/sotc-decomp/issues/2065))
- [ ] Match SetStageManagerAreaPreload ([#2067](https://github.com/TheRealestNwah/sotc-decomp/issues/2067))
- [ ] Match ResetAnimeFrameTableInfo ([#2068](https://github.com/TheRealestNwah/sotc-decomp/issues/2068))
- [ ] Match DebugControl ([#2069](https://github.com/TheRealestNwah/sotc-decomp/issues/2069))
- [ ] Match get_animation_designer_node_quater_motion_ik_base ([#2070](https://github.com/TheRealestNwah/sotc-decomp/issues/2070))
- [ ] Match get_animation_designer_node_rotXYZ_motion_ik_base ([#2071](https://github.com/TheRealestNwah/sotc-decomp/issues/2071))
- [ ] Match SequenceKickParticle ([#2073](https://github.com/TheRealestNwah/sotc-decomp/issues/2073))
- [ ] Match GetAnimationEffectDefByName ([#2074](https://github.com/TheRealestNwah/sotc-decomp/issues/2074))
- [ ] Match graphFrameInit ([#2075](https://github.com/TheRealestNwah/sotc-decomp/issues/2075))
- [ ] Match SpriteMenuGetPartsDefByHash ([#2076](https://github.com/TheRealestNwah/sotc-decomp/issues/2076))
- [ ] Match _initstage ([#2078](https://github.com/TheRealestNwah/sotc-decomp/issues/2078))
- [ ] Match SearchJudgeVolumeByName ([#2079](https://github.com/TheRealestNwah/sotc-decomp/issues/2079))
- [ ] Match graphFrameFinish ([#2080](https://github.com/TheRealestNwah/sotc-decomp/issues/2080))
- [ ] Match get_particle_effect_id_by_name ([#2081](https://github.com/TheRealestNwah/sotc-decomp/issues/2081))
- [ ] Match get_camera_region_resource_id_by_name ([#2083](https://github.com/TheRealestNwah/sotc-decomp/issues/2083))
- [ ] Match get_wind_effect_data ([#2084](https://github.com/TheRealestNwah/sotc-decomp/issues/2084))
- [ ] Match getPosPQSAnimIntFrame ([#2085](https://github.com/TheRealestNwah/sotc-decomp/issues/2085))
- [ ] Match sheetMgrSpecialFsEnd ([#2086](https://github.com/TheRealestNwah/sotc-decomp/issues/2086))
- [ ] Match graphInit ([#2088](https://github.com/TheRealestNwah/sotc-decomp/issues/2088))
- [ ] Match graphFrameBufferReInitialize ([#2089](https://github.com/TheRealestNwah/sotc-decomp/issues/2089))
- [ ] Match CreateLightColMan ([#2090](https://github.com/TheRealestNwah/sotc-decomp/issues/2090))
- [ ] Match GetCollisionDBAttributeAdr ([#2091](https://github.com/TheRealestNwah/sotc-decomp/issues/2091))
- [ ] Match GetCollisionDBAttribute ([#2093](https://github.com/TheRealestNwah/sotc-decomp/issues/2093))
- [ ] Match GetCollisionDBVertexPoint ([#2094](https://github.com/TheRealestNwah/sotc-decomp/issues/2094))
- [ ] Match GetCollisionDBEdgeVertexPoint ([#2095](https://github.com/TheRealestNwah/sotc-decomp/issues/2095))
- [ ] Match GetCollisionEdgePointerOtherSideCollisionEdge ([#2097](https://github.com/TheRealestNwah/sotc-decomp/issues/2097))
- [ ] Match GetCollisionWorkSize ([#2098](https://github.com/TheRealestNwah/sotc-decomp/issues/2098))
- [ ] Match player_setWeaponScriptSwitch ([#2099](https://github.com/TheRealestNwah/sotc-decomp/issues/2099))
- [ ] Match gameflowJumpOp2DemoSkip ([#2100](https://github.com/TheRealestNwah/sotc-decomp/issues/2100))
- [ ] Match FinishCharacterObjAllAdditionMotion ([#2101](https://github.com/TheRealestNwah/sotc-decomp/issues/2101))
- [ ] Match InitJudgeVolumeClass ([#2103](https://github.com/TheRealestNwah/sotc-decomp/issues/2103))
- [ ] Match DEBUG_get_cur_using_anb_file_name ([#2104](https://github.com/TheRealestNwah/sotc-decomp/issues/2104))
- [ ] Match func_000D5CA8 ([#2106](https://github.com/TheRealestNwah/sotc-decomp/issues/2106))

## Next phase: Source cleanup

Matching is finished when every Game code function in the Loader and the three
Game modules is a Matched function; SDK routines only need identifying
([ADR 0004](docs/adr/0004-finish-line-and-source-cleanup.md)). Source cleanup
then reorganizes the source while the Matching build keeps matching.

- [ ] Shared headers first: one definition of each struct and prototype, used by
  every file that needs it.
- [ ] Merge Source groups into Original source files, one Game module per thread.
- [ ] Replace Placeholder names with descriptive ones as purposes become known
  (runs alongside the rest).

## Native port

Decisions are recorded in [ADRs 0005 to 0016](docs/adr/). In short: one source
tree with a build macro, Windows x64 first, SDL3 and SDL_GPU, CMake and Clang,
SDK routines replaced by a Platform layer, a Render translator for the game's
GS packets and VU1 microprograms, the game's own Sound driver ported to C, saves
as memory card folders, EE threads as fibers, a 4 GB arena with 32-bit offset
pointers, and Reference runs against PCSX2 as the main check. Assets come from
the owner's own Disc image; no Original game binaries or assets are distributed.
Scope is NTSC-U only for now, and network and `host0` debug code is compiled out
of the port.

### Groundwork that can start now

These don't need cleaned-up source, so they run alongside matching.

- [ ] Owner dumps a full Disc image into `iso/` (needed for `NICO.DAT` and
  `SG2IOPM1.IRX`; `iso/` currently holds only the executables).
- [ ] Disc image reader and `NICO.DAT` archive parser, with asset-free tests on
  synthetic data.
- [ ] Reference run recording: capture inputs and per-frame game state from the
  Matching build in PCSX2.
- [ ] Render translator prototype fed from PCSX2 GS dumps, starting with
  hand-translating the roughly 14 VU1 microprogram overlay sets into C and
  checking them against PCSX2's VU1 output.

### Milestones

Port code built from the game's source starts once Source cleanup has shared
headers.

- [ ] M1: boots to the title screen.
- [ ] M2: the first colossus is playable.
- [ ] M3: a full playthrough matches its Reference run.
- [ ] Investigate original error-path contracts and address confirmed defects
  deliberately, with regression coverage. Current tracked concerns include the
  [sheet lookup missing-header read (#492)](https://github.com/TheRealestNwah/sotc-decomp/issues/492),
  [AI damage checks reading before a null guard (#490)](https://github.com/TheRealestNwah/sotc-decomp/issues/490),
  and [sequence stop using uncaptured interrupt state (#708)](https://github.com/TheRealestNwah/sotc-decomp/issues/708).
  Preserve exact original behavior during the matching phase.
- [ ] After M3: Linux, then macOS, then Port features.

The port ships as source only until M3. After that, prebuilt binaries may go on
GitHub Releases, each with the maintainer's explicit permission and never with
Original game files.

### Community proposals awaiting scope decisions

[Feature request #498](https://github.com/TheRealestNwah/sotc-decomp/issues/498)
asks for Xbox-style controls, keyboard/mouse input, improved textures and
anti-aliasing, FSR, uncapped frame rates, and a launcher section for patches and
mods. These are Port features, considered only after M3; they are not accepted 1.0
requirements.

A release or tag still requires explicit maintainer permission.
