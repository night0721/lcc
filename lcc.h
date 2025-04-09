#ifndef LCC_H_H
#define LCC_H_H

#define MAX_EXTENSIONS 10

typedef struct {
    const char *name;
    const char *extensions[MAX_EXTENSIONS];
    const char *block_comment_start;
    const char *block_comment_end;
    const char *line_comment;
} language;

language languages[] = {
    {"Ada", {".adb", ".ads"}, NULL, NULL, "--"},
    {"Assembly", {".s"}, "/*", "*/", "#"},
    {"C", {".c"}, "/*", "*/", "//"},
    {"C++", {".cc", ".cpp", ".hh", ".hpp"}, "/*", "*/", "//"},
    {"Clojure", {".clj", ".edn"}, NULL, NULL, ";"},
    {"COBOL", {".cbl"}, NULL, NULL, "*>"},
    {"CSS", {".css"}, "/*", "*/", NULL},
    {"D", {".d"}, "/*", "*/", "//"},
    {"Emacs Lisp", {".el"}, NULL, NULL, ";;"},
    {"Erlang", {".erl", ".hrl"}, NULL, NULL, "%"},
    {"Fortran", {".f77", ".f95"}, NULL, NULL, "!"},
    {"Go", {".go"}, "/*", "*/", "//"},
    {"Haskell", {".hs", ".lhs"}, "{-", "-}", "--",},
    {"C Header", {".h"}, "/*", "*/", "//"},
    {"HTML", {".htm", ".html"}, "<!--", "-->", NULL},
    {"Java", {".java"}, "/*", "*/", "//"},
    {"JavaScript", {".js"}, "/*", "*/", "//"},
    {"Julia", {".jl"}, NULL, NULL, "#"},
    {"LaTeX", {".tex", ".sty"}, NULL, NULL, "%"},
    {"Kotlin", {".kt"}, "/*", "*/", "//"},
    {"Lisp", {".lsp", ".lisp"}, NULL, NULL, ";"},
    {"Lua", {".lua"}, "--[[", "]]", "--"},
    {"Makefile", {"Makefile",".mk"}, NULL, NULL, "#"},
    {"Objective-C", {".m"}, "/*", "*/", "//"},
    {"OCaml", {".ml"}, "(*", "*)", NULL},
    {"Pascal", {".pas"}, "{", "}", NULL},
    {"Perl", {".pl", ".pm", ".pp"}, NULL, NULL, "#"},
    {"PHP", {".php"}, "/*", "*/", "//"},
    {"Python", {".py"}, "\"\"\"", "\"\"\"", "#"},
    {"R", {".r", ".R"}, NULL, NULL, "#"},
    {"Ruby", {".rb", ".rbw"}, NULL, NULL, "#"},
    {"Scala", {".scala"}, "/*", "*/", "//"},
    {"Scheme", {".scm"}, NULL, NULL, ";"},
    {"Shell", {".sh", ".bash"}, NULL, NULL, "#"},
    {"SQL", {".sql"}, "/*", "*/", "--"},
    {"TypeScript", {".ts",".tsx"}, "/*", "*/", "//"},
	{"Typst", {".typ"}, "/*", "*/", "//"},
    {"Vimscript", {".vim"}, NULL, NULL, "\""},
};

char *ignore_dir[IGNORE_DIRS] = {"env", "ref", "coslinux", "Zig", "pdfs", NULL};

#endif
