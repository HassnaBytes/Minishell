# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houattou <houattou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 12:13:42 by sait-bah          #+#    #+#              #
#    Updated: 2023/08/15 02:03:48 by sait-bah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = minishell

PARSSING = ./src/parssing/get_commands.c ./src/parssing/get_commands_comp.c

EXECUTION = ./src/execution/get_path_env.c  ./src/execution/execute_cmd.c \
		    ./src/execution/handle_heredoc.c \
			./src/execution/is_builtins.c \
			./src/execution/execute_multipe_cmd.c ./src/execution/handle_redirection.c\
			./src/execution/prepare_cmd.c ./src/execution/execution.c \
			./src/execution/find_path.c ./src/execution/handle_signals.c \
			./src/execution/parent_procees.c ./src/execution/check_type_of_redirection.c \
			./src/execution/utls_heredoc.c\


BUILTIN = ./src/builtin/cd_cmd.c ./src/builtin/echo_cmd.c ./src/builtin/env_cmd.c \
		  ./src/builtin/exit_cmd.c ./src/builtin/export_.c ./src/builtin/pwd_cmd.c \
		  ./src/builtin/unset_cmd.c ./src/builtin/utls.c ./src/builtin/utls2.c \
		  ./src/builtin/utls3.c

ERR = ./errors/check_user_input.c ./errors/print_err.c ./errors/check_1d_err.c ./errors/check_1d_err_comp.c

PARSING_TOOLS = ./src/parssing/tools/checks.c ./src/parssing/tools/counters.c ./src/parssing/tools/tools.c \
./src/parssing/tools/print_err.c ./src/parssing/tools/ft_split_pipe.c ./src/parssing/tools/tools_com.c \
./src/parssing/tools/expand.c ./src/parssing/tools/redir.c \
./src/parssing/tools/handle_quotes.c ./src/parssing/tools/fix_expand.c ./src/parssing/tools/norm_help.c \
./src/parssing/tools/expand_comp.c ./src/parssing/tools/expand_comp_two.c ./src/parssing/tools/redir_cmp.c \
./src/parssing/tools/redir_cmp_two.c ./src/parssing/tools/tools_three.c

CC = cc

LIBFT = ./libft/libft.a


CFLAGS = -Wall -Wextra -Werror

ROUTE = ./main.c

ROUTE_OBJS = ${ROUTE:.c=.o}

EXECUTION_OBJS = ${EXECUTION:.c=.o}

BUILTIN_OBJS = ${BUILTIN:.c=.o}

PARSSING_OBJS = ${PARSSING:.c=.o}

ERR_OBJS = ${ERR:.c=.o}

TOOLS_OBJS = ${PARSING_TOOLS:.c=.o}

READLINE =  $(shell brew --prefix readline)

RM = rm -f

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${ROUTE_OBJS} ${PARSSING_OBJS} ${EXECUTION_OBJS} ${ERR_OBJS} ${TOOLS_OBJS} ${BUILTIN_OBJS}
	make all -C ./libft
	${CC} ${CFLAGS} -I $(READLINE)/include/readline ${ROUTE_OBJS} -lreadline ${EXECUTION_OBJS} -L $(READLINE)/lib ${PARSSING_OBJS} ${ERR_OBJS} ${BUILTIN_OBJS} ${TOOLS_OBJS}  ${LIBFT} -o ${NAME}

clean:
	make clean -C ./libft
	${RM} ${ROUTE_OBJS}
	${RM} ${PARSSING_OBJS}
	${RM} ${EXECUTION_OBJS}
	${RM} ${ERR_OBJS}
	${RM} ${TOOLS_OBJS}
	${RM} ${BUILTIN_OBJS}

fclean: clean
	make fclean -C ./libft
	${RM} ${NAME}

re: fclean all
