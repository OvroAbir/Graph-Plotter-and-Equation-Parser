
# define _CRT_SECURE_NO_WARNINGS
# define window_width 1280
# define window_height 720
# define keyboard_width 400
# define centre_coordinate_x 440 // global
# define centre_coordinate_y 360 // global
# define width_of_origin_line 2
# define width_of_Graph 860	// global
# define height_of_graph 700
# define border_coordinate_common 5
# define width_of_border_line 5
# define width_of_border 870	// global
# define heigth_of_border 710	// global
# define size_of_square 7.5
# define py 3.14159265
# include "iGraphics.h"
# define len_x_axis 450
# define len_y_axis 450
# define len_z_axis 450
# define PI 3.14159265
# define A 30*PI/180.0
# define B 30*PI/180.0
# define size_point 2
# define start_x 450
# define start_y 100
# define end_x 400
# define end_y 400
# define end_z 400
# define multiplier_z 100
# define arrow_len 25
# define axis_name_dis 5
int x=end_x,y=end_y,z;
double x_point, y_point;
double x_value, y_value;
char main_eqn[200];
char inputStr[100], lowerRange[50], upperRange[50]; //showInput[] = "z = ";
//int x = 300, y = 300, r = 20;
void n_strcpy(char from_str[],char to_str[],int pos1,int pos2);
double f3(char str[],double x, double y);
int Graph_2D=1,Graph_3D = 0;
int flag=0, state_in = 0, flag_graph = 0, flag_range_calc=0,flag_help = 0;
int flag_error=1,len_str_check_error;
double unit_x,unit_y,lim_1,lim_2,prev_point_x,prev_point_y;
double c=0;

int count_parenthesis_blance(char str[])
{
    int i,count1=0,count2=0;
    for(i=0;i<len_str_check_error;i++)
    {
        if(str[i]=='(')
            count1++;
        else if(str[i]==')')
            count1--;
        else if(str[i]=='[')
            count2++;
        else if(str[i]==']')
            count2--;
        if(count1<0 || count2<0)
            return 0;
    }
    if(count1==0 && count2==0)
        return 1;
    return 0;
}
void parenthesis_blance(char str[],int pos,int brac)// finds if the parenthesis are balanced
{
    if(flag_error==0)
        return;
	flag_error=count_parenthesis_blance(str);
    if(pos>=len_str_check_error)
        return;
    if(str[pos]=='(')
        parenthesis_blance(str,pos+1,1);
    else if(str[pos]=='[')
        parenthesis_blance(str,pos+1,2);
    if(brac==1)
    {
        if(str[pos]==')')
            return;
        else if(str[pos]==']')
        {
            flag_error=0;
            return;
        }
    }
    else if(brac==2)
    {
        if(str[pos]==']')
            return;
        else if(str[pos]==')')
        {
            flag_error=0;
            return;
        }
    }
}
void find_error(char str[])
{
    int len,i;
    len_str_check_error=strlen(str);
	len=len_str_check_error;
    parenthesis_blance(str,0,0);
    if(Graph_2D==1)//finds if there is y in input string of 2d eqn
    {
        for(i=3;i<len;i++)
            if(str[i]=='y' && Graph_3D==0)
			{
                flag_error=-1;
				return;
			}
    }
    for(i=1;i<len;i++)//finds if there are to consequtive signs
    {
        if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/' ||str[i]=='*' || str[i]=='^')
        {
			if(str[i-1]=='+' || str[i-1]=='-' || str[i-1]=='*' || str[i-1]=='/' ||str[i-1]=='*' || str[i-1]=='^'){
                flag_error=-2;
				return;
			}
        }
    }
	if(lim_1>=lim_2){
        flag_error=-3;
		return;
	}
    for(i=0;i<len;i++)// finds wrong with the . character
    {
        if(str[i]=='.')
        {
			if(!((str[i-1]>='0' && str[i-1]<='9') || str[i-1]=='x' || str[i-1]=='y')){
                flag_error=-4;
				return;
			}
            if(!((str[i+1]>='0' && str[i+1]<='9') || str[i+1]=='x' || str[i+1]=='y'))
			{
                flag_error=-4;
				return;
			}
        }
    }
	if(str[0]=='+' || str[0]=='*' && str[0]=='/' || str[0]=='^' || str[len-1]=='+' || str[len-1]=='-' || str[len-1]=='*' && str[len-1]=='/' || str[len-1]=='^'){ //finds if there is any sign in first or last place
        flag_error=-5;
		return;
	}
  /*  for(i=3;i<len;i++)
    {
        if(str[i]=='x' || (str[i]>='0' && str[i]<='9') || str[i]=='y' || str[i]=='s' || str[i]=='c' || str[i]=='t' || str[i]=='l' || str[i]=='e' )//if the input is xy or xsin(x) or 6x format.
        {
            if(str[i-1]!='+' &&str[i-1]!='-' &&str[i-1]!='*' &&str[i-1]!='/' &&str[i-1]!='^' && str[i-1]!='(' && str[i-1]!=')' && str[i-1]!=' ')
			{
                flag_error=-6;
				return;
			}
        }
    }
	*/
}
void draw_graphPaperAndKeyboard()
{
	int i, j;
	double array1x[] = {10, 26, 26},    array1y[] = {360, 352, 368};
	double array2x[] = {870, 854, 854}, array2y[] = {360, 352, 368};
	double array3x[] = {440, 432, 448}, array3y[] = {710, 694, 694};
	double array4x[] = {440, 432, 448}, array4y[] = {10, 26, 26};
	//flag=1; //change
	// Partition
	iSetColor(20, 50, 100);
	for (i = 0; i <= 9; i ++)
	{
		iLine(window_width - keyboard_width + i, 0, window_width - keyboard_width + i, window_height);
	}
	// Border
	for (i = 0; i <= width_of_border_line; i ++)
	{
		iRectangle(border_coordinate_common + i, border_coordinate_common + i, width_of_border - 2 * i, heigth_of_border - 2 * i);
	}
	// Background
	iSetColor(255, 255, 255);
	iFilledRectangle(border_coordinate_common + width_of_border_line, border_coordinate_common + width_of_border_line, width_of_Graph, height_of_graph);

	// Right secondary grid lines accross height
	for (i = 1; i < width_of_Graph / (size_of_square * 2); i ++)
	{
		if (i % 5)
		{
			iSetColor(128,255,128);
			iLine(centre_coordinate_x + size_of_square * i, border_coordinate_common + width_of_border_line, centre_coordinate_x + size_of_square * i, border_coordinate_common + width_of_border_line + height_of_graph);
		}
		//else iSetColor(0,128,64);
	}

	// Left secondary grid lines accross height
	for (i = 1; i < width_of_Graph / (size_of_square * 2); i ++)
	{
		if (i % 5)
		{
			iSetColor(128,255,128);
			iLine(centre_coordinate_x - size_of_square * i, border_coordinate_common + width_of_border_line, centre_coordinate_x - size_of_square * i, border_coordinate_common + width_of_border_line + height_of_graph);
		}
		//else iSetColor(0,128,64);
	}

	// High secondary grid lines accross width
	for (i = 1; i < height_of_graph / (size_of_square * 2); i ++)
	{
		if (i % 5)
		{
			iSetColor(128,255,128);
			iLine(border_coordinate_common + width_of_border_line, centre_coordinate_y + size_of_square * i, width_of_Graph + border_coordinate_common + width_of_border_line, centre_coordinate_y +  size_of_square * i);
		}
	}

	// Low secondary grid lines accross width
	for (i = 1; i < height_of_graph / (size_of_square * 2); i ++)
	{
		if (i % 5)
		{
			iSetColor(128,255,128);
			iLine(border_coordinate_common + width_of_border_line, centre_coordinate_y - size_of_square * i, width_of_Graph + border_coordinate_common + width_of_border_line, centre_coordinate_y -  size_of_square * i);
		}
	}

	// Right primary grid lines accross height
	for (i = 1; i < width_of_Graph / (size_of_square * 2); i ++)
	{
		if (!(i % 5))
		{
			iSetColor(0,128,64);
			iLine(centre_coordinate_x + size_of_square * i, border_coordinate_common + width_of_border_line, centre_coordinate_x + size_of_square * i, border_coordinate_common + width_of_border_line + height_of_graph);
		}
		//else iSetColor(0,128,64);
	}

	// Left primary grid lines accross height
	for (i = 1; i < width_of_Graph / (size_of_square * 2); i ++)
	{
		if (!(i % 5))
		{
			iSetColor(0,128,64);
			iLine(centre_coordinate_x - size_of_square * i, border_coordinate_common + width_of_border_line, centre_coordinate_x - size_of_square * i, border_coordinate_common + width_of_border_line + height_of_graph);
		}
		//else iSetColor(0,128,64);
	}

	// High primary grid lines accross width
	for (i = 1; i < height_of_graph / (size_of_square * 2); i ++)
	{
		if (!(i % 5))
		{
			iSetColor(0,128,64);
			iLine(border_coordinate_common + width_of_border_line, centre_coordinate_y + size_of_square * i, width_of_Graph + border_coordinate_common + width_of_border_line, centre_coordinate_y +  size_of_square * i);
		}
	}

	// Low primary grid lines accross width
	for (i = 1; i < height_of_graph / (size_of_square * 2); i ++)
	{
		if (!(i % 5))
		{
			iSetColor(0,128,64);
			iLine(border_coordinate_common + width_of_border_line, centre_coordinate_y - size_of_square * i, width_of_Graph + border_coordinate_common + width_of_border_line, centre_coordinate_y -  size_of_square * i);
		}
	}
	// Centre line
	iSetColor(0, 0, 174);
	//iFilledRectangle(border_coordinate_common + width_of_border_line, centre_coordinate_y + border_coordinate_common + width_of_border_line - width_of_origin_line / 2, width_of_Graph - 2 * (border_coordinate_common + width_of_border_line), width_of_origin_line);
	//iFilledRectangle(centre_coordinate_x - width_of_origin_line / 2, 0, width_of_origin_line, width_of_Graph);

	// Accross width
	for (i = -1; i <= 1; i++)
	{
		iLine(border_coordinate_common + width_of_border_line, centre_coordinate_y + i, width_of_Graph + border_coordinate_common + width_of_border_line, centre_coordinate_y + i);
	}

	// Accross height
	for (i = -1; i <= 1; i++)
	{
		iLine(centre_coordinate_x + i, border_coordinate_common + width_of_border_line, centre_coordinate_x + i, border_coordinate_common + width_of_border_line + height_of_graph);
	}
	// Arrows

	iFilledPolygon(array1x,array1y, 3);
	iFilledPolygon(array2x,array2y, 3);
	iFilledPolygon(array3x,array3y, 3);
	iFilledPolygon(array4x,array4y, 3);
		// NameAxes

	iText(855, 340, "X", GLUT_BITMAP_HELVETICA_18);
	iText(451, 340, "O", GLUT_BITMAP_HELVETICA_18);
	iText(20, 340, "X'", GLUT_BITMAP_HELVETICA_18);
	iText(451, 694, "Y", GLUT_BITMAP_HELVETICA_18);
	iText(451, 25, "Y'", GLUT_BITMAP_HELVETICA_18);


	// Background of Keyboard
	/*iSetColor(192, 192, 192);
	iFilledRectangle(890, 0, 390, 720);*/

	// Input Function Box
	iSetColor(255, 255, 255);
	iFilledRectangle(900, 610, 370, 100);

	// Limit Box
	iFilledRectangle(1000, 560, 110, 40);
	iFilledRectangle(1160, 560, 110, 40);
	iText(900, 575, "Lim: From", GLUT_BITMAP_HELVETICA_18);
	iText(1120, 575, "To", GLUT_BITMAP_HELVETICA_18);
	// Buttons
	/*iFilledRectangle(900, 530, 100, 40);
	iFilledRectangle(1035, 530, 100, 40);
	iFilledRectangle(1170, 530, 100, 40);*/
	for (i = 0; i < 3; i ++)
		iFilledRectangle(900 + 127 * i, 510, 115, 40);
	for (i = 0; i < 3; i ++)
	{
		iFilledRectangle(900 + 127 * i, 460, 115, 40);
	}
	for (i = 0; i < 5; i ++)
	{
	    
		iFilledRectangle(900 + 76.5 * i, 410, 64, 40);
	}
	for (j = 0; j < 4; j ++)
	{
		iFilledRectangle(900 + 95 * j, 360, 85, 40);
	}
	for (i = 0; i < 4; i ++)
	{
		if (i == 3) iSetColor(0, 255, 128);
		iFilledRectangle(900 + 95 * i, 310, 85, 40);
	}
	for(i = 0; i < 6; i ++)
	{
		iSetColor(192, 192, 192);
		for (j = 0; j < 3; j ++)
		{
			if ((i == 0 && j == 1) || (i == 0 && j == 2))
			{
				iSetColor(255, 62, 62);
			}
			iFilledRectangle(900 + 130 * j, 260 - 50 * i, 110, 40);
            if ((i == 0 && j == 0))
			{
				iShowBMP(930, 260, "PI.bmp");
			}
		}
	}

	// Putting the corresponding texts at the buttons
	iSetColor(0, 0, 0);
	iText(950, 475, "x", GLUT_BITMAP_HELVETICA_18);
	iText(1077, 475, "y", GLUT_BITMAP_HELVETICA_18);
	//iText(1083, 545, "z", GLUT_BITMAP_HELVETICA_18);
	//iText(1156, 545, "=", GLUT_BITMAP_HELVETICA_18);
	iText(1190, 475, "END", GLUT_BITMAP_HELVETICA_18);
	iText(930, 425, "ln", GLUT_BITMAP_HELVETICA_18);
	iText(1006.5, 425, "e", GLUT_BITMAP_HELVETICA_18);
	iText(1070, 425, "log", GLUT_BITMAP_HELVETICA_18);
	iText(1159.5, 425, "(", GLUT_BITMAP_HELVETICA_18);
	iText(1236, 425, ")", GLUT_BITMAP_HELVETICA_18);
	iText(925, 375, "sin", GLUT_BITMAP_HELVETICA_18);
	iText(1020, 375, "cos", GLUT_BITMAP_HELVETICA_18);
	iText(1115, 375, "tan", GLUT_BITMAP_HELVETICA_18);
	iText(1210, 375, "sec", GLUT_BITMAP_HELVETICA_18);
	iText(925, 325, "cot", GLUT_BITMAP_HELVETICA_18);
	iText(1020, 325, "cosec", GLUT_BITMAP_HELVETICA_18);
	iText(1125, 320, "^", GLUT_BITMAP_HELVETICA_18);
	iText(1210, 325, "Help", GLUT_BITMAP_HELVETICA_18);
	//iText(1200, 325, "Range", GLUT_BITMAP_HELVETICA_18);
	iText(945, 525, "2D", GLUT_BITMAP_HELVETICA_18);
	//iText(1160, 345, "3D", GLUT_BITMAP_HELVETICA_18);
	//iText(1115, 345, "acot", GLUT_BITMAP_HELVETICA_18);
	iText(1070, 525, "3D", GLUT_BITMAP_HELVETICA_18);
	iText(1175, 525, "PutPos", GLUT_BITMAP_HELVETICA_18);
	//iText(945, 275, "PI", GLUT_BITMAP_HELVETICA_18);
	iText(1070, 275, "DEL", GLUT_BITMAP_HELVETICA_18);
	iText(1200, 275, "AC", GLUT_BITMAP_HELVETICA_18);
	iText(950, 225, "+", GLUT_BITMAP_HELVETICA_18);
	iText(1080, 225, "-", GLUT_BITMAP_HELVETICA_18);
	iText(1210, 225, "*");
	iText(950, 175, "/", GLUT_BITMAP_HELVETICA_18);
	iText(1080, 175, ".", GLUT_BITMAP_HELVETICA_18);
	iText(1210, 175, "0", GLUT_BITMAP_HELVETICA_18);
	iText(950, 125, "1", GLUT_BITMAP_HELVETICA_18);
	iText(1080, 125, "2", GLUT_BITMAP_HELVETICA_18);
	iText(1210, 125, "3", GLUT_BITMAP_HELVETICA_18);
	iText(950, 75, "4", GLUT_BITMAP_HELVETICA_18);
	iText(1080, 75, "5", GLUT_BITMAP_HELVETICA_18);
	iText(1210, 75, "6", GLUT_BITMAP_HELVETICA_18);
	iText(950, 25, "7", GLUT_BITMAP_HELVETICA_18);
	iText(1080, 25, "8", GLUT_BITMAP_HELVETICA_18);
	iText(1210, 25, "9", GLUT_BITMAP_HELVETICA_18);
}







void draw_axis_3D()
{
	iSetColor(255,0,0);
	iLine(start_x,start_y,start_x+len_x_axis*cos(A),start_y+len_x_axis*sin(A));
	iLine(start_x,start_y,start_x-len_y_axis*cos(B),start_y+len_y_axis*sin(B));
	iLine(start_x,start_y,start_x,start_y+len_z_axis);
	//iSetColor(0, 100, 0);
	iText(start_x+len_x_axis*cos(A)+axis_name_dis,start_y+len_x_axis*sin(A)+axis_name_dis, "X", GLUT_BITMAP_HELVETICA_18);
	iText(start_x-len_y_axis*cos(B),start_y+len_y_axis*sin(B)+axis_name_dis,"Y",GLUT_BITMAP_HELVETICA_18);
	iText(start_x+axis_name_dis,start_y+len_z_axis+axis_name_dis,"Z",GLUT_BITMAP_HELVETICA_18);
}
void draw_arrow_3D()
{
	iSetColor(255,0,0);
	double Xx_arrow[3],Xy_arrow[3],Yx_arrow[3],Yy_arrow[3],Zx_arrow[3],Zy_arrow[3];
	Xx_arrow[0]=start_x+len_x_axis*cos(A);
	Xx_arrow[1]=start_x+len_x_axis*cos(A)-arrow_len*cos(80*PI/180.0);
	Xx_arrow[2]=start_x+len_x_axis*cos(A)-arrow_len*cos(10*PI/180.0);
	Xy_arrow[0]=start_y+len_x_axis*sin(A);
	Xy_arrow[1]=start_y+len_x_axis*sin(A)-arrow_len*sin(80*PI/180.0);
	Xy_arrow[2]=start_y+len_x_axis*sin(A)+arrow_len*sin(10*PI/180.0);
	iFilledPolygon(Xx_arrow,Xy_arrow,3);

	Yx_arrow[0]=start_x-len_y_axis*cos(B);
	Yx_arrow[1]=start_x-len_y_axis*cos(B)+arrow_len*cos(60*PI/180.0);
	Yx_arrow[2]=start_x-len_y_axis*cos(B)+arrow_len*cos(10*PI/180.0);
	Yy_arrow[0]=start_y+len_y_axis*sin(B);
	Yy_arrow[1]=start_y+len_y_axis*sin(B)-arrow_len*sin(60*PI/180.0);
	Yy_arrow[2]=start_y+len_y_axis*sin(B)+arrow_len*sin(10*PI/180.0);
	iFilledPolygon(Yx_arrow,Yy_arrow,3);

	Zx_arrow[0]=start_x;
	Zx_arrow[1]=start_x-arrow_len*sin(30*PI/180.0);
	Zx_arrow[2]=start_x+arrow_len*sin(30*PI/180.0);
	Zy_arrow[0]=start_y+len_z_axis;
	Zy_arrow[1]=start_y+len_z_axis-arrow_len*cos(45*PI/180.0);
	Zy_arrow[2]=start_y+len_z_axis-arrow_len*cos(30*PI/180.0);
	iFilledPolygon(Zx_arrow,Zy_arrow,3);
}
void locate_3D_point()
{
	if(x>1)
		x=x-2;
	else if(y>1)
	{
		y=y-2;
		x=end_x;
	}
	z=multiplier_z*f3(main_eqn,x,y);
}

void draw_graph_3D()
{
	iSetColor(0,0,(int)z%150+150);
	iPoint(start_x+x*cos(A)-y*cos(B),start_y+z+y*sin(B)+x*sin(A),size_point);
}




void iDraw() {

	iSetColor(0, 0, 0);
	iFilledRectangle(0, 710, 900, 20);
	if(Graph_2D==1)
	{
		if(flag==0)
		{
			draw_graphPaperAndKeyboard();
			flag = 1;
			// change
			//iText(910, 700, inputStr, GLUT_BITMAP_9_BY_15);
		}
        // Help window
        if (flag_help == 1)
            iShowBMP(30, 180, "Help.BMP");
		//int i;
		if(flag_error!=1)
		{
			if (flag_error == 0) iShowBMP(29, 326, "error(0).bmp");
			if (flag_error == -1) iShowBMP(29, 326, "error(-1).bmp");
			if (flag_error == -2) iShowBMP(29, 326, "error(-2).bmp");
			if (flag_error == -6) iShowBMP(29, 326, "error(-6).bmp");
			if (flag_error == -3) iShowBMP(29, 326, "error(-3).bmp");
			if (flag_error == -4) iShowBMP(29, 326, "error(-4).bmp");
			if (flag_error == -5) iShowBMP(29, 326, "error(-5).bmp");
		}
		else if (flag_graph == 1 )
		{
			iSetColor(255,0,0);
			if(c!=0)
				iLine(prev_point_x,prev_point_y,x_point,y_point);
			c=1;
			prev_point_x=x_point;
			prev_point_y=y_point;
			//iPoint(x_point, y_point, 1);
			//printf("yes\n");
		}
		/*iSetColor(20, 200, 200);
		iCircle(centre_coordinate_x, centre_coordinate_y, 5);*/
	}
	else if(Graph_3D==1)
	{
		draw_axis_3D();
		draw_arrow_3D();
			if(flag_graph==1)
			{
				locate_3D_point();
				draw_graph_3D();
			}
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	//printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
int len_new_char[30], ix = 0;

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		printf("x = %d, y= %d\n",mx,my);
		if (state_in == 0)
		{

			if ((mx > 900) && (mx < 1014) && (my > 460) && (my < 500))	{strcat(inputStr, "x"); len_new_char[ix++]=1;}
			if ((mx > 1027) && (mx < 1140) && (my > 460) && (my < 500))	{strcat(inputStr, "y"); len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 964) && (my > 410) && (my < 450))	{strcat(inputStr, "ln("); len_new_char[ix++]=3;}
			if ((mx > 976) && (mx < 1038) && (my > 410) && (my < 450))	{strcat(inputStr, "e^("); len_new_char[ix++]=3;}
			if ((mx > 1054) && (mx < 1118) && (my > 410) && (my < 450))	{strcat(inputStr, "log("); len_new_char[ix++]=4;}
			if ((mx > 1130) && (mx < 1193) && (my > 410) && (my < 450))	{strcat(inputStr, "("); len_new_char[ix++]=1;}
			if ((mx > 1207) && (mx < 1270) && (my > 410) && (my < 450))	{strcat(inputStr, ")"); len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 985) && (my > 360) && (my < 400))	{strcat(inputStr, "sin("); len_new_char[ix++]=4;}
			if ((mx > 997) && (mx < 1077) && (my > 360) && (my < 400))	{strcat(inputStr, "cos("); len_new_char[ix++]=4;}
			if ((mx > 1091) && (mx < 1175) && (my > 360) && (my < 400))	{strcat(inputStr, "tan("); len_new_char[ix++]=4;}
			if ((mx > 1185) && (mx < 1270) && (my > 360) && (my < 400))	{strcat(inputStr, "sec("); len_new_char[ix++]=4;}
			if ((mx > 900) && (mx < 985) && (my > 310) && (my < 350))	{strcat(inputStr, "cot("); len_new_char[ix++]=4;}
			if ((mx > 997) && (mx < 1077) && (my > 310) && (my < 350))	{strcat(inputStr, "cosec("); len_new_char[ix++]=6;}
			if ((mx > 1091) && (mx < 1175) && (my > 310) && (my < 350))	{strcat(inputStr, "^"); len_new_char[ix++]=1;}
		//	if ((mx > 1185) && (mx < 1270) && (my > 310) && (my < 350)) ;// Range
			if ((mx > 900) && (mx < 1014) && (my > 510) && (my < 550))	// 2D
			{
				strcpy(inputStr, "y = ");
			//	iText(910, 670, "y = ", GLUT_BITMAP_9_BY_15);
				for (ix = 0; ix < 30; ix ++) len_new_char[ix] = 0;
				ix = 0;
				iSetColor(255, 255, 255);
				iFilledRectangle(900, 610, 370, 100);
				Graph_2D=1;
				Graph_3D=0;
			//	iText(920, 670, "y = ", GLUT_BITMAP_9_BY_15);

			}
			//if ((mx > 997) && (mx < 1077) && (my > 330) && (my < 370))	{strcat(inputStr, "asec"); len_new_char[ix++]=4;}
			if ((mx > 1027) && (mx < 1140) && (my > 510) && (my < 550))	// 3D
			{
				strcpy(inputStr, "z = ");
				for (ix = 0; ix < 30; ix ++) len_new_char[ix] = 0;
				ix = 0;
				iSetColor(255, 255, 255);
				iFilledRectangle(900, 610, 370, 100);
				iFilledRectangle(border_coordinate_common + width_of_border_line, border_coordinate_common + width_of_border_line, width_of_Graph, height_of_graph);
				Graph_2D=0;
				Graph_3D=1;
			}
			//if ((mx > 1154) && (mx < 1267) && (my > 510) && (my < 550)) // PutPos
			//if ((mx > 1185) && (mx < 1270) && (my > 330) && (my < 370))	{strcat(inputStr, "acosec"); len_new_char[ix++]=6;}
			if ((mx > 900) && (mx < 1008) && (my > 260) && (my < 300))	{strcat(inputStr, "180"); len_new_char[ix++]=3;}
			if ((mx > 900) && (mx < 1008) && (my > 210) && (my < 250))	{strcat(inputStr, "+"); len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 210) && (my < 250))	{strcat(inputStr, "-"); len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 210) && (my < 250))	{strcat(inputStr, "*"); len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 1008) && (my > 160) && (my < 200))	{strcat(inputStr, "/"); len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 160) && (my < 200))	{strcat(inputStr, "."); len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 160) && (my < 200))	{strcat(inputStr, "0"); len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 1008) && (my > 110) && (my < 150))	{strcat(inputStr, "1"); len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 110) && (my < 150))	{strcat(inputStr, "2"); len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 110) && (my < 150))	{strcat(inputStr, "3"); len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 1008) && (my > 60) && (my < 100))	{strcat(inputStr, "4"); len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 60) && (my < 100))	{strcat(inputStr, "5"); len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 60) && (my < 100))	{strcat(inputStr, "6"); len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 1008) && (my > 10) && (my < 50))	{strcat(inputStr, "7"); len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 10) && (my < 50))	{strcat(inputStr, "8"); len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 10) && (my < 50))	{strcat(inputStr, "9"); len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 260) && (my < 300) && ix) // DEL
			{
				ix --;
				inputStr[strlen(inputStr) - len_new_char[ix]] = '\0';
				iSetColor(255, 255, 255);
				iFilledRectangle(900, 610, 370, 100);
			}
		}

/*************************************************************************************************************/
		//if ((mx > 1185) && (mx < 1270) && (my > 380) && (my < 420)) {state_in = 1;}// Range
		if (state_in == 1)
		{
			//printf("low\n");
			if ((mx > 900) && (mx < 1008) && (my > 260) && (my < 300))	{strcat(lowerRange, "180");}
			if ((mx > 1031) && (mx < 1137) && (my > 210) && (my < 250))	{strcat(lowerRange, "-");}
			if ((mx > 900) && (mx < 1008) && (my > 210) && (my < 250))	{strcat(lowerRange, "+");}
			if ((mx > 1160) && (mx < 1270) && (my > 210) && (my < 250))	{strcat(lowerRange, "*");}
			if ((mx > 900) && (mx < 1008) && (my > 160) && (my < 200))	{strcat(lowerRange, "/");}
			if ((mx > 1031) && (mx < 1137) && (my > 160) && (my < 200))	{strcat(lowerRange, ".");}// len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 160) && (my < 200))	{strcat(lowerRange, "0");}// len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 1008) && (my > 110) && (my < 150))	{strcat(lowerRange, "1");}// len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 110) && (my < 150))	{strcat(lowerRange, "2");}// len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 110) && (my < 150))	{strcat(lowerRange, "3");}// len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 1008) && (my > 60) && (my < 100))	{strcat(lowerRange, "4");}// len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 60) && (my < 100))	{strcat(lowerRange, "5");}// len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 60) && (my < 100))	{strcat(lowerRange, "6");}// len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 1008) && (my > 10) && (my < 50))	{strcat(lowerRange, "7");}// len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 10) && (my < 50))	{strcat(lowerRange, "8");}// len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 10) && (my < 50))	{strcat(lowerRange, "9");}// len_new_char[ix++]=1;}
			//if ((mx > 900) && (mx < 1008) && (my > 280) && (my < 320))	{strcat(lowerRange, "180");}// len_new_char[ix++]=2;}
		}

		if (state_in == 2)
		{
			//printf("high\n");
			if ((mx > 900) && (mx < 1008) && (my > 260) && (my < 300))	{strcat(upperRange, "180");}
			if ((mx > 1031) && (mx < 1137) && (my > 210) && (my < 250))	{strcat(upperRange, "-");}
			if ((mx > 900) && (mx < 1008) && (my > 210) && (my < 250))	{strcat(upperRange, "+");}
			if ((mx > 1160) && (mx < 1270) && (my > 210) && (my < 250))	{strcat(upperRange, "*");}
			if ((mx > 900) && (mx < 1008) && (my > 160) && (my < 200))	{strcat(upperRange, "/");}
			if ((mx > 1031) && (mx < 1137) && (my > 160) && (my < 200))	{strcat(upperRange, ".");}// len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 160) && (my < 200))	{strcat(upperRange, "0");}// len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 1008) && (my > 110) && (my < 150))	{strcat(upperRange, "1");}// len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 110) && (my < 150))	{strcat(upperRange, "2");}// len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 110) && (my < 150))	{strcat(upperRange, "3");}// len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 1008) && (my > 60) && (my < 100))	{strcat(upperRange, "4");}// len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 60) && (my < 100))	{strcat(upperRange, "5");}// len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 60) && (my < 100))	{strcat(upperRange, "6");}// len_new_char[ix++]=1;}
			if ((mx > 900) && (mx < 1008) && (my > 10) && (my < 50))	{strcat(upperRange, "7");}// len_new_char[ix++]=1;}
			if ((mx > 1031) && (mx < 1137) && (my > 10) && (my < 50))	{strcat(upperRange, "8");}// len_new_char[ix++]=1;}
			if ((mx > 1160) && (mx < 1270) && (my > 10) && (my < 50))	{strcat(upperRange, "9");}// len_new_char[ix++]=1;}
			//if ((mx > 900) && (mx < 1008) && (my > 280) && (my < 320))	{strcat(lowerRange, "180");}// len_new_char[ix++]=2;}
		}
        if ((mx > 1185) && (mx < 1270) && (my > 310) && (my < 350)) flag_help = 1;
		if ((mx > 1000) && (mx < 1110) && (my > 560) && (my < 600))	state_in = 1; // lowLim
		if ((mx > 1160) && (mx < 1270) && (my > 560) && (my < 600))	state_in = 2; //upLim
		if ((mx > 1160) && (mx < 1270) && (my > 260) && (my < 300)) // AC //Put outside state_in
		{
			strcpy(inputStr, "\0");
			strcpy(lowerRange, "\0");
			strcpy(upperRange, "\0");
			for (ix = 0; ix < 30; ix ++) len_new_char[ix] = 0;
			ix = 0;
			flag = 0; //change
			flag_graph = 0; //change
			flag_range_calc = 0;
			state_in = 0;
			flag_help = 0;
			flag_error=1;
			c=0;
			//x_value = 0; //change
			//y_value = 0; //change
			/*iSetColor(255, 255, 255);
			iFilledRectangle(900, 610, 370, 100);*/
		}
		if ((mx > 1154) && (mx < 1267) && (my > 460) && (my < 500)) //End //Put outside state_in
		{
			int len;
			strcat(inputStr, "\0");
			strcat(lowerRange, "\0");
			strcat(upperRange, "\0");
			lim_1=atof(lowerRange);
			lim_2=atof(upperRange);
			c=0;
			prev_point_x=atof(lowerRange)-.05;
			prev_point_y=f3(inputStr,atof(lowerRange)-.05,0);
			flag_error=1;
			find_error(inputStr);
			x_value = atof(lowerRange);
			flag_graph = 1;
			len=strlen(inputStr);
			n_strcpy(inputStr,main_eqn,4,len-1);
			state_in = 0;
			//printf("0");
		}
		/*if ((mx > 1031) && (mx < 1137) && (my > 280) && (my < 320) && ix) // DEL
		{
			ix --;
			inputStr[strlen(inputStr) - len_new_char[ix]] = '\0';
			iSetColor(255, 255, 255);
			iFilledRectangle(900, 580, 370, 120);
		}
		*/
		//printf("%s\n", inputStr);
		//strcat(showInput, inputStr);
		//strcpy(showInput, "z = ");
		iSetColor(0, 0, 0);
		iText(935, 670, inputStr, GLUT_BITMAP_9_BY_15);
		iText(1170, 582, upperRange, GLUT_BITMAP_9_BY_15);
		iText(1010, 582, lowerRange, GLUT_BITMAP_9_BY_15);
	//	printf("eqn = %s low = %s high = %s\n", inputStr, lowerRange, upperRange);
		//ix ++;
		/*x += 10;
		y += 10;*/
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		/*x -= 10;
		y -= 10;*/
	}
}
/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == 'p') {
		iPauseTimer(0);
	}
	if(key=='r')
		iResumeTimer(0);

	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//place your codes for other keys here
}







#define input_size 200
char token_eqn[200][201];
int find_target(char str[],int start,int serial,int mode)
{
    // mode 1 finds the end of brackets.
    // mode 2 finds the starting of brackets.
    int pos=-1,i,len,serial_temp=serial;
    len=strlen(str);
    for(i=start;i<len && mode==1;i++)
    {
        if(str[i]==')' && serial_temp==serial)
        {
            pos=i-1;
            break;
        }
        else if(str[i]=='(')
            serial_temp++;
        else if(str[i]==')')
            serial_temp--;
    }
    for(i=start;i<len && mode==2;i++)
    {
        if(str[i]=='(')
        {
            pos=i-2;
            break;
        }
    }
    return pos;
}
void n_strcpy(char from_str[],char to_str[],int pos1,int pos2)
{
    int i,j;
    for(i=pos1,j=0;i<=pos2;i++,j++)
        to_str[j]=from_str[i];
    to_str[j]='\0';
}
void leftShift_num(double array[],int len,int start_pos)
{
    int i;
    for(i=start_pos;i<len-1;i++)//the element of the starting pos will be erased
        array[i]=array[i+1];
    array[len-1]=0;
    //return len-1;
}
int leftShift_str(char array[],int len,int start_pos)
{
    int i;
    for(i=start_pos;i<len-1;i++)//the element of the starting pos will be erased
        array[i]=array[i+1];
    array[len-1]='\0';
    return len-1;
}
double ultimate_value(char ch, double val1,double val2)
{
    if(ch=='+')
        return val1+val2;
    if(ch=='-')
        return val1-val2;
    if(ch=='*')
        return val1*val2;
    if(ch=='/')
        return val1/val2;
    if(ch=='^')
        return pow(val1,val2);
}
int count_sign(char str1[],char sign[])
{
    int i,count=0,len,depth=0;
    len=strlen(str1);
    for(i=0;i<len;i++)
    {
        if(str1[i]=='(')
            depth++;
        else if(str1[i]==')')
            depth--;
        else if((str1[i]=='+' || str1[i]=='-' || str1[i]=='*' || str1[i]=='/' || str1[i]=='^') && depth==0)
        {
            sign[count]=str1[i];
            count++;
        }
    }
    return count;
}

double ff(char str[],double x, double y)
{

    if(strcmp(str,"x")==0)
        return x;
    if(strcmp(str,"y")==0)
        return y;
    return atof(str);
}

int strTok(char str1[],char str2[])//returns how many substrings are there
{
    int i,j,len1,len2,len3=0,flag1=0,count=0;
    len1=strlen(str1);
    len2=strlen(str2);
    for(i=0;i<=len1;i++)
    {
        flag1=0;
        for(j=0;j<len2;j++)
        {
            if(str1[i]==str2[j])
                flag1=1;
		}
        if(flag1==0)
        {
            token_eqn[count][len3]=str1[i];
            len3++;
        }
        else
        {
            token_eqn[count][len3]='\0';
            count++;
            len3=0;
        }
    }
	return count+1;
}
double f2(double temp[],char sign[],int num_signs)
{
    int found_pow=1,found_mult=1,found_div=1,i=0;
    while(found_mult==1 || found_div==1 || found_pow==1)
    {
        for(i=0;i<num_signs;i++)
        {
            if(sign[i]=='^')
            {
                found_pow=1;
                temp[i]=ultimate_value('^',temp[i],temp[i+1]);
                leftShift_num(temp,num_signs+1,i+1);
                leftShift_str(sign,num_signs,i);
                num_signs--;
            }
        }
        for(i=0;i<num_signs;i++)
        {
            if(sign[i]=='*')
            {
                found_mult=1;
                temp[i]=ultimate_value('*',temp[i],temp[i+1]);
                leftShift_num(temp,num_signs+1,i+1);
                leftShift_str(sign,num_signs,i);
                num_signs--;
            }
        }
        for(i=0;i<num_signs;i++)
        {
            if(sign[i]=='/')
            {
                found_div=1;
                temp[i]=ultimate_value('/',temp[i],temp[i+1]);
                leftShift_num(temp,num_signs+1,i+1);
                leftShift_str(sign,num_signs,i);
                num_signs--;
            }
        }
        found_mult=0;
        found_div=0;
        found_pow=0;
        for(i=0;i<num_signs;i++)
        {
            if(sign[i]=='^')
            {
                found_pow=1;
                break;
            }
            if(sign[i]=='*')
            {
                found_mult=1;
                break;
            }
            if(sign[i]=='/')
            {
                found_div=1;
                break;
            }
        }
    }
    while(num_signs>0)
    {
        temp[0]=ultimate_value(sign[0],temp[0],temp[1]);
        leftShift_num(temp,num_signs+1,1);
        leftShift_str(sign,num_signs,0);
        num_signs--;
    }
    return temp[0];
}

/*double f1(char str[],double x,double y)
{
    double temp[input_size];
    int num_signs,i;
    char sign_temp[input_size];
    num_signs=count_sign(str,sign_temp);
    strTok(str,"+-/*^");
    for(i=0;i<=num_signs;i++)
        temp[i]=ff(token_eqn[i],x,y);
    return f2(temp,sign_temp,num_signs);
}
*/
#define PI 3.14159265
double f3(char str[],double x,double y)
{
    int len,i,start=-1,end=-2,count1=0,count2=0,sign_num,k;
    double temp[input_size],argument=0;
    char sign[input_size],str_temp[input_size];
    len=strlen(str);
   // sign_num=count_sign(str,)
    for(i=0;i<len;i++)
    {
        if(str[i]=='(')
        {
            start=i+1;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            temp[count1]=f3(str_temp,x,y);
            count1++;
            i=end+1;
        }
        else if(str[i]=='+' ||str[i]=='-' ||str[i]=='*' ||str[i]=='/' ||str[i]=='^')
        {
            sign[count2]=str[i];
            count2++;
        }
        else if(str[i]=='s' && str[i+1]=='i' && str[i+2]=='n')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=sin(argument*PI/180.0);
            count1++;
            i=end+1;
        }
        else if(str[i]=='c' && str[i+1]=='o' && str[i+2]=='s' && str[i+3]!='e')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=cos(argument*PI/180.0);
            count1++;
            i=end+1;
        }
        else if(str[i]=='t' && str[i+1]=='a' && str[i+2]=='n')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=tan(argument*PI/180.0);
            count1++;
            i=end+1;
        }
        else if(str[i]=='c' && str[i+1]=='o' && str[i+2]=='t')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=(cos(argument*PI/180.0)/sin(argument*PI/180.0));
            count1++;
            i=end+1;
        }
        else if(str[i]=='s' && str[i+1]=='e' && str[i+2]=='c')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=(1.0/cos(argument*PI/180.0));
            count1++;
            i=end+1;
        }
        else if(str[i]=='c' && str[i+1]=='o' && str[i+2]=='s' && str[i+3]=='e' && str[i+4]=='c')
        {
            start=i+6;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=(1.0/sin(argument*PI/180.0));
            count1++;
            i=end+1;
        }
        else if(str[i]=='l' && str[i+1]=='o' && str[i+2]=='g')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=log10(argument);
            count1++;
            i=end+1;
        }
        else if(str[i]=='l' && str[i+1]=='n')
        {
            start=i+3;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=log(argument);
            count1++;
            i=end+1;
        }
        else if(str[i]=='e' && str[i+1]=='^')
        {
            start=i+3;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=exp(argument);
            count1++;
            i=end+1;
        }
        else
        {
            k=0;
            while(str[i]!='(' && str[i]!=')' && str[i]!='+' && str[i]!='-' && str[i]!='*' && str[i]!='/' && str[i]!='^' && i<len)
            {
                str_temp[k]=str[i];
                k++;
                i++;
            }
            str_temp[k]='\0';
            temp[count1]=ff(str_temp,x,y);
            count1++;
           i--;
        }
    }
    sign[count2]='\0';
    return f2(temp,sign,count2);
}







//char lim1[10];
//char lim2[10];

void locate_points_2D()
{
	//printf("1");
//	x_value=atof(lowerRange);
    if(flag_graph==0 || x_value>lim_2 )
        return;
//	printf("2");
    double y_min,y_max,range_y,kx,ky,unit_x_left,unit_x_right,x_for_y_min=0,x_for_y_max=0;
    if(flag_range_calc==0)
    {
		//printf("3");
        flag_range_calc=1;
        lim_1=atof(lowerRange);
        lim_2=atof(upperRange);
		x_for_y_min=lim_1;
		x_for_y_max=lim_1;
		//centre_coordinate_x=abs(((0-lim_2)/(lim_1-0))*width_of_Graph);
        //centre_coordinate_y=abs(((y_min-0)/(y_max-0))*height_of_graph);
        y_min=f3(main_eqn,lim_1,0);
        y_max=y_min;

        kx=lim_1;
        while(kx<=lim_2)
        {
            ky=f3(main_eqn,kx,0);
            if(ky>y_max)
			{
                y_max=ky;
				x_for_y_max=kx;
			}
            if(ky<y_min)
			{
                y_min=ky;
				x_for_y_min=kx;
			}
            kx=kx+.1;
        }

		unit_x_left=(centre_coordinate_x-100)/abs(lim_1);
		unit_x_right=(centre_coordinate_x-100)/abs(lim_2);

		if(unit_x_left>=unit_x_right)
			unit_x=unit_x_right;
		else
			unit_x=unit_x_left;
        //unit_x=(width_of_Graph-200)/(double)(lim_1-lim_2);
        //unit_x=abs(unit_x);

        range_y=abs(y_max-y_min);
        if(range_y<=0.001)
            unit_y=5;
        else if(range_y>=.001 && range_y<=20000)
            unit_y=(height_of_graph-200.00)/range_y;
        else//if(range_y>20000)
		{
            unit_y=3.5;
		//	y_max=700;
		//	y_min=-700;
		}

		//while((y_min*unit_y+centre_coordinate_y)>25 || (y_max*unit_y+centre_coordinate_y)>(height_of_graph-25))
		//	unit_y=unit_y-.0001;


		unit_y=abs(unit_y);

        x_value=lim_1;
    }
//	printf("4");
    y_value=f3(main_eqn,x_value,0);

    x_point=x_value*unit_x+centre_coordinate_x;
    y_point=y_value*unit_y+centre_coordinate_y;

    x_value=x_value+.5;
	//printf("%lf %lf.....%lf %lf \n",x_value,y_value,x_point,y_point);
	if(f3(main_eqn,x_value,0)*unit_y+centre_coordinate_y>90000000000)
		//x_value=lim_1+2;
		locate_points_2D();
}




int main() {
	//place your own initialization codes here.
	x_point = centre_coordinate_x;
	y_point = centre_coordinate_y;
	x_value = 0;
	strcpy(inputStr, "\0");
	strcpy(lowerRange, "\0");
	strcpy(upperRange, "\0");
	//y_value = (double) sin((double) x_value);
	//printf("point %lf %lf", x_point, y_point);
	iSetTimer(1, locate_points_2D);
	iInitialize(window_width, window_height, "3-D_GRAPH");
	return 0;
}
