int CAM_get_ground_contact_obj(int *p)
{
    int v = p[0xB2];

    if (v != 0) {
        return v;
    }
    return p[0];
}
