typedef struct {
    int unk0[7];
    float dist;
    float unk20;
    float unk24;
    float unk28;
    float unk2C;
    float unk30;
    float unk34;
    float fov;
    float unk3C;
} CameraModeLocal;

void constructor_game_camera_mode_local_parameter(CameraModeLocal *p)
{
    p->unk0[0] = 0;
    p->unk0[1] = 0;
    p->unk0[2] = 0;
    p->unk0[3] = 0;
    p->unk0[4] = 0;
    p->unk0[5] = 0;
    p->unk0[6] = 0;
    p->dist = 4.5f;
    p->unk20 = 2.0f;
    p->unk24 = 2.0f;
    p->unk28 = 2.0f;
    p->unk2C = 0.5f;
    p->unk30 = 0.5f;
    p->unk34 = 0.5f;
    p->fov = 45.0f;
    p->unk3C = 1.0f;
}
