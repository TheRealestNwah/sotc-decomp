typedef struct {
    long a, b, c, d;
} Quad;

void SetInertiaRotInterpMode(void *o)
{
    char *obj = o;
    char *cls;

    switch ((unsigned char)obj[8]) {
    case 9:
        cls = obj + 0x90;
        break;
    case 0x16:
        cls = obj + 0x90;
        break;
    default:
        cls = 0;
    }

    if (*(signed char *)(cls + 0xA26) != 0) {
        cls[0xA29] = 1;
        *(Quad *)(cls + 0xA50) = *(Quad *)(cls + 0xA30);
    }
}
