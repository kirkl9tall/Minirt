#include "minirt.h"


int check_cross(t_vec3 v1, t_vec3 v2)
{
    if (v1.x == v2.x && v1.y == v2.y &&  v1.z == v2.z)
        return 1;
    return (0);
}
void project_camera(t_mini *mini)
{
    t_vec3 rand_vec;
    
    rand_vec.x = 0;
    rand_vec.y = 1;
    rand_vec.z = 0;
    // check_ori(mini->cam.orient);
    // check_cross(rand_vec,mini->cam.orient);`
    mini->cam.right_v = vect_cross(rand_vec,mini->cam.orient);
    mini->cam.up_v = vect_cross(mini->cam.orient,mini->cam.right_v);
    mini->cam.width_canva = 2 * tan(mini->cam.fov * 0.01745329 / 2);
    mini->cam.height_canva =  (mini->cam.width_canva * W_H) / W_W ;
}