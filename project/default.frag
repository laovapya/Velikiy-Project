#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform float alpha;

uniform vec3 lightPos;
uniform vec3 lightColor;
in vec3 Normal;

void main()
{

	  float ambientStrength = 1.0f;
      vec3 ambient = ambientStrength * lightColor;

      //vec3 norm = normalize(Normal);
      //vec3 lightDir = normalize(lightPos - FragPos);
      //float diff = max(dot(norm, lightDir), 0.0);
      //vec3 diffuse = diff * lightColor;

      //vec3 result = (ambient + diffuse) * objectColor;
      vec3 result = ambient * objectColor;
      FragColor = vec4(result, alpha);
}

