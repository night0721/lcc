#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#include "lcc.h"

#define BUFFER_SIZE 8192
#define NUM_LANGS sizeof(languages) / sizeof(language)

typedef struct {
    const char *name;
    int files;
    int lines;
    int blanks;
    int comments;
} lang_stats;

lang_stats stats[NUM_LANGS] = {0};
lang_stats total_stats = {0};

void count_lines(const char *filename, language *lang, lang_stats *stat)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen");
        return;
    }

    char buffer[BUFFER_SIZE];
    int in_comment = 0;

    while (fgets(buffer, BUFFER_SIZE, file)) {
        stat->lines++;
        total_stats.lines++;
        char *line = buffer;
        while (isspace(*line)) line++; /* Skip leading whitespace */

        if (*line == '\0') {
            stat->blanks++;
            total_stats.blanks++;
            continue;
        }

        if (in_comment) {
            char *end = strstr(line, lang->block_comment_end);
            if (end) {
                in_comment = 0;
                line = end + strlen(lang->block_comment_end);
                stat->comments++;
                total_stats.comments++;
            } else {
                stat->comments++;
                total_stats.comments++;
                continue;
            }
        }

        if (lang->line_comment && strncmp(line, lang->line_comment, strlen(lang->line_comment)) == 0) {
            stat->comments++;
            total_stats.comments++;
        } else if (lang->block_comment_start && strstr(line, lang->block_comment_start) != NULL) {
            char *start = strstr(line, lang->block_comment_start);
            char *end = strstr(start + strlen(lang->block_comment_start), lang->block_comment_end);
            if (end) {
                stat->comments++;
                total_stats.comments++;
                line = end + strlen(lang->block_comment_end);
            } else {
                in_comment = 1;
                stat->comments++;
                total_stats.comments++;
            }
        }
    }

    fclose(file);
}

void process_directory(const char *dirname)
{
    struct dirent *entry;
    DIR *dp = opendir(dirname);
    if (!dp) {
        perror("opendir");
        return;
    }

    char path[PATH_MAX];
    struct stat info;

    while ((entry = readdir(dp))) {
        if (entry->d_name[0] == '.') continue;  /* Skip hidden files and directories */
        
        int skip = 0;
        /* not count ignore folders */
        for (int i = 0; i < IGNORE_DIRS; i++) {
            if (strstr(entry->d_name, ignore_dir[i]) != NULL) {
                skip = 1;
                continue;
            }
        }
        if (skip) continue;

        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);
        if (stat(path, &info) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(info.st_mode)) {
            process_directory(path);
        } else {
            for (size_t i = 0; i < NUM_LANGS; i++) {
                for (int j = 0; languages[i].extensions[j] != NULL; j++) {
                    char *ext = strstr(entry->d_name, ".");
                    if (strcmp(ext ? ext : entry->d_name, languages[i].extensions[j]) == 0) {
                        stats[i].files++;
                        total_stats.files++;
                        count_lines(path, &languages[i], &stats[i]);
                        break;
                    }
                }
            }
        }
    }

    closedir(dp);
}

int compare_stats(const void *a, const void *b) {
    lang_stats *a_stats = (lang_stats *) a;
    lang_stats *b_stats = (lang_stats *) b;
    int a_code_lines = a_stats->lines - a_stats->blanks - a_stats->comments;
    int b_code_lines = b_stats->lines - b_stats->blanks - b_stats->comments;

    return b_code_lines - a_code_lines;
}

int main(int argc, char **argv)
{
    for (size_t i = 0; i < NUM_LANGS; i++) {
        stats[i].name = languages[i].name;
    }

    if (argc < 2) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd");
            return 1;
        }
        process_directory(cwd);
    } else {
        for (int i = 1; i < argc; i++) {
            process_directory(argv[i]);
        }
    }

    qsort(stats, NUM_LANGS, sizeof(lang_stats), compare_stats);

    printf("%-10s %-6s %-6s %-8s %-6s %-6s\n", "Language", "Files", "Code", "Comment", "Blank", "Total");
    printf("%-10s %-6d %-6d %-8d %-6d %-6d\n", "Total", total_stats.files, total_stats.lines - total_stats.comments - total_stats.blanks, total_stats.comments, total_stats.blanks, total_stats.lines);
    for (size_t i = 0; i < NUM_LANGS; i++) {
        if (stats[i].files > 0) {
            int code_lines = stats[i].lines - stats[i].blanks - stats[i].comments;
            printf("%-10s %-6d %-6d %-8d %-6d %-6d\n", stats[i].name, stats[i].files, code_lines, stats[i].comments, stats[i].blanks, stats[i].lines);
        }
    }

    return 0;
}
