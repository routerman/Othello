#include "game.h"


/* mouse motion */
void Game::mouse(int cx,int cy){
	/* 位置情報を補正してcursorに代入。cursorからcursor_squareを求める。 */
	//補正関数()
	cursor_adjust(cx,cy);
	//std::cout<<cursor.x<<","<<cursor.y<<"ration="<<ration<<std::endl;
	//人間は自分のターンではないときはカーソルを動かさない
	if( player_mode[turn]==HUMAN ){
		//cursor_square.set(cursor.x/(60*ration)-1,cursor.y/(60*ration)-1);		
		cursor_square.set(cursor.x/60-1,cursor.y/60-1);		
	}
}
/* mouse click */
void Game::mousebotton(int state ,int button, int cx,int cy){
	if(  state != GLUT_DOWN ||  button != GLUT_LEFT_BUTTON  )return;
	//補正関数()
	cursor_adjust(cx,cy);
	

	//ボタン
	board.button_proc(stat,cursor);
	if( board.undo.isPushed(cursor) ){
		undo(turn);
	}else if( board.reset.isPushed(cursor) ){
		int w = this->width;
		int h = this->height;
		delete game;
		game = new Game;
		reshape(w,h);
	}

	bool color=BLACK;
	do{
		if( board.player[color].isPushed(cursor) && stat==READY ){
			player_mode[color]=static_cast<PlayerMode>( player_mode[color] + 1 );
			if( player_mode[color] > ROUTERMAN )player_mode[color]=HUMAN;		
			if( player_mode[color] == AGENT )machine[color] =new Agent(color);
			else if( player_mode[color] == ROUTERMAN )machine[color] =new Routerman(color);
			board.player[color].selectLabel(player_mode[color]);
			//machine[color]->setColor(color);
		}
	}while(color=!color, color==WHITE);//BLACK,WHITEの2つだけ。

	//diskを置く
	if( player_mode[turn]==HUMAN ){
		cursor_square.set(cursor.x/60-1,cursor.y/60-1);		
		Proc();
	}
	glutPostRedisplay();
}
/* time event */
void Game::timer(int dt){
	//グローバルタイム
	if( stat == PLAY ){
		time1++;
		subtime++;
	}
	if( subtime>30 && player_mode[turn] != HUMAN  && stat==PLAY ){
		machine[turn]->setDisk(othello->disk);
		machine[turn]->select();
		cursor_square=machine[turn]->getCursor();
		Proc();
	}
	glutPostRedisplay();
}

//石を置く際の共通処理
void Game::Proc(){
	//出番のアクセス制御
	//アクセス制御
	subtime=0;
	if( stat != PLAY )return;
	//置ける場所かどうか
	if( cursor_square.isOnboard()==false || othello->disk[cursor_square.x][cursor_square.y].isPutable(turn) == false )return;
	//置く前にUNDO用に保存する
	save(turn);
	before_square[turn]=cursor_square;

	//石を置く
	othello->disk[cursor_square.x][cursor_square.y].place(turn);

	//リバースする
	reverse(turn,cursor_square);
	
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
					if( othello->disk[i][j].isOnboard() ){
						num_disk[othello->disk[i][j].getColor()]++;
					}
				}
			}
		}
	}
}

//キー入力
void Game::key(unsigned char k, int x, int y){
	switch (k) {
        case 27:  /* Escape */
            exit(0);
            break;
        default:
            break;
	}
	glutPostRedisplay();
}

void Game::display(void){
	/* Before Draw */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if( stat == PLAY ){
		/* 置いた場所 */
		glColor3f(1,0,0);
		DrawSquare(60*(before_square[!turn].x+1),60*(before_square[!turn].y+1));
	}
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			othello->disk[i][j].draw(turn);
		}
	}
	//ボタン
	board.player[BLACK].draw();
	board.player[WHITE].draw();
	board.play.draw();
	board.undo.draw();
	board.reset.draw();

	board.draw(time1);
	if( stat == PLAY ){
		/* カーソル */
		if(turn==WHITE)glColor3f(1,1,1);
		else glColor3f(0,0,0);
		if( cursor_square.isOnboard() && othello->disk[cursor_square.x][cursor_square.y].isPutable(turn) )DrawCircle(90+cursor_square.x*60,90+cursor_square.y*60);
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
		if( player_mode[BLACK]!=HUMAN && player_mode[WHITE]!=HUMAN ){
			int w = this->width;
			int h = this->height;
			delete game;
			game = new Game;
			reshape(w,h);
			player_mode[BLACK]=AGENT;
			player_mode[WHITE]=ROUTERMAN;
		}

	}else if( stat == READY ){
		/* モード設定 */
		/*
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
		*/
	}
	/* After Draw */
	glutSwapBuffers();
}

void Game::reverseLine(bool color,I2 r,I2 d){
    do{
		r+=d;
		othello->disk[r.x][r.y].setColor(color);
	}while(othello->disk[r.x+d.x][r.y+d.y].getColor()!=color && r.isOnboard() );
}

void Game::reverse(bool color,I2 position){
    if( checkLine(color,position,I2( 0, 1)) ) reverseLine(color,position,I2( 0, 1));
    if( checkLine(color,position,I2( 1, 1)) ) reverseLine(color,position,I2( 1, 1));
    if( checkLine(color,position,I2( 1, 0)) ) reverseLine(color,position,I2( 1, 0));
    if( checkLine(color,position,I2( 1,-1)) ) reverseLine(color,position,I2( 1,-1));
    if( checkLine(color,position,I2( 0,-1)) ) reverseLine(color,position,I2( 0,-1));
    if( checkLine(color,position,I2(-1,-1)) ) reverseLine(color,position,I2(-1,-1));
    if( checkLine(color,position,I2(-1, 0)) ) reverseLine(color,position,I2(-1, 0));
    if( checkLine(color,position,I2(-1, 1)) ) reverseLine(color,position,I2(-1, 1));
}


/* Is there any square to place? */
bool Game::isAnyPutable(bool color){
	for(int x=0;x<8;x++){
		for(int y=0;y<8;y++){
			if( othello->disk[x][y].isPutable(color) )return true;
		}
	}
	return false;
}

/* その方向に対してリバースできるか */
bool Game::checkLine(bool color,I2 r,I2 d){
	if( d.x==0 && d.y==0 )return false;
	r+=d;
	//while(異色の石が存在 && 盤内)
	while(  othello->disk[r.x][r.y].getColor() != color && othello->disk[r.x][r.y].isOnboard() && r.isOnboard() ){
		r+=d;
		if( othello->disk[r.x][r.y].getColor() == color && othello->disk[r.x][r.y].isOnboard() && r.isOnboard() )return true;
	}
	return false;
}

/* Analyze a square which can be putable. */
bool Game::checkPutable(bool color,I2 position){
	if( othello->disk[position.x][position.y].isOnboard() )return false;
    if( checkLine(color,position,I2( 0, 1)) ) return true;
    if( checkLine(color,position,I2( 1, 1)) ) return true;
    if( checkLine(color,position,I2( 1, 0)) ) return true;
    if( checkLine(color,position,I2( 1,-1)) ) return true;
    if( checkLine(color,position,I2( 0,-1)) ) return true;
    if( checkLine(color,position,I2(-1,-1)) ) return true;
    if( checkLine(color,position,I2(-1, 0)) ) return true;
    if( checkLine(color,position,I2(-1, 1)) ) return true;
	return false;
}

/* Check all square in board, and set putable value each square. */
void Game::ScanPutable(bool color){
	for(int x=0;x<8;x++){
		for(int y=0;y<8;y++){
			othello->disk[x][y].setPutable(color, checkPutable(color,I2(x,y)) );
		}
	}
}

/* ゲーム単位の初期設定 */
void Game::init(){

}

/* Construct with coping all disks infomation */
Game::Game( Disk disk[][8] ){
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			this->othello->disk[m][n]=disk[m][n];
		}
	}
}

/* 起動後、最初に呼び出される。*/
Game::Game(){
	//game init
	stat=READY;
	player_mode[BLACK]=HUMAN;
	player_mode[WHITE]=HUMAN;

	machine[BLACK] = new Machine;
	machine[WHITE] = new Machine;
	machine[BLACK]->setColor(BLACK);
	machine[WHITE]->setColor(WHITE);
	ration=1;
	calib=0;
	turn=BLACK;
	time1=subtime=0;
	num_disk[BLACK]=num_disk[WHITE]=0;
	init();
	//Disk
    othello = new Othello();
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			othello->disk[m][n].init_postion(m,n);
			othello->disk[m][n].setOnboard(false);
			othello->disk[m][n].setColor(BLACK);
		}
	}
	othello->disk[3][3].place(BLACK);
	othello->disk[4][3].place(WHITE);
	othello->disk[3][4].place(WHITE);
	othello->disk[4][4].place(BLACK);
	ScanPutable(BLACK);
	ScanPutable(WHITE);
	save(BLACK);
	save(WHITE);
	cursor_square.set(-2,-2);
	before_square[WHITE].set(-2,-2);
	//button
	board.player[BLACK].set(590,790,200,260,0.1,0.1,0.1);
	board.player[BLACK].setstring("1P : Human","1P : Agent","1P : Routerman");
	board.player[WHITE].set(590,790,280,340,0.9,0.9,0.9);
	board.player[WHITE].setstring("2P : Human","2P : Agent","2P : Routerman");
	board.play.set(590,790,390,450,0.7,0.7,0.7);
	board.play.setstring("Play","Pause","Continue");
	board.undo.set(590,790,460,520,0.7,0.7,0.7);
	board.undo.setstring("Undo","","");
	board.reset.set(590,790,530,590,0.7,0.7,0.7);
	board.reset.setstring("Reset","","");
	board.reset.setActive(true);
}
