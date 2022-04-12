/*!\file window.cpp
 *
 * \brief premier exemple de code GL4Dummies/OpenGL avec création et
 * utilisation d'un shader sur une géométrie de quadrilatère. Le
 * quadrilatère subit un changement d'échelle variable utilisant une
 * sinusoïdale.
 *
 * \author Farès BELHADJ, amsi@up8.edu
 * \date March 11, 2022
 */
#include <GL4D/gl4du.h>
#include <GL4D/gl4duw_SDL2.h>
/* Prototypes des fonctions statiques contenues dans ce fichier C */
static void init(void);
static void draw(void);
static void quit(void);
/*!\brief largeur et hauteur de la fenêtre */
static int _wW = 800, _wH = 600;
/*!\brief identifiant du quadrilatère faisant office de "plan couché" */
static GLuint _quad = 0;
/*!\brief identifiant du cube */
static GLuint _cube = 0;
/*!\brief identifiant du (futur) GLSL program */
static GLuint _pId = 0;
/*!\brief créé la fenêtre d'affichage, initialise GL et les données,
 * affecte les fonctions d'événements et lance la boucle principale
 * d'affichage. */
int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "GL4Dummies", 20, 20, 
			 _wW, _wH, GL4DW_RESIZABLE | GL4DW_SHOWN))
    return 1;
  init();
  atexit(quit);
  gl4duwDisplayFunc(draw);
  gl4duwMainLoop();
  return 0;
}
/*!\brief initialise les paramètres OpenGL et les données. 
 */
static void init(void) {
  SDL_GL_SetSwapInterval(0);
  /* Création du programme shader (voir le dossier shader) */
  _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/basic.fs", NULL);
  /* Set de la couleur (RGBA) d'effacement OpenGL */
  glClearColor(0.2f, 0.0f, 0.0f, 0.0f);
  /* activer le test de profondeur */
  glEnable(GL_DEPTH_TEST);
  /* dans quelle partie de l'écran on effectue le rendu */
  glViewport(0, 0, _wW, _wH);
  /* génération de la géométrie du quadrilatère */
  _quad = gl4dgGenQuadf();
  /* génération de la géométrie du quadrilatère */
  _cube = gl4dgGenCubef();

  gl4duGenMatrix(GL_FLOAT, "projection");
  gl4duGenMatrix(GL_FLOAT, "model");
  gl4duGenMatrix(GL_FLOAT, "view");

  gl4duBindMatrix("projection");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 1000.0f);
  /* pour le mode fil de fer */
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
/*!\brief Cette fonction dessine dans le contexte OpenGL actif. */
static void draw(void) {
  const GLfloat rouge[] = { 1.0f, 0.0f, 0.0f, 1.0f };
  const GLfloat bleu[] = { 0.0f, 0.0f, 1.0f, 1.0f };
  const GLfloat bleu_cyan[] = { 0.019f, 0.91f, 0.48f, 1.0f };
  const GLfloat chrome[] = { 0.7f, 0.6f, 0.3f, 1.0f };
  const GLfloat mat[] = { 0.1f, 0.1f, 0.1f, 1.0f };

  /* Variation de temps en seconde sur la frmae actuelle par rapport à la precedente */
  static double t0 = 0.0;
  double dt, t = gl4dGetElapsedTime();
  static float d = 10;
  dt = (t - t0) * .0001;
  t0 = t;

  /* effacement du buffer de couleur */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /* activation du programme de rendu _pId */
  glUseProgram(_pId);
  glUniform4fv(glGetUniformLocation(_pId, "ambient_light"), 1, bleu_cyan);

  gl4duBindMatrix("view");
  gl4duLoadIdentityf();
  gl4duLookAtf(-5, 6, 6, 0, 0, 0, 0, 1, 0);
  gl4duBindMatrix("model");
  gl4duLoadIdentityf();
  gl4duPushMatrix(); {
	  gl4duScalef(5, 5, 5);
	  gl4duRotatef(-90, 1, 0, 0);
	  gl4duSendMatrices();
	  /* du rouge pour le quad */
	  glUniform4fv(glGetUniformLocation(_pId, "diffuse_color"), 1, bleu_cyan);
	  glUniform4fv(glGetUniformLocation(_pId, "specular_color"), 1, mat);
	  /* dessin de la géométrie du quadrilatère */
	  gl4dgDraw(_quad);
  }
  gl4duPopMatrix();
  gl4duTranslatef(0, 1.2f, 0);
  gl4duRotatef(-d * 5.0f, 0, 1, 0);
  gl4duTranslatef(1.5, 0.0f, 0);
  gl4duRotatef(d, 0, 1, 0);
  gl4duSendMatrices();
  /* du bleu pour le cube */
  glUniform4fv(glGetUniformLocation(_pId, "diffuse_color"), 1, bleu);
  glUniform4fv(glGetUniformLocation(_pId, "specular_color"), 1, chrome);
  /* dessin de la géométrie du cube */
  gl4dgDraw(_cube);
  /* désactiver le programme shader */
  glUseProgram(0);
  d += 360.0 * dt;

  //SLD_Delay(100);
}
/*!\brief appelée au moment de sortir du programme (atexit), elle
 *  libère les éléments OpenGL utilisés.*/
static void quit(void) {
  /* nettoyage des éléments utilisés par la bibliothèque GL4Dummies */
  gl4duClean(GL4DU_ALL);
}
