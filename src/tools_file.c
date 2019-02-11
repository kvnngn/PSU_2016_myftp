/*
** tool_file.c for  in /home/kevin/rendu/PSU_2016_myftp/src
** 
** Made by kevin
** Login   <kevin3.nguyen@epitech.eu>
** 
** Started on  Sun May 21 13:22:53 2017 kevin
** Last update Sun May 21 13:30:11 2017 kevin
*/

#include			"my_ftp.h"

char				*get_filename(char *buffer)
{
  int				i;
  char				*filename;

  i = 0;
  if ((filename = malloc(sizeof(char) * (strlen(buffer) + 1))) == NULL)
    return (NULL);
  while (buffer[i] != '\n' && buffer[i] != '\0')
    {
      filename[i] = buffer[i];
      i++;
    }
  filename[i] = 0;
  return (filename);
}

char				*check_path(char *path)
{
  DIR*				dir;
  int				len;

  len = strlen(path);
  if (path[len] != '/')
    path = strcat(path, "/");
  dir = opendir(path);
  if (dir)
    closedir(dir);
  else if (ENOENT == errno)
    return (NULL);
  return (path);
}

char				*get_content(char *buffer)
{
  int				i;
  int				j;
  char				*content;

  i = 0;
  j = 0;
  if ((content = malloc(sizeof(char) * (strlen(buffer) + 1))) == NULL)
    return (NULL);
  while (buffer[i] != '\n' && buffer[i] != '\0')
    i++;
  i++;
  if (buffer[i - 1] == '\n')
    {
      while (buffer[i] != '\0')
	{
	  content[j] = buffer[i];
	  j++;
	  i++;
	}
      content[j] = 0;
    }
  return (content);
}
