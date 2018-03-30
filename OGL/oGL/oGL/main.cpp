#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


int main()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* win = glfwCreateWindow(400, 400, "Hello", NULL, NULL);
	if (!win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(win, key_callback);

	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(win))
	{
		float ratio;
		int width, height;
		glfwGetFramebufferSize(win, &width, &height);
		ratio = width / height;

		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBegin(GL_TRIANGLES);

		glVertex3f(1.0f, 0.5f, 4.0f);    // lower left vertex
		glVertex3f(1.0f, 0.5f,4.0f);    // lower right vertex
		glVertex3f(0.0f, 0.5f, 4.0f);    // upper vertex

		glVertex3f(0.5f, 1.5f, 4.0f);
		glVertex3f(0.5f, 1.5f, 4.0f);
		glVertex3f(0.0f, 1.0f, 4.0f);

		glEnd();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	glfwDestroyWindow(win);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}


void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
