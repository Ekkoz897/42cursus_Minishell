#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int get_token_length(const char *str, const char *delimiters) {
    int length = 0;
    while (str[length] && !strchr(delimiters, str[length])) {
        length++;
    }
    return length;
}

const char *get_next_token(const char *str, const char *delimiters) {
    while (*str && strchr(delimiters, *str)) {
        str++;
    }
    return *str ? str : NULL;
}

char **split_commands(const char *input, int *cmd_count) {
    int i, count = 0;
    const char *token;
    char **commands;

    // Count the number of commands
    for (i = 0; input[i] != '\0'; i++) {
        if (input[i] == '|') {
            count++;
        }
    }
    count++;

    // Allocate memory for commands array
    commands = (char **)malloc((count + 1) * sizeof(char *));

    // Split input string into commands
    i = 0;
    token = input;
    while (token) {
        int length = get_token_length(token, "|");
        commands[i] = strndup(token, length);
        i++;

        token = get_next_token(token + length, "|");
    }
    commands[i] = NULL;
    *cmd_count = i;

    return commands;
}

void print_arguments(const char *command_str) {
    int arg_num = 1;
    const char *word = get_next_token(command_str, " \t\n");

    while (word) {
        int length = get_token_length(word, " \t\n");
        printf("  Argument %d: %.*s\n", arg_num, length, word);
        word = get_next_token(word + length, " \t\n");
        arg_num++;
    }
}

int main() {
    char *input = "command1 arg1 arg2 | command2 arg3 | grep arg4";
    int cmd_count;
    char **commands = split_commands(input, &cmd_count);

    for (int i = 0; i < cmd_count; i++) {
        printf("Command %d:\n", i + 1);
        print_arguments(commands[i]);
        free(commands[i]);
    }

    free(commands);
    return 0;
}
