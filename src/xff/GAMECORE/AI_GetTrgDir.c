/* The empty noreorder block stops the assembler from moving the final sqc2
   into the return delay slot, as in the original. */
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x20];
    s128 dir;
    char pad30[0x10];
    float scale;
    float time;
    float height;
} TrgWork;

void AI_GetTrgDir(float *out, TrgWork *w, float t)
{
    if (w->time != 0.0f) {
        out[0] = ((float *)&w->dir)[0] * w->scale;
        out[1] = -(w->height + t * w->height / w->time);
        out[2] = ((float *)&w->dir)[2] * w->scale;
        out[3] = 0.0f;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             ".set noreorder\n"
                             ".set reorder\n"
                             : : "r"(out) : "memory");
    } else {
        *(s128 *)out = w->dir;
    }
}
