#include "Othello.hpp"

void Othello::mousebotton(int state ,int button, int cx,int cy){
	if(  state != GLUT_DOWN ||  button != GLUT_LEFT_BUTTON  )return;
	procedure();
	glutPostRedisplay();
}

void Othello::timer(int dt){
	//グローバルタイム
	//if( stat != POSE && stat!=GAMEOVER &&  stat!=READY )time1++;
	machine[0].place(&cursor,disk);
	procedure();
	glutPostRedisplay();
}


//石を置く際の共通処理
void Othello::procedure(){
	//アクセス制御
	if( stat != PLAY )return;
	//出番のアクセス制御
	//if( ( mode==P2M && turn==WHITE ) || (mode==M2P && turn==BLACK) || ( mode==M2M ) ){	}
	//if( ( mode==P2M && turn==BLACK ) || (mode==M2P && turn==WHITE) ){	}
	//置ける場所かどうか
	if( disk[cursor.x][cursor.y].putable[turn] != true )return;
	//石を置く
	disk[cursor.x][cursor.y].onboard=true;
	disk[cursor.x][cursor.y].color=turn;
	before.x=cursor.x;
	before.y=cursor.y;
	//リバースする
	reverse(turn,cursor.x,cursor.y);
	//置けるかチェック
	if( CanPut(!turn) )turn=!turn;	//敵が置ける場合は交代
	else if( !CanPut(turn) ){	//敵が置けない場合、自分も置けない場合は終了
		stat=GAMEOVER;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if( disk[i][j].onboard ){
					num_disk[disk[i][j].color]++;
				}
			}
		}
	}
	std::cout<<"a";
}

//マウスの動き
void Othello::mouse(int cx,int cy){
	//人間は自分のターンではないときはカーソルを動かさない。
//	if( ( mode==P2M && turn==BLACK ) || ( mode==M2P && turn==WHITE ) || ( mode==P2P ) ){
		cursor.x=cx/60-1;
		cursor.y=cy/60-1;
//	}
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
            if(stat==PLAY)stat=POSE;
			else if(stat==POSE)stat=PLAY;

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

void Othello::display(void){
	/* Before Draw */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* 置いた場所 */
	glColor3f(1,0,0);
	DrawSquare(60*(before.x+1),60*(before.y+1));
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			disk[i][j].drow(turn);
		}
	}
	board.drow(mode,stat);

	/* カーソル */
	if(turn)glColor3f(1,1,1);
	else glColor3f(0,0,0);
	//if( (cursor.x>=0) && (cursor.x<8) && (cursor.y>=0) && (cursor.y<8) )
	DrawCircle(90+cursor.x*60,90+cursor.y*60);

	/* After Draw */
	glutSwapBuffers();
}


bool Othello::line(bool color,signed int y,signed int x,signed int dy,signed int dx){
	x+=dx;
	y+=dy;
	//while(異色の石が存在 && 盤内)
	while( disk[x][y].color!=color && disk[x][y].onboard==true && ( x>=0 && x<=7 ) && ( y>=0 && y<=7 ) ){
		x+=dx;
		y+=dy;
		if( disk[x][y].color==color && disk[x][y].onboard==true && ( x>=0 && x<=7 ) && ( y>=0 && y<=7 ) )return true;
	}
	return false;
}
void Othello::reverse(bool color,signed int cy ,signed int cx){
	signed int vx=cx,vy=cy;
	//I2 center,vector;
	for(signed int i=-1;i<=1;i++){
		for(signed int j=-1;j<=1;j++){
			if( line(color,cx,cy,j,i) ){	//reverse可
				do{
					vx+=i;
					vy+=j;
					disk[vx][vy].color=color;	//reverse
				}while(disk[vy+i][vx+j].color!=color);	//同じ色の石が見つかるまで
				vx=cx;	//置いた場所に戻る
				vy=cy;
			}
		}
	}
}
bool Othello::CanPut(bool color){
	bool state=false;	//コードを短くするためだけの変数
	bool putable=false;	//戻す用変数
	for(signed int x=0;x<8;x++){
		for(signed int y=0;y<8;y++){
			if(disk[x][y].onboard == true)state=false;
			else{
				state=(
                       line(color,x,y,+1, 0)||
                       line(color,x,y,+1,+1)||
                       line(color,x,y, 0,+1)||
                       line(color,x,y,-1,+1)||
                       line(color,x,y,-1, 0)||
                       line(color,x,y,-1,-1)||
                       line(color,x,y, 0,-1)||
                       line(color,x,y,+1,-1)
                       );
			}
			disk[x][y].putable[color]=state;
			if(state)putable=true;	//置ける場所が一つでもあれば置ける。
		}
	}
	return putable;
}

void Othello::init(){
	/* 初期設定 */
	//gameover=false;
	stat=READY;
	mode=P2P;
	
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			disk[m][n].x=m;
			disk[m][n].y=n;
			disk[m][n].onboard=false;
			disk[m][n].color=false;
		}
	}
	disk[3][3].onboard=true;
	disk[4][3].onboard=true;
	disk[3][4].onboard=true;
	disk[4][4].onboard=true;
    
	disk[3][4].color=WHITE;
	disk[4][3].color=WHITE;
    
	CanPut(BLACK);
	turn=BLACK;
	cursor.x=cursor.y=time1=time2=0;
	num_disk[0]=num_disk[1]=0;
    
}



#ifdef OOP
//static なメンバ関数しか呼び出せない
int main(int argc, char **argv){
	Othello *othelo = new Othello();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	
	Othello::CreateWindow(0,800,0,600,"othello");

	glClearColor( 0 , 0.7, 0, 1);//back ground color
	glutDisplayFunc(Othello::display);
	glutKeyboardFunc(Othello::key);
	glutPassiveMotionFunc(Othello::mouse);
	glutMouseFunc(Othello::mousebotton);
	glutTimerFunc(0,Othello::timer,100);
    
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
	glutTimerFunc(0,timer,10);
    
	glutMainLoop();
	return 0;
}
#endif