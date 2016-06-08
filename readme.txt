开发环境：Mac OS X ＋ qt5.6 ＋ Qt Creator

目录结构：
Lianliankan/
├── *.ui			UI层
├── Model/			模型层
├── MainWindow/			主界面
├── BasicModeWindow/ 		基本模式
├── RelaxedModeWindow/		休闲模式
├── LevelModeWindow/		关卡模式
├── res/			资源文件
├── Lianliankan.pro		qt工程文件
├── Lianliankan.pro.user	qt工程配置信息
├── readme.txt			你正在看的文件。。。

可能出现的问题：
我是在OS X系统下进行的开发，当我在Win10系统下进行编译时，出现了许多编译错误。。。经过我的排查，好像是中文注释导致的问题，我的解决办法是把所有的中文注释去掉，然后就可以通过编译了。