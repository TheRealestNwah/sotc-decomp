typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    u_long128 words[3];
    struct {
        u_long128 first;
        u_long128 second;
        int count;
    } fields;
} PositionFilter;

void GAMEUTIL_reset_position_filter(PositionFilter *filter, u_long128 *position) {
    filter->fields.first = *position;
    filter->fields.second = *position;
    filter->fields.count = 1;
}
