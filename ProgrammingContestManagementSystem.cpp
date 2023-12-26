//
// Created by 钱鑫 on 2023/12/12.
//
#include "ProgrammingContestManagementSystem.h"
#include<iostream>//输入输出流
#include<fstream>//文件流
#include<sstream>//字符串流
#include<algorithm>//算法  all_of 判断队伍状态是否为Finished   unvisited.erase，remove（）删除未访问容器中的当前节点 reverse（）反转路径
#include <mutex>//互斥量  numeric_limits  导航计算距离
#include <chrono>//时间  chrono::milliseconds(500) 模拟0.5秒
#include<vector>//容器
#include <unordered_map>//无序映射
#include <iomanip>//格式化，put_time输出时间
#include <ctime>//时间
#include <thread>//this_thread::sleep_for(chrono::milliseconds(500)) 模拟0.5秒

using namespace std;

TeamNode* root;//二叉排序树根节点

//插入节点
void ProgrammingContestManagementSystem::InsertNode(TeamNode* current, TeamNode* newNode)//需要当前节点和新节点作为参数
{
    //如果新节点比当前节点小
    if ((newNode->team.teamNumber )<(current->team.teamNumber)) {
        //如果当前节点的左子树为空则放在左子树
        if (current->left == nullptr) {
            current->left = newNode;
        }
            //如果当前节点的左子树不空则继续寻找当前节点左子树的空的左子树
        else {
            InsertNode(current->left, newNode);
        }
    }
        //如果新节点比当前节点大
    else {
        //如果当前节点的右子树为空则放在右子树
        if (current->right == nullptr) {
            current->right = newNode;
        }
        else
        {
            //如果当前节点的右子树不空则继续寻找当前节点右子树的空的右子树
            InsertNode(current->right, newNode);
        }
    }
}

//将赛事信息从team.txt文件中读取出来并放入二叉排序树中
void ProgrammingContestManagementSystem::LoadTeamsFromFile()         //读取文件
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


        getline(ss, temp, '\t'); // 跳过分数的 #
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

//添加队伍信息
void ProgrammingContestManagementSystem::AddTeam()
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
//修改
void ProgrammingContestManagementSystem::ModifyTeam()
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

//计算二叉树中指定节点的高度
int ProgrammingContestManagementSystem::GetHeight(TeamNode* node)
{
    if (node == nullptr) {
        return 0;
    }

    int leftHeight = GetHeight(node->left);
    int rightHeight = GetHeight(node->right);

    return 1 + max(leftHeight, rightHeight);
}
//计算二叉树中指定节点的平衡因子
int ProgrammingContestManagementSystem::GetBalanceFactor(TeamNode* node)
{
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = GetHeight(node->left);
    int rightHeight = GetHeight(node->right);
    return leftHeight - rightHeight;
}
//左旋
TeamNode* ProgrammingContestManagementSystem::RotateLeft(TeamNode* node)
{
    //当前节点的右子节点保存在newRoot中
    TeamNode* newRoot = node->right;
    //原右子节点的左子节点保存在subtree中
    TeamNode* subtree = newRoot->left;

    // 左旋
    //将当前节点变为变为newRoot的左子节点
    newRoot->left = node;
    //将原右子节点的左子节点变为当前节点的右子节点
    node->right = subtree;
    //返回新的根节点（当前节点的右子节点）
    return newRoot;
}
//右旋（同上）
TeamNode* ProgrammingContestManagementSystem::RotateRight(TeamNode* node)
{
    TeamNode* newRoot = node->left;
    TeamNode* subtree = newRoot->right;

    // 右旋
    newRoot->right = node;
    node->left = subtree;

    return newRoot;
}
//找最小节点
TeamNode* ProgrammingContestManagementSystem::FindMinimumNode(TeamNode* current)
{
    //当左子树不空时找到最左边的节点就是最小节点
    while (current->left != nullptr) {
        current = current->left;
    }
    //左子树为空则当前节点就是最小节点
    return current;
}
//在文件中删除
void ProgrammingContestManagementSystem::Deletefile(string id)
{
    ifstream inputFile("new-team.txt");

    if (!inputFile) {
        cout << "无法打开文件\n";
        return;
    }

    // 创建一个临时文件
    ofstream outputFile("temp.txt");

    if (!outputFile) {
        cout << "无法创建文件 temp.txt\n";
        inputFile.close();
        return;
    }

    string line;
    string contentToRemove = id;  // 要删除的内容

    while (getline(inputFile, line))
    {
        if (line.find(contentToRemove) != string::npos)
        {
            // 跳过包含要删除内容的行
            continue;
        }

        // 将不包含要删除内容的行写入临时文件中
        outputFile << line << endl;
    }

    inputFile.close();
    outputFile.close();

    remove("new-team.txt");        // 删除原始文件
    rename("temp.txt", "new-team.txt");  // 将临时文件重命名为原始文件的名称
}
//在二叉树中找到需要删除的节点
TeamNode* ProgrammingContestManagementSystem::DeleteNode(TeamNode* current, const string& teamNumber)
{
    // 如果当前节点为空，则返回当前节点
    if (current == nullptr) {
        return current;
    }
    // 如果需要删除的节点编号比当前节点编号小，则在前节点的左孩子中找需要删除的节点并赋给当前节点的左孩子
    if (teamNumber.compare(current->team.teamNumber) < 0) {
        current->left = DeleteNode(current->left, teamNumber);
    }
        // 如果需要删除的节点编号比当前节点编号大，则在前节点的右孩子中找需要删除的节点并赋给当前节点的右孩子
    else if (teamNumber.compare(current->team.teamNumber) > 0) {
        current->right = DeleteNode(current->right, teamNumber);
    }
        //需要删除的节点编号和当前节点编号相等
    else {
        // 找到要删除的节点

        // 如果节点为叶子节点或只有一个子节点
        if (current->left == nullptr) {
            TeamNode* temp = current->right;
            delete current;
            return temp;
        }
        else if (current->right == nullptr) {
            TeamNode* temp = current->left;
            delete current;
            return temp;
        }

        // 如果节点有两个子节点
        TeamNode* successor = FindMinimumNode(current->right);
        current->team = successor->team;
        current->right = DeleteNode(current->right, successor->team.teamNumber);
    }

    // 进行平衡调整
    int balanceFactor = GetBalanceFactor(current);

    // 右旋操作
    if (balanceFactor > 1 && GetBalanceFactor(current->left) >= 0) {
        return RotateRight(current);
    }

    // 左旋操作
    if (balanceFactor < -1 && GetBalanceFactor(current->right) <= 0) {
        return RotateLeft(current);
    }

    // 左右旋操作
    if (balanceFactor > 1 && GetBalanceFactor(current->left) < 0) {
        current->left = RotateLeft(current->left);
        return RotateRight(current);
    }

    // 右左旋操作
    if (balanceFactor < -1 && GetBalanceFactor(current->right) > 0) {
        current->right = RotateRight(current->right);
        return RotateLeft(current);
    }
    //返回当前节点作为删除后的根节点
    return current;
}
//删除参赛队伍信息
void ProgrammingContestManagementSystem::DeleteTeam(string teamNumber)
{
    //如果根节点为空，说明本来就没有参赛队伍信息，无法进行删除
    if (root == nullptr) {
        cout << "当前无参赛队伍信息。\n";
        return;
    }

    // 查找要删除的节点，将查找到的节点赋值给一个新的节点targetNode
    TeamNode* targetNode = SearchNode(root, teamNumber);
    //如果找不到要删除的节点，给出提示
    if (targetNode == nullptr) {
        cout << "未找到对应的参赛队伍信息。\n";
        return;
    }
    //找到要删除的节点
    // 执行删除操作
    root = DeleteNode(root, teamNumber);
    Deletefile(teamNumber);
    cout << "参赛队伍信息已删除。\n";
}

//按编号查找队伍并输出ASL
void ProgrammingContestManagementSystem::SearchTeam()
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
//查找按队伍编号节点
TeamNode* ProgrammingContestManagementSystem::SearchNode(TeamNode* current, const string& teamNumber)//需要当前节点和要查找的队伍编号信息
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

// 在文本文件中修改参赛队伍信息
void ProgrammingContestManagementSystem::UpdateInFile(string teamNumber, const Team& updatedInfo) {
    ifstream inputFile;
    inputFile.open("new-team.txt",ios::in);
    if (!inputFile.is_open()) {
        cout << "无法打开文档" << endl;
        return;
    }

    ofstream outputFile("temp.txt");
    if (!outputFile.is_open()) {
        cout << "无法创建临时文件" << endl;
        inputFile.close();
        return;
    }
    TeamNode* node = SearchNode(root, teamNumber);
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string currentTeamNumber;
        ss >> currentTeamNumber;
        if (currentTeamNumber.compare(teamNumber) == 0) {
            // 找到要修改的队伍信息，将新的信息写入临时文件
            outputFile << teamNumber << "	#	" << updatedInfo.projectName << "	#	" << updatedInfo.university << "	#	" << updatedInfo.eventCategory << "	#	" << updatedInfo.participants << "	#	" << updatedInfo.guideTeacher << "	#	" << updatedInfo.scores << endl;
        }
        else {
            // 将原始行写入临时文件
            outputFile << line << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    if (SearchNode(root, teamNumber) != nullptr) {
        remove("new-team.txt");       // 删除原始的队伍信息文件
        rename("temp.txt", "new-team.txt");  // 将临时文件重命名为原始的队伍信息文件

    }
    else {
        remove("temp.txt");  // 删除临时文件
        cout << "未找到指定的队伍信息，无法修改。" << endl;
    }
}
//管理参赛队伍信息
void ProgrammingContestManagementSystem::Management()
{
    int choice;
    do {
        cout << "============= 菜单 =============\n";
        cout << "1. 增加参赛队伍信息\n";
        cout << "2. 修改参赛队伍信息\n";
        cout << "3. 删除参赛队伍信息\n";
        cout << "4. 查询参赛队伍秩序\n";
        cout << "0.      退出\n";
        cout << "===============================\n";
        cout << "请输入选项：";
        cin >> choice;

        switch (choice) {
            case 1:
                AddTeam();
                break;
            case 2:
                ModifyTeam();
                break;
            case 3:
            {
                string teamNumber;
                cout << "请输入需要删除的队伍编号：";
                cin >> teamNumber;
                DeleteTeam(teamNumber);
                break;
            }
            case 4:
                SearchFinalTeam();
                break;
            case 0:
                cout << "程序已退出。\n";
                break;
            default:
                cout << "无效选项，请重新输入。\n";
                break;
        }
    } while (choice != 0);
}
//计算路径长度
int ProgrammingContestManagementSystem::CalculatePathLength(TeamNode* node, const string& teamNumber, int level) {
    if (node == nullptr) {
        return 0;  // 未找到目标节点
    }
    if (teamNumber < node->team.teamNumber) {
        return 1 + CalculatePathLength(node->left, teamNumber, level + 1);
    }
    else if (teamNumber > node->team.teamNumber) {
        return 1 + CalculatePathLength(node->right, teamNumber, level + 1);
    }
    else {
        return level;  // 找到目标节点，返回路径长度
    }
}
//队伍状态
string ProgrammingContestManagementSystem::statusToString(TeamStatus status) {
    switch (status) {
        case Waiting: return "候场";
        case Playing: return "比赛中";
        case Finished: return "比赛结束";
        default: return "未知状态";
    }
}
//打印输出
void ProgrammingContestManagementSystem::printCurrentStatus(const vector<vector<Team>>& rooms, const time_t& currentTime) {
    struct tm* localTime = localtime(&currentTime);
    cout << "=====================" << put_time(localTime, "%Y-%m-%d %H:%M:%S") << "=====================" << endl;
    for (size_t i = 0; i < rooms.size(); ++i) {
        cout << "决赛室" << i + 1 << ":" << endl;
        for (const auto& team : rooms[i]) {
            cout << "队伍编号:" << team.teamNumber <<"    初赛成绩："<<team.scores << "    状态:" << statusToString(team.status) << endl;
        }
        cout << "==========" << endl;
    }
}
//判断是否所有队伍都已完成比赛
bool ProgrammingContestManagementSystem::isCompetitionFinished(const vector<vector<Team>>& rooms) {
    return all_of(rooms.begin(), rooms.end(), [](const vector<Team>& room) {
        return all_of(room.begin(), room.end(), [](const Team& team) {
            return team.status == Finished;
        });
    });
}
//读取文件，排序，循环输出
void ProgrammingContestManagementSystem::simulateCompetition(ifstream& file) {
    // 修改队列为向量，以保持队伍状态
    vector<vector<Team>> rooms(17);
    string line;
    getline(file,line);
    // 读取和解析文件
    while (getline(file, line)) {
        istringstream iss(line);
        Team team;
        team.status = Waiting;
        iss >> team.roomNumber >> team.teamNumber >> team.projectName >> team.university
            >> team.eventCategory >> team.participants >> team.guideTeacher >> team.scores;
        team.roomNumber--; // 使决赛室编号从0开始
        rooms[team.roomNumber].push_back(team);

        // 输出格式化的信息
        //cout << "参赛队伍编号: " << team.teamNumber << "       初赛成绩: " << team.scores << endl;
    }

    // 为每个决赛室队伍排序
    for (auto& room : rooms) {
        selectionSort(room);
    }


    // 获取当前时间
    time_t currentTime = time(nullptr);
    printCurrentStatus(rooms, currentTime);

    while (!isCompetitionFinished(rooms)) {
        //this_thread::sleep_for(chrono::milliseconds(500)); // 模拟0.5秒
        currentTime += 5 * 60; // 增加5分钟

        // 更新队伍状态
        for (auto& room : rooms) {
            for (auto& team : room) {
                if (team.status == Waiting) {
                    team.status = Playing;
                    break;
                } else if (team.status == Playing) {
                    team.status = Finished;
                    break;
                }
            }
        }

        printCurrentStatus(rooms, currentTime);
    }
}
//选择排序
void ProgrammingContestManagementSystem::selectionSort(vector<Team> &data)
{
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (stoi(data[j].scores) > stoi(data[minIndex].scores)) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(data[i], data[minIndex]);
        }
    }
}
// 生成初赛成绩添加到final-tean1.txt文件里
void ProgrammingContestManagementSystem::simulateTeamStatusDisplay()  {

    ifstream inputFile("final-team.txt");   // 打开输入文件
    ofstream outputFile("final-team1.txt"); // 创建输出文件

    string line;

    srand(time(0)); // 设置随机种子
    if (inputFile.is_open() && outputFile.is_open()) {
        getline(inputFile,line);
        line+="      初赛成绩";
        outputFile << line << endl; // 写入到输出文件
        //存入随机数
        while (getline(inputFile, line)) {
            int scores = rand() % 41 + 60;  // 生成60到100之间的随机数
            line += "\t\t\t"+ to_string(scores); // 在行末尾添加随机数
            outputFile << line << endl; // 写入到输出文件
        }

        inputFile.close();   // 关闭输入文件
        outputFile.close();  // 关闭输出文件

        cout << "处理完成！" << endl;
    } else {
        cout << "无法打开文件！" << endl;
    }
    ifstream file("final-team1.txt");
    if (!file.is_open()) {
        cerr << "无法打开文件" << endl;
    }
    simulateCompetition(file);
    file.close();
}

//按编号查找队伍并输出所在决赛室
void ProgrammingContestManagementSystem::SearchFinalTeam()
{
    // 修改队列为向量，以保持队伍状态
    vector<vector<Team>> rooms(17);
    ifstream inputFile("final-team.txt");   // 打开输入文件
    string line;
    getline(inputFile,line);
    // 读取和解析文件
    while (getline(inputFile, line)) {
        istringstream iss(line);
        Team team;
        iss >> team.roomNumber>> team.teamNumber ;
        team.roomNumber--; // 使决赛室编号从0开始
        rooms[team.roomNumber].push_back(team);

    }
    string teamNumberl;
    cout<<"请输入要查询的队伍编号"<<endl;
    cin>>teamNumberl;
    for (auto& room : rooms) {
        for (auto& team : room) {
            if(teamNumberl==team.teamNumber)
            {
                cout<<"决赛室号为："<<(team.roomNumber+1)<<endl;
            }
        }
    }


}
//导航系统
void ProgrammingContestManagementSystem::CampusGuide() {
    unordered_map<int, string> destinationInfo = {
            {1, "行政楼，用途：办公楼"},
            {2, "海韵湖，用途：湖泊，风景优美"},
            {3, "图书馆，用途：查阅资料，自习室"},
            {4, "东食堂，用途：进餐休息"},
            {5, "东操场，用途：跑道，足球场"},
            {6, "南门，用途：学校的大门"},
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

    cout << "1.行政楼 " << "2.海韵湖 " << "3.图书馆 " << "4.东食堂 " << "5.东操场 "<< "6.南门\n" << "7.文体中心" << "8.西操场 " << "9.经世楼 " << "10.文理大楼" << "11.西食堂 " << "12.西宿舍区" << endl;

    int start, end;
    cout << "请输入起点编号：" << endl;
    cin >> start;
    cout << "请输入终点编号：" << endl;
    cin >> end;

    if (destinationInfo.find(start) == destinationInfo.end() || destinationInfo.find(end) == destinationInfo.end()) {
        cout << "请输入有效的起点和终点编号！" << endl;
        return;
    }

    unordered_map<int, int> distance;//距离
    unordered_map<int, int> prev;//前驱节点
    vector<int> unvisited;//未访问容器
    //初始化距离和前驱节点，将所有节点标记为未访问
    for (const auto& pair : destinationInfo) {
        const int& destination = pair.first;
        distance[destination] = numeric_limits<int>::max();
        prev[destination] = -1;
        unvisited.push_back(destination);
    }
    distance[start] = 0;
    //循环遍历未访问的节点
    while (!unvisited.empty()) {
        int u = unvisited[0];
        int minDistance = distance[u];
        for (const int& destination : unvisited) {
            if (distance[destination] < minDistance) {
                u = destination;
                minDistance = distance[destination];//选择距离最小的节点作为当前节点
            }
        }

        unvisited.erase(remove(unvisited.begin(), unvisited.end(), u), unvisited.end());

        if (u == end) {
            break;
        }
        //更新与其相邻节点的距离和前驱节点
        for (const auto& neighbor : navigationGraph[u]) {
            const int& v = neighbor.first;
            int altDistance = distance[u] + neighbor.second.first;
            if (altDistance < distance[v]) {
                distance[v] = altDistance;
                prev[v] = u;
            }
        }
    }

    if (prev[end] == -1) {
        cout << "无法找到最短路径" << endl;
        return;
    }

    vector<int> path;
    int current = end;
    while (current != start) {
        path.push_back(current);
        current = prev[current];
    }
    path.push_back(start);

    reverse(path.begin(), path.end());

    cout << "最短路径为：" << endl;
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    cout << "路径长度为：" << distance[end] << " 米" << endl;
    cout << "详细信息：" << endl;
    for (const int& destination : path) {
        cout << destination << ": " << destinationInfo[destination] << endl;
    }
}