# Double Trouble

My goal is to develop a jump and run side scroller. In this jump and run you control two players at the same time (with
the same keys). So when you press "a" both player sprites will move to the left and so on. Both player sprites however
start on a different position on the map and you have to use walls etc to get both of them to the finish (flag)
simultaneously.

If one of the two players die, you have to retry the level. If you finish a level you will unlock the next one.

In the main menu you can select already unlocked levels or start a new game. However the new game does not delete the current progress.

If you are not able to complete the level but still wanna play the next one, you can change the value in the res/level/unlockedLevel.txt to a higher number. I know this is easy to cheat but I guessed there is no point in preventing the user from this.


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


  # Missed Goals

  I did not implement advanced enemies, because I did not have the time to do so.
  I also skipped fighting mechanics, because with the fighting mechanics the game would get to easy to play.
  Moreover I did not implement audio, because I could not implement it before the build test and afterwards I did not want to risk adding a new library which potentially does not work on the target pc.


Have fun!
