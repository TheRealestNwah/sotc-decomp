extern char *GetCharacterClass(void *);
extern void StabilizeToYRotQuaternion(float *);
extern void SetLayoutClassRootQuaternion(char *, float *);

void nico_StabCharacterRootRotationToXZ(void *obj)
{
    char *c = GetCharacterClass(obj);
    float *q;

    c[0x529] = 0;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(c + 0x4B0) : "memory");
    StabilizeToYRotQuaternion(*(float **)(c + 0x13C));
    q = *(float **)(c + 0x13C);
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(q) : "memory");
    SetLayoutClassRootQuaternion(c, *(float **)(c + 0x13C));
}
