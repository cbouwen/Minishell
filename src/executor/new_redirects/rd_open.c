/*header pls*/

#include "../../../inc/minishell.h"

/* The plan is to create 2 loops
 * 1st loop will iterate throught the output array and open the files
 * Either in append or create mode, based on if there is a a_ at the start of the string
 * 2nd loop will iterate through the input array and execute the heredoc function
 * Except for the last element, all other elements can be ingnored.
 * 
 * Order of business:
 * 1. Open the files
 * 2. Execute the heredoc
 * 3. execute the command
 * 4. pipe output of command to either stdin or file
 * 5. close the files
 * 6. free the arrays
 * 7. return
*/

int	open_output(t_rd_collection *rd)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < rd->output_size)
	{
		if (rd->output[i][0] == '#')
		{
			temp = ft_strdup(rd->output[i] + 1);
			if (!temp)
				return (12);
			free(rd->output[i]);
			rd->output[i] = temp;
			rd->o_fd = open(rd->output[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		}
		else
			rd->o_fd = open(rd->output[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (rd->o_fd < 0)
			return (2);
		if (i < rd->output_size - 1)
			close(rd->output_fd);
		i++;
	}
	return (0);
}
