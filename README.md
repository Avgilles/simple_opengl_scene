![](/preview/IL_light.gif)


**fs**
```cpp
in float IL;

out vec4 fragColor;
uniform vec4 diffuse_color;

void main(void) {
  /* mettre la couleur de sortie à color */
  fragColor = IL* diffuse_color;
}
```
**vs**
```cpp
layout (location = 1) in vec3 vsiNormal;

void main(void) {
  IL = dot(vsiNormal, -Ld);
  vec4 pos = projection * view * model * vec4(vsiPosition, 1.0f);
  gl_Position = pos;
}
```


![](/preview/phong_light.gif)
**fs**
```cpp

in vec3 vsoNormal;
in vec4 vsoModPos;


out vec4 fragColor;
uniform vec4 diffuse_color;


vec3 Lp = vec3(0,10.5, 3.0);


void main(void) {

  vec3 Ld = normalize(vsoModPos.xyz - Lp);
  float IL = dot(vsoNormal, -Ld);
  /* mettre la couleur de sortie à color */
  fragColor = IL* diffuse_color;
}

```

```cpp


layout (location = 1) in vec3 vsiNormal;

/* variable cablée sur l'attribut 2 du sommet dans le code CPU (dans
 * gl4dg.c, dans l'appel glVertexAttribPointer(2, ...), le 2
 * correspond au location = 2) */
layout (location = 2) in vec2 vsiTexCoord;

uniform mat4 projection, model, view;

out vec3 vsoNormal;
out vec4 vsoModPos;


void main(void) {
  vsoNormal = normalize((transpose(inverse(model)) * vec4(vsiNormal, 0.0)).xyz);
  vsoModPos = model * vec4(vsiPosition, 1.0f);
  gl_Position =  projection * view * vsoModPos;
}

```

![](/preview/phong_light_specular.gif)
