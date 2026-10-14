typedef struct {
    int id;
    float x;
    float y;
    float z;
    char pad10[0x24];
    int mode;
} NodeExpression;

typedef struct {
    char pad0[0x9C];
    int count;
    NodeExpression nodes[1];
} NodeData;

void set_node_data_expression(NodeData *data, int id, int mode, float x, float y, float z)
{
    NodeExpression *e;
    int n;
    int i;

    if (id == 0) {
        return;
    }
    n = data->count;
    i = 0;
    if (n > 0) {
        e = data->nodes;
        do {
            if (e->id == id) {
                e->x = x;
                e->y = y;
                e->z = z;
                e->mode = mode;
                return;
            }
            i++;
            e++;
        } while (i < n);
    }
}
