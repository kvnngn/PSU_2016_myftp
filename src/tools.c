/*
** get_next_line.c for get_next_line in /home/nguye_z/rendu/CPE_2015_getnextline
** 
** Made by nguyen kevin
** Login   <nguye_z@epitech.net>
** 
** Started on  Fri Jan 15 10:22:15 2016 nguyen kevin
** Last update Sun May 21 13:13:50 2017 kevin
*/

#include			"my_ftp.h"

void				my_putstr(int fd, char *str)
{
  write(fd, str, strlen(str));
  write(fd, "\r\n", 2);
}

char				*my_itoa(int nb)
{
  int				len;
  char				*str;
  int				tmp;

  tmp = nb;
  len = 0;
  while (tmp > 0)
    {
      tmp /= 10;
      len++;
    }
  str = malloc(sizeof(*str) * (len + 1));
  str[len] = '\0';
  while (len--)
    {
      str[len] = nb % 10  + '0';
      nb /= 10;
    }
  return (str);
}

char				**my_str_to_wordtab(char *str)
{
  char				**tab;
  char				*save;
  int				i;

  tab = NULL;
  save = strtok(str, " \r\n");
  i = 0;
  while (save)
    {
      tab = realloc(tab, sizeof(char *) * ++i);
      tab[i - 1] = save;
      save = strtok(NULL, " \r\n");
    }
  if (i == 0)
    return (NULL);
  tab = realloc(tab, sizeof(char *) * (i + 1));
  tab[i] = NULL;
  return (tab);
}

char				*my_realloc(char *old, int size)
{
  int				i;
  char				*new;
  int				len;

  i = 0;
  len = strlen(old) + 1;
  if ((new = malloc(len + size + 1)) == NULL)
    return (NULL);
  while (old[i])
    {
      new[i] = old[i];
      i++;
    }
  new[i] = '\0';
  free(old);
  return (new);
}

char				*get_next_line(const int fd)
{
  char				buff;
  int				 i;
  int				 rd;
  char				*line;

  i = 0;
  if ((line = malloc(sizeof(char) + 2)) == NULL)
    return (NULL);
  if ((rd = read(fd, &buff, 1)) <= 0)
    return (NULL);
  while (buff != '\n')
    {
      line[i] = buff;
      line[i + 1] = '\0';
      line = my_realloc(line, 1);
      read(fd, &buff, 1);
      i++;
    }
  line[i] = '\0';
  return (line);
}

