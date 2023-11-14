#include <bits/stdc++.h>

int eps = 1e9;

std::vector<int> Calculate_2b(std::vector<int>& a, int N) {
    int l = a.size();
    std::vector<int> ans(N, eps);
    ans[0] = 0;
    for (int counter = 0; counter < N; counter++) {
        for (int i = 0; i < N; i++) {
            if (ans[i] == counter) {
                for (int j = 1; j <= l; j++) {
                    int clockwise = (i + a[j-1] + N) % N;
                    int counterclockwise = (i - a[j-1] + N) % N;
                    ans[counterclockwise] = std::min(ans[counterclockwise], counter + 1);
                    ans[clockwise] = std::min(ans[clockwise], counter + 1);
                }
            }
        }
    }
    return ans;
}

std::vector<int> Calculate_3b(std::vector<int>& a, int N) {
    int l = a.size();
    std::vector<int> ans(N, eps);
    ans[0] = 0;
    for (int counter = 0; counter < N; counter++) {
        for (int i = 0; i < N; i++) {
            if (ans[i] == counter) {
                for (int j = 1; j <= l; j++) {
                    int counterclockwise = (i - a[j-1] + N) % N;
                    ans[counterclockwise] = std::min(ans[counterclockwise], counter + 1);
                }
            }
        }
    }
    return ans;
}

void change(std::vector<int>& a, int N) {
    int l = a.size();
    for (int i = l; i >= 1; i--) {
        if (a[i - 1] != N - l + i - 1) {
            a[i - 1]++;
            for (int j = i+1; j <= l; j++) {
                a[j - 1] = a[i - 1] + 1;
            }
            break;
        }
    }
}

int maxVisit = 0;

std::pair<std::vector<int>, std::vector<int>> Calculate_4a(int N, int k, int l) {
    std::vector<int> aGenerated(l);
    std::vector<int> aFinalPossible(l);
    std::vector<int> chosenA;
    for (int i = 1; i <= l; i++) {
        aGenerated[i-1] = i;
        aFinalPossible[i-1] = N - l + i - 1;
    }
    int maxVisited = 0;
    std::vector<int> maxValue;
    while (aGenerated != aFinalPossible){
        std::vector<int> ans(N, eps);
        ans[0] = 0;
        for (int counter = 0; counter < k; counter++) {
            for (int i = 0; i < N; i++) {
                if (ans[i] == counter) {
                    for (int j = 1; j <= l; j++) {
                        int clockwise = (i + aGenerated[j-1] + N) % N;
                        int counterclockwise = (i - aGenerated[j-1] + N) % N;
                        ans[counterclockwise] = std::min(ans[counterclockwise], counter + 1);
                        ans[clockwise] = std::min(ans[clockwise], counter + 1);
                    }
                }
            }
        }
        int visited = 0;
        for (int i = 1; i <= N; i++) {
            if (ans[i-1] != eps) {
                visited++;
            }
        }
        if (visited > maxVisited) {
            maxVisited = visited;
            maxValue = ans;
            chosenA = aGenerated;
        }
        change(aGenerated, N);
    }
    maxVisit = maxVisited;
    return std::make_pair(maxValue, chosenA);
}

void solve_4a(int N, int k, int l){
    std::pair<std::vector<int>, std::vector<int>> ans = Calculate_4a(N, k, l);
    std::vector<int> arr = ans.first;
    std::vector<int> chosenA = ans.second;
    std::cout << "The max number of visited sectors: " << maxVisit << std::endl;
    std::cout << "chosen a: ";
    for (int i = 1; i <= chosenA.size(); i++) {
        std::cout << chosenA[i-1] << " ";
    }
    std::cout << std::endl;
    std::cout << "the ans result: ";
    for (int i = 1; i <= arr.size(); i++) {
        if (arr[i-1] == eps) {
            std::cout << "* ";
            continue;
        }
        std::cout << arr[i-1] << " ";
    }
}

void ask_2b(){
    std::cout << "Write the value of N:" << std::endl;
    int N;
    std::cin >> N;
    std::cout << "Write the value of l:" << std::endl;
    int l;
    std::cin >> l;
    std::cout << "Write the values of a_1, a_2, ..., a_l (without commas):" << std::endl;
    std::vector<int> a(l);
    for (int i = 1; i <= l; i += 1) {
        std::cin >> a[i-1];
    }
    std::vector<int> ans = Calculate_2b(a, N);
    std::cout << "The answer is: " << std::endl;
    for (int i = 1; i <= N; i += 1) {
        std::cout << ans[i-1] << " ";
    }
}

void ask_3b(){
    std::cout << "Write the value of N:" << std::endl;
    int N;
    std::cin >> N;
    std::cout << "Write the value of l:" << std::endl;
    int l;
    std::cin >> l;
    std::cout << "Write the values of a_1, a_2, ..., a_l (without commas):" << std::endl;
    std::vector<int> a(l);
    for (int i = 1; i <= l; i += 1) {
        std::cin >> a[i-1];
    }
    std::vector<int> ans = Calculate_3b(a, N);
    std::cout << "The answer is: " << std::endl;
    for (int i = 1; i <= N; i += 1) {
        std::cout << ans[i-1] << " ";
    }
}

void ask_4a(){
    std::cout << "Write the values of N, k, l" << std::endl;
    int N, k, l;
    std::cin >> N >> k >> l;
    solve_4a(N, k, l);
}

void ask_4b(){
    std::cout << "Write the values of N, k" << std::endl;
    int N, k;
    std::cin >> N >> k;
    int l = 1;
    while (true) {
        std::pair<std::vector<int>, std::vector<int>> ans = Calculate_4a(N, k, l);
        if (maxVisit == N) {
            std::cout << "l will be equal: " << l << std::endl;
            std::vector<int> chosenA = ans.second;
            std::cout << "chosen a: ";
            for (int i = 1; i <= chosenA.size(); i++) {
                std::cout << chosenA[i-1] << " ";
            }
            break;
        }
        l++;
    }
}

int main()
{
    std::cout << "What task: " << std::endl;
    std::cout << "if task 2b, write 1" << std::endl;
    std::cout << "if task 3b, write 2" << std::endl;
    std::cout << "if task 4a, write 3" << std::endl;
    std::cout << "if task 4b, write 4" << std::endl;
    int exactTask;
    std::cin >> exactTask;
    if (exactTask == 1) {
        ask_2b();
    }
    else if (exactTask == 2) {
        ask_3b();
    }
    else if (exactTask == 3) {
        ask_4a();
    }
    else if (exactTask == 4) {
        ask_4b();
    }
    return 0;
}
