# ==============================================================================
#                               PROJECT CONFIG
# ==============================================================================
NAME		= philo 

# ============== COLORS ========================================================
RESET		= \033[0m
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
CYAN		= \033[0;36m
WHITE		= \033[0;37m
BOLD		= \033[1m

# ============== DIRECTORIES & LIBRARIES =======================================
SRC_DIR			= src
INC_DIR			= include
OBJ_DIR			= obj
TEST_DIR		= test

# ============== SUB-DIRECTORIES ===============================================

# ============== FILES =========================================================
SRCS_FILES		=

SRCS 			= $(addprefix $(SRC_DIR)/, $(SRCS_FILES))

OBJS			= $(SRCS:%.c=$(OBJ_DIR)/%.o)

TESTS_FILES		=

TESTS			= $(addprefix $(TEST_DIR)/, $(TESTS_FILES))

TEST_EXECS		= $(TESTS:%.c=%.out)

# ============== COMPILATION ===================================================
CC			= @cc
CFLAGS		= -Wall -Wextra -Werror
IFLAGS		= -I$(INC_DIR)
LFLAGS		=
CUT_DIR		= $(TEST_DIR)/cut
CUT_INC_DIR	= $(CUT_DIR)/include
CUT			= $(CUT_DIR)/libcut.a

# ============== COMMANDS & FLAGS ==============================================
NORMINETTE		= @norminette
RM 				= @rm
RMFLAGS 		= -r -f
MKDIR			= @mkdir
MKDIRFLAGS		= -p
PRINTF			= @printf
GREP			= @grep
GREPFLAGS		= -r -n --color=always
FIND			= @find
VALGRIND		= valgrind
VALGRIND_FLAGS	= --leak-check=full --show-leak-kinds=all --track-fds=yes \
				  --track-origins=yes --trace-childrens=yes

# ==============================================================================
#                                 RULES
# ==============================================================================

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) $(LFLAGS) -o $(NAME)
	$(PRINTF) "\n$(WHITE)=====================================\n$(RESET)"
	$(PRINTF) "	   $(BOLD)$(GREEN)BUILD COMPLETE$(RESET)\n"
	$(PRINTF) "$(WHITE)=====================================$(RESET)\n\n"

$(OBJ_DIR)/%.o: %.c
	$(MKDIR) $(MKDIRFLAGS) $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	$(PRINTF) "$(CYAN)  Compiling: $(RESET)$<\n"

# ============== CLEAN =========================================================

clean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)
	$(PRINTF) "\n$(WHITE)=====================================\n$(RESET)"
	$(PRINTF) "	   $(BOLD)$(YELLOW)CLEAN COMPLETE$(RESET)\n"
	$(PRINTF) "$(WHITE)=====================================$(RESET)\n\n"

fclean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)
	$(RM) $(RMFLAGS) $(NAME)
	$(PRINTF) "\n$(WHITE)=====================================\n$(RESET)"
	$(PRINTF) "	   $(BOLD)$(YELLOW)FCLEAN COMPLETE$(RESET)\n"
	$(PRINTF) "$(WHITE)=====================================$(RESET)\n\n"

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
	$(PRINTF) "\n$(CYAN)=====================================\n$(RESET)"
	$(PRINTF) "	   $(BOLD)CHECK NORM INCLUDES$(RESET)\n"
	$(PRINTF) "$(CYAN)=====================================$(RESET)\n\n"
	$(NORMINETTE) $(INC_DIR)
	$(PRINTF) "\n$(CYAN)=====================================\n$(RESET)"
	$(PRINTF) "	   $(BOLD)CHECK NORM SRCS$(RESET)\n"
	$(PRINTF) "$(CYAN)=====================================$(RESET)\n\n"
	$(NORMINETTE) $(SRC)
	
# ============== TESTS =========================================================
$(CUT):
	$(MAKE) -C $(CUT_DIR) --no-print-directory

$(TEST_DIR)/%.out: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -L $(CUT_DIR) -l cut -c $< -o $@
	$(PRINTF) "$(CYAN)  Compiling: $(RESET)$<\n"

test: $(CUT) $(TESTS)
	$(PRINTF) "\n$(CYAN)=====================================\n$(RESET)"
	$(PRINTF) "	   $(BOLD)$(NAME)TESTS (normal mode)$(RESET)\n"
	$(PRINTF) "$(CYAN)=====================================$(RESET)\n\n"
	for test in $(TEST_EXECS) ; do \
		./$$test ; \
	done

test_leaks:
	$(PRINTF) "\n$(CYAN)=====================================\n$(RESET)"
	$(PRINTF) "	   $(BOLD)$(NAME)TESTS (leaks mode)$(RESET)\n"
	$(PRINTF) "$(CYAN)=====================================$(RESET)\n\n"
	for test in $(TEST_EXECS) ; do \
		$(VALGRIND) $(VALGRIND_FLAGS) ./$$test ; \
	done

fclean_test:
	$(RM) $(RMFLAGS) $(TEST_EXECS)
	$(PRINTF) "\n$(WHITE)=====================================\n$(RESET)"
	$(PRINTF) "	   $(BOLD)$(YELLOW)FCLEAN TEST COMPLETE$(RESET)\n"
	$(PRINTF) "$(WHITE)=====================================$(RESET)\n\n"

.PHONY: all clean fclean re leaks leaks_supp sanitize thread checknorm test \
	test_leaks fclean_test \
