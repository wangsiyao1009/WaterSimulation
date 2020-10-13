#include "WaterSimulation.h"
#include <random>
#include <iostream>
#include <ctime>
using namespace std;
WaterSimulation::~WaterSimulation() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * 产生碰撞生成水花
 */
void WaterSimulation::collision() {
    if (rock.getPosition().second > Config::waterHorizon && rock.isVisible()
        && !rock.isInWater()) {
        rock.setInWater();
        int posX = rock.getPosition().first;
        posX /= Config::waterColumnWidth;
        waterColumns[posX].updateVelocity(800);
        uniform_int_distribution<int> velocityRandom(10, 80);
        default_random_engine engine(time(0));
        uniform_int_distribution<int> angleRandom(30, 150);
        for (WaterParticle &particle:waterParticles) {
			cout << "pariticle" << endl;
            particle.initPositionVisibleSpeed(rock.getPosition().first, Config::waterHorizon,
                                              velocityRandom(engine), angleRandom(engine));
        }
    }
}

void WaterSimulation::eventLoop() {
    bool stop = false;
    unsigned int lastTime = SDL_GetTicks();
    int mouseX = 0, mouseY = 0;
    while (!stop) {
        unsigned int curTime = SDL_GetTicks();
        double timeDuration = 1.0 * (curTime - lastTime) / 100;
        lastTime = curTime;
        while (!stop && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    stop = true;
                    break;
                case SDL_MOUSEMOTION:
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (!rock.isVisible()) {
                        rock.initPositionVisibleAndInWaterFlag(mouseX, mouseY);
                    }
                    break;
                default:
                    break;
            }
        }
		SDL_SetRenderDrawColor(renderer, 135, 206, 235, 0);
		SDL_RenderClear(renderer);
		for (WaterColumn &waterColumn : waterColumns) {
			waterColumn.update(timeDuration);
		}
		for (WaterParticle &particle : waterParticles) {
			particle.update(timeDuration);
		}
		if (rock.isVisible()) {
			rock.update(timeDuration);
			collision();
		}
		int left[200];
		int right[200];
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < waterColumns.size(); ++j) {
				if (j > 0) {
					left[j] = (waterColumns[j].getHeight() - waterColumns[j - 1].getHeight());
					waterColumns[j - 1].updateVelocity(2*left[j]);
				}
				if (j < waterColumns.size() - 1) {
					right[j] = (waterColumns[j].getHeight() - waterColumns[j + 1].getHeight());
					waterColumns[j + 1].updateVelocity(2*right[j]);
				}
			}
			for (int j = 0; j < waterColumns.size(); ++j) {
				if (j > 0) {
					waterColumns[j - 1].updateHeight(0.35*left[j]);
				}
				if (j < waterColumns.size() - 1) {
					waterColumns[j + 1].updateHeight(0.35*right[j]);
				}
			}
		}
	
		render();
		SDL_RenderPresent(renderer);
		if (timeDuration < (1.0f / 50.0f)) {
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - timeDuration) * 1000.0f));
		}
    }
}

WaterSimulation::WaterSimulation() : event(), rock() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("WaterSimulation", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              Config::windowWidth, Config::windowHeight, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    for (int posX = -Config::waterColumnWidth; posX < Config::windowWidth; posX += Config::waterColumnWidth) {
        waterColumns.emplace_back(posX);
    }
    for (int i = 0; i < Config::particleNum; ++i) {
        waterParticles.emplace_back();
    }
}

void WaterSimulation::render() {
    for (auto &waterColumn:waterColumns) {
        waterColumn.render(renderer);
    }
    for (auto &waterParticle:waterParticles) {
        waterParticle.render(renderer);
    }
    rock.render(renderer);
}
