extern void *GetSCRCharaAIWorkPtr(void *);

extern void boot_camera_lws_animation_by_script(void *param);

extern void *SCameraLwsAnimationParam_PLAYER_ACCUMULATE_ATTACK_CAM_VIB;

void SCRPlayerBeginAccumulateAttack(void *actor)
{
    *(int *)((char *)GetSCRCharaAIWorkPtr(actor) + 0xD8C) = 1;
    boot_camera_lws_animation_by_script(SCameraLwsAnimationParam_PLAYER_ACCUMULATE_ATTACK_CAM_VIB);
}
