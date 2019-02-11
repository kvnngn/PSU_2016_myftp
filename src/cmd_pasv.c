/*
** server.c for server in /home/kevin/rendu/PSU_2016_myftp/src
** 
** Made by kevin
** Login   <kevin3.nguyen@epitech.eu>
** 
** Started on  Tue May  9 14:21:07 2017 kevin
** Last update Sun May 21 23:34:24 2017 kevin
*/

#include		"my_ftp.h"

void			init_transfert(t_serveur *_serveur)
{
  _serveur->data.socket = -1;
  _serveur->data.port = -1;
  _serveur->data.status = -1;
}

void			send_ip(t_serveur *server)
{
  int			i;

  i = 0;
  while (server->server_ip[i])
    {
      if (server->server_ip[i] == '.')
	write(server->client_id, ",", 1);
      else
	write(server->client_id, &server->server_ip[i], 1);
      i++;
    }
  write(server->client_id, ",", 1);
}

void			send_pasv(t_serveur *_serveur)
{
  char			*str;

  write(_serveur->client_id,
	"227 Entering Passive Mode (",
	strlen("227 Entering Passive Mode ("));
  send_ip(_serveur);
  if ((str = malloc(4)) == NULL)
    return;
  sprintf(str, "%d", _serveur->data.port / 256);
  write(_serveur->client_id, str, strlen(str));
  write(_serveur->client_id, ",", 1);
  sprintf(str, "%d", _serveur->data.port % 256);
  write(_serveur->client_id, str, strlen(str));
  write(_serveur->client_id, ")\r\n", 3);
  free(str);
}

void			init_data(t_serveur *_serveur)
{
  _serveur->data.socket = socket(AF_INET, SOCK_STREAM, 0);
  _serveur->data.config.sin_family = AF_INET;
  _serveur->data.config.sin_addr.s_addr = INADDR_ANY;
  _serveur->data.port = 10000;
  _serveur->data.len = sizeof(struct sockaddr);
}

void			pasv_cmd(t_serveur *_serveur)
{
  int			check;

  if (_serveur->status == 2)
    {
      init_data(_serveur);
      while (_serveur->data.port < 65536)
	{
	  _serveur->data.config.sin_port = htons(_serveur->data.port);
	  check = bind(_serveur->data.socket, (struct sockaddr *)
			&_serveur->data.config, sizeof(struct sockaddr_in));
	  if (!check)
	    break;
	  _serveur->data.port++;
	}
      listen(_serveur->data.socket, 1);
      send_pasv(_serveur);
      _serveur->data.status = 1;
    }
  else my_putstr(_serveur->client_id, "530 Please login with USER and PASS.");
}
