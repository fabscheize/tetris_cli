#include "tetris_fsm_logic.h"

void play(game_info_t *game) {
  game->state = PLAYING;
  clock_gettime(CLOCK_MONOTONIC, &game->start);
}

void update_current_state(user_action_t action, game_info_t *game,
                          figure_t *figure) {
  switch (game->state) {
    case STARTED:
    case PAUSED:
      if (action == START) play(game);
      if (action == QUIT) game->state = TERMINATED;
      break;
    case PLAYING:
      game_tact(game, figure);
      user_input(action, game, figure);
      calculate_shadow(game, figure);
      break;
    case STOPPED:
      if (action == NO) play(game);
      if (action == YES) game->state = TERMINATED;
      break;
    case OVER:
      if (action == START) {
        restart_game(game, RANDOM_FIGURE);
        drop_new_figure(game, figure, RANDOM_FIGURE);
        play(game);
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
    case UP_KEY:
      /* no action */
      break;
    case DOWN_KEY:
      act = DOWN;
      break;
    case LEFT_KEY:
      act = LEFT;
      break;
    case RIGHT_KEY:
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
