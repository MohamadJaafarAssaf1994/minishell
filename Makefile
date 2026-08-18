NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CPPFLAGS = -I. -Ilibft -Ilibft/getNextLine -Ilibft/libftprintf
LDLIBS = -lreadline

MANDATORY_SRCS = \
				builtin/builtin_cd.c \
				builtin/builtin_echo.c \
				builtin/builtin_env.c \
				builtin/builtin_exit.c \
				builtin/builtin_export_env.c \
				builtin/builtin_export.c \
				builtin/builtin_pwd.c \
				builtin/builtin_unset.c \
				builtin/builtin_utils.c \
				builtin/builtin.c \
				builtin/parent_builtin_redirs.c \
				exec/exec_utils_1.c \
				exec/exec_utils_2.c \
				parsing/tmp_parse.c \
				parsing/copy_env.c \
				parsing/expansion.c \
				parsing/expansion_utils.c \
				parsing/expansion_len.c \
				parsing/expansion_copy.c \
				parsing/expansion_heredoc.c \
				parsing/tmp_parse_suite.c \
				parsing/shell_loop.c \
				parsing/shell_parse.c \
				parsing/tokenizer.c \
				parsing/tokenizer_utils.c \
				redir/pipeline.c \
				redir/pipeline2.c \
				redir/pipeline_script.c \
				redir/heredoc.c \
				redir/heredoc2.c \
				redir/redirections.c \
				utils/signals.c \
				utils/utils.c \
				utils/print.c \
				src/main.c


OBJS_SRCS = $(MANDATORY_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS_SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SRCS) $(LIBFT) $(LDLIBS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c header/minishell.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS_SRCS)
	rm -f $(NAME)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
