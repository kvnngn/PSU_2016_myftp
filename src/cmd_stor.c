/*
** cmd_stor.c for  in /home/kevin/rendu/PSU_2016_myftp
** 
** Made by kevin
** Login   <kevin3.nguyen@epitech.eu>
** 
** Started on  Sun May 21 13:27:14 2017 kevin
** Last update Sun May 21 23:11:00 2017 kevin
*/

#include			"my_ftp.h"

void				stor_cmd(t_serveur *_serveur)
{
  int				fd;
  char				str[10];
  int				buffer;

  if (_serveur->status == 2)
    {
      if (_serveur->data.status == 1)
	{
	  if (_serveur->cmd[1])
	    {
	      if ((fd = creat(_serveur->cmd[1],
			      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return;
	      my_putstr(_serveur->client_id, "150 Opening data connection");
	      while ((buffer = read(_serveur->data.socket, str, 10)) > 0)
		write(fd, str, buffer);
	      my_putstr(_serveur->client_id, "226 Transfer completed.");
	      close(fd);
	      close(_serveur->data.socket);
	      init_transfert(_serveur);
	    }
	}
      else my_putstr(_serveur->client_id, "550 Permission denied.");
    }
  else my_putstr(_serveur->client_id, "530 Please login with USER and PASS.");
}
