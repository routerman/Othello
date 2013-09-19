#include "Othello.hpp"

void Othello::mousebotton(int state ,int button, int cx,int cy){
	if(  state != GLUT_DOWN ||  button != GLUT_LEFT_BUTTON  )return;
	if( ( ( mode==P2M && turn==BLACK ) || ( mode==M2P && turn==WHITE) || ( mode==P2P ) ) && ( stat == PLAY )){	
		Proc();
	}
	glutPostRedisplay();
}

void Othello::timer(int dt){
	//�O���[�o���^�C��
	if( stat == PLAY ){
		time1++;
		subtime++;
	}
	if(subtime<100)return;
	if( ( ( mode==P2M && turn==WHITE ) || ( mode==M2P && turn==BLACK) || ( mode==M2M ) ) && ( stat == PLAY )){
		if( cpu==AGENT ){
			agent.select(cursor,disk);
		}else if( cpu==ROUTERMAN ){
			routerman.select(cursor,disk);
		}else if( ( cpu==A2R && turn==BLACK ) || ( cpu==R2A && turn==WHITE )){
			agent.select(cursor,disk);
		}else if( ( cpu==A2R && turn==WHITE ) || ( cpu==R2A && turn==BLACK )){
			routerman.select(cursor,disk);
		}
		Proc();
	}
	glutPostRedisplay();
}


//�΂�u���ۂ̋��ʏ���
void Othello::Proc(){
	//�o�Ԃ̃A�N�Z�X����
	//�u����ꏊ���ǂ���
	//�A�N�Z�X����
	subtime=0;
	if( stat != PLAY )return;
	if( disk[cursor.x][cursor.y].putable[turn] == false )return;
	//�΂�u��
	disk[cursor.x][cursor.y].place(turn);
	before.x=cursor.x;
	before.y=cursor.y;
	//���o�[�X����
	reverse(turn,cursor.x,cursor.y);
	//�G���u���邩�`�F�b�N
	if( CanPut(!turn) ){
		turn=!turn;	//���
	}else if( !CanPut(turn) ){	//�������u���Ȃ��ꍇ�͏I��
		stat=GAMEOVER;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if( disk[i][j].isOnboard() ){
					num_disk[disk[i][j].color]++;
				}
			}
		}
	}
}

//�}�E�X�̓���
void Othello::mouse(int cx,int cy){
	//�l�Ԃ͎����̃^�[���ł͂Ȃ��Ƃ��̓J�[�\���𓮂����Ȃ��B
	if( ( mode==P2M && turn==BLACK ) || ( mode==M2P && turn==WHITE ) || ( mode==P2P ) ){
		cursor.x=cx/60-1;
		cursor.y=cy/60-1;
	}
}

void Othello::key(unsigned char k, int x, int y){
	switch (k) {
        case 27:  /* Escape */
            exit(0);
            break;
        case 127: /* delete */
            init();
			stat=READY;
            break;
        case 13: /* ENTER */
            if( stat == READY ){
				init();
				stat=PLAY;
			}
            break;
        case 'q':
            stat=GAMEOVER;
            break;
        case 'p':	//�|�[�Y
            if(stat==PLAY)stat=POSE;
			else if(stat==POSE)stat=PLAY;

            break;
        case 'm':	//playmode�؂�ւ�
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
        case 'c':	//computer�؂�ւ�
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
		/* �u�����ꏊ */
		glColor3f(1,0,0);
		DrawSquare(60*(before.x+1),60*(before.y+1));
	}
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			disk[i][j].drow(turn);
		}
	}
	board.drow(mode,stat,cpu,time1);
	if( stat == PLAY ){
		/* �J�[�\�� */
		if(turn==WHITE)glColor3f(1,1,1);
		else glColor3f(0,0,0);
		if( cursor.isOnboard() && disk[cursor.x][cursor.y].putable[turn] )DrawCircle(90+cursor.x*60,90+cursor.y*60);
	}else if( stat == GAMEOVER ){
		/* �Q�[���I�� */
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
		/* ���[�h�ݒ� */
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

bool Othello::line(bool color,int x,int y,int dx,int dy){
	x+=dx;
	y+=dy;
	//while(�ِF�̐΂����� && �Փ�)
	while( disk[x][y].color!=color && disk[x][y].isOnboard() && ( x>=0 && x<=7 ) && ( y>=0 && y<=7 ) ){
		x+=dx;
		y+=dy;
		if( disk[x][y].color==color && disk[x][y].isOnboard() && ( x>=0 && x<=7 ) && ( y>=0 && y<=7 ) )return true;
	}
	return false;
}

void Othello::reverse(bool color,int cx ,int cy){
	I2 vector(cx,cy);
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if( line(color,cx,cy,i,j) ){	//reverse��
				do{
					vector.x+=i;
					vector.y+=j;
					disk[vector.x][vector.y].color=color;	//reverse
				}while(disk[vector.x+i][vector.y+j].color!=color && vector.isOnboard() );	//�����F�̐΂�������܂�
				vector.x=cx;	//�u�����ꏊ�ɖ߂�
				vector.y=cy;
			}
		}
	}
}

bool Othello::CanPut(bool color){
	bool state=false;	//�R�[�h��Z�����邽�߂����̕ϐ�
	bool putable=false;	//�߂��p�ϐ�
	for(signed int x=0;x<8;x++){
		for(signed int y=0;y<8;y++){
			if(disk[x][y].isOnboard())state=false;
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
			if(state)putable=true;	//�u����ꏊ����ł�����Βu����B
		}
	}
	return putable;
}

/* �Q�[���P�ʂ̏����ݒ� */
void Othello::init(){
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			disk[m][n].x=m;
			disk[m][n].y=n;
			disk[m][n].onboard=false;
			disk[m][n].color=false;
		}
	}
	disk[3][3].place(BLACK);
	disk[4][3].place(WHITE);
	disk[3][4].place(WHITE);
	disk[4][4].place(BLACK);
	CanPut(BLACK);

	turn=BLACK;
	time1=subtime=0;
	num_disk[0]=num_disk[1]=0;
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

	if( cpu==AGENT ){
		agent.select(cursor,disk);
	}else if( cpu==ROUTERMAN ){
		routerman.select(cursor,disk);
	}else if( ( cpu==A2R && turn==BLACK ) || ( cpu==R2A && turn==WHITE )){
		agent.select(cursor,disk);
	}else if( ( cpu==A2R && turn==WHITE ) || ( cpu==R2A && turn==BLACK )){
		routerman.select(cursor,disk);
	}

}


Othello::Othello( Disk disk[][8] ){
	for(int m=0;m<8;m++){
		for(int n=0;n<8;n++){
			this->disk[m][n]=disk[m][n];
		}
	}
}

/* �N����A�ŏ��ɌĂяo�����B*/
Othello::Othello(){
	stat=READY;
	mode=P2M;
	cpu=AGENT;
}



#ifdef OOP
//static �ȃ����o�֐������Ăяo���Ȃ�
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

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	/*
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);
 
	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	if (width >= height) {
	// aspect >= 1, set the height from -1 to 1, with larger width
	gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
	} else {
	// aspect < 1, set the width to -1 to 1, with larger height
	gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
	}*/
}
 

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	othello.CreateWindow(0,800,600,0,"othello");
	glClearColor( 0 , 0.7, 0, 1);//back ground color
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mousebotton);
	glutTimerFunc(0,timer,10);
    
	glutMainLoop();
	return 0;
}
#endif