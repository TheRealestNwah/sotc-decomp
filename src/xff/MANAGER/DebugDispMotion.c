/* ~130 diffs, 2 words short (161 vs 163). Debug motion overlay: sets up GL state (enable 3/7/8, GL_LINES, blend 5/6), then draws the motion tree in two passes using callbacks func_0003DA98 and (when the drawn count differs from o[4]) func_0003DB20: each pass pushes the matrix, calls the callback on the root node (node+0x38 != -1), sets the matrix, recurses with func_0003DB80 on child +0x30 (or calls the callback in leaf mode) and sibling +0x34, and counts successes in a stack counter. Original keeps scale in $f20 and the node scale in $f21, p2 in $s1, o in $s2, mat in $s4, callback in $s5 (copy in $s7 / $fp); ours swaps the two floats and the saved-register order (declaration order, register pins and float pins all tried: best 123 with int pins, 134 with float pins). */
typedef int (*MotionCb)(void *, int, float, float);

extern int func_0003DA98(void *, int, float, float);
extern int func_0003DB20(void *, int, float, float);
extern void func_0003DB80(int, void *, void *, MotionCb, void *, int *, float, float);
extern void iosUnitCurrentMatrix(void);
extern void iosPushCurrentMatrix(void);
extern void iosSetCurrentMatrix(void *);
extern void iosPopCurrentMatrix(void);
extern void glEnable(int);
extern void glDisable(int);
extern void glBegin(int);
extern void glEnd(void);
extern void glBlendFunc(int, int);

#ifdef NONMATCHING
void DebugDispMotion(char *o, void *mat, void *p2, float *f, float scale)
{
    int count = 0;
    char *node;
    MotionCb cb;
    int a;
    int b;
    float fs;

    iosUnitCurrentMatrix();
    glEnable(3);
    glEnable(7);
    glEnable(8);
    glBegin(1);
    glBlendFunc(5, 6);
    cb = func_0003DA98;
    node = *(char **)(o + 8);
    fs = f[2];
    iosPushCurrentMatrix();
    b = *(int *)(node + 0x34);
    a = *(int *)(node + 0x30);
    if (*(int *)(node + 0x38) == -1 || cb(p2, 0, scale, *(float *)(node + 0x18) * fs) != 0)
        count++;
    iosSetCurrentMatrix(mat);
    if (a != -1)
        func_0003DB80(a, o, mat, cb, p2, &count, scale, fs);
    else
        cb(p2, 1, scale, *(float *)(node + 0x18) * fs);
    iosPopCurrentMatrix();
    if (b != -1)
        func_0003DB80(b, o, mat, cb, p2, &count, scale, fs);
    glEnd();
    if (count != *(int *)(o + 4)) {
        cb = func_0003DB20;
        node = *(char **)(o + 8);
        fs = f[2];
        iosPushCurrentMatrix();
        b = *(int *)(node + 0x34);
        a = *(int *)(node + 0x30);
        if (*(int *)(node + 0x38) == -1 || cb(p2, 0, scale, *(float *)(node + 0x18) * fs) != 0)
            count++;
        iosSetCurrentMatrix(mat);
        if (a != -1)
            func_0003DB80(a, o, mat, cb, p2, &count, scale, fs);
        else
            cb(p2, 1, scale, *(float *)(node + 0x18) * fs);
        iosPopCurrentMatrix();
        if (b != -1)
            func_0003DB80(b, o, mat, cb, p2, &count, scale, fs);
    }
    glDisable(8);
}
#endif
