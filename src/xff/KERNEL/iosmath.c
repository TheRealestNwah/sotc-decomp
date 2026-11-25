typedef int s128 __attribute__((mode(TI)));

extern void iosGetSinCosf(float *, float);
extern s128 B_000543F0[];
extern void iosDI(void);
extern void iosEI(void);
extern s128 B_000545F0[];
extern int B_000547F0;
extern int iosCreateSema(int, int, int);
extern s128 D_00040930[2];
extern void iosInitPushPosVuSema(void);
extern void InitQuaternionDrive(void);
extern void InitTableSinCos(void);

void InitMath(void)
{
    volatile unsigned int *mask;
    volatile unsigned int *mode;
    volatile unsigned int *reset;
    volatile s128 *fifo;
    iosInitPushPosVuSema();
    mask = (volatile unsigned int *)0x10003830;
    mode = (volatile unsigned int *)0x10003820;
    reset = (volatile unsigned int *)0x10003810;
    *mask = 0;
    *mode = 0;
    *reset = 1;
    __asm__ __volatile__("cfc2 $8, $28\n" "ori $8, $8, 2\n" "ctc2 $8, $28\n" "sync.p\n"
        : : : "$8", "memory");
    fifo = (volatile s128 *)0x10004000;
    *fifo = D_00040930[0];
    *fifo = D_00040930[1];
    InitQuaternionDrive();
    InitTableSinCos();
}

static void func_0000B438(int n, float out[][4], float in[][4])
{
    int i, j, k, r;
    float a[n][n + 1];
    float b[n][n + 1];
    float c[n][n + 1];
    float d[n][n + 1];
    float v[n];
    float e[n][n + 1];
    float f[n][n + 1];
    float g[n][n + 1];
    float h[n][n + 1];
    float w[n];
    float m[n][n + 1];

    for (r = 0; r < n; r++) {
        for (j = 0; j < n; j++) {
            if (r == j) {
                out[r][j] = 1.0f;
            } else {
                out[r][j] = 0.0f;
            }
        }
    }

    for (k = 0; k < n; k++) {
        for (r = 0; r < n; r++) {
            a[r][n] = out[r][k];
        }
        for (r = 0; r < n; r++) {
            for (j = 0; j < n; j++) {
                a[r][j] = in[r][j];
            }
        }
        for (i = 0; i < n - 1; i++) {
            for (j = i; j <= n; j++) {
                b[i][j] = a[i][j] / a[i][i];
            }
            for (j = i; j <= n; j++) {
                a[i][j] = b[i][j];
            }
            for (r = i + 1; r < n; r++) {
                for (j = i; j <= n; j++) {
                    c[r][j] = a[r][i] * b[i][j];
                }
            }
            for (r = i + 1; r < n; r++) {
                for (j = i; j <= n; j++) {
                    a[r][j] = a[r][j] - c[r][j];
                }
            }
        }
        for (r = 0; r < n; r++) {
            for (j = 0; j <= n; j++) {
                d[r][j] = a[r][j];
            }
        }
        for (r = 0; r < n; r++) {
            v[r] = d[r][n];
            for (j = n; j > 0; j--) {
                e[r][j] = d[r][j - 1];
            }
            e[r][0] = v[r];
        }
        for (i = n - 1; i > 0; i--) {
            for (j = i + 1; j >= 0; j--) {
                f[i][j] = e[i][j] / e[i][i + 1];
            }
            for (j = i + 1; j >= 0; j--) {
                e[i][j] = f[i][j];
            }
            for (r = i - 1; r >= 0; r--) {
                for (j = i + 1; j >= 0; j--) {
                    g[r][j] = e[r][i + 1] * f[i][j];
                }
            }
            for (r = i - 1; r >= 0; r--) {
                for (j = i + 1; j >= 0; j--) {
                    e[r][j] = e[r][j] - g[r][j];
                }
            }
        }
        for (r = 0; r < n; r++) {
            for (j = 0; j <= n; j++) {
                h[r][j] = e[r][j];
            }
        }
        for (r = 0; r < n; r++) {
            w[r] = h[r][0];
            for (j = 0; j < n; j++) {
                m[r][j] = h[r][j + 1];
            }
            m[r][n] = w[r];
        }
        for (r = 0; r < n; r++) {
            out[r][k] = m[r][n];
        }
    }
}

/* Nonzero when the two 16-byte strings differ. */
int CompareString16(s128 *a, s128 *b)
{
    long t[2] __attribute__((aligned(16)));

    __asm__ __volatile__("lq $8, 0x0(%1)\n"
                         "lq $9, 0x0(%2)\n"
                         "pxor $10, $8, $9\n"
                         "sq $10, 0x0(%0)\n"
                         : : "r"(t), "r"(a), "r"(b) : "$8", "$9", "$10", "memory");
    return t[0] | t[1];
}

void iosInitCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vmove.xyzw vf4, vf0\n"
        "vmr32.xyzw vf3, vf4\n"
        "vmr32.xyzw vf2, vf3\n"
        "vmr32.xyzw vf1, vf2\n"
        "viaddi vi15, vi0, 0x0\n"
        ".set reorder\n"
        : : : "memory");
}

void iosUnitCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vmove.xyzw vf4, vf0\n"
        "vmr32.xyzw vf3, vf4\n"
        "vmr32.xyzw vf2, vf3\n"
        "vmr32.xyzw vf1, vf2\n"
        ".set reorder\n"
        : : : "memory");
}

void iosPushCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vsqi.xyzw vf1, (vi15++)\n"
        "vsqi.xyzw vf2, (vi15++)\n"
        "vsqi.xyzw vf3, (vi15++)\n"
        "vsqi.xyzw vf4, (vi15++)\n"
        ".set reorder\n"
        : : : "memory");
}

void iosPopCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vlqd.xyzw vf4, (--vi15)\n"
        "vlqd.xyzw vf3, (--vi15)\n"
        "vlqd.xyzw vf2, (--vi15)\n"
        "vlqd.xyzw vf1, (--vi15)\n"
        ".set reorder\n"
        : : : "memory");
}

void iosPushVu0RegistersToWork(char *a0)
{
    __asm__ __volatile__(".set noreorder\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         "sqc2 vf6, 0x10(%0)\n"
                         "sqc2 vf7, 0x20(%0)\n"
                         "sqc2 vf1, 0x30(%0)\n"
                         "sqc2 vf2, 0x40(%0)\n"
                         "sqc2 vf3, 0x50(%0)\n"
                         "sqc2 vf4, 0x60(%0)\n"
                         "sqc2 vf8, 0x70(%0)\n"
                         "sqc2 vf9, 0x80(%0)\n"
                         "sqc2 vf10, 0x90(%0)\n"
                         "sqc2 vf11, 0xA0(%0)\n"
                         "sqc2 vf12, 0xB0(%0)\n"
                         "sqc2 vf13, 0xC0(%0)\n"
                         "sqc2 vf14, 0xD0(%0)\n"
                         "sqc2 vf15, 0xE0(%0)\n"
                         "sqc2 vf16, 0xF0(%0)\n"
                         "sqc2 vf17, 0x100(%0)\n"
                         "sqc2 vf18, 0x110(%0)\n"
                         "sqc2 vf19, 0x120(%0)\n"
                         "sqc2 vf20, 0x130(%0)\n"
                         "sqc2 vf21, 0x140(%0)\n"
                         "sqc2 vf22, 0x150(%0)\n"
                         "sqc2 vf23, 0x160(%0)\n"
                         "sqc2 vf24, 0x170(%0)\n"
                         "sqc2 vf25, 0x180(%0)\n"
                         "sqc2 vf26, 0x190(%0)\n"
                         "sqc2 vf27, 0x1A0(%0)\n"
                         "sqc2 vf28, 0x1B0(%0)\n"
                         "sqc2 vf29, 0x1C0(%0)\n"
                         "sqc2 vf30, 0x1D0(%0)\n"
                         "sqc2 vf31, 0x1E0(%0)\n"
                         "sqc2 vf1, 0x0(%1)\n"
                         "sqc2 vf2, 0x10(%1)\n"
                         "sqc2 vf3, 0x20(%1)\n"
                         "sqc2 vf4, 0x30(%1)\n"
                         "sqc2 vf5, 0x40(%1)\n"
                         "sqc2 vf6, 0x50(%1)\n"
                         "sqc2 vf7, 0x60(%1)\n"
                         "sqc2 vf8, 0x70(%1)\n"
                         "sqc2 vf9, 0x80(%1)\n"
                         "sqc2 vf10, 0x90(%1)\n"
                         "sqc2 vf11, 0xA0(%1)\n"
                         "sqc2 vf12, 0xB0(%1)\n"
                         "sqc2 vf13, 0xC0(%1)\n"
                         "sqc2 vf14, 0xD0(%1)\n"
                         "sqc2 vf15, 0xE0(%1)\n"
                         "sqc2 vf16, 0xF0(%1)\n"
                         "sqc2 vf17, 0x100(%1)\n"
                         "sqc2 vf18, 0x110(%1)\n"
                         "sqc2 vf19, 0x120(%1)\n"
                         "sqc2 vf20, 0x130(%1)\n"
                         "sqc2 vf21, 0x140(%1)\n"
                         "sqc2 vf22, 0x150(%1)\n"
                         "sqc2 vf23, 0x160(%1)\n"
                         "sqc2 vf24, 0x170(%1)\n"
                         "sqc2 vf25, 0x180(%1)\n"
                         "sqc2 vf26, 0x190(%1)\n"
                         "sqc2 vf27, 0x1A0(%1)\n"
                         "sqc2 vf28, 0x1B0(%1)\n"
                         "sqc2 vf29, 0x1C0(%1)\n"
                         "sqc2 vf30, 0x1D0(%1)\n"
                         "sqc2 vf31, 0x1E0(%1)\n"
                         ".set reorder\n"
                         : : "r"(a0 + 0x200), "r"(a0) : "memory");
}

void iosPopVu0RegistersFromWork(char *a0)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x10(%0)\n"
                         "lqc2 vf7, 0x20(%0)\n"
                         "lqc2 vf1, 0x30(%0)\n"
                         "lqc2 vf2, 0x40(%0)\n"
                         "lqc2 vf3, 0x50(%0)\n"
                         "lqc2 vf4, 0x60(%0)\n"
                         "lqc2 vf8, 0x70(%0)\n"
                         "lqc2 vf9, 0x80(%0)\n"
                         "lqc2 vf10, 0x90(%0)\n"
                         "lqc2 vf11, 0xA0(%0)\n"
                         "lqc2 vf12, 0xB0(%0)\n"
                         "lqc2 vf13, 0xC0(%0)\n"
                         "lqc2 vf14, 0xD0(%0)\n"
                         "lqc2 vf15, 0xE0(%0)\n"
                         "lqc2 vf16, 0xF0(%0)\n"
                         "lqc2 vf17, 0x100(%0)\n"
                         "lqc2 vf18, 0x110(%0)\n"
                         "lqc2 vf19, 0x120(%0)\n"
                         "lqc2 vf20, 0x130(%0)\n"
                         "lqc2 vf21, 0x140(%0)\n"
                         "lqc2 vf22, 0x150(%0)\n"
                         "lqc2 vf23, 0x160(%0)\n"
                         "lqc2 vf24, 0x170(%0)\n"
                         "lqc2 vf25, 0x180(%0)\n"
                         "lqc2 vf26, 0x190(%0)\n"
                         "lqc2 vf27, 0x1A0(%0)\n"
                         "lqc2 vf28, 0x1B0(%0)\n"
                         "lqc2 vf29, 0x1C0(%0)\n"
                         "lqc2 vf30, 0x1D0(%0)\n"
                         "lqc2 vf31, 0x1E0(%0)\n"
                         "lqc2 vf1, 0x0(%1)\n"
                         "lqc2 vf2, 0x10(%1)\n"
                         "lqc2 vf3, 0x20(%1)\n"
                         "lqc2 vf4, 0x30(%1)\n"
                         "lqc2 vf5, 0x40(%1)\n"
                         "lqc2 vf6, 0x50(%1)\n"
                         "lqc2 vf7, 0x60(%1)\n"
                         "lqc2 vf8, 0x70(%1)\n"
                         "lqc2 vf9, 0x80(%1)\n"
                         "lqc2 vf10, 0x90(%1)\n"
                         "lqc2 vf11, 0xA0(%1)\n"
                         "lqc2 vf12, 0xB0(%1)\n"
                         "lqc2 vf13, 0xC0(%1)\n"
                         "lqc2 vf14, 0xD0(%1)\n"
                         "lqc2 vf15, 0xE0(%1)\n"
                         "lqc2 vf16, 0xF0(%1)\n"
                         "lqc2 vf17, 0x100(%1)\n"
                         "lqc2 vf18, 0x110(%1)\n"
                         "lqc2 vf19, 0x120(%1)\n"
                         "lqc2 vf20, 0x130(%1)\n"
                         "lqc2 vf21, 0x140(%1)\n"
                         "lqc2 vf22, 0x150(%1)\n"
                         "lqc2 vf23, 0x160(%1)\n"
                         "lqc2 vf24, 0x170(%1)\n"
                         "lqc2 vf25, 0x180(%1)\n"
                         "lqc2 vf26, 0x190(%1)\n"
                         "lqc2 vf27, 0x1A0(%1)\n"
                         "lqc2 vf28, 0x1B0(%1)\n"
                         "lqc2 vf29, 0x1C0(%1)\n"
                         "lqc2 vf30, 0x1D0(%1)\n"
                         "lqc2 vf31, 0x1E0(%1)\n"
                         ".set reorder\n"
                         : : "r"(a0 + 0x200), "r"(a0) : "memory");
}

void iosTransCurrentMatrix(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf8, 0x0(%0)\n"
        "vmulax.xyzw ACC, vf1, vf8x\n"
        "vmadday.xyzw ACC, vf2, vf8y\n"
        "vmaddaz.xyzw ACC, vf3, vf8z\n"
        "vmaddw.xyzw vf4, vf4, vf0w\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}

void iosSetTransCurrentMatrix(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf8, 0x0(%0)\n"
        "vmove.xyzw vf4, vf8\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}

void iosClearTransCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vmove.xyzw vf4, vf0\n"
        ".set reorder\n"
        : : : "memory");
}

void iosGetRotXVector(void *destination, void *source, float angle)
{
    float matrix[16] __attribute__((aligned(16)));
    float sc[2];

    iosGetSinCosf(sc, angle);
    __asm__ __volatile__(".set noreorder\n"
                         "vmove.xyzw vf17, vf0\n"
                         "vmr32.xyzw vf16, vf17\n"
                         "vmr32.xyzw vf15, vf16\n"
                         "vmr32.xyzw vf14, vf15\n"
                         ".set reorder\n");
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "mfc1 $9, %1\n"
                         "qmtc2.ni $8, vf5\n"
                         "qmtc2.ni $9, vf6\n"
                         "vaddx.y vf15, vf0, vf5x\n"
                         "vsubx.y vf16, vf0, vf6x\n"
                         "vaddx.z vf15, vf0, vf6x\n"
                         "vaddx.z vf16, vf0, vf5x\n"
                         "sqc2 vf14, 0(%2)\n"
                         "sqc2 vf15, 16(%2)\n"
                         "sqc2 vf16, 32(%2)\n"
                         "sqc2 vf17, 48(%2)\n"
                         ".set reorder\n"
                         : : "f"(sc[0]), "f"(sc[1]), "r"(matrix)
                         : "$8", "$9", "memory");
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%1)\n"
                         "lqc2 vf15, 16(%1)\n"
                         "lqc2 vf16, 32(%1)\n"
                         "lqc2 vf17, 48(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(destination), "r"(matrix), "r"(source)
                         : "memory");
}

void iosGetRotYVector(void *destination, void *source, float angle)
{
    float matrix[16] __attribute__((aligned(16)));
    float sc[2];

    iosGetSinCosf(sc, angle);
    __asm__ __volatile__(".set noreorder\n"
                         "vmove.xyzw vf17, vf0\n"
                         "vmr32.xyzw vf16, vf17\n"
                         "vmr32.xyzw vf15, vf16\n"
                         "vmr32.xyzw vf14, vf15\n"
                         ".set reorder\n");
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "mfc1 $9, %1\n"
                         "qmtc2.ni $8, vf5\n"
                         "qmtc2.ni $9, vf6\n"
                         "vaddx.x vf14, vf0, vf5x\n"
                         "vaddx.x vf16, vf0, vf6x\n"
                         "vsubx.z vf14, vf0, vf6x\n"
                         "vaddx.z vf16, vf0, vf5x\n"
                         "sqc2 vf14, 0(%2)\n"
                         "sqc2 vf15, 16(%2)\n"
                         "sqc2 vf16, 32(%2)\n"
                         "sqc2 vf17, 48(%2)\n"
                         ".set reorder\n"
                         : : "f"(sc[0]), "f"(sc[1]), "r"(matrix)
                         : "$8", "$9", "memory");
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%1)\n"
                         "lqc2 vf15, 16(%1)\n"
                         "lqc2 vf16, 32(%1)\n"
                         "lqc2 vf17, 48(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(destination), "r"(matrix), "r"(source)
                         : "memory");
}

void iosRotCurrentMatrixX(float angle)
{
    float sc[2];

    iosGetSinCosf(sc, angle);
    __asm__ __volatile__(".set noreorder\n"
                         "vmove.xyzw vf17, vf0\n"
                         "vmr32.xyzw vf16, vf17\n"
                         "vmr32.xyzw vf15, vf16\n"
                         "vmr32.xyzw vf14, vf15\n"
                         ".set reorder\n");
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "mfc1 $9, %1\n"
                         "qmtc2.ni $8, vf5\n"
                         "qmtc2.ni $9, vf6\n"
                         "vaddx.y vf15, vf0, vf5x\n"
                         "vsubx.y vf16, vf0, vf6x\n"
                         "vaddx.z vf15, vf0, vf6x\n"
                         "vaddx.z vf16, vf0, vf5x\n"
                         "vmulax.xyzw ACC, vf1, vf14x\n"
                         "vmadday.xyzw ACC, vf2, vf14y\n"
                         "vmaddaz.xyzw ACC, vf3, vf14z\n"
                         "vmaddw.xyzw vf14, vf4, vf14w\n"
                         "vmulax.xyzw ACC, vf1, vf15x\n"
                         "vmadday.xyzw ACC, vf2, vf15y\n"
                         "vmaddaz.xyzw ACC, vf3, vf15z\n"
                         "vmaddw.xyzw vf15, vf4, vf15w\n"
                         "vmulax.xyzw ACC, vf1, vf16x\n"
                         "vmadday.xyzw ACC, vf2, vf16y\n"
                         "vmaddaz.xyzw ACC, vf3, vf16z\n"
                         "vmaddw.xyzw vf16, vf4, vf16w\n"
                         "vmulax.xyzw ACC, vf1, vf17x\n"
                         "vmadday.xyzw ACC, vf2, vf17y\n"
                         "vmaddaz.xyzw ACC, vf3, vf17z\n"
                         "vmaddw.xyzw vf17, vf4, vf17w\n"
                         "vmove.xyzw vf1, vf14\n"
                         "vmove.xyzw vf2, vf15\n"
                         "vmove.xyzw vf3, vf16\n"
                         "vmove.xyzw vf4, vf17\n"
                         ".set reorder\n"
                         : : "f"(sc[0]), "f"(sc[1]) : "$8", "$9");
}

void iosRotCurrentMatrixY(float angle)
{
    float sc[2];

    iosGetSinCosf(sc, angle);
    __asm__ __volatile__(".set noreorder\n"
                         "vmove.xyzw vf17, vf0\n"
                         "vmr32.xyzw vf16, vf17\n"
                         "vmr32.xyzw vf15, vf16\n"
                         "vmr32.xyzw vf14, vf15\n"
                         ".set reorder\n");
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "mfc1 $9, %1\n"
                         "qmtc2.ni $8, vf5\n"
                         "qmtc2.ni $9, vf6\n"
                         "vaddx.x vf14, vf0, vf5x\n"
                         "vaddx.x vf16, vf0, vf6x\n"
                         "vsubx.z vf14, vf0, vf6x\n"
                         "vaddx.z vf16, vf0, vf5x\n"
                         "vmulax.xyzw ACC, vf1, vf14x\n"
                         "vmadday.xyzw ACC, vf2, vf14y\n"
                         "vmaddaz.xyzw ACC, vf3, vf14z\n"
                         "vmaddw.xyzw vf14, vf4, vf14w\n"
                         "vmulax.xyzw ACC, vf1, vf15x\n"
                         "vmadday.xyzw ACC, vf2, vf15y\n"
                         "vmaddaz.xyzw ACC, vf3, vf15z\n"
                         "vmaddw.xyzw vf15, vf4, vf15w\n"
                         "vmulax.xyzw ACC, vf1, vf16x\n"
                         "vmadday.xyzw ACC, vf2, vf16y\n"
                         "vmaddaz.xyzw ACC, vf3, vf16z\n"
                         "vmaddw.xyzw vf16, vf4, vf16w\n"
                         "vmulax.xyzw ACC, vf1, vf17x\n"
                         "vmadday.xyzw ACC, vf2, vf17y\n"
                         "vmaddaz.xyzw ACC, vf3, vf17z\n"
                         "vmaddw.xyzw vf17, vf4, vf17w\n"
                         "vmove.xyzw vf1, vf14\n"
                         "vmove.xyzw vf2, vf15\n"
                         "vmove.xyzw vf3, vf16\n"
                         "vmove.xyzw vf4, vf17\n"
                         ".set reorder\n"
                         : : "f"(sc[0]), "f"(sc[1]) : "$8", "$9");
}

void iosRotCurrentMatrixZ(float angle)
{
    float sc[2];

    iosGetSinCosf(sc, angle);
    __asm__ __volatile__(".set noreorder\n"
                         "vmove.xyzw vf17, vf0\n"
                         "vmr32.xyzw vf16, vf17\n"
                         "vmr32.xyzw vf15, vf16\n"
                         "vmr32.xyzw vf14, vf15\n"
                         ".set reorder\n");
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "mfc1 $9, %1\n"
                         "qmtc2.ni $8, vf5\n"
                         "qmtc2.ni $9, vf6\n"
                         "vaddx.x vf14, vf0, vf5x\n"
                         "vsubx.x vf15, vf0, vf6x\n"
                         "vaddx.y vf14, vf0, vf6x\n"
                         "vaddx.y vf15, vf0, vf5x\n"
                         "vmulax.xyzw ACC, vf1, vf14x\n"
                         "vmadday.xyzw ACC, vf2, vf14y\n"
                         "vmaddaz.xyzw ACC, vf3, vf14z\n"
                         "vmaddw.xyzw vf14, vf4, vf14w\n"
                         "vmulax.xyzw ACC, vf1, vf15x\n"
                         "vmadday.xyzw ACC, vf2, vf15y\n"
                         "vmaddaz.xyzw ACC, vf3, vf15z\n"
                         "vmaddw.xyzw vf15, vf4, vf15w\n"
                         "vmulax.xyzw ACC, vf1, vf16x\n"
                         "vmadday.xyzw ACC, vf2, vf16y\n"
                         "vmaddaz.xyzw ACC, vf3, vf16z\n"
                         "vmaddw.xyzw vf16, vf4, vf16w\n"
                         "vmulax.xyzw ACC, vf1, vf17x\n"
                         "vmadday.xyzw ACC, vf2, vf17y\n"
                         "vmaddaz.xyzw ACC, vf3, vf17z\n"
                         "vmaddw.xyzw vf17, vf4, vf17w\n"
                         "vmove.xyzw vf1, vf14\n"
                         "vmove.xyzw vf2, vf15\n"
                         "vmove.xyzw vf3, vf16\n"
                         "vmove.xyzw vf4, vf17\n"
                         ".set reorder\n"
                         : : "f"(sc[0]), "f"(sc[1]) : "$8", "$9");
}

void iosScaleCurrentMatrix(float f0, float f1, float f2)
{
    __asm__ __volatile__(".set noreorder\n"
        "vmove.xyzw vf17, vf0\n"
        "vmr32.xyzw vf16, vf17\n"
        "vmr32.xyzw vf15, vf16\n"
        "vmr32.xyzw vf14, vf15\n"
        "mfc1 $6, %0\n"
        "mfc1 $7, %1\n"
        "mfc1 $8, %2\n"
        "qmtc2.ni $6, vf5\n"
        "qmtc2.ni $7, vf6\n"
        "qmtc2.ni $8, vf7\n"
        "vaddx.x vf14, vf0, vf5x\n"
        "vaddx.y vf15, vf0, vf6x\n"
        "vaddx.z vf16, vf0, vf7x\n"
        "vmulax.xyzw ACC, vf1, vf14x\n"
        "vmadday.xyzw ACC, vf2, vf14y\n"
        "vmaddaz.xyzw ACC, vf3, vf14z\n"
        "vmaddw.xyzw vf14, vf4, vf14w\n"
        "vmulax.xyzw ACC, vf1, vf15x\n"
        "vmadday.xyzw ACC, vf2, vf15y\n"
        "vmaddaz.xyzw ACC, vf3, vf15z\n"
        "vmaddw.xyzw vf15, vf4, vf15w\n"
        "vmulax.xyzw ACC, vf1, vf16x\n"
        "vmadday.xyzw ACC, vf2, vf16y\n"
        "vmaddaz.xyzw ACC, vf3, vf16z\n"
        "vmaddw.xyzw vf16, vf4, vf16w\n"
        "vmulax.xyzw ACC, vf1, vf17x\n"
        "vmadday.xyzw ACC, vf2, vf17y\n"
        "vmaddaz.xyzw ACC, vf3, vf17z\n"
        "vmaddw.xyzw vf17, vf4, vf17w\n"
        "vmove.xyzw vf1, vf14\n"
        "vmove.xyzw vf2, vf15\n"
        "vmove.xyzw vf3, vf16\n"
        "vmove.xyzw vf4, vf17\n"
        ".set reorder\n"
        : : "f"(f0), "f"(f1), "f"(f2) : "$6", "$7", "$8");
}

void iosGetCurrentMatrix(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "sqc2 vf1, 0x0(%0)\n"
        "sqc2 vf2, 0x10(%0)\n"
        "sqc2 vf3, 0x20(%0)\n"
        "sqc2 vf4, 0x30(%0)\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}

void iosGetCurrentMatrixTrans(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "sqc2 vf4, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}

void iosSetCurrentMatrix(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf1, 0x0(%0)\n"
        "lqc2 vf2, 0x10(%0)\n"
        "lqc2 vf3, 0x20(%0)\n"
        "lqc2 vf4, 0x30(%0)\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}

void iosMulCurrentMatrixR(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf14, 0x0(%0)\n"
        "lqc2 vf15, 0x10(%0)\n"
        "lqc2 vf16, 0x20(%0)\n"
        "lqc2 vf17, 0x30(%0)\n"
        "vmulax.xyzw ACC, vf1, vf14x\n"
        "vmadday.xyzw ACC, vf2, vf14y\n"
        "vmaddaz.xyzw ACC, vf3, vf14z\n"
        "vmaddw.xyzw vf14, vf4, vf14w\n"
        "vmulax.xyzw ACC, vf1, vf15x\n"
        "vmadday.xyzw ACC, vf2, vf15y\n"
        "vmaddaz.xyzw ACC, vf3, vf15z\n"
        "vmaddw.xyzw vf15, vf4, vf15w\n"
        "vmulax.xyzw ACC, vf1, vf16x\n"
        "vmadday.xyzw ACC, vf2, vf16y\n"
        "vmaddaz.xyzw ACC, vf3, vf16z\n"
        "vmaddw.xyzw vf16, vf4, vf16w\n"
        "vmulax.xyzw ACC, vf1, vf17x\n"
        "vmadday.xyzw ACC, vf2, vf17y\n"
        "vmaddaz.xyzw ACC, vf3, vf17z\n"
        "vmaddw.xyzw vf17, vf4, vf17w\n"
        "vmove.xyzw vf1, vf14\n"
        "vmove.xyzw vf2, vf15\n"
        "vmove.xyzw vf3, vf16\n"
        "vmove.xyzw vf4, vf17\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}

void iosMulCurrentMatrixL(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf14, 0x0(%0)\n"
        "lqc2 vf15, 0x10(%0)\n"
        "lqc2 vf16, 0x20(%0)\n"
        "lqc2 vf17, 0x30(%0)\n"
        "vmulax.xyzw ACC, vf14, vf1x\n"
        "vmadday.xyzw ACC, vf15, vf1y\n"
        "vmaddaz.xyzw ACC, vf16, vf1z\n"
        "vmaddw.xyzw vf1, vf17, vf1w\n"
        "vmulax.xyzw ACC, vf14, vf2x\n"
        "vmadday.xyzw ACC, vf15, vf2y\n"
        "vmaddaz.xyzw ACC, vf16, vf2z\n"
        "vmaddw.xyzw vf2, vf17, vf2w\n"
        "vmulax.xyzw ACC, vf14, vf3x\n"
        "vmadday.xyzw ACC, vf15, vf3y\n"
        "vmaddaz.xyzw ACC, vf16, vf3z\n"
        "vmaddw.xyzw vf3, vf17, vf3w\n"
        "vmulax.xyzw ACC, vf14, vf4x\n"
        "vmadday.xyzw ACC, vf15, vf4y\n"
        "vmaddaz.xyzw ACC, vf16, vf4z\n"
        "vmaddw.xyzw vf4, vf17, vf4w\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}

void iosApplyCurrentMatrix(void *a0, void *a1)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf8, 0x0(%1)\n"
        "vmulax.xyzw ACC, vf1, vf8x\n"
        "vmadday.xyzw ACC, vf2, vf8y\n"
        "vmaddaz.xyzw ACC, vf3, vf8z\n"
        "vmaddw.xyzw vf10, vf4, vf8w\n"
        "sqc2 vf10, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1) : "memory");
}

void iosApplyRotCurrentMatrix(void *a0, void *a1)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf8, 0x0(%1)\n"
        "vmulax.xyzw ACC, vf1, vf8x\n"
        "vmadday.xyzw ACC, vf2, vf8y\n"
        "vmaddaz.xyzw ACC, vf3, vf8z\n"
        "vmaddw.xyzw vf10, vf0, vf8w\n"
        "sqc2 vf10, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1) : "memory");
}

void iosRotTransPersCurrentMatrix(void *a0, void *a1)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf8, 0x0(%1)\n"
        "vmulax.xyzw ACC, vf1, vf8x\n"
        "vmadday.xyzw ACC, vf2, vf8y\n"
        "vmaddaz.xyzw ACC, vf3, vf8z\n"
        "vmaddw.xyzw vf10, vf4, vf8w\n"
        "vdiv Q, vf0w, vf10w\n"
        "vwaitq\n"
        "vmulq.xyz vf10, vf10, Q\n"
        "sqc2 vf10, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1) : "memory");
}

void iosTransposeCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vsub.xyzw vf5, vf0, vf0\n"
        "vaddx.y vf14, vf5, vf2x\n"
        "vaddx.z vf14, vf5, vf3x\n"
        "vaddx.w vf14, vf5, vf4x\n"
        "vaddy.x vf15, vf5, vf1y\n"
        "vaddy.z vf15, vf5, vf3y\n"
        "vaddy.w vf15, vf5, vf4y\n"
        "vaddz.x vf16, vf5, vf1z\n"
        "vaddz.y vf16, vf5, vf2z\n"
        "vaddz.w vf16, vf5, vf4z\n"
        "vaddw.x vf17, vf5, vf1w\n"
        "vaddw.y vf17, vf5, vf2w\n"
        "vaddw.z vf17, vf5, vf3w\n"
        "vmove.yzw vf1, vf14\n"
        "vmove.xzw vf2, vf15\n"
        "vmove.xyw vf3, vf16\n"
        "vmove.xyz vf4, vf17\n"
        ".set reorder\n"
        : : : "memory");
}

void iosTransposeRotationCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vsub.xyzw vf5, vf0, vf0\n"
        "vaddx.y vf14, vf5, vf2x\n"
        "vaddx.z vf14, vf5, vf3x\n"
        "vaddy.x vf15, vf5, vf1y\n"
        "vaddy.z vf15, vf5, vf3y\n"
        "vaddz.x vf16, vf5, vf1z\n"
        "vaddz.y vf16, vf5, vf2z\n"
        "vmove.yz vf1, vf14\n"
        "vmove.xz vf2, vf15\n"
        "vmove.xy vf3, vf16\n"
        ".set reorder\n"
        : : : "memory");
}

void iosInverseCurrentMatrix(void)
{
    __asm__ __volatile__(".set noreorder\n"
        "vsub.xyzw vf5, vf0, vf0\n"
        "vsubw.x vf6, vf0, vf0w\n"
        "vaddx.y vf14, vf5, vf2x\n"
        "vaddx.z vf14, vf5, vf3x\n"
        "vaddy.x vf15, vf5, vf1y\n"
        "vaddy.z vf15, vf5, vf3y\n"
        "vaddz.x vf16, vf5, vf1z\n"
        "vaddz.y vf16, vf5, vf2z\n"
        "vmulx.xyz vf17, vf4, vf6x\n"
        "vmove.yz vf1, vf14\n"
        "vmove.xz vf2, vf15\n"
        "vmove.xy vf3, vf16\n"
        "vmove.w vf17, vf0\n"
        "vmulax.xyzw ACC, vf1, vf17x\n"
        "vmadday.xyzw ACC, vf2, vf17y\n"
        "vmaddaz.xyzw ACC, vf3, vf17z\n"
        "vmaddw.xyzw vf4, vf0, vf17w\n"
        ".set reorder\n"
        : : : "memory");
}

void iosPushVu0Registers(void)
{
    register s128 *p __asm__("$3");

    iosDI();
    p = &B_000543F0[32];
    __asm__ __volatile__(
        "sqc2 $vf5, 0x0(%0)
"
        "	sqc2 $vf6, 0x10(%0)
"
        "	sqc2 $vf7, 0x20(%0)
"
        "	sqc2 $vf1, 0x30(%0)
"
        "	sqc2 $vf2, 0x40(%0)
"
        "	sqc2 $vf3, 0x50(%0)
"
        "	sqc2 $vf4, 0x60(%0)
"
        "	sqc2 $vf8, 0x70(%0)
"
        "	sqc2 $vf9, 0x80(%0)
"
        "	sqc2 $vf10, 0x90(%0)
"
        "	sqc2 $vf11, 0xA0(%0)
"
        "	sqc2 $vf12, 0xB0(%0)
"
        "	sqc2 $vf13, 0xC0(%0)
"
        "	sqc2 $vf14, 0xD0(%0)
"
        "	sqc2 $vf15, 0xE0(%0)
"
        "	sqc2 $vf16, 0xF0(%0)
"
        "	sqc2 $vf17, 0x100(%0)
"
        "	sqc2 $vf18, 0x110(%0)
"
        "	sqc2 $vf19, 0x120(%0)
"
        "	sqc2 $vf20, 0x130(%0)
"
        "	sqc2 $vf21, 0x140(%0)
"
        "	sqc2 $vf22, 0x150(%0)
"
        "	sqc2 $vf23, 0x160(%0)
"
        "	sqc2 $vf24, 0x170(%0)
"
        "	sqc2 $vf25, 0x180(%0)
"
        "	sqc2 $vf26, 0x190(%0)
"
        "	sqc2 $vf27, 0x1A0(%0)
"
        "	sqc2 $vf28, 0x1B0(%0)
"
        "	sqc2 $vf29, 0x1C0(%0)
"
        "	sqc2 $vf30, 0x1D0(%0)
"
        "	sqc2 $vf31, 0x1E0(%0)"
        : : "r"(p) : "memory");
    __asm__ __volatile__(
        "sqc2 $vf1, 0x0(%0)
"
        "	sqc2 $vf2, 0x10(%0)
"
        "	sqc2 $vf3, 0x20(%0)
"
        "	sqc2 $vf4, 0x30(%0)
"
        "	sqc2 $vf5, 0x40(%0)
"
        "	sqc2 $vf6, 0x50(%0)
"
        "	sqc2 $vf7, 0x60(%0)
"
        "	sqc2 $vf8, 0x70(%0)
"
        "	sqc2 $vf9, 0x80(%0)
"
        "	sqc2 $vf10, 0x90(%0)
"
        "	sqc2 $vf11, 0xA0(%0)
"
        "	sqc2 $vf12, 0xB0(%0)
"
        "	sqc2 $vf13, 0xC0(%0)
"
        "	sqc2 $vf14, 0xD0(%0)
"
        "	sqc2 $vf15, 0xE0(%0)
"
        "	sqc2 $vf16, 0xF0(%0)
"
        "	sqc2 $vf17, 0x100(%0)
"
        "	sqc2 $vf18, 0x110(%0)
"
        "	sqc2 $vf19, 0x120(%0)
"
        "	sqc2 $vf20, 0x130(%0)
"
        "	sqc2 $vf21, 0x140(%0)
"
        "	sqc2 $vf22, 0x150(%0)
"
        "	sqc2 $vf23, 0x160(%0)
"
        "	sqc2 $vf24, 0x170(%0)
"
        "	sqc2 $vf25, 0x180(%0)
"
        "	sqc2 $vf26, 0x190(%0)
"
        "	sqc2 $vf27, 0x1A0(%0)
"
        "	sqc2 $vf28, 0x1B0(%0)
"
        "	sqc2 $vf29, 0x1C0(%0)
"
        "	sqc2 $vf30, 0x1D0(%0)
"
        "	sqc2 $vf31, 0x1E0(%0)"
        : : "r"(p - 32) : "memory");
    iosEI();
}

void iosPopVu0Registers(void)
{
    register s128 *p __asm__("$3");
    register s128 *q __asm__("$2");

    iosDI();
    p = B_000545F0;
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%0)
"
        "	lqc2 $vf6, 0x10(%0)
"
        "	lqc2 $vf7, 0x20(%0)
"
        "	lqc2 $vf1, 0x30(%0)
"
        "	lqc2 $vf2, 0x40(%0)
"
        "	lqc2 $vf3, 0x50(%0)
"
        "	lqc2 $vf4, 0x60(%0)
"
        "	lqc2 $vf8, 0x70(%0)
"
        "	lqc2 $vf9, 0x80(%0)
"
        "	lqc2 $vf10, 0x90(%0)
"
        "	lqc2 $vf11, 0xA0(%0)
"
        "	lqc2 $vf12, 0xB0(%0)
"
        "	lqc2 $vf13, 0xC0(%0)
"
        "	lqc2 $vf14, 0xD0(%0)
"
        "	lqc2 $vf15, 0xE0(%0)
"
        "	lqc2 $vf16, 0xF0(%0)
"
        "	lqc2 $vf17, 0x100(%0)
"
        "	lqc2 $vf18, 0x110(%0)
"
        "	lqc2 $vf19, 0x120(%0)
"
        "	lqc2 $vf20, 0x130(%0)
"
        "	lqc2 $vf21, 0x140(%0)
"
        "	lqc2 $vf22, 0x150(%0)
"
        "	lqc2 $vf23, 0x160(%0)
"
        "	lqc2 $vf24, 0x170(%0)
"
        "	lqc2 $vf25, 0x180(%0)
"
        "	lqc2 $vf26, 0x190(%0)
"
        "	lqc2 $vf27, 0x1A0(%0)
"
        "	lqc2 $vf28, 0x1B0(%0)
"
        "	lqc2 $vf29, 0x1C0(%0)
"
        "	lqc2 $vf30, 0x1D0(%0)
"
        "	lqc2 $vf31, 0x1E0(%0)"
        : : "r"(p) : "memory");
    __asm__ __volatile__(
        "lqc2 $vf1, 0x0(%0)
"
        "	lqc2 $vf2, 0x10(%0)
"
        "	lqc2 $vf3, 0x20(%0)
"
        "	lqc2 $vf4, 0x30(%0)
"
        "	lqc2 $vf5, 0x40(%0)
"
        "	lqc2 $vf6, 0x50(%0)
"
        "	lqc2 $vf7, 0x60(%0)
"
        "	lqc2 $vf8, 0x70(%0)
"
        "	lqc2 $vf9, 0x80(%0)
"
        "	lqc2 $vf10, 0x90(%0)
"
        "	lqc2 $vf11, 0xA0(%0)
"
        "	lqc2 $vf12, 0xB0(%0)
"
        "	lqc2 $vf13, 0xC0(%0)
"
        "	lqc2 $vf14, 0xD0(%0)
"
        "	lqc2 $vf15, 0xE0(%0)
"
        "	lqc2 $vf16, 0xF0(%0)
"
        "	lqc2 $vf17, 0x100(%0)
"
        "	lqc2 $vf18, 0x110(%0)
"
        "	lqc2 $vf19, 0x120(%0)
"
        "	lqc2 $vf20, 0x130(%0)
"
        "	lqc2 $vf21, 0x140(%0)
"
        "	lqc2 $vf22, 0x150(%0)
"
        "	lqc2 $vf23, 0x160(%0)
"
        "	lqc2 $vf24, 0x170(%0)
"
        "	lqc2 $vf25, 0x180(%0)
"
        "	lqc2 $vf26, 0x190(%0)
"
        "	lqc2 $vf27, 0x1A0(%0)
"
        "	lqc2 $vf28, 0x1B0(%0)
"
        "	lqc2 $vf29, 0x1C0(%0)
"
        "	lqc2 $vf30, 0x1D0(%0)
"
        "	lqc2 $vf31, 0x1E0(%0)"
        : : "r"(q = B_000543F0) : "memory");
    iosEI();
}

void iosInitPushPosVuSema(void)
{
    B_000547F0 = iosCreateSema(1, 1, 0);
}

void iosCopyMatrix(float *dst, float *src)
{
    __asm__ __volatile__(
                         "lq $9, 0x30(%1)\n"
                         "sq $9, 0x30(%0)\n"
                         "lq $8, 0x20(%1)\n"
                         "sq $8, 0x20(%0)\n"
                         "lq $7, 0x10(%1)\n"
                         "sq $7, 0x10(%0)\n"
                         "lq $6, 0x0(%1)\n"
                         "sq $6, 0x0(%0)\n"
                         :
                         : "r"(dst), "r"(src)
                         : "$6", "$7", "$8", "$9", "memory");
}

void iosApplyRotMatrix(void *a0, void *a1, void *a2)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf8, 0x0(%2)\n"
        "lqc2 vf14, 0x0(%1)\n"
        "lqc2 vf15, 0x10(%1)\n"
        "lqc2 vf16, 0x20(%1)\n"
        "vmulax.xyzw ACC, vf14, vf8x\n"
        "vmadday.xyzw ACC, vf15, vf8y\n"
        "vmaddaz.xyzw ACC, vf16, vf8z\n"
        "vmaddw.xyzw vf10, vf0, vf8w\n"
        "sqc2 vf10, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(a0), "r"(a1), "r"(a2) : "memory");
}

void iosUnitMatrix(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "vmove.xyzw vf17, vf0\n"
        "vmr32.xyzw vf16, vf17\n"
        "vmr32.xyzw vf15, vf16\n"
        "vmr32.xyzw vf14, vf15\n"
        "sqc2 vf14, 0x0(%0)\n"
        "sqc2 vf15, 0x10(%0)\n"
        "sqc2 vf16, 0x20(%0)\n"
        "sqc2 vf17, 0x30(%0)\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}

void iosUnitRotation(void *a0)
{
    __asm__ __volatile__(".set noreorder\n"
        "vmove.xyzw vf17, vf0\n"
        "vmr32.xyzw vf16, vf17\n"
        "vmr32.xyzw vf15, vf16\n"
        "vmr32.xyzw vf14, vf15\n"
        "sqc2 vf14, 0x0(%0)\n"
        "sqc2 vf15, 0x10(%0)\n"
        "sqc2 vf16, 0x20(%0)\n"
        ".set reorder\n"
        : : "r"(a0) : "memory");
}

void iosTransposeMatrix(float *dst, float *src)
{
    __asm__ __volatile__(
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "lq $11, 0x30(%1)\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "sq $8, 0x0(%0)\n"
                         "sq $9, 0x10(%0)\n"
                         "sq $10, 0x20(%0)\n"
                         "sq $11, 0x30(%0)\n"
                         :
                         : "r"(dst), "r"(src)
                         : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

void iosInverseMatrix(float *dst, float *src)
{
    __asm__ __volatile__(
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "lqc2 vf1, 0x30(%1)\n"
                         "vmove.xyzw vf2, vf1\n"
                         "vsub.xyz vf1, vf1, vf1\n"
                         "vmove.xyzw vf9, vf1\n"
                         "qmfc2.ni $11, vf1\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "qmtc2.ni $8, vf3\n"
                         "qmtc2.ni $9, vf4\n"
                         "qmtc2.ni $10, vf8\n"
                         "vmulax.xyz ACC, vf3, vf2x\n"
                         "vmadday.xyz ACC, vf4, vf2y\n"
                         "vmaddz.xyz vf1, vf8, vf2z\n"
                         "vsub.xyz vf1, vf9, vf1\n"
                         "sq $8, 0x0(%0)\n"
                         "sq $9, 0x10(%0)\n"
                         "sq $10, 0x20(%0)\n"
                         "sqc2 vf1, 0x30(%0)\n"
                         :
                         : "r"(dst), "r"(src)
                         : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

void iosInverseMatrixPerfect(float out[][4], float in[][4])
{
    func_0000B438(4, out, in);
}
