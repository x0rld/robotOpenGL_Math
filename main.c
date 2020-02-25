


#ifdef _WIN32
#include<windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <stdbool.h>


#endif

double angleE = 0.0;
GLboolean etatE = true;
double angleC = 0.0;
GLboolean etatC = true;


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
    glutCreateWindow("TP3: Mouvement de bras, Avant-bras : Rouge, Bras : Bleu");

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

    /* Déclaration des couleurs et positions des lampes */
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};   // Color (0.2, 0.2, 0.2)



    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();




    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0f, 0.0f, -5.0f);                      // déplacement caméra
    glColor3f(1.0f, 1.0f, 1.0f);


    // Ajout lumière ambiante
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);


    glPushMatrix();

    glTranslatef(-1,0,0);
    glutSolidSphere(0.5, 10, 10);
    glRotatef(angleE, 0, 0, 1);
    glTranslatef(1, 0, 0);

    glPushMatrix();

    glScalef(2, 1, 1);
    glutWireCube(1.0);

    glPopMatrix();


    glTranslatef(1,0,0);
    glutSolidSphere(0.5, 10, 10);
    glRotatef(angleC, 0, 0, 1);
    glTranslatef(1, 0, 0);

    glPushMatrix();

    glScalef(2, 1, 1);
    glutWireCube(1.0);

    glPopMatrix();




    glPopMatrix();


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



/* Fonction de gestion au clavier des activations des lumières */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {

        case 'q':
            if (etatE == true) {
                angleE += 3;
            } else {
                angleE -= 3;
            }

            if (angleE >= 45) {
                etatE = false;
            }
            if (angleE <= 0) {
                etatE = true;
            }
            break;

        case 'd':
            if (etatC == true) {
                angleC += 3;
            } else {
                angleC -= 3;
            }

            if (angleC >= 45) {
                etatC = false;
            }
            if (angleC <= 0) {
                etatC = true;
            }
    }
}