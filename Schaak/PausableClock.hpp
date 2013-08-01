/*

PauseableClock.hpp

* An extension of sf::Clock for SFML 2.0. Allows the instanced clock to be 
paused and resumed.

* Also, if Think() is run on the individual clock, it can support a 
universal pause function, which allows the instanced clock to be
paused along with every other clock that runs Think().

Copyright (C) 2013 by Anthony Nichols

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef PAUSEABLECLOCK_HPP
#define PAUSEABLECLOCK_HPP

#include <SFML/System.hpp>

namespace sfuser {

	class PauseableClock {

		sf::Clock internalClock;
		bool paused;
		static bool universalpause;
		sf::Time pcTime;

	public:

		// Think must be run for the instanced Pauseableclock to support
		// Universal Pause. If not run, will work/pause normally but Universal Pausing
		// will not be supported.
		void think();

		void pause();
		void start();
		const sf::Time getElapsedTime();
		sf::Time restart(const bool pause = false);

		static void universalPause();
		static void universalStart();

		PauseableClock();

	};

}
#endif