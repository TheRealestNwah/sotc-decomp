extern int GAMEUTIL_get_pre_changed_status_status_manager(void *);

int get_pre_type_expression(char *work)
{
    return GAMEUTIL_get_pre_changed_status_status_manager((void *)(work + 4));
}
