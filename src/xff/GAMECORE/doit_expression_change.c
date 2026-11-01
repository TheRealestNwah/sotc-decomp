typedef struct {
    int type;
    float yaw;
    float max;
    int motA;
    float min;
    int motB;
} ExprElem;

typedef struct {
    int count;
    ExprElem e[5];
} ExprList;

extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern void SCRRequestMotionDirect(void *, int);

ExprElem *doit_expression_change(ExprList *list, int type, void *motion, float yaw)
{
    int i;
    for (i = 0; i < list->count; i++) {
        ExprElem *e = &list->e[i];
        int r = 0;
        if (e->type == type) {
            float d = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(e->yaw, yaw);
            if (0.0f <= d) {
                if (e->max <= d)
                    SCRRequestMotionDirect(motion, e->motA);
            } else {
                if (d <= e->min)
                    SCRRequestMotionDirect(motion, e->motB);
            }
            r = 1;
        }
        if (r == 1)
            return e;
    }
    return 0;
}
