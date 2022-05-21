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
		calculate(input,len);
		//value_list(input, len);
		printf("%s\n", input);
	}
	 Descartes<char> dc = Descartes<char>();
	 dc.add_elems('a','e');
	 dc.add_elems('b', 'a');
	 dc.add_elems('c', 'd');
	 Descartes<char> d = Descartes<char>();
	 d.add_elems('a', 'b');
	 d.add_elems('a', 'e');
	 d.add_elems('c', 'd');
	 Descartes<char> sum = Descartes<char>();
	 sum = d + dc;
	 printf("size:%d", sum.get_size());
	 return 0;
	char a[] = {'1','2','3','4','5',};
}