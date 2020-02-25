


#ifdef _WIN32
#include<windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <stdbool.h>
#endif
#include<math.h>


double R = 6;
double Rprim;
double alpha = 0;
double phi = 0;
double eyex = 0.0;
double eyey = 0.0;
double eyez = 5.0;

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

    Rprim = R * cos(phi);

    eyex = Rprim * sin(alpha);
    eyey = R * sin(phi);
    eyez = Rprim * cos(alpha);

    gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);


    // Ajout lumière ambiante
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);


   //TODO: Zone de création




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
        case 'z' :
            if(phi < M_PI_2 - 0.1){
                phi += 0.1;
            }
            break;

        case 's' :
            if(phi > -M_PI_2 + 0.1){
                phi -= 0.1;
            }
            break;

        case 'd' :
            alpha += 0.1;
            break;

        case 'q' :
            alpha -= 0.1;
            break;

        case 'c' :
            R += 1;
            break;

        case 'v' :
            R -= 1;
            break;
    }
}