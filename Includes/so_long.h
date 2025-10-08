#ifndef SO_LONG_H
# define SO_LONG_H

# define DIR_RIGHT 1
# define DIR_LEFT 2
# define DIR_DOWN 3
# define DIR_UP 4
# define IMG_H 64
# define IMG_W 64

# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_player
{
    int moves;
    int dir;
    int x;
    int y;
} t_player;

typedef struct s_physicals
{
    void *img;
    void *closed_d;
    void *opened_d;
    void *collectibles;
    void *block;
    void *floor;
    void *looking_up;
    void *looking_down;
    void *looking_right;
    void *looking_left;
    void *ghost1;
    void *ghost2;
    void *ghost3;
    void *ghost4;
    void *numbers[10];
    int height;
    int width;
} t_physicals;

typedef struct s_game
{
    char **map;
    void *mlx;
    int collectables;
    int collected;
    int exit_y;
    int exit_x;
    int height;
    int width;
    t_player player;
    t_physicals imgs;
    void *window;
} t_game;

/****************************************/
/*         error_handling.c             */
/****************************************/
int invalid_file(char *file);
int check_extension(char *file);
int empty_file_check(char *file);
void validate_file(int argc, char *argv);

/****************************************/
/*            map_helpers.c             */
/****************************************/
void flood_fill(char **map, int x, int y);
void clean_map(char **map);
char **mock_map_(char **map, int rows);
void find_player(char **map, int *x, int *y);
int not_flooded(char **map);

/****************************************/
/*         map_validation.c             */
/****************************************/
int is_not_rectangular(char **map, int columns);
int gaps_check(char **map, int columns, int rows);
int check_invalid_chars(char **map, int columns, int rows);
int check_counters(char **map);
int is_the_map_valid(char **map);

/****************************************/
/*              counters.c              */
/****************************************/
void check_map_tools(char **map, int rows, int columns,int *player_counter, int *exits_counter);
int count_collectibles(char **map);
int ft_strlen_so_long(char *str);

/****************************************/
/*              read_map.c              */
/****************************************/
int read_map(char *map, char ***parsed, int count);
int count_lines(int fd);
int unreachable_element(char **map, int rows);

/****************************************/
/*            start_game.c             */
/****************************************/
int start_game(t_game *pac_man, char *map);
char **parse_map(char *map);
void locate_exit(t_game *pac_man);
void map_measurements(char **map, int *rows, int *columns);

/****************************************/
/*            rendering.c              */
/****************************************/
void render_game(t_game *pac_man);
void render_player(t_game *pac_man, int y, int x);
void render_img(t_game *pac_man, char type, int y, int x);
void render_moves(t_game *pac_man);
void stick_image(t_game *pac_man, void *img, int grid_x, int grid_y);

/****************************************/
/*            install_imgs.c            */
/****************************************/
void spawn_player(t_player *player, char **map);
void deploy_player(t_physicals *imgs, void *mlx);
void load_number_imgs(t_physicals *imgs, void *mlx);
int	check_imgs(t_physicals *imgs);
int deploy_imgs(t_physicals *imgs, void *mlx);

/****************************************/
/*         img_helper.c                 */
/****************************************/
int img_is_null(t_physicals *imgs);
int player_is_null(t_physicals *imgs);
void *select_ghost_sprite(t_game *pac_man, int seq);

/****************************************/
/*         close_game.c                 */
/****************************************/
void clean_numbers(t_physicals *imgs, void *mlx);
void clean_player_imgs(t_physicals *imgs, void *mlx);
void null_imgs(t_physicals *imgs);
void clean_imgs(t_physicals *imgs, void *mlx);
int close_game(t_game *pac_man);

/****************************************/
/*         end_game.c                   */
/****************************************/
void end_game(t_game *pac_man, char elem);

/****************************************/
/*         mlx_hook_helper.c            */
/****************************************/
void re_render(t_game *pac_man);
int pac_keys(int keycode, t_game *pac_man);
int	blocked(t_game *g, int new_x, int new_y);
void attempt_move(t_game *g, int dx, int dy, int dir);


#endif
