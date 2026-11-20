extern void set_node_data_expression(void *, int, int, float, float, float);
extern int SkelFocusDef_PLAYER_HAND_A_R;
extern int SkelFocusDef_PLAYER_HARA;
extern int SkelFocusDef_PLAYER_HEAD;
extern int SkelFocusDef_PLAYER_JOWA_L;
extern int SkelFocusDef_PLAYER_JOWA_R;
extern int SkelFocusDef_PLAYER_KUBI;
extern int SkelFocusDef_PLAYER_LEFT_SHOULDER;
extern int SkelFocusDef_PLAYER_MUNE;
extern int SkelFocusDef_PLAYER_RIGHT_SHOULDER;
extern int SkelFocusDef_PLAYER_UDE_L;

#define F(v, n, p) ((v) >= 0.0f ? (v) * (p) : -((v) * (n)))
#define Z(v, p) ((v) >= 0.0f ? (v) * (p) : 0.0f)

static void func_0008E918(void *obj, float a, float b)
{
    set_node_data_expression(obj, SkelFocusDef_PLAYER_HARA, 1, a * (a >= 0.0f ? -10.0f : -40.0f), 0.0f, 0.0f);
    set_node_data_expression(obj, SkelFocusDef_PLAYER_MUNE, 0, F(b, 18.0f, -20.375f), F(b, -33.5f, 17.348f),
        -(Z(b, 14.9f) + a * (a >= 0.0f ? -10.0f : -40.0f)));
    set_node_data_expression(obj, SkelFocusDef_PLAYER_KUBI, 0, F(b, 8.0f, -1.71f), Z(b, -3.4f), -Z(b, -8.05f));
    set_node_data_expression(obj, SkelFocusDef_PLAYER_HEAD, 0, F(b, 9.3f, -17.98f), Z(b, 7.5f),
        -(F(b, 3.4f, 24.06f) + a * -30.0f));
    set_node_data_expression(obj, SkelFocusDef_PLAYER_LEFT_SHOULDER, 0, F(b, 6.4f, -14.77f), Z(b, 17.99f), 0.0f);
    set_node_data_expression(obj, SkelFocusDef_PLAYER_JOWA_L, 0, F(b, 22.6f, 1.69f), F(b, -2.6f, 4.97f), -F(b, -41.3f, -27.1f));
    set_node_data_expression(obj, SkelFocusDef_PLAYER_UDE_L, 0, 0.0f, Z(b, -7.98f), 0.0f);
    set_node_data_expression(obj, SkelFocusDef_PLAYER_RIGHT_SHOULDER, 0, F(b, 4.4f, -23.42f),
        F(b, 9.0f, -18.94f) + a * (a >= 0.0f ? -30.0f : -10.0f), 0.0f);
    set_node_data_expression(obj, SkelFocusDef_PLAYER_JOWA_R, 0, F(b, 17.6f, -5.84f), F(b, 15.2f, -21.196f), -F(b, 7.7f, 35.786f));
    set_node_data_expression(obj, SkelFocusDef_PLAYER_HAND_A_R, 0, F(b, 35.5f, 9.19f), 0.0f, -F(b, 11.2f, -12.91f));
}
