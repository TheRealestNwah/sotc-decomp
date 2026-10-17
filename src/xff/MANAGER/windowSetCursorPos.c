typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern Vec4 D_00139B90;
extern void mouseSetCursorPosition(float, float);
void windowSetCursorPos(Vec4 *position)
{
    char *state = (char *)&D_00139B90;
    ((Vec4 *)state)->q = position->q;
    state -= 0x10;
    mouseSetCursorPosition(position->f[0], position->f[1]);
    (*(Vec4 **)(state + 4))->f[0] = position->f[0];
    (*(Vec4 **)(state + 4))->f[1] = position->f[1];
}
