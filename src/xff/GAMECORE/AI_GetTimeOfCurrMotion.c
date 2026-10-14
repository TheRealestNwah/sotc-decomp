typedef struct {
    char pad0[0x50];
    char frames[0xC];
    int fps;
} MotionResource;

typedef struct {
    MotionResource *res;
    char pad4[0x28];
    float rate;
} MotionState;

typedef struct {
    char pad0[0x44];
    float speed;
} MotionCtrl;

typedef struct {
    char pad0[0x1C0];
    MotionState motion;
    char pad1F0[0xF50];
    MotionCtrl *ctrl;
} AIObj;

extern int GetMotionResourceFrames(void *);

float AI_GetTimeOfCurrMotion(AIObj *obj, float scale)
{
    MotionState *m = &obj->motion;
    MotionResource *res = m->res;

    if (res != 0) {
        float speed = obj->ctrl->speed;

        return GetMotionResourceFrames(res->frames) * m->rate / (res->fps * speed * scale);
    }
    return 0.0f;
}
