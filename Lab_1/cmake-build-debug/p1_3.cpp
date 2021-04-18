#include <cstdio>
#include <vector>

int main() {
    int soldiers, startIndex, step;
    scanf("%d%d%d", &step, &soldiers, &startIndex);

    std::vector<int> squad;
    for(int i = 1; i <= soldiers; i++) squad.push_back(i);

    int currentIndex = startIndex - 1;
    do{
        currentIndex = (currentIndex + step - 1) % squad.size();
        printf (" --- CURRENT INDEX: %d \n", currentIndex);
        printf (" --- AM ELIMINAT %d \n", *(squad.begin() + currentIndex));
        squad.erase(squad.begin() + currentIndex);
        printf (" --- A RAMAS PE POZITIE %d \n", *(squad.begin() + currentIndex));
        if(currentIndex == squad.size()) currentIndex = 0;
    } while(squad.size() > 1);

    printf("%d", squad[0]);
    return 0;
}