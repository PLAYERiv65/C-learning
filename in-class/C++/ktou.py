import numpy as np

# 定义模拟函数，考虑同时击杀的情况
def simulate_kills(a_attack_rate, a_damage_per_attack, b_attack_rate, b_damage_per_attack, total_monsters=100000, max_health=100):
    a_kills = 0
    b_kills = 0
    
    for _ in range(total_monsters):
        health = np.random.randint(1, max_health + 1)
        
        a_attack_interval = 1 / a_attack_rate
        b_attack_interval = 1 / b_attack_rate
        
        a_next_attack_time = a_attack_interval
        b_next_attack_time = b_attack_interval
        current_time = 0
        
        while health > 0:
            if current_time >= a_next_attack_time:
                health -= a_damage_per_attack
                a_next_attack_time += a_attack_interval
                
            if current_time >= b_next_attack_time:
                health -= b_damage_per_attack
                b_next_attack_time += b_attack_interval
                
            if health <= 0:
                if a_next_attack_time == b_next_attack_time:
                    a_kills += 0.5
                    b_kills += 0.5
                elif a_next_attack_time < b_next_attack_time:
                    a_kills += 1
                else:
                    b_kills += 1
                break
                
            current_time = min(a_next_attack_time, b_next_attack_time)
    
    a_kill_probability = a_kills / total_monsters
    b_kill_probability = b_kills / total_monsters
    
    return a_kill_probability, b_kill_probability

# 生成等DPS参数组，排除对称情况
def generate_equal_dps_params(dps, total_monsters=1000, max_health=100):
    params = []
    
    # 根据dps,使用生成器生成攻速和伤害的组合
    damage_options = [(damage, dps / damage) for damage in [1, 2, 5]]
    #不重复也不对称地选取参数
    for a_damage, a_attack_rate in damage_options:
        for b_damage, b_attack_rate in damage_options:
            if a_damage < b_damage:
                params.append((a_attack_rate, a_damage, b_attack_rate, b_damage))
    
    results = []
    for param in params:
        result = simulate_kills(*param, total_monsters=total_monsters, max_health=max_health)
        results.append((param, result))
    
    return results

# 假设A的DPS为10，B的DPS为20
dps = 10
results = generate_equal_dps_params(dps)
#百分比输出结果
for param, (a_kill_probability, b_kill_probability) in results:
    print(f"A的DPS参数：{param[0]} {param[1]}，B的DPS参数：{param[2]} {param[3]}，你的击杀概率：{a_kill_probability * 100:.2f}%，B的击杀概率：{b_kill_probability * 100:.2f}%")