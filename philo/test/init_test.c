#include "context.h"
#include "fork.h"
#include "master.h"
#include "philo.h"
#include "cut.h"

# define CONTEXT_ARGS_SIZE 4
# define MASTER_ARGS_SIZE 5

static void	init_context_test(void);

static void	init_fork_test(void);

static void	init_master_test(void);

static void	init_philo_test(void);

int	main(void)
{
	init_context_test();
	init_fork_test();
	init_master_test();
	init_philo_test();
	return (0);
}

static void	init_context_test(void)
{
	t_unit_test	*unit_test;
	t_context	context;
	int			rc;
	const char	*str_args[CONTEXT_ARGS_SIZE] = {"140", "100", "20", "3"};
	const int	int_args[CONTEXT_ARGS_SIZE] = {140, 100, 20, 3};

	unit_test = new_unit_test("init_context", false);
	rc = init_context(&context, CONTEXT_ARGS_SIZE - 1, (char **) str_args);
	cut_assert(rc == 0, unit_test, "returns 0 for valid arguments "
		"without meal_target");
	cut_expect(context.time_to_die == int_args[0], unit_test,
		"converts time_to_die argument to its numeric counterpart");
	cut_expect(context.time_to_eat == int_args[1], unit_test,
		"converts time_to_eat argument to its numeric counterpart");
	cut_expect(context.time_to_sleep == int_args[2], unit_test,
		"converts time_to_sleep argument to its numeric counterpart");
	cut_expect(context.meal_target == -1, unit_test,
		"sets meal_target to -1 when no meal_target argument is given");
	clear_context(&context);
	rc = init_context(&context, CONTEXT_ARGS_SIZE, (char **) str_args);
	cut_assert(rc == 0, unit_test, "returns 0 for valid arguments "
		"with meal_target");
	cut_expect(context.meal_target == int_args[3], unit_test,
		"sets meal_target argument to its numeric counterpart");
	clear_context(&context);
	rc = init_context(&context, CONTEXT_ARGS_SIZE, (char *[]) {"1", "2", "3", "-1"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given a negative integer as argument");
	rc = init_context(&context, CONTEXT_ARGS_SIZE, (char *[]) {"1", "2", "0", "4"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given a zero as argument");
	rc = init_context(&context, CONTEXT_ARGS_SIZE, (char *[]) {"1", "2147483648", "3", "4"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given an overflowing integer as argument");
	rc = init_context(&context, CONTEXT_ARGS_SIZE, (char *[]) {"one", "2", "3", "4"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given a non-numeric argument");
	rc = init_context(&context, CONTEXT_ARGS_SIZE - 2, (char *[]) {"1", "2"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given less than expected number of arguments");
	rc = init_context(&context, CONTEXT_ARGS_SIZE + 1, (char *[]) {"1", "2", "3", "4", "5"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given more than expected number of arguments");
	end_unit_test(unit_test);
}

static void	init_fork_test(void)
{
	t_unit_test	*unit_test;
	t_fork		fork;
	int			rc;

	unit_test = new_unit_test("init_fork", false);
	rc = init_fork(&fork);
	cut_assert(rc == 0, unit_test, "returns 0 on success");
	clear_fork(&fork);
	end_unit_test(unit_test);
}

static void	init_master_test(void)
{
	t_unit_test	*unit_test;
	t_master	master;
	int			rc;
	const char	*str_args[MASTER_ARGS_SIZE] = {"2", "140", "100", "20", "3"};
	const int	int_args[MASTER_ARGS_SIZE] = {2, 140, 100, 20, 3};

	unit_test = new_unit_test("init_master", false);
	rc = init_master(&master, MASTER_ARGS_SIZE - 1, (char **) str_args);
	cut_assert(rc == 0, unit_test,
		"returns 0 for valid arguments without meal_target argument");
	cut_expect((int) master.philos_size == int_args[0], unit_test,
		"converts number_of_philosophers argument to its numeric counterpart");
	clear_master(&master);
	rc = init_master(&master, MASTER_ARGS_SIZE, (char **) str_args);
	cut_assert(rc == 0, unit_test,
		"returns 0 for valid arguments with meal_target argument");
	clear_master(&master);
	rc = init_master(&master, MASTER_ARGS_SIZE, (char *[]) {"-1", "2", "3", "4", "5"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given a negative integer as first argument");
	rc = init_master(&master, MASTER_ARGS_SIZE, (char *[]) {"0", "2", "3", "4", "5"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given a zero as first argument");
	rc = init_master(&master, MASTER_ARGS_SIZE, (char *[]) {"2147483648", "2", "3", "4", "5"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given an overflowing integer as first argument");
	rc = init_master(&master, MASTER_ARGS_SIZE, (char *[]) {"one", "2", "3", "4", "5"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given a non-numeric first argument");
	rc = init_master(&master, MASTER_ARGS_SIZE - 2, (char *[]) {"1", "2", "3"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given less than expected number of arguments");
	rc = init_master(&master, MASTER_ARGS_SIZE + 1, (char *[]) {"1", "2", "3", "4", "5", "6"});
	cut_expect(rc != 0, unit_test,
		"returns non-zero value when given more than expected number of arguments");
	end_unit_test(unit_test);
}

static void	init_philo_test(void)
{
	t_unit_test		*unit_test;
	t_master		master;
	t_philo			philo;
	int				rc;
	unsigned int	number;

	unit_test = new_unit_test("init_philo", false);
	number = 1;
	rc = init_philo(&philo, number, &master);
	cut_assert(rc == 0, unit_test,
		"returns 0 for valid arguments");
	cut_expect(philo.state == IS_THINKING, unit_test,
		"sets philo's initial state to thinking");
	cut_expect(philo.number == number, unit_test,
		"sets philo's number to number argument");
	cut_expect(philo.last_meal == master.context.start, unit_test,
		"sets philo's last meal to context's starting time");
	cut_expect(philo.meal_count == 0, unit_test,
		"sets philo's meal count to 0");
	cut_expect(philo.forks[0] == master.forks + (number - 1), unit_test,
		"sets philo's left fork to corresponding master fork");
	cut_expect(philo.forks[1] == master.forks + (number), unit_test,
		"sets philo's right fork to corresponding master fork");
	cut_expect(philo.context == &master.context, unit_test,
		"sets philo's context to master's context");
	clear_philo(&philo);
	rc = init_philo(&philo, -1, &master);
	cut_expect(rc != 0, unit_test,
		"returns non-zero value for negative philo number");
	rc = init_philo(&philo, 0, &master);
	cut_expect(rc != 0, unit_test,
		"returns non-zero value for non-positive philo number");
	rc = init_philo(&philo, number, NULL);
	cut_expect(rc != 0, unit_test,
		"returns non-zero value for null master argument");
}
