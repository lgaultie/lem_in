// Header 42

#include <lem_in.h>

int	fill_reserved(t_farm *farm)
{
	t_paths	*tmp_paths;
	t_rooms	*tmp_rooms;
	int		i;

	tmp_paths = farm->paths;
	tmp_rooms = farm->rooms;
	while (tmp_paths->next)
		tmp_paths = tmp_paths->next;
	while (tmp_rooms)
	{
		i = 0;
		while (i < tmp_paths->length)
		{
			if (tmp_rooms->room_id == tmp_paths->path[i] \
				&& tmp_rooms->start_end != 1 && tmp_rooms->start_end != 2)
			{
				printf("reserve room %d\n", tmp_rooms->room_id);
				tmp_rooms->reserved = 1;
			}
			i++;
		}
		tmp_rooms->visited = 0;
		tmp_rooms = tmp_rooms->next;
	}
	return (SUCCESS);
}