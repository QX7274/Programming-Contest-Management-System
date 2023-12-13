#                                中国大学生计算机设计大赛省级赛事管理系统
#                                Programming-Contest-Management-System
中国大学生计算机设计大赛是我国高校面向本科生的计算机应用设计大赛，大赛旨在激发学生学习计算机知识和技能的兴趣与潜能，提高学生运用信息技术解决实际问题的综合能力。通过大赛这种计算机教学实践形式，可展示师生的教与学成果，最终以赛促学，以赛促教，以赛促创。该赛事在历届学生中影响力较大，参与者众多。
请了解该赛事组织及管理方式，利用数据结构课程所学的相关知识，为中国大学生计算机设计大赛江苏省组委会设计一个省级赛事管理系统。以2021年省赛数据为例，通过对数据的处理和分析，设计合理的数据结构对赛事相关的数据进行存储及处理。赛事相关数据存储在文本文件和excel文件中，文件中不同的数据项之间均使用#分隔，图1中给出了文件team.txt中参赛信息的对应数据示例。



【问题描述】

  要求协助中国大学生计算机设计大赛江苏省组委会，设计一款赛事管理系统，实现赛务相关的数据管理及信息服务，该系统能够为省级赛事管理解决以下问题：

（1）从team.txt中读取参赛队伍的基本信息，能够管理各参赛队的基本信息（包含参赛队编号，参赛作品名称，参赛学校，赛事类别，参赛者，指导老师），赛事类别共11项（参见大赛官网jsjds.blcu.edu.cn）；包括增加、删除、修改参赛队伍的信息。

（2）实现基于二叉排序树的查找。根据提示输入参赛队编号，若查找成功，输出该赛事类别对应的基本信息（参赛作品名称、参赛学校、赛事类别、参赛者和指导老师信息），同时，输出查找成功时的平均查找长度ASL；否则，输出“查找失败！”。请输出ASL的计算表达式和结果值。
（3）能够提供按参赛学校查询参赛团队，根据提示输入参赛学校名称，若查找成功，输出该学校参赛的所有团队的基本信息，输出的参赛团队需有序输出（按参赛队编号）。（排序算法可从选择排序、插入排序、希尔排序、归并排序、堆排序中任意选择，并为选择算法的原因做出说明。）

（4）为省赛现场设计一个决赛叫号系统。所有参赛队按赛事组织文件中的赛事类别分到9个决赛室，决赛室按顺序叫号，被叫号参赛队进场，比赛结束后，下一参赛队才能进赛场。请模拟决赛叫号系统，演示省赛现场各决赛室的参赛队进场情况。（模拟时，各参赛队进场比赛时间可设为0.5秒）

（5）赛事系统为参赛者提供赛地的校园导游程序。为参赛者提供各种路径导航的查询服务。以我校长山校区提供比赛场地为例，（请为参赛者提供不少于10个目标地的导航。可为参赛者提供校园地图中任意目标地（建筑物）相关信息的查询；提供图中任意目标地（建筑物）的问路查询，即查询任意两个目的地（建筑物）之间的一条最短的简单路径。

# 1  参赛队伍管理
能够管理各参赛队的基本信息（包含参赛队编号，参赛作品名称，参赛学校，赛事类别，参赛者，指导老师），赛事类别共11项（参见大赛官网jsjds.blcu.edu.cn）；包括增加、删除、修改参赛队伍的信息。

## 1.1 问题分析
管理各参赛队的基本信息的前提是得先获得各个参赛队的信息，此时需要先进行读取，详细信息见读取信息模块。读取时已经将详细信息按照队伍编号大小存入了二叉排序树中，此时需要对得到的二叉排序树进行相关操作来进行增加、删除、修改的操作，在实现上述功能时，在对节点进行增加、删除、修改后，需要在txt文件中也进行相关操作，删除节点时应该保持二叉排序树的完好。

## 1.2算法设计
1、采用结构体定义参赛队伍的结构，包括参赛队编号、参赛作品名称、参赛学校、赛事类别、参赛者、指导教师等成员变量。定义二叉排序树的节点也需要采用结构体来定义。

// 参赛队伍结构体

struct Team {

    string teamNumber;

    string projectName;

    string university;

    string eventCategory;

    string participants;

    string guideTeacher;

};

// 参赛队伍节点结构体

struct TeamNode {

    Team team;

    TeamNode* left;

    TeamNode* right;

    int height = 1;

    TeamNode()

    {

       this->team.teamNumber = team.teamNumber;

       this->team.projectName = team.projectName;

       this->team.eventCategory = team.eventCategory;

       this->team.participants = team.participants;

       this->team.university = team.university;

       this->team.guideTeacher = team.guideTeacher;

      

       left = nullptr;

       right = nullptr;

    }

   

    // 构造函数，接受队伍编号作为参数

    TeamNode(const string& number, const string& projectName,const string& university, const string& eventCategory, const string& participants, const string& guideTeacher) {

       TeamNode* node = new TeamNode();

       team.teamNumber = number;

       team.projectName = projectName;

       team.university = university;

       team.eventCategory = eventCategory;

       team.participants = participants;

       team.guideTeacher = guideTeacher;

       left = nullptr;

       right = nullptr;

    }

2、在对节点进行相关操作时，应该注意二叉树的平衡，适当做出调整。



## 1.3 算法实现
//添加队伍信息


## 1.4 实验结果
 增加队伍：根据提示输入指令和需要添加的相关信息，就能在二叉排序树中添加新的节点，并保持二叉树的结构，在文件中也添加该队伍信息。



删除队伍：根据提示输入指令和需要删除的队伍编号，就能在二叉排序树中删除该节点，并保持二叉树的结构，在文件中也删除该队伍信息。



 修改队伍信息：根据提示输入指令和需要修改的相关信息，就能在二叉排序树中找到该节点并修改，在文件中也就进行修改。



# 2 基于二叉树的查找
从team.txt中读取参赛队伍的基本信息，实现基于二叉排序树的查找。根据提示输入参赛队编号，若查找成功，输出该赛事类别对应的基本信息（参赛作品名称、参赛学校、赛事类别、参赛者和指导老师信息），同时，输出查找成功时的平均查找长度ASL；否则，输出“查找失败！”。

## 2.1 问题分析
使用二叉排序树（BST）来进行查找。具体实现过程如下：

1、从数据文件 team.txt 中读取参赛队伍的基本信息，构建一个二叉排序树。

2、读取用户输入的参赛队伍编号，将其作为关键字进行查找。

3、在二叉排序树中查找该关键字，如果查找成功，则输出该赛事类别对应的基本信息（参赛作品名称、参赛学校、赛事类别、参赛者和指导老师信息），并计算平均查找长度 ASL；否则，输出“查找失败！”。

4、重复步骤2-3，直到所有参赛队伍的基本信息都被查找完毕。

## 2.2 算法设计
1、采用字符串用于存储和处理队伍基本信息。

//从输入流中读取一行文本，并将其存储到一个字符串变量中

    string line;

2、采用文件流用于读取txt文件。

ifstream inFile("team.txt");//打开文件

inFile.close();//关闭文件

3、采用二叉排序树来存储参赛队伍信息，根据参赛队伍编号（String类型）大小来构建二叉排序树，可以实现参赛队伍信息的添加、删除和修改。

TeamNode* root;//二叉排序树根节点

// 为当前行的信息用队伍编号创建一个新的队伍节点

        TeamNode* newNode = new TeamNode(teamNumber,projectName,university,eventCategory,participants,guideTeacher);

        //如果根节点为空则当前节点就是根节点

        if (root == nullptr)

        {

            root = newNode;

        }

        //如果根节点不空，则将创建的新节点插入到二叉排序树中

        else

        {

            insertNode(root, newNode);

        }

## 2.3 算法实现
//将赛事信息从team.txt文件中读取出来并放入二叉排序树中



## 2.4 实验结果
用户根据指令输入需要查找的参赛队伍编号就能得到相关的队伍信息。



# 3 参赛团队查询
能够提供按参赛学校查询参赛团队（或根据赛事类别查询参赛团队），即，根据提示输入参赛学校名称（赛事类别），若查找成功，输出该学校参赛的（该赛事类别的）所有团队的基本信息，输出的参赛团队按赛事类别有序输出。（排序算法可从选择排序、插入排序、希尔排序、归并排序、堆排序中任意选择，并为选择算法的原因做出说明。）

## 3.1 问题分析
从数据文件中读取参赛队伍的基本信息，包括参赛队伍编号、参赛作品名称、参赛学校、赛事类别、参赛者和指导老师信息等。提示用户输入参赛学校名称或赛事类别，并进行输入验证和错误提示。根据用户输入的参赛学校名称或赛事类别，在数据文件中查找相应的参赛团队。将查找到的参赛团队按赛事类别进行排序，并输出排序后的参赛团队的基本信息。

## 3.2 算法设计
采用选择排序算法进行排序，每次从待排序的元素中选择最小（或最大）的元素，将其与未排序部分的第一个元素交换位置，直到所有元素都排序完成。选择排序的时间复杂度是O(n^2)，其中n是参赛队伍的数量，每个学校的参赛团队数量较小，选择排序的性能足够满足需求，并且实现简单。

## 3.3 算法实现
//按学校查找队伍



## 3.4 实验结果


# 4 决赛叫号模拟
所有参赛队按赛事组织文件中的赛事类别分到9个决赛室，决赛室按顺序叫号，被叫号参赛队进场，比赛结束后，下一参赛队才能进赛场。请模拟决赛叫号系统，演示省赛现场各决赛室的参赛队进场情况。（模拟时，要能直观展示叫号顺序与进场秩序一致）。      

## 4.1 问题分析
1、所有参赛队按赛事组织文件中的赛事类别分到9个决赛室，每个决赛室容纳的参赛队数量相同。

       2、决赛室按顺序叫号，被叫号参赛队进场，比赛结束后，下一参赛队才能进赛场。

## 4.2 算法设计
根据赛事类别将参赛队伍分配到不同的决赛室，并按照顺序叫号让队伍进入赛场进行比赛。函数接受一个参数 `teamInfos`，即存储参赛队伍信息的向量。首先，创建一个无序映射 `categoryMap`，用于按照赛事类别将参赛队伍分组。遍历 `teamInfos` 向量中的每个参赛队伍，将其加入到对应赛事类别的向量中。然后，创建一个向量 `categories`，用于存储赛事类别，并进行排序，以确保按照字母顺序输出。接下来，定义变量 `numFinalRooms` 表示决赛室的数量，并创建一个二维向量 `finalRooms`，用于存储每个决赛室中的参赛队伍。通过遍历排序后的赛事类别向量 `categories`，将对应赛事类别的参赛队伍按顺序分配到不同的决赛室中。使用 `roomIndex` 变量追踪当前的决赛室索引，并将参赛队伍依次添加到相应的决赛室中。当 `roomIndex` 超过决赛室数量时，使用取余操作使其循环回到第一个决赛室。最后，使用循环遍历每个决赛室，并依次输出决赛室的编号。对于每个决赛室，遍历其中的参赛队伍，并输出参赛队编号，表示队伍进入赛场进行比赛。使用 `this_thread::sleep_for()` 函数模拟比赛进行，每次比赛结束前等待 0.5 秒。输出比赛结束提示，并输出空行以分隔不同的决赛室。实现了一个决赛叫号系统，将参赛队伍按照赛事类别分配到不同的决赛室，并模拟比赛叫号过程。

## 4.3 算法实现
// 决赛叫号系统

## 4.4 实验结果
用户通过指令选择叫号系统，就好通过算法进行模拟叫号操作。



# 5 校园导航
赛事系统为参赛者提供赛地的校园导游程序,为参赛者提供各种路径导航的查询服务。以我校长山校区提供比赛场地为例，（请为参赛者提供不少于10个目标地的导航。可为参赛者提供校园地图中任意目标地（建筑物）相关信息的查询；提供任意两个目标地（建筑物）的导航查询，即查询任意两个目的地（建筑物）之间的一条最短路径。



## 5.1 问题分析
使用了无序映射（`unordered_map`）来存储目的地的信息和导航图的信息。用户输入起点和终点，使用Dijkstra 算法找到最短路径并输出。

## 5.2 算法设计
使用了无序映射（`unordered_map`）来存储目的地的信息和导航图的信息。首先，使用无序映射 `destinationInfo` 存储了各个目的地的编号和描述信息。键为目的地的编号，值为目的地的描述。然后，使用无序映射 `navigationGraph` 存储了导航图的信息。它的键是起点的编号，值是另一个无序映射，其中键是终点的编号，值是一个二元组，包含了到达终点的距离和导航所需的时间。接下来，用户输入起点编号和终点编号，并进行判断是否有效。如果起点或终点的编号不存在于 `destinationInfo` 中，则提示输入有效的起点和终点编号。然后，使用 Dijkstra 算法计算从起点到终点的最短路径。首先初始化距离和前驱节点的映射，并将所有节点标记为未访问。然后，循环遍历未访问的节点，选择距离最小的节点作为当前节点，并更新与其相邻节点的距离和前驱节点。直到找到终点或所有节点都被访问过。如果找不到最短路径（即终点的前驱节点为-1），则输出无法找到最短路径的信息。如果找到了最短路径，将路径存储在向量 `path` 中，并输出最短路径的编号序列。最后，输出最短路径的长度，并根据编号在 `destinationInfo` 中查找并输出详细信息。实现了根据起点和终点之间的最短路径进行校园导游，并提供了路径长度和详细信息的输出。

## 5.3 算法实现
//导航系统

