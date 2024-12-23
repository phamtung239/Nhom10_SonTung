#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <vector_matrix.h>


using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,   0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,  -0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,   0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },

	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v7-v2-v1
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	// v3-v2-v7
	{ { 0.5f,	 -0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },

	// v4-v7-v6 (back)
	{ { 0.5f,	 -0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	-0.5f,	 -0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);
/*vec3 eye(0.0f, 0.0f, 2.0f); // Vị trí mắt
vec3 at(0.0f, 0.0f, 0.0f);  // Điểm nhìn
vec3 up(0.0f, 1.0f, 0.0f);  // Vector hướng lên*/
int 
	CurrentWidth = 700,
	CurrentHeight = 700;

GLuint
	VaoId,
	VboId,
	VertexShaderId,
	FragmentShaderId,
	ProgramId;
mat4 model_mat_cpp,
	 view_mat_cpp,
	 projection_mat_cpp;
int model_mat_location,
    view_mat_location,
    projection_mat_location;

float n = 0.0f;
float t = 0.0f;
float Alpha = 0.0f;
// ---------------------------------------------------------------------------	
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

// ---------------------------------------------------------------------------	
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
// ---------------------------------------------------------------------------	
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ---------------------------------------------------------------------------	
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

// ---------------------------------------------------------------------------	
void TuongSau() {
	glUniform4f(glGetUniformLocation(ProgramId, "color_shader"), 0.5f, 0.5f, 0.5f, 1.0f);

	mat4 instance = identity_mat4();
	instance = model_mat_cpp * translate(vec3(0.25, 0.0, -2.0)) * scale(vec3(4.0, 1.5, 0.01));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void TuongTrai() {
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * translate(vec3(-1.75, 0.0, -1.0))* rotate_y(90.0) * scale(vec3(2.0, 1.5, 0.01)) ;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void TuongPhai() {
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * translate(vec3(2.25, 0.0, -1.0)) * rotate_y(-90.0) * scale(vec3(2.0, 1.5, 0.01));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void SanNha() {
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * translate(vec3(0.25, -0.76, -1.0)) * scale(vec3(4.0, 0.02, 2.0));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void TuongSauTang2() {
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * translate(vec3(0.25, 1.5, -1.38)) * scale(vec3(4.0, 1.5, 0.01));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	//glUniform4f(color_shader_location, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TuongTraiTang2() {
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * translate(vec3(2.4, 1.47, -1.4)) * rotate_y(90.0) * scale(vec3(2.0, 1.55, 0.01));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	//glUniform4f(color_shader_location, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TuongPhaiTang2() {
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * translate(vec3(-1.8, 1.47, -1.4)) * rotate_y(-90.0) * scale(vec3(2.0, 1.55, 0.01));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	//glUniform4f(color_shader_location, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SanNhaTang2() {
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * translate(vec3(0.25, 0.74, -1.0)) * scale(vec3(4.0, 0.02, 2.0));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	//glUniform4f(color_shader_location, 0.5f, 0.5f, 0.5f, 1.0f); // Màu xám
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

float door_angle = 0.0f; // Góc cửa, 0 là đóng, 90 là mở hoàn toàn
bool is_door_opening = false; // Trạng thái cửa


// Hàm vẽ cánh cửa
void CanhCua() {
	mat4 instance = identity_mat4();

	// Tính toán vị trí và xoay cửa quanh bản lề
	instance = model_mat_cpp
		* translate(vec3(0.0, 0.0, 0.3))  // Vị trí bản lề cửa
		* rotate_y(-door_angle)             // Xoay cửa quanh bản lề
		* translate(vec3(0.7, 0.0, 0.0))   // Đưa cửa ra khỏi bản lề
		* scale(vec3(0.8, 1.2, 0.05));     // Kích thước cánh cửa

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	//glUniform4f(glGetUniformLocation(ProgramId, "color_shader"), 0.5f, 0.2f, 0.1f, 1.0f); // Màu nâu
	glDrawArrays(GL_TRIANGLES, 0, 36);

	TayNamCua(instance);
}
// Hàm vẽ tay nắm cửa	
void TayNamCua(const mat4& door_transform) {
	mat4 instance = door_transform;

	instance = instance
		* translate(vec3(0.8, 0.1, 1.0))  
		* scale(vec3(0.1, 0.1, 0.05));     

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);
	glUniform4f(glGetUniformLocation(ProgramId, "color_shader"), 0.8f, 0.8f, 0.8f, 1.0f); // Màu xám
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
// Hàm cập nhật góc xoay của cửa
void UpdateDoorAngle() {
	if (is_door_opening) {
		if (door_angle < 90.0f) {
			door_angle += 1.0f; // Tăng góc từ từ
		}
	}
	else {
		if (door_angle > 0.0f) {
			door_angle -= 1.0f; // Giảm góc từ từ
		}
	}
}
// ---------------------------------------------------------------------------
void Tang1() {
	TuongSau();	
	TuongTrai();
	TuongPhai();
	SanNha();
	CanhCua();
}
void Tang2() {
	TuongSauTang2();
	TuongTraiTang2();
	TuongPhaiTang2();
	SanNhaTang2();
}
void DisplayFunc(void)
{
	vec3 eye(0.0f, 1.5f, 2.0f),
		at(0.0f, 1.0f, 0.0f),
		up(0.0f, 1.0f, 0.0f);
	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);
	float
		znear = 0.1f,
		zfar = 100.0f,
		fov = 90.0f,
		aspect = (float)CurrentWidth / CurrentHeight;
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glFrontFace(GL_CW);	

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	UpdateDoorAngle(); // Cập nhật góc cửa
	Tang1();
	Tang2();
	
	glutSwapBuffers();
}
// ---------------------------------------------------------------------------	
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ---------------------------------------------------------------------------	
void IdleFunc(void)
{
	glutPostRedisplay();
}
// ---------------------------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{ 
	const float step = 0.1f;
	switch (key) {
	case 'O': // Nhấn 'O' để mở cửa
	case 'o':
		is_door_opening = true;
		break;
	case 'C': // Nhấn 'C' để đóng cửa
	case 'c':
		is_door_opening = false;
		break;
	case 27:
		exit(EXIT_SUCCESS); break;
	}
}
// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);	
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("House");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);	
	glutCloseFunc(CloseFunc);

	glutMainLoop();

	return 0;
}
// --------------------------------------
bool CompileShader(GLuint shaderID) {
	cout << "Compiling shader" << shaderID << "..." << endl;
	glCompileShader(shaderID);
	int result = -1;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		cout << "Shader " << shaderID << " compile failed" << endl;
		int maxLength = 2048;
		int realLength = 0;
		char log[2048];
		glGetShaderInfoLog(shaderID, maxLength, &realLength, log);
		cout << log << endl;
		return false;
	}
	cout << "Shader " << shaderID << " compile successful" << endl;
	return true;
}