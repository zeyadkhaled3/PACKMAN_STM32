/*
 * PACKMAN.h
 *
 *  Created on: Jul 24, 2025
 */

#ifndef PACKMAN_H_
#define PACKMAN_H_



#define PACKMAN_RIGHT   1
#define PACKMAN_LEFT   -1
#define PACKMAN_UP      2
#define PACKMAN_DOWN   -2

#define PACKMAN_MOVE_RIGHT    1
#define PACKMAN_MOVE_LEFT    -1
#define PACKMAN_MOVE_UP      -2
#define PACKMAN_MOVE_DOWN     2

#define PACKMAN_GHOST_1       0
#define PACKMAN_GHOST_2       1
#define PACKMAN_GHOST_3       2
#define PACKMAN_GHOST_4       3

void PACKMAN_DrawPackMan(u8 x,u8 y,s8 direction);

void PACKMAN_DrawBackGround(u8 Game_Level);
void PACKMAN_DrawWINLOSEScreen(u8 win);
void PACKMAN_Move(s8 move_direction);
s16 PACKMAN_Check_Move(u8 array_position,s8 direction);
u8 PACKMAN_Ghost_Move(u8 Ghost_id,s8 move_direction);
void PACKMAN_Update_Ghosts(void);
u8 PACKMAN_Check_Collision(void);
void PACKMAN_RESTART_NO_LOSS();

void PACKMAN_StartGame(void);

#endif /* PACKMAN_H_ */
