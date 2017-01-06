/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:28:44 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/06 09:46:59 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define LS_RECUR 0b00001
# define LS_ALL 0b00010
# define LS_LONG 0b00100
# define LS_REV 0b01000
# define LS_TIME 0b10000

#include "../libft/includes/libft.h"
#include "../libft/includes/ft_getopt.h"
#include "dirent.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int	g_option;
int g_multi;
const char *g_path;

typedef struct	s_len
{
	int	link;
	int	user;
	int	group;
	int filesize;
}				t_len;

typedef struct	s_file
{
	struct dirent	*info;
	struct stat		st;
	struct passwd	*pass;
	struct group	*gr;
}				t_file;

typedef struct	s_node
{
	t_file			*content;
	struct s_node	*brother;
	struct s_node	*child;
}				t_node;

int		tree_is_empty(t_node *tree);
t_node	*create_btree(struct dirent *info, t_node *brother, t_node *child, const char *path);
void	new_node(t_node **tree, struct dirent *content, int (*f)(void *s1, void *s2, const char *path), const char *path);
void	clean_tree(t_node *tree);
int		ft_ls(const char *path);
t_node	*put_in_tree(t_node *tree, const char *path);
void	put_opt_binary(int ret);
int		cmprev(void *s1, void *s2, const char *path);
int		cmp(void *s1, void *s2, const char *path);
int		cmp_time(void *s1, void *s2, const char *path);
void	sort_arg(int ac, const char *av[]);
void	new_list(t_list **lst, const char *content, size_t content_size, int (*f)(void *s1, void *s2));
t_list	*create_lst(const char *content, size_t content_size, t_list *next);
int		cmp_arg_time(void *s1, void *s2);
int		cmp_arg(void *s1, void *s2);

#endif
