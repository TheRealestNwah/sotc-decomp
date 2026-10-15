typedef struct {
    char pad[0xC];
    long *p;
    char pad2[0xC];
    int busy;
} GsCtx;

extern GsCtx *D_00040BF4;

/* Appends a GS register write in A+D form (data, then register address). */
void gsReg(long reg, long data)
{
    if (D_00040BF4->busy == 0) {
        *D_00040BF4->p++ = data;
        *D_00040BF4->p++ = reg;
    }
}
