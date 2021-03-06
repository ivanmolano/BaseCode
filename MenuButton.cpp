#include "MenuButton.h"

MenuButton::MenuButton(void(*callback)()) : m_callback(callback) {

	m_bReleased = false;
	
};

void MenuButton::load(const LoaderParams* pParams) {
	MenuButton::Params = pParams;
	if (TextureManager::Instance()->load(pParams->getTextureID(), pParams->getTextureID(), Game::Instance()->getRender())) {
	}
};

void MenuButton::draw()
{
	TextureManager::Instance()->drawFrame(Params->getTextureID(), (int)Params->getX(), (int)Params->getY(), Params->getWidth(), Params->getHeight(), 0, m_currentFrame, Game::Instance()->getRender(), SDL_FLIP_NONE);
}

void MenuButton::update()
{
	Vector2D* pMousePos = InputHandler::Instance()->getMousePosition();

	if (pMousePos->getX() < (Params->getX() + Params->getWidth()) && pMousePos->getX() > Params->getX()	&& pMousePos->getY() < (Params->getY() + Params->getHeight()) && pMousePos->getY() > Params->getY())
	{
		if (InputHandler::Instance()->getMouseButtonState(0) && m_bReleased)
		{
			m_currentFrame = CLICKED;
			m_callback(); // call our callback function
			m_bReleased = false;
		}
		else if (!InputHandler::Instance()->getMouseButtonState(0)) {
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
		
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	InputHandler::Instance()->clean();
}
