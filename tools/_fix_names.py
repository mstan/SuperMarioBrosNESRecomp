import re
for p in ['semcomp/EnemyHandlers2.h', 'semcomp/EnemyHandlers2.cpp', '_wiring_EnemyHandlers2.txt']:
    with open(p, 'r', encoding='utf-8') as f: s = f.read()
    s = s.replace('kill_all_enemies', 'kill_all_enemies_d071')
    s = s.replace('move_d__bowser', 'move_d_bowser')
    s = s.replace('inc3_b', 'inc_3b')
    s = s.replace('init_v_stf', 'init_vstf')
    with open(p, 'w', encoding='utf-8') as f: f.write(s)
print('ok')
