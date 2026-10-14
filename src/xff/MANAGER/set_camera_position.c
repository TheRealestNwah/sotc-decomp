typedef int s128 __attribute__((mode(TI)));

void set_camera_position(char *dst, char *src)
{
    *(s128 *)(dst + 0x1E0) = *(s128 *)(src + 0x0);
}
