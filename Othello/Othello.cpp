#include "Othello.hpp"

void Othello::mousebotton(int state ,int button, int cx,int cy){

	if(  state != GLUT_DOWN ||  button !=GLUT_LEFT_BUTTON  )return;
	if( (disk[my][mx].Canput_white != true && turn==true ) || ( disk[my][mx].Canput_black != true && turn==false) )return;
    
	if( ( ( mode==P2M && turn==BLACK ) || (mode==M2P && turn==WHITE ) ) && (stat!=POSE) && (stat!=GAMEOVER) ){
		disk[my][mx].put=true;
		disk[my][mx].color=turn;
		preY=my;
		preX=mx;
		reverse(turn,my,mx);
		
		if( CanPut(!turn) )turn=!turn;	//敵が置ける場合は交代
		else if( !CanPut(turn) ){
			stat=GAMEOVER;
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					if( disk[i][j].color && disk[i][j].put )w++;
					else if( !disk[i][j].color && disk[i][j].put )b++;
				}
			}
		}
	}
	//コンピュータ相手なら思考時間
	if( mode != P2P ){
		stat=THINK;
		time2=50;
	}else{
		stat=TURN;
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
            init();
            break;
        case 13: /* ENTER */
            if( stat == READY )stat=PLAY;
            break;
        case 'q':
            stat=GAMEOVER;
            break;
        case 'p':	//ポーズ
            //pose=!pose;
            stat=POSE;
            break;
        case 'm':	//playmode切り替え
            if( stat==READY ){
				mode = static_cast<Mode>(mode + 1);
                if(mode>M2M)mode=P2P;
            }
            break;
        default:
            break;
	}
	glutPostRedisplay();
}


void Othello::timer(int dt){
	//グローバルタイム
	if( stat != POSE && stat!=GAMEOVER &&  stat!=READY )time1++;
    
	//思考時間
	if( stat == THINK ){
		time2--;
		if(time2>0){
			glutPostRedisplay();
			//glutTimerFunc(dt,this->timer,10);
			return;
		}
		stat=PLAY;
	}
    
	if( ( (mode==P2M && turn==WHITE ) || (mode==M2P && turn==BLACK) || ( mode==M2M ) ) && ( stat != POSE ) && ( stat != GAMEOVER ) && ( stat != READY ) ){
		int m,n;
		c.computer(turn,m,n,disk);
		disk[m][n].put=true;
		disk[m][n].color=turn;
		preY=m;
		preX=n;
		reverse(turn,m,n);
		if( CanPut(!turn) )turn=!turn;	//敵が置ける場合は交代
		else if( !CanPut(turn) ){	//敵が置けない場合、自分も置けない場合は終了
			stat=GAMEOVER;
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					if( disk[i][j].color && disk[i][j].put )w++;
					else if( !disk[i][j].color && disk[i][j].put )b++;
				}
			}
		}
	}
	glutPostRedisplay();
}


void Othello::display(void){
	/* Before Draw */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* 置いた場所 */
	glColor3f(1,0,0);
	Drawsquare(60*(preX+1),60*(preY+1));
   
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if( disk[i][j].put ){
				if( disk[i][j].color )glColor3f(1,1,1);
				else glColor3f(0,0,0);
				Drawstone(90+60*j,90+60*i);
			}
			if( (disk[i][j].Canput_white == true && turn == WHITE ) || (disk[i][j].Canput_black==true && turn==BLACK) ){
				glColor3f(0,1,0.1);
				Drawsquare(60+60*j,60+60*i);
			}
		}
	}

	board.drow(mode,stat);

	/* カーソル */
	if(turn)glColor3f(1,1,1);
	else glColor3f(0,0,0);
	if( (mx>=0) && (mx<=7) && (my>=0) && (my<=7)  )Drawstone(90+mx*60,90+my*60);

	if( stat == READY ){
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
	}else if( stat == GAMEOVER ){
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
	while( disk[y][x].color!=color && disk[y][x].put==true && ( x>=0 && x<=7 ) && ( y>=0 && y<=7 ) ){
		x+=dx;
		y+=dy;
		if( disk[y][x].color==color && disk[y][x].put==true && ( x>=0 && x<=7 ) && ( y>=0 && y<=7 ) )return true;
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
					disk[vy][vx].color=color;	//reverse
				}while(disk[vy+j][vx+i].color!=color);	//同じ色の石が見つかるまで
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
			if(disk[y][x].put == true)state=false;
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
			if(color)disk[y][x].Canput_white=state;
			else disk[y][x].Canput_black=state;
			if(state)putable=true;	//置ける場所が一つでもあれば置ける。
		}
	}
	return putable;
}

void Othello::init(){
	/* 初期設定 */
	//gameover=false;
	stat=READY;
	
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			disk[m][n].put=false;
			disk[m][n].color=false;
		}
	}
	disk[3][3].put=true;
	disk[4][3].put=true;
	disk[3][4].put=true;
	disk[4][4].put=true;
    
	disk[3][4].color=WHITE;
	disk[4][3].color=WHITE;
    
	CanPut(BLACK);
	turn=BLACK;
	preX=preY=w=b=time1=time2=0;
    
}



#ifdef OOP
//static なメンバ関数しか呼び出せない
int main(int argc, char **argv){
	Othello *othelo = new Othello();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	
	Othello::CreateWindow(0,800,0,600,"othello");

	glClearColor( 0 , 0.7, 0, 1);//back ground color
	glutDisplayFunc(Game::display);
	glutKeyboardFunc(Game::key);
	glutPassiveMotionFunc(Game::mouse);
	glutMouseFunc(Game::mousebotton);
	glutTimerFunc(0,Game::timer,100);
    
	glutMainLoop();
	return 0;
}

#else 


Othello othello;
void display(void){othello.display();}
void mousebotton(int state ,int button, int cx,int cy){othello.mousebotton(state,button,cx,cy);}
void mouse(int cx,int cy){othello.mouse(cx,cy);}
void key(unsigned char k, int x, int y){othello.key(k,x,y);}
void timer(int dt){
	othello.timer(dt);
	glutTimerFunc(dt,timer,10);
}

int main(int argc, char **argv){
	othello.init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	othello.CreateWindow(0,800,600,0,"othello");
	glClearColor( 0 , 0.7, 0, 1);//back ground color
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mousebotton);
	glutTimerFunc(0,timer,100);
    
	glutMainLoop();
	return 0;
}
#endif