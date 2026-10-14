void set_root_node_data_expression(int arg0, float fparg0, float fparg1, float fparg2, float fparg3, float fparg4, float fparg5)
{
    void *temp_a0;

    temp_a0 = arg0 + 0x34;
    (*(float *)((char *)(temp_a0) + 0x40)) = fparg5;
    (*(float *)((char *)(temp_a0) + 4)) = fparg0;
    (*(float *)((char *)(temp_a0) + 8)) = fparg1;
    (*(float *)((char *)(temp_a0) + 0xC)) = fparg2;
    (*(float *)((char *)(temp_a0) + 0x38)) = fparg3;
    (*(float *)((char *)(temp_a0) + 0x3C)) = fparg4;
    (*(int *)((char *)(temp_a0) + 0x34)) = 0;
}
