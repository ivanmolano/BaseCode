#pragma once
#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"

class Game
{
	private:
		Game();
		bool running;
	
		SDL_Window* g_pWindow;
		SDL_Renderer* g_pRenderer;
		std::vector< GameObject* > m_gameObjects;
		
	

	public:
		static Game* Instance()
		{
			if (s_pInstance == 0)
			{
				s_pInstance = new Game();
			}
			return s_pInstance;
		}
	
		~Game();

		static Game* s_pInstance;
		bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
		void render();
		void update();
		int handleEvents();
		void clean();
		bool isRunning();
		SDL_Renderer * getRender();
		int getP();

};

#endif