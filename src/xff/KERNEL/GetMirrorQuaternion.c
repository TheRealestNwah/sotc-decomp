typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Quaternion;
void GetMirrorQuaternion(Quaternion *out, Quaternion *in, unsigned int mode)
{
    out->q = in->q;
    switch (mode) {
    case 0: out->f[0] = -out->f[0]; break;
    case 1: out->f[1] = -out->f[1]; break;
    case 2: out->f[2] = -out->f[2]; break;
    case 4: out->f[0] = -out->f[0]; out->f[1] = -out->f[1]; break;
    case 3: out->f[0] = -out->f[0]; out->f[2] = -out->f[2]; break;
    case 5: out->f[1] = -out->f[1]; out->f[2] = -out->f[2]; break;
    case 6:
    default: out->f[0] = -out->f[0]; out->f[1] = -out->f[1]; out->f[2] = -out->f[2]; break;
    }
}
