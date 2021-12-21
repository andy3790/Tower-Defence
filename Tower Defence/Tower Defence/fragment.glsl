#version 330
//--- out_Color: ���ؽ� ���̴����� �Է¹޴� ���� ��
//--- FragColor: ����� ������ ������ ������ ���۷� ���� ��. 

in vec4 out_Color; //--- ���ؽ� ���̴����Լ� ���� ����
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
out vec4 FragColor; //--- ���� ���

uniform sampler2D outTexture; // �ؽ�ó �ε���: ������ ������ 0������ ����

uniform vec3 lightPos; //--- ���� ��ġ
uniform vec3 lightColor; //--- ���� ����

uniform vec3 viewPos; //--- ī�޶� ��ġ

uniform bool lightOn;
uniform bool textureOn;

uniform float alphaValue;

void main(void) 
{
	float ambientLight = 0.3;
	vec3 ambient = ambientLight * lightColor;

	vec3 result;

	if (lightOn) {
		vec3 lightDir = normalize(lightPos - FragPos);
		float diffuseLight = max(dot(Normal, lightDir), 0.0);
		vec3 diffuse = diffuseLight * lightColor;

		int shininess = 128;
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, Normal);
		float specularLight = max(dot(viewDir, reflectDir), 0.0);
		specularLight = pow(specularLight, shininess);
		vec3 specular = specularLight * lightColor;
	
		result = (ambient + diffuse + specular) * vec3(out_Color);
		if(textureOn){
			FragColor = texture(outTexture, TexCoord) * vec4((ambient + diffuse + specular), 1.0);
		}
		else{
			FragColor = vec4 (result, out_Color.a * alphaValue);
		}
	}
	else {
		result = ambient * vec3(out_Color);
		if(textureOn){
			FragColor = texture(outTexture, TexCoord) * vec4(ambient, 1.0);
		}
		else{
			FragColor = vec4 (result, out_Color.a * alphaValue);
		}
	}
}