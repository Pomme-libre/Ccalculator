#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// 式の入力を受け取る関数
int input(char** buffer, size_t* size);

// トークン分割関数
int tokenize(char* formula);

// メイン関数
int main(void) {
    // ローカル変数の初期化
    size_t input_size = 0;
    char* formula_ptr = NULL;

    // 入力を受け取る
    if ( input(&formula_ptr, &input_size) == -1 ) {
        printf("入力が読み取れませんでした。\n");
    }

    // トークンを分割
    tokenize(formula_ptr);

    // 結果の出力
    printf("結果: %s\n", formula_ptr);

    // メモリの開放
    free(formula_ptr);
    return 0;
}


// 式の入力を受け取る関数
int input(char** buffer, size_t* size) {
    // 変数の初期化
    size_t len = 0;
    int token;

    // バッファの確保
    if ( *buffer == NULL ) {
        *size = 30;
        *buffer = (char*)malloc(*size);
        if (*buffer == NULL) return -1;
    }

    printf("計算したい式を入力してください。\n");
    printf("> ");

    // ループで位置文字ずつ全体の式を取得 (Ctrl + D = EOF)
    while ( (token = getchar()) != '\n' && token != EOF ) {
        if ( len + 1 >= *size ) {
            *size += 30;
            char* tmp = (char*)realloc(*buffer, *size);
            if (tmp == NULL) return -1;
            *buffer = tmp;
        }
        // 入力を取得
        (*buffer)[len] = token;
        len++;
    }

    // EOF(Ctrl + D)なら終了
    if ( token == EOF ) return -1;

    // 終端文字を追加
    (*buffer)[len] = '\0';
    return 0;
}


// トークン分割関数
int tokenize(char* formula) {
    // ローカル変数の初期化
    size_t index = 0;
    char min_token;
    const size_t digit_size = 256; 
    char digit_tokens[digit_size * sizeof(int)];

    // トークン分割
    // ヌル終端文字までトークンを分割
    while (formula[index] != '\0') {
        // 変数の初期化
        int digit_num = 0;
        int counter = 0;

        // トークン分割開始
        if ( isspace(formula[index]) ) {
            // 空白行は無視
            index++;
        }else if ( isdigit(formula[index]) ) {
            // 数字をcharからintへ変換
            while ( isdigit(formula[index]) ) {
                digit_tokens[counter] = formula[index];
                index++;
                counter++;
            }
            for (int i = 0; i < counter; i++) {
                digit_num += (int)(( digit_tokens[i] - '0' ) * (int)pow(10.0, (double)(counter - i - 1)));
            }
            printf("数字: %d\n", digit_num);
        }else if ( formula[index] == '+' || formula[index] == '-' || formula[index] == '*' || formula[index] == '/' ) {
            // 演算子を出力
            min_token = formula[index];
            printf("記号: %c\n", min_token);
            index++;
        }else {
            // 上記以外無視
            index++;
        }
    }
    return 0;
}