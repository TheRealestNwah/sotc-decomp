int iosGetFontIDWithJIS(int arg0)
{
    return (((arg0 >> 8) * 0x5E) + (arg0 & 0xFF)) - 0xC3F;
}
