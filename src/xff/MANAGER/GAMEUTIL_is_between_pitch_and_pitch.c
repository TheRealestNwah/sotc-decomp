int GAMEUTIL_is_between_pitch_and_pitch(float fparg0, float fparg1, float fparg2)
{
    if (((fparg1 <= fparg0) && (fparg0 <= fparg2)) || ((fparg2 <= fparg0) && (fparg0 <= fparg1))) {
        return 1;
    }
    return 0;
}
