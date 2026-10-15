int GetCollisionFinderWorkSize(int count)
{
    unsigned int a = count * 8;
    unsigned int b = count * 12;

    return a + b + 0x66;
}
