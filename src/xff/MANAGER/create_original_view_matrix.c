extern int iosSetCameraMatrix();

int create_original_view_matrix(int a, int b, int c, int d)
{
    return iosSetCameraMatrix(a, b, c, d);
}
