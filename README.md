# Hybrid - (Jinx) 2D Game Engine & Game Jam Submission

### Scratch Notes (Game)

#### Ideas
* 1v1 brick-breaker meets pong
	* Each player controls 1 paddle
	* Similar rules to tennis, except for out-of-bounds on either adjacent side
	* Ball spawns in the center of the gameboard
	* Tees to a random player at the start of the game, swapping directions each round
	* "Bricks" exist on the gameboard that are:
		* Normal - which just break when hit
		* Positive/Negative Powerup - Depending on which player last hit the ball, the positive/negative affect effects them.
			* Pong Bigger
			* Pong Smaller
			* Pong Slowdown


### Scratch Notes (Game Engine)

#### Game Engine Architecture
* ECS - Entity, Component, System based
* Build with Windows OS in mind, maybe include Linux and/or MacOS support later.