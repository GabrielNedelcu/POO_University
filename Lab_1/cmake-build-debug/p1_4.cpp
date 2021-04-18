#include <cstdio>
#include <cstring>
#include <cctype>

bool isValidWord(char * word, char alpha, char beta) {
    return tolower(word[0]) == alpha &&
           tolower(word[strlen(word)-1]) == beta;
}

int main() {
    char alpha, beta;
    int m, n;
    scanf("%c %c %d %d", &alpha, &beta, &m, &n);
    alpha = tolower(alpha);
    beta = tolower(beta);

    //printf(" --- ALPHA & BETA: %c & %c", alpha, beta);

    char word[4000];
    int small, medium, large;
    small = 0;
    medium = 0;
    large = 0;
    while(scanf("%s", word) != EOF) {
        if(isValidWord(word, alpha, beta)) {
            if(strlen(word) < m) small++;
            else if(strlen(word) < n && strlen(word) >= m) medium++;
            else large++;
        }
    }
    printf("%d %d %d", small, medium, large);
    return 0;
}