//
// Created by Ǯ�� on 2023/12/12.
//

#ifndef EVENTMANAGEMENTSYSTEM_EVENTMANAGEMENTSYSTEM_H
#define EVENTMANAGEMENTSYSTEM_EVENTMANAGEMENTSYSTEM_H

#endif //EVENTMANAGEMENTSYSTEM_EVENTMANAGEMENTSYSTEM_H
#pragma once  //��֤ͷ�ļ�ֻ������һ�Σ���ֹͷ�ļ����ظ����á�ͬһ���ļ����ᱻ�����Ρ�
#include<string>
#include<vector>
#include <list>


using namespace std;

enum TeamStatus {
    Waiting,
    Playing,
    Finished
};
// ��������ṹ��
struct Team {


    string teamNumber;
    string projectName;
    string university;
    string eventCategory;
    string participants;
    string guideTeacher;
    string scores;
    int roomNumber;
    TeamStatus status; // ��Ӷ���״̬

};

// ��������ڵ�ṹ��
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

    // ���캯�������ܶ�������Ϊ����
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
    TeamNode* SearchNode(TeamNode* current, const string& teamNumber);//���Ҷ���ڵ�
    TeamNode* RotateLeft(TeamNode* node);//����
    TeamNode* RotateRight(TeamNode* node);//����
    TeamNode* FindMinimumNode(TeamNode* current);//������С�ڵ�
    TeamNode* DeleteNode(TeamNode* current, const string& teamNumber);//ɾ������ڵ�
    void UpdateInFile(string teamNumber, const Team& updatedInfo);//�����ļ��ڶ�����Ϣ
    void ModifyTeam();//�޸Ķ�����Ϣ
    void Management();//���������Ϣ
    void DeleteTeam(string teamNumber);//ɾ��������Ϣ
    void SearchTeam();//��ѯ������Ϣ
    void AddTeam();//��Ӷ�����Ϣ
    void InsertNode(TeamNode* current, TeamNode* newNode);//�������ڵ�
    void LoadTeamsFromFile();//���ļ��ж�ȡ������Ϣ
    int GetHeight(TeamNode* node);//��ȡ�ڵ�߶�
    int GetBalanceFactor(TeamNode* node);//��ȡƽ������
    void Deletefile(string id);//ɾ���ļ��ڶ�����Ϣ
    void CampusGuide();//У԰����
    void simulateTeamStatusDisplay();//ģ�����״̬��ʾ
    void simulateCompetition(ifstream& file);//ģ�����
    void printCurrentStatus(const vector<vector<Team>>& rooms, const time_t& currentTime);//��ӡ��ǰ״̬
    bool isCompetitionFinished(const vector<vector<Team>>& rooms);//�жϱ����Ƿ����
    int CalculatePathLength(TeamNode* node, const string& teamNumber, int level);//����·������
    void selectionSort(vector<Team>& data);//ѡ������
    string statusToString(TeamStatus status);//����״̬ת�ַ���
    void SearchFinalTeam();
};
