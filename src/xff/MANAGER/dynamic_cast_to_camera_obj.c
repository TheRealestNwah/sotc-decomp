typedef struct {
    char pad[8];
    unsigned char type;
} LayoutObj;

LayoutObj *dynamic_cast_to_camera_obj(LayoutObj *p)
{
    if (p->type != 0x11) {
        __asm__ __volatile__("break 0");
        return 0;
    }
    return p;
}
