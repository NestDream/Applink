# Applink
App-Link is a Mahjong game based on C++ and Qt framework. 

### Feature
App-Link has great user interface design and excellent interaction.

### Function

1. Basic Mahjong game: Game map is generated randomly. When the player clickes on two same blocks and the bend between them are less than or equal to 3, both of the blocks will disappear. The player wins when all blocks disappear. The system will record how long the player has spent.  

2. Gameplay: The game has two modes, easy mode and hard mode. The player can get up to 3 hints and 2 chances to change the map. In easy mode, hints are unlimited. The top five winners will enter the rankings.

3. Interaction: 用户鼠标点击连连看图标时会有点击音效；图标相消时有相消音效；图标具有三种状态，分别是静息状态、鼠标停留状态和鼠标点击状态，每个三种的状态对应着三种图标形态，有助于用户分辨；提示按钮和地图更换按钮在次数用尽后会变成灰色；  

4. Algorithm: Utilize depth-first search algorithm to optimize the image matching function, which improves the efficiency of the  programme.
  

### Program Structure

- appendices.h和appendices.cpp用于实现记录时间（Time类）、背景音乐（MusicPLayer类）、点击音效（MusicPlayer类）以及排行榜（Rank类）展示功能  

- applink.h和applink.cpp用于实现本程序的主体内容：登陆界面和游戏界面的实现。连连看游戏可以看做图的连通问题。本次实验在判断两个图片能否满足游戏条件时使用了深度优先搜索提高效率。原理是用一个二维数组存储游戏地图，用DFS判断两个点之间能否消去。若两个相同点之间能通过三次以下的垂直弯折连通的话即可以消去，如果不存在这样的点对，程序会自动更新地图。最外层会设置一圈虚节点以助于判断。用户可以获得三次获得提示的机会和两次主动更换地图的机会。  

- button.h和button.cpp用于为连连看图标提供多种状态（静息状态、鼠标停留状态和鼠标点击状态）  

- start.h和start.cpp用于游戏启动和用户名的输入  

- user.h是保存用户信息的类，其中可以得到用户的名字和游戏时间  
