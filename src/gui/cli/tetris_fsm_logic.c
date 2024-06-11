#include "tetris_fsm_logic.h"

void update_current_state(user_action_t action, game_info_t *game,
                          figure_t *figure) {
  switch (game->state) {
    case STARTED:
      print_welcome_window();
      if (action == START) {
        game->state = PLAYING;
        clock_gettime(CLOCK_MONOTONIC, &game->start);
      }
      if (action == QUIT) game->state = TERMINATED;
      break;
    case PLAYING:
      game_tact(game, figure);
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
      if (action == NO) {
        game->state = PLAYING;
        clock_gettime(CLOCK_MONOTONIC, &game->start);
      }
      if (action == YES) game->state = TERMINATED;
      break;
    case PAUSED:
      print_pause_window();
      if (action == START) {
        game->state = PLAYING;
        clock_gettime(CLOCK_MONOTONIC, &game->start);
      }
      if (action == QUIT) game->state = TERMINATED;
      break;
    case OVER:
      print_gameover_window();
      if (action == START) {
        restart_game(game);
        drop_new_figure(game, figure);
        clear_overlay();
        game->state = PLAYING;
        clock_gettime(CLOCK_MONOTONIC, &game->start);
      }
      if (action == QUIT) game->state = TERMINATED;
      break;
    default:
      break;
  }
}

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

void user_input(user_action_t action, game_info_t *game, figure_t *figure) {
  switch (action) {
    case NOTHING:
      // game_tact(game, figure);
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

void game_tact(game_info_t *game, figure_t *figure) {
  struct timespec end;
  long delta = 0L;
  clock_gettime(CLOCK_MONOTONIC, &end);
  delta = (end.tv_sec - game->start.tv_sec) * 1000000000L +
          (end.tv_nsec - game->start.tv_nsec);

  if (delta >= game->speed) {
    movedown(figure);
    handle_collision(game, figure);
    clock_gettime(CLOCK_MONOTONIC, &game->start);
  }
}
