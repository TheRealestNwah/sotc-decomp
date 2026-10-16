unsigned char *isysGetLetterObj(unsigned char *o)
{
    switch (o[8]) {
    case 6:
    case 9:
    case 11:
    case 13:
    case 22:
        return o;
    case 7:
    case 8:
    case 10:
    case 12:
    case 14 ... 21:
        break;
    }
    return 0;
}
