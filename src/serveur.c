/*
** server.c for server in /home/kevin/rendu/PSU_2016_myftp/src
** 
** Made by kevin
** Login   <kevin3.nguyen@epitech.eu>
** 
** Started on  Tue May  9 14:21:07 2017 kevin
** Last update Sun May 21 22:41:51 2017 kevin
*/

#include		"my_ftp.h"

void			init_tab(t_pointeur *tab)
{
  tab[0].func = "HELP";
  tab[0].ptr = &help_cmd;
  tab[1].func = "CWD";
  tab[1].ptr = &cwd_cmd;
  tab[2].func = "PASV";
  tab[2].ptr = &pasv_cmd;
  tab[3].func = "RETR";
  tab[3].ptr = &retr_cmd;
  tab[4].func = "USER";
  tab[4].ptr = &user_cmd;
  tab[5].func = "PWD";
  tab[5].ptr = &pwd_cmd;
  tab[6].func = "DELE";
  tab[6].ptr = &dele_cmd;
  tab[7].func = "PASS";
  tab[7].ptr = &pass_cmd;
  tab[8].func = "QUIT";
  tab[8].ptr = &quit_cmd;
  tab[9].func = "STOR";
  tab[9].ptr = &stor_cmd;
  tab[10].func = "NOOP";
  tab[10].ptr = &noop_cmd;
}

int			init_serveur(t_serveur *_serveur, int port, char *path)
{
  _serveur->id = socket(AF_INET, SOCK_STREAM, 0);
  _serveur->config.sin_family = AF_INET;
  _serveur->config.sin_addr.s_addr = htonl(INADDR_ANY);
  _serveur->config.sin_port = htons(port);
  _serveur->port = port;
  _serveur->pid = 0;
  _serveur->status = 0;
  _serveur->path = path;
  _serveur->filename = NULL;
  _serveur->client_id = 0;
  _serveur->cmd = NULL;
  _serveur->len = sizeof(struct sockaddr);
  bind(_serveur->id, (struct sockaddr *)&_serveur->config,
       sizeof(struct sockaddr_in));
  return (0);
}

void			execute(t_serveur *_serveur, t_pointeur *tab)
{
  int			j;

  j = 0;
  if (_serveur->cmd != NULL)
    {
      while (j < 11)
	{
	  if (strcmp(_serveur->cmd[0], tab[j].func) == 0)
	    {
	      tab[j].ptr(_serveur);
	      return;
	    }
	  j = j + 1;
	}
    }
  if (_serveur->status == 2)
    my_putstr(_serveur->client_id, "500 Unknown command.");
  else
    my_putstr(_serveur->client_id, "530 Please login with USER and PASS.");
}

int			run(t_serveur *_serveur, t_pointeur *tab)
{
  while (1)
    {
      if ((_serveur->client_id =
	   accept(_serveur->id, (struct sockaddr *)&_serveur->client_id,
		  &_serveur->len)) == -1)
	return (-1);
      else
	my_putstr(_serveur->client_id, "220 Service ready for new user");
      _serveur->pid = fork();
      if (_serveur->pid == 0)
	{
	  _serveur->server_ip = inet_ntoa(_serveur->client_config.sin_addr);
	  while (1)
	    {
	      _serveur->buf = get_next_line(_serveur->client_id);
	      _serveur->cmd = my_str_to_wordtab(_serveur->buf);
	      execute(_serveur, tab);
	    }
	  close(_serveur->client_id);
	}
      else
	close(_serveur->client_id);
    }
  return (0);
}

int			main(int ac, char **av)
{
  t_serveur		_serveur;
  int		        ret;
  t_pointeur		*tab;

  if (ac == 3 && atoi(av[1]) > 0)
    {
      if (check_path(av[2]) == NULL)
	{
	  my_putstr(1, "[ERROR] Invalid Path");
	  return (-1);
	}
      if ((init_serveur(&_serveur, atoi(av[1]), av[2])) == -1)
	return (-1);
      if ((tab = malloc(sizeof(t_pointeur) * 11)) == NULL)
	return (-1);
      init_tab(tab);
      if ((ret = listen(_serveur.id, 6)) == -1)
	return (-1);
      if (run(&_serveur, tab) == -1)
	return (-1);
    }
  else
    printf("Usage : ./server port path\n");
  return (0);
}
