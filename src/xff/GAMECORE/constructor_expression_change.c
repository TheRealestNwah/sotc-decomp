typedef struct {
    int type;
    float start;
    float end;
    int time;
    float speed;
    int flag;
} ExpressionChangeEntry;

typedef struct {
    int count;
    ExpressionChangeEntry entries[5];
} ExpressionChange;

void constructor_expression_change(ExpressionChange *self)
{
    ExpressionChangeEntry *entry = self->entries;
    int i;

    self->count = 0;
    for (i = 4; i >= 0; --i, ++entry) {
        entry->type = 0;
        entry->start = 0.0f;
        entry->speed = 0.0f;
        entry->end = 0.0f;
        entry->flag = 0;
        entry->time = 0;
    }
}
