extern char *iosMallocAlign(void *, int, int);
extern void *create_camera_obj(void *, void *, void *, float);
extern void constructor_game_camera(void *, void *);
extern void iosUnitMatrix(void *);

char *create_cameraman(void *ptn, void *a, void *b, void *c, void *d, void *e, void *f, float g)
{
    char *cm = iosMallocAlign(ptn, 0x3810, 0x10);

    *(void **)(cm + 0x0) = create_camera_obj(ptn, e, f, g);
    *(void **)(cm + 0x8) = a;
    *(void **)(cm + 0xC) = b;
    *(void **)(cm + 0x10) = c;
    *(void **)(cm + 0x14) = d;
    *(int *)(cm + 0x4) = 0;
    *(int *)(cm + 0x18) = 0;
    *(int *)(cm + 0x1C) = 0;
    constructor_game_camera(cm + 0x20, ptn);
    *(int *)(cm + 0x37C0) = 0;
    *(int *)(cm + 0x37C4) = 0;
    iosUnitMatrix(cm + 0x37D0);
    return cm;
}
