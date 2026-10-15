/* Splits a packed RGBA color into four ints. */
void iosIColToMvecSl(int *v, unsigned int c)
{
    v[0] = c & 0xFF;
    v[1] = (c >> 8) & 0xFF;
    v[2] = (c >> 16) & 0xFF;
    v[3] = c >> 24;
}
