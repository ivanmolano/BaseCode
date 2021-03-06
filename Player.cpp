#include "Player.h"

Player::Player() {

	m_velocity.setX(0.1);
	m_velocity.setY(0);
	m_friction.setX(m_velocity.getX() - 0.08);
};

Player::~Player() {};

void Player::load(const LoaderParams* pParams)
{
	m_textureID = pParams->getTextureID();
	m_position.setX(pParams->getX());
	m_position.setY(pParams->getY());

	//m_x = pParams->getX(); 
	//m_y = pParams->getY();

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	
	m_currentRow = 0;
	m_sprite = pParams->getSprits();
	//m_currentFrame = 0;
	m_velocity.setX(0);
	m_velocity.setY(0);
}

void Player::draw() {

	TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRender(), flip);

}

void Player::update() {

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		m_velocity.setX(2);
		m_acceleration.setX(25);
		m_friction.setX(0.4);
		m_maxVelocity.setX(10);
		flip = SDL_FLIP_NONE;
		m_currentFrame = (int)((SDL_GetTicks() / 100) % m_sprite);
		if (m_position.getX() >= 500) {
			m_position.setX(500);
			m_velocity.setX(0);
		}
		if (m_maxVelocity.getX() > (m_velocity.getX() + m_acceleration.getX())) {
			m_position.setX(m_position.getX() + m_velocity.getX() + m_acceleration.getX() - m_friction.getX());
		}
		else {
			m_position.setX(m_position.getX() + m_maxVelocity.getX() - m_friction.getX());
		}
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		m_velocity.setX(-2);
		m_acceleration.setX(-25);
		m_friction.setX(-0.4);
		m_maxVelocity.setX(-10);
		flip = SDL_FLIP_HORIZONTAL;

		m_currentFrame = (int)((SDL_GetTicks() / 100) % m_sprite);

		if (m_position.getX() <= 0) {
			m_position.setX(0);
		}

		if (m_maxVelocity.getX() < (m_velocity.getX() + m_acceleration.getX())) {
			m_position.setX(m_position.getX() + m_velocity.getX() + m_acceleration.getX() - m_friction.getX());
		}
		else {
			m_position.setX(m_position.getX() + m_maxVelocity.getX() - m_friction.getX());
			m_velocity.setX(0);
		}
	}
	else {
		m_acceleration.setX(0);
		m_currentFrame = (int)((SDL_GetTicks() / 100) % 1);
		if (m_velocity.getX() > 0 && m_friction.getX() > 0) {
			m_velocity.setX(m_velocity.getX() - m_friction.getX());
			m_position.setX(m_position.getX() + m_velocity.getX());
		}

		if (m_velocity.getX() < 0) {
			if (m_friction.getX() < 0) {
				m_velocity.setX(m_velocity.getX() - m_friction.getX());
				m_position.setX(m_position.getX() + m_velocity.getX());
			}
		}
	}
}
	
void Player::clean() {};