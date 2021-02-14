# Double Trouble

My goal is to develop a jump and run side scroller. In this jump and run you control two players at the same time (with
the same keys). So when you press "a" both player sprites will move to the left and so on. Both player sprites however
start on a different position on the map and you have to use walls etc to get both of them to the finish (flag)
simultaniously.

I also wanna implement enemies (static ones like lava and moving ones) where the player can die. Maybe I will also
implement some kind of Super Mario kind of fighting (jumping on top of an enemy defeats it). If one of the two players
die, you will lose one live and you have to repeat the level (both player sprites will spawn at the starting position
again)
The game is over when you run out on lives.

Moreover there should be a main menu when you start the game where you can save and load or start a new game. When you
start a new game you can select a difficulty level. The difficulty level decides how many chances you have to complete a
level or if you are able to save between or even in a level.

I wanna implement this on my own without a team, because of the reasons I explained in the

# Goals (11 Points)

* (2) basic movement, basic animation (jumping, sliding), gravity and win condition:
  + "w", "a" and "d" to move around and complete the world
  + animation of moving players
  + maybe some sliding mechanics too, where you can fit below walls, where the player wouldnt fit while he is running
* (3) 10 different levels
* (2) enemies
  + static enemies (like lava etc.)
  + simple moving enemies
* (1) advanced enemies
  + random moving enemies, maybe even with some kind of AI
* (1) fighting mechanics
  + super mario like fighting mechanics where you can defeat an enemy when you jump on top of them
* (1) audio
  + background music
  + sound effects
* (1) main menu
  + new game
  + load game
  + exit
