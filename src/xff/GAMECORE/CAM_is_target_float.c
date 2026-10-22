extern int *GAMEUTIL_get_data_record_info(void *, int);

int CAM_is_target_float(char *camera, int count)
{
    char *records = camera + 0x2CC;
    int i;

    if (count <= 0 || *(int *)(records + 0xC) < count)
        count = *(int *)(records + 0xC);
    for (i = 0; i < count; i++) {
        if (*GAMEUTIL_get_data_record_info(records, i) == 1)
            return 1;
    }
    return 0;
}
