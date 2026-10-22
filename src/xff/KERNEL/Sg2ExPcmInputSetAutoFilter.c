extern int func_0002EA68(int);
extern int func_0002EAB8(int, int);
extern void func_0002E8D8(int, int, int, int);

int Sg2ExPcmInputSetAutoFilter(unsigned int channel, int filter, int index)
{
    int count;

    if (channel >= 4)
        return -2;
    count = func_0002EA68(filter);
    if (count == -1)
        return count;
    if (!(index < count))
        return -2;
    func_0002E8D8(func_0002EAB8(filter, index), channel, filter, index);
    return 0;
}
