//
// Created by Ǯ�� on 2023/12/12.
//
#include<iostream>
#include<fstream>
#include"ProgrammingContestManagementSystem.h"

using namespace std;

int main()
{
    int choice;

    do {
        cout << "�й���ѧ���������ƴ���ʡ�����¹���ϵͳ\n";
        cout << "==================================\n";
        cout << "========       �˵�      =========\n";
        cout << "========1. �������������Ϣ=========\n";
        cout << "========2. �������������Ϣ=========\n";
        cout << "========3. ��ѯ����������Ϣ=========\n";
        cout << "========    4. �к�ϵͳ   =========\n";
        cout << "========    5. ��������   =========\n";
        cout << "========      0. �˳�    =========\n";
        cout << "==================================\n";
        cout << "������ѡ�\n";
        cin >> choice;

        switch (choice) {
            case 1:
                ProgrammingContestManagementSystem a;
                a.Management();
                break;
            case 2:
                ProgrammingContestManagementSystem b;
                b.LoadTeamsFromFile();
                break;
            case 3: {
                ProgrammingContestManagementSystem c;
                c.SearchTeam();
                break;
            }
            case 4: {
                ProgrammingContestManagementSystem d;
                d.simulateTeamStatusDisplay();
                break;
            }
            case 5:
            {
                ProgrammingContestManagementSystem e;
                e.CampusGuide();
                break;
            }

            case 0:
                cout << "�������˳���\n";
                break;
            default:
                cout << "��Чѡ����������롣\n";
                break;
        }
    } while (choice != 0);
    return 0;
}