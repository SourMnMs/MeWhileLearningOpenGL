#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 ourOffset;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()

{
   FragColor = mix(texture(tex1, TexCoord), texture(tex2, TexCoord), ourOffset.z+0.2);
//   FragColor = mix(texture(tex1, TexCoord), texture(tex2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
//   FragColor = mix(texture(tex1, TexCoord)*vec4(ourColor, 1.0), texture(tex2, TexCoord), sin(TexCoord.x));
}