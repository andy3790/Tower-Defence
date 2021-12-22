#include "includer.h"
#include "shader_program.h"
#include "Figure.h"
#define WIN_WIDTH 800	// ������ ���� ũ��
#define WIN_HIGHT 800	// ������ ���� ũ��


std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> F_urd(0.1, 1.0);	// Figure class�� ���� ���� ������

GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid KeyboardUp(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid MouseWheel(int button, int dir, int x, int y);
GLvoid Special(int key, int x, int y);
GLvoid SpecialUp(int key, int x, int y);
GLvoid Timer(int value);

GLuint s_program;
GLuint vertexShader;
GLuint fragmentShader;

glm::vec3 camera_startPos_v3; // ī�޶� �ʱ� ��ġ
glm::vec3 camera_startDir_v3; // ī�޶� �ʱ� �ٶ󺸴� ����
glm::vec3 camera_pos_v3; //--- ī�޶� ���� ��ġ
glm::vec3 camera_direction_v3; //--- ī�޶� ���� �ٶ󺸴� ����
glm::vec3 camera_up_v3; //--- ī�޶� ���� ����
glm::mat4 camera_rot_m4; // ī�޶� ȸ�� ���
glm::mat4 camera_trans_m4; // ī�޶� �̵� ���

glm::vec4 light_pos_v4; // ���� ��ġ
glm::mat4 light_trans_m4; // ���� �̵����
glm::mat4 light_rot_m4; // ���� ȸ�����
bool is_light_on; // �� Ȱ��ȭ/��Ȱ��ȭ

bool is_texture_on; // �ؽ��� Ȱ��ȭ/��Ȱ��ȭ


unsigned int transformLocation_ui;
unsigned int viewLocation_ui;
unsigned int projectionLocation_ui;
unsigned int colorLocation_ui;

unsigned int lightPosLocation_ui;
unsigned int lightColorLocation_ui;
unsigned int lightOnLocation_ui;
unsigned int viewPosLocation_ui;

unsigned int textureOnLocation_ui;

unsigned int alphaValueLocation_ui;


Figure Figure_floor;

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(WIN_WIDTH, WIN_HIGHT); // �������� ũ�� ����
	glutCreateWindow("Tower Defence"); // ������ ���� (������ �̸�)
		//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	InitShader();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	camera_startPos_v3 = glm::vec3(5.0f, 5.0f, 5.0f);
	camera_startDir_v3 = glm::vec3(0.0f, 0.0f, 0.0f);
	camera_pos_v3 = camera_startPos_v3; //--- ī�޶� ��ġ
	camera_direction_v3 = camera_startDir_v3; //--- ī�޶� �ٶ󺸴� ����
	camera_up_v3 = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����
	camera_rot_m4 = glm::mat4(1.0f);
	camera_trans_m4 = glm::mat4(1.0f);

	light_trans_m4 = glm::mat4(1.0f);
	light_rot_m4 = glm::mat4(1.0f);
	light_trans_m4 = glm::translate(light_trans_m4, glm::vec3(0.0f, 5.0f, -10.0f));
	light_pos_v4 = glm::vec4(0.0, 0.0, 0.0, 1.0);
	is_light_on = true;

	is_texture_on = false;

	transformLocation_ui = glGetUniformLocation(s_program, "model");
	viewLocation_ui = glGetUniformLocation(s_program, "view");
	projectionLocation_ui = glGetUniformLocation(s_program, "projection");
	colorLocation_ui = glGetUniformLocation(s_program, "model_color");

	lightPosLocation_ui = glGetUniformLocation(s_program, "lightPos");
	lightColorLocation_ui = glGetUniformLocation(s_program, "lightColor");
	lightOnLocation_ui = glGetUniformLocation(s_program, "lightOn");
	viewPosLocation_ui = glGetUniformLocation(s_program, "viewPos");

	textureOnLocation_ui = glGetUniformLocation(s_program, "textureOn");

	alphaValueLocation_ui = glGetUniformLocation(s_program, "alphaValue");

	Figure_floor.MakeCube(0.0, -0.1, 0.0, 10.0, 0.1, 10.0, 0.5, 0.5, 0.5);

	glutTimerFunc(10, Timer, 1);

	glutDisplayFunc(DrawScene); // ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �ݹ��Լ� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ��Լ� ����
	glutKeyboardUpFunc(KeyboardUp); // Ű���� �Է� �ݹ��Լ� ����
	glutSpecialFunc(Special); // Ư�� Ű �Է� �ݹ��Լ� ����
	glutSpecialUpFunc(SpecialUp); // Ư�� Ű �Է� �ݹ��Լ� ����
	glutMouseFunc(Mouse); // ���콺 �Է� �ݹ��Լ� ����
	glutMouseWheelFunc(MouseWheel); // ���콺 �Է� �ݹ��Լ� ����
	glutMotionFunc(Motion);
	glutMainLoop(); // �̺�Ʈ ó�� ����
}

GLvoid DrawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	//--- ����� ���� ����
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	//--- ��ȯ ��� ���� ���ؽ� ���̴��� ������
	glUniform3f(colorLocation_ui, -1.0, -1.0, -1.0);

	glm::vec4 current_light_pos_v4 = light_rot_m4 * light_trans_m4 * light_pos_v4;
	glUniform3f(lightPosLocation_ui, current_light_pos_v4.x, current_light_pos_v4.y, current_light_pos_v4.z);
	glUniform1i(lightOnLocation_ui, is_light_on);
	glUniform3f(lightColorLocation_ui, 1.0, 1.0, 1.0);
	glUniform3f(viewPosLocation_ui, camera_pos_v3.x, camera_pos_v3.y, camera_pos_v3.z);

	glUniform1i(textureOnLocation_ui, is_texture_on);

	glUniform1f(alphaValueLocation_ui, 1.0f);

	glm::mat4 viewMat_m4 = glm::mat4(1.0f);
	glm::mat4 projMat_m4 = glm::mat4(1.0f);
	viewMat_m4 = glm::lookAt(camera_pos_v3, camera_direction_v3, camera_up_v3) * camera_trans_m4 * camera_rot_m4;

	projMat_m4 = glm::perspective((GLfloat)glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HIGHT, 0.1f, 50.0f);
	projMat_m4 = glm::translate(projMat_m4, glm::vec3(0.0, 0.0, -5.0));

	{
		glUniformMatrix4fv(viewLocation_ui, 1, GL_FALSE, &viewMat_m4[0][0]);
		glUniformMatrix4fv(projectionLocation_ui, 1, GL_FALSE, glm::value_ptr(projMat_m4));

		Figure_floor.Draw(transformLocation_ui);
	}

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}
GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	case 27: exit(0);  break;

	}
	glutPostRedisplay(); //--- ������ �ٲ𶧸��� ��� �ݹ��Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}
GLvoid KeyboardUp(unsigned char key, int x, int y)
{
	switch (key) {

	}
}
GLvoid Special(int key, int x, int y)
{
	switch (key) {

	}
}
GLvoid SpecialUp(int key, int x, int y)
{
	switch (key) {

	}
}

GLvoid Mouse(int button, int state, int x, int y)
{

}

GLvoid Motion(int x, int y)
{

}

GLvoid MouseWheel(int button, int dir, int x, int y)
{

}

GLvoid Timer(int value)
{

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}