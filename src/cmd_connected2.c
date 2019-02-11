/*
** server.c for server in /home/kevin/rendu/PSU_2016_myftp/src
** 
** Made by kevin
** Login   <kevin3.nguyen@epitech.eu>
** 
** Started on  Tue May  9 14:21:07 2017 kevin
** Last update Sun May 21 15:15:37 2017 kevin
*/

#include	        "my_ftp.h"

void			pwd_cmd(t_serveur *_serveur)
{
  char			*tmp;

  if (_serveur->status == 2)
    {
      if (!(tmp = malloc(sizeof(char) * (strlen("257 \"")
					 + strlen(_serveur->path) + 1))))
	return;
      tmp = strcat(tmp, "257 \"");
      tmp = strcat(tmp, _serveur->path);
      tmp = strcat(tmp, "\"");
      my_putstr(_serveur->client_id, tmp);
      free(tmp);
    }
  else
    my_putstr(_serveur->client_id, "530 Please login with USER and PASS.");
}

void			help_cmd(t_serveur *_serveur)
{
  if (_serveur->status == 2)
    my_putstr(_serveur->client_id, "214 PWD HELP PASV RETR STOR NOOP CWD");
  else
    my_putstr(_serveur->client_id, "530 Please login with USER and PASS.");
}

void			noop_cmd(t_serveur *_serveur)
{
  if (_serveur->status == 2)
    my_putstr(_serveur->client_id, "200 NOOP ok.");
  else
    my_putstr(_serveur->client_id, "530 Please login with USER and PASS.");
}

void			quit_cmd(t_serveur *_serveur)
{
  my_putstr(_serveur->client_id, "221 Goodbye.");
  close(_serveur->client_id);
}
