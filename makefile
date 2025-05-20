NAME    := cub3D
CC      := cc
CFLAGS  := -Iincludes -std=c99
SRCDIR  := src
INCDIR  := includes

SRCS    := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/draw_utils/*.c) $(wildcard $(SRCDIR)/ray_casting/*.c) \
			$(wildcard $(SRCDIR)/parser/*.c)
OBJS    := $(SRCS:.c=.o)

MLXDIR  := minilibx-linux
MLXLIB  := $(MLXDIR)/libmlx.a
MLXFLAG := -L$(MLXDIR) -lmlx

LIBFTDIR := libft
LIBFTLIB := $(LIBFTDIR)/libft.a
LIBFTFLAG:= -L$(LIBFTDIR) -lft

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    MLXFLAG += -framework OpenGL -framework AppKit
else
    MLXFLAG += -lXext -lX11
endif

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
