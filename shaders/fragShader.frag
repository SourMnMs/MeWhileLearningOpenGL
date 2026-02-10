#version 330 core
out vec4 FragColor;

in vec4 color;
//in vec2 TexCoord;
//in float dist;

//uniform sampler2D tex1;
//uniform sampler2D tex2;
//uniform int maxDist = 25;

void main()

{
    FragColor = color;
//   FragColor = mix(texture(tex1, TexCoord), texture(tex2, TexCoord), 0.2);
//   FragColor = vec4(1.0, 1.0, 1.0, 1.0) - vec4(dist/maxDist, dist/maxDist, dist/maxDist, 0.0);
//   FragColor = mix(texture(tex1, TexCoord), texture(tex2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
//   FragColor = mix(texture(tex1, TexCoord)*vec4(ourColor, 1.0), texture(tex2, TexCoord), sin(TexCoord.x));
}