//
// Created by Ǯ�� on 2023/12/12.
//
#include "ProgrammingContestManagementSystem.h"
#include<iostream>//���������
#include<fstream>//�ļ���
#include<sstream>//�ַ�����
#include<algorithm>//�㷨  all_of �ж϶���״̬�Ƿ�ΪFinished   unvisited.erase��remove����ɾ��δ���������еĵ�ǰ�ڵ� reverse������ת·��
#include <mutex>//������  numeric_limits  �����������
#include <chrono>//ʱ��  chrono::milliseconds(500) ģ��0.5��
#include<vector>//����
#include <unordered_map>//����ӳ��
#include <iomanip>//��ʽ����put_time���ʱ��
#include <ctime>//ʱ��
#include <thread>//this_thread::sleep_for(chrono::milliseconds(500)) ģ��0.5��

using namespace std;

TeamNode* root;//�������������ڵ�

//����ڵ�
void ProgrammingContestManagementSystem::InsertNode(TeamNode* current, TeamNode* newNode)//��Ҫ��ǰ�ڵ���½ڵ���Ϊ����
{
    //����½ڵ�ȵ�ǰ�ڵ�С
    if ((newNode->team.teamNumber )<(current->team.teamNumber)) {
        //�����ǰ�ڵ��������Ϊ�������������
        if (current->left == nullptr) {
            current->left = newNode;
        }
            //�����ǰ�ڵ�����������������Ѱ�ҵ�ǰ�ڵ��������Ŀյ�������
        else {
            InsertNode(current->left, newNode);
        }
    }
        //����½ڵ�ȵ�ǰ�ڵ��
    else {
        //�����ǰ�ڵ��������Ϊ�������������
        if (current->right == nullptr) {
            current->right = newNode;
        }
        else
        {
            //�����ǰ�ڵ�����������������Ѱ�ҵ�ǰ�ڵ��������Ŀյ�������
            InsertNode(current->right, newNode);
        }
    }
}

//��������Ϣ��team.txt�ļ��ж�ȡ���������������������
void ProgrammingContestManagementSystem::LoadTeamsFromFile()         //��ȡ�ļ�
{
    ifstream inputFile("team.txt");   // �������ļ�
    ofstream outputFile("new-team.txt"); // ��������ļ�

    string line;

    srand(time(0)); // �����������
    if (inputFile.is_open() && outputFile.is_open()) {
        getline(inputFile,line);
        line+="  #   �����ɼ�";
        outputFile << line << endl; // д�뵽����ļ�
        //���������
        while (getline(inputFile, line)) {
            int scores = rand() % 41 + 60;  // ����60��100֮��������
            line += "\t#\t" + to_string(scores); // ����ĩβ��������
            outputFile << line << endl; // д�뵽����ļ�
        }

        inputFile.close();   // �ر������ļ�
        outputFile.close();  // �ر�����ļ�

        cout << "������ɣ�" << endl;
    } else {
        cout << "�޷����ļ���" << endl;
    }
    ifstream inFile;
    inFile.open("new-team.txt",ios::in);//���ļ�
    if (!inFile.is_open()) {
        cout << "�޷����ļ� \n";
        return;
    }

    getline(inFile, line); // ��ȡ�ļ��еı����У�����

    while (getline(inFile, line)) {


        // ʹ�� stringstream ���зָ�
        stringstream ss(line);
        string temp;

        string teamNumber;
        getline(ss, teamNumber, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // ����������Ʒ���Ƶ� #
        string projectName;
        getline(ss, projectName, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // ��������ѧУ�� #
        string university;
        getline(ss, university, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // ������������ #
        string eventCategory;
        getline(ss, eventCategory, '\t');
        ss.ignore();

        getline(ss, temp, '\t'); // ���������ߵ� #
        string participants;
        getline(ss, participants, '\t');
        ss.ignore();


        getline(ss, temp, '\t'); // ����ָ����ʦ�� #
        string guideTeacher;
        getline(ss, guideTeacher,'\t');


        getline(ss, temp, '\t'); // ���������� #
        string scores;
        getline(ss, scores, '\t');
        ss.ignore();


        // �����ʽ������Ϣ
        cout << "����������: " << teamNumber << endl;
        cout << "������Ʒ����: " << projectName << endl;
        cout << "����ѧУ: " << university << endl;
        cout << "�������: " << eventCategory << endl;
        cout << "������: " << participants << endl;
        cout << "ָ����ʦ: " << guideTeacher << endl;
        cout << "�����ɼ�: " << scores << endl;

        // Ϊ��ǰ�е���Ϣ�ö����Ŵ���һ���µĶ���ڵ�
        TeamNode* newNode = new TeamNode(teamNumber,projectName,university,eventCategory,participants,guideTeacher,scores);
        //������ڵ�Ϊ����ǰ�ڵ���Ǹ��ڵ�
        if (root == nullptr)
        {
            root = newNode;
        }
            //������ڵ㲻�գ��򽫴������½ڵ���뵽������������
        else
        {
            InsertNode(root, newNode);
        }
        cout << endl;
    }
    //��ȡ��ϣ��ر��ļ�
    inFile.close();
    cout << "����������\n";
    cout<<endl;
}

//��Ӷ�����Ϣ
void ProgrammingContestManagementSystem::AddTeam()
{
    //���ȴ����½ڵ㣬�Ա�����Ҫ��ӵĶ�����Ϣ
    TeamNode* newNode = new TeamNode;

    string teamNumber1;
    // ���û������ȡ����������Ϣ
    cout << "��������������ţ�";
    cin.ignore(); // ����֮ǰ�Ļ��з�
    cin>>teamNumber1;
    string line;
    ifstream inFile;
    inFile.open("new-team.txt",ios::in);//���ļ�
    if (!inFile.is_open()) {
        cout << "�޷����ļ� \n";
        return;
    }

    getline(inFile, line); // ��ȡ�ļ��еı����У�����

    while (getline(inFile, line)) {
        // ʹ�� stringstream ���зָ�
        stringstream ss(line);
        string temp;

        string teamNumber;
        getline(ss, teamNumber, '\t');
        ss.ignore();

        if(teamNumber1==teamNumber)
        {
            cout<<"�ö����Ѵ���,���������룺"<<endl;
            AddTeam();
        }
        else
            newNode->team.teamNumber=teamNumber1;
    }
    cin.ignore(); // ����֮ǰ�Ļ��з�
    cout << "�����������Ʒ���ƣ�";
    getline(cin, newNode->team.projectName);
    cout << "���������ѧУ��";
    getline(cin, newNode->team.university);
    cout << "�������������";
    getline(cin, newNode->team.eventCategory);
    cout<<endl;
    cout << "����������ߣ�";
    getline(cin, newNode->team.participants);
    cout << "������ָ����ʦ��";
    getline(cin, newNode->team.guideTeacher);
    cout << "����������ɼ���";
    getline(cin, newNode->team.scores);
    //��txt�ļ����޸�
    ofstream mycout("new-team.txt", ios::app);
    mycout << newNode->team.teamNumber << "	#	" << newNode->team.projectName << "	#	"  << newNode->team.university << "	#	" << newNode->team.eventCategory << "	#	" << newNode->team.participants <<  "	#	" << newNode->team.guideTeacher<<"	  #	   " << newNode->team.scores << endl;
    mycout.close();


    //�����Ϣ¼����ɣ�����ǰ�ڵ�����������ֱ�Ϊ��
    newNode->left = nullptr;
    newNode->right = nullptr;

    // ����ڵ㵽����������
    //������ڵ�Ϊ�գ���ǰ�ڵ���Ǹ��ڵ�
    if (root == nullptr) {
        root = newNode;
    }
        //���򽫵�ǰ�ڵ���������������
    else {
        InsertNode(root, newNode);
    }
    //������ӳɹ�����ʾ

    cout << "����������Ϣ����ӡ�"<<endl;
}
//�޸�
void ProgrammingContestManagementSystem::ModifyTeam()
{
    if (root == nullptr) {
        cout << "��ǰ�޲���������Ϣ��\n";
        return;
    }

    string teamNumber;
    cout << "������Ҫ�޸ĵĲ��������ţ�";
    cin >> teamNumber;

    TeamNode* target = SearchNode(root, teamNumber);
    if (target == nullptr) {
        cout << "δ�ҵ���Ӧ�Ĳ���������Ϣ��\n";
        return;
    }

    // ������Ҫ���޸Ĳ���������ֶ���Ϣ
    cout << "�������µĲ�����Ʒ���ƣ�";
    cin.ignore();
    getline(cin, target->team.projectName);
    cout << "�������µĲ���ѧУ��";
    getline(cin, target->team.university);
    cout << "�������µ��������";
    getline(cin, target->team.eventCategory);
    cout<<endl;
    cout << "�������µĲ����ߣ�";
    getline(cin, target->team.participants);
    cout << "�������µ�ָ����ʦ��";
    getline(cin, target->team.guideTeacher);
    cout << "�������µĳ����ɼ���";
    getline(cin, target->team.scores);

    UpdateInFile(teamNumber, target->team);
    // ����޸ĳɹ�����ʾ��Ϣ
    cout << "����������Ϣ���޸Ĳ����浽�ļ��С�\n";
}

//�����������ָ���ڵ�ĸ߶�
int ProgrammingContestManagementSystem::GetHeight(TeamNode* node)
{
    if (node == nullptr) {
        return 0;
    }

    int leftHeight = GetHeight(node->left);
    int rightHeight = GetHeight(node->right);

    return 1 + max(leftHeight, rightHeight);
}
//�����������ָ���ڵ��ƽ������
int ProgrammingContestManagementSystem::GetBalanceFactor(TeamNode* node)
{
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = GetHeight(node->left);
    int rightHeight = GetHeight(node->right);
    return leftHeight - rightHeight;
}
//����
TeamNode* ProgrammingContestManagementSystem::RotateLeft(TeamNode* node)
{
    //��ǰ�ڵ�����ӽڵ㱣����newRoot��
    TeamNode* newRoot = node->right;
    //ԭ���ӽڵ�����ӽڵ㱣����subtree��
    TeamNode* subtree = newRoot->left;

    // ����
    //����ǰ�ڵ��Ϊ��ΪnewRoot�����ӽڵ�
    newRoot->left = node;
    //��ԭ���ӽڵ�����ӽڵ��Ϊ��ǰ�ڵ�����ӽڵ�
    node->right = subtree;
    //�����µĸ��ڵ㣨��ǰ�ڵ�����ӽڵ㣩
    return newRoot;
}
//������ͬ�ϣ�
TeamNode* ProgrammingContestManagementSystem::RotateRight(TeamNode* node)
{
    TeamNode* newRoot = node->left;
    TeamNode* subtree = newRoot->right;

    // ����
    newRoot->right = node;
    node->left = subtree;

    return newRoot;
}
//����С�ڵ�
TeamNode* ProgrammingContestManagementSystem::FindMinimumNode(TeamNode* current)
{
    //������������ʱ�ҵ�����ߵĽڵ������С�ڵ�
    while (current->left != nullptr) {
        current = current->left;
    }
    //������Ϊ����ǰ�ڵ������С�ڵ�
    return current;
}
//���ļ���ɾ��
void ProgrammingContestManagementSystem::Deletefile(string id)
{
    ifstream inputFile("new-team.txt");

    if (!inputFile) {
        cout << "�޷����ļ�\n";
        return;
    }

    // ����һ����ʱ�ļ�
    ofstream outputFile("temp.txt");

    if (!outputFile) {
        cout << "�޷������ļ� temp.txt\n";
        inputFile.close();
        return;
    }

    string line;
    string contentToRemove = id;  // Ҫɾ��������

    while (getline(inputFile, line))
    {
        if (line.find(contentToRemove) != string::npos)
        {
            // ��������Ҫɾ�����ݵ���
            continue;
        }

        // ��������Ҫɾ�����ݵ���д����ʱ�ļ���
        outputFile << line << endl;
    }

    inputFile.close();
    outputFile.close();

    remove("new-team.txt");        // ɾ��ԭʼ�ļ�
    rename("temp.txt", "new-team.txt");  // ����ʱ�ļ�������Ϊԭʼ�ļ�������
}
//�ڶ��������ҵ���Ҫɾ���Ľڵ�
TeamNode* ProgrammingContestManagementSystem::DeleteNode(TeamNode* current, const string& teamNumber)
{
    // �����ǰ�ڵ�Ϊ�գ��򷵻ص�ǰ�ڵ�
    if (current == nullptr) {
        return current;
    }
    // �����Ҫɾ���Ľڵ��űȵ�ǰ�ڵ���С������ǰ�ڵ������������Ҫɾ���Ľڵ㲢������ǰ�ڵ������
    if (teamNumber.compare(current->team.teamNumber) < 0) {
        current->left = DeleteNode(current->left, teamNumber);
    }
        // �����Ҫɾ���Ľڵ��űȵ�ǰ�ڵ��Ŵ�����ǰ�ڵ���Һ���������Ҫɾ���Ľڵ㲢������ǰ�ڵ���Һ���
    else if (teamNumber.compare(current->team.teamNumber) > 0) {
        current->right = DeleteNode(current->right, teamNumber);
    }
        //��Ҫɾ���Ľڵ��ź͵�ǰ�ڵ������
    else {
        // �ҵ�Ҫɾ���Ľڵ�

        // ����ڵ�ΪҶ�ӽڵ��ֻ��һ���ӽڵ�
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

        // ����ڵ��������ӽڵ�
        TeamNode* successor = FindMinimumNode(current->right);
        current->team = successor->team;
        current->right = DeleteNode(current->right, successor->team.teamNumber);
    }

    // ����ƽ�����
    int balanceFactor = GetBalanceFactor(current);

    // ��������
    if (balanceFactor > 1 && GetBalanceFactor(current->left) >= 0) {
        return RotateRight(current);
    }

    // ��������
    if (balanceFactor < -1 && GetBalanceFactor(current->right) <= 0) {
        return RotateLeft(current);
    }

    // ����������
    if (balanceFactor > 1 && GetBalanceFactor(current->left) < 0) {
        current->left = RotateLeft(current->left);
        return RotateRight(current);
    }

    // ����������
    if (balanceFactor < -1 && GetBalanceFactor(current->right) > 0) {
        current->right = RotateRight(current->right);
        return RotateLeft(current);
    }
    //���ص�ǰ�ڵ���Ϊɾ����ĸ��ڵ�
    return current;
}
//ɾ������������Ϣ
void ProgrammingContestManagementSystem::DeleteTeam(string teamNumber)
{
    //������ڵ�Ϊ�գ�˵��������û�в���������Ϣ���޷�����ɾ��
    if (root == nullptr) {
        cout << "��ǰ�޲���������Ϣ��\n";
        return;
    }

    // ����Ҫɾ���Ľڵ㣬�����ҵ��Ľڵ㸳ֵ��һ���µĽڵ�targetNode
    TeamNode* targetNode = SearchNode(root, teamNumber);
    //����Ҳ���Ҫɾ���Ľڵ㣬������ʾ
    if (targetNode == nullptr) {
        cout << "δ�ҵ���Ӧ�Ĳ���������Ϣ��\n";
        return;
    }
    //�ҵ�Ҫɾ���Ľڵ�
    // ִ��ɾ������
    root = DeleteNode(root, teamNumber);
    Deletefile(teamNumber);
    cout << "����������Ϣ��ɾ����\n";
}

//����Ų��Ҷ��鲢���ASL
void ProgrammingContestManagementSystem::SearchTeam()
{
    int totalPathLength = 0;
    int nodeCount = 0;
    //������ڵ�Ϊ�գ�˵��������û�в���������Ϣ���޷����в�ѯ
    if (root == nullptr) {
        cout << "��ǰ�޲���������Ϣ��\n";
        return;
    }

    string teamNumber;
    cout << "������Ҫ��ѯ�Ĳ��������ţ�"<<endl;
    cin >> teamNumber;

    // ����Ҫ��ѯ�Ľڵ㣬�����ҵ��Ľڵ㸳ֵ��һ���µĽڵ�targetNode
    TeamNode* targetNode = SearchNode(root, teamNumber);
    //����Ҳ���Ҫ��ѯ�Ľڵ㣬������ʾ
    if (targetNode == nullptr) {
        cout << "δ�ҵ���Ӧ�Ĳ���������Ϣ��\n";
        SearchTeam();
        return ;
    }

    //�ҵ�Ҫ��ѯ�Ľڵ�
    cout << "����������: " << targetNode->team.teamNumber << endl;
    cout << "������Ʒ����: " << targetNode->team.projectName << endl;
    cout <<"����ѧУ: " << targetNode->team.university << endl;
    cout << "�������: "<<targetNode->team.eventCategory << endl;
    cout << "������: "<<targetNode->team.participants << endl;
    cout << "ָ����ʦ: " <<targetNode->team.guideTeacher << endl;
    cout << "�����ɼ�: " <<targetNode->team.scores << endl;
    cout << "���в����ӵ�ƽ�����ҳ������£�"<<endl;
    string line;
    ifstream inFile;
    inFile.open("new-team.txt",ios::in);//���ļ�
    if (!inFile.is_open()) {
        cout << "�޷����ļ� \n";
        return;
    }

    getline(inFile, line); // ��ȡ�ļ��еı����У�����

    while (getline(inFile, line)) {
        // ʹ�� stringstream ���зָ�
        stringstream ss(line);
        string temp;

        string teamNumber;
        getline(ss, teamNumber, '\t');
        ss.ignore();

        // ����Ҫ��ѯ�Ľڵ㲢����·������
        int pathLength = CalculatePathLength(root, teamNumber, 1);
        if (pathLength == 0) {
            cout << "δ�ҵ���Ӧ�Ĳ���������Ϣ��\n";
            return;
        }

        totalPathLength += pathLength;
        nodeCount++;

        double asl = static_cast<double>(totalPathLength) / nodeCount;
        cout << "����"<<teamNumber<<"��ƽ�����ҳ���ASL��" << asl << endl;
    }

}
//���Ұ������Žڵ�
TeamNode* ProgrammingContestManagementSystem::SearchNode(TeamNode* current, const string& teamNumber)//��Ҫ��ǰ�ڵ��Ҫ���ҵĶ�������Ϣ
{
    //�����ǰ�ڵ�Ϊ�ջ��ߵ�ǰ�ڵ�Ķ����ŵ�����Ҫ���ҵĶ����ţ��򷵻ص�ǰ�ڵ�
    if (current == nullptr || current->team.teamNumber.compare(teamNumber) == 0) {
        return current;
    }
    //��Ҫ���ҵĽڵ��űȵ�ǰ�ڵ���С����ȥ��ǰ�ڵ���������м���Ѱ��
    if (teamNumber.compare(current->team.teamNumber) < 0) {
        return SearchNode(current->left, teamNumber);
    }
        //��Ҫ���ҵĽڵ��űȵ�ǰ�ڵ��Ŵ���ȥ��ǰ�ڵ���������м���Ѱ��
    else {
        return SearchNode(current->right, teamNumber);
    }
}

// ���ı��ļ����޸Ĳ���������Ϣ
void ProgrammingContestManagementSystem::UpdateInFile(string teamNumber, const Team& updatedInfo) {
    ifstream inputFile;
    inputFile.open("new-team.txt",ios::in);
    if (!inputFile.is_open()) {
        cout << "�޷����ĵ�" << endl;
        return;
    }

    ofstream outputFile("temp.txt");
    if (!outputFile.is_open()) {
        cout << "�޷�������ʱ�ļ�" << endl;
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
            // �ҵ�Ҫ�޸ĵĶ�����Ϣ�����µ���Ϣд����ʱ�ļ�
            outputFile << teamNumber << "	#	" << updatedInfo.projectName << "	#	" << updatedInfo.university << "	#	" << updatedInfo.eventCategory << "	#	" << updatedInfo.participants << "	#	" << updatedInfo.guideTeacher << "	#	" << updatedInfo.scores << endl;
        }
        else {
            // ��ԭʼ��д����ʱ�ļ�
            outputFile << line << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    if (SearchNode(root, teamNumber) != nullptr) {
        remove("new-team.txt");       // ɾ��ԭʼ�Ķ�����Ϣ�ļ�
        rename("temp.txt", "new-team.txt");  // ����ʱ�ļ�������Ϊԭʼ�Ķ�����Ϣ�ļ�

    }
    else {
        remove("temp.txt");  // ɾ����ʱ�ļ�
        cout << "δ�ҵ�ָ���Ķ�����Ϣ���޷��޸ġ�" << endl;
    }
}
//�������������Ϣ
void ProgrammingContestManagementSystem::Management()
{
    int choice;
    do {
        cout << "============= �˵� =============\n";
        cout << "1. ���Ӳ���������Ϣ\n";
        cout << "2. �޸Ĳ���������Ϣ\n";
        cout << "3. ɾ������������Ϣ\n";
        cout << "4. ��ѯ������������\n";
        cout << "0.      �˳�\n";
        cout << "===============================\n";
        cout << "������ѡ�";
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
                cout << "��������Ҫɾ���Ķ����ţ�";
                cin >> teamNumber;
                DeleteTeam(teamNumber);
                break;
            }
            case 4:
                SearchFinalTeam();
                break;
            case 0:
                cout << "�������˳���\n";
                break;
            default:
                cout << "��Чѡ����������롣\n";
                break;
        }
    } while (choice != 0);
}
//����·������
int ProgrammingContestManagementSystem::CalculatePathLength(TeamNode* node, const string& teamNumber, int level) {
    if (node == nullptr) {
        return 0;  // δ�ҵ�Ŀ��ڵ�
    }
    if (teamNumber < node->team.teamNumber) {
        return 1 + CalculatePathLength(node->left, teamNumber, level + 1);
    }
    else if (teamNumber > node->team.teamNumber) {
        return 1 + CalculatePathLength(node->right, teamNumber, level + 1);
    }
    else {
        return level;  // �ҵ�Ŀ��ڵ㣬����·������
    }
}
//����״̬
string ProgrammingContestManagementSystem::statusToString(TeamStatus status) {
    switch (status) {
        case Waiting: return "��";
        case Playing: return "������";
        case Finished: return "��������";
        default: return "δ֪״̬";
    }
}
//��ӡ���
void ProgrammingContestManagementSystem::printCurrentStatus(const vector<vector<Team>>& rooms, const time_t& currentTime) {
    struct tm* localTime = localtime(&currentTime);
    cout << "=====================" << put_time(localTime, "%Y-%m-%d %H:%M:%S") << "=====================" << endl;
    for (size_t i = 0; i < rooms.size(); ++i) {
        cout << "������" << i + 1 << ":" << endl;
        for (const auto& team : rooms[i]) {
            cout << "������:" << team.teamNumber <<"    �����ɼ���"<<team.scores << "    ״̬:" << statusToString(team.status) << endl;
        }
        cout << "==========" << endl;
    }
}
//�ж��Ƿ����ж��鶼����ɱ���
bool ProgrammingContestManagementSystem::isCompetitionFinished(const vector<vector<Team>>& rooms) {
    return all_of(rooms.begin(), rooms.end(), [](const vector<Team>& room) {
        return all_of(room.begin(), room.end(), [](const Team& team) {
            return team.status == Finished;
        });
    });
}
//��ȡ�ļ�������ѭ�����
void ProgrammingContestManagementSystem::simulateCompetition(ifstream& file) {
    // �޸Ķ���Ϊ�������Ա��ֶ���״̬
    vector<vector<Team>> rooms(17);
    string line;
    getline(file,line);
    // ��ȡ�ͽ����ļ�
    while (getline(file, line)) {
        istringstream iss(line);
        Team team;
        team.status = Waiting;
        iss >> team.roomNumber >> team.teamNumber >> team.projectName >> team.university
            >> team.eventCategory >> team.participants >> team.guideTeacher >> team.scores;
        team.roomNumber--; // ʹ�����ұ�Ŵ�0��ʼ
        rooms[team.roomNumber].push_back(team);

        // �����ʽ������Ϣ
        //cout << "����������: " << team.teamNumber << "       �����ɼ�: " << team.scores << endl;
    }

    // Ϊÿ�������Ҷ�������
    for (auto& room : rooms) {
        selectionSort(room);
    }


    // ��ȡ��ǰʱ��
    time_t currentTime = time(nullptr);
    printCurrentStatus(rooms, currentTime);

    while (!isCompetitionFinished(rooms)) {
        //this_thread::sleep_for(chrono::milliseconds(500)); // ģ��0.5��
        currentTime += 5 * 60; // ����5����

        // ���¶���״̬
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
//ѡ������
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
// ���ɳ����ɼ���ӵ�final-tean1.txt�ļ���
void ProgrammingContestManagementSystem::simulateTeamStatusDisplay()  {

    ifstream inputFile("final-team.txt");   // �������ļ�
    ofstream outputFile("final-team1.txt"); // ��������ļ�

    string line;

    srand(time(0)); // �����������
    if (inputFile.is_open() && outputFile.is_open()) {
        getline(inputFile,line);
        line+="      �����ɼ�";
        outputFile << line << endl; // д�뵽����ļ�
        //���������
        while (getline(inputFile, line)) {
            int scores = rand() % 41 + 60;  // ����60��100֮��������
            line += "\t\t\t"+ to_string(scores); // ����ĩβ��������
            outputFile << line << endl; // д�뵽����ļ�
        }

        inputFile.close();   // �ر������ļ�
        outputFile.close();  // �ر�����ļ�

        cout << "������ɣ�" << endl;
    } else {
        cout << "�޷����ļ���" << endl;
    }
    ifstream file("final-team1.txt");
    if (!file.is_open()) {
        cerr << "�޷����ļ�" << endl;
    }
    simulateCompetition(file);
    file.close();
}

//����Ų��Ҷ��鲢������ھ�����
void ProgrammingContestManagementSystem::SearchFinalTeam()
{
    // �޸Ķ���Ϊ�������Ա��ֶ���״̬
    vector<vector<Team>> rooms(17);
    ifstream inputFile("final-team.txt");   // �������ļ�
    string line;
    getline(inputFile,line);
    // ��ȡ�ͽ����ļ�
    while (getline(inputFile, line)) {
        istringstream iss(line);
        Team team;
        iss >> team.roomNumber>> team.teamNumber ;
        team.roomNumber--; // ʹ�����ұ�Ŵ�0��ʼ
        rooms[team.roomNumber].push_back(team);

    }
    string teamNumberl;
    cout<<"������Ҫ��ѯ�Ķ�����"<<endl;
    cin>>teamNumberl;
    for (auto& room : rooms) {
        for (auto& team : room) {
            if(teamNumberl==team.teamNumber)
            {
                cout<<"�����Һ�Ϊ��"<<(team.roomNumber+1)<<endl;
            }
        }
    }


}
//����ϵͳ
void ProgrammingContestManagementSystem::CampusGuide() {
    unordered_map<int, string> destinationInfo = {
            {1, "����¥����;���칫¥"},
            {2, "���Ϻ�����;���������羰����"},
            {3, "ͼ��ݣ���;���������ϣ���ϰ��"},
            {4, "��ʳ�ã���;��������Ϣ"},
            {5, "���ٳ�����;���ܵ�������"},
            {6, "���ţ���;��ѧУ�Ĵ���"},
            {7, "�������ģ���;�������˶����ģ���Ժ�糡"},
            {8, "���ٳ�����;���ܵ�������"},
            {9, "����¥����;����ѧ¥"},
            {10, "�����¥����;��ʵ�����ģ���ѧ¥"},
            {11, "��ʳ�ã���;��������Ϣ"},
            {12, "������������;��ѧ������"}
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

    cout << "1.����¥ " << "2.���Ϻ� " << "3.ͼ��� " << "4.��ʳ�� " << "5.���ٳ� "<< "6.����\n" << "7.��������" << "8.���ٳ� " << "9.����¥ " << "10.�����¥" << "11.��ʳ�� " << "12.��������" << endl;

    int start, end;
    cout << "����������ţ�" << endl;
    cin >> start;
    cout << "�������յ��ţ�" << endl;
    cin >> end;

    if (destinationInfo.find(start) == destinationInfo.end() || destinationInfo.find(end) == destinationInfo.end()) {
        cout << "��������Ч�������յ��ţ�" << endl;
        return;
    }

    unordered_map<int, int> distance;//����
    unordered_map<int, int> prev;//ǰ���ڵ�
    vector<int> unvisited;//δ��������
    //��ʼ�������ǰ���ڵ㣬�����нڵ���Ϊδ����
    for (const auto& pair : destinationInfo) {
        const int& destination = pair.first;
        distance[destination] = numeric_limits<int>::max();
        prev[destination] = -1;
        unvisited.push_back(destination);
    }
    distance[start] = 0;
    //ѭ������δ���ʵĽڵ�
    while (!unvisited.empty()) {
        int u = unvisited[0];
        int minDistance = distance[u];
        for (const int& destination : unvisited) {
            if (distance[destination] < minDistance) {
                u = destination;
                minDistance = distance[destination];//ѡ�������С�Ľڵ���Ϊ��ǰ�ڵ�
            }
        }

        unvisited.erase(remove(unvisited.begin(), unvisited.end(), u), unvisited.end());

        if (u == end) {
            break;
        }
        //�����������ڽڵ�ľ����ǰ���ڵ�
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
        cout << "�޷��ҵ����·��" << endl;
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

    cout << "���·��Ϊ��" << endl;
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    cout << "·������Ϊ��" << distance[end] << " ��" << endl;
    cout << "��ϸ��Ϣ��" << endl;
    for (const int& destination : path) {
        cout << destination << ": " << destinationInfo[destination] << endl;
    }
}