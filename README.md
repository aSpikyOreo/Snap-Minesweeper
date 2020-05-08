# Snap-Minesweeper
Randomised mine-sifting in the form of flipping with the M5Stack

### Instructions
> * Tilt the M5Stack to move the cursor to a desired location
> * Lock the cursor into a space by pressing BtnC (the third button)
> * Flip the M5Stack to confirm your move. 
> * Unflip and find the result! If you chose a mine, the GAME OVER screen appears.
> * If not, a number representing `how many neighbouring mines that space has appears`
> * Using this number, repeat this until only the spaces with mines are left!
> * Have fun!



### Motivations
Snap-Minesweeper is a spin-off to the classic digital game, Minesweeper. The twist is that it makes use of a tangible interface known as the M5Stack to represent this and potentially provide a more immersive user experience. 

The main question at hand is whether or not tangibles can be used to improve user immersion & engagement for a better overall experience. Snap-Minesweeper just happens to be the medium at which this objective is being tested by.

### Tangibility
What makes this interface tangible is the usage of the M5Stack's accelerometer, gyroscopic and rotational data from the user's tilting and flipping controls for a more natural, ergonomic and dynamic playthrough of Minesweeper. This is to emulate the process of sifting through possible block and/or uncovering a mine.


### Snap-Roll
In the process of making Snap-Minesweeper, a more fast-paced game was made that utilises turning mechanics to increment a number in the centre of the screen. Once a target value has been reached, a user can place the M5Stack face-up to complete the game. 
