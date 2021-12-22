#include "includer.h"
#include "shader_program.h"
#include "Figure.h"
#define WIN_WIDTH 800	// 윈도우 가로 크기
#define WIN_HIGHT 800	// 윈도우 세로 크기


std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<float> F_urd(0.1, 1.0);	// Figure class를 위한 랜덤 생성자

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

glm::vec3 camera_startPos_v3; // 카메라 초기 위치
glm::vec3 camera_startDir_v3; // 카메라 초기 바라보는 방향
glm::vec3 camera_pos_v3; //--- 카메라 현재 위치
glm::vec3 camera_direction_v3; //--- 카메라 현재 바라보는 방향
glm::vec3 camera_up_v3; //--- 카메라 위쪽 방향
glm::mat4 camera_rot_m4; // 카메라 회전 행렬
glm::mat4 camera_trans_m4; // 카메라 이동 행렬

glm::vec4 light_pos_v4; // 빛의 위치
glm::mat4 light_trans_m4; // 빛의 이동행렬
glm::mat4 light_rot_m4; // 빛의 회전행렬
bool is_light_on; // 빛 활성화/비활성화

bool is_texture_on; // 텍스쳐 활성화/비활성화


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

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(WIN_WIDTH, WIN_HIGHT); // 윈도우의 크기 지정
	glutCreateWindow("Tower Defence"); // 윈도우 생성 (윈도우 이름)
		//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
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
	camera_pos_v3 = camera_startPos_v3; //--- 카메라 위치
	camera_direction_v3 = camera_startDir_v3; //--- 카메라 바라보는 방향
	camera_up_v3 = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
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

	glutDisplayFunc(DrawScene); // 출력 콜백함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 콜백함수 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백함수 지정
	glutKeyboardUpFunc(KeyboardUp); // 키보드 입력 콜백함수 지정
	glutSpecialFunc(Special); // 특수 키 입력 콜백함수 지정
	glutSpecialUpFunc(SpecialUp); // 특수 키 입력 콜백함수 지정
	glutMouseFunc(Mouse); // 마우스 입력 콜백함수 지정
	glutMouseWheelFunc(MouseWheel); // 마우스 입력 콜백함수 지정
	glutMotionFunc(Motion);
	glutMainLoop(); // 이벤트 처리 시작
}

GLvoid DrawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	//--- 변경된 배경색 설정
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 변경
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	//--- 변환 행렬 값을 버텍스 세이더로 보내기
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

	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}
GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	case 27: exit(0);  break;

	}
	glutPostRedisplay(); //--- 배경색이 바뀔때마다 출력 콜백함수를 호출하여 화면을 refresh 한다
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