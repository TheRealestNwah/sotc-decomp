extern int opFlag;

void opflowOp2End(int arg0)
{
    opFlag = ((opFlag | 4) & ~8) | ((arg0 & 1) * 8);
}
