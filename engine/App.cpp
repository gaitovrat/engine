#include "App.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

#include "Resource/ResourceManager.hpp"
#include "KeyboardEvent/KeyboardEvent.hpp"
#include "KeyboardEvent/EKey.hpp"
#include "Configuration.hpp"
#include "Light/SpotLight.hpp"
#include "Camera.hpp"

App::App(const int width, const int height, const char *title) :
    m_window(width, height, title)
{
    m_window.EnableVSync();
    RegisterDefaultKeyEvents();
	m_scenes.emplace_back();
}

void App::Run()
{ 
    m_scenes[Configuration::Level].UpdateObjects();

    while (m_window.ShoudlClose() == false)
    {
		m_renderer.Draw(m_scenes[Configuration::Level].GetSky());
        m_renderer.Clear();
        /*for (auto& object : m_scenes[Configuration::Level].GetObjects())
        {
            m_renderer.Draw(object);
        }*/

        m_window.PollEvents();
        m_window.SwapBuffers();
    }
}

void App::RegisterDefaultKeyEvents()
{
	for (const std::vector listeners = {
		     KeyboardEventListener(m_window, KEY_S, []() {
			     Camera::GetInstance().MoveBackward(Configuration::PlayerSpeed);
			     std::cout << "move backward clicked\n";
		     }),
		     KeyboardEventListener(m_window, KEY_W, []() {
			     Camera::GetInstance().MoveForward(Configuration::PlayerSpeed);
			     std::cout << "move backward clicked\n";
		     }),
		     KeyboardEventListener(m_window, KEY_A, []() {
			     Camera::GetInstance().MoveLeft(Configuration::PlayerSpeed);
			     std::cout << "move backward clicked\n";
		     }),
		     KeyboardEventListener(m_window, KEY_D, []() {
			     Camera::GetInstance().MoveRight(Configuration::PlayerSpeed);
			     std::cout << "move backward clicked\n";
		     }),
		     KeyboardEventListener(m_window, KEY_S, []() {
			     Camera::GetInstance().MoveBackward(Configuration::PlayerSpeed);
			     std::cout << "move backward clicked\n";
		     }),
		     KeyboardEventListener(m_window, KEY_ESCAPE, [this]() {
			     m_window.Close();
		     })
	     }; const auto& listener : listeners)
    {
        KeyboardEvent::GetInstance().AddListener(listener);
    }
}
