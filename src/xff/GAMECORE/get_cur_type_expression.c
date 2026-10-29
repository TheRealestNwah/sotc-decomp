extern int GAMEUTIL_get_cur_status_status_manager(int *);

int get_cur_type_expression(char *work)
{
    return GAMEUTIL_get_cur_status_status_manager((int *)(work + 4));
}
