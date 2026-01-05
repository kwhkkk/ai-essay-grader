#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
const char* keywordSet[8] = {"else","end","if","read","repeat","then","until","write" };
static struct
{
	const char* str;
	const char* value;
} reservedWords[11] = {{"%","MOD"},{"/","DIVIDE"},{";","SEMI"},{"<","LT"},{"=","EQ"},{">","GT"},{"\(","LPAREN"},{"\)","RPAREN"},{"\*","TIMES"},{"\+","PLUS"},{"^","CARET"} };
static struct
{
	const char* op;
	const int code;
} keywordLexCode[8] = {{"else",3},{"end",4},{"if",1},{"read",7},{"repeat",5},{"then",2},{"until",6},{"write",8} };
static struct
{
	const char* op;
	const int code;
} opLexCode[11] = {{"%",204},{"/",202},{";",208},{"<",205},{"=",207},{">",206},{"\(",209},{"\)",210},{"\*",201},{"\+",200},{"^",203} };
void concat(char str[], char tmp) {
	size_t len = strlen(str);

	str[len] = tmp;

	str[len + 1] = '\0';
}

bool findKeyWord(const char* str) {
	int i = 0;
	for (i = 0; i < 8; i++) {
		if (strcmp(str,keywordSet[i]) == 0) {
			return true;
		}
	}
	return false;
}

const char* getValue(const char* str) {
	int i = 0;
	for (i = 0; i < 11; ++i) {
		if (strcmp(reservedWords[i].str, str) == 0) {
			return reservedWords[i].value;
		}
	}
	return NULL;
}
//判断是否是数字
bool is_Digit(char ch) {
	if(ch >= '0' && ch <= '9') return true;
	else return false;
}

//判断是否是字母
bool is_Alpha(char ch){
	if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))return true;
	else return false;
}

void coding(FILE* input_fp,FILE* output_fp) {
	char tmp = fgetc(input_fp);
	if (tmp == ' ' || tmp == '\n' || tmp == '\t'){
		return;
	}
	ungetc(tmp, input_fp);
	int state = 0;
	bool flag = false;
	bool isIdentifier = false;
	bool isDigit = false;
	bool isAnnotation = false;
	char value[1024];
	value[0] = '\0';
	while (!flag) {
		tmp = fgetc(input_fp);
		switch (state) {
		case 0: {
			if(is_Digit(tmp)) {
				isDigit = true;state = 1; break;
			}
			else if(is_Alpha(tmp)){
				isIdentifier = true;state = 4; break;
			}
			switch (tmp) {
			case '+':state = 3; break;
			case '(':state = 3; break;
			case ')':state = 3; break;
			case '*':state = 3; break;
			case '%':state = 3; break;
			case '/':state = 3; break;
			case ';':state = 3; break;
			case '<':state = 3; break;
			case '=':state = 3; break;
			case '>':state = 3; break;
			case '^':state = 3; break;
			case 'e':state = 2; break;
			case 'i':state = 8; break;
			case 'r':state = 7; break;
			case 't':state = 9; break;
			case 'u':state = 11; break;
			case 'w':state = 15; break;
			case '{':state = 19; break;
			}
			break;
		}
		case 1: {
			if(is_Digit(tmp)) {
				isDigit = true;state = 1; break;
			}
			switch (tmp) {
			}
			break;
		}
		case 2: {
			switch (tmp) {
			case 'l':state = 21; break;
			case 'n':state = 6; break;
			}
			break;
		}
		case 3: {
			switch (tmp) {
			}
			break;
		}
		case 4: {
			if(is_Digit(tmp)) {
				isDigit = true;state = 4; break;
			}
			else if(is_Alpha(tmp)){
				isIdentifier = true;state = 4; break;
			}
			switch (tmp) {
			}
			break;
		}
		case 5: {
			switch (tmp) {
			case 'a':state = 6; break;
			case 'p':state = 20; break;
			}
			break;
		}
		case 6: {
			switch (tmp) {
			case 'd':state = 3; break;
			}
			break;
		}
		case 7: {
			switch (tmp) {
			case 'e':state = 5; break;
			}
			break;
		}
		case 8: {
			switch (tmp) {
			case 'f':state = 3; break;
			}
			break;
		}
		case 9: {
			switch (tmp) {
			case 'h':state = 13; break;
			}
			break;
		}
		case 10: {
			switch (tmp) {
			case 'i':state = 23; break;
			}
			break;
		}
		case 11: {
			switch (tmp) {
			case 'n':state = 22; break;
			}
			break;
		}
		case 12: {
			switch (tmp) {
			case 'a':state = 24; break;
			}
			break;
		}
		case 13: {
			switch (tmp) {
			case 'e':state = 18; break;
			}
			break;
		}
		case 14: {
			switch (tmp) {
			case 'l':state = 3; break;
			}
			break;
		}
		case 15: {
			switch (tmp) {
			case 'r':state = 10; break;
			}
			break;
		}
		case 16: {
			switch (tmp) {
			case 'i':state = 14; break;
			}
			break;
		}
		case 17: {
			switch (tmp) {
			case 'e':state = 3; break;
			}
			break;
		}
		case 18: {
			switch (tmp) {
			case 'n':state = 3; break;
			}
			break;
		}
		case 19: {
			switch (tmp) {
			case '}':state = 3; break;
			default:state = 19; isAnnotation = true; break;
			}
			break;
		}
		case 20: {
			switch (tmp) {
			case 'e':state = 12; break;
			}
			break;
		}
		case 21: {
			switch (tmp) {
			case 's':state = 17; break;
			}
			break;
		}
		case 22: {
			switch (tmp) {
			case 't':state = 16; break;
			}
			break;
		}
		case 23: {
			switch (tmp) {
			case 't':state = 17; break;
			}
			break;
		}
		case 24: {
			switch (tmp) {
			case 't':state = 3; break;
			}
			break;
		}
		}
		concat(value, tmp);
		if (state ==1) {
			tmp = fgetc(input_fp);
			if(is_Digit(tmp)){} 
			else switch (tmp) {
			default: {
				flag=true;
			}
			}
			ungetc(tmp, input_fp);
		}
		else if (state ==3) {
			tmp = fgetc(input_fp);
			switch (tmp) {
			default: {
				flag=true;
			}
			}
			ungetc(tmp, input_fp);
		}
		else if (state ==4) {
			tmp = fgetc(input_fp);
			if(is_Digit(tmp)){} 
			else if(is_Alpha(tmp)){} 
			else switch (tmp) {
			default: {
				flag=true;
			}
			}
			ungetc(tmp, input_fp);
		}
	}
	if (findKeyWord(value)) {
		int i;		for(i=0;i<8;i++){
			if(strcmp(value, keywordLexCode[i].op) == 0) {				fprintf(output_fp, "%d:%s \n", keywordLexCode[i].code, value);
				printf("%d:%s \n", keywordLexCode[i].code, value);
				return;}
		}
	}
	if (isIdentifier) {
		fprintf(output_fp, "101:%s \n", value);
		printf("101:%s \n", value);
	return;
	}
	if (isDigit) {
		fprintf(output_fp, "100:%s \n", value);
		printf("100:%s \n", value);
		return;
	}
	if (!isAnnotation) {
		int i;		for(i=0;i<11;i++){
			if(strcmp(value,  opLexCode[i].op) == 0) {				fprintf(output_fp, "%d:%s \n", opLexCode[i].code, value);
				printf("%d:%s \n",opLexCode[i].code, value);
				return;}
		}
	}
};
int main(int argc, char* argv[]) {
	FILE* input_fp;fopen_s(&input_fp,"C:/scnuwcnm/sample.tny", "r");
	if (input_fp == NULL) {
		printf("Failed to open input file");
		return 1;
	}
	FILE* output_fp;fopen_s(&output_fp,"C:/scnuwcnm/sample.lex", "w");
	if (output_fp == NULL) {
		printf("Failed to open output file");
		fclose(input_fp);
		return 1;
	}
	char c;
	while ((c=fgetc(input_fp)) != EOF) {
		ungetc(c, input_fp);
		coding(input_fp, output_fp);
	}
	fprintf(output_fp, "EOF:EOF");
	printf("EOF:EOF");
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}