#include "../../inc/tetris_fsm_logic.h"

user_action_t get_signal(int user_input) {
  user_action_t act = NOTHING;

  switch (user_input) {
    case ENTER_KEY:
      act = START;
      break;
    case 'q':
      act = QUIT;
      break;
    case KEY_UP:
      /* no action */
      break;
    case KEY_DOWN:
      act = DOWN;
      break;
    case KEY_LEFT:
      act = LEFT;
      break;
    case KEY_RIGHT:
      act = RIGHT;
      break;
    case ESCAPE:
      act = PAUSE;
      break;
    case SPACE:
      act = ACTION;
      break;
    case 'y':
      act = YES;
      break;
    case 'n':
      act = NO;
      break;
    default:
      break;
  }

  return act;
}

void moveup(figure_t *figure) { figure->y -= 1; }

void movedown(figure_t *figure) { figure->y += 1; }

void moveleft(figure_t *figure) {
  bool flag = TRUE;

  for (int i = 0; i < DOTS && flag == TRUE; i++)
    if (figure->shape[i][X] + figure->x == 0) flag = FALSE;

  if (flag) figure->x -= 1;
}

void moveright(figure_t *figure) {
  bool flag = TRUE;

  for (int i = 0; i < DOTS && flag == TRUE; i++)
    if (figure->shape[i][X] + figure->x == BOARD_W - 1) flag = FALSE;

  if (flag) figure->x += 1;
}

void handle_collision(game_info_t *game, figure_t *figure) {
  if (check_borders_collision(figure) || check_figure_collision(game, figure)) {
    moveup(figure);
    plant_figure(game, figure);
    update_stats(game, erase_lines(game));
    drop_new_figure(game, figure);
    if (check_figure_collision(game, figure)) {
      game->state = OVER;
    }
  }
}

void update_current_state(user_action_t action, game_info_t *game,
                          figure_t *figure) {
  switch (game->state) {
    case STARTED:
      print_welcome_window();
      if (action == START) game->state = PLAYING;
      if (action == QUIT) game->state = TERMINATED;
      break;
    case PLAYING:
      user_input(action, game, figure);
      clear_overlay();
      print_overlay();
      print_stats(game);
      print_field(game);
      print_figure(BOARD_Y + figure->y, BOARD_X + figure->x, figure->shape,
                   figure->id);
      break;
    case STOPPED:
      print_quit_window();
      if (action == NO) game->state = PLAYING;
      if (action == YES) game->state = TERMINATED;
      break;
    case PAUSED:
      print_pause_window();
      if (action == START) game->state = PLAYING;
      if (action == QUIT) game->state = TERMINATED;
      break;
    case OVER:
      print_gameover_window();
      if (action == START) {
        restart_game(game);
        drop_new_figure(game, figure);
        clear_overlay();
        game->state = PLAYING;
      }
      if (action == QUIT) game->state = TERMINATED;
      break;
    default:
      break;
  }
}

void game_tact(game_info_t *game, figure_t *figure) {
  if (game->ticks_left <= 0) {
    game->ticks_left = game->speed;
    movedown(figure);
    handle_collision(game, figure);
  }
  game->ticks_left--;
}

void user_input(user_action_t action, game_info_t *game, figure_t *figure) {
  switch (action) {
    case NOTHING:
      game_tact(game, figure);
      break;
    case PAUSE:
      game->state = PAUSED;
      break;
    case QUIT:
      game->state = STOPPED;
      break;
    case LEFT:
      moveleft(figure);
      if (check_figure_collision(game, figure)) moveright(figure);
      break;
    case RIGHT:
      moveright(figure);
      if (check_figure_collision(game, figure)) moveleft(figure);
      break;
    case UP:
      /* no action */
      break;
    case DOWN:
      movedown(figure);
      handle_collision(game, figure);
      break;
    case ACTION:
      if (figure->id != O) rotate_figure(figure, game);
      break;
    default:
      break;
  }
}
