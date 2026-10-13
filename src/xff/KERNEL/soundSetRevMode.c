extern int sg2NicoReverbMode;

void soundSetRevMode(int arg0, int arg1)
{
    if (arg0 == 0) {
        sg2NicoReverbMode |= arg1;
        return;
    }
    sg2NicoReverbMode &= ~arg1;
}
