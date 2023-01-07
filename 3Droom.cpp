#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void initialize(void);
void display(void);
void reshape(int w,int h);
void keyboard(unsigned char key, int x, int y);
void idle(void);

void setLight0(bool flag);
void setLight1(bool flag);
void setLight2(bool flag);


//ȫ�ֱ������� 

//��Դ0 
GLfloat light_pos0[] = {0, 25, -10, 1};
GLfloat light_dir0[]   = {0, -1, 0};
GLfloat light_cutoff0 = 45;
GLfloat light_amb0[] = {0.2, 0.2, 0.2, 1.0};
GLfloat light_dif0[] = {0.4, 0.4, 0.4, 1.0};
GLfloat light_spc0[] = {1.0, 1.0, 1.0, 1.0};

//��Դ1 
GLfloat light_pos1[] = {10, 10, 10, 1};
GLfloat light_dir1[]   = {0, -1, -1};
GLfloat light_cutoff1 = 20;
GLfloat light_amb1[] = {0.1, 0.3, 0.1, 1.0};
GLfloat light_dif1[] = {0.1, 0.7, 0.1, 1.0};
GLfloat light_spc1[] = {1.0, 1.0, 1.0, 1.0};

//��Դ2 
GLfloat light_pos2[] = {0, 10, -10, 1};
GLfloat light_dir2[]   = {0, -1, 0};
GLfloat light_cutoff2 = 50;
GLfloat light_amb2[] = {0.2, 0.15, 0, 1.0};
GLfloat light_dif2[] = {0.8, 0.75, 0, 1.0};
GLfloat light_spc2[] = {1.0, 1.0, 0, 1.0};



bool RoomLight = true;
bool Computer=false;

bool ChristmasTree = false;
int ChristmasTreeAng = 0;
bool ChristmasTreeLight = false;
bool ChristmasTreeJumpUp = true;
float ChristmasTreeJumpDis = 0;

bool CeilingLight = false;

bool Mouse = false;
bool MouseEyeBigger = true;
float MouseEyeScale = 1.0;
float MouseTrace[] = {0,0,0};//�����λ�� 

void setLight0(bool flag)   //���ù���0 
{
	//glLightfv(��Դ��, ����, ��ֵ) 
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);//��Դλ��������� 
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir0);//���Դ�۹ⷽ��ʸ��
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light_cutoff0);//���Դ�۹��ֹ��

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb0);//������ 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif0);//������ 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spc0);//���淴�� 

	if(flag)
		glEnable(GL_LIGHT0);//���ù�Դ 
	else
		glDisable(GL_LIGHT0);//�رչ�Դ 
}

void setLight1(bool flag)   //���ù���1 
{
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light_cutoff1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_dif1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_spc1);
	
	if(flag)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
}

void setLight2(bool flag)  //���ù���2 
{
	glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_dir2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, light_cutoff2);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_amb2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_dif2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_spc2);
	
	if(flag)
		glEnable(GL_LIGHT2);
	else
		glDisable(GL_LIGHT2);
}

void initialize(void) // ��ʼ���趨 
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void display(void) // Here's Where We Do All The Drawing
{
	
	//���÷��ݹ�Դ 
	setLight0(RoomLight);
	setLight1(ChristmasTreeLight);
	setLight2(CeilingLight);

	// �����ɫ��ȼ�ɫ�ʻ��� 
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	//��ɫ���� 
	GLfloat matBlack[] = {0, 0, 0, 1};
	GLfloat matWhite[] = {1, 1, 1, 1};
	GLfloat matPink[] = {1, 0.8, 0.2, 1};
	GLfloat matBrown[] = {1, 0.6, 0.3, 1};
	GLfloat matYellowGreen[] = {0.5, 1, 0.5, 1};
	GLfloat matRed[] = {1, 0, 0, 1};
	GLfloat matGreen[] = {0, 1, 0, 1};
	GLfloat matBlue[] = {0, 0, 1, 1};
	GLfloat matSkyBlue[]={0.5, 1, 1, 1};
	GLfloat matYellow[] = {1, 1, 0, 1};
	GLfloat matGold[] = {0.4, 0.3, 0.1, 1};
	GLfloat matShininess[] = {50};


	//����ķ�Χ x:10 to -10; y:10 to -10; z:0 to -20
	
	//����ǽ��ɫ��
	//back wall 
	glColor3f(0.6, 1, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matSkyBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matSkyBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSkyBlue);
	glMaterialfv(GL_FRONT, GL_SHININESS,matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);		
	glVertex3f( 10, 10, -20);
	glVertex3f(-10, 10, -20);
	glVertex3f(-10,-10, -20);
	glVertex3f( 10,-10, -20);
	glEnd();
	
	//top wall 
	glColor3f(0.9,0.8, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matWhite);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matWhite);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION,matBlack);
	glBegin(GL_QUADS);
	glVertex3f( 10, 10, -20);
	glVertex3f( 10, 10,   0);
	glVertex3f(-10, 10,   0);
	glVertex3f(-10, 10, -20);
	glEnd();
	
	//left wall
	glColor3f(0.6, 1, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matSkyBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matSkyBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSkyBlue);
	glMaterialfv(GL_FRONT, GL_SHININESS,matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);
	glVertex3f(-10, 10, -20);
	glVertex3f(-10, 10,   0);
	glVertex3f(-10,-10,   0);
	glVertex3f(-10,-10, -20);
	glEnd();
	
	//bottom wall
	glColor3f(0.5, 0.45, 0.33);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matBlack);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);
	glVertex3f(-10,-10, -20);
	glVertex3f(-10,-10,   0);
	glVertex3f( 10,-10,   0);
	glVertex3f( 10,-10, -20);
	glEnd();
	
	//right wall 
	glColor3f(0.6, 1, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matSkyBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matSkyBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSkyBlue);
	glMaterialfv(GL_FRONT, GL_SHININESS,matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);
	glVertex3f( 10,-10, -20);
	glVertex3f( 10,-10,   0);
	glVertex3f( 10, 10,   0);
	glVertex3f( 10, 10, -20);
	glEnd();
	
	//Bed
	glColor3f(1, 0.8, 0.2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

	glPushMatrix();
	glTranslatef(-6, -6, -19.5);
	glScalef( 8, 8, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, -7, -11.5);
	glScalef( 8, 1, 16);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, -8.5, -4);
	glScalef( 8, 3, 1);
	glutSolidCube(1);
	glPopMatrix();
	
	//Bed mattress
	glPushMatrix();
	glColor3f(1, 0.7, 0.7);	
	glMaterialfv(GL_FRONT, GL_AMBIENT, matPink);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matPink);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glTranslatef(-6, -6, -11.5);
	glScalef( 8, 2, 16);
	glutSolidCube(1);
	glPopMatrix();

	//cabin ���� 
	glColor3f(1, 0.8, 0.1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matBrown);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matGold);

	glPushMatrix();
	glTranslatef(6, -10, -18);
	glScalef( 8,10, 4);
	glutSolidCube(1);
	glPopMatrix();
	
	
	//computer
	//bottom 
	glColor3f(0, 0,0);
	glPushMatrix();
	glTranslatef(6, -5, -18);
	glRotatef(0, 0, 1, 0);
	glScalef(1,0.1,0.8);
	glutSolidCube(1);
	glPopMatrix();
	
	//neck
	glPushMatrix();
	glTranslatef(6, -4.9, -18);
	glRotatef(0, 0, 1, 0);
	glScalef(0.1,0.8, 0.1);
	glutSolidCube(1);
	glPopMatrix();
	//screen
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	if(Computer) glMaterialfv(GL_FRONT, GL_EMISSION, matBlue);
	glTranslatef(6, -3.6, -18);
	glRotatef(0, 0, 1, 0);
	glScalef(3, 1.8, 0.1);
	glutSolidCube(1);
	glPopMatrix();
	
	
	//Brown desk
	glColor3f(1, 0.6, 0.3);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

	glPushMatrix();
	glTranslatef(8, -4.5, -6);
	glScalef( 4, 1, 12);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(9.5, -7, -6);
	glScalef( 1, 6, 12);
	glutSolidCube(1);
	glPopMatrix();
	
	//Teapot
	glPushMatrix();	
	glColor3f(1,1,1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matWhite);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matWhite);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glTranslatef(7.5, -3.2, -10);
	glRotatef(-135, 0, 1, 0);
	glutWireTeapot(1);
	glPopMatrix();


	//ChristmasTree
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);
	
	glPushMatrix();
	glColor3f(0.5, 1, 0.5);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellowGreen);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellowGreen);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glTranslatef(8, -2, -2);
	glTranslatef(0, ChristmasTreeJumpDis, 0);		//Jump animation
	glRotatef(ChristmasTreeAng, 0, 1, 0);	//Rotate animation

		glPushMatrix();
		glTranslatef(0, 1.5, 0);
		glRotatef(270,1,0, 0);
		glutSolidCone(0.8,1,20,20);			           //layer1
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0, 0.5, 0);
		glRotatef(270,1,0, 0);
		glutSolidCone(1.2,1.5,16,16);		           //layer2
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0, -0.8, 0);
		glRotatef(270,1,0, 0);
		glutSolidCone(1.5,2,16,16);                   //layer3   
		glPopMatrix();
		
		glColor3f(205/255, 200/255, 200/255);
		glPushMatrix();                               //trunk
		glTranslatef(0,-0.8,0);
		glRotatef(90, 1, 0, 0);
		gluCylinder(quadratic, 0.3, 0.5, 1, 20, 20);
		glPopMatrix();
		
		
		glColor3f(1, 1, 1);
		glPushMatrix();                               //branch
		glTranslatef(1.3,-0.5,0);
		glRotatef(90, 1, 0, 0);
		gluCylinder(quadratic, 0.2, 0.2, 0.3, 20, 20);
		glPopMatrix();
		
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, -10, -19.99);
		glPushMatrix();				//Mice hole
		glColor3f(0, 0, 0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, matBlack);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matBlack);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matBlack);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
		glScalef(1, 1.5, 1);
		gluDisk(quadratic, 0, 1, 16, 5);
		glPopMatrix();
		glPushMatrix();				//Mice eye
		glColor3f(1, 1, 0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matYellow);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, matYellow);
		glTranslatef(0.5, 0.5, 0.01);
	    glTranslatef(MouseTrace[0],MouseTrace[1],MouseTrace[2]);
		glScalef(MouseEyeScale, MouseEyeScale, 1);                 //control the size of mouse eyes
		gluDisk(quadratic, 0, 0.1, 8, 1);
		glPopMatrix();
		glPushMatrix();				//Mice eye
		glTranslatef(-0.5, 0.5, 0.01);
		glTranslatef(MouseTrace[0],MouseTrace[1],MouseTrace[2]);  //control the size of mouse eyes
		glScalef(MouseEyeScale, MouseEyeScale, 1);
		gluDisk(quadratic, 0, 0.1, 8, 1);
		glPopMatrix();
		if(Mouse){
			glPushMatrix();			//Mice Body
			glColor3f(0, 0, 0);
			glMaterialfv(GL_FRONT, GL_AMBIENT, matBlack);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, matBlack);
			glMaterialfv(GL_FRONT, GL_SPECULAR, matBlack);
			glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
			glTranslatef(0,0,-1);
			glTranslatef(MouseTrace[0],MouseTrace[1],MouseTrace[2]);
			glScalef(1,1,1.7);
			glutSolidSphere(0.8,16,16);
			glPopMatrix();
		}
	glPopMatrix();
	
	glPushMatrix();					//Celling Light
	glColor3f(1, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	if(CeilingLight) glMaterialfv(GL_FRONT, GL_EMISSION, matYellow);
	glTranslatef(0,9.0,-10);
	glRotatef(270, 1, 0, 0);
	glutSolidCone(1,1,16,16);
	glPopMatrix();

	// TODO:
	// Add animation here
	
	glFlush();
	glutSwapBuffers();
	
}

void reshape(int w, int h) // �������ô��ڴ�С
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(65,(GLfloat)w/(GLfloat)h,1.0,100.0); 
	
	//�����ӽ�(x1,y1,z1) ����(x2,y2,z2) ��(x,y,z) 
	gluLookAt( 0.0, 0.0, 15, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) //�����¼���Ӧ 
{
	   switch (key) 
	   {
	    
	   case'\033'://press 'esc' to quit
		   exit(0);
		   break;

		case'1'://���ݵƹ� 
		 RoomLight = !RoomLight;
		   printf("Press key '1'.\n");
		   break;
		case'2'://�컨��ƹ� 
			CeilingLight = !CeilingLight;
		   printf("Press key '2'.\n");
		   break;
		case'3'://ʥ�����ƹ� 
			ChristmasTreeLight = !ChristmasTreeLight;
			if(!ChristmasTreeLight) ChristmasTreeJumpDis = 0;
		   printf("Press key '3'.\n");
		   break;
		case'4'://ʥ�����˶� 
			ChristmasTree = !ChristmasTree;
			if(!ChristmasTree) ChristmasTreeJumpDis = 0;
		   printf("Press key '4'.\n");
		   break;
		case'5'://�����˶� 
			if(!RoomLight && !CeilingLight && !ChristmasTreeLight)
				Mouse = !Mouse;
		   printf("Press key '5'.\n");
		   break;
		case'6'://���� 
			Computer=!Computer;
			printf("Press key '6'.\n");
			break;
	   }
		
	   if(RoomLight  || CeilingLight || ChristmasTreeLight)
		   Mouse = false;
}
       
void idle(void)//���ƶ��� 
{
	if(ChristmasTree){
		if(!ChristmasTreeLight)
			ChristmasTreeAng = ++ChristmasTreeAng % 360;   //ʥ������ת 
		else{
			if(ChristmasTreeJumpUp){
				ChristmasTreeJumpDis += 0.1;              //ʥ�������� 
				if(ChristmasTreeJumpDis >= 1) ChristmasTreeJumpUp = false;
			}else{
				ChristmasTreeJumpDis -= 0.1;
				if(ChristmasTreeJumpDis <= 0) ChristmasTreeJumpUp = true;
			}
		}
	}
	if(!Mouse){                          //control  the size of mouse eyes 
		if(MouseEyeBigger){  
			MouseEyeScale += 0.2;
			if(MouseEyeScale >= 3) MouseEyeBigger = false;
		}else{
			MouseEyeScale -= 0.2;
			if(MouseEyeScale <= 0) MouseEyeBigger = true;
		}
		MouseTrace[0] = MouseTrace[1] = MouseTrace[2] = 0;
	}else{
		MouseEyeScale = 1;
		MouseTrace[2] += 0.5;
		if(MouseTrace[2] < 10)
			MouseTrace[0] += 0.3;                 //x���ƶ� 
		else
			MouseTrace[0] -= 0.3;
		if(MouseTrace[2] > 25)                   //z���ƶ� 
			MouseTrace[0] = MouseTrace[1] = MouseTrace[2] = 0;
	}
	Sleep(10);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	//��ʼ��GLUT�� 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);

	//�������� 
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3D ROOM");
	
	//��ʼ���趨 
	initialize();	 
	
	//�����¼���Ӧ 
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	
	//���������ڵ�ѭ�������� 
	glutMainLoop();
	
}
