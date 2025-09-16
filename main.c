#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 式の入力を受け取る関数
int input(char** buffer, size_t* size);

int main(void) {
    // 変数の初期化
    size_t input_size = 0;
    char* formula_ptr = NULL;

    // 入力を受け取る
    if ( input(&formula_ptr, &input_size) == -1 ) {
        printf("入力が読み取れませんでした。\n");
    }

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