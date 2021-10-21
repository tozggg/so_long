/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:05:03 by taejkim           #+#    #+#             */
/*   Updated: 2021/10/21 14:07:54 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

int		ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin_free_s1(char *s1, char *s2);
char	*ft_strjoin_free_s2(char *s1, char *s2);
char	*ft_itoa(int n);

#endif
