#### Configuration file

Check that you can configure ALL the following elements in the configuration file. The formatting has to be as described in the subject.

- North texture path - NO
- North texture path - NO
- East texture path - EA
- South texture path - SO
- West texture path - WE
- Floor color - F
- Ceiling color - C
- The map (see subject for the map configuration details)

Also, check that the program returns an error and exits properly when the configuration file is misconfigured (for example, an unknown key, double keys, an invalid path..) or if the filename doesn't end with the `.cub` extension. If not, the defense is over and use the appropriate flag incomplete work, crash...

#### Technical elements of the display

We're going to evaluate the technical elements of the display. Run the program and execute the following tests. If at least one fails, no points will be awarded for this section. Move to the next one.

- A window must open at the launch of the program. A window must open at the launch of the program.
- An image representing the inside of a maze must be displayed inside the window.
- Hide all or part of the window either by using another window or by using the screen's borders, then minimize the windows and maximize it back. In all cases, the content of the window must remain consistent.

#### User basic events

In this section, we're going to evaluate the program's user-generated events. Execute the 3 following tests. If at least one fails, this means that no points will be awarded for this section. Move to the next one.

- Click the red cross at the top left of the window. The window must close and the program must exit cleanly.
- Press the ESC key. The window must close and the program must exit cleanly. In the case of this test, we will accept that another key exits the program, for example, Q.
- Press the four movement keys (we'll accept WASD or ZQSD keys) in the order of your liking. Each key press must render a visible result on the window, such as a player's movement/rotation.

#### Movements

In this section, we'll evaluate the implementation of the player's movement/orientation inside the maze. Execute the 5 following tests. If at least one fails, this means that no points will be awarded for this section.

- The player's spawning orientation on the first image must be in accordance with the configuration file, test for each cardinal orientation (N, S, E, W).
- Press the left arrow then the right arrow. The player's view must rotate to the left then to the right as if the player's head was moving.
- Press W (or Z) then S. The player's view must go forward and then backward in a straight line.
- Press A (or Q) then D. The player's view must go to the left and then to the right in a straight line.
- During those four movements, was the display smooth? By smooth, we mean is the game "playable" or is it slow.

#### Walls

In this section, we'll evaluate the walls in the maze. Execute the 4 following tests. If at least one fails, this means that no points will be awarded for this section.

- The wall's texture varies depending on which compass point the wall is facing (north, south, east, west). Check that the textures on the walls and perspective are visible and correct.
- Check that if you modify the path of a wall texture in the configuration file, it modifies the rendered texture when the program is re-executed. Also check that if you set a non-existent path it raises an error.
- Check that the floor and ceiling colors are well handled when you modify them in the configuration file.

#### Error management

In this section, we'll evaluate the program's error management and reliability. Execute the 4 following tests. If at least one fails, this means that no points will be awarded for this section. Move to the next one.

- Run the program using numerous arguments and random values. Even if the program doesn't require any arguments, it is critical that those arguments don't alternate or create unhandled errors.
- Check that there are no memory leaks. You can use the top or leaks command in another shell to monitor that the memory use is stable. The memory used must not increase each time an action is made.
- Roll either your arm or your face on the keyboard. The program must not show any strange behaviors and it must stay functional.
- Modify the map. The program must not show any strange behaviors and it must stay functional if the map is well configured, if not it must raise an error.

This format should provide a clear and organized overview of the evaluation criteria for the project "cub3d".
