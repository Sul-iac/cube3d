NAME    := cub3D
CC      := cc
CFLAGS  := -Iincludes
SRCDIR  := src
INCDIR  := includes

SRCS    := $(wildcard $(SRCDIR)/*.c)
OBJS    := $(SRCS:.c=.o)

MLXDIR  := minilibx-linux
MLXLIB  := $(MLXDIR)/libmlx_Linux.a
MLXFLAG := -L$(MLXDIR) -lmlx_Linux -lXext -lX11

LIBFTDIR := libft
LIBFTLIB := $(LIBFTDIR)/libft.a
LIBFTFLAG:= -L$(LIBFTDIR) -lft

SYSLIBS := -lm

GREEN := \033[0;32m
RESET := \033[0m
SPIN  := '/-\|'

all: $(NAME)

$(NAME): $(MLXLIB) $(LIBFTLIB) $(OBJS)
	@printf "$(GREEN)[Link]\t$@$(RESET)\n"
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAG) $(LIBFTFLAG) $(SYSLIBS) -o $@

%.o: %.c
	@printf "$(GREEN)[Comp]\t$<$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

define spin
	@i=0 ; \
	printf "$(GREEN)[$(1)]\tbuilding... $(RESET)"; \
	while [ $$i -lt 8 ]; do \
		printf "\b$$(echo $(SPIN) | cut -c$$(( ($$i%4)+1 )) )"; \
		sleep 0.05 ; \
		i=$$((i+1)); \
	done ; \
	printf "\b \n"
endef

$(MLXLIB):
	$(call spin,mlx)
	@$(MAKE) -C $(MLXDIR) >/dev/null

$(LIBFTLIB):
	$(call spin,libft)
	@$(MAKE) -C $(LIBFTDIR) >/dev/null

clean:
	@$(MAKE) -C $(MLXDIR) clean
	@$(MAKE) -C $(LIBFTDIR) clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
