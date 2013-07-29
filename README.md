Schaak
======

Public repository: https://github.com/essarrdee/Schaak

Chess-based 7 Day RTS game with local multiplayer.
Written in 168 hours.
Start time: 21:00, Monday 22/07/2013
End time: 21:00, Monday 29/07/2013

Design: SRD. Contributions from Chris Heyes, Derrick Creamer, Michal Walczak.
Code: SRD. Contribution from Michal Walczak.
Art: SRD.
Makefile: Michal Walczak.
SFML: Laurent Gomila.

Controls:
** Arrow keys ** to scroll.
** Mouse to window edge ** to scroll.
** Scroll ** to zoom.
** Space ** to pause.
Tab to switch control between black and white.
Be nice and share the mouse/keyboard (or plug in two!).
Current control has green cover squares, enemy has magenta.
** Left-click drag ** to select pieces.
** Right-click drag ** to set destination area.
** Click piece symbols ** to select all pieces of that type.
** Control-click piece symbols ** to restrict the current selection to pieces of that type.
** Delete ** sacrifices any selected pawns for money.
Upgrades:
** Click the "Speed" and "Block" buttons ** to spend money on upgrades
Each upgrade costs 10*level*level money, and increase that stat's level by 1. That means the cumulative cost of upgrading a stat is cubic.
AI:
** Click the AI buttons ** to switch between different AI modes for your units.

======= The Block/Speed/AI buttons provide no visual feedback, but =======
==== rest assured they are *NOT* inert! They are also key to winning! ====


None of AI, Speed, and Block have feedback, so here are the spoilers:
AI 1 (default) is survive (prioritise survival)
AI 2 is evade (don't walk into enemy cover, but take exchanges)
AI 3 is advance (walk into enemy cover if there is friendly cover or a piece to capture)
AI 4 is kamikaze (ignore enemy threats, go to destination and take any opportunity to capture a piece)
AI 5 loops back to AI 1 (survive).
Block starts at 0% for all pieces and goes up 1% each time.
Speed starts at 30,40,50, or 60 and goes up by 1 each time.
You'll have to keep track of them yourself, or get an updated non-7dRTS version that displays these values on screen :)

========== Capture the enemy King! ==========
============ Protect your King! =============

Windows users:
Download from
https://dl.dropboxusercontent.com/u/6433222/Schaak-7dRTS.zip (strict 7dRTS version)
or
https://dl.dropboxusercontent.com/u/6433222/Schaak.zip (potential updates)

Linux/OSX users:
Clone github repository https://github.com/essarrdee/Schaak
make && make info && make clean && make run
requires SFML 2.0 and c++11-compatible compiler (preferably g++)
http://sfml-dev.org/download/sfml/2.0/