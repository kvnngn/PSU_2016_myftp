/*
** server.c for server in /home/kevin/rendu/PSU_2016_myftp/src
** 
** Made by kevin
** Login   <kevin3.nguyen@epitech.eu>
** 
** Started on  Tue May  9 14:21:07 2017 kevin
** Last update Sun May 21 22:17:27 2017 kevin
*/

#include	        "my_ftp.h"

void			retr_cmd(t_serveur *_serveur)
{
  if (_serveur->status == 2)
    my_putstr(_serveur->client_id, "150 File status okay");
  else
    my_putstr(_serveur->client_id, "530 Please login with USER and PASS.");
}

void			cwd_cmd(t_serveur *_serveur)
{
  char			*tmp;

  if (_serveur->status == 2)
    {
      if (_serveur->cmd[1])
	{
	  if (chdir(_serveur->cmd[1]) == -1)
	    {
	      my_putstr(_serveur->client_id, "550 failed to change directory");
	      return;
	    }
	  tmp = strcat(_serveur->path, _serveur->cmd[1]);
	  _serveur->path = strdup(tmp);
	  my_putstr(_serveur->client_id, "250 Directory successfully changed");
	}
      else
	my_putstr(_serveur->client_id, "501 Failed to change directory.");
    }
  else
    my_putstr(_serveur->client_id, "530 Please login with USER and PASS.");
}

void			dele_cmd(t_serveur *_serveur)
{
  if (_serveur->status == 2)
    my_putstr(_serveur->client_id, "250 Requested file action ok.");
  else
    my_putstr(_serveur->client_id, "530 Please login with USER and PASS.");
}
