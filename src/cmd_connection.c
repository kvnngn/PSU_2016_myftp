/*
** cmd_connection.c for  in /home/kevin/Téléchargements/PSU_2016_myftp/src
** 
** Made by kevin
** Login   <kevin3.nguyen@epitech.eu>
** 
** Started on  Thu May 18 17:42:43 2017 kevin
** Last update Sun May 21 15:12:46 2017 kevin
*/

#include			"my_ftp.h"

void				pass_cmd(t_serveur *_serveur)
{
  if (_serveur->username != NULL)
    {
      if (strcmp(_serveur->username, "Anonymous") == 0)
	{
	  _serveur->status = 2;
	  my_putstr(_serveur->client_id, "230 Login successful");
	}
      else
	my_putstr(_serveur->client_id, "530 Login incorrect");
    }
  else
    my_putstr(_serveur->client_id, "530 Please use command USER first");
}

void				user_cmd(t_serveur *_serveur)
{
  if (_serveur->status != 2)
    {
      if (_serveur->cmd[1] != NULL)
	{
	  _serveur->username = strdup(_serveur->cmd[1]);
	  _serveur->status = 1;
	  my_putstr(_serveur->client_id, "331 User name okay, need password.");
	}
      else
	my_putstr(_serveur->client_id, "530 INVALID USER");
    }
  else
    my_putstr(_serveur->client_id, "530 Can't change from guest user.");
}
