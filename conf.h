/* neatvi configuration file */

/* access mode of new files */
#define MKFILE_MODE	0600

/* map file names to file types */
static struct filetype {
	char *ft;		/* file type */
	char *pat;		/* file name pattern */
} filetypes[] = {
	{"c", "\\.[hc]$"},				/* C */
	{"roff", "\\.(ms|me|mom|tr|roff|tmac|txt|[1-9])$"},	/* troff */
	{"tex", "\\.tex$"},				/* tex */
	{"msg", "letter$|mbox$|mail$"},			/* email */
	{"mk", "Makefile$|makefile$|\\.mk$"},		/* makefile */
	{"sh", "\\.sh$"},				/* shell script */
	{"py", "\\.py$"},				/* python */
	{"bib", "bib$"},				/* refer */
	{"nm", "\\.nm$"},				/* neatmail */
	{"diff", "\\.(patch|diff)$"},			/* diff */
	{"rust", "\\.rs$"},				/* rust */
	{"st", "\\.st$"}				/* smalltalk */
};

#define HL_TYPE 5
#define HL_KEYWORD 4
#define HL_COMMENT 2
#define HL_STRING 4
#define HL_FUNCTION 6
#define HL_NUMBER 1
#define HL_MISC 3

/* syntax highlighting patterns */
static struct highlight {
	char *ft;		/* the filetype of this pattern */
	int att[16];		/* attributes of the matched groups */
	char *pat;		/* regular expression */
	int end;		/* the group ending this pattern */
} highlights[] = {
	{"c", {HL_TYPE}, "\\<(signed|unsigned|char|short|int|long|float|double|void|struct|enum|union|typedef)\\>"},
	{"c", {HL_TYPE}, "\\<(static|extern|register)\\>"},
	{"c", {HL_TYPE}, "[a-zA-Z][a-zA-Z0-9_]*_t"},
	{"c", {HL_KEYWORD}, "\\<(return|for|while|if|else|do|sizeof|goto|switch|case|default|break|continue)\\>"},
	{"c", {HL_COMMENT}, "//.*$"},
	{"c", {HL_COMMENT}, "(/\\*[^*/]*)|([^\"/*]*\\*/)"},
	{"c", {HL_COMMENT}, "(^[[:blank:]]\\*[^*/]*)"}, /* hack for multiline comments */
	{"c", {HL_MISC}, "^#[ \t]*[a-zA-Z0-9_]+"},
	{"c", {HL_FUNCTION}, "([a-zA-Z][a-zA-Z0-9_]+)\\(", 1},
	{"c", {HL_STRING}, "\"(\\\\\"|[^\"])*\""},
	{"c", {HL_STRING}, "'(\\\\'|[^'])*'"},
	{"c", {HL_NUMBER}, "[-+]?\\<(0[xX][0-9a-fA-F]+|[0-9]+)\\>"},

	{"roff", {4, 0, 5, 4, 5, 4},
		"^[.'][ \t]*((SH.*)|(de) (.*)|([^ \t\\]{2,}))?.*$", 1},
	{"roff", {2}, "\\\\\".*$"},
	{"roff", {3}, "\\\\{1,2}[*$fgkmns]([^[(]|\\(..|\\[[^]]*\\])"},
	{"roff", {3}, "\\\\([^[(*$fgkmns]|\\(..|\\[[^]]*\\])"},
	{"roff", {3}, "\\$[^$]+\\$"},

	{"tex", {4, 0, 3, 0, 5},
		"\\\\[^[{ \t]+(\\[([^]]+)\\])?(\\{([^}]*)\\})?"},
	{"tex", {3}, "\\$[^$]+\\$"},
	{"tex", {2}, "%.*$"},

	/* mail */
	{"msg", {6}, "^From .*20..$"},
	{"msg", {6, 4}, "^Subject: (.*)$"},
	{"msg", {6, 2}, "^From: (.*)$"},
	{"msg", {6, 5}, "^To: (.*)$"},
	{"msg", {6, 5}, "^Cc: (.*)$"},
	{"msg", {6}, "^[A-Z][-A-Za-z]+: .+$"},
	{"msg", {2}, "^> .*$"},

	/* makefile */
	{"mk", {0, 3}, "([A-Za-z_][A-Za-z0-9_]*)[ \t]*="},
	{"mk", {3}, "\\$\\([a-zA-Z0-9_]+\\)"},
	{"mk", {2}, "#.*$"},
	{"mk", {0}, "([A-Za-z_%.]+):"},

	/* shell script */
	{"sh", {5}, "\\<(break|case|continue|do|done|elif|else|esac|fi|for|if|in|then|until|while|return)\\>"},
	{"sh", {4}, "\"([^\"\\]|\\\\.)*\""},
	{"sh", {4}, "'[^']*'"},
	{"sh", {3}, "`([^`\\]|\\\\.)*`"},
	{"sh", {1}, "\\$(\\{[^}]+\\}|[a-zA-Z_0-9]+|[!#$?*@-])"},
	{"sh", {0}, "^([a-zA-Z_][a-zA-Z_0-9]* *\\(\\)) *\\{"},
	{"sh", {SYN_BD}, "^\\. .*$"},
	{"sh", {2}, "#.*$"},

	{"bib", {0, 8, SYN_BGMK(11)}, "^(%L) +(.*)$", 1},
	{"bib", {0, 8, 12}, "^(%A) (.*)$", 1},
	{"bib", {0, 8, 5}, "^(%T) (.*)$", 1},
	{"bib", {0, 8, 2}, "^(%[JB]) (.*)$", 1},
	{"bib", {0, 8, 5}, "^(%D) (.*)$", 1},
	{"bib", {0, 8, 7}, "^(%O) (.*)$", 1},
	{"bib", {0, 8, 8}, "^(%[A-Z]) (.*)$", 1},
	{"bib", {25}, "^#.*$", 1},

	/* python */
	{"py", {2}, "#.*$"},
	{"py", {5}, "\\<(class|def)\\>"},
	{"py", {5}, "\\<(and|or|not|is|in)\\>"},
	{"py", {5}, "\\<(import|from|global|lambda|del)\\>"},
	{"py", {5}, "\\<(for|while|if|elif|else|pass|return|break|continue)\\>"},
	{"py", {5}, "\\<(try|except|as|raise|finally|with)\\>"},
	{"py", {0, 0}, "([a-zA-Z][a-zA-Z0-9_]+)\\(", 1},
	{"py", {4}, "[\"']([^\"']|\\\\\")*[\"']"},

	/* neatmail */
	{"nm", {0 | SYN_BGMK(15), 6, 12, 5, 8},
		"^([ROU])([0-9]+)\t([^\t]*)\t([^\t]*)"},
	{"nm", {0 | SYN_BGMK(6)}, "^[N].*$"},
	{"nm", {0 | SYN_BGMK(13)}, "^[A-Z][HT].*$"},
	{"nm", {0 | SYN_BGMK(11)}, "^[A-Z][MI].*$"},
	{"nm", {7 | SYN_BGMK(15)}, "^[A-Z][LJ].*$"},
	{"nm", {0 | SYN_BGMK(7)}, "^[F].*$"},
	{"nm", {7}, "^\t.*$"},
	{"nm", {SYN_BD}, "^:.*$"},

	/* diff */
	{"diff", {1}, "^-.*$"},
	{"diff", {2}, "^\\+.*$"},
	{"diff", {6}, "^@.*$"},
	{"diff", {SYN_BD}, "^diff .*$"},

	/* status bar */
	{"---", {8, 4, 1}, "^(\".*\").*(\\[[wr]\\]).*$"},
	{"---", {8, 4, 4}, "^(\".*\").*(L[0-9]+) +(C[0-9]+).*$"},
	{"---", {8}, "^.*$"},

        /* rust */
	{"rust", {HL_TYPE}, "\\<(i|u|f)(8|16|32|64|128|size)\\>"},
	{"rust", {HL_TYPE}, "(->|:) (&[a-zA-Z']* |[a-zA-Z&])[a-zA-Z0-9_: ]*"},
	{"rust", {HL_TYPE}, "<[a-zA-Z&'][a-zA-Z0-9_:, '+]*>"},
	{"rust", {HL_KEYWORD}, "\\<(ref|const|impl|self|pub|struct|enum|as|move|static|super|trait|type|unsafe|where|async|await|dyn|use|crate|let|fn|return|for|in|while|loop|if|else|match|break|continue|mut|macro_rules)\\>"},
	{"rust", {HL_COMMENT}, "//.*$"},
	{"rust", {HL_FUNCTION}, "([a-zA-Z][a-zA-Z0-9_]+)\\(", 1},
	{"rust", {HL_FUNCTION}, " (==|!=|<|>|%|-=|+=|=>|<=|>=) "},
	{"rust", {HL_STRING}, "\"(\\\\\"|[^\"])*\""},
	{"rust", {HL_STRING}, "b?'(\\\\'|[^'])*'"},
	{"rust", {HL_NUMBER}, "[-+]?\\<(0[xbo][0-9a-fA-F_]+|[0-9_]+)\\>"},

	/* smalltalk */
	{"st", {HL_TYPE}, "\\|.*\\|"},
	{"st", {HL_TYPE}, "(^| )[A-Z][a-zA-Z0-9]*"},
	{"st", {HL_FUNCTION}, "\\<(do|whileTrue|whileFalse|ifTrue|ifFalse|put|to|at|add|new|for|super|subclass|class|init|category)\\>:?"},
	{"st", {HL_FUNCTION}, " (:=|>>) "},
	{"st", {HL_FUNCTION}, "\\^"},
	{"st", {HL_COMMENT}, "\"[^\"]*\""},
	{"st", {HL_MISC}, "#([a-zA-Z_][a-zA-Z0-9_]*|'[^']*')"},
	{"st", {HL_STRING}, "'[^']*'"},
	{"st", {HL_STRING}, "\\$.?"},
	{"st", {HL_NUMBER}, "[-+]?\\<([0-9]+r[0-9a-fA-F]+|[0-9]+)\\>"}
};

/* how to hightlight current line (hll option) */
#define SYN_LINE	(SYN_BGMK(11))

/* how to hightlight text in the reverse direction */
#define SYN_REVDIR	(SYN_BGMK(7))

/* define it as "\33[8l" to disable BiDi in vte-based terminals */
#define LNPREF		""

/* right-to-left characters (used only in dircontexts[] and dirmarks[]) */
#define CR2L		"ءآأؤإئابةتثجحخدذرزسشصضطظعغـفقكلمنهوىييپچژکگی‌‍؛،»«؟ًٌٍَُِّْ"
/* neutral characters (used only in dircontexts[] and dirmarks[]) */
#define CNEUT		"-!\"#$%&'()*+,./:;<=>?@^_`{|}~ "

/* direction context patterns; specifies the direction of a whole line */
static struct dircontext {
	int dir;
	char *pat;
} dircontexts[] = {
	{-1, "^[" CR2L "]"},
	{+1, "^[a-zA-Z_0-9]"},
};

/* direction marks; the direction of a few words in a line */
static struct dirmark {
	int ctx;	/* the direction context for this mark; 0 means any */
	int dir;	/* the direction of the matched text */
	int grp;	/* the nested subgroup; 0 means no groups */
	char *pat;
} dirmarks[] = {
	{+0, +1, 1, "\\\\\\*\\[([^]]+)\\]"},
	{+1, -1, 0, "[" CR2L "][" CNEUT CR2L "]*[" CR2L "]"},
	{-1, +1, 0, "[a-zA-Z0-9_][^" CR2L "\\\\`$']*[a-zA-Z0-9_]"},
	{+0, +1, 0, "\\$([^$]+)\\$"},
	{+0, +1, 1, "\\\\[a-zA-Z0-9_]+\\{([^}]+)\\}"},
	{-1, +1, 0, "\\\\[^ \t" CR2L "]+"},
};

/* character placeholders */
static struct placeholder {
	char *s;	/* the source character */
	char *d;	/* the placeholder */
	int wid;	/* the width of the placeholder */
} placeholders[] = {
	{"‌", "-", 1},
	{"‍", "-", 1},
};
