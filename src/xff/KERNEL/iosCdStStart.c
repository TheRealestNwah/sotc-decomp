extern int B_00046554, B_00046550, B_0004654C;
extern long B_0004E590;

void iosCdStStart(int lsn)
{
    B_0004654C = B_00046550;
    B_0004E590 = (long)(lsn + B_00046554) << 11;
}
