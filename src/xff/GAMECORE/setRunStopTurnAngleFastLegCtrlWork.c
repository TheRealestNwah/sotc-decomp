void setRunStopTurnAngleFastLegCtrlWork(char *p, float f)
{
    *(float *)(p + 0x4C) = f * 0.0174532925f;
}
