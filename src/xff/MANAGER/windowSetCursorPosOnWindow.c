typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef struct { char pad[0x264]; float x; float y; } Window;
typedef struct { int unknown; Window *window; } WindowHandle;
extern Vec4 D_00139B90;
extern void mouseSetCursorPosition(float, float);
extern void *memset(void *, int, unsigned int);
void windowSetCursorPosOnWindow(WindowHandle *handle, Vec4 *position)
{
    Vec4 absolute;
    char *state = (char *)&D_00139B90;
    Window *window = handle->window;
    memset(&absolute, 0, sizeof(absolute));
    absolute.f[0] = position->f[0] + window->x;
    absolute.f[1] = position->f[1] + window->y;
    ((Vec4 *)state)->q = absolute.q;
    state -= 0x10;
    mouseSetCursorPosition(absolute.f[0], absolute.f[1]);
    (*(Vec4 **)(state + 4))->f[0] = absolute.f[0];
    (*(Vec4 **)(state + 4))->f[1] = absolute.f[1];
}
