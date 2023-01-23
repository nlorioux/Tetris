
#include <Windows.h>

#include <iostream>
#include <stdio.h> 
#include <vector>
#include "GameManager.h"

// Fichiers d'en-têtes pour OpenGL et GLUT

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#define GL_GLEXT_PROTOTYPES


// JPEG Lib
#include "jpeglib.h"
#include "jerror.h"
#include <chrono>




// Structure de données simpliste
// pour stocker un sommet 3D et 
// ses informations de couleur

typedef struct {
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
    //float a;
} vertex;

//origine
float xOrigin = -1.0f;
float yOrigin = -1.0f;
float zOrigin = 0.0f;



// Indice des coordonnees de texture
typedef struct {
    float s;
    float t;
} textureCoord;



// Quelques variables globales (c'est pas bien)
GLfloat pointSize = 1.0f;

// Rotations autour de X et Y
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLint oldX = 0;
GLint oldY = 0;
GLboolean boutonClick = false;

// Taille de la fenêtre
int windowW = 1800;
int windowH = 900;
gameManager GM;
vector<vector<vector<float>>> grid;


//float near = 0.1f;
//float far = 100.0f;

// Déclarations des fonctions de rappel (callbacks)
GLvoid displayBackground();
GLvoid displayGrid(std::vector<std::vector<std::vector<float>>>);
GLvoid displayMetris();

// Texture
GLuint textureID = 0;
bool LoadJPEG(char* FileName, bool Fast = true);
auto startTime = chrono::system_clock::now();
double timer=0;
double moveSpeed = 0.3;
// TEXTURE
unsigned long x;
unsigned long y;
unsigned short int bpp; //bits per pixels   unsigned short int
GLbyte* texData;             //the data of the image
GLuint ID;                //the id ogl gives it
unsigned long sizeFile;     //length of the file
int channels;      //the channels of the image 3 = RGA 4 = RGBA
GLuint type;

GLboolean colorCube = false;
GLint texEnvMode = 1;
GLboolean alpha = false;

bool LoadJPEG(const char* FileName, bool Fast)
{
    FILE* file = fopen(FileName, "rb");  //open the file
    struct jpeg_decompress_struct info;  //the jpeg decompress info
    struct jpeg_error_mgr err;           //the error handler

    info.err = jpeg_std_error(&err);     //tell the jpeg decompression handler to send the errors to err
    jpeg_create_decompress(&info);       //sets info to all the default stuff

    //if the jpeg file didnt load exit
    if (!file)
    {
        fprintf(stderr, "Error reading JPEG file %s!!!", FileName);
        return false;
    }

    jpeg_stdio_src(&info, file);    //tell the jpeg lib the file we'er reading

    jpeg_read_header(&info, TRUE);   //tell it to start reading it

    //if it wants to be read fast or not
    if (Fast)
    {
        info.do_fancy_upsampling = FALSE;
    }

    jpeg_start_decompress(&info);    //decompress the file

    //set the x and y
    x = info.output_width;
    y = info.output_height;
    channels = info.num_components;

    type = GL_RGB;

    if (channels == 4)
    {
        type = GL_RGBA;
    }

    bpp = channels * 8;

    sizeFile = x * y * 3;

    //read turn the uncompressed data into something ogl can read
    texData = new GLbyte[sizeFile];      //setup data for the data its going to be handling

    GLbyte* p1 = texData;
    GLbyte** p2 = &p1;
    int numlines = 0;

    while (info.output_scanline < info.output_height)
    {
        numlines = jpeg_read_scanlines(&info, (JSAMPLE**)p2, 1);
        *p2 += numlines * 3 * info.output_width;
    }

    jpeg_finish_decompress(&info);   //finish decompressing this file

    fclose(file);                    //close the file

    return true;
}

GLvoid displayMetris() {
    displayBackground();
    
    auto currentTime = chrono::system_clock::now();
    chrono::duration<double> elapsed = currentTime - startTime;
    timer += elapsed.count();
    if (timer > moveSpeed) {
        GM.nextTurn();
        timer = 0;
        if (moveSpeed>0.1 && GM.getNewShapeSpawned())
        {
            moveSpeed -= 0.05;
            GM.setNewShapeSpawned(false);
        }
    }
    startTime = currentTime;

    //grid.clear();
    //grid = GM.display();
    displayGrid(GM.display());

    glFlush();
    glutSwapBuffers();
}



// Definition de la fonction d'affichage
GLvoid displayBackground() {
    // Effacement du frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);


    // Combinaison avec le fragment
    switch (texEnvMode) {
    case 0:
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
        break;
    case 1:
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        break;
    case 2:
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        break;

    default:
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
        break;
    }


    // Animation du cube!
    glLoadIdentity();
    glRotatef(-angleY, 1.0f, 0.0f, 0.0f);
    glRotatef(-angleX, 0.0f, 1.0f, 0.0f);


    glBegin(GL_QUADS);
    // Premier sommet 
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(xOrigin, yOrigin, zOrigin);
    // Second sommet 
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(xOrigin + 2.0f, yOrigin, zOrigin);
    // Troisième sommet
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(xOrigin + 2.0f, yOrigin + 2.0f, zOrigin);
    // Quatrième sommet 
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(xOrigin, yOrigin + 2.0f, zOrigin);




}

GLvoid displayGrid(std::vector<std::vector<std::vector<float>>> grid) {
    // Effacement du frame buffer
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f((1.0f) / 20.0f, -1.0f, 1.0f);
    glVertex3f((1.0f) / 20.0f, (1.0f) / 10.0f - 1.0f, 1.0f);
    glVertex3f(0.0f, (1.0f) / 10.0f - 1.0f, 1.0f);
    glVertex3f(0.0f, -1.0f, 1.0f);
    glEnd();

    if (grid.size()==10) {
        for (int j = 0; j < 10; j++) {
            for (int i = 0; i < 20; i++) {
                if (grid[j][i][0] != 0.0f || grid[j][i][1] != 0.0f || grid[j][i][2] != 0.0f) {
                    glDisable(GL_TEXTURE_2D);
                    glBegin(GL_QUADS);
                    glColor3f(grid[j][i][0], grid[j][i][1], grid[j][i][2]);
                    glVertex3f((j + 1.0f) / 20.0f, i / 10.0f - 1.0f, -1.0f);
                    glVertex3f(j / 20.0f, i / 10.0f - 1.0f, -1.0f);
                    glVertex3f(j / 20.0f, (i + 1) / 10.0f - 1.0f, -1.0f);
                    glVertex3f((j + 1.0f) / 20.0f, (i + 1) / 10.0f - 1.0f, -1.0f);



                    glEnd();
                }
            }
        }
    }


}


// Définition de la fonction gérant les interruptions clavier
GLvoid clavier(int touche, int x, int y) {
    GM.onKeyPress(touche);
    // Demande a GLUT de réafficher la scene
    glutPostRedisplay();
}



int main(int argc, char* argv[])
{
    srand(time(NULL));

    
    // Initialisation de GLUT
    glutInit(&argc, argv);
    // Choix du mode d'affichage (ici RVB)
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    // Position initiale de la fenetre GLUT
    glutInitWindowPosition(100, 100);
    // Taille initiale de la fenetre GLUT
    glutInitWindowSize(windowW, windowH);
    // Creation de la fenetre GLUT
    glutCreateWindow("Metris");

    // Définition de la couleur d'effacement du framebuffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Initialement on desactive le Z-buffer
    glEnable(GL_DEPTH_TEST);

    // Loading a texture
    boolean loaded = LoadJPEG("METRIS_Background.jpg", true);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 14032, 7016, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);




     // Définition des fonctions de callbacks
    glutDisplayFunc(displayMetris);
    glutIdleFunc(displayMetris);
    // Nouveaux callbacks
    glutSpecialFunc(clavier);
    // Lancement de la boucle infinie GLUT
    glutMainLoop();

    return 0;


}