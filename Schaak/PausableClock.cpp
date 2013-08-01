#include "PauseableClock.hpp"

namespace sfuser {

	bool PauseableClock::universalpause = false;

	void PauseableClock::think() {

		if (universalpause) {
			pause();
		} else {
			start();
		}

	}

	void PauseableClock::pause() {

		if (!paused) {
			paused = true;
			pcTime += sf::seconds(internalClock.getElapsedTime().asSeconds());
		}

	}

	void PauseableClock::start() {

		if (paused) {
			paused = false;
			internalClock.restart();
		}

	}

	const sf::Time PauseableClock::getElapsedTime() {

		if (!paused) {
			return sf::seconds(pcTime.asSeconds() + internalClock.getElapsedTime().asSeconds());
		} else {
			return pcTime;
		}

	}

	sf::Time PauseableClock::restart(const bool pause) {

		sf::Time et = sf::seconds(pcTime.asSeconds() + internalClock.getElapsedTime().asSeconds());

		paused = pause;
		pcTime = sf::seconds(0);
		internalClock.restart();

		return et;

	}

	void PauseableClock::universalPause() {

		if (!universalpause) {
			universalpause = true;
		}

	}

	void PauseableClock::universalStart() {

		if (universalpause) {
			universalpause = false;
		}

	}

	PauseableClock::PauseableClock () : 
		paused(false),
		pcTime(sf::seconds(0)) { }

}