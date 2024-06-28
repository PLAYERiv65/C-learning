#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

// 模拟函数，计算在特定条件下A和B的击杀概率
void simulate_single_case(int total_monsters, int max_health, double& your_kill_probability, double& b_kill_probability) {
    double your_kills = 0;
    double b_kills = 0;

    int your_attack_rate = 1; // A的攻击频率为1次/秒
    int your_damage_per_attack = 10; // A每次攻击造成10点伤害
    int b_attack_rate = 2; // B的攻击频率为2次/秒
    int b_damage_per_attack = 5; // B每次攻击造成5点伤害

    double your_attack_interval = 1.0 / your_attack_rate;
    double b_attack_interval = 1.0 / b_attack_rate;

    // 随机数种子
    std::srand(std::time(0));

    for (int i = 0; i < total_monsters; ++i) {
        int health = std::rand() % max_health + 1; // 随机生成怪物血量

        double your_next_attack_time = 0;
        double b_next_attack_time = 0;

        while (health > 0) {
            if (your_next_attack_time <= b_next_attack_time) {
                health -= your_damage_per_attack;
                your_next_attack_time += your_attack_interval;

                if (health <= 0) {
                    if (your_next_attack_time == b_next_attack_time) {
                        your_kills += 0.5;
                        b_kills += 0.5;
                    } else {
                        your_kills += 1;
                    }
                    break;
                }
            } else {
                health -= b_damage_per_attack;
                b_next_attack_time += b_attack_interval;

                if (health <= 0) {
                    if (your_next_attack_time == b_next_attack_time) {
                        your_kills += 0.5;
                        b_kills += 0.5;
                    } else {
                        b_kills += 1;
                    }
                    break;
                }
            }
        }
    }

    your_kill_probability = static_cast<double>(your_kills) / total_monsters;
    b_kill_probability = static_cast<double>(b_kills) / total_monsters;
}

int main() {
    int total_monsters = 1000000; // 怪物数量
    int max_health = 100; // 怪物最大血量
    double your_kill_probability = 0.0;
    double b_kill_probability = 0.0;

    simulate_single_case(total_monsters, max_health, your_kill_probability, b_kill_probability);

    std::cout << "Your kill probability: " << your_kill_probability << std::endl;
    std::cout << "B's kill probability: " << b_kill_probability << std::endl;

    return 0;
}
