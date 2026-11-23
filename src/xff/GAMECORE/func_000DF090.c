extern int CAM_get_ground_contact_obj(void *);
extern char *GAMEUTIL_get_motion_kind(int);
extern void func_000E2358(void *, void *, float, float);

static void func_000DF090(char *c, char *b, float t)
{
    int obj;
    char *kind;
    int k;
    float w;

    obj = CAM_get_ground_contact_obj(b + 0x23C);
    if (obj != 0) {
        kind = GAMEUTIL_get_motion_kind(obj);
        if (kind != 0)
            k = *(int *)(kind + 0x6C) & 0xF;
        else
            k = 1;
    } else {
        k = 1;
    }
    w = 0.0f;
    if (k == 1 || k == 2)
        w = 1.0f;
    func_000E2358(c + 0x60, c + 0x80, w, t);
    w = 0.0f;
    if (k == 1 || k == 3)
        w = 1.0f;
    func_000E2358(c + 0x8C, c + 0xAC, w, t);
    w = 0.0f;
    if (k == 1 || k == 4)
        w = 1.0f;
    func_000E2358(c + 0xB8, c + 0xD8, w, t);
    w = 0.0f;
    if (k == 1 || k == 5)
        w = 1.0f;
    func_000E2358(c + 0xE4, c + 0x104, w, t);
    w = 0.0f;
    if (k == 1 || k == 6)
        w = 1.0f;
    func_000E2358(c + 0x110, c + 0x130, w, t);
    w = 0.0f;
    if (k == 1 || k == 7)
        w = 1.0f;
    func_000E2358(c + 0x13C, c + 0x15C, w, t);
}
