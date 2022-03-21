#define NEGATIVE '!'
#define AND '&'
#define OR '|'
#define CONDITION '>'
#define DOUBLE_CONDITION '~'
#define XOR '^'
#define TRUE 't'
#define FALSE 'f'
#define SPACE ' ' 
void operation(int len, char input[]);
int  recursive_computation(char* exp, int len);
void delect_space(char* expression, int* len);
int not_formatted(char* context, int len);