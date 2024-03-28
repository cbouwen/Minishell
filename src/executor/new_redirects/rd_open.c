/*header pls*/

#include "../../../inc/minishell.h"

/* The plan is to create 2 loops
 * 1st loop will iterate throught the output array and open the files
 * Either in append or create mode, based on if there is a a_ at the start of the string
 * 2nd loop will iterate through the input array and execute the heredoc function
 * Except for the last element, all other elements can be ingnored.
 * 
 * Order of business:
 * 1. Open the files									--DONE
 * 2. Execute the heredoc								--DONE
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
	temp = NULL;
	while (i < rd->output_size)
	{
		if (rd->output[i][0] == '#')
		{
			temp = ft_strdup(rd->output[i] + 1);
			if (!temp)
				return (rd_error_handler(12, NULL, rd));
			free(rd->output[i]);
			rd->output[i] = temp;
			rd->o_fd = open(rd->output[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		}
		else
			rd->o_fd = open(rd->output[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (rd->o_fd < 0)
			return (rd_error_handler(2, rd->output[i], rd));
		if (i < rd->output_size - 1)
			close(rd->o_fd);
		i++;
	}
	return (rd_error_handler(0, NULL, rd));
}

int	open_input(t_rd_collection *rd)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (i < rd->input_size)
	{
		if (rd->input[i][0] == '#')
		{
			temp = ft_strdup(rd->input[i] + 1);
			if (!temp)
				return (rd_error_handler(12, NULL, rd));
			free(rd->input[i]);
			rd->input[i] = temp;
			rd->i_fd = open_heredoc(rd->input[i]);
		}
		else
			rd->i_fd = open(rd->input[i], O_RDONLY, 0644);
		if (rd->i_fd < 0)
			return (rd_error_handler(2, rd->input[i], rd));
		if (i < rd->input_size - 1)
			close(rd->i_fd);
		i++;
	}
	return (rd_error_handler(0, NULL, rd));
}

int	open_heredoc(char *input)
{
	int		heredoc_fd;
	char	*line;

	heredoc_fd = open("/tmp/heredoc_dump", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
		return (rd_error_handler(2, "/tmp/heredoc_dump", NULL));
	line = readline("heredoc> ");
	while (ft_strcmp(line, input) != 0)
	{
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
		line = NULL;
		line = readline("heredoc> ");
	}
	if (line)
		free(line);
	return (heredoc_fd);
}

//rd->i_fd = open(rd->input[i], O_RDWR | O_CREAT | O_APPEND, 0644);
