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