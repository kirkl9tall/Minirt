#include "minirt.h"

int	main(void)
{
	t_mini	mini;
	double	aspect_ratio;
	double	scale;

	// Initialize MLX
	mini.mlx_utils.mlx = mlx_init();
	if (!mini.mlx_utils.mlx)
		return (1);
	mini.mlx_utils.win = mlx_new_window(mini.mlx_utils.mlx, W_W, W_H,
			"Ray Tracer Test");
	if (!mini.mlx_utils.win)
		return (1);
	mini.mlx_utils.img = mlx_new_image(mini.mlx_utils.mlx, W_W, W_H);
	if (!mini.mlx_utils.img)
		return (1);
	mini.mlx_utils.addr = mlx_get_data_addr(mini.mlx_utils.img,
			&mini.mlx_utils.bpp, &mini.mlx_utils.size_line,
			&mini.mlx_utils.endian);

	// Initialize camera with proper FOV
	mini.cam.pos = (t_vec3){0, 0, 0};
	mini.cam.orient = vect_normalized((t_vec3){0, 0, 1});
	mini.cam.up_v = vect_normalized((t_vec3){0, 1, 0});
	mini.cam.right_v = vect_normalized(vect_cross(mini.cam.orient, mini.cam.up_v));
	
	// Use FOV to calculate viewport size
	double fov = 60.0;
	aspect_ratio = (double)W_W / (double)W_H;
	scale = tan(fov * 0.5 * M_PI / 180.0);
	mini.cam.width_canva = 2.0 * scale * aspect_ratio;
	mini.cam.height_canva = 2.0 * scale;

	// Create a sphere
	mini.sph = malloc(sizeof(t_sphere));
	if (!mini.sph)
		return (1);
	mini.sph->sph_center = (t_vec3){0, 0, 5};
	mini.sph->s_diam = 2.0;
	mini.sph->color = (t_vec3){255, 0, 0};
	mini.sph->next = NULL;

	// Create a plane  
	mini.plane = malloc(sizeof(t_plan));
	if (!mini.plane)
		return (1);
	mini.plane->cor_plan = (t_vec3){0, -2, 0};
	mini.plane->nnv_plan = (t_vec3){0, 1, 0};
	mini.plane->color = (t_vec3){0, 255, 0};
	mini.plane->next = NULL;

	// Set cylinder to NULL
	mini.cy = NULL;

	// ADD AMBIENT LIGHTING (THIS WAS MISSING!)
	mini.amb.alr = 0.3;  // 30% ambient light
	mini.amb.color = (t_vec3){255, 255, 255};  // White ambient light

	// ADD LIGHT SOURCE (THIS WAS MISSING!)
	mini.light.light_point = (t_vec3){5, 5, 0};
	mini.light.lbr = 1.0;
	mini.light.color = (t_vec3){255, 255, 255};

	// Render the scene
	render_scene(&mini);

	// Display and wait
	mlx_put_image_to_window(mini.mlx_utils.mlx, mini.mlx_utils.win,
		mini.mlx_utils.img, 0, 0);
	mlx_loop(mini.mlx_utils.mlx);

	// Cleanup
	free(mini.sph);
	free(mini.plane);
	return (0);
}
