#ifdef NONMATCHING
/* Parked: 40 words differ. Stereo looping mixer; loop/flow and frame match, but
   gcc schedules the wrap tests (slt/movz, andi/movn) and the div/mflo pairs
   in a different order. */
typedef struct { short *src; float *out; int pad[2]; int idx; } PcmCvt;
static void func_0002E068(PcmCvt *p, int n, int gl, int gr, int start, int end)
{
    float *ol = p->out;
    short *src = p->src;
    float *or = ol + 256;
    int idx = p->idx;
    int j; int k;
    for (j = 0; j < n; j += 0x200) {
        for (k = 0; k < 256; k++) {
            int a = src[idx], b = src[idx + 0x100]; int l = a * gl; int r = b * gr; idx++; if (idx + 0x100 >= end) idx = start; if (idx & 0x100) idx += 0x100; *ol = l / 100; ol++; *or = r / 100; or++;
        }
        ol += 256; or += 256;
    }
    p->idx = idx;
}
#endif
