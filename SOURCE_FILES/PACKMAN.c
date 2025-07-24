/*
 * 
 *
 *  Created on: Jul 24, 2025
 *      
 */


#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MSYSTICK_interface.h"
#include "TFT_interface.h"
#include "PACKMAN.h"
#include<stdlib.h>
/*
 *   <--------------12-------------->
 * 					|
 * 					|
 * 					|14
 */
/**
 * 1 - start position
 * 0 - empty
 * 2 - wall
 */
static u8 PACMAN_Map[168]={

		1,0,0,0,0,2,2,2,2,0,2,0,//6
		0,0,0,2,0,0,2,0,0,0,0,0,//10
		0,0,2,2,0,0,2,0,0,2,2,2,//6
		0,0,0,0,0,0,0,0,0,0,0,0,//12
		2,2,2,0,2,0,0,0,0,0,2,0,//7
		0,0,0,0,2,0,2,2,2,0,2,0,//7
		0,2,0,0,0,0,2,2,2,0,0,0,//8
		0,2,0,2,2,0,0,0,0,0,2,2,//7
		0,2,0,0,2,0,2,0,0,0,0,0,//9
		0,0,0,0,0,0,2,0,2,0,0,0,//10
		2,0,0,0,0,0,0,0,2,0,0,2,//9
		2,0,2,2,2,0,2,2,2,2,0,2,//3
		0,0,0,0,2,0,0,0,2,0,0,2,//9
		2,2,0,0,2,0,2,0,0,0,0,0 //8


};


static u16 PACKMAN_ARRAY[64]={

		TFT_BLACK,TFT_BLACK,TFT_BLACK,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_BLACK,TFT_BLACK,
		TFT_BLACK,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_BLACK,TFT_BLACK,
		TFT_BLACK,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_BLACK,
		TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_BLACK,TFT_YELLOW,TFT_ORANGE,
		TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_BLACK,
		TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_BLACK,TFT_BLACK,TFT_BLACK,
		TFT_BLACK,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_BLACK,
		TFT_BLACK,TFT_BLACK,TFT_YELLOW,TFT_YELLOW,TFT_YELLOW,TFT_BLACK,TFT_BLACK,TFT_BLACK

};
static u16 GHOST_ARRAY[64]={
		//change the colors
		TFT_BLACK,TFT_BLACK,TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_BLACK,TFT_BLACK,
		TFT_BLACK,TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_BLACK,
		TFT_RED,TFT_RED,TFT_LIGHT_BLUE,TFT_RED,TFT_RED,TFT_LIGHT_BLUE,TFT_RED,TFT_RED,
		TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_RED,
		TFT_RED,TFT_RED,TFT_BLACK,TFT_BLACK,TFT_BLACK,TFT_BLACK,TFT_RED,TFT_RED,
		TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_RED,TFT_RED,
		TFT_BLACK,TFT_RED,TFT_BLACK,TFT_RED,TFT_RED,TFT_BLACK,TFT_RED,TFT_BLACK,
		TFT_BLACK,TFT_RED,TFT_BLACK,TFT_RED,TFT_RED,TFT_BLACK,TFT_RED,TFT_BLACK

};
/*********************************PackMan state vaiables ***********************************************/
/**
 *1-  PackMan_y , PackMan_x are the current Postion of Packman
 *2-  X_COORDINATE_PACKMAN , Y_COORDINATE_PACKMAN current position of the PACKMAN
 *3-  needed_horizontal ,needed_vertical diraction needed for reach packman
 /******************************************************************************************/
static u8 PackMan_y=0;
static u8 PackMan_x=0;
//static u8 Packman_array_position=12*8+3;
static u8 Packman_array_position=0;
static u8 food_count=0;

static s8 X_COORDINATE_PACKMAN=0;
static s8 Y_COORDINATE_PACKMAN=0;


///////////////////////////////////////
//-----Ghosts-Variables-------------//
/*********************************ghost state vaiables ***********************************************/
/**
 *1-  Ghost_y , Ghost_x   Pixel Postion
 *2-  X_COORDINATE_GHOST , Y_COORDINATE_GHOST current position of the ghost
 *3-  direction   Direction movement
 *4-  prev_dir the last direction each ghost moved in
 *5-  previous_dir_state ,current_state used to store movement possipilites to avoid the walls
 *6-  random_choice1 add some random buses
 /******************************************************************************************/

static s8 needed_vertical[4];
static s8 needed_horizontal[4];

static s8 X_COORDINATE_GHOST[4];
static s8 Y_COORDINATE_GHOST[4];
static u8 Ghost_x[4];
static u8 Ghost_y[4];
static u8 random_choice1[4]={0};
static s16 previous_dir_state[4][4];
static s16 current_state[4][4];
static s8 prev_dir[4];

static s8 ghost_update_shape[3]={0};
static u8 time_to_draw=0;
s8 direction[4];
static u8 restart=0;
static s8 targets_x[3]={0,9,2};
static s8 targets_y[3]={0,0,12};
static u8 game_stage=0;

static u8 random_location[3]={2,2,2};
////////////////////////////////////

/**
 * 1  -> right
 * -1 -> left
 * 2  -> down
 * -2 -> up
 */
s8 PACKMAN_WhereGhostGo(u8 Ghost_ID,s8 packman_x_coordinate,s8 packman_y_coordinate,s8 ghost_x_coordinate,s8 ghost_y_coordinate)
{
	current_state[Ghost_ID][0]=PACKMAN_Check_Move((ghost_x_coordinate+12*ghost_y_coordinate),PACKMAN_MOVE_RIGHT);
	current_state[Ghost_ID][1]=PACKMAN_Check_Move((ghost_x_coordinate+12*ghost_y_coordinate),PACKMAN_MOVE_LEFT);
	current_state[Ghost_ID][2]=PACKMAN_Check_Move((ghost_x_coordinate+12*ghost_y_coordinate),PACKMAN_MOVE_UP);
	current_state[Ghost_ID][3]=PACKMAN_Check_Move((ghost_x_coordinate+12*ghost_y_coordinate),PACKMAN_MOVE_DOWN);

	// convert the 2d position into 1d position array
	u8 GHOST_ARRAY_POS=(ghost_x_coordinate+12*ghost_y_coordinate);

	u8 on_change=0;
	for(u8 i=0;i<4;i++)
	{
		on_change+=((current_state[Ghost_ID][i]==-1 && previous_dir_state[Ghost_ID][i]==-1) ||(current_state[Ghost_ID][i]!=-1 && previous_dir_state[Ghost_ID][i]!=-1));
	}

	for(u8 i=0;i<4;i++)
	{
		previous_dir_state[Ghost_ID][i]=current_state[Ghost_ID][i];
	}

	if(ghost_y_coordinate!=packman_y_coordinate)
	{
		u8 absolute_y;
		if(ghost_y_coordinate>packman_y_coordinate)
		{
			absolute_y = ghost_y_coordinate-packman_y_coordinate;
		}
		else
		{
			absolute_y=packman_y_coordinate-ghost_y_coordinate;
		}

		needed_vertical[Ghost_ID]=(2*(packman_y_coordinate-ghost_y_coordinate))/(absolute_y);
	}
	else
	{
		needed_vertical[Ghost_ID]=0;
	}

	if(packman_x_coordinate!=ghost_x_coordinate)
	{
		u8 absolute_x;
		if(ghost_x_coordinate>packman_x_coordinate)
		{
			absolute_x=ghost_x_coordinate-packman_x_coordinate;
		}
		else
		{
			absolute_x=packman_x_coordinate-ghost_x_coordinate;
		}

		needed_horizontal[Ghost_ID]=((packman_x_coordinate-ghost_x_coordinate))/(absolute_x);
	}
	else
	{
		needed_horizontal[Ghost_ID]=0;
	}
	if(needed_vertical[Ghost_ID]==0 && needed_horizontal[Ghost_ID]==0)
	{
		return 0;
	}
	else if(on_change==((4==4)*4) && (PACKMAN_Check_Move(GHOST_ARRAY_POS,prev_dir[Ghost_ID])!=-1))
	{
		return prev_dir[Ghost_ID];
		/*
		if(prev_dir==2 || prev_dir==-2)
		{
			Y_COORDINATE_PACKMAN+=prev_dir/2;

		}
		else
		{
			X_COORDINATE_PACKMAN+=prev_dir;

		}-------------COPY THIS PLEASE--------------*/
	}
	else
	{
		if(needed_vertical[Ghost_ID]==0 && needed_horizontal[Ghost_ID]!=0)
		{

			s16 new_position=PACKMAN_Check_Move(GHOST_ARRAY_POS,needed_horizontal[Ghost_ID]);
			if(new_position!=-1 && prev_dir[Ghost_ID]!=(-1*needed_horizontal[Ghost_ID]))
			{
				prev_dir[Ghost_ID]=needed_horizontal[Ghost_ID];

				return needed_horizontal[Ghost_ID];
			}
			else
			{
				if(PACKMAN_Check_Move(GHOST_ARRAY_POS,PACKMAN_MOVE_UP)!=-1)
				{
					prev_dir[Ghost_ID]=PACKMAN_MOVE_UP;
					return PACKMAN_MOVE_UP;
				}
				else if(PACKMAN_Check_Move(GHOST_ARRAY_POS,PACKMAN_MOVE_DOWN)!=-1)
				{
					prev_dir[Ghost_ID]=PACKMAN_MOVE_DOWN;
					return PACKMAN_MOVE_DOWN;
				}
				else
				{
					prev_dir[Ghost_ID]=-1*needed_horizontal[Ghost_ID];
					return (-1*needed_horizontal[Ghost_ID]);
				}

			}

		}
		else if(needed_vertical[Ghost_ID]!=0 && needed_horizontal[Ghost_ID]==0)
		{
			s16 new_position=PACKMAN_Check_Move(GHOST_ARRAY_POS,needed_vertical[Ghost_ID]);
			if(new_position!=-1 && prev_dir[Ghost_ID]!=(-1*needed_vertical[Ghost_ID]))
			{
				prev_dir[Ghost_ID]=needed_vertical[Ghost_ID];
				return needed_vertical[Ghost_ID];
			}
			else
			{
				if(PACKMAN_Check_Move(GHOST_ARRAY_POS,PACKMAN_MOVE_LEFT)!=-1)
				{

					prev_dir[Ghost_ID]=PACKMAN_MOVE_LEFT;
					return PACKMAN_MOVE_LEFT;
				}
				else if(PACKMAN_Check_Move(GHOST_ARRAY_POS,PACKMAN_MOVE_RIGHT)!=-1)
				{

					prev_dir[Ghost_ID]=PACKMAN_MOVE_RIGHT;
					return PACKMAN_MOVE_RIGHT;
				}

				else
				{

					prev_dir[Ghost_ID]=-1*needed_vertical[Ghost_ID];
					return (-1*needed_vertical[Ghost_ID]);
				}

			}

		}
		else if(needed_vertical[Ghost_ID]!=0 && needed_horizontal[Ghost_ID]!=0)
		{
			s16 new_position=PACKMAN_Check_Move(GHOST_ARRAY_POS,needed_vertical[Ghost_ID]);
			s16 new_position2=PACKMAN_Check_Move(GHOST_ARRAY_POS,needed_horizontal[Ghost_ID]);
			s16 new_position3=PACKMAN_Check_Move(GHOST_ARRAY_POS,prev_dir[Ghost_ID]);
			//
			s16 new_position4=PACKMAN_Check_Move(GHOST_ARRAY_POS,needed_horizontal[Ghost_ID]*-1);
			s16 new_position5=PACKMAN_Check_Move(GHOST_ARRAY_POS,needed_vertical[Ghost_ID]*-1);
			s16 new_position6=PACKMAN_Check_Move(GHOST_ARRAY_POS,prev_dir[Ghost_ID]*-1);
			if(new_position!=-1 && prev_dir[Ghost_ID]!=(-1*needed_vertical[Ghost_ID]))
			{

				prev_dir[Ghost_ID]=needed_vertical[Ghost_ID];
				return needed_vertical[Ghost_ID];
			}
			else if(new_position2!=-1 && prev_dir[Ghost_ID]!=(-1*needed_horizontal[Ghost_ID]))
			{
				prev_dir[Ghost_ID]=needed_horizontal[Ghost_ID];
				return needed_horizontal[Ghost_ID];
			}
			else if(PACKMAN_Check_Move(GHOST_ARRAY_POS,prev_dir[Ghost_ID])!=-1)
			{

				return prev_dir[Ghost_ID];
			}
			else
			{
				if(new_position4!=-1 && new_position5!=-1)
				{
					random_choice1[Ghost_ID]^=1;
					if(random_choice1[Ghost_ID]==1)
					{

						prev_dir[Ghost_ID]=-1*needed_horizontal[Ghost_ID];
						return (-1*needed_horizontal[Ghost_ID]);
					}
					else
					{

						prev_dir[Ghost_ID]=-1*needed_vertical[Ghost_ID];
						return (-1*needed_vertical[Ghost_ID]);
					}
				}
				else
				{
					if(new_position4!=-1)
					{

						prev_dir[Ghost_ID]=-1*needed_horizontal[Ghost_ID];
						return -1*needed_horizontal[Ghost_ID];
					}
					else if(new_position5!=-1)
					{

						prev_dir[Ghost_ID]=-1*needed_vertical[Ghost_ID];
						return -1*needed_vertical[Ghost_ID];
					}
					else
					{
						prev_dir[Ghost_ID]=prev_dir[Ghost_ID]*-1;
						return prev_dir[Ghost_ID];

					}

				}
			}

		}
		else if(needed_vertical[Ghost_ID]==0 && needed_horizontal[Ghost_ID]==0)
		{
			return 0;
		}
	}
	//write here

}
void PACKMAN_DrawGhost(u8 Ghost_id,u8 x,u8 y)
{
	u8 MADACTL=1<<7 | 1<<6;
	TFT_SendCommand(0x36);//MADCTL
	TFT_SendData(MADACTL);
	TFT_SendCommand(0x2A);//x
	TFT_SendData(0);
	TFT_SendData(x+1);
	TFT_SendData(0);
	TFT_SendData(x+8);
	///////////
	TFT_SendCommand(0x2B);//y
	TFT_SendData(0);
	TFT_SendData(y+1);
	TFT_SendData(0);
	TFT_SendData(y+8);
	TFT_SendCommand(0x2c);
	for(u8 i=0;i<64;i++)
	{
		if(GHOST_ARRAY[i]==TFT_RED && Ghost_id==0)
		{
			TFT_SendColor(TFT_RED);
		}
		else if(GHOST_ARRAY[i]==TFT_RED && Ghost_id==1)
		{
			TFT_SendColor(TFT_GREEN);

		}
		else if(GHOST_ARRAY[i]==TFT_RED && Ghost_id==2)
		{
			TFT_SendColor(TFT_YELLOW);

		}
		else if(GHOST_ARRAY[i]==TFT_RED && Ghost_id==3)
		{
			TFT_SendColor(TFT_DARK_BLUE);

		}
		else
		{
			TFT_SendColor(GHOST_ARRAY[i]);
		}
	}
}
void PACKMAN_DrawPackMan(u8 x,u8 y,s8 direction)
{
	u8 MADACTL=1<<7 | 1<<6;
	TFT_SendCommand(0x36);//MADCTL
	if(direction==PACKMAN_RIGHT)
	{
		TFT_SendData(1<<7 | 1<<6);
		TFT_SendCommand(0x2A);//x
		TFT_SendData(0);
		TFT_SendData(x+1);
		TFT_SendData(0);
		TFT_SendData(x+8);
		///////////
		TFT_SendCommand(0x2B);//y
		TFT_SendData(0);
		TFT_SendData(y+1);
		TFT_SendData(0);
		TFT_SendData(y+8);
		TFT_SendCommand(0x2c);
	}
	else if(direction==PACKMAN_LEFT)
	{
		TFT_SendData(1<<7 | 0<<6);
		TFT_SendCommand(0x2A);//x
		TFT_SendData(0);
		TFT_SendData(127-(x+8));
		TFT_SendData(0);
		TFT_SendData(127-(x+1));
		///////////
		TFT_SendCommand(0x2B);//y
		TFT_SendData(0);
		TFT_SendData(y+1);
		TFT_SendData(0);
		TFT_SendData(y+8);
		TFT_SendCommand(0x2c);

	}
	else if(direction==PACKMAN_UP)
	{
		TFT_SendData(0<<7 | 1<<6 | 1<<5);
		TFT_SendCommand(0x2A);//x
		TFT_SendData(0);
		TFT_SendData(159-(y+8));
		TFT_SendData(0);
		TFT_SendData(159-(y+1));
		///////////
		TFT_SendCommand(0x2B);//y

		TFT_SendData(0);
		TFT_SendData(x+1);
		TFT_SendData(0);
		TFT_SendData(x+8);
		TFT_SendCommand(0x2c);

	}
	else if(direction==PACKMAN_DOWN)
	{
		TFT_SendData(1<<7 | 1<<6 | 1<<5);
		TFT_SendCommand(0x2A);//x
		TFT_SendData(0);
		TFT_SendData((y+1));
		TFT_SendData(0);
		TFT_SendData((y+8));
		///////////
		TFT_SendCommand(0x2B);//y

		TFT_SendData(0);
		TFT_SendData(x+1);
		TFT_SendData(0);
		TFT_SendData(x+8);
		TFT_SendCommand(0x2c);

	}

	for(u8 i=0;i<64;i++)
	{
		TFT_SendColor(PACKMAN_ARRAY[i]);

	}
	TFT_SendCommand(0x36);//MADCTL
	TFT_SendData(MADACTL);

}
// 12 is the Width * 14 is the height of the grid = 168 cell

s16 PACKMAN_Check_Move(u8 array_position,s8 direction)
{
	u8 arr_pos=array_position;
	u8 right_check=(arr_pos%12)+1;  // if right_check == 12 then the cant move right
	u8 left_check=(arr_pos%12);     // if left_check == 0 then the cant move left
	u8 down_check=(arr_pos+12);     // to move down  you should position +12
	s16 up_check=((s16)arr_pos-12); // to move up  you should position -12

	if(direction==PACKMAN_MOVE_UP)
	{
		arr_pos=(arr_pos-12)%168;
       /**
        * up_check>=0 , Make sure it wont go outside the top of the grid
        * PACMAN_Map[arr_pos]!=2 , Make sure it wont go to the wall
        */
		if(up_check>=0 && PACMAN_Map[arr_pos]!=2)
		{
			return (array_position-12);
		}
	}
	else if(direction==PACKMAN_MOVE_DOWN)
	{
		arr_pos=(arr_pos+12)%168;
		/**
		 * down_check<=167 , still inside the map
		 */
		if(down_check<=167 && (PACMAN_Map[arr_pos]!=2))
		{
			return (array_position+12);
		}

	}
	else if(direction==PACKMAN_MOVE_RIGHT)
	{
		arr_pos=(arr_pos+1)%168;
		if( right_check!=12 && PACMAN_Map[arr_pos]!=2 )
		{
			return (array_position+1);

		}
	}
	else if(direction==PACKMAN_MOVE_LEFT)
	{
		arr_pos=(arr_pos-1)%168;
		if(left_check!=0 && PACMAN_Map[arr_pos]!=2)
		{
			return (array_position-1);


		}
	}
	return -1;

}
u8 PACKMAN_Ghost_Move(u8 Ghost_id,s8 move_direction)
{
	ghost_update_shape[Ghost_id]++;
	if(ghost_update_shape[Ghost_id]==4)
	{
		ghost_update_shape[Ghost_id]=0;
		return 0;
	}
	else
	{
		if(move_direction==0)
		{
			return 2;
		}

		TFT_DrawRectangle(Ghost_x[Ghost_id]+1,Ghost_y[Ghost_id]+1,Ghost_x[Ghost_id]+8,Ghost_y[Ghost_id]+8,TFT_BLACK);
		if(PACMAN_Map[X_COORDINATE_GHOST[Ghost_id]+(12*Y_COORDINATE_GHOST[Ghost_id])]==0)
		{
			TFT_DrawRectangle((X_COORDINATE_GHOST[Ghost_id])*10+4,(Y_COORDINATE_GHOST[Ghost_id])*10+4,((X_COORDINATE_GHOST[Ghost_id])*10)+6,((Y_COORDINATE_GHOST[Ghost_id])*10)+6,0xffee);//bright yellow
		}

		if(move_direction==PACKMAN_MOVE_RIGHT)
		{
			if(ghost_update_shape[Ghost_id]==1)
				Ghost_x[Ghost_id]+=1;

			Ghost_x[Ghost_id]+=3;
			PACKMAN_DrawGhost(Ghost_id,Ghost_x[Ghost_id],Ghost_y[Ghost_id]);
		}
		else if(move_direction==PACKMAN_MOVE_LEFT)
		{
			if(ghost_update_shape[Ghost_id]==1)
				Ghost_x[Ghost_id]-=1;
			Ghost_x[Ghost_id]-=3;
			PACKMAN_DrawGhost(Ghost_id,Ghost_x[Ghost_id],Ghost_y[Ghost_id]);

		}
		else if(move_direction==PACKMAN_MOVE_UP)
		{
			if(ghost_update_shape[Ghost_id]==1)
				Ghost_y[Ghost_id]-=1;
			Ghost_y[Ghost_id]-=3;
			PACKMAN_DrawGhost(Ghost_id,Ghost_x[Ghost_id],Ghost_y[Ghost_id]);

		}
		else if(move_direction==PACKMAN_MOVE_DOWN)
		{
			if(ghost_update_shape[Ghost_id]==1)
				Ghost_y[Ghost_id]+=1;
			Ghost_y[Ghost_id]+=3;
			PACKMAN_DrawGhost(Ghost_id,Ghost_x[Ghost_id],Ghost_y[Ghost_id]);

		}

		return 1;
	}

}
void PACKMAN_Move(s8 move_direction)
{

	for(u8 i=0;i<3;i++)
	{
		TFT_DrawRectangle(PackMan_x+1,PackMan_y+1,PackMan_x+9,PackMan_y+9,TFT_BLACK);
		if(move_direction==PACKMAN_MOVE_RIGHT)
		{
			if(i==0)
				PackMan_x+=1;

			PackMan_x+=3;
			PACKMAN_DrawPackMan(PackMan_x,PackMan_y,PACKMAN_RIGHT);

		}
		else if(move_direction==PACKMAN_MOVE_LEFT)
		{
			if(i==0)
				PackMan_x-=1;
			PackMan_x-=3;
			PACKMAN_DrawPackMan(PackMan_x,PackMan_y,PACKMAN_LEFT);

		}
		else if(move_direction==PACKMAN_MOVE_UP)
		{
			if(i==0)
				PackMan_y-=1;
			PackMan_y-=3;
			PACKMAN_DrawPackMan(PackMan_x,PackMan_y,PACKMAN_UP);

		}
		else if(move_direction==PACKMAN_MOVE_DOWN)
		{
			if(i==0)
				PackMan_y+=1;
			PackMan_y+=3;
			PACKMAN_DrawPackMan(PackMan_x,PackMan_y,PACKMAN_DOWN);

		}
		for(u8 k=0;k<4;k++)
		{
			MSYSYTICK_voidDelayms(23);
			PACKMAN_Update_Ghosts();
		}
		if(PACKMAN_Check_Collision()==1)
		{
			PACKMAN_RESTART_NO_LOSS();
			return;
		}

	}

}






void PACKMAN_DrawBackGround(u8 Game_Level)
{
	if(Game_Level==1)
	{
		TFT_DrawRectangle(0,0,127,159,TFT_BROWN);
		TFT_DrawRectangle(0,0,119,139,TFT_VIOLET);
		TFT_DrawRectangle(1,1,118,138,TFT_BLACK);
		for(u8 j=0;j<168;j++)
		{
			if(PACMAN_Map[j]==2)
			{
				TFT_DrawRectangle((j%12)*10,(j/12)*10,((j%12)*10)+9,((j/12)*10)+9,TFT_RED);
				TFT_DrawRectangle((j%12)*10 +1,(j/12)*10 +1,((j%12)*10)+9 -1,((j/12)*10)+9 -1,TFT_BLACK);

			}
			else
			{
				TFT_DrawRectangle((j%12)*10+4,(j/12)*10+4,((j%12)*10)+6,((j/12)*10)+6,0xfd20);

			}
		}
		TFT_DrawRectangle((5%12)*10 +1,(5/12)*10 +1,((8%12)*10)+9 -1,((8/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((6%12)*10 +1,(6/12)*10 +1,((30%12)*10)+9 -1,((30/12)*10)+9 -1,TFT_BLACK);

		TFT_DrawRectangle((15%12)*10 +1,(15/12)*10 +1,((27%12)*10)+9 -1,((27/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((26%12)*10 +1,(26/12)*10 +1,((27%12)*10)+9 -1,((27/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((33%12)*10 +1,(33/12)*10 +1,((35%12)*10)+9 -1,((35/12)*10)+9 -1,TFT_BLACK);

		TFT_DrawRectangle((48%12)*10 +1,(48/12)*10 +1,((50%12)*10)+9 -1,((50/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((52%12)*10 +1,(52/12)*10 +1,((64%12)*10)+9 -1,((64/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((58%12)*10 +1,(58/12)*10 +1,((70%12)*10)+9 -1,((70/12)*10)+9 -1,TFT_BLACK);

		TFT_DrawRectangle((66%12)*10 +1,(66/12)*10 +1,((80%12)*10)+9 -1,((80/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((73%12)*10 +1,(73/12)*10 +1,((97%12)*10)+9 -1,((97/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((87%12)*10 +1,(87/12)*10 +1,((88%12)*10)+9 -1,((88/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((88%12)*10 +1,(88/12)*10 +1,((100%12)*10)+9 -1,((100/12)*10)+9 -1,TFT_BLACK);

		TFT_DrawRectangle((120%12)*10 +1,(120/12)*10 +1,((132%12)*10)+9 -1,((132/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((156%12)*10 +1,(156/12)*10 +1,((157%12)*10)+9 -1,((157/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((134%12)*10 +1,(134/12)*10 +1,((136%12)*10)+9 -1,((136/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((136%12)*10 +1,(136/12)*10 +1,((160%12)*10)+9 -1,((160/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((102%12)*10 +1,(102/12)*10 +1,((114%12)*10)+9 -1,((114/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((94%12)*10 +1,(94/12)*10 +1,((95%12)*10)+9 -1,((95/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((116%12)*10 +1,(116/12)*10 +1,((152%12)*10)+9 -1,((152/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((138%12)*10 +1,(138/12)*10 +1,((141%12)*10)+9 -1,((141/12)*10)+9 -1,TFT_BLACK);
		TFT_DrawRectangle((131%12)*10 +1,(131/12)*10 +1,((155%12)*10)+9 -1,((155/12)*10)+9 -1,TFT_BLACK);



	}

}
void PACKMAN_DrawWINLOSEScreen(u8 win)
{


}

u8 PACKMAN_Check_Collision(void)
{
	u8 check=0;
	for(u8 h=0;h<3;h++)
	{
		check+=(((abs(Ghost_x[h]-PackMan_x))<10)&&((abs(Ghost_y[h]-PackMan_y))<10));
	}
	if(check>=1)
	{

		return 1;
	}
	return 0;
}
void PACKMAN_RESTART_NO_LOSS()
{
	MSYSYTICK_voidDelayms(2000);
	for(u8 i=0;i<4;i++)
	{
		for(u8 j=0;j<4;j++)
		{
			previous_dir_state[i][j]=-1;
		}
	}
	for(u8 j=0;j<168;j++)
	{
		if(PACMAN_Map[j]!=2)
		{
			TFT_DrawRectangle((j%12)*10,(j/12)*10,((j%12)*10)+9,((j/12)*10)+9,TFT_BLACK);

		}
		if(PACMAN_Map[j]==0)
		{
			TFT_DrawRectangle((j%12)*10+4,(j/12)*10+4,((j%12)*10)+6,((j/12)*10)+6,0xfd20);
		}

	}
	PACKMAN_DrawPackMan(0,0,PACKMAN_RIGHT);


	PackMan_x=0;
	PackMan_y=0;
	Packman_array_position=0;

	X_COORDINATE_PACKMAN=0;
	Y_COORDINATE_PACKMAN=0;



	Ghost_x[PACKMAN_GHOST_1]=110;
	Ghost_y[PACKMAN_GHOST_1]=120;
	prev_dir[PACKMAN_GHOST_1]=PACKMAN_MOVE_LEFT;
	X_COORDINATE_GHOST[PACKMAN_GHOST_1]=11;
	Y_COORDINATE_GHOST[PACKMAN_GHOST_1]=12;


	Ghost_x[PACKMAN_GHOST_2]=110;
	Ghost_y[PACKMAN_GHOST_2]=0;
	prev_dir[PACKMAN_GHOST_2]=PACKMAN_MOVE_DOWN;
	X_COORDINATE_GHOST[PACKMAN_GHOST_2]=11;
	Y_COORDINATE_GHOST[PACKMAN_GHOST_2]=0;


	Ghost_x[PACKMAN_GHOST_3]=0;
	Ghost_y[PACKMAN_GHOST_3]=120;
	prev_dir[PACKMAN_GHOST_3]=PACKMAN_MOVE_RIGHT;
	X_COORDINATE_GHOST[PACKMAN_GHOST_3]=0;
	Y_COORDINATE_GHOST[PACKMAN_GHOST_3]=12;


	targets_x[1]=9;
	targets_x[2]=2;
	targets_y[1]=0;
	targets_y[2]=12;
	direction[0]=PACKMAN_WhereGhostGo(PACKMAN_GHOST_1,X_COORDINATE_PACKMAN,Y_COORDINATE_PACKMAN,X_COORDINATE_GHOST[0],Y_COORDINATE_GHOST[0]);
	direction[1]=PACKMAN_WhereGhostGo(PACKMAN_GHOST_2,X_COORDINATE_PACKMAN+9,Y_COORDINATE_PACKMAN+0,X_COORDINATE_GHOST[1],Y_COORDINATE_GHOST[1]);
	direction[2]=PACKMAN_WhereGhostGo(PACKMAN_GHOST_3,X_COORDINATE_PACKMAN+2,Y_COORDINATE_PACKMAN+12,X_COORDINATE_GHOST[2],Y_COORDINATE_GHOST[2]);


	for(u8 k=0;k<3;k++)
	{
		ghost_update_shape[k]=0;
	}
	time_to_draw=0;
	restart=1;

}
void PACKMAN_Update_Ghosts(void)
{
	time_to_draw++;
	if(time_to_draw==10)
	{
		time_to_draw=0;
		u8 should_not_change_dir=PACKMAN_Ghost_Move(PACKMAN_GHOST_1,direction[0]);
		PACKMAN_Ghost_Move(PACKMAN_GHOST_2,direction[1]);
		PACKMAN_Ghost_Move(PACKMAN_GHOST_3,direction[2]);
		if(should_not_change_dir==0)
		{
			for(u8 u=0;u<3;u++)
			{
				if(direction[u]==2 || direction[u]==-2)
				{
					Y_COORDINATE_GHOST[u]+=direction[u]/2;

				}
				else if(direction[u]==1 || direction[u]==-1)
				{
					X_COORDINATE_GHOST[u]+=direction[u];

				}

			}
			///
			targets_x[0]=X_COORDINATE_PACKMAN;
			targets_y[0]=Y_COORDINATE_PACKMAN;
			if(game_stage==1)
			{
				targets_x[1]=X_COORDINATE_PACKMAN;
				targets_y[1]=Y_COORDINATE_PACKMAN;
			}
			else if(game_stage==2)
			{
				targets_x[1]=X_COORDINATE_PACKMAN;
				targets_y[1]=Y_COORDINATE_PACKMAN;
				targets_x[2]=X_COORDINATE_PACKMAN;
				targets_y[2]=Y_COORDINATE_PACKMAN;
			}

			///
			for(u8 l=0;l<3;l++)
			{

				direction[l]=PACKMAN_WhereGhostGo(l,targets_x[l],targets_y[l],X_COORDINATE_GHOST[l],Y_COORDINATE_GHOST[l]);
			}
			if(direction[1]==0)
			{

				targets_x[1]=X_COORDINATE_PACKMAN;
				targets_y[1]=(Y_COORDINATE_PACKMAN+random_location[1])%14;
				while(PACMAN_Map[targets_x[1]+12*targets_y[1]]==2)
				{
					targets_y[1]=(targets_y[1]+1)%14;
				}
				random_location[1]+=2;
				if(random_location[1]>10)
				{
					random_location[1]=2;
				}
				direction[1]=PACKMAN_WhereGhostGo(1,targets_x[1],targets_y[1],X_COORDINATE_GHOST[1],Y_COORDINATE_GHOST[1]);

			}
			if(direction[2]==0)
			{
				targets_x[2]=(X_COORDINATE_PACKMAN+random_location[2])%12;
				targets_y[2]=Y_COORDINATE_PACKMAN;
				while(PACMAN_Map[targets_x[2]+12*targets_y[2]]==2)
				{
					targets_x[2]=(targets_x[2]+1)%12;
				}
				random_location[2]+=2;
				if(random_location[2]>10)
				{
					random_location[2]=2;
				}

				direction[2]=PACKMAN_WhereGhostGo(2,targets_x[2],targets_y[2],X_COORDINATE_GHOST[2],Y_COORDINATE_GHOST[2]);

			}
			PACKMAN_Ghost_Move(PACKMAN_GHOST_1,direction[0]);
			PACKMAN_Ghost_Move(PACKMAN_GHOST_2,direction[1]);
			PACKMAN_Ghost_Move(PACKMAN_GHOST_3,direction[2]);

		}


	}

}

void PACKMAN_StartGame(void)
{
	PACKMAN_DrawBackGround(1);

	PACKMAN_RESTART_NO_LOSS();
	while(1)
	{
		u8 but1=1;
		u8 but2=1;
		u8 but3=1;
		u8 but4=1;
		MSYSYTICK_voidDelayms(22);
		PACKMAN_Update_Ghosts();
		u8 collide=PACKMAN_Check_Collision();
		if(collide==1)
		{
			PACKMAN_RESTART_NO_LOSS();
		}
		MGPIO_GetPinValue(PORT_B,PIN_0,&but1);
		MGPIO_GetPinValue(PORT_B,PIN_1,&but2);
		MGPIO_GetPinValue(PORT_B,PIN_6,&but3);
		MGPIO_GetPinValue(PORT_B,PIN_4,&but4);

		restart=0;
		if(food_count>=30)
		{
			game_stage=1;
		}
		if(food_count>=70)
		{
			game_stage=2;

		}
		if(food_count==111)
		{
			TFT_DrawRectangle(0,0,127,159,TFT_YELLOW);
			while(1);

		}
		// 1 -->
		//           <--- 2



		s16 new_position;

		if(but1==0 )
		{
			new_position=PACKMAN_Check_Move(Packman_array_position,PACKMAN_MOVE_UP);

			if(new_position!=-1)
			{
				Packman_array_position=(u8)new_position;
				PACKMAN_Move(PACKMAN_MOVE_UP);
				if(restart==1)
				{
					restart=0;
				}
				else
				{
					X_COORDINATE_PACKMAN=Packman_array_position%12;
					Y_COORDINATE_PACKMAN=Packman_array_position/12;
					if(PACMAN_Map[Packman_array_position]==0)
					{
						PACMAN_Map[Packman_array_position]=1;
						food_count++;
					}
				}
			}


		}
		else if(but2==0 )
		{
			new_position=PACKMAN_Check_Move(Packman_array_position,PACKMAN_MOVE_DOWN);

			if(new_position!=-1)
			{
				Packman_array_position=(u8)new_position;
				PACKMAN_Move(PACKMAN_MOVE_DOWN);
				if(restart==1)
				{
					restart=0;
				}
				else
				{
					X_COORDINATE_PACKMAN=Packman_array_position%12;
					Y_COORDINATE_PACKMAN=Packman_array_position/12;
					if(PACMAN_Map[Packman_array_position]==0)
					{
						PACMAN_Map[Packman_array_position]=1;
						food_count++;
					}
				}
			}

		}
		else if(but3==0 )
		{
			new_position=PACKMAN_Check_Move(Packman_array_position,PACKMAN_MOVE_RIGHT);

			if(new_position!=-1)
			{
				Packman_array_position=(u8)new_position;
				PACKMAN_Move(PACKMAN_MOVE_RIGHT);
				if(restart==1)
				{
					restart=0;
				}
				else
				{
					X_COORDINATE_PACKMAN=Packman_array_position%12;
					Y_COORDINATE_PACKMAN=Packman_array_position/12;
					if(PACMAN_Map[Packman_array_position]==0)
					{
						PACMAN_Map[Packman_array_position]=1;
						food_count++;
					}
				}
			}
		}
		else if(but4==0)
		{
			new_position=PACKMAN_Check_Move(Packman_array_position,PACKMAN_MOVE_LEFT);

			if(new_position!=-1)
			{
				Packman_array_position=(u8)new_position;
				PACKMAN_Move(PACKMAN_MOVE_LEFT);
				if(restart==1)
				{
					restart=0;
				}
				else
				{
					X_COORDINATE_PACKMAN=Packman_array_position%12;
					Y_COORDINATE_PACKMAN=Packman_array_position/12;
					if(PACMAN_Map[Packman_array_position]==0)
					{
						PACMAN_Map[Packman_array_position]=1;
						food_count++;
					}
				}
			}

		}

	}

}


