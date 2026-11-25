extern float RO_00042F60[];

void iosGetSinCosf(float *, float);

void iosGetAlignSinCosf(float *out, float a)
{
    float t[4] __attribute__((aligned(16)));
    iosGetSinCosf(t, a);
    out[0] = t[1];
    out[1] = t[0];
}

void iosGetSinCosf(float *out, float x)
{
    __asm__ __volatile__(".set noreorder\n"
                         "mtc1 $0, $f0\n"
                         "li.s $f3, 1.57079632679490\n"
                         "c.lt.s %0, $f0\n"
                         "bc1f 3f\n"
                         "nop\n"
                         "li.s $f1, -3.14159265358979\n"
                         "c.le.s $f1, %0\n"
                         "bc1t 1f\n"
                         "nop\n"
                         "sub.s $f1, $f0, $f1\n"
                         "li.s $f2, 6.28318530717959\n"
                         "sub.s $f4, $f1, %0\n"
                         "div.s $f4, $f4, $f2\n"
                         "cvt.w.s $f4, $f4\n"
                         "cvt.s.w $f4, $f4\n"
                         "mul.s $f4, $f4, $f2\n"
                         "add.s %0, %0, $f4\n"
                         "c.lt.s %0, $f0\n"
                         "bc1f 4f\n"
                         "nop\n"
                         "1:\n"
                         "add.s $f5, $f3, %0\n"
                         "addiu $7, $0, 1
"
                         "j 5f\n"
                         "nop\n"
                         "3:\n"
                         "li.s $f1, 3.14159265358979\n"
                         "c.lt.s %0, $f1\n"
                         "bc1t 4f\n"
                         "nop\n"
                         "li.s $f2, 6.28318530717959\n"
                         "add.s $f4, $f1, %0\n"
                         "div.s $f4, $f4, $f2\n"
                         "cvt.w.s $f4, $f4\n"
                         "cvt.s.w $f4, $f4\n"
                         "mul.s $f4, $f4, $f2\n"
                         "sub.s %0, %0, $f4\n"
                         "c.lt.s %0, $f0\n"
                         "bc1t 1b\n"
                         "nop\n"
                         "4:\n"
                         "sub.s $f5, $f3, %0\n"
                         "daddu $7, $0, $0
"
                         "5:\n"
                         "mfc1 $8, $f5\n"
                         "qmtc2.ni $8, vf16\n"
                         "lqc2 vf15, 0(%1)\n"
                         "vmr32.w vf16, vf16\n"
                         "vaddx.x vf18, vf0, vf16x\n"
                         "vmul.x vf16, vf16, vf16\n"
                         "vmulx.yzw vf18, vf18, vf0x\n"
                         "vmulw.xyzw vf19, vf15, vf16w\n"
                         "vmulx.xyzw vf19, vf19, vf16x\n"
                         "vmulx.xyz vf19, vf19, vf16x\n"
                         "vaddw.x vf18, vf18, vf19w\n"
                         "vmulx.xy vf19, vf19, vf16x\n"
                         "vaddz.x vf18, vf18, vf19z\n"
                         "vmulx.x vf19, vf19, vf16x\n"
                         "vaddy.x vf18, vf18, vf19y\n"
                         "vaddx.x vf18, vf18, vf19x\n"
                         "vaddx.xy vf18, vf0, vf18x
"
                         "vmul.x vf17, vf18, vf18
"
                         "vsubx.w vf17, vf0, vf17x
"
                         "vsqrt Q, vf17w
"
                         "bnez $7, 6f
"
                         "nop
"
                         "vwaitq
"
                         "vaddq.y vf18, vf0, Q
"
                         "b 7f
"
                         "nop
"
                         "6:
"
                         "vwaitq
"
                         "vsubq.y vf18, vf0, Q
"
                         "7:
"
                         "sqc2 vf18, 0(%2)
"
                         ".set reorder\n"
                         : "+f"(x) : "r"(RO_00042F60), "r"(out) : "$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$7", "$8", "memory");
}

float iosGetSinf(float x)
{
    __asm__ __volatile__(".set noreorder\n"
                         "mtc1 $0, $f0\n"
                         "c.lt.s %0, $f0\n"
                         "bc1f 3f\n"
                         "nop\n"
                         "li.s $f1, -3.14159265358979\n"
                         "c.le.s $f1, %0\n"
                         "bc1t 1f\n"
                         "nop\n"
                         "sub.s $f1, $f0, $f1\n"
                         "li.s $f2, 6.28318530717959\n"
                         "sub.s $f4, $f1, %0\n"
                         "div.s $f4, $f4, $f2\n"
                         "cvt.w.s $f4, $f4\n"
                         "cvt.s.w $f4, $f4\n"
                         "mul.s $f4, $f4, $f2\n"
                         "add.s %0, %0, $f4\n"
                         "c.lt.s %0, $f0\n"
                         "bc1f 4f\n"
                         "nop\n"
                         "1:\n"
                         "add.s $f3, $f0, %0\n"
                         "addiu $7, $0, 1\n"
                         "j 5f\n"
                         "nop\n"
                         "3:\n"
                         "li.s $f1, 3.14159265358979\n"
                         "c.lt.s %0, $f1\n"
                         "bc1t 4f\n"
                         "nop\n"
                         "li.s $f2, 6.28318530717959\n"
                         "add.s $f4, $f1, %0\n"
                         "div.s $f4, $f4, $f2\n"
                         "cvt.w.s $f4, $f4\n"
                         "cvt.s.w $f4, $f4\n"
                         "mul.s $f4, $f4, $f2\n"
                         "sub.s %0, %0, $f4\n"
                         "c.lt.s %0, $f0\n"
                         "bc1t 1b\n"
                         "nop\n"
                         "4:\n"
                         "sub.s $f3, $f0, %0\n"
                         "daddu $7, $0, $0\n"
                         "5:\n"
                         "mfc1 $8, $f3\n"
                         "qmtc2.ni $8, vf16\n"
                         "lqc2 vf15, 0(%1)\n"
                         "vmr32.w vf16, vf16\n"
                         "vaddx.x vf18, vf0, vf16x\n"
                         "vmul.x vf16, vf16, vf16\n"
                         "vmulx.yzw vf18, vf18, vf0x\n"
                         "vmulw.xyzw vf19, vf15, vf16w\n"
                         "vmulx.xyzw vf19, vf19, vf16x\n"
                         "vmulx.xyz vf19, vf19, vf16x\n"
                         "vaddw.x vf18, vf18, vf19w\n"
                         "vmulx.xy vf19, vf19, vf16x\n"
                         "vaddz.x vf18, vf18, vf19z\n"
                         "vmulx.x vf19, vf19, vf16x\n"
                         "vaddy.x vf18, vf18, vf19y\n"
                         "vaddx.x vf18, vf18, vf19x\n"
                         "bnez $7, 6f\n"
                         "nop\n"
                         "vsubx.xyzw vf18, vf0, vf18x\n"
                         "6:\n"
                         "qmfc2.ni $8, vf18\n"
                         "mtc1 $8, %0\n"
                         ".set reorder\n"
                         : "+f"(x) : "r"(RO_00042F60) : "$f0", "$f1", "$f2", "$f3", "$f4", "$7", "$8");
    return x;
}

float iosGetCosf(float x)
{
    __asm__ __volatile__(".set noreorder\n"
                         "mtc1 $0, $f0\n"
                         "li.s $f3, 1.57079632679490\n"
                         "c.lt.s %0, $f0\n"
                         "bc1f 3f\n"
                         "nop\n"
                         "li.s $f1, -3.14159265358979\n"
                         "c.le.s $f1, %0\n"
                         "bc1t 1f\n"
                         "nop\n"
                         "sub.s $f1, $f0, $f1\n"
                         "li.s $f2, 6.28318530717959\n"
                         "sub.s $f4, $f1, %0\n"
                         "div.s $f4, $f4, $f2\n"
                         "cvt.w.s $f4, $f4\n"
                         "cvt.s.w $f4, $f4\n"
                         "mul.s $f4, $f4, $f2\n"
                         "add.s %0, %0, $f4\n"
                         "c.lt.s %0, $f0\n"
                         "bc1f 4f\n"
                         "nop\n"
                         "1:\n"
                         "add.s $f5, $f3, %0\n"
                         "j 5f\n"
                         "nop\n"
                         "3:\n"
                         "li.s $f1, 3.14159265358979\n"
                         "c.lt.s %0, $f1\n"
                         "bc1t 4f\n"
                         "nop\n"
                         "li.s $f2, 6.28318530717959\n"
                         "add.s $f4, $f1, %0\n"
                         "div.s $f4, $f4, $f2\n"
                         "cvt.w.s $f4, $f4\n"
                         "cvt.s.w $f4, $f4\n"
                         "mul.s $f4, $f4, $f2\n"
                         "sub.s %0, %0, $f4\n"
                         "c.lt.s %0, $f0\n"
                         "bc1t 1b\n"
                         "nop\n"
                         "4:\n"
                         "sub.s $f5, $f3, %0\n"
                         "5:\n"
                         "mfc1 $8, $f5\n"
                         "qmtc2.ni $8, vf16\n"
                         "lqc2 vf15, 0(%1)\n"
                         "vmr32.w vf16, vf16\n"
                         "vaddx.x vf18, vf0, vf16x\n"
                         "vmul.x vf16, vf16, vf16\n"
                         "vmulx.yzw vf18, vf18, vf0x\n"
                         "vmulw.xyzw vf19, vf15, vf16w\n"
                         "vmulx.xyzw vf19, vf19, vf16x\n"
                         "vmulx.xyz vf19, vf19, vf16x\n"
                         "vaddw.x vf18, vf18, vf19w\n"
                         "vmulx.xy vf19, vf19, vf16x\n"
                         "vaddz.x vf18, vf18, vf19z\n"
                         "vmulx.x vf19, vf19, vf16x\n"
                         "vaddy.x vf18, vf18, vf19y\n"
                         "vaddx.x vf18, vf18, vf19x\n"
                         "qmfc2.ni $7, vf18\n"
                         "mtc1 $7, %0\n"
                         ".set reorder\n"
                         : "+f"(x) : "r"(RO_00042F60) : "$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$7", "$8");
    return x;
}

float iosGetTanf(float angle)
{
    float sc[4] __attribute__((aligned(16)));

    iosGetSinCosf(sc, angle);
    return sc[1] / sc[0];
}

void iosGetSinCos(float *output, int angle)
{
    iosGetSinCosf(output, (float) angle * 0.000000000465660988935301389801679761148989200592041015625f * 3.141592562198638916015625f);
}

float iosGetSin(int arg0)
{
    return iosGetSinf((float) arg0 * 0.000000000465660988935301389801679761148989200592041015625f * 3.141592562198638916015625f);
}

float iosGetCos(int arg0)
{
    return iosGetCosf((float) arg0 * 0.000000000465660988935301389801679761148989200592041015625f * 3.141592562198638916015625f);
}

float iosGetTan(int a)
{
    float sc[4] __attribute__((aligned(16)));

    iosGetSinCos(sc, a);
    return sc[1] / sc[0];
}
