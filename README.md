#                                **中国大学生计算机设计大赛省级赛事管理系统**
#                                **Programming-Contest-Management-System**
中国大学生计算机设计大赛是我国高校面向本科生的计算机应用设计大赛，大赛旨在激发学生学习计算机知识和技能的兴趣与潜能，提高学生运用信息技术解决实际问题的综合能力。通过大赛这种计算机教学实践形式，可展示师生的教与学成果，最终以赛促学，以赛促教，以赛促创。该赛事在历届学生中影响力较大，参与者众多。
利用数据结构课程所学的相关知识，为中国大学生计算机设计大赛江苏省组委会设计一个省级赛事管理系统。以2021年省赛数据为例，通过对数据的处理和分析，设计合理的数据结构对赛事相关的数据进行存储及处理。赛事相关数据存储在文本文件和excel文件中，文件中不同的数据项之间均使用#分隔，下图给出了文件team.txt中参赛信息的对应数据示例。

<div align=center>
<img src="https://github.com/QX7274/Programming-Contest-Management-System/blob/main/%E6%95%B0%E6%8D%AE%E8%B5%84%E6%96%99/image.png" />
</div>



**【任务描述】**
设计一款赛事管理系统，实现赛务相关的数据管理及信息服务，该系统能够为省级赛事管理解决以下问题：

（1）赛事信息管理：从team.txt中读取参赛队伍的基本信息，设计合适的数据结构存储，能实现对参赛队伍的增加、修改和浏览。为参赛队伍分配一个分数为60 ~ 100之间的初赛成绩，并能实现参赛队伍的成绩查询（实现基于二叉排序树的查找）。设计合适的输入输出，根据提示输入参赛队编号，查询队伍的初赛成绩，若查找成功，输出该赛事类别对应的基本信息（参赛作品名称、参赛学校、赛事类别、参赛者和初赛成绩信息）。另外，输出全部参赛队的平均查找长度ASL。

（2）决赛现场模拟：首先进行决赛分组，生成决赛秩序册，供参赛队查询。根据赛事类别将参赛队伍分配到17个决赛室（编号为1 ~ 17）。秩序册中每个决赛室的进场顺序为初赛成绩降序排列。（排序算法从选择排序、插入排序、希尔排序、归并排序、堆排序中选择一种，并为选择该算法的原因做出说明）然后，模拟决赛秩序。比赛现场会设置大型候赛区，场地中有大屏以时间线动态展示各决赛室中正在决赛的队伍，侯赛的队伍及比赛结束的队伍信息。请编写程序模拟候赛区大屏上动态展示各参赛队候场、比赛中、比赛结束的状态。

（3）决赛地图导览：为参赛者提供决赛主办地的各种路径导航的查询服务，以我校长山校区提供比赛场地为例，为参赛者提供不少于12个目标地的导航。为参赛者提供校园地图中任意目标地（建筑物）相关信息的查询；提供图中任意目标地（建筑物）的问路查询。

# 1  参赛队伍管理
能够管理各参赛队的基本信息（包含参赛队编号，参赛作品名称，参赛学校，赛事类别，参赛者，指导老师）；能实现对参赛队伍的增加、修改、和浏览。

## 1.1 问题分析
管理各参赛队的基本信息的前提是得先获得各个参赛队的信息，此时需要先进行读取，详细信息见读取信息模块。读取时已经将详细信息按照队伍编号大小存入了二叉排序树中，此时需要对得到的二叉排序树进行相关操作来进行增加、修改的操作，在实现上述功能时，在对节点进行增加、修改后，需要在txt文件中也进行相关操作。参赛队伍的信息浏览在进行文件读取的时候直接输出即可。

## 1.2算法设计
1、采用结构体定义参赛队伍的结构，包括参赛队编号、参赛作品名称、参赛学校、赛事类别、参赛者、指导教师等成员变量。定义二叉排序树的节点也需要采用结构体来定义。

参赛队伍结构体
```
struct Team {
    string teamNumber;
    string projectName;
    string university;
    string eventCategory;
    string participants;
    string guideTeacher;
    string scores;
    int roomNumber;
    TeamStatus status; // 添加队伍状态
};
```

参赛队伍节点结构体
```
struct TeamNode {
    Team team;
    TeamNode* left;
    TeamNode* right;

    TeamNode()
    {
        this->team.teamNumber = team.teamNumber;
        this->team.projectName = team.projectName;
        this->team.eventCategory = team.eventCategory;
        this->team.participants = team.participants;
        this->team.university = team.university;
        this->team.guideTeacher = team.guideTeacher;
        this->team.scores = team.scores;
        this->team.status = team.status;
        this->team.roomNumber = team.roomNumber;
        left = nullptr;
        right = nullptr;
    }

    // 构造函数，接受队伍编号作为参数
    TeamNode(const string& number, const string& projectName, const string& university, const string& eventCategory, const string& participants, const string& guideTeacher,
             const string& scores) {
        TeamNode* node = new TeamNode();
        team.teamNumber = number;
        team.projectName = projectName;
        team.university = university;
        team.eventCategory = eventCategory;
        team.participants = participants;
        team.guideTeacher = guideTeacher;
        team.scores = scores;
        left = nullptr;
        right = nullptr;
    }
};
```


2、增加队伍时应注意重复添加的判定，输入已存在的队伍编号则给出提示并重新输入。
```
if(teamNumber1==teamNumber)
        {
            cout<<"该队伍已存在,请重新输入："<<endl;
            AddTeam();
        }
```
3、浏览选项放在主菜单，增加和修改选项放在管理菜单，用do-while循环和switch语句实现菜单功能。
4、读取文件时生成随机数，并放入二叉排序树和新的文件里。
5、注意初赛成绩存入时与文件格式保持一致，即数据前面加上“#”号，且在第一行末尾加上“初赛成绩”。
6、浏览队伍的实现：在读取文件，生成初赛成绩和建立二叉排序树时直接输出，不用另外调用函数。
## 1.3 算法实现
浏览队伍信息
```
    ifstream inFile;
    inFile.open("new-team.txt",ios::in);//打开文件
    if (!inFile.is_open()) {
        cout << "无法打开文件 \n";
        return;
    }

    getline(inFile, line); // 读取文件中的标题行，忽略

    while (getline(inFile, line)) {


        // 使用 stringstream 进行分割
        stringstream ss(line);
        string temp;

        string teamNumber;
        getline(ss, teamNumber, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // 跳过参赛作品名称的 #
        string projectName;
        getline(ss, projectName, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // 跳过参赛学校的 #
        string university;
        getline(ss, university, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // 跳过赛事类别的 #
        string eventCategory;
        getline(ss, eventCategory, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // 跳过参赛者的 #
        string participants;
        getline(ss, participants, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // 跳过指导教师的 #
        string guideTeacher;
        getline(ss, guideTeacher,'\t');

        getline(ss, temp, '\t'); // 跳过参赛者的 #
        string scores;
        getline(ss, scores, '\t');
        ss.ignore();

        // 输出格式化的信息
        cout << "参赛队伍编号: " << teamNumber << endl;
        cout << "参赛作品名称: " << projectName << endl;
        cout << "参赛学校: " << university << endl;
        cout << "赛事类别: " << eventCategory << endl;
        cout << "参赛者: " << participants << endl;
        cout << "指导教师: " << guideTeacher << endl;
        cout << "初赛成绩: " << scores << endl;
```
添加队伍信息
```
void EventManagementSystem::AddTeam()
{
    //首先创建新节点，以便存放需要添加的队伍信息
    TeamNode* newNode = new TeamNode;

    string teamNumber1;
    // 从用户输入获取参赛队伍信息
    cout << "请输入参赛队伍编号：";
    cin.ignore(); // 忽略之前的换行符
    cin>>teamNumber1;
    string line;
    ifstream inFile;
    inFile.open("new-team.txt",ios::in);//打开文件
    if (!inFile.is_open()) {
        cout << "无法打开文件 \n";
        return;
    }

    getline(inFile, line); // 读取文件中的标题行，忽略

    while (getline(inFile, line)) {
        // 使用 stringstream 进行分割
        stringstream ss(line);
        string temp;

        string teamNumber;
        getline(ss, teamNumber, '\t');
        ss.ignore();

        if(teamNumber1==teamNumber)
        {
            cout<<"该队伍已存在,请重新输入："<<endl;
            AddTeam();
        }
        else
            newNode->team.teamNumber=teamNumber1;
    }
    cin.ignore(); // 忽略之前的换行符
    cout << "请输入参赛作品名称：";
    getline(cin, newNode->team.projectName);
    cout << "请输入参赛学校：";
    getline(cin, newNode->team.university);
    cout << "请输入赛事类别：";
    getline(cin, newNode->team.eventCategory);
    cout<<endl;
    cout << "请输入参赛者：";
    getline(cin, newNode->team.participants);
    cout << "请输入指导教师：";
    getline(cin, newNode->team.guideTeacher);
    cout << "请输入初赛成绩：";
    getline(cin, newNode->team.scores);
    //在txt文件中修改
    ofstream mycout("new-team.txt", ios::app);
    mycout << newNode->team.teamNumber << "	#	" << newNode->team.projectName << "	#	"  << newNode->team.university << "	#	" << newNode->team.eventCategory << "	#	" << newNode->team.participants <<  "	#	" << newNode->team.guideTeacher<<"	  #	   " << newNode->team.scores << endl;
    mycout.close();


    //相关信息录入完成，将当前节点的左右子树分别赋为空
    newNode->left = nullptr;
    newNode->right = nullptr;

    // 插入节点到二叉排序树
    //如果根节点为空，则当前节点就是根节点
    if (root == nullptr) {
        root = newNode;
    }
        //否则将当前节点插入二叉排序树中
    else {
        InsertNode(root, newNode);
    }
    //给出添加成功的提示

    cout << "参赛队伍信息已添加。"<<endl;
}
```

修改参赛队伍信息
```
void EventManagementSystem::ModifyTeam()
{
    if (root == nullptr) {
        cout << "当前无参赛队伍信息。\n";
        return;
    }

    string teamNumber;
    cout << "请输入要修改的参赛队伍编号：";
    cin >> teamNumber;

    TeamNode* target = SearchNode(root, teamNumber);
    if (target == nullptr) {
        cout << "未找到对应的参赛队伍信息。\n";
        return;
    }

    // 根据需要，修改参赛队伍的字段信息
    cout << "请输入新的参赛作品名称：";
    cin.ignore();
    getline(cin, target->team.projectName);
    cout << "请输入新的参赛学校：";
    getline(cin, target->team.university);
    cout << "请输入新的赛事类别：";
    getline(cin, target->team.eventCategory);
    cout<<endl;
    cout << "请输入新的参赛者：";
    getline(cin, target->team.participants);
    cout << "请输入新的指导教师：";
    getline(cin, target->team.guideTeacher);
    cout << "请输入新的初赛成绩：";
    getline(cin, target->team.scores);

    UpdateInFile(teamNumber, target->team);
    // 输出修改成功的提示信息
    cout << "参赛队伍信息已修改并保存到文件中。\n";
}
```



# 2 参赛队伍的成绩查询（基于二叉排序树的查找）
为参赛队伍分配一个分数为60 ~ 100之间的初赛成绩，从team.txt中读取参赛队伍的基本信息，实现基于二叉排序树的查找。根据提示输入参赛队编号，若查找成功，输出该赛事类别对应的基本信息（参赛作品名称、参赛学校、赛事类别、参赛者和初赛成绩信息）。另外，输出全部参赛队伍的平均查找长度ASL；否则，输出“查找失败！”。

## 2.1 问题分析

1、为参赛队伍分配60 ~ 100的随机初赛成绩，采用srand函数生成随机数，time函数生成随机数种子。

2、从数据文件 team.txt 中读取参赛队伍的基本信息，构建一个二叉排序树。

3、读取用户输入的参赛队伍编号，将其作为关键字进行查找。

4、在二叉排序树中查找该关键字，如果查找成功，则输出该赛事类别对应的基本信息（参赛队伍编号，参赛作品名称，参赛学校，赛事类别，参赛者，指导教师，初赛成绩），并计算输出所有队伍平均查找长度 ASL，若查找失败则给出提示。

5、重复步骤2-3，直到所有参赛队伍的基本信息都被查找完毕。

## 2.2 算法设计
1、生成随机数。
```
    srand(time(0));
    int scores=rand() %41+60;
```
2、文件读取和存储，构造二叉排序树。
3、遍历文件里的队伍，分别计算ASL并输出

## 2.3 算法实现

将赛事信息从team.txt文件中读取出来并放入二叉排序树中
```
void EventManagementSystem::LoadTeamsFromFile()         //读取文件
{
    ifstream inputFile("team.txt");   // 打开输入文件
    ofstream outputFile("new-team.txt"); // 创建输出文件

    string line;

    srand(time(0)); // 设置随机种子
    if (inputFile.is_open() && outputFile.is_open()) {
        getline(inputFile,line);
        line+="  #   初赛成绩";
        outputFile << line << endl; // 写入到输出文件
        //存入随机数
        while (getline(inputFile, line)) {
            int scores = rand() % 41 + 60;  // 生成60到100之间的随机数
            line += "\t#\t" + to_string(scores); // 在行末尾添加随机数
            outputFile << line << endl; // 写入到输出文件
        }

        inputFile.close();   // 关闭输入文件
        outputFile.close();  // 关闭输出文件

        cout << "处理完成！" << endl;
    } else {
        cout << "无法打开文件！" << endl;
    }
    ifstream inFile;
    inFile.open("new-team.txt",ios::in);//打开文件
    if (!inFile.is_open()) {
        cout << "无法打开文件 \n";
        return;
    }

    getline(inFile, line); // 读取文件中的标题行，忽略

    while (getline(inFile, line)) {


        // 使用 stringstream 进行分割
        stringstream ss(line);
        string temp;

        string teamNumber;
        getline(ss, teamNumber, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // 跳过参赛作品名称的 #
        string projectName;
        getline(ss, projectName, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // 跳过参赛学校的 #
        string university;
        getline(ss, university, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // 跳过赛事类别的 #
        string eventCategory;
        getline(ss, eventCategory, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // 跳过参赛者的 #
        string participants;
        getline(ss, participants, '\t');
        ss.ignore();


        getline(ss, temp, '\t'); // 跳过指导教师的 #
        string guideTeacher;
        getline(ss, guideTeacher,'\t');


        getline(ss, temp, '\t'); // 跳过参赛者的 #
        string scores;
        getline(ss, scores, '\t');
        ss.ignore();


        // 输出格式化的信息
        cout << "参赛队伍编号: " << teamNumber << endl;
        cout << "参赛作品名称: " << projectName << endl;
        cout << "参赛学校: " << university << endl;
        cout << "赛事类别: " << eventCategory << endl;
        cout << "参赛者: " << participants << endl;
        cout << "指导教师: " << guideTeacher << endl;
        cout << "初赛成绩: " << scores << endl;

        // 为当前行的信息用队伍编号创建一个新的队伍节点
        TeamNode* newNode = new TeamNode(teamNumber,projectName,university,eventCategory,participants,guideTeacher,scores);
        //如果根节点为空则当前节点就是根节点
        if (root == nullptr)
        {
            root = newNode;
        }
            //如果根节点不空，则将创建的新节点插入到二叉排序树中
        else
        {
            InsertNode(root, newNode);
        }
        cout << endl;
    }
    //读取完毕，关闭文件
    inFile.close();
    cout << "数据输出完毕\n";
    cout<<endl;
}
```

按编号查找队伍并输出ASL
```
void EventManagementSystem::SearchTeam()
{
    int totalPathLength = 0;
    int nodeCount = 0;
    //如果根节点为空，说明本来就没有参赛队伍信息，无法进行查询
    if (root == nullptr) {
        cout << "当前无参赛队伍信息。\n";
        return;
    }

    string teamNumber;
    cout << "请输入要查询的参赛队伍编号："<<endl;
    cin >> teamNumber;

    // 查找要查询的节点，将查找到的节点赋值给一个新的节点targetNode
    TeamNode* targetNode = SearchNode(root, teamNumber);
    //如果找不到要查询的节点，给出提示
    if (targetNode == nullptr) {
        cout << "未找到对应的参赛队伍信息。\n";
        SearchTeam();
        return ;
    }

    //找到要查询的节点
    cout << "参赛队伍编号: " << targetNode->team.teamNumber << endl;
    cout << "参赛作品名称: " << targetNode->team.projectName << endl;
    cout <<"参赛学校: " << targetNode->team.university << endl;
    cout << "赛事类别: "<<targetNode->team.eventCategory << endl;
    cout << "参赛者: "<<targetNode->team.participants << endl;
    cout << "指导教师: " <<targetNode->team.guideTeacher << endl;
    cout << "初赛成绩: " <<targetNode->team.scores << endl;
    cout << "所有参赛队的平均查找长度如下："<<endl;
    string line;
    ifstream inFile;
    inFile.open("new-team.txt",ios::in);//打开文件
    if (!inFile.is_open()) {
        cout << "无法打开文件 \n";
        return;
    }

    getline(inFile, line); // 读取文件中的标题行，忽略

    while (getline(inFile, line)) {
        // 使用 stringstream 进行分割
        stringstream ss(line);
        string temp;

        string teamNumber;
        getline(ss, teamNumber, '\t');
        ss.ignore();

        // 查找要查询的节点并计算路径长度
        int pathLength = CalculatePathLength(root, teamNumber, 1);
        if (pathLength == 0) {
            cout << "未找到对应的参赛队伍信息。\n";
            return;
        }

        totalPathLength += pathLength;
        nodeCount++;

        double asl = static_cast<double>(totalPathLength) / nodeCount;
        cout << "队伍"<<teamNumber<<"的平均查找长度ASL：" << asl << endl;
    }

}
```
查找待查队伍在二叉树中的节点
```
TeamNode* EventManagementSystem::SearchNode(TeamNode* current, const string& teamNumber)//需要当前节点和要查找的队伍编号信息
{
    //如果当前节点为空或者当前节点的队伍编号等于需要查找的队伍编号，则返回当前节点
    if (current == nullptr || current->team.teamNumber.compare(teamNumber) == 0) {
        return current;
    }
    //需要查找的节点编号比当前节点编号小，则去当前节点的左子树中继续寻找
    if (teamNumber.compare(current->team.teamNumber) < 0) {
        return SearchNode(current->left, teamNumber);
    }
        //需要查找的节点编号比当前节点编号大，则去当前节点的右子树中继续寻找
    else {
        return SearchNode(current->right, teamNumber);
    }
}
```
# 3 决赛分组，生成秩序册
根据赛事类别将参赛队伍分配到17个决赛室（编号为1~17）。秩序册中每个决赛室的进场顺序为初赛成绩降序排列。（排序算法从选择排序、插入排序、希尔排序、归并排序、堆排序中选择一种，并为选择该算法的原因做出说明）。

## 3.1 问题分析
从数据文件中读取参赛队伍的基本信息，包括参赛队伍编号、参赛作品名称、参赛学校、赛事类别、参赛者和指导老师信息等。提示用户输入参赛学校名称或赛事类别，并进行输入验证和错误提示。根据用户输入的参赛学校名称或赛事类别，在数据文件中查找相应的参赛团队。将查找到的参赛团队按赛事类别进行排序，并输出排序后的参赛团队的基本信息。

## 3.2 算法设计
采用选择排序算法进行排序，每次从待排序的元素中选择最小（或最大）的元素，将其与未排序部分的第一个元素交换位置，直到所有元素都排序完成。选择排序的时间复杂度是O(n^2)，其中n是参赛队伍的数量，每个学校的参赛团队数量较小，选择排序的性能足够满足需求，并且实现简单。

## 3.3 算法实现
按学校查找队伍
```
void ProgrammingContestManagementSystem::SearchTeamByUniversity(const string& university, const vector<Team>& teamInfos) {

    vector<Team> matchedTeams;

    // 遍历参赛队伍，找到匹配的队伍信息
    
    // 使用选择排序按参赛队编号排序

    // 输出排序后的参赛团队信息
}
```

# 4 决赛叫号模拟
所有参赛队按赛事组织文件中的赛事类别分到17个决赛室，比赛现场会设置大型候赛区，场地中有大屏以时间线动态展示各决赛室中正在决赛的队伍，侯赛的队伍及比赛结束的队伍信息。请编写程序模拟候赛区大屏上动态展示各参赛队候场、比赛中、比赛结束的状态。 

## 4.1 问题分析
1、所有参赛队按赛事组织文件中的赛事类别分到17个决赛室，每个决赛室容纳的参赛队数量相同。

2、决赛室按顺序叫号，被叫号参赛队进场，比赛结束后，下一参赛队才能进赛场。

3、采用队列实现。

## 4.2 算法设计
根据赛事类别将参赛队伍分配到不同的决赛室，并按照顺序叫号让队伍进入赛场进行比赛。函数接受一个参数 “teamInfos”，即存储参赛队伍信息的向量。首先，创建一个无序映射 “categoryMap”，用于按照赛事类别将参赛队伍分组。遍历 “teamInfos” 向量中的每个参赛队伍，将其加入到对应赛事类别的向量中。然后，创建一个向量 “categories”，用于存储赛事类别，并进行排序，以确保按照字母顺序输出。接下来，定义变量 “numFinalRooms” 表示决赛室的数量，并创建一个二维向量 “finalRooms”，用于存储每个决赛室中的参赛队伍。通过遍历排序后的赛事类别向量 “categories”，将对应赛事类别的参赛队伍按顺序分配到不同的决赛室中。使用“roomIndex”变量追踪当前的决赛室索引，并将参赛队伍依次添加到相应的决赛室中。当“roomIndex”超过决赛室数量时，使用取余操作使其循环回到第一个决赛室。最后，使用循环遍历每个决赛室，并依次输出决赛室的编号。对于每个决赛室，遍历其中的参赛队伍，并输出参赛队编号，表示队伍进入赛场进行比赛。使用 “this_thread::sleep_for()”函数模拟比赛进行，每次比赛结束前等待 0.5 秒。输出比赛结束提示，并输出空行以分隔不同的决赛室。实现了一个决赛叫号系统，将参赛队伍按照赛事类别分配到不同的决赛室，并模拟比赛叫号过程。

## 4.3 算法实现
决赛叫号系统
```
void ProgrammingContestManagementSystem::FinalsCallSystem(const vector<Team>& teamInfos) {

    // 按照赛事类别将参赛队伍分组

    // 按照赛事类别进行排序

    // 将参赛队伍按照顺序分配到决赛室

    // 模拟决赛叫号
}
```

# 5 校园导航
为参赛者提供决赛主办地的各种路径导航的查询服务，以我校长山校区提供比赛场地为例，为参赛者提供不少于12个目标地的导航。为参赛者提供校园地图中任意目标地（建筑物）相关信息的查询；提供图中任意目标地（建筑物）的问路查询。需输出目的地（建筑物）名称、代号、简介等信息；最短路径的输出需包含途经地及最短路径值；并分析主要算法的时间复杂度。

## 5.1 问题分析
使用了无序映射（“unordered_map”）来存储目的地的信息和导航图的信息。用户输入起点和终点，使用Dijkstra 算法找到最短路径并输出。

## 5.2 算法设计
使用了无序映射（“unordered_map”）来存储目的地的信息和导航图的信息。首先，使用无序映射 “destinationInfo” 存储了各个目的地的编号和描述信息。键为目的地的编号，值为目的地的描述。然后，使用无序映射 “navigationGraph”存储了导航图的信息。它的键是起点的编号，值是另一个无序映射，其中键是终点的编号，值是一个二元组，包含了到达终点的距离和导航所需的时间。接下来，用户输入起点编号和终点编号，并进行判断是否有效。如果起点或终点的编号不存在于 “destinationInfo”中，则提示输入有效的起点和终点编号。然后，使用 Dijkstra 算法计算从起点到终点的最短路径。首先初始化距离和前驱节点的映射，并将所有节点标记为未访问。然后，循环遍历未访问的节点，选择距离最小的节点作为当前节点，并更新与其相邻节点的距离和前驱节点。直到找到终点或所有节点都被访问过。如果找不到最短路径（即终点的前驱节点为-1），则输出无法找到最短路径的信息。如果找到了最短路径，将路径存储在向量 `path` 中，并输出最短路径的编号序列。最后，输出最短路径的长度，并根据编号在 “destinationInfo”中查找并输出详细信息。实现了根据起点和终点之间的最短路径进行校园导游，并提供了路径长度和详细信息的输出。

## 5.3 算法实现
导航系统
```
void EventManagementSystem::CampusGuide() {

    unordered_map<int, string> destinationInfo = {

        {1, "行政楼，用途：办公楼"},

        {2, "海韵湖，用途：湖泊，风景优美"},

        {3, "图书馆，用途：查阅资料，自习室"},

        {4, "东食堂，用途：进餐休息"},

        {5, "东操场，用途：跑道，足球场"},

        {6, "南门，用途：学校的主门"},

        {7, "文体中心，用途：室内运动中心，船院剧场"},

        {8, "西操场，用途：跑道，足球场"},

        {9, "经世楼，用途：教学楼"},

        {10, "文理大楼，用途：实验中心，教学楼"},

        {11, "西食堂，用途：进餐休息"},

        {12, "西宿舍区，用途：学生宿舍"}

    };

    unordered_map<int, unordered_map<int, pair<int, int>>> navigationGraph = {

        {1, {{2, {300, 2}}, {10, {700, 10}}}},

        {2, {{3, {600, 3}}, {1, {300, 1}}}},

        {3, {{10, {400, 10}}, {8, {550, 8}}, {4, {100, 4}}, {2, {300, 2}}}},

        {4, {{7, {550, 7}}, {5, {100, 5}}, {3, {100, 3}}}},

        {5, {{6, {250, 6}}, {4, {100, 4}}}},

        {6, {{7, {250, 7}}, {12, {700, 12}}, {5, {250, 5}}}},

        {7, {{8, {100, 8}}, {6, {250, 6}}, {11, {300, 11}}, {4, {550, 4}}}},

        {8, {{9, {100, 9}}, {7, {100, 7}}, {11, {250, 11}}, {3, {550, 3}}}},

        {9, {{10, {100, 10}}, {8, {100, 8}}}},

        {10, {{9, {100, 9}}, {1, {700, 1}}, {3, {400, 3}}}},

        {11, {{12, {200, 12}}, {8, {250, 8}}, {7, {300, 7}}}},

        {12, {{11, {200, 11}}, {6, {700, 6}}}}

    };
    
    //输入起点终点
    
    //查找并输出路径
    
    //查找并输出最短路径
}
```

# 6菜单设计
主菜单
```
        cout << "中国大学生计算机设计大赛省级赛事管理系统\n";
        cout << "====================================\n";
        cout << "=========       菜单      ==========\n";
        cout << "=========1. 管理参赛队伍信息==========\n";
        cout << "=========2. 读取参赛队伍信息==========\n";
        cout << "=========3. 查询参赛队伍信息=========\n";
        cout << "=========    4. 叫号系统   ==========\n";
        cout << "=========    5. 导航服务   ==========\n";
        cout << "=========      0. 退出    ==========\n";
        cout << "====================================\n";
```
管理菜单
```
        cout << "============= 菜单 =============\n";
        cout << "1. 增加参赛队伍信息\n";
        cout << "2. 删除参赛队伍信息\n";
        cout << "3. 修改参赛队伍信息\n";
        cout << "0.      退出\n";
        cout << "===============================\n";
```
采用do-while循环操作菜单，采用switch语句对菜单进行选择。

# 7类定义
```
class ProgrammingContestManagementSystem{
public:    
      void DeleteTeam(string teamNumber);    
      void Deletefile(string id);    
      TeamNode* RotateLeft(TeamNode* node);    
      TeamNode* RotateRight(TeamNode* node);    
      int GetHeight(TeamNode* node);    
      int GetBalanceFactor(TeamNode* node);    
      TeamNode* SearchNode(TeamNode* current, const string& teamNumber);    
      TeamNode* DeleteNode(TeamNode* current, const string& teamNumber);    
      TeamNode* FindMinimumNode(TeamNode* current);    
      void UpdateInFile(string teamNumber, const Team& updatedInfo);    
      void ModifyTeam();    
      void Management();    
      void SearchTeam();    
      void SearchTeamByUniversity(const string& university, const vector<Team>& teamInfos);    
      void FinalsCallSystem(const vector<Team>& teamInfos);    
      void InsertNode(TeamNode* current, TeamNode* newNode);    
      void LoadTeamsFromFile();    
      void AddTeam();    
      void CampusGuide();    
      int CalculatePathLength(TeamNode* node, const string& teamNumber, int level);
};
```
# 校园地图

<div align=center>
<img src="https://github.com/QX7274/Programming-Contest-Management-System/blob/main/数据资料/江科大地图a.jpg" />
</div>
