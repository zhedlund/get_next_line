/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:25:33 by zhedlund          #+#    #+#             */
/*   Updated: 2023/06/18 21:22:14 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;
	int		i;

	if (!s1)
		return (ft_strdup(""));
	len = ft_strlen(s1);
	s2 = ft_calloc(len + 1, sizeof(*s2));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*zero;
	size_t			total;

	total = nmemb * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	zero = ptr;
	while (total != 0)
	{
		*zero = '\0';
		zero++;
		total--;
	}
	return (ptr);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	if (dest == src)
		return (dest);
	if (s < d)
		while (n--)
			*(d + n) = *(s + n);
	else
		while (n--)
			*d++ = *s++;
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;
	int				i;

	ch = c;
	if (ch == '\0')
	{
		i = ft_strlen(s);
		return ((char *)s + i);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
