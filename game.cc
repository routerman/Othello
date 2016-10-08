#include "game.h"

/* mouse motion */
void Game::mouse_motion(I2 point){
	I2 cursor=cursor_adjust(point);
	if( player_mode[turn]==HUMAN ){
		cursor_square.set(cursor.x/60-1,cursor.y/60-1);		
	}
}

/* mouse click */
void Game::mouse_click(int state ,int button, I2 point){
	if(  state != GLUT_DOWN ||  button != GLUT_LEFT_BUTTON  )return;

	I2 cursor=cursor_adjust(point);

	//board.button_proc(stat,cursor);
    if( play_button.isPushed(cursor) ){
        if( stat == READY )stat=PLAY;
        else if( stat == PLAY )stat=PAUSE;
        else if( stat == PAUSE )stat=PLAY;
        play_button.selectLabel(stat);
        if( stat == READY )reset_button.setActive(true);
        else reset_button.setActive(false);
    }

	if( undo_button.isPushed(cursor) ){
		undo();
	}

	if( reset_button.isPushed(cursor) ){
		this->history.clear();
		delete game;
		game = new Game;
	}

	if( stat==READY ){
		if( player_button[BLACK].isPushed(cursor) ){
			player_mode[BLACK]=static_cast<PlayerMode>( player_mode[BLACK] + 1 );
			if( player_mode[BLACK] >  ROUTERMAN )player_mode[BLACK]=HUMAN;
			if( player_mode[BLACK] == AGENT     )machine[BLACK] =new Agent(BLACK);
			if( player_mode[BLACK] == ROUTERMAN )machine[BLACK] =new Routerman(BLACK);
			player_button[BLACK].selectLabel(player_mode[BLACK]);
		}
		if( player_button[WHITE].isPushed(cursor) ){
			player_mode[WHITE]=static_cast<PlayerMode>( player_mode[WHITE] + 1 );
			if( player_mode[WHITE] >  ROUTERMAN )player_mode[WHITE]=HUMAN;
			if( player_mode[WHITE] == AGENT     )machine[WHITE] =new Agent(WHITE);
			if( player_mode[WHITE] == ROUTERMAN )machine[WHITE] =new Routerman(WHITE);
			player_button[WHITE].selectLabel(player_mode[WHITE]);
		}
	}

	//diskを置く
	if( player_mode[turn]==HUMAN ){
		cursor_square.set(cursor.x/60-1,cursor.y/60-1);		
		proc();
	}
	glutPostRedisplay();
}

/* time event */
void Game::timer(int dt){
	//グローバルタイム
	if( stat == PLAY ){
		global_time++;
		sub_time++;
		if( sub_time>30 && player_mode[turn] != HUMAN ){
			machine[turn]->setOthello(*othello);
			machine[turn]->select();
			cursor_square=machine[turn]->getCursor();
			proc();
		}
	}
	glutPostRedisplay();
}

void Game::proc(){
	sub_time=0;
	if( stat != PLAY )return;

	if( cursor_square.isOnboard() == false )return;

	if( othello->isPutable(turn,cursor_square) == false )return;

	//save current state for UNDO function
	history.push_back(*othello);

	before_square[turn]=cursor_square;

	othello->put_disk(turn,cursor_square);

	//othello->reverse(turn,cursor_square);

	if(	othello->isAnyPutable(!turn) ){
		turn = !turn;
	}

	if( othello->isAnyPutable(turn) == false ){
		stat=GAMEOVER;
		result = othello->judge();
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

	othello->draw_disks(turn);

	/* オセロライン */
    glColor3f(0,0,0);
    for(int i=1;i<=9;i++){
        GL::DrawLine(2,60*i,60,60*i,540);//縦
        GL::DrawLine(2,60,60*i,540,60*i);//横
    }
    GL::DrawPoint(8,180,180);
    GL::DrawPoint(8,180,420);
    GL::DrawPoint(8,420,180);
    GL::DrawPoint(8,420,420);

    	/* ガジェット */
    //Line
    glLineWidth(7);
    glBegin(GL_LINES);
    glColor3f(0,0,0);
    glVertex2i(570,0);
    glColor3f(1,1,1);
    glVertex2i(570,600);
    glEnd();

    //時計
    GL::DrawWatch(700,100,global_time/60);

	//ボタン
	player_button[BLACK].draw();
	player_button[WHITE].draw();
	play_button.draw();
	undo_button.draw();
	reset_button.draw();

	if( stat == PLAY ){
		/* カーソル */
		if(turn==WHITE)glColor3f(1,1,1);
		else glColor3f(0,0,0);
		if( cursor_square.isOnboard() && othello->isPutable(turn,cursor_square) )DrawCircle(90+cursor_square.x*60,90+cursor_square.y*60);
	}else if( stat == GAMEOVER ){
		result_message();
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

I2 Game::cursor_adjust(I2 point){
	//cursor_square.set(cursor.x/(60*ration)-1,cursor.y/(60*ration)-1);
	return I2(point.x/ration, point.y/ration-calib);
}

void Game::reshape(GLsizei width, GLsizei height){
	this->width=width;
	this->height=height;
	if( width > height*4/3 ){
		ration=(double)height/600;
		glViewport( 0, 0, height*4/3, height );
	}else{
		ration=(double)width/800;
		calib=height-600*ration;
		glViewport( 0, 0, width, width*3/4 );
	}
}

void Game::undo(){
	if(this->history.size() > 1){
		this->history.pop_back();
	   *this->othello = this->history.back();
		this->history.pop_back();
	}
}

void Game::result_message(){
	/* ゲーム終了 */
	int num_disk[2];
	num_disk[BLACK] = result.x;
	num_disk[WHITE] = result.y;

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
	global_time=0;
	sub_time=0;
	result.set(0,0);

	//Disk
    othello = new Othello();
	history.push_back(*othello);

	cursor_square.set(-1,-1);
	before_square[WHITE].set(-1,-1);
	before_square[BLACK].set(-1,-1);

	//button
	player_button[BLACK].set(590,790,200,260,0.1,0.1,0.1);
	player_button[BLACK].setstring("1P : Human","1P : Agent","1P : Routerman");
	player_button[WHITE].set(590,790,280,340,0.9,0.9,0.9);
	player_button[WHITE].setstring("2P : Human","2P : Agent","2P : Routerman");
	play_button.set(590,790,390,450,0.7,0.7,0.7);
	play_button.setstring("Play","Pause","Continue");
	undo_button.set(590,790,460,520,0.7,0.7,0.7);
	undo_button.setstring("Undo","","");
	reset_button.set(590,790,530,590,0.7,0.7,0.7);
	reset_button.setstring("Reset","","");
	reset_button.setActive(true);
}
