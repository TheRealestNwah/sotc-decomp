float getexpressiondatapoint(int arg0, int arg1)
{
    return (*(float *)((char *)(((arg1 * 0x10) + arg0)) + 4));
}
