typedef struct {
    float cur;
    float prev;
    float target;
} Grip;

extern char gcGlobalVar[];
extern Grip D_0017B008;
extern int D_0017AFF4;
extern float D_0017AFF8;
extern void func_000BC988(int);

void setgrip(float g)
{
    if (g != D_0017B008.cur) {
        if (g < D_0017B008.cur) {
            if (D_0017AFF4 == 0)
                D_0017AFF8 = *(float *)(gcGlobalVar + 0x178);
            D_0017AFF4 = 1;
        } else {
            D_0017AFF4 = 0;
        }
        D_0017B008.prev = D_0017B008.target;
        D_0017B008.cur = g;
        D_0017B008.target = g;
        func_000BC988(0);
    } else {
        D_0017B008.prev = D_0017B008.target;
        D_0017AFF4 = 0;
    }
}
