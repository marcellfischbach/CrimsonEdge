#include <ceLauncher/window/sdlinputsystem.hh>


namespace ce::launcher
{

SDLInputSystem::SDLInputSystem(SDLKeyboard* keyboard, SDLMouse* mouse)
  : iInputSystem()
  , m_keyboard(keyboard)
  , m_mouse(mouse)
{
  CE_CLASS_GEN_CONSTR;
}


iKeyboard* SDLInputSystem::GetKeyboard() const
{
  return m_keyboard;
}

iMouse* SDLInputSystem::GetMouse() const
{
  return m_mouse;
}

}