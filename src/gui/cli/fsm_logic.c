#include "../../inc/fsm_logic.h"

user_action_t get_signal(int user_input) {
  user_action_t act = START;

  switch (user_input) {
    case 'q':
      act = TERMINATE;
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

void game_tact(game_info_t *game, figure_t *figure) {
  if (game->ticks_left <= 0) {
    game->ticks_left = TIMEOUT;
    movedown(figure);
  }
  game->ticks_left--;
}

void handle_collision(game_info_t *game, figure_t *figure) {
  if (check_borders_collision(figure) || check_figure_collision(game, figure)) {
    moveup(figure);
    plant_figure(game, figure);
    game->score += erase_lines(game);
    drop_new_figure(game, figure);
    if (check_figure_collision(game, figure)) {
      game->state = OVER;
    }
  }
}

void sigact(user_action_t sig, game_info_t *game, figure_t *figure) {
  switch (sig) {
    case START:
      game_tact(game, figure);
      handle_collision(game, figure);
      break;
    case PAUSE:
      // game->state = STOPPED;
      break;
    case TERMINATE:
      game->state = QUIT;
      break;
    case LEFT:
      moveleft(figure);
      break;
    case RIGHT:
      moveright(figure);
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
