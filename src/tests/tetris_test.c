#include <check.h>

#include "tetris_fsm_logic.h"

START_TEST(tetris_logic) {
#line 4
  int signal = 0;
  int ***figures = init_figures();

  game_info_t *game = create_game(figures, T, BOARD_H, BOARD_W);
  figure_t *figure = create_figure(figures, I, START_Y, START_X);

  signal = ENTER_KEY;
  update_current_state(get_signal(signal), game, figure);
  ck_assert_int_eq(game->state, PLAYING);
  signal = ESCAPE;
  update_current_state(get_signal(signal), game, figure);
  ck_assert_int_eq(game->state, PAUSED);
  signal = ENTER_KEY;
  update_current_state(get_signal(signal), game, figure);
  ck_assert_int_eq(game->state, PLAYING);

  for (int i = 0; i < 10; i++) {
    signal = RIGHT_KEY;
    update_current_state(get_signal(signal), game, figure);
  }
  ck_assert_int_eq(figure->x, 8);

  for (int i = 0; i < 10; i++) {
    signal = LEFT_KEY;
    update_current_state(get_signal(signal), game, figure);
  }
  ck_assert_int_eq(figure->x, 2);

  usleep(500000);
  signal = 0;
  update_current_state(get_signal(signal), game, figure);
  ck_assert_int_eq(figure->y, 1);

  for (int i = 0; i < 19; i++) {
    signal = DOWN_KEY;
    update_current_state(get_signal(signal), game, figure);
  }
  ck_assert_int_eq(game->field[19][0], SHAPE_COLOR(I));
  ck_assert_int_eq(game->field[19][1], SHAPE_COLOR(I));
  ck_assert_int_eq(game->field[19][2], SHAPE_COLOR(I));
  ck_assert_int_eq(game->field[19][3], SHAPE_COLOR(I));

  ck_assert_int_eq(figure->id, T);

  signal = DOWN_KEY;
  update_current_state(get_signal(signal), game, figure);
  signal = SPACE;
  update_current_state(get_signal(signal), game, figure);
  signal = SPACE;
  update_current_state(get_signal(signal), game, figure);

  for (int i = 0; i < 19; i++) {
    signal = DOWN_KEY;
    update_current_state(get_signal(signal), game, figure);
  }
  ck_assert_int_eq(game->field[19][4], SHAPE_COLOR(T));
  ck_assert_int_eq(game->field[19][5], SHAPE_COLOR(T));
  ck_assert_int_eq(game->field[19][6], SHAPE_COLOR(T));

  drop_new_figure(game, figure, L);
  drop_new_figure(game, figure, L);
  ck_assert_int_eq(figure->id, L);

  signal = DOWN_KEY;
  update_current_state(get_signal(signal), game, figure);
  signal = DOWN_KEY;
  update_current_state(get_signal(signal), game, figure);
  signal = SPACE;
  update_current_state(get_signal(signal), game, figure);
  signal = SPACE;
  update_current_state(get_signal(signal), game, figure);
  for (int i = 0; i < 3; i++) {
    signal = RIGHT_KEY;
    update_current_state(get_signal(signal), game, figure);
  }
  for (int i = 0; i < 19; i++) {
    signal = DOWN_KEY;
    update_current_state(get_signal(signal), game, figure);
  }
  // for (int i = 0; i < 19; i++) {
  //   for (int j = 0; j < 9; j++) {
  //     printf("%d ", game->field[i][j]);
  //   }
  //   putchar('\n');
  // }

  ck_assert_int_eq(game->score, 100);

  for (int i = 0; i < 200; i++) {
    signal = DOWN_KEY;
    update_current_state(get_signal(signal), game, figure);
  }

  ck_assert_int_eq(game->state, OVER);

  signal = ENTER_KEY;
  update_current_state(get_signal(signal), game, figure);
  ck_assert_int_eq(game->state, PLAYING);

  ck_assert_int_eq(game->high_score, 100);

  signal = 'q';
  update_current_state(get_signal(signal), game, figure);
  ck_assert_int_eq(game->state, STOPPED);

  signal = 'y';
  update_current_state(get_signal(signal), game, figure);
  ck_assert_int_eq(game->state, TERMINATED);

  save_high_score(game);
  destroy_game(game);
  destroy_figure(figure);
  free_figures(figures);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, tetris_logic);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
