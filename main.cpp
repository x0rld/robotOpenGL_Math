


/************************************************************/
/*            TP2: Primitives 3D et couleur                 */
/************************************************************/
/*													        */
/*        ESGI: algorithmique pour l'infographie	        */
/*													        */
/************************************************************/
/*													        */
/*  Objectif: afficher des formes 3D et illuminer la scène  */
/*													        */
/************************************************************/




#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdlib.h>
#include<stdio.h>
#include <math.h>



float epaule = 0.0;
float coude = 0.0;

double R= 6;
double alpha =0;
double phi = 0;
double X1;
double Y1;
double Z1;

GLUquadric* params;


/* prototypes de fonctions */
void initRendering();
void display(void);
void reshape(int w,int h);
void update(int value);
void keyboard(unsigned char key, int x, int y);


/* Programme principal */
int main(int argc,  char **argv){

	/* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("TP2: primitives 3D et illumination");

	/* Initialisation d'OpenGL */
	initRendering();

	/* Enregistrement des fonctions de rappel */
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc (20,update, 0);
	glutKeyboardFunc(keyboard);

	/* Entrée dans la boucle principale de glut, traitement des évènements */
    glutMainLoop();
    return 0;
}


/* Initialisation d'OpenGL pour le rendu de la scène */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

	/* Activation des couleurs */
	glEnable(GL_COLOR_MATERIAL);

	/* définit la couleur d'effacement et la couleur de fond */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* Activation des lumières */
	//glEnable(GL_LIGHTING);          // Activation du mode
	//glEnable(GL_LIGHT0);            // Activation lumière n°0
	//glEnable(GL_LIGHT1);            // Activation lumière n°1
	//glEnable(GL_LIGHT2);            // Activation lumière n°2

	/* Les normales (crées par glNormal(*)) sont automatiquement unitaires */
	glEnable(GL_NORMALIZE);


	/* Activation du mode ombrage (shading) et lissage (smooth) des couleur */
	glShadeModel(GL_SMOOTH);

	/*  définit la taille d'un pixel*/
	glPointSize(2.0);

}

/* Création de la scène avec lampes */
void display(void){
    params = gluNewQuadric();


	/* Déclaration des couleurs et positions des lampes */
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};   // Color (0.2, 0.2, 0.2)




	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();




	X1 = R * cos(phi) * sin(alpha);
	Y1 = R * sin(phi);
	Z1 = R * cos(phi)* cos(alpha);

	gluLookAt(X1, Y1, Z1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glTranslatef(0.0f, 0.0f, -5.0f);                      // déplacement caméra
	glColor3f(1.0f, 1.0f, 1.0f);


	// Ajout lumière ambiante
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);



    //Creation du cube

    glPushMatrix();



        glPushMatrix();
            glutSolidSphere(1,10,10);
            glRotatef(epaule,0,0,1);
        glPopMatrix();

        glPushMatrix();
            gluCylinder(params,1,1,2.5,20,1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1,0,-1);
            glRotatef(40,0,1,0);
            gluCylinder(params,1,0.5,1.5,20,1);
            glTranslatef(1,0,0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1.1,0,-0.8);
            glutSolidSphere(1,10,10);
            glTranslatef(1,0,0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1.1,0,-1.9);
            gluCylinder(params,1,1,1.2,20,1);
            glTranslatef(1,0,0);
        glPopMatrix();






    glPopMatrix();








	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);








	glutSwapBuffers();

	/* On force l'affichage */
	glFlush();
}


/* Fonction de mise à jour: mouvements des objets*/
void update(int value){



	glutPostRedisplay();
	glutTimerFunc(10,update, 0);


}


/*  Mise en forme de la scène pour l'affichage */
void reshape(int w, int h){
	glViewport(0, 0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0,	200.0);



}



/* Fonction de gestion au clavier des activations du bras*/
void keyboard(unsigned char key, int x, int y) {
		switch (key){

			case 'a':   /* monté l'epaule*/
				epaule += 1;

                if (epaule > 45){
                    epaule = 45;
                }
				break;

			case 'b':   /* monté le coude*/
			    coude += 1;
				if (coude > 45){
                    coude = 45;
                }
				break;
            case 'z':    /*Descendre l'épaule*/
                epaule -= 1;

                if (epaule < -45){
                    epaule = -45;
                }
				break;



			case 'v':   /* Descendre le coude */
				 coude -= 1;
				if (coude < -45){
                    coude = -45;
                }
				break;
            case 'o':   /* Descendre l'autre */
				if(alpha < 2 * M_PI){
                    alpha += 0.1;
				}
				break;
            case 'p':   /* Descendre l'autre */
				if(alpha >0){
                    alpha -= 0.1;
				}
				break;
            case 'y':   /* Monté l'autre */
                if(phi < M_PI_2-0.1){
                phi += 0.1;
                }

				break;
            case 'u':   /* Monté l'autre */
                if(phi > -M_PI_2+0.1){
                phi -= 0.1;
                }

				break;
            case 'q':   /* Monté l'autre */
                R+=0.5;

                break;
            case 's':   /* Monté l'autre */
                R-=0.5;

				break;
			case '8':   /* Quitter le programme */
				exit(0);
		}
}
