#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Atom {
    ll x, y;
    ll vx, vy;
    ll energy;
};
ll map2[4010][4010] = {};

ll solve() {
    ll n;
    cin >> n;
    vector<Atom> atoms(n);
    memset(map2,0,sizeof(map2));

    // 입력 및 초기화
    for (ll i = 0; i < n; i++) {
        ll dir;
        cin >> atoms[i].x >> atoms[i].y >> dir >> atoms[i].energy;
        atoms[i].x *= 2;
        atoms[i].y *= 2;
        if (dir == 0) atoms[i].vx = 0, atoms[i].vy = 1;
        else if (dir == 1) atoms[i].vx = 0, atoms[i].vy = -1;
        else if (dir == 2) atoms[i].vx = -1, atoms[i].vy = 0;
        else if (dir == 3) atoms[i].vx = 1, atoms[i].vy = 0;
        atoms[i].x += 2000;
        atoms[i].y += 2000;

        // 초기 좌표 기록
        if (atoms[i].x >= 0 && atoms[i].x < 4010 && atoms[i].y >= 0 && atoms[i].y < 4010) {
            map2[atoms[i].x][atoms[i].y]++;
        }
    }

    ll ans = 0;

    // 시뮬레이션 루프
    for (ll t = 1; t <= 2000; t++) {
        for (auto &atom : atoms) {
            if (atom.energy == -1) continue;

            // 이전 위치에서 카운트 감소
            map2[atom.x][atom.y]--;
            // 새 위치로 이동
            atom.x += atom.vx;
            atom.y += atom.vy;

            // 새로운 위치가 범위를 벗어나면 무효화
            if (atom.x < 0 || atom.x >= 4010 || atom.y < 0 || atom.y >= 4010) {
                atom.energy = -1;
                continue;
            }

            // 새로운 위치에서 카운트 증가
            map2[atom.x][atom.y]++;
        }
        
        for (ll i = 0; i < atoms.size(); i++) {
            if (atoms[i].energy == -1) continue;
            if (map2[atoms[i].x][atoms[i].y] >= 2) {
               // printf("t:%lld ,i: %lld\n",t, i);
                ans += atoms[i].energy;
                atoms[i].energy = -1;
            }
        }

        for (ll i = 0; i < atoms.size(); i++) {
          auto atom=atoms[i];
          if (atom.x < 0 || atom.x >= 4010 || atom.y < 0 || atom.y >= 4010) {
                
                continue;
            }
            if(map2[atom.x][atom.y]>=2) map2[atom.x][atom.y]=0;
        }
       

        // 무효화된 원자 제거
        atoms.erase(remove_if(atoms.begin(), atoms.end(), [](const Atom& atom) {
            return atom.energy == -1;
        }), atoms.end());
    }

    return ans;
}

int main() {
    ll T;
    cin >> T;
    for (ll i = 1; i <= T; i++) {
        cout << "#" << i << " " << solve() << endl;
    }
    return 0;
}
