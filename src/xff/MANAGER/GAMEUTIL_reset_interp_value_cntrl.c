typedef struct {
    float start;
    float value;
    float hope;
} InterpValueCntrl;

extern float GAMEUTIL_get_interp_value_interp_value_cntrl(InterpValueCntrl *cntrl);

float GAMEUTIL_reset_interp_value_cntrl(InterpValueCntrl *cntrl, float value)
{
    cntrl->start = value;
    cntrl->value = value;
    cntrl->hope = value;
    return GAMEUTIL_get_interp_value_interp_value_cntrl(cntrl);
}
