#version 330 core
//--- in_Position: attribute index 0 
//--- in_Color: attribute index 1
//--- in_Normal: attribute index 2

layout (location = 0) in vec3 in_Position; // ��ġ ����: attribute position 0
layout (location = 1) in vec4 in_Color; // �÷� ����: attribute position 1
layout (location = 2) in vec3 in_Normal; // ��� ����: attribute position 2
layout (location = 3) in vec2 in_TexCoord; // �ؽ��� ��ǥ

out vec4 out_Color;	//--- �����׸�Ʈ ���̴����� ����
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 model; //--- �𵨸� ��ȯ��: ���� ���α׷����� ���� -> uniform ������ ����: ���� �̸�"model"�� �޾ƿ�
uniform mat4 view; //--- ���� ��ȯ��: ���� ���α׷����� ���� -> uniform ������ ����: ���� �̸�"view"�� �޾ƿ�
uniform mat4 projection; //--- ���� ��ȯ��: ���� ���α׷����� ���� -> uniform ������ ����: ���� �̸�"projection"�� �޾ƿ�
uniform vec3 model_color;

void main()
{
	gl_Position = projection * view * model * vec4 (in_Position.x, in_Position.y, in_Position.z, 1.0);

	if (model_color.x > -1 && model_color.y > -1 && model_color.z > -1) { out_Color = vec4(model_color, 1.0f); }
	else { out_Color = in_Color; }

	FragPos = vec3(model * vec4(in_Position, 1.0));

	vec4 modelNormal = model * vec4 (in_Normal, 1.0) -  model * vec4 (0.0, 0.0, 0.0, 1.0);

	Normal = vec3(modelNormal.x, modelNormal.y, modelNormal.z);

	TexCoord = in_TexCoord;
}