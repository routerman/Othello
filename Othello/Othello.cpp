#include "Othello.hpp"

#include <GL/glut.h>


void Othello::mousebotton(int state ,int button, int cx,int cy){

	if(  state != GLUT_DOWN ||  button !=GLUT_LEFT_BUTTON  )return;
	if( (s[my][mx].Canput_white != true && turn==true ) || ( s[my][mx].Canput_black != true && turn==false) )return;
    
	if( ( ( player==MODE_YOUCOM && turn==BLACK ) || (player==MODE_COMYOU && turn==WHITE ) ) && (stat!=STAT_POSE) && (stat!=STAT_GAMEOVER) ){
		s[my][mx].put=true;
		s[my][mx].color=turn;
		preY=my;
		preX=mx;
		reverse(turn,my,mx);
		
		if( CanPut(!turn) )turn=!turn;	//敵が置ける場合は交代
		else if( !CanPut(turn) ){
			stat=STAT_GAMEOVER;
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					if( s[i][j].color && s[i][j].put )w++;
					else if( !s[i][j].color && s[i][j].put )b++;
				}
			}
		}
	}
	//コンピュータ相手なら思考時間
	if( player != MODE_YOUYOU ){
		stat=STAT_THINK;
		time2=50;
	}else{
		stat=STAT_TURN;
		time2=60;
	}
	glutPostRedisplay();

}

void Othello::mouse(int cx,int cy){
	mx=cx/60-1;
	my=cy/60-1;
}


void Othello::key(unsigned char k, int x, int y){
	switch (k) {
        case 27:  /* Escape */
            exit(0);
            break;
        case 127: /* delete */
            InitGame();
            break;
        case 13: /* ENTER */
            if( stat == STAT_READY )stat=STAT_PLAY;
            break;
        case 'q':
            stat=STAT_GAMEOVER;
            break;
        case 'p':	//ポーズ
            //pose=!pose;
            stat=STAT_POSE;
            break;
        case 'm':	//playmode切り替え
            if( stat==STAT_READY ){
                player++;
                if(player==5)player=1;
            }
            break;
        default:
            break;
	}
	glutPostRedisplay();
}


void Othello::timer(int dt){
	//グローバルタイム
	if( stat != STAT_POSE && stat!=STAT_GAMEOVER &&  stat!=STAT_READY )time1++;
    
	//思考時間
	if( stat == STAT_THINK ){
		time2--;
		if(time2>0){
			glutPostRedisplay();
			//glutTimerFunc(dt,this->timer,10);
			return;
		}
		stat=STAT_PLAY;
	}
    
	if( ( (player==MODE_YOUCOM && turn==WHITE ) || (player==MODE_COMYOU && turn==BLACK) || ( player==MODE_COMCOM ) ) && ( stat != STAT_POSE ) && ( stat != STAT_GAMEOVER ) && ( stat != STAT_READY ) ){
		int m,n;
		c.computer(turn,m,n,s);
		s[m][n].put=true;
		s[m][n].color=turn;
		preY=m;
		preX=n;
		reverse(turn,m,n);
		if( CanPut(!turn) )turn=!turn;	//敵が置ける場合は交代
		else if( !CanPut(turn) ){	//敵が置けない場合、自分も置けない場合は終了
			stat=STAT_GAMEOVER;
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					if( s[i][j].color && s[i][j].put )w++;
					else if( !s[i][j].color && s[i][j].put )b++;
				}
			}
		}
	}
	glutPostRedisplay();
}


void Othello::display(void){
	/* Before Draw */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	board.drow(player,stat);
   
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( s[i][j].put ){
				if( s[i][j].color )glColor3f(1,1,1);
				else glColor3f(0,0,0);
				Drawstone(90+60*j,90+60*i);
			}
			if( (s[i][j].Canput_white == true && turn == WHITE ) || (s[i][j].Canput_black==true && turn==BLACK) ){
				glColor3f(0,1,0.1);
				Drawsquare(60+60*j,60+60*i);
			}
		}
	}
	/* 置いた場所 */
	glColor3f(1,0,0);
	Drawsquare(60*(preX+1),60*(preY+1));

	/* カーソル */
	if(turn)glColor3f(1,1,1);
	else glColor3f(0,0,0);
	if( (mx>=0) && (mx<=7) && (my>=0) && (my<=7)  )Drawstone(90+mx*60,90+my*60);

	if( stat == STAT_READY ){
		/* モード設定 */
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
		glVertex2i(100,360);
		glVertex2i(100,280);
		glVertex2i(500,280);
		glVertex2i(500,360);
		glEnd();
		glColor3f(0,0,0);
		DrawString(130,310,"Please, press m and choose mode,");
		DrawString(130,340,"and press Enter to start GAME!");
	}else if( stat == STAT_GAMEOVER ){
		/* ゲーム終了 */
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
		glVertex2i(100,340);
		glVertex2i(100,260);
		glVertex2i(500,260);
		glVertex2i(500,340);
		glEnd();
        
		char message[30];
		glColor3f(0,0,0);
//		if(w>b)sprintf(message,"white=%d,black=%d WHITE WIN!",w,b);
	//	else if(w<=b)sprintf(message,"white=%d,black=%d BLACK WIN!",w,b);
		DrawString(130,300,message);
	}
	/* After Draw */
	glutSwapBuffers();
}


bool Othello::line(bool color,signed int y,signed int x,signed int dy,signed int dx){
	x+=dx;
	y+=dy;
	//while(異色の石が存在 && 盤内)
	while( s[y][x].color!=color && s[y][x].put==true && ( x>=0 && x<=7 ) && ( y>=0 && y<=7 ) ){
		x+=dx;
		y+=dy;
		if( s[y][x].color==color && s[y][x].put==true && ( x>=0 && x<=7 ) && ( y>=0 && y<=7 ) )return true;
	}
	return false;
}
void Othello::reverse(bool color,signed int cy ,signed int cx){
	signed int vx=cx,vy=cy;
	for(signed int i=-1;i<=1;i++){
		for(signed int j=-1;j<=1;j++){
			if( line(color,cy,cx,j,i) ){	//reverse可
				do{
					vx+=i;
					vy+=j;
					s[vy][vx].color=color;	//reverse
				}while(s[vy+j][vx+i].color!=color);	//同じ色の石が見つかるまで
				vx=cx;	//置いた場所に戻る
				vy=cy;
			}
		}
	}
}
bool Othello::CanPut(bool color){
	bool state=false;	//コードを短くするためだけの変数
	bool putable=false;	//戻す用変数
	for(signed int y=0;y<8;y++){
		for(signed int x=0;x<8;x++){
			if(s[y][x].put == true)state=false;
			else{
				state=(
                       line(color,y,x,+1, 0)||
                       line(color,y,x,+1,+1)||
                       line(color,y,x, 0,+1)||
                       line(color,y,x,-1,+1)||
                       line(color,y,x,-1, 0)||
                       line(color,y,x,-1,-1)||
                       line(color,y,x, 0,-1)||
                       line(color,y,x,+1,-1)
                       );
			}
			if(color)s[y][x].Canput_white=state;
			else s[y][x].Canput_black=state;
			if(state)putable=true;	//置ける場所が一つでもあれば置ける。
		}
	}
	return putable;
}

void Othello::InitGame(){
	/* 初期設定 */
	//gameover=false;
	stat=STAT_READY;
	
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			s[m][n].put=false;
			s[m][n].color=false;
		}
	}
	s[3][3].put=true;
	s[4][3].put=true;
	s[3][4].put=true;
	s[4][4].put=true;
    
	s[3][4].color=WHITE;
	s[4][3].color=WHITE;
    
	CanPut(BLACK);
	turn=BLACK;
	preX=preY=w=b=time1=time2=0;
    
}
