#include<stdio.h>
#include<malloc.h>
#include<memory.h>
#include<string.h>
#include "dispersed.h"

int main() {
	char input[64];
	int len;
	while (true) {
		printf(">");
		scanf("%s", input);
		len = strlen(input);
		if (not_formatted(input, len)) {
			printf("公式不合法\n");
			continue;
		}
		while (len != 1)
		{
			recursive_computation(input, len);
			len = strlen(input);
		}
		//value_list(input, len);
		printf("%s\n", input);
	}
	return 0;
}