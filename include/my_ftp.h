/*
** my_ftp.h for my_ftp in /home/kevin/rendu/PSU_2016_myftp/include
** 
** Made by kevin
** Login   <kevin3.nguyen@epitech.eu>
** 
** Started on  Tue May  9 15:13:53 2017 kevin
** Last update Sun May 21 23:05:06 2017 kevin
*/

#ifndef MY_FTP_H
# define MY_FTP_H

#include				<sys/types.h>
#include				<arpa/inet.h>
#include				<stdio.h>
#include				<stdlib.h>
#include				<unistd.h>
#include				<sys/socket.h>
#include				<string.h>
#include				<sys/types.h>
#include				<signal.h>
#include				<libgen.h>
#include				<dirent.h>
#include				<errno.h>
#include				<sys/stat.h>
#include				<fcntl.h>

typedef struct				s_transfert
{
  int					socket;
  int					client_id;
  int					port;
  char					*ip;
  unsigned int			        len;
  int					status;
  struct sockaddr_in			client_config;
  struct sockaddr_in			config;
}					t_transfert;

typedef struct				s_serveur
{
  int					id;
  int					client_id;
  unsigned int			        len;
  int				        port;
  int					pid;
  char					*path;
  char					*server_ip;
  char					*buf;
  char					*pwd;
  char					*filename;
  char					*username;
  int					status;
  char					**cmd;
  struct sockaddr_in			client_config;
  struct sockaddr_in			config;
  t_transfert				data;
}					t_serveur;

typedef struct				t_pointeur
{
  char					*func;
  void					(*ptr)(t_serveur *_serveur);
}				        t_pointeur;

char					*my_itoa(int nb);
char					*get_next_line(const int fd);
char					**my_str_to_wordtab(char *str);
void					my_putstr(int fd, char *str);
void					pass_cmd(t_serveur *_serveur);
void					user_cmd(t_serveur *_serveur);
void					quit_cmd(t_serveur *_serveur);
void					noop_cmd(t_serveur *_serveur);
void					help_cmd(t_serveur *_serveur);
void					pwd_cmd(t_serveur *_serveur);
void				        dele_cmd(t_serveur *_serveur);
void					cwd_cmd(t_serveur *_serveur);
void					retr_cmd(t_serveur *_serveur);
char					*check_path(char *path);
char					*get_filename(char *buffer);
char					*get_content(char *buffer);
void					stor_cmd(t_serveur *_serveur);
void					init_transfert(t_serveur *_serveur);
void					print_ip(t_serveur *server);
void					print_pasv(t_serveur *_serveur);
void					pasv_cmd(t_serveur *_serveur);

#endif /* MY_FTP_H */
