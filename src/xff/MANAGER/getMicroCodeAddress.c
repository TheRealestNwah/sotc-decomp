extern char MicroCode[];

int getMicroCodeAddress(int i)
{
    return ((int *)MicroCode)[i];
}
