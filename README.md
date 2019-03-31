# Applink
App-Link is a Mahjong game based on C++ and Qt framework. 

### Feature
App-Link has great user interface design and excellent interaction.

### Function

1. Basic Mahjong game: Game map is generated randomly. When the player clickes on two same blocks and the bend between them are less than or equal to 3, both of the blocks will disappear. The player wins when all blocks disappear. The system will record how long the player has spent.  

2. Gameplay: The game has two modes, easy mode and hard mode. The player can get up to 3 hints and 2 chances to change the map. In easy mode, hints are unlimited. The top five winners will enter the rankings.

3. Interaction: The game has sound effect for mouse clicking；sound effect for icon matching；the blocks have three status: normal, hover and click,which correspond to three different pictures, so that players can distiguish them easily；the hint buttion and map change button will turn grey when the hint and changing map becomes unavailable；  

4. Algorithm: Utilize depth-first search algorithm to optimize the image matching function, which improves the efficiency of the  programme.
  

### Program Structure

- appendices.h and appendices.cpp are used to record time(Class Time), set and play background music(Class MusicPLayer), set sound effect(Class MusicPlayer), and display ranking(Class Rank)  

- Applink. h and applink. CPP are used to realize the main content of this game: the logging in interface and the game interface. Mahjong game can be regarded as the connectivity problem of graphs.This game uses depth-first search to improve the efficiency when judging whether two images can meet the game conditions.The idea is to use a two-dimensional array to store the game map and DFS to determine whether two points can be eliminated. If the two points can be connected by vertical bending within three times, they can be eliminated. If no such point pair exists, the program will automatically update the map.The outermost layer sets a circle of virtual nodes to aid judgment. Players get three prompts and two map changing chances. 

- button.h and button.cpp are used to provide various states (resting state, hover state and mouse click state) for the Mahjong icon.  

- start.h and start.cpp are used for game startup and user name input.

- user.h defines classes to store user information like name and gaming time. 
