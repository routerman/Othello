#include "Othello.hpp"
Othello *othello;


/* mouse motion */
void Othello::mouse(int cx,int cy){
	//人間は自分のターンではないときはカーソルを動かさない。
	if( ( mode==P2M && turn==BLACK ) || ( mode==M2P && turn==WHITE ) || ( mode==P2P ) ){
		cursor.set(cx/(60*ration)-1,cy/(60*ration)-1);		
	}
}
/* mouse click */
void Othello::mousebotton(int state ,int button, int cx,int cy){
	if(  state != GLUT_DOWN ||  button != GLUT_LEFT_BUTTON  )return;
	if( play.isPushed(cx,cy) ){
		if( stat == READY )stat=PLAY;
		else if( stat == PLAY )stat=PAUSE;
		else if( stat == PAUSE )stat=PLAY;
		play.selectLabel(stat);
	}else if( reset.isPushed(cx,cy) ){
		delete othello;
		othello = new Othello;
	}
	if( ( ( mode==P2M && turn==BLACK ) || ( mode==M2P && turn==WHITE) || ( mode==P2P ) ) && ( stat == PLAY )){	
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
	if(subtime<100)return;
	if( ( ( mode==P2M && turn==WHITE ) || ( mode==M2P && turn==BLACK) || ( mode==M2M ) ) && ( stat == PLAY )){
		//machine[turn]->setDisk(disk);
		//machine[turn]->select();
		//cursor=machine[turn]->getCursor();
		
		if( cpu==AGENT ){
			agent.setDisk(disk);
			agent.select();
			cursor=agent.getCursor();
		}else if( cpu==ROUTERMAN ){
			routerman.setDisk(disk);
			routerman.select();
			cursor=routerman.getCursor();
		}else if( ( cpu==A2R && turn==BLACK ) || ( cpu==R2A && turn==WHITE )){
			agent.setDisk(disk);
			agent.select();
			cursor=agent.getCursor();
		}else if( ( cpu==A2R && turn==WHITE ) || ( cpu==R2A && turn==BLACK )){
			routerman.setDisk(disk);
			routerman.select();
			cursor=routerman.getCursor();
		}
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
        case 127: /* delete */
			delete othello;
			othello = new Othello;
            break;
        case 13: /* ENTER */
            if( stat == READY )stat=PLAY;
            break;
        case 'q':
            stat=GAMEOVER;
            break;
        case 'p':	//ポーズ
            if(stat==PLAY)stat=PAUSE;
			else if(stat==PAUSE)stat=PLAY;

            break;
        case 'm':	//playmode切り替え
            if( stat!=READY )break;
			mode = static_cast<Mode>(mode + 1);
			if(mode>M2M)mode=P2P;
			if(mode==P2P){
				cpu=NON;
			}else if( mode==P2M || mode==M2P){
				cpu=AGENT;
			}else if( mode==M2M ){
				cpu=A2R;
			}
			break;
        case 'c':	//computer切り替え
            if( stat!=READY )break;
			cpu = static_cast<Cpu>(cpu + 1);
			if(mode==P2P){
				cpu=NON;
			}else if( mode==P2M || mode==M2P){
				if( cpu>ROUTERMAN )cpu=AGENT;
			}else if( mode==M2M ){
				if( cpu>R2A )cpu=A2R;
			}
            break;
        default:
            break;
	}
	std::cout<<mode<<","<<cpu<<std::endl;
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
	player1.drow();
	player2.drow();
	play.drow();
	//undo.drow();
	reset.drow();

	board.drow(mode,stat,cpu,time1);
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
		DrawString(130,340,"Press Enter to start GAME!");
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

	turn=BLACK;
	time1=subtime=0;
	num_disk[BLACK]=num_disk[WHITE]=0;
	cursor.set(-2,-2);
	before.set(-2,-2);

	if( mode==P2M){
		agent.setColor(WHITE);
		routerman.setColor(WHITE);
	}else if( mode==M2P ){
		agent.setColor(BLACK);
		routerman.setColor(BLACK);
	}else if( mode==M2M && cpu==A2R ){
		agent.setColor(BLACK);   
		routerman.setColor(WHITE);
	}else if( mode==M2M && cpu==R2A ){
		routerman.setColor(BLACK);
		agent.setColor(WHITE);   
	}
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
	mode=P2M;
	cpu=AGENT;
	ration=1;
	init();
	player1.set(590,790,200,260,0.1,0.1,0.1);
	player1.setstring("1P : Human","1P : Agent","1P : Routerman");
	player2.set(590,790,280,340,0.9,0.9,0.9);
	player2.setstring("2P : Human","2P : Agent","2P : Routerman");
	play.set(590,790,390,450,0.7,0.7,0.7);
	play.setstring("Ready","Play","Pause");
	//undo.set(590,790,460,520,0.7,0.7,0.7);
	//undo.setstring("UNDO","","");
	reset.set(590,790,530,590,0.7,0.7,0.7);
	reset.setstring("Reset","","");
	//p1=&agent;
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