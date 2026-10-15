typedef struct {
    char pad0[0x1D0];
    int width[2];
    int height[2];
} ScissorCntrl;

void set_scissor_screen_size(ScissorCntrl *s, int index, int width, int height)
{
    s->width[index] = width;
    s->height[index] = height;
}
