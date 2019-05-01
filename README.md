# monopoly - 大富翁
A C++ Monopoly Game for EEE102 AS3.

## 使用方法
### 快速开始
 - 打开`bin/`文件夹下的`monopoly.exe`开始游戏
 - 本游戏仅可在windows7以上版本中运行
 
### 编译方法
**自动编译 - GNU**<br/>
 - 打开`click-me.bat`文件根据提示进行编译

**手动编译**<br/>
 - 请链接`lib/`和`src/`文件夹下全部文件
 - 请使用`C++11`标准编译
 - 请使用`utf-8`字符集编译
 - GNU参考指令`g++ -O2 -o monopoly src/main.cpp src/controller.cpp src/roll.cpp src/player.cpp src/square.cpp src/msgbox.cpp src/scoreboard.cpp src/hintbox.cpp src/map.cpp src/point.cpp src/startinterface.cpp src/tools.cpp lib/ovo.cpp -std=c++11 -fexec-charset=utf-8`
 
## 游戏说明
本游戏分为三个模式，人人模式，人机模式和机机模式。游戏数据将储存在`data/`文件夹中。
### 人人模式
需要两个玩家进行登录或注册。

### 人机模式
需要一个玩家进行登录或注册。

### 机机模式
无需登录，将自动生成AI进行对战。

## 游戏规则
 - 每个玩家初始余额$5000
 - 地图包含40块地，其中38块可进行购买，1块GO(落入时获得$200奖励), 1块JAIL(落入的玩家会多停留一轮)
 - 玩家通过投骰子(1-6)决定每一轮前进的步数
 - 玩家经过无人占领的地时，可以选择购买
 - 玩家经过对手的孤立的地时，将被罚款此地价格的10%
 - 玩家经过对手不孤立的地时，将被罚款此地价格的20%
 - 玩家经过自己占领的地时，可以选择付此地价格的50%进行升级。土地升级后价格将抬升5%。
 - 土地可无限制升级，但一轮只能升级一次。
 - 当有玩家破产时，游戏结束。未破产的玩家赢！
 
 ## 开源协议
 - 本项目使用[**GNU General Public License 3.0**开源协议](/LICENSE)！
 
