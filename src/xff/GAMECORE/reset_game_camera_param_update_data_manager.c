extern char rootPtn[];
extern void iosFree(void *);
extern char *iosMallocAlign(void *, int, int);
extern void func_000ED5D8(void *);

typedef struct {
    int num;
    char *ents;
} UpdManager;

void reset_game_camera_param_update_data_manager(UpdManager *m, int n)
{
    int i;
    char *e;

    m->num = 0;
    if (m->ents != 0) {
        iosFree(m->ents);
        m->ents = 0;
    }
    m->num = n;
    m->ents = iosMallocAlign(rootPtn, n * 0x65C, 0x10);
    for (i = 0; i < n; i++) {
        e = (char *)(i * 0x65C + (int)m->ents);
        *(int *)(e + 0) = 0;
        *(int *)(e + 4) = 0;
        func_000ED5D8(e + 8);
    }
}
