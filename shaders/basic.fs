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
uniform vec4 specular_color;
uniform vec4 ambient_light;
uniform mat4 view;


vec4 ambient_light2 = vec4(0.75, .75, 0.25, 1.0);
vec3 Lp = vec3(0,0.5, 3.0);


void main(void) {

  vec3 Ld = normalize(vsoModPos.xyz - Lp);
  vec3 R = reflect(Ld, vsoNormal);
  vec3 Vue = vec3(0.0,0.0,-1.0);
  R = normalize((view * vec4(R, 0.0)).xyz);

  float intensite_diffus = clamp(dot(vsoNormal, -Ld),0,1);
  float intensite_specular = pow(clamp(dot(R, -Vue),0,1),10);

  /* mettre la couleur de sortie à color */
  /* généralement on set l'ambient occcusion a 20% et la light a 80% */

  fragColor = 0.2 * ambient_light + .8 * intensite_diffus + intensite_specular;
}
