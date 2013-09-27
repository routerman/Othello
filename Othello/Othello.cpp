#include "Othello.hpp"
Othello *othello;


/* mouse motion */
void Othello::mouse(int cx,int cy){
	//人間は自分のターンではないときはカーソルを動かさない
	if( playermode[turn]==HUMAN ){
		cursor.set(cx/(60*ration)-1,cy/(60*ration)-1);		
	}
}
/* mouse click */
void Othello::mousebotton(int state ,int button, int cx,int cy){
	if(  state != GLUT_DOWN ||  button != GLUT_LEFT_BUTTON  )return;
	//ボタン
	if( board.play.isPushed(cx,cy) ){
		if( stat == READY )stat=PLAY;
		else if( stat == PLAY )stat=PAUSE;
		else if( stat == PAUSE )stat=PLAY;
		board.play.selectLabel(stat);
	}else if( board.reset.isPushed(cx,cy) ){
		delete othello;
		othello = new Othello;
	}
	bool color=BLACK;
	do{
		if( board.player[color].isPushed(cx,cy) && stat==READY ){
			playermode[color]=static_cast<PlayerMode>( playermode[color] + 1 );
			if( playermode[color] > ROUTERMAN )playermode[color]=HUMAN;		
			if( playermode[color] == AGENT )machine[color] =new Agent(color);
			else if( playermode[color] == ROUTERMAN )machine[color] =new Routerman(color);
			board.player[color].selectLabel(playermode[color]);
			//machine[color]->setColor(color);
		}
	}while(color=!color, color==WHITE);//BLACK,WHITEの2つだけ。
	//diskを置く
	if( playermode[turn]==HUMAN ){
		Proc();
	}
	glutPostRedisplay();
}
/* time event */
void Othello::timer(int dt){
	//グローバルタイム
	if( stat == PLAY ){
		time1++;
		subtime++;
	}
	if( subtime>10 && playermode[turn] != HUMAN  && stat==PLAY ){
		machine[turn]->setDisk(disk);
		machine[turn]->select();
		cursor=machine[turn]->getCursor();
		Proc();
	}
	glutPostRedisplay();
}

//石を置く際の共通処理
void Othello::Proc(){
	//出番のアクセス制御
	//アクセス制御
	subtime=0;
	if( stat != PLAY )return;
	//置ける場所かどうか
	if( cursor.isOnboard()==false || disk[cursor.x][cursor.y].isPutable(turn) == false )return;
	//石を置く
	disk[cursor.x][cursor.y].place(turn);
	before=cursor;
	//リバースする
	reverse(turn,cursor);
	
	//敵が置けるかチェック
	if(	ScanPutable(!turn),isAnyPutable(!turn) ){
		turn=!turn;	//交代
	}else{
		//敵が置けない場合自分に戻る
		ScanPutable(turn);
		if( isAnyPutable(turn) == false ){
			//自分も置けない場合は終了
			stat=GAMEOVER;
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					if( disk[i][j].isOnboard() ){
						num_disk[disk[i][j].getColor()]++;
					}
				}
			}
		}
	}
}

//キー入力
void Othello::key(unsigned char k, int x, int y){
	switch (k) {
        case 27:  /* Escape */
            exit(0);
            break;
        default:
            break;
	}
	glutPostRedisplay();
}

void Othello::display(void){
	/* Before Draw */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if( stat == PLAY ){
		/* 置いた場所 */
		glColor3f(1,0,0);
		DrawSquare(60*(before.x+1),60*(before.y+1));
	}
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			disk[i][j].drow(turn);
		}
	}
	//ボタン
	board.player[BLACK].drow();
	board.player[WHITE].drow();
	board.play.drow();
	//undo.drow();
	board.reset.drow();

	board.drow(time1);
	if( stat == PLAY ){
		/* カーソル */
		if(turn==WHITE)glColor3f(1,1,1);
		else glColor3f(0,0,0);
		if( cursor.isOnboard() && disk[cursor.x][cursor.y].isPutable(turn) )DrawCircle(90+cursor.x*60,90+cursor.y*60);
	}else if( stat == GAMEOVER ){
		/* ゲーム終了 */
		if( num_disk[BLACK] <= num_disk[WHITE] ){
			glColor3f(1,1,1);
		}else if(num_disk[BLACK] > num_disk[WHITE] ){
			glColor3f(0,0,0);
		}
		glBegin(GL_QUADS);
		glVertex2i(100,340);
		glVertex2i(100,260);
		glVertex2i(500,260);
		glVertex2i(500,340);
		glEnd();
		message.str("");
		if( num_disk[BLACK] <= num_disk[WHITE] ){
			message << "white=" << num_disk[WHITE] << ",black=" << num_disk[BLACK] << "WHITE WIN!";
			glColor3f(0,0,0);
		}else if(num_disk[BLACK] > num_disk[WHITE] ){
			message << "white=" << num_disk[WHITE] << ",black=" << num_disk[BLACK] << "BLACK WIN!";
			glColor3f(1,1,1);
		}
		DrawString(130,300,message.str());
	}else if( stat == READY ){
		/* モード設定 */
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
		glVertex2i(100,360);
		glVertex2i(100,280);
		glVertex2i(500,280);
		glVertex2i(500,360);
		glEnd();
		glColor3f(0,0,0);
		DrawString(130,310,"Press 'm' and choose gamemode,");
		DrawString(130,340,"Press 'Play' to start GAME!");
	}
	/* After Draw */
	glutSwapBuffers();
}

void Othello::reverse(bool color,I2 position){
	I2 hand=position;
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			I2 temp(i,j);
			if( checkLine(color,position,temp) ){	//reverse可
				do{
					hand+=temp;
					disk[hand.x][hand.y].setColor(color);	//reverse
				}while(disk[hand.x+temp.x][hand.y+temp.y].getColor()!=color && hand.isOnboard() );	//同じ色の石が見つかるまで
				hand=position;	//置いた場所に戻る
			}
		}
	}
}


/* Is there any square to place? */
bool Othello::isAnyPutable(bool color){
	for(int x=0;x<8;x++){
		for(int y=0;y<8;y++){
			if( disk[x][y].isPutable(color) )return true;
		}
	}
	return false;
}

/* その方向に対してリバースできるか */
bool Othello::checkLine(bool color,I2 r,I2 d){
	if( d.x==0 && d.y==0 )return false;
	r+=d;
	//while(異色の石が存在 && 盤内)
	while(  disk[r.x][r.y].getColor() != color && disk[r.x][r.y].isOnboard() && r.isOnboard() ){
		r+=d;
		if( disk[r.x][r.y].getColor() == color && disk[r.x][r.y].isOnboard() && r.isOnboard() )return true;
	}
	return false;
}

/* Analyze a square which can be putable. */
bool Othello::checkPutable(bool color,I2 position){
	if( disk[position.x][position.y].isOnboard() )return false;
	else{
		for(int i=-1;i<=1;i++){
			for(int j=-1;j<=1;j++){
				I2 direction(i,j);
				if( checkLine(color,position,direction) )return true;
			}
		}
	}
	return false;
}

/* Check all square in board, and set putable value each square. */
void Othello::ScanPutable(bool color){
	for(int x=0;x<8;x++){
		for(int y=0;y<8;y++){
			//disk[x][y].checkPutable(color);
			I2 position(x,y);
			disk[position.x][position.y].setPutable(color, checkPutable(color,position) );
		}
	}
}

/* ゲーム単位の初期設定 */
void Othello::init(){
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			disk[m][n].init_postion(m,n);
			disk[m][n].setOnboard(false);
			disk[m][n].setColor(BLACK);
		}
	}
	disk[3][3].place(BLACK);
	disk[4][3].place(WHITE);
	disk[3][4].place(WHITE);
	disk[4][4].place(BLACK);
	ScanPutable(BLACK);
	ScanPutable(WHITE);

	turn=BLACK;
	time1=subtime=0;
	num_disk[BLACK]=num_disk[WHITE]=0;
	cursor.set(-2,-2);
	before.set(-2,-2);
}

/* Construct with coping all disks infomation */
Othello::Othello( Disk disk[][8] ){
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			this->disk[m][n]=disk[m][n];
		}
	}
}

/* 起動後、最初に呼び出される。*/
Othello::Othello(){
	stat=READY;
	playermode[BLACK]=HUMAN;
	playermode[WHITE]=HUMAN;
	machine[BLACK] = new Machine;
	machine[WHITE] = new Machine;
	machine[BLACK]->setColor(BLACK);
	machine[WHITE]->setColor(WHITE);
	ration=1;
	subtime=0;
	init();
	board.player[BLACK].set(590,790,200,260,0.1,0.1,0.1);
	board.player[BLACK].setstring("1P : Human","1P : Agent","1P : Routerman");
	board.player[WHITE].set(590,790,280,340,0.9,0.9,0.9);
	board.player[WHITE].setstring("2P : Human","2P : Agent","2P : Routerman");
	board.play.set(590,790,390,450,0.7,0.7,0.7);
	board.play.setstring("Ready","Play","Pause");
	//board.undo.set(590,790,460,520,0.7,0.7,0.7);
	//board.undo.setstring("Undo","","");
	board.reset.set(590,790,530,590,0.7,0.7,0.7);
	board.reset.setstring("Reset","","");
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

void display(void){othello->display();}
void mousebotton(int state ,int button, int cx,int cy){othello->mousebotton(state,button,cx,cy);}
void mouse(int cx,int cy){othello->mouse(cx,cy);}
void key(unsigned char k, int x, int y){othello->key(k,x,y);}
void timer(int dt){
	othello->timer(dt);
	glutTimerFunc(dt,timer,10);
}
void reshape(GLsizei width, GLsizei height){othello->reshape(width,height);}
 

int main(int argc, char **argv){
	othello = new Othello;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	othello->CreateWindow(0,800,600,0,"othello");
	glClearColor( 0 , 0.7, 0, 1);//back ground color
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mousebotton);
	glutTimerFunc(0,timer,10);
    
	glutMainLoop();
	delete othello;
	return 0;
}
#endif