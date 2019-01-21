# Applink
App-Link is a Mahjong game based on C++ and Qt framework. 

### Function

1. Basic Mahjong game：Game map is generated randomly. When the player clickes on two same blocks and the bend between them are less than or equal to 3, both of the blocks will disappear. The player wins when all blocks disappear. The system will record how long the player has spent.  

2. 游戏性方面：游戏有简单和困难两个模式；用户有三次获取提示和两次主动更换地图的机会；简单模式下用户获取提示的次数不限；用户获胜最高的五名会进入排行榜中。  

3. 交互性方面：用户鼠标点击连连看图标时会有点击音效；图标相消时有相消音效；图标具有三种状态，分别是静息状态、鼠标停留状态和鼠标点击状态，每个三种的状态对应着三种图标形态，有助于用户分辨；提示按钮和地图更换按钮在次数用尽后会变成灰色；  

4. 程序算法方面：使用深度优先搜索算法对图片匹配函数进行优化，提高了游戏运行效率。  

### Program Structure

- appendices.h和appendices.cpp用于实现记录时间（Time类）、背景音乐（MusicPLayer类）、点击音效（MusicPlayer类）以及排行榜（Rank类）展示功能  

- applink.h和applink.cpp用于实现本程序的主体内容：登陆界面和游戏界面的实现。连连看游戏可以看做图的连通问题。本次实验在判断两个图片能否满足游戏条件时使用了深度优先搜索提高效率。原理是用一个二维数组存储游戏地图，用DFS判断两个点之间能否消去。若两个相同点之间能通过三次以下的垂直弯折连通的话即可以消去，如果不存在这样的点对，程序会自动更新地图。最外层会设置一圈虚节点以助于判断。用户可以获得三次获得提示的机会和两次主动更换地图的机会。  

- button.h和button.cpp用于为连连看图标提供多种状态（静息状态、鼠标停留状态和鼠标点击状态）  

- start.h和start.cpp用于游戏启动和用户名的输入  

- user.h是保存用户信息的类，其中可以得到用户的名字和游戏时间  
