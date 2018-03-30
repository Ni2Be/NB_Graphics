#include "NB_Test_Application.h"



NB::NB_Test_Application::NB_Test_Application()
	:
	m_delta_time(0.0f),
	m_last_frame(0.0f),
	m_window(500, 500, "")
{
}

NB::NB_Test_Application::~NB_Test_Application()
{
	glfwTerminate();
}

void NB::NB_Test_Application::run()
{
	application_loop();
}

void NB::NB_Test_Application::application_loop()
{
	while (m_window.is_running())
	{
		m_window.clear();

		//FPS
		m_current_frame = glfwGetTime();
		m_delta_time    = static_cast<GLfloat>(m_current_frame - m_last_frame);
		m_last_frame    = m_current_frame;
		m_window.set_title(std::to_string(1 / m_delta_time));


		glfwPollEvents();

		m_window.update();
	}
}
