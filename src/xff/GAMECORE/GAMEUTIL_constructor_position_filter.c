typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    u_long128 words[3];
    struct {
        u_long128 first;
        u_long128 second;
        int count;
    } fields;
} PositionFilter;

extern u_long128 ZeroPoint;
extern void GAMEUTIL_reset_position_filter(PositionFilter *, u_long128 *);
extern void GAMEUTIL_set_parameter_position_filter(void *, float);

void GAMEUTIL_constructor_position_filter(PositionFilter *filter)
{
    GAMEUTIL_reset_position_filter(filter, &ZeroPoint);
    GAMEUTIL_set_parameter_position_filter(filter, 0.0f);
}
