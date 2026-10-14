extern int GAMEUTIL_get_node_quaternion_posi_by_id_extend();

int GAMEUTIL_get_node_quaternion_posi_by_id(int a, int b, int c, int d)
{
    return GAMEUTIL_get_node_quaternion_posi_by_id_extend(a, b, c, d, 0, 0);
}
