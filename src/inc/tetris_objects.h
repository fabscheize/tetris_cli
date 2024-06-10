#ifndef TETRIS_OBJECTS_H_
#define TETRIS_OBJECTS_H_

typedef struct figure_s {
  int **shape;
  int id;
  int x;
  int y;
} figure_t;

typedef enum signals {
  NOTHING,
  START,
  PAUSE,
  QUIT,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  ACTION,
  YES,
  NO
} user_action_t;

typedef enum states {
  STARTED,
  PLAYING,
  PAUSED,
  STOPPED,
  TERMINATED,
  OVER,
} game_states_t;

typedef struct game_info_s {
  int ***shapes_list;
  int **field;
  int **next;
  int next_id;
  int score;
  int high_score;
  int level;
  int lines;
  int speed;
  int ticks_left;
  game_states_t state;
} game_info_t;

#endif  // TETRIS_OBJECTS_H_
