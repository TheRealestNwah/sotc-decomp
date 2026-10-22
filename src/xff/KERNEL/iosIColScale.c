typedef int s128 __attribute__((mode(TI)));
typedef union { long words[2]; int i[4]; s128 q; } IVector;
typedef struct { unsigned char r, g, b, a; } Col;

/* iosMulMvec: component-wise integer-vector multiplication. */
static void func_0000D548(IVector *dst, const IVector *a, const IVector *b)
{
    IVector x;
    IVector y;
    s128 r;

    x.words[0] = a->words[0];
    x.words[1] = a->words[1];
    y.words[0] = b->words[0];
    y.words[1] = b->words[1];
    __asm__ __volatile__(
        "pmultw $8, %1, %2\n"
        "\tmtsab $0, 4\n"
        "\tqfsrv $9, %1, %2\n"
        "\tqfsrv $10, %2, %1\n"
        "\tpmultw $11, $9, $10\n"
        "\tpmthi $11\n"
        "\tpmtlo $8\n"
        "\tpmfhl.lw %0"
        : "=r"(r) : "r"(x.q), "r"(y.q) : "$8", "$9", "$10", "$11");
    dst->q = r;
}

void iosApplyM_Mat(void *unused, IVector *m, const IVector *v)
{
    IVector x;

    x.words[0] = v->words[0];
    x.words[1] = v->words[1];
    __asm__ __volatile__(
        ".set noreorder\n"
        "\tli $10, 4\n"
        "1:\n"
        "\tlq $8, 0(%0)\n"
        "\taddi $10, $10, -1\n"
        "\tpmultw $9, %1, $8\n"
        "\taddi %0, %0, 16\n"
        "\tmtsab $0, 4\n"
        "\tqfsrv $12, $0, $8\n"
        "\tqfsrv $13, $0, %1\n"
        "\tpmultw $14, $13, $12\n"
        "\tpaddw $15, $9, $14\n"
        "\tmtsab $0, 8\n"
        "\tqfsrv $16, $0, $15\n"
        "\tpaddw $11, $15, $16\n"
        "\tsw $11, 0(%0)\n"
        "\taddi %0, %0, 4\n"
        "\tbgtz $10, 1b\n"
        "\tnop\n"
        "\t.set reorder"
        : "+r"(m) : "r"(x.q) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$16", "memory");
}

int iosCalcIcolorToBrightness(unsigned int color)
{
    IVector channels;

    channels.i[0] = color & 0xFF;
    channels.i[1] = (color >> 8) & 0xFF;
    channels.i[2] = (color >> 16) & 0xFF;
    channels.i[3] = color >> 24;
    {
        IVector factors = { .i = {0x266666, 0x4B851E, 0xE147A, 0x7FFFFFFF} };
        func_0000D548(&channels, &channels, &factors);
    }
    return ((channels.i[0] + channels.i[1] + channels.i[2]) >> 23) & 0xFF;
}

static void func_0000D778(IVector *dst);

void iosIColScale(Col *out, unsigned int color, float scale)
{
    IVector c;
    IVector f;
    int k;

    k = scale * 4096.0f;
    f.i[0] = k;
    f.i[1] = k;
    f.i[2] = k;
    c.i[0] = color & 0xFF;
    c.i[1] = (color >> 8) & 0xFF;
    c.i[2] = (color >> 16) & 0xFF;
    c.i[3] = color >> 24;
    func_0000D548(&c, &c, &f);
    __asm__ __volatile__("psrlw %0, %1, 12" : "=r"(c.q) : "r"(c.q));
    func_0000D778(&c);
    out->r = c.i[0];
    out->g = c.i[1];
    out->b = c.i[2];
    out->a = 0xFF;
}

typedef union { Col c; int i; s128 q; } ColU;

void iosIColAddVec(Col *out, int a, int b)
{
    ColU x;
    ColU y;
    ColU z;

    x.i = a;
    y.i = b;
    __asm__ __volatile__("paddub %0, %1, %2" : "=r"(z.q) : "r"(x.q), "r"(y.q));
    *(int *)out = z.i;
}

/* iosSwClip255Mvec: clamps each word of $v0 to 0..255 and stores it. */
static void func_0000D778(IVector *dst)
{
    register s128 r __asm__("$2");

    __asm__ __volatile__(
        "pceqw $8, $0, $0\n"
        "\tpsrlw $9, $8, 23\n"
        "\tpsrlw $11, $8, 1\n"
        "\tpsubsw $9, $11, $9\n"
        "\tpaddsw %0, %0, $9\n"
        "\tpsrlw $10, $8, 31\n"
        "\tpsubsw %0, %0, $9\n"
        "\tpaddw $10, $11, $10\n"
        "\tpaddsw %0, %0, $10\n"
        "\tpsubsw %0, %0, $10"
        : "+r"(r) : : "$8", "$9", "$10", "$11");
    dst->q = r;
}
