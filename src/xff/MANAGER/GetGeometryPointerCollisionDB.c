void *GetGeometryPointerCollisionDB(char *g)
{
    switch (*(unsigned int *)(g + 0x30)) {
    case 2:
    case 3:
    case 4:
    case 5:
        return g;
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
        break;
    }
    return 0;
}
