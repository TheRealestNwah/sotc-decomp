typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 q;
} Vec4;

typedef struct {
    int id;
    int frame;
    int next;
    int pad0C;
    Vec4 rot;
    Vec4 rot_speed;
    Vec4 pos;
    Vec4 pos_speed;
    int unk50;
    int unk54;
    int pad58[2];
    Vec4 target;
    Vec4 target_speed;
    int unk80;
    int unk84;
    int unk88;
    float scale;
} CameraLwsAnimeData;

extern Vec4 ZeroPoint;
extern Vec4 ZeroVector;

void constructor_camera_lws_anime_data(CameraLwsAnimeData *d)
{
    d->id = -1;
    d->frame = 0;
    d->next = -1;
    d->rot = ZeroVector;
    d->rot_speed = ZeroVector;
    d->pos = ZeroPoint;
    d->pos_speed = ZeroPoint;
    d->unk50 = 0;
    d->unk54 = -1;
    d->target = ZeroPoint;
    d->target_speed = ZeroPoint;
    d->unk80 = 0;
    d->unk84 = 0;
    d->unk88 = 0;
    d->scale = 1.0f;
}
