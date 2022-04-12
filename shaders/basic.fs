/*!\file basic.fs
 *
 * \brief fragment shader basique qui applique une couleur à chaque
 * fragment de l'image.
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date March 11, 2018
 */
/* Version GLSL 3.30 */
#version 330
/* sortie du frament shader : une couleur */


in vec3 vsoNormal;
in vec4 vsoModPos;


out vec4 fragColor;
uniform vec4 diffuse_color;

vec4 ambient_light = vec4(0.75, .75, 0.25, 1.0);
vec3 Lp = vec3(0,0.5, 3.0);


void main(void) {

  vec3 Ld = normalize(vsoModPos.xyz - Lp);
  float IL = dot(vsoNormal, -Ld);
  /* mettre la couleur de sortie à color */
  /* généralement on set l'ambient occcusion a 20% et la light a 80% */
  fragColor = 0.2 * ambient_light + .8 * IL * diffuse_color;
}
