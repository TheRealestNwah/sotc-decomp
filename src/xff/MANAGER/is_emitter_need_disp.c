typedef struct {
    char pad0[0x124];
    int count;
    char pad128[0x18];
    float alpha;
} Emitter;

extern int func_000BFF48(void);

int is_emitter_need_disp(Emitter *e)
{
    if (e != 0 && e->count > 0 && func_000BFF48() == 0 && e->alpha > 0.0f) {
        return 1;
    }
    return 0;
}
