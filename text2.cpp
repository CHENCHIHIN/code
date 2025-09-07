#include <stdio.h>

int main() {
    struct {
        char key[20];
        char value[20];
    } 
    pairs[] = {
        {"Robot", "RL"},
        {"sdf", "vdv"},
        {"sad", "dfdsv"},
        {"eff", "vsad"}
    };
    for (int i = 0; i < 4; i++) {
        printf("%s:%s\n", pairs[i].key, pairs[i].value);
    }

    return 0;
}