#include "fsm_logic.h"

user_action_t get_signal(int user_input) {
  user_action_t act = START;

  if (user_input == 'q')
    act = TERMINATE;
  else if (user_input == KEY_DOWN)
    act = DOWN;
  else if (user_input == KEY_LEFT)
    act = LEFT;
  else if (user_input == KEY_RIGHT)
    act = RIGHT;
  else if (user_input == ESCAPE)
    act = PAUSE;
  else if (user_input == SPACE)
    act = ACTION;

  return act;
}

// void movedown(player_pos *frog_pos) {
//   if (frog_pos->y != BOARD_N) {
//     CLEAR_BACKPOS(frog_pos->y, frog_pos->x);
//     frog_pos->y += 2;
//   }
// }

// void moveright(player_pos *frog_pos) {
//   if (frog_pos->x != BOARD_M) {
//     CLEAR_BACKPOS(frog_pos->y, frog_pos->x);
//     frog_pos->x++;
//   }
// }

// void moveleft(player_pos *frog_pos) {
//   if (frog_pos->x != 1) {
//     CLEAR_BACKPOS(frog_pos->y, frog_pos->x);
//     frog_pos->x--;
//   }
// }

// void sigact(user_action_t sig, frog_state *state, game_stats_t *stats,
//             board_t *map, player_pos *frog_pos) {
//   switch (*state) {
//     case START:
//       switch (sig) {
//         case ENTER_BTN:
//           *state = SPAWN;
//           break;
//         case ESCAPE_BTN:
//           *state = EXIT_STATE;
//           break;
//         default:
//           *state = START;
//           break;
//       }

//       break;
//     case SPAWN:
//       if (stats->level > LEVEL_CNT)
//         *state = GAMEOVER;
//       else if (!lvlproc(map, stats)) {
//         fill_finish(map->finish);
//         print_finished(map);
//         frogpos_init(frog_pos);
//         *state = MOVING;
//       } else
//         *state = FILE_ERROR_STATE;

//       break;
//     case MOVING:
//       switch (sig) {
//         case MOVE_UP:
//           moveup(frog_pos);
//           break;
//         case MOVE_DOWN:
//           movedown(frog_pos);
//           break;
//         case MOVE_RIGHT:
//           moveright(frog_pos);
//           break;
//         case MOVE_LEFT:
//           moveleft(frog_pos);
//           break;
//         case ESCAPE_BTN:
//           *state = EXIT_STATE;
//           break;
//         default:
//           break;
//       }

//       if (*state != EXIT_STATE) {
//         if (check_collide(frog_pos, map))
//           *state = COLLIDE;
//         else if (check_finish_state(frog_pos, map))
//           *state = REACH;
//         else
//           *state = SHIFTING;
//       }

//       break;
//     case SHIFTING:
//       shift_map(map);

//       if (check_collide(frog_pos, map))
//         *state = COLLIDE;
//       else {
//         *state = MOVING;
//         print_board(map, frog_pos);
//         print_stats(stats);
//       }

//       break;
//     case REACH:
//       stats->score += 1;
//       add_proggress(map);
//       if (check_level_compl(map)) {
//         stats->level++;
//         stats->speed++;
//         *state = SPAWN;
//       } else {
//         frogpos_init(frog_pos);
//         print_finished(map);
//         *state = MOVING;
//       }

//       break;
//     case COLLIDE:
//       if (stats->lives) {
//         stats->lives--;
//         frogpos_init(frog_pos);
//         *state = MOVING;
//       } else
//         *state = GAMEOVER;
//       break;
//     case GAMEOVER:
//       print_banner(stats);
//       break;
//     default:
//       break;
//   }
// }
