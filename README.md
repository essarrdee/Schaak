Schaak
======

Public repository: https://github.com/essarrdee/Schaak

Chess-based 7 Day RTS game.
Written in 168 hours.
Start time: 21:00, Monday 22/07/2013
End time: 21:00, Monday 29/07/2013

Controls:
Arrow keys to scroll.
Mouse to window edge to scroll.
Scroll to zoom.
Space to pause.
Tab to switch control between black and white.
Current control has green cover squares, enemy has magenta.
Left-click drag to select pieces.
Right-click drag to set destination area.
Click piece symbols to select all pieces of that type.
Control-click piece symbols to restrict the current selection to pieces of that type.
Money:
Select pawns and sacrifice them (with the delete key) to get money.
Upgrades:
Spend money on upgrades by clicking the "Speed" and "Block" buttons.
Each upgrade costs 10*level*level money, and increase that stat's level by 1. That means the cumulative cost of upgrading a stat is cubic.
AI:
Click the AI buttons to switch between different AI modes for your units.

========== Capture the enemy King! ==========

Windows users:
Download from
https://dl.dropboxusercontent.com/u/6433222/Schaak-7dRTS.zip (strict 7dRTS version)
or
https://dl.dropboxusercontent.com/u/6433222/Schaak.zip (potential updates)

Linux/OSX users:
Clone github repository https://github.com/essarrdee/Schaak
make | make info | make clean | make run
requires SFML 2.0 and c++11-compatible compiler (preferably g++)
http://sfml-dev.org/download/sfml/2.0/