# ==============================================================================
#                               PROJECT CONFIG
# ==============================================================================
NAME	= philo 

# ============== DIRECTORIES & LIBRARIES =======================================
SRC_DIR			= src
INC_DIR			= include
OBJ_DIR			= obj
TEST_DIR		= test

# ============== SUB-DIRECTORIES ===============================================

# ============== FILES =========================================================
SRCS_FILES		= context.c fork.c master.c philo.c utils.c action.c

SRCS 			= $(addprefix $(SRC_DIR)/, $(SRCS_FILES))

OBJS_FILES		= $(SRCS_FILES:%.c=%.o)

OBJS			= $(addprefix $(OBJ_DIR)/, $(OBJS_FILES))

TESTS_FILES		= init_test.c

TESTS			= $(addprefix $(TEST_DIR)/, $(TESTS_FILES))

TEST_EXECS		= $(TESTS:%.c=%.out)

# ============== COMPILATION ===================================================
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
IFLAGS		= -I$(INC_DIR)
LFLAGS		=
CUT_DIR		= $(TEST_DIR)/cut
CUT_INC_DIR	= $(CUT_DIR)/include
CUT			= $(CUT_DIR)/libcut.a

# ============== COMMANDS & FLAGS ==============================================
AR				= ar
ARFLAGS			= -r -c -s
NORMINETTE		= @norminette
RM 				= rm
RMFLAGS 		= -r -f
MKDIR			= @mkdir
MKDIRFLAGS		= -p
VALGRIND		= valgrind
VALGRIND_FLAGS	= --leak-check=full --show-leak-kinds=all --track-fds=yes \
				  --track-origins=yes --trace-children=yes

# ==============================================================================
#                                 RULES
# ==============================================================================

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(MKDIRFLAGS) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# ============== CLEAN =========================================================

clean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)

fclean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all

# ============== DEBUG & ANALYSIS ==============================================

leaks: $(NAME)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME)

leaks_supp: $(NAME)
	$(VALGRIND) $(VALGRIND_FLAGS) --suppressions=supp.supp ./$(NAME)

sanitize: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address" all

thread: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=thread" all

# ============== NORMINETTE ====================================================

checknorm:
	$(NORMINETTE) $(INC_DIR)
	$(NORMINETTE) $(SRC_DIR)
	
# ============== TESTS =========================================================
$(CUT):
	$(MAKE) -C $(CUT_DIR) --no-print-directory

%.out: %.c $(CUT) $(OBJS)
	$(AR) $(ARFLAGS) libphilo.a $(OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(IFLAGS) -I$(CUT_INC_DIR) -L$(CUT_DIR) -L. -lcut -lphilo 

test: $(TEST_EXECS)
	@for test in $(TEST_EXECS) ; do \
		./$$test ; \
	done

test_leaks: $(CUT) $(TEST_EXECS)
	@for test in $(TEST_EXECS) ; do \
		$(VALGRIND) $(VALGRIND_FLAGS) ./$$test ; \
	done

fclean_test:
	$(RM) $(RMFLAGS) $(TEST_EXECS)
	$(MAKE) -C $(CUT_DIR) fclean --no-print-directory

.PHONY: all clean fclean re leaks leaks_supp sanitize thread checknorm test \
	test_leaks fclean_test \
