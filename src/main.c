#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (parse_args(argc, argv, &data) != 0)
		return (1);
	if (init_data(&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	if (start_simulation(&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}
