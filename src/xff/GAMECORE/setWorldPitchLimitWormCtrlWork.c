void setWorldPitchLimitWormCtrlWork(char *p, float a, float b)
{
    a *= 0.0174532925f;
    b *= 0.0174532925f;
    *(float *)(p + 0x74) = -__builtin_fabsf(a);
    *(float *)(p + 0x78) = __builtin_fabsf(b);
}
