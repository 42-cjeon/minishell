CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCS_ROOT = srcs
PARSER_ROOT = $(SRCS_ROOT)/parser
UTILS_ROOT = $(SRCS_ROOT)/utils
SHELL_ROOT = $(SRCS_ROOT)/shell

INCLUDE_ROOT = includes

vpath %.c $(SRCS_ROOT) $(PARSER_ROOT)

PARSER_SRCS := tk_types_escape.c tk_types_operator.c \
	token_container.c tokenizer_helper.c tokenizer_normal.c \
	tokenizer_pair.c tokenize.c exp_types.c expander_helper.c \
	expander_split.c expand.c lexer.c parser.c
PARSER_SRCS := $(addprefix $(PARSER_ROOT)/, $(PARSER_SRCS))

UTILS_SRCS := ft_string.c
UTILS_SRCS := $(addprefix $(UTILS_ROOT)/, $(UTILS_SRCS))

SHELL_SRCS := shell.c
SHELL_SRCS := $(addprefix $(SHELL_ROOT)/, $(SHELL_SRCS))

MAIN_SRCS := minishell.c
MAIN_SRCS := $(addprefix $(SRCS_ROOT)/, $(MAIN_SRCS))

SRCS = $(PARSER_SRCS) $(MAIN_SRCS) $(SHELL_SRCS)
OBJS = $(SRCS:.c=.o)

# -- 나중에 지우기 -- #
TEST_SRCS := minishell.c
TEST_SRCS := $(addprefix $(SRCS_ROOT)/test/, $(TEST_SRCS))
TSRCS = $(PARSER_SRCS) $(TEST_SRCS)
TOBJS = $(TSRCS:.c=.o)
# --            -- #

LIBFT_ROOT = $(SRCS_ROOT)/libft
LIBFT = $(LIBFT_ROOT)/libft.a

LIBRL_ROOT = $(SRCS_ROOT)/readline
LIBRL_INCLUDE_ROOT = $(SRCS_ROOT)
LIBRL = $(LIBRL_ROOT)/libreadline.a
LIBRL_HISTORY = $(LIBRL_ROOT)/libhistory.a

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(LIBRL) $(LIBRL_HISTORY)
	$(CC) $(CFLAGS) -lncurses -o $@ $^

%.o : %.c
	$(CC) -I$(INCLUDE_ROOT) -I$(LIBRL_INCLUDE_ROOT) -c $(CFLAGS) -o $@ $<

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_ROOT) INCLUDE_ROOT=$(realpath $(INCLUDE_ROOT)) all

$(LIBRL) :
	@$(MAKE) -C $(LIBRL_ROOT) install-static

# -- 나중에 지우기 -- #
test : $(TOBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^
# --            -- #

clean :
	@$(MAKE) -C $(LIBFT_ROOT) clean
	@$(MAKE) -C $(LIBRL_ROOT) clean
	rm -f $(OBJS)
# -- 나중에 지우기 -- #
	rm -f $(TOBJS)
	rm -f test
# --           -- #

fclean : clean
	@$(MAKE) -C $(LIBFT_ROOT) fclean
	@$(MAKE) -C $(LIBRL_ROOT) clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re