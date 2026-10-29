extern void iosRotMatrixY(float *, float);

void GAMEUTIL_get_yaw_matrix(float *matrix, float yaw)
{
    iosRotMatrixY(matrix, yaw);
}
