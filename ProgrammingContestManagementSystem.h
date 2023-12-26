//
// Created by 钱鑫 on 2023/12/12.
//

#ifndef EVENTMANAGEMENTSYSTEM_EVENTMANAGEMENTSYSTEM_H
#define EVENTMANAGEMENTSYSTEM_EVENTMANAGEMENTSYSTEM_H

#endif //EVENTMANAGEMENTSYSTEM_EVENTMANAGEMENTSYSTEM_H
#pragma once  //保证头文件只被编译一次，防止头文件被重复引用。同一个文件不会被编译多次。
#include<string>
#include<vector>
#include <list>


using namespace std;

enum TeamStatus {
    Waiting,
    Playing,
    Finished
};
// 参赛队伍结构体
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

// 参赛队伍节点结构体
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

class ProgrammingContestManagementSystem
{
public:
    TeamNode* SearchNode(TeamNode* current, const string& teamNumber);//查找队伍节点
    TeamNode* RotateLeft(TeamNode* node);//左旋
    TeamNode* RotateRight(TeamNode* node);//右旋
    TeamNode* FindMinimumNode(TeamNode* current);//查找最小节点
    TeamNode* DeleteNode(TeamNode* current, const string& teamNumber);//删除队伍节点
    void UpdateInFile(string teamNumber, const Team& updatedInfo);//更新文件内队伍信息
    void ModifyTeam();//修改队伍信息
    void Management();//管理队伍信息
    void DeleteTeam(string teamNumber);//删除队伍信息
    void SearchTeam();//查询队伍信息
    void AddTeam();//添加队伍信息
    void InsertNode(TeamNode* current, TeamNode* newNode);//插入队伍节点
    void LoadTeamsFromFile();//从文件中读取队伍信息
    int GetHeight(TeamNode* node);//获取节点高度
    int GetBalanceFactor(TeamNode* node);//获取平衡因子
    void Deletefile(string id);//删除文件内队伍信息
    void CampusGuide();//校园导航
    void simulateTeamStatusDisplay();//模拟队伍状态显示
    void simulateCompetition(ifstream& file);//模拟比赛
    void printCurrentStatus(const vector<vector<Team>>& rooms, const time_t& currentTime);//打印当前状态
    bool isCompetitionFinished(const vector<vector<Team>>& rooms);//判断比赛是否结束
    int CalculatePathLength(TeamNode* node, const string& teamNumber, int level);//计算路径长度
    void selectionSort(vector<Team>& data);//选择排序
    string statusToString(TeamStatus status);//队伍状态转字符串
    void SearchFinalTeam();
};
