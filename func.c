#include <stdio.h>

int ub(int a) {
        return *(&a+100);
}

int main(int argc, char** argv) {
	int i;
	if(scanf("%d", &i)) {
		printf("%d\n", ub(i));
	}
	return 0;
}
