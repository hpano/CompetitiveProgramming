#include <bits/stdc++.h>
#define dbg(x) std::cerr << #x << "=" << x << std::endl

const int H = 20, W = 20;
const int N = 100;

enum Instruction
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    GET,
    RELEASE
};

void Input(std::vector<int> &initial_pos_i, std::vector<int> &initial_pos_j)
{
    initial_pos_i.resize(N);
    initial_pos_j.resize(N);

    for (int i = 0; i < N; i++)
    {
        std::cin >> initial_pos_i[i] >> initial_pos_j[i];
    }
}

void AddAnswer(std::vector<char> &answer, Instruction d)
{
    switch (d)
    {
    case UP:
        answer.push_back('U');
        break;
    case DOWN:
        answer.push_back('D');
        break;
    case RIGHT:
        answer.push_back('R');
        break;
    case LEFT:
        answer.push_back('L');
        break;
    case GET:
        answer.push_back('I');
        break;
    case RELEASE:
        answer.push_back('O');
        break;
    default:
        break;
    }
}

int CalcDist(int i0, int j0, int i1, int j1)
{
    return (int)std::abs(i0 - i1) + (int)std::abs(j0 - j1);
}

inline bool IsNotCollected(int i, const std::vector<std::vector<int>> &card_map, const std::vector<int> &pos_i, const std::vector<int> &pos_j)
{
    return card_map[pos_i[i]][pos_j[i]] == i;
}

void ProceedStep(int &ci, int &cj, int ti, int tj, std::vector<char> &answer)
{
    if (ci != ti)
    {
        if (ci < ti)
        {
            ci++;
            AddAnswer(answer, DOWN);
        }
        else
        {
            ci--;
            AddAnswer(answer, UP);
        }
    }
    else
    {
        if (cj < tj)
        {
            cj++;
            AddAnswer(answer, RIGHT);
        }
        else
        {
            cj--;
            AddAnswer(answer, LEFT);
        }
    }
}

void GetCard(int i, std::vector<std::vector<int>> &card_map, const std::vector<int> &pos_i, const std::vector<int> &pos_j, std::stack<int> &cards, std::vector<char> &answer)
{
    cards.push(i);
    card_map[pos_i[i]][pos_j[i]] = -1;
    AddAnswer(answer, GET);
}

void ReleaseCard(int ci, int cj, std::vector<std::vector<int>> &card_map, std::vector<int> &pos_i, std::vector<int> &pos_j, std::stack<int> &cards, std::vector<char> &answer)
{
    int i = cards.top();
    cards.pop();
    card_map[ci][cj] = i;
    pos_i[i] = ci;
    pos_j[i] = cj;
    AddAnswer(answer, RELEASE);
}

inline bool IsValidPoint(int i, int j)
{
    return i >= 0 && i < H && j >= 0 && j < W;
}

bool IsEmptyPoint(int i, int j, const std::vector<std::vector<int>> &card_map)
{
    return card_map[i][j] == -1;
}

void CalcCloseReleasePoint(int ci, int cj, int &ni, int &nj, const std::vector<std::vector<int>> &card_map)
{
    for (int dist = 1; dist <= H; dist++)
    {
        for (int absi = 0; absi <= dist; absi++)
        {
            int absj = dist - absi;
            for (int sgni : {-1, +1})
            {
                for (int sgnj : {-1, +1})
                {
                    int ti = ci + absi * sgni;
                    int tj = cj + absj * sgnj;
                    if (IsValidPoint(ti, tj) && card_map[ti][tj] == -1)
                    {
                        ni = ti;
                        nj = tj;
                        return;
                    }
                }
            }
        }
    }
}

int CalcPenalty(const std::vector<char> &v)
{
    int pen = 0;
    for (char c : v)
    {
        if (c == 'R' || c == 'L' || c == 'U' || c == 'D')
        {
            pen++;
        }
    }
    return pen;
}

std::vector<char> MergeAnswer(const std::vector<char> &a, const std::vector<char> &b)
{
    std::vector<char> x;
    for (char c : a)
    {
        x.push_back(c);
    }
    for (char c : b)
    {
        x.push_back(c);
    }
    return x;
}

std::vector<char> Solve(std::vector<int> &initial_pos_i, std::vector<int> &initial_pos_j)
{
    /*std::vector<char> ini_answer;
    { // compress
        std::vector<int> pos_i(N), pos_j(N);
        std::vector<std::vector<int>> card_map(H, std::vector<int>(W, -1));
        for (int i = 0; i < N; i++)
        {
            pos_i[i] = initial_pos_i[i];
            pos_j[i] = initial_pos_j[i];
            card_map[pos_i[i]][pos_j[i]] = i;
        }
        std::stack<int> cards;

        int si = 0, sj = 0;
        while (!(si == H - 1 && sj == 0))
        {
            if (!IsEmptyPoint(si, sj, card_map))
            {
                GetCard(card_map[si][sj], card_map, pos_i, pos_j, cards, ini_answer);
            }
            if (si % 2 == 0)
            {
                if (sj == W - 1)
                {
                    // si++;
                    ProceedStep(si, sj, si + 1, sj, ini_answer);
                }
                else
                {
                    // sj++;
                    ProceedStep(si, sj, si, sj + 1, ini_answer);
                }
            }
            else
            {
                if (sj == 0)
                {
                    // si++;
                    ProceedStep(si, sj, si + 1, sj, ini_answer);
                }
                else
                {
                    // sj--;
                    ProceedStep(si, sj, si, sj - 1, ini_answer);
                }
            }
        }
        if (!IsEmptyPoint(si, sj, card_map))
        {
            GetCard(card_map[si][sj], card_map, pos_i, pos_j, cards, ini_answer);
        }

        while (!(si == H - 1 && sj == (W / 2) - 1))
        {
            ReleaseCard(si, sj, card_map, pos_i, pos_j, cards, ini_answer);
            if (sj % 2 == 0)
            {
                if (si == H / 2)
                {
                    // sj++;
                    ProceedStep(si, sj, si, sj + 1, ini_answer);
                }
                else
                {
                    // si--;
                    ProceedStep(si, sj, si - 1, sj, ini_answer);
                }
            }
            else
            {
                if (si == H - 1)
                {
                    // sj++;
                    ProceedStep(si, sj, si, sj + 1, ini_answer);
                }
                else
                {
                    // si++;
                    ProceedStep(si, sj, si + 1, sj, ini_answer);
                }
            }
        }
        ReleaseCard(si, sj, card_map, pos_i, pos_j, cards, ini_answer);

        initial_pos_i = pos_i;
        initial_pos_j = pos_j;
    }*/

    const int maximum_card_num = 15;
    std::vector<int> score_table(N + 1, INT_MAX), start_i(N + 1, 0), start_j(N + 1, 0);
    std::vector<std::vector<char>> partial_answer(N + 1);
    score_table[0] = 0;
    for (int next_target = 0; next_target < N; next_target++)
    {

        for (int card_num = 1; card_num <= std::min(maximum_card_num, N - next_target); card_num++)
        {
            std::vector<int> sav_pos_i(N), sav_pos_j(N);
            std::vector<std::vector<int>> sav_card_map(H, std::vector<int>(W, -1));
            for (int i = next_target; i < N; i++)
            {
                sav_pos_i[i] = initial_pos_i[i];
                sav_pos_j[i] = initial_pos_j[i];
                sav_card_map[sav_pos_i[i]][sav_pos_j[i]] = i;
            }

            std::vector<std::vector<int>> dp(1 << card_num, std::vector<int>(card_num, INT_MAX));
            std::vector<std::vector<int>> pre(1 << card_num, std::vector<int>(card_num, INT_MAX));
            for (int i = next_target; i < next_target + card_num; i++)
            {
                dp[(1 << (i - next_target))][i - next_target] = CalcDist(start_i[next_target], start_j[next_target], sav_pos_i[i], sav_pos_j[i]);
                pre[(1 << (i - next_target))][i - next_target] = -1;
            }
            for (int S = 1; S < (1 << card_num); S++)
            {
                for (int v = next_target; v < next_target + card_num; v++)
                {
                    if (dp[S][v - next_target] == INT_MAX)
                        continue;
                    for (int nv = next_target; nv < next_target + card_num; nv++)
                    {
                        int new_score = dp[S][v - next_target] + CalcDist(sav_pos_i[v], sav_pos_j[v], sav_pos_i[nv], sav_pos_j[nv]);
                        if (dp[S | (1 << (nv - next_target))][nv - next_target] > new_score)
                        {
                            dp[S | (1 << (nv - next_target))][nv - next_target] = new_score;
                            pre[S | (1 << (nv - next_target))][nv - next_target] = v;
                        }
                    }
                }
            }

            for (int last_v = next_target; last_v < next_target + card_num; last_v++)
            {
                std::vector<int> pos_i = sav_pos_i, pos_j = sav_pos_j;
                std::vector<std::vector<int>> card_map = sav_card_map;

                int crt_v = last_v, crt_S = (1 << card_num) - 1;
                std::vector<int> card_order;
                while (crt_v != -1)
                {
                    card_order.push_back(crt_v);

                    int nxt_v = pre[crt_S][crt_v - next_target];
                    int nxt_S = crt_S ^ (1 << (crt_v - next_target));
                    crt_v = nxt_v, crt_S = nxt_S;
                }
                std::reverse(card_order.begin(), card_order.end());

                // simulation

                std::vector<char> tmp_ans;
                std::stack<int> cards;
                int ci = start_i[next_target], cj = start_j[next_target];
                for (int target : card_order)
                {
                    while (ci != pos_i[target] || cj != pos_j[target])
                    {
                        ProceedStep(ci, cj, pos_i[target], pos_j[target], tmp_ans);
                    }
                    GetCard(target, card_map, pos_i, pos_j, cards, tmp_ans);
                }

                std::vector<int> cycle_i, cycle_j;
                int ni = ci, nj = cj;
                cycle_i.push_back(ni);
                cycle_j.push_back(nj);
                for (int delta = 1; delta <= 2 * H && cycle_i.size() < card_num; delta++)
                {
                    if (delta % 2 == 1)
                    {
                        for (int k = 0; k < delta && cycle_i.size() < card_num; k++)
                        {
                            ni--;
                            if (IsValidPoint(ni, nj) && IsEmptyPoint(ni, nj, card_map))
                            {
                                cycle_i.push_back(ni);
                                cycle_j.push_back(nj);
                            }
                        }
                        for (int k = 0; k < delta && cycle_i.size() < card_num; k++)
                        {
                            nj++;
                            if (IsValidPoint(ni, nj) && IsEmptyPoint(ni, nj, card_map))
                            {
                                cycle_i.push_back(ni);
                                cycle_j.push_back(nj);
                            }
                        }
                    }
                    else
                    {
                        for (int k = 0; k < delta && cycle_i.size() < card_num; k++)
                        {
                            ni++;
                            if (IsValidPoint(ni, nj) && IsEmptyPoint(ni, nj, card_map))
                            {
                                cycle_i.push_back(ni);
                                cycle_j.push_back(nj);
                            }
                        }
                        for (int k = 0; k < delta && cycle_i.size() < card_num; k++)
                        {
                            nj--;
                            if (IsValidPoint(ni, nj) && IsEmptyPoint(ni, nj, card_map))
                            {
                                cycle_i.push_back(ni);
                                cycle_j.push_back(nj);
                            }
                        }
                    }
                }

                assert(cycle_i.size() == card_num);

                for (int i = 0; i < card_num; i++)
                {
                    while (ci != cycle_i[i] || cj != cycle_j[i])
                    {
                        ProceedStep(ci, cj, cycle_i[i], cycle_j[i], tmp_ans);
                    }
                    ReleaseCard(ci, cj, card_map, pos_i, pos_j, cards, tmp_ans);
                }

                for (int target = next_target; target < next_target + card_num; target++)
                {
                    while (ci != pos_i[target] || cj != pos_j[target])
                    {
                        ProceedStep(ci, cj, pos_i[target], pos_j[target], tmp_ans);
                    }
                    GetCard(target, card_map, pos_i, pos_j, cards, tmp_ans);
                }

                int penalty = CalcPenalty(tmp_ans);
                if (score_table[next_target] + penalty < score_table[next_target + card_num])
                {
                    score_table[next_target + card_num] = score_table[next_target] + penalty;
                    partial_answer[next_target + card_num] = MergeAnswer(partial_answer[next_target], tmp_ans);
                    start_i[next_target + card_num] = ci;
                    start_j[next_target + card_num] = cj;
                }
            }
        }
    }

    return partial_answer[N];
}

void OutputAnswer(const std::vector<char> &ans)
{
    for (char c : ans)
    {
        std::cout << c;
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> ini_x, ini_y;
    Input(ini_x, ini_y);
    std::vector<char> answer = Solve(ini_x, ini_y);
    OutputAnswer(answer);
    return 0;
}
