int IsNonISysObjTypeRes(int t)
{
    switch (t) {
    case 15 ... 28:
    case 32 ... 35:
        return 1;
    }
    return 0;
}
