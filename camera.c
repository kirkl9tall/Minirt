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
    if (check_cross(rand_vec,mini->cam.orient))
        
    mini->cam.right_v = vect_cross(rand_vec,mini->cam.orient);
    mini->cam.up_v = vect_cross(mini->cam.orient,mini->cam.right_v);

    // printf("x : %lf  y :%lf  z : %lf \n",right_vec.x,right_vec.y,right_vec.z);

}