//
// Created by 钱鑫 on 2023/12/12.
//
#include<iostream>
#include<fstream>
#include"ProgrammingContestManagementSystem.h"

using namespace std;

int main()
{
    int choice;

    do {
        cout << "中国大学生计算机设计大赛省级赛事管理系统\n";
        cout << "==================================\n";
        cout << "========       菜单      =========\n";
        cout << "========1. 管理参赛队伍信息=========\n";
        cout << "========2. 浏览参赛队伍信息=========\n";
        cout << "========3. 查询参赛队伍信息=========\n";
        cout << "========    4. 叫号系统   =========\n";
        cout << "========    5. 导航服务   =========\n";
        cout << "========      0. 退出    =========\n";
        cout << "==================================\n";
        cout << "请输入选项：\n";
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
                cout << "程序已退出。\n";
                break;
            default:
                cout << "无效选项，请重新输入。\n";
                break;
        }
    } while (choice != 0);
    return 0;
}