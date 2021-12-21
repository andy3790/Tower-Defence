#pragma once
#include "includer.h"
// Cube Rotate Type List
#define CUBE_X 'x'
#define CUBE_Y 'y'
#define CUBE_Z 'z'
#define CUBE_ROT_T_ORIGIN 'a'
#define CUBE_ROT_T_INDPEN_SELF 'b'
#define CUBE_ROT_T_DPEN_SELF 'c'
#define CUBE_SCALE_T_ORIGIN 'o'
#define CUBE_SCALE_T_SELF 'm'

// Cube MakeCube Type List
#define CUBE_COLOR_POINT_RAND 0
#define CUBE_COLOR_FIGURE_SIDE_RAND 1
#define CUBE_COLOR_FIGURE_RAND 2
#define CUBE_COLOR_FIGURE_GRAY 3
#define CUBE_COLOR_FIGURE_SMOOTH 6
#define CUBE_COLOR_BLOCK_RAND 4
#define CUBE_COLOR_BLOCK_SMOOTH 5
#define CUBE_COLOR_CUBE_SIDE_DEFAULT 7
#define CUBE_COLOR_FIGURE_GRAY_SMOOTH 8

#define CUBE_COLORTYPE_BLOCK 4

// Cube Print Type List
#define CUBE_PRINT_WALL 0
#define CUBE_PRINT_ROAD 1

// Rotate Return Val
#define CUBE_SEQUENCE_END false
#define CUBE_SEQUENCE_ING true

// Cube Print Animation Type List
#define CUBE_ANIMATION_DEFALUT 1
#define CUBE_ANIMATION_MAZE 2

extern std::random_device rd;
extern std::default_random_engine dre;
extern std::uniform_real_distribution<float> F_urd;

class Figure {
private:
	GLfloat point[8][6];
	GLfloat vertex[36][12];
	GLfloat midPoint[3];
	GLfloat size[3];
	GLuint VAO;
	GLuint VBO;
	int countOfData;
	int Shape; // 1 line 2 Cube 3 Pyramid
	float T_val[3]; // x , y , z
	float C_R_val_x; // camera
	float C_R_val_y;
	float rotate_val_x; // rotate
	float rotate_val_y;
	float Self_R_val_x; // self rotate
	float Self_R_val_y;
	float ScaleVal;
	glm::mat4 Tx; //--- translation matrix
	glm::mat4 Ty; //--- translation matrix
	glm::mat4 Tz; //--- translation matrix
	glm::mat4 Rx; //--- rotation matrix
	glm::mat4 Ry; //--- rotation matrix
	glm::mat4 SelfRx; //--- rotation matrix
	glm::mat4 SelfRy; //--- rotation matrix
	glm::mat4 SelfRxy; //--- rotation matrix
	glm::mat4 So; //--- scale matrix
	glm::mat4 Sm; //--- scale matrix
	glm::mat4 TR; //--- transformation matrix
public:
	Figure() {
		Shape = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 6; j++) {
				point[i][j] = 0.0f;
			}
		}
		for (int i = 0; i < 36; i++) {
			for (int j = 0; j < 12; j++) {
				vertex[i][j] = 0.0f;
			}
		}
		for (int i = 0; i < 3; i++) {
			midPoint[i] = 0.0f;
			size[i] = 0.0f;
		}
		VAO = 0;
		VBO = 0;
		countOfData = 0;
		C_R_val_x = 30.0f;
		C_R_val_y = -30.0f;
		rotate_val_x = 0.0f;
		rotate_val_y = 0.0f;
		Self_R_val_x = 0.0f;
		Self_R_val_y = 0.0f;
		T_val[0] = 0.0f;
		T_val[1] = 0.0f;
		T_val[2] = 0.0f;
		ScaleVal = 1.0f;

		Tx = glm::mat4(1.0f);
		Ty = glm::mat4(1.0f);
		Tz = glm::mat4(1.0f);
		Rx = glm::mat4(1.0f);
		Ry = glm::mat4(1.0f);
		SelfRx = glm::mat4(1.0f);
		SelfRy = glm::mat4(1.0f);
		SelfRxy = glm::mat4(1.0f);
		So = glm::mat4(1.0f);
		Sm = glm::mat4(1.0f);
		TR = glm::mat4(1.0f);
	}

	void MakeLine() {
		Shape = 1;
		countOfData = 6;
		rotate_val_x = 0.0f;
		rotate_val_y = 0.0f;
		T_val[0] = 0.0f;
		T_val[1] = 0.0f;
		T_val[2] = 0.0f;

		for (int i = 0; i < countOfData; i++) {
			for (int j = 0; j < 3; j++) {
				vertex[i][j] = 0.0f;
				if (i / 2 == j) {
					float temp = 1;
					for (int k = 0; k < i % 2; k++) { temp *= -1; }
					vertex[i][j] = 1.0f * temp;
				}
			}
		}

		for (int i = 0; i < 3; i++) {
			float tempcolor = F_urd(dre);
			tempcolor = 0.0;
			for (int j = 0; j < countOfData; j++) {
				vertex[j][i + 3] = tempcolor;
				if (j / 2 == i) {
					vertex[j][i + 3] = 1.0f;
				}
			}
		}
		for (int i = 0; i < countOfData; i++) {
			vertex[i][6] = 1.0f;
		}
		MakeTransformMat();
		InitBuffer();
	}
	void MakeLine(float len) {
		Shape = 1;
		countOfData = 6;
		rotate_val_x = 0.0f;
		rotate_val_y = 0.0f;
		T_val[0] = 0.0f;
		T_val[1] = 0.0f;
		T_val[2] = 0.0f;

		for (int i = 0; i < countOfData; i++) {
			for (int j = 0; j < 3; j++) {
				vertex[i][j] = 0.0f;
				if (i / 2 == j) {
					float temp = 1;
					for (int k = 0; k < i % 2; k++) { temp *= -1; }
					vertex[i][j] = len * temp;
				}
			}
		}

		for (int i = 0; i < 3; i++) {
			float tempcolor = F_urd(dre);
			tempcolor = 0.0;
			for (int j = 0; j < countOfData; j++) {
				vertex[j][i + 3] = tempcolor;
				if (j / 2 == i) {
					vertex[j][i + 3] = 1.0f;
				}
			}
		}
		for (int i = 0; i < countOfData; i++) {
			vertex[i][6] = 1.0f;
		}
		MakeTransformMat();
		InitBuffer();
	}
	void MakeLine(const char type) {
		Shape = 1;
		countOfData = 2;
		rotate_val_x = 0.0f;
		rotate_val_y = 0.0f;
		T_val[0] = 0.0f;
		T_val[1] = 0.0f;
		T_val[2] = 0.0f;
		int tempVal = 0;
		if (type == 'x') { tempVal = 0; }
		else if (type == 'y') { tempVal = 2; }
		else if (type == 'z') { tempVal = 4; }

		for (int i = 0; i < countOfData; i++) {
			for (int j = 0; j < 3; j++) {
				vertex[i][j] = 0.0f;
				if ((i + tempVal) / 2 == j) {
					float temp = 1;
					for (int k = 0; k < i % 2; k++) { temp *= -1; }
					vertex[i][j] = 1.0f * temp;
				}
			}
		}

		for (int i = 0; i < 3; i++) {
			float tempcolor = F_urd(dre);
			tempcolor = 0.0;
			for (int j = 0; j < countOfData; j++) {
				vertex[j][i + 3] = tempcolor;
				if ((j + tempVal) / 2 == i) {
					vertex[j][i + 3] = 1.0f;
				}
			}
		}
		for (int i = 0; i < countOfData; i++) {
			vertex[i][6] = 1.0f;
		}
		MakeTransformMat();
		InitBuffer();
	}
	void MakeLine(float sx, float sy, float sz, float ex, float ey, float ez) {
		Shape = 1;
		countOfData = 2;
		rotate_val_x = 0.0f;
		rotate_val_y = 0.0f;
		T_val[0] = 0.0f;
		T_val[1] = 0.0f;
		T_val[2] = 0.0f;

		vertex[0][0] = sx;
		vertex[0][1] = sy;
		vertex[0][2] = sz;
		vertex[1][0] = ex;
		vertex[1][1] = ey;
		vertex[1][2] = ez;

		for (int i = 0; i < countOfData; i++) {
			for (int j = 0; j < 3; j++) {
				vertex[i][j + 3] = F_urd(dre);
			}
		}
		for (int i = 0; i < countOfData; i++) {
			vertex[i][6] = 1.0f;
		}
		MakeTransformMat();
		InitBuffer();
	}
	void MakeLine_N(float sx, float sy, float sz, float ex, float ey, float ez) {
		Shape = 1;
		countOfData = 2;
		rotate_val_x = 0.0f;
		rotate_val_y = 0.0f;
		T_val[0] = 0.0f;
		T_val[1] = 0.0f;
		T_val[2] = 0.0f;

		vertex[0][0] = sx;
		vertex[0][1] = sy;
		vertex[0][2] = sz;
		vertex[1][0] = ex;
		vertex[1][1] = ey;
		vertex[1][2] = ez;

		for (int i = 0; i < countOfData; i++) {
			for (int j = 0; j < 3; j++) {
				vertex[i][j + 3] = F_urd(dre);
			}
			for (int j = 0; j < 3; j++) {
				vertex[i][j + 6] = vertex[1][j] - vertex[0][j];
			}
		}
		for (int i = 0; i < countOfData; i++) {
			vertex[i][6] = 1.0f;
		}
		MakeTransformMat();
		InitBuffer();
	}
	void MakeCube() {
		float tempsize = 0.3f;
		InitCubeData(0.0f, 0.0f, 0.0f, tempsize, tempsize, tempsize);

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				vertex[j + 6 * i][3] = F_urd(dre);
				vertex[j + 6 * i][4] = F_urd(dre);
				vertex[j + 6 * i][5] = F_urd(dre);
			}
		}

		InitCubeNormal();
		//for (int i = 0; i < 3; i++) {
		//	for (int j = 0; j < 6; j++) {
		//		float tempcolor = F_urd(dre);
		//		for (int k = 0; k < 6; k++) {
		//			vertex[k + 6 * j][i + 3] = tempcolor;
		//		}
		//	}
		//}
		MakeTransformMat();
		InitBuffer();
	}
	void MakeCube(float midx, float midy, float midz, float sizex, float sizey, float sizez) {
		InitCubeData(midx, midy, midz, sizex, sizey, sizez);

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				vertex[j + 6 * i][3] = F_urd(dre);
				vertex[j + 6 * i][4] = F_urd(dre);
				vertex[j + 6 * i][5] = F_urd(dre);
			}
		}

		InitCubeNormal();
		MakeTransformMat();
		InitBuffer();
	}
	void MakeCube(float midx, float midy, float midz, float sizex, float sizey, float sizez, float colorR, float colorG, float colorB) {
		InitCubeData(midx, midy, midz, sizex, sizey, sizez);

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				vertex[j + 6 * i][3] = colorR;
				vertex[j + 6 * i][4] = colorG;
				vertex[j + 6 * i][5] = colorB;
			}
		}

		InitCubeNormal();
		MakeTransformMat();
		InitBuffer();
	}
	void MakeCube(float midx, float midy, float midz, float sizex, float sizey, float sizez, float colorR, float colorG, float colorB, float alpha) {
		InitCubeData(midx, midy, midz, sizex, sizey, sizez);
		for (int i = 0; i < countOfData; i++) { // alpha
			vertex[i][6] = alpha;
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				vertex[j + 6 * i][3] = colorR;
				vertex[j + 6 * i][4] = colorG;
				vertex[j + 6 * i][5] = colorB;
			}
		}

		InitCubeNormal();
		MakeTransformMat();
		InitBuffer();
	}
	void MakeCube(float midx, float midy, float midz, float sizex, float sizey, float sizez, float colorR[6], float colorG[6], float colorB[6]) {
		InitCubeData(midx, midy, midz, sizex, sizey, sizez);

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				vertex[j + 6 * i][3] = colorR[i];
				vertex[j + 6 * i][4] = colorG[i];
				vertex[j + 6 * i][5] = colorB[i];
			}
		}
		InitCubeNormal();
		MakeTransformMat();
		InitBuffer();
	}
	void MakeCube(float midx, float midy, float midz, float sizex, float sizey, float sizez, int type) {
		InitCubeData(midx, midy, midz, sizex, sizey, sizez);

		if (type == 0) { // 정점별 같은 색
			int front = 0;
			int back = 4;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 3; j++) {
					point[i][j + 3] = F_urd(dre);
				}
			}

			for (int i = 3; i < 6; i++) {
				// 앞면
				vertex[0 + 6 * 0][i] = point[0 + front][i];
				vertex[1 + 6 * 0][i] = point[3 + front][i];
				vertex[2 + 6 * 0][i] = point[2 + front][i];
				vertex[3 + 6 * 0][i] = point[0 + front][i];
				vertex[4 + 6 * 0][i] = point[2 + front][i];
				vertex[5 + 6 * 0][i] = point[1 + front][i];
				//뒷면
				vertex[0 + 6 * 1][i] = point[1 + back][i];
				vertex[1 + 6 * 1][i] = point[2 + back][i];
				vertex[2 + 6 * 1][i] = point[3 + back][i];
				vertex[3 + 6 * 1][i] = point[1 + back][i];
				vertex[4 + 6 * 1][i] = point[3 + back][i];
				vertex[5 + 6 * 1][i] = point[0 + back][i];
				//오른쪽 면
				vertex[0 + 6 * 2][i] = point[1 + front][i];
				vertex[1 + 6 * 2][i] = point[2 + front][i];
				vertex[2 + 6 * 2][i] = point[2 + back][i];
				vertex[3 + 6 * 2][i] = point[1 + front][i];
				vertex[4 + 6 * 2][i] = point[2 + back][i];
				vertex[5 + 6 * 2][i] = point[1 + back][i];
				//왼쪽 면
				vertex[0 + 6 * 3][i] = point[0 + back][i];
				vertex[1 + 6 * 3][i] = point[3 + back][i];
				vertex[2 + 6 * 3][i] = point[3 + front][i];
				vertex[3 + 6 * 3][i] = point[0 + back][i];
				vertex[4 + 6 * 3][i] = point[3 + front][i];
				vertex[5 + 6 * 3][i] = point[0 + front][i];
				//위쪽 면
				vertex[0 + 6 * 4][i] = point[0 + back][i];
				vertex[1 + 6 * 4][i] = point[0 + front][i];
				vertex[2 + 6 * 4][i] = point[1 + front][i];
				vertex[3 + 6 * 4][i] = point[0 + back][i];
				vertex[4 + 6 * 4][i] = point[1 + front][i];
				vertex[5 + 6 * 4][i] = point[1 + back][i];
				//아래쪽 면
				vertex[0 + 6 * 5][i] = point[3 + front][i];
				vertex[1 + 6 * 5][i] = point[3 + back][i];
				vertex[2 + 6 * 5][i] = point[2 + back][i];
				vertex[3 + 6 * 5][i] = point[3 + front][i];
				vertex[4 + 6 * 5][i] = point[2 + back][i];
				vertex[5 + 6 * 5][i] = point[2 + front][i];
			}
		}
		else if (type == 1) { // 면 별 같은 색
			float tempColor[3];
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 3; k++) {
					tempColor[k] = F_urd(dre);
				}
				for (int k = 0; k < 3; k++) {
					for (int j = 0; j < 6; j++) {
						vertex[j + 6 * i][k + 3] = tempColor[k];
					}
				}
			}
		}
		else if (type == 2) { // 도형별 같은 색
			float tempColor[3];
			for (int k = 0; k < 3; k++) {
				tempColor[k] = F_urd(dre);
			}
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 3; k++) {
					for (int j = 0; j < 6; j++) {
						vertex[j + 6 * i][k + 3] = tempColor[k];
					}
				}
			}
		}
		else if (type == 3) { // 그레이 스케일
			float tempColor;
			tempColor = F_urd(dre);
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 3; k++) {
					for (int j = 0; j < 6; j++) {
						vertex[j + 6 * i][k + 3] = tempColor;
					}
				}
			}
		}
		else { // 잘못된 타입의 경우 vertex 별 랜덤색
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					vertex[j + 6 * i][3] = F_urd(dre);
					vertex[j + 6 * i][4] = F_urd(dre);
					vertex[j + 6 * i][5] = F_urd(dre);
				}
			}
		}
		InitCubeNormal();
		MakeTransformMat();
		InitBuffer();
	}
	void MakeCube(float midx, float midy, float midz, float sizex, float sizey, float sizez, float alpha, int type) {
		InitCubeData(midx, midy, midz, sizex, sizey, sizez);
		for (int i = 0; i < countOfData; i++) { // alpha
			vertex[i][6] = alpha;
		}
		if (type == 0) { // 정점별 같은 색
			int front = 0;
			int back = 4;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 3; j++) {
					point[i][j + 3] = F_urd(dre);
				}
			}

			for (int i = 3; i < 6; i++) {
				// 앞면
				vertex[0 + 6 * 0][i] = point[0 + front][i];
				vertex[1 + 6 * 0][i] = point[3 + front][i];
				vertex[2 + 6 * 0][i] = point[2 + front][i];
				vertex[3 + 6 * 0][i] = point[0 + front][i];
				vertex[4 + 6 * 0][i] = point[2 + front][i];
				vertex[5 + 6 * 0][i] = point[1 + front][i];
				//뒷면
				vertex[0 + 6 * 1][i] = point[1 + back][i];
				vertex[1 + 6 * 1][i] = point[2 + back][i];
				vertex[2 + 6 * 1][i] = point[3 + back][i];
				vertex[3 + 6 * 1][i] = point[1 + back][i];
				vertex[4 + 6 * 1][i] = point[3 + back][i];
				vertex[5 + 6 * 1][i] = point[0 + back][i];
				//오른쪽 면
				vertex[0 + 6 * 2][i] = point[1 + front][i];
				vertex[1 + 6 * 2][i] = point[2 + front][i];
				vertex[2 + 6 * 2][i] = point[2 + back][i];
				vertex[3 + 6 * 2][i] = point[1 + front][i];
				vertex[4 + 6 * 2][i] = point[2 + back][i];
				vertex[5 + 6 * 2][i] = point[1 + back][i];
				//왼쪽 면
				vertex[0 + 6 * 3][i] = point[0 + back][i];
				vertex[1 + 6 * 3][i] = point[3 + back][i];
				vertex[2 + 6 * 3][i] = point[3 + front][i];
				vertex[3 + 6 * 3][i] = point[0 + back][i];
				vertex[4 + 6 * 3][i] = point[3 + front][i];
				vertex[5 + 6 * 3][i] = point[0 + front][i];
				//위쪽 면
				vertex[0 + 6 * 4][i] = point[0 + back][i];
				vertex[1 + 6 * 4][i] = point[0 + front][i];
				vertex[2 + 6 * 4][i] = point[1 + front][i];
				vertex[3 + 6 * 4][i] = point[0 + back][i];
				vertex[4 + 6 * 4][i] = point[1 + front][i];
				vertex[5 + 6 * 4][i] = point[1 + back][i];
				//아래쪽 면
				vertex[0 + 6 * 5][i] = point[3 + front][i];
				vertex[1 + 6 * 5][i] = point[3 + back][i];
				vertex[2 + 6 * 5][i] = point[2 + back][i];
				vertex[3 + 6 * 5][i] = point[3 + front][i];
				vertex[4 + 6 * 5][i] = point[2 + back][i];
				vertex[5 + 6 * 5][i] = point[2 + front][i];
			}
		}
		else if (type == 1) { // 면 별 같은 색
			float tempColor[3];
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 3; k++) {
					tempColor[k] = F_urd(dre);
				}
				for (int k = 0; k < 3; k++) {
					for (int j = 0; j < 6; j++) {
						vertex[j + 6 * i][k + 3] = tempColor[k];
					}
				}
			}
		}
		else if (type == 2) { // 도형별 같은 색
			float tempColor[3];
			for (int k = 0; k < 3; k++) {
				tempColor[k] = F_urd(dre);
			}
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 3; k++) {
					for (int j = 0; j < 6; j++) {
						vertex[j + 6 * i][k + 3] = tempColor[k];
					}
				}
			}
		}
		else if (type == 3) { // 그레이 스케일
			float tempColor;
			tempColor = F_urd(dre);
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 3; k++) {
					for (int j = 0; j < 6; j++) {
						vertex[j + 6 * i][k + 3] = tempColor;
					}
				}
			}
		}
		else { // 잘못된 타입의 경우 vertex 별 랜덤색
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					vertex[j + 6 * i][3] = F_urd(dre);
					vertex[j + 6 * i][4] = F_urd(dre);
					vertex[j + 6 * i][5] = F_urd(dre);
				}
			}
		}
		InitCubeNormal();
		MakeTransformMat();
		InitBuffer();
	}
	void MakePyramid() {
		float tempsize = 0.3f;
		InitPyramidData(0.0f, 0.0f, 0.0f, tempsize, tempsize, tempsize);

		for (int j = 0; j < 3; j++) { point[0][j + 3] = F_urd(dre); }
		for (int j = 0; j < 3; j++) { point[1][j + 3] = F_urd(dre); }
		for (int j = 0; j < 3; j++) { point[2][j + 3] = F_urd(dre); }
		for (int j = 0; j < 3; j++) { point[3][j + 3] = F_urd(dre); }
		for (int j = 0; j < 3; j++) { point[4][j + 3] = F_urd(dre); }

		for (int i = 0; i < 3; i++) {
			//밑면
			vertex[0 + 3 * 0][i + 3] = point[1][i + 3];
			vertex[1 + 3 * 0][i + 3] = point[2][i + 3];
			vertex[2 + 3 * 0][i + 3] = point[3][i + 3];
			vertex[0 + 3 * 1][i + 3] = point[1][i + 3];
			vertex[1 + 3 * 1][i + 3] = point[3][i + 3];
			vertex[2 + 3 * 1][i + 3] = point[0][i + 3];
			//앞면
			vertex[0 + 3 * 2][i + 3] = point[4][i + 3];
			vertex[1 + 3 * 2][i + 3] = point[3][i + 3];
			vertex[2 + 3 * 2][i + 3] = point[2][i + 3];
			//뒷면
			vertex[0 + 3 * 3][i + 3] = point[4][i + 3];
			vertex[1 + 3 * 3][i + 3] = point[1][i + 3];
			vertex[2 + 3 * 3][i + 3] = point[0][i + 3];
			//왼쪽 면
			vertex[0 + 3 * 4][i + 3] = point[4][i + 3];
			vertex[1 + 3 * 4][i + 3] = point[0][i + 3];
			vertex[2 + 3 * 4][i + 3] = point[3][i + 3];
			//오른쪽 면
			vertex[0 + 3 * 5][i + 3] = point[4][i + 3];
			vertex[1 + 3 * 5][i + 3] = point[2][i + 3];
			vertex[2 + 3 * 5][i + 3] = point[1][i + 3];
		}
		InitPyramidNormal();
		MakeTransformMat();
		InitBuffer();
	}
	void MakePyramid(float midx, float midy, float midz, float sizex, float sizey, float sizez) {
		InitPyramidData(midx, midy, midz, sizex, sizey, sizez);
		for (int j = 0; j < 3; j++) { point[0][j + 3] = F_urd(dre); }
		for (int j = 0; j < 3; j++) { point[1][j + 3] = F_urd(dre); }
		for (int j = 0; j < 3; j++) { point[2][j + 3] = F_urd(dre); }
		for (int j = 0; j < 3; j++) { point[3][j + 3] = F_urd(dre); }
		for (int j = 0; j < 3; j++) { point[4][j + 3] = F_urd(dre); }

		for (int i = 0; i < 3; i++) {
			//밑면
			vertex[0 + 3 * 0][i + 3] = point[1][i + 3];
			vertex[1 + 3 * 0][i + 3] = point[2][i + 3];
			vertex[2 + 3 * 0][i + 3] = point[3][i + 3];
			vertex[0 + 3 * 1][i + 3] = point[1][i + 3];
			vertex[1 + 3 * 1][i + 3] = point[3][i + 3];
			vertex[2 + 3 * 1][i + 3] = point[0][i + 3];
			//앞면
			vertex[0 + 3 * 2][i + 3] = point[4][i + 3];
			vertex[1 + 3 * 2][i + 3] = point[3][i + 3];
			vertex[2 + 3 * 2][i + 3] = point[2][i + 3];
			//뒷면
			vertex[0 + 3 * 3][i + 3] = point[4][i + 3];
			vertex[1 + 3 * 3][i + 3] = point[1][i + 3];
			vertex[2 + 3 * 3][i + 3] = point[0][i + 3];
			//왼쪽 면
			vertex[0 + 3 * 4][i + 3] = point[4][i + 3];
			vertex[1 + 3 * 4][i + 3] = point[0][i + 3];
			vertex[2 + 3 * 4][i + 3] = point[3][i + 3];
			//오른쪽 면
			vertex[0 + 3 * 5][i + 3] = point[4][i + 3];
			vertex[1 + 3 * 5][i + 3] = point[2][i + 3];
			vertex[2 + 3 * 5][i + 3] = point[1][i + 3];
		}
		InitPyramidNormal();
		MakeTransformMat();
		InitBuffer();
	}

	void InitCubeData(float midx, float midy, float midz, float sizex, float sizey, float sizez) {
		midPoint[0] = midx;
		midPoint[1] = midy;
		midPoint[2] = midz;
		size[0] = sizex;
		size[1] = sizey;
		size[2] = sizez;

		int front = 0;
		int back = 4;
		Shape = 2;
		countOfData = 36;
		rotate_val_x = 0.0f;
		rotate_val_y = 0.0f;
		T_val[0] = 0.0f;
		T_val[1] = 0.0f;
		T_val[2] = 0.0f;

		point[0][0] = midx - sizex;
		point[0][1] = midy + sizey;
		point[0][2] = midz + sizez;

		point[1][0] = midx + sizex;
		point[1][1] = midy + sizey;
		point[1][2] = midz + sizez;

		point[2][0] = midx + sizex;
		point[2][1] = midy - sizey;
		point[2][2] = midz + sizez;

		point[3][0] = midx - sizex;
		point[3][1] = midy - sizey;
		point[3][2] = midz + sizez;

		for (int i = 0; i < 4; i++) {
			point[i + 4][0] = point[i][0];
			point[i + 4][1] = point[i][1];
			point[i + 4][2] = point[i][2] - (sizez * 2);
		}

		for (int i = 0; i < 3; i++) {
			// 앞면
			vertex[0 + 6 * 0][i] = point[0 + front][i];
			vertex[1 + 6 * 0][i] = point[3 + front][i];
			vertex[2 + 6 * 0][i] = point[2 + front][i];
			vertex[3 + 6 * 0][i] = point[0 + front][i];
			vertex[4 + 6 * 0][i] = point[2 + front][i];
			vertex[5 + 6 * 0][i] = point[1 + front][i];
			//뒷면
			vertex[0 + 6 * 1][i] = point[1 + back][i];
			vertex[1 + 6 * 1][i] = point[2 + back][i];
			vertex[2 + 6 * 1][i] = point[3 + back][i];
			vertex[3 + 6 * 1][i] = point[1 + back][i];
			vertex[4 + 6 * 1][i] = point[3 + back][i];
			vertex[5 + 6 * 1][i] = point[0 + back][i];
			//오른쪽 면
			vertex[0 + 6 * 2][i] = point[1 + front][i];
			vertex[1 + 6 * 2][i] = point[2 + front][i];
			vertex[2 + 6 * 2][i] = point[2 + back][i];
			vertex[3 + 6 * 2][i] = point[1 + front][i];
			vertex[4 + 6 * 2][i] = point[2 + back][i];
			vertex[5 + 6 * 2][i] = point[1 + back][i];
			//왼쪽 면
			vertex[0 + 6 * 3][i] = point[0 + back][i];
			vertex[1 + 6 * 3][i] = point[3 + back][i];
			vertex[2 + 6 * 3][i] = point[3 + front][i];
			vertex[3 + 6 * 3][i] = point[0 + back][i];
			vertex[4 + 6 * 3][i] = point[3 + front][i];
			vertex[5 + 6 * 3][i] = point[0 + front][i];
			//위쪽 면
			vertex[0 + 6 * 4][i] = point[0 + back][i];
			vertex[1 + 6 * 4][i] = point[0 + front][i];
			vertex[2 + 6 * 4][i] = point[1 + front][i];
			vertex[3 + 6 * 4][i] = point[0 + back][i];
			vertex[4 + 6 * 4][i] = point[1 + front][i];
			vertex[5 + 6 * 4][i] = point[1 + back][i];
			//아래쪽 면
			vertex[0 + 6 * 5][i] = point[3 + front][i];
			vertex[1 + 6 * 5][i] = point[3 + back][i];
			vertex[2 + 6 * 5][i] = point[2 + back][i];
			vertex[3 + 6 * 5][i] = point[3 + front][i];
			vertex[4 + 6 * 5][i] = point[2 + back][i];
			vertex[5 + 6 * 5][i] = point[2 + front][i];
		}
		for (int i = 0; i < countOfData; i++) { // alpha
			vertex[i][6] = 1.0f;
		}
		InitCubeUVPos();
	}
	void InitPyramidData(float midx, float midy, float midz, float sizex, float sizey, float sizez) {
		midPoint[0] = midx;
		midPoint[1] = midy;
		midPoint[2] = midz;
		size[0] = sizex;
		size[1] = sizey;
		size[2] = sizez;

		Shape = 3;
		countOfData = 18;
		rotate_val_x = 0.0f;
		rotate_val_y = 0.0f;
		T_val[0] = 0.0f;
		T_val[1] = 0.0f;
		T_val[2] = 0.0f;

		point[0][0] = midx - sizex;
		point[0][1] = midy - sizey;
		point[0][2] = midz - sizez;

		point[1][0] = midx + sizex;
		point[1][1] = midy - sizey;
		point[1][2] = midz - sizez;

		point[2][0] = midx + sizex;
		point[2][1] = midy - sizey;
		point[2][2] = midz + sizez;

		point[3][0] = midx - sizex;
		point[3][1] = midy - sizey;
		point[3][2] = midz + sizez;

		point[4][0] = midx;
		point[4][1] = midy + sizey;
		point[4][2] = midz;


		for (int i = 0; i < 3; i++) {
			//밑면
			vertex[0 + 3 * 0][i] = point[1][i];
			vertex[1 + 3 * 0][i] = point[2][i];
			vertex[2 + 3 * 0][i] = point[3][i];
			vertex[0 + 3 * 1][i] = point[1][i];
			vertex[1 + 3 * 1][i] = point[3][i];
			vertex[2 + 3 * 1][i] = point[0][i];
			//앞면
			vertex[0 + 3 * 2][i] = point[4][i];
			vertex[1 + 3 * 2][i] = point[3][i];
			vertex[2 + 3 * 2][i] = point[2][i];
			//뒷면
			vertex[0 + 3 * 3][i] = point[4][i];
			vertex[1 + 3 * 3][i] = point[1][i];
			vertex[2 + 3 * 3][i] = point[0][i];
			//왼쪽 면
			vertex[0 + 3 * 4][i] = point[4][i];
			vertex[1 + 3 * 4][i] = point[0][i];
			vertex[2 + 3 * 4][i] = point[3][i];
			//오른쪽 면
			vertex[0 + 3 * 5][i] = point[4][i];
			vertex[1 + 3 * 5][i] = point[2][i];
			vertex[2 + 3 * 5][i] = point[1][i];
		}
		for (int i = 0; i < countOfData; i++) {
			vertex[i][6] = 1.0f;
		}
		InitPyramidUVPos();
	}

	glm::vec3 calNormal(int sv, int sel, int vcount)
	{
		float v1[3], v2[3], cube_sideSelecter_i[3];
		static const int x = 0;
		static const int y = 1;
		static const int z = 2;

		v1[x] = vertex[sv + 0 + vcount * sel][x] - vertex[sv + 1 + vcount * sel][x];
		v1[y] = vertex[sv + 0 + vcount * sel][y] - vertex[sv + 1 + vcount * sel][y];
		v1[z] = vertex[sv + 0 + vcount * sel][z] - vertex[sv + 1 + vcount * sel][z];

		v2[x] = vertex[sv + 1 + vcount * sel][x] - vertex[sv + 2 + vcount * sel][x];
		v2[y] = vertex[sv + 1 + vcount * sel][y] - vertex[sv + 2 + vcount * sel][y];
		v2[z] = vertex[sv + 1 + vcount * sel][z] - vertex[sv + 2 + vcount * sel][z];

		cube_sideSelecter_i[x] = v1[y] * v2[z] - v1[z] * v2[y];
		cube_sideSelecter_i[y] = v1[z] * v2[x] - v1[x] * v2[z];
		cube_sideSelecter_i[z] = v1[x] * v2[y] - v1[y] * v2[x];

		float tlen = (float)sqrt(cube_sideSelecter_i[x] * cube_sideSelecter_i[x] + cube_sideSelecter_i[y] * cube_sideSelecter_i[y] + cube_sideSelecter_i[z] * cube_sideSelecter_i[z]);

		return glm::vec3(cube_sideSelecter_i[x] / tlen, cube_sideSelecter_i[y] / tlen, cube_sideSelecter_i[z] / tlen);
	}
	void InitCubeNormal() {
		glm::vec3 t[6];
		for (int i = 0; i < 6; i++) {
			t[i] = calNormal(0, i, 6);
		}

		for (int i = 0; i < 6; i++) {	// 노멀 저장
			for (int j = 0; j < 3; j++) {
				//앞면
				vertex[i + 6 * 0][j + 7] = t[0][j];
				//뒷면
				vertex[i + 6 * 1][j + 7] = t[1][j];
				//오른쪽 면
				vertex[i + 6 * 2][j + 7] = t[2][j];
				//왼쪽 면
				vertex[i + 6 * 3][j + 7] = t[3][j];
				//위쪽 면
				vertex[i + 6 * 4][j + 7] = t[4][j];
				//아래쪽 면
				vertex[i + 6 * 5][j + 7] = t[5][j];
			}
		}
	}
	void InitPyramidNormal() {
		glm::vec3 t[5];
		for (int i = 0; i < 5; i++) {
			t[i] = calNormal(0, i + 1, 3);
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//밑면
				vertex[j + 3 * 0][7 + i] = t[0][i];
				vertex[j + 3 * 1][7 + i] = t[0][i];
				//앞면
				vertex[j + 3 * 2][7 + i] = t[1][i];
				//뒷면
				vertex[j + 3 * 3][7 + i] = t[2][i];
				//왼쪽 면
				vertex[j + 3 * 4][7 + i] = t[3][i];
				//오른쪽 면
				vertex[j + 3 * 5][7 + i] = t[4][i];
			}
		}
	}

	void InitCubeUVPos() {
		const int U = 10;
		const int V = 11;
		// 앞면
		vertex[0 + 6 * 0][U] = 0.0f;			vertex[0 + 6 * 0][V] = 1.0f;
		vertex[1 + 6 * 0][U] = 0.0f;			vertex[1 + 6 * 0][V] = 0.0f;
		vertex[2 + 6 * 0][U] = 1.0f;			vertex[2 + 6 * 0][V] = 0.0f;
		vertex[3 + 6 * 0][U] = 0.0f;			vertex[3 + 6 * 0][V] = 1.0f;
		vertex[4 + 6 * 0][U] = 1.0f;			vertex[4 + 6 * 0][V] = 0.0f;
		vertex[5 + 6 * 0][U] = 1.0f;			vertex[5 + 6 * 0][V] = 1.0f;
		//뒷면
		vertex[0 + 6 * 1][U] = 0.0f;			vertex[0 + 6 * 1][V] = 1.0f;
		vertex[1 + 6 * 1][U] = 0.0f;			vertex[1 + 6 * 1][V] = 0.0f;
		vertex[2 + 6 * 1][U] = 1.0f;			vertex[2 + 6 * 1][V] = 0.0f;
		vertex[3 + 6 * 1][U] = 0.0f;			vertex[3 + 6 * 1][V] = 1.0f;
		vertex[4 + 6 * 1][U] = 1.0f;			vertex[4 + 6 * 1][V] = 0.0f;
		vertex[5 + 6 * 1][U] = 1.0f;			vertex[5 + 6 * 1][V] = 1.0f;
		//오른쪽 면
		vertex[0 + 6 * 2][U] = 0.0f;			vertex[0 + 6 * 2][V] = 1.0f;
		vertex[1 + 6 * 2][U] = 0.0f;			vertex[1 + 6 * 2][V] = 0.0f;
		vertex[2 + 6 * 2][U] = 1.0f;			vertex[2 + 6 * 2][V] = 0.0f;
		vertex[3 + 6 * 2][U] = 0.0f;			vertex[3 + 6 * 2][V] = 1.0f;
		vertex[4 + 6 * 2][U] = 1.0f;			vertex[4 + 6 * 2][V] = 0.0f;
		vertex[5 + 6 * 2][U] = 1.0f;			vertex[5 + 6 * 2][V] = 1.0f;
		//왼쪽 면
		vertex[0 + 6 * 3][U] = 0.0f;			vertex[0 + 6 * 3][V] = 1.0f;
		vertex[1 + 6 * 3][U] = 0.0f;			vertex[1 + 6 * 3][V] = 0.0f;
		vertex[2 + 6 * 3][U] = 1.0f;			vertex[2 + 6 * 3][V] = 0.0f;
		vertex[3 + 6 * 3][U] = 0.0f;			vertex[3 + 6 * 3][V] = 1.0f;
		vertex[4 + 6 * 3][U] = 1.0f;			vertex[4 + 6 * 3][V] = 0.0f;
		vertex[5 + 6 * 3][U] = 1.0f;			vertex[5 + 6 * 3][V] = 1.0f;
		//위쪽 면
		vertex[0 + 6 * 4][U] = 0.0f;			vertex[0 + 6 * 4][V] = 1.0f;
		vertex[1 + 6 * 4][U] = 0.0f;			vertex[1 + 6 * 4][V] = 0.0f;
		vertex[2 + 6 * 4][U] = 1.0f;			vertex[2 + 6 * 4][V] = 0.0f;
		vertex[3 + 6 * 4][U] = 0.0f;			vertex[3 + 6 * 4][V] = 1.0f;
		vertex[4 + 6 * 4][U] = 1.0f;			vertex[4 + 6 * 4][V] = 0.0f;
		vertex[5 + 6 * 4][U] = 1.0f;			vertex[5 + 6 * 4][V] = 1.0f;
		//아래쪽 면
		vertex[0 + 6 * 5][U] = 0.0f;			vertex[0 + 6 * 5][V] = 1.0f;
		vertex[1 + 6 * 5][U] = 0.0f;			vertex[1 + 6 * 5][V] = 0.0f;
		vertex[2 + 6 * 5][U] = 1.0f;			vertex[2 + 6 * 5][V] = 0.0f;
		vertex[3 + 6 * 5][U] = 0.0f;			vertex[3 + 6 * 5][V] = 1.0f;
		vertex[4 + 6 * 5][U] = 1.0f;			vertex[4 + 6 * 5][V] = 0.0f;
		vertex[5 + 6 * 5][U] = 1.0f;			vertex[5 + 6 * 5][V] = 1.0f;
	}
	void InitPyramidUVPos() {
		const int U = 10;
		const int V = 11;

		for (int i = 0; i < 3; i++) {
			//밑면
			vertex[0 + 3 * 0][U] = 0.0f;			vertex[0 + 3 * 0][V] = 0.0f;
			vertex[1 + 3 * 0][U] = 0.0f;			vertex[1 + 3 * 0][V] = 1.0f;
			vertex[2 + 3 * 0][U] = 1.0f;			vertex[2 + 3 * 0][V] = 1.0f;
			vertex[0 + 3 * 1][U] = 0.0f;			vertex[0 + 3 * 1][V] = 0.0f;
			vertex[1 + 3 * 1][U] = 1.0f;			vertex[1 + 3 * 1][V] = 1.0f;
			vertex[2 + 3 * 1][U] = 1.0f;			vertex[2 + 3 * 1][V] = 0.0f;
			//앞면
			vertex[0 + 3 * 2][U] = 0.5f;			vertex[0 + 3 * 2][V] = 1.0f;
			vertex[1 + 3 * 2][U] = 0.0f;			vertex[1 + 3 * 2][V] = 0.0f;
			vertex[2 + 3 * 2][U] = 1.0f;			vertex[2 + 3 * 2][V] = 0.0f;
			//뒷면
			vertex[0 + 3 * 3][U] = 0.5f;			vertex[0 + 3 * 3][V] = 1.0f;
			vertex[1 + 3 * 3][U] = 0.0f;			vertex[1 + 3 * 3][V] = 0.0f;
			vertex[2 + 3 * 3][U] = 1.0f;			vertex[2 + 3 * 3][V] = 0.0f;
			//왼쪽 면
			vertex[0 + 3 * 4][U] = 0.5f;			vertex[0 + 3 * 4][V] = 1.0f;
			vertex[1 + 3 * 4][U] = 0.0f;			vertex[1 + 3 * 4][V] = 0.0f;
			vertex[2 + 3 * 4][U] = 1.0f;			vertex[2 + 3 * 4][V] = 0.0f;
			//오른쪽 면
			vertex[0 + 3 * 5][U] = 0.5f;			vertex[0 + 3 * 5][V] = 1.0f;
			vertex[1 + 3 * 5][U] = 0.0f;			vertex[1 + 3 * 5][V] = 0.0f;
			vertex[2 + 3 * 5][U] = 1.0f;			vertex[2 + 3 * 5][V] = 0.0f;
		}
	}

	void Reset() {
		Tx = glm::mat4(1.0f);
		Ty = glm::mat4(1.0f);
		Tz = glm::mat4(1.0f);
		Rx = glm::mat4(1.0f);
		Ry = glm::mat4(1.0f);
		SelfRx = glm::mat4(1.0f);
		SelfRy = glm::mat4(1.0f);
		SelfRxy = glm::mat4(1.0f);
		So = glm::mat4(1.0f);
		Sm = glm::mat4(1.0f);
		TR = glm::mat4(1.0f);
		rotate_val_x = 0.0f;
		rotate_val_y = 0.0f;
		Self_R_val_x = 0.0f;
		Self_R_val_y = 0.0f;
		ScaleVal = 1.0f;

		MakeTransformMat();
	}

	void Translate(float x, float y, float z) {
		Tx = glm::translate(Tx, glm::vec3(x, 0.0, 0.0)); //--- x축으로 translation
		Ty = glm::translate(Ty, glm::vec3(0.0, y, 0.0)); //--- y축으로 translation
		Tz = glm::translate(Tz, glm::vec3(0.0, 0.0, z)); //--- z축으로 translation
		ChangeTransformMat();
	}
	void Translate(const char type, float val) {
		if (type == 'x') {
			Tx = glm::translate(Tx, glm::vec3(val, 0.0, 0.0)); //--- x축으로 translation
		}
		else if (type == 'y') {
			Ty = glm::translate(Ty, glm::vec3(0.0, val, 0.0)); //--- y축으로 translation
		}
		else if (type == 'z') {
			Tz = glm::translate(Tz, glm::vec3(0.0, 0.0, val)); //--- z축으로 translation
		}
		ChangeTransformMat();
	}
	void Translate_Reset(float x, float y, float z) {
		Tx = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0, 0.0)); //--- x축으로 translation
		Ty = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, y, 0.0)); //--- y축으로 translation
		Tz = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, z)); //--- z축으로 translation
		ChangeTransformMat();
	}
	void Translate_Reset(const char type, float val) {
		if (type == 'x') {
			Tx = glm::translate(glm::mat4(1.0f), glm::vec3(val, 0.0, 0.0)); //--- x축으로 translation
		}
		else if (type == 'y') {
			Ty = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, val, 0.0)); //--- y축으로 translation
		}
		else if (type == 'z') {
			Tz = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, val)); //--- z축으로 translation
		}
		ChangeTransformMat();
	}

	void Rotate(const char type, const char type2, float degree) {
		if (type == 'a') { // 원점 기준 회전
			if (type2 == 'x') {
				Rx = glm::rotate(Rx, (GLfloat)glm::radians(degree), glm::vec3(1.0, 0.0, 0.0)); //--- x축에대하여 회전
			}
			else if (type2 == 'y') {
				Ry = glm::rotate(Ry, (GLfloat)glm::radians(degree), glm::vec3(0.0, 1.0, 0.0)); //--- y축에대하여 회전
			}
			else if (type2 == 'z') {
				Ry = glm::rotate(Ry, (GLfloat)glm::radians(degree), glm::vec3(0.0, 0.0, 1.0)); //--- z축에대하여 회전
			}
		}
		else if (type == 'b') { // 회전 영향을 안받는 제자리 회전
			if (type2 == 'x') {
				SelfRxy = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(1.0, 0.0, 0.0)) * SelfRxy; //--- x축에대하여 회전
			}
			else if (type2 == 'y') {
				SelfRxy = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(0.0, 1.0, 0.0)) * SelfRxy; //--- y축에대하여 회전
			}
			else if (type2 == 'z') {
				SelfRxy = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(0.0, 0.0, 1.0)) * SelfRxy; //--- z축에대하여 회전
			}
		}
		else if (type == 'c') { // 회전 영향을 받는 제자리 회전
			if (type2 == 'x') {
				SelfRxy = glm::rotate(SelfRxy, (GLfloat)glm::radians(degree), glm::vec3(1.0, 0.0, 0.0)); //--- x축에대하여 회전
			}
			else if (type2 == 'y') {
				SelfRxy = glm::rotate(SelfRxy, (GLfloat)glm::radians(degree), glm::vec3(0.0, 1.0, 0.0)); //--- y축에대하여 회전
			}
			else if (type2 == 'z') {
				SelfRxy = glm::rotate(SelfRxy, (GLfloat)glm::radians(degree), glm::vec3(0.0, 0.0, 1.0)); //--- z축에대하여 회전
			}
		}
		ChangeTransformMat();
	}
	void Rotate(glm::vec3 shaft, float degree) {
		SelfRxy = glm::rotate(SelfRxy, (GLfloat)glm::radians(degree), shaft); //--- 임의의 축에 대하여 회전
		ChangeTransformMat();
	}

	void Rotate_Reset(const char type, const char type2, float degree) {
		if (type == 'a') { // 원점 기준 회전
			if (type2 == 'x') {
				Rx = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(1.0, 0.0, 0.0)); //--- x축에대하여 회전
			}
			else if (type2 == 'y') {
				Ry = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(0.0, 1.0, 0.0)); //--- y축에대하여 회전
			}
			else if (type2 == 'z') {
				Ry = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(0.0, 0.0, 1.0)); //--- z축에대하여 회전
			}
		}
		else if (type == 'b') { // 회전 영향을 안받는 제자리 회전
			if (type2 == 'x') {
				SelfRxy = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(1.0, 0.0, 0.0)) * SelfRxy; //--- x축에대하여 회전
			}
			else if (type2 == 'y') {
				SelfRxy = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(0.0, 1.0, 0.0)) * SelfRxy; //--- y축에대하여 회전
			}
			else if (type2 == 'z') {
				SelfRxy = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(0.0, 0.0, 1.0)) * SelfRxy; //--- z축에대하여 회전
			}
		}
		else if (type == 'c') { // 회전 영향을 받는 제자리 회전
			if (type2 == 'x') {
				SelfRxy = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(1.0, 0.0, 0.0)); //--- x축에대하여 회전
			}
			else if (type2 == 'y') {
				SelfRxy = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(0.0, 1.0, 0.0)); //--- y축에대하여 회전
			}
			else if (type2 == 'z') {
				SelfRxy = glm::rotate(glm::mat4(1.0f), (GLfloat)glm::radians(degree), glm::vec3(0.0, 0.0, 1.0)); //--- z축에대하여 회전
			}
		}
		ChangeTransformMat();
	}

	void Scale(const char type, float sizex, float sizey, float sizez) {
		if (type == 'o') { // 원점을 기준으로 스케일링
			So = glm::scale(So, glm::vec3(sizex, sizey, sizez));
		}
		else if (type == 'm') { // 자신을 기준으로 스케일링
			Sm = glm::scale(Sm, glm::vec3(sizex, sizey, sizez));
		}
		ChangeTransformMat();
	}

	void PrintPoints() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << point[i][j] << '\t';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
	void Erasing() {
		ScaleVal -= 0.05f;
		Sm = glm::scale(glm::mat4(1.0f), glm::vec3(ScaleVal, ScaleVal, ScaleVal));
		ChangeTransformMat();
	}
	float GetScaleVal() { return ScaleVal; }

	GLvoid Draw() {
		if (ScaleVal < 0.1) { return; }
		glBindVertexArray(VAO);
		if (Shape == 1) {
			glDrawArrays(GL_LINES, 0, countOfData);
		}
		else if (Shape == 2) {
			glDrawArrays(GL_TRIANGLES, 0, countOfData);
		}
		else if (Shape == 3) {
			glDrawArrays(GL_TRIANGLES, 0, countOfData);
		}
	}
	GLvoid Draw(int sel) {
		glBindVertexArray(VAO);
		if (Shape == 1) {
			glDrawArrays(GL_LINES, sel * 3, 2);
		}
		else if (Shape == 2) {
			glDrawArrays(GL_TRIANGLES, sel * 6, 6);
		}
		else if (Shape == 3) {
			glDrawArrays(GL_TRIANGLES, sel * 3, 3);
		}
	}
	GLvoid Draw(unsigned int transformLocation) {
		glBindVertexArray(VAO);
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(TR));
		if (Shape == 1) {
			glDrawArrays(GL_LINES, 0, countOfData);
		}
		else if (Shape == 2) {
			glDrawArrays(GL_TRIANGLES, 0, countOfData);
		}
		else if (Shape == 3) {
			glDrawArrays(GL_TRIANGLES, 0, countOfData);
		}
	}
	GLvoid Draw(unsigned int transformLocation, int sel) {
		glBindVertexArray(VAO);
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(TR));
		if (Shape == 1) {
			glDrawArrays(GL_LINES, sel * 3, 2);
		}
		else if (Shape == 2) {
			glDrawArrays(GL_TRIANGLES, sel * 6, 6);
		}
		else if (Shape == 3) {
			glDrawArrays(GL_TRIANGLES, sel * 3, 3);
		}
	}
	GLvoid Draw(unsigned int transformLocation, glm::mat4 afterMat) {
		glBindVertexArray(VAO);
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(afterMat * TR));
		if (Shape == 1) {
			glDrawArrays(GL_LINES, 0, countOfData);
		}
		else if (Shape == 2) {
			glDrawArrays(GL_TRIANGLES, 0, countOfData);
		}
		else if (Shape == 3) {
			glDrawArrays(GL_TRIANGLES, 0, countOfData);
		}
	}

	GLvoid MakeTransformMat() {
		//--- 변환 행렬 만들기

		Tx = glm::translate(Tx, glm::vec3(T_val[0], 0.0, 0.0)); //--- x축으로 translation
		Ty = glm::translate(Ty, glm::vec3(0.0, T_val[1], 0.0)); //--- y축으로 translation
		Tz = glm::translate(Tz, glm::vec3(0.0, 0.0, T_val[2])); //--- z축으로 translation
		Rx = glm::rotate(Rx, (GLfloat)glm::radians(rotate_val_x), glm::vec3(1.0, 0.0, 0.0)); //--- x축에대하여 회전
		Ry = glm::rotate(Ry, (GLfloat)glm::radians(rotate_val_y), glm::vec3(0.0, 1.0, 0.0)); //--- y축에대하여 회전

		//TR = Rx * Txyz * Ry; //--- 합성 변환 행렬: rotate -> translat
		ChangeTransformMat();
	}

	GLvoid ChangeTransformMat() {
		if (Shape == 0) {
			TR = So * Ry * Rx * Tz * Ty * Tx * SelfRxy * Sm;
		}
		else if (Shape == 1) {
			TR =  Ry * Rx * Tz * Tx * Ty;
		}
		else if (Shape == 2 || Shape == 3) {
			TR = So * Ry * Rx * Tz * Ty * Tx * SelfRxy * Sm;
		}
		else if (Shape == 4) {
			TR = Tz * Rx * Tx * Ry * Ty;
		}
		TR = TR;
	}

	bool CrashCheck(Figure* b) {
		float a_min[3];
		float a_max[3];
		float b_min[3];
		float b_max[3];
		float* btempMid = b->GetMidPos();
		float* bSize = b->GetSize();
		glm::vec4 bMid = b->GetTransformMat() * glm::vec4(btempMid[0], btempMid[1], btempMid[2], 1.0f);

		for (int i = 0; i < 3; i++) {
			a_min[i] = midPoint[i] - size[i];
			a_max[i] = midPoint[i] + size[i];
			b_min[i] = bMid[i] - bSize[i];
			b_max[i] = bMid[i] + bSize[i];
			if (a_min[i] > b_max[i] || a_max[i] < b_min[i]) {
				return false;
			}
		}
		return true;
	}
	bool CrashCheck(Figure* b, glm::mat4 mymat) {
		float a_min[3];
		float a_max[3];
		float b_min[3];
		float b_max[3];
		float* btempMid = b->GetMidPos();
		float* bSize = b->GetSize();
		glm::vec4 bMid = b->GetTransformMat() * glm::vec4(btempMid[0], btempMid[1], btempMid[2], 1.0f);
		glm::vec4 aMid = mymat * glm::vec4(midPoint[0], midPoint[1], midPoint[2], 1.0f);

		for (int i = 0; i < 3; i++) {
			a_min[i] = aMid[i] - size[i];
			a_max[i] = aMid[i] + size[i];
			b_min[i] = bMid[i] - bSize[i];
			b_max[i] = bMid[i] + bSize[i];
			if (a_min[i] > b_max[i] || a_max[i] < b_min[i]) {
				return false;
			}
		}
		return true;
	}

	glm::mat4 GetTransformMat() {
		return TR;
	}
	float* GetMidPos() { return midPoint; }
	glm::vec3 GetNowMidPosVec() { return glm::vec3(TR * glm::vec4(midPoint[0], midPoint[1], midPoint[2], 1.0f)); }
	float* GetSize() { return size; }

	GLuint InitBuffer()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, (countOfData * 12) * sizeof(GLfloat), vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (void*)(10 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);
		return VAO;
	}

	~Figure() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
};