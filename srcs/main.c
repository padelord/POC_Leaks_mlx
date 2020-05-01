#include "test.h"

typedef struct    s_xvar
{
    Display        *display;
    Window        root;
    int            screen;
    int            depth;
    Visual        *visual;
    Colormap    cmap;
    int            private_cmap;
    t_win_list    *win_list;
    int            (*loop_hook)();
    void        *loop_param;
    int            use_xshm;
    int            pshm_format;
    int            do_flush;
    int            decrgb[6];
    Atom        wm_delete_window;
}                t_xvar;

void mlx_destroy(t_xvar *mlx)
{
	XFlush(mlx->display);
	XCloseDisplay(mlx->display);
	free(mlx);
}

int   main(int ac, char **av)
{
	t_xvar	*mlx = 0;
	t_img	*img = 0;
	t_win_list	*win = 0;

	mlx = mlx_init();
	img = mlx_new_image(mlx, 50, 50);
	win = mlx_new_window(mlx, 50, 50, "test");
	mlx_destroy_image(mlx, img);
	mlx_destroy_window(mlx, win);
	//mlx_destroy(mlx);
    return 0;
}
