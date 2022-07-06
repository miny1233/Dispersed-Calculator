#include<stdio.h>
#include<malloc.h>
#include<memory.h>
#include<string.h>
#include "dispersed.h"
#include "des.cpp"
//#include"power_set.h"
//#include"power_set.cpp"


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
		//calculate(input,len);
		value_list(input, len);
		printf("%s\n", input);
	}
	
}