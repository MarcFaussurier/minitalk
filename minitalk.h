#ifndef MINITALK_H
# define MINITALK_H
typedef struct
{
	union
	{
		int				len;
		struct
		{
			char 	c1;
			char	c2;
			char	c3;
			char	c4;
		};
	};
	int				p;
	unsigned char	i;
	char			*o;
}	t_str;
#endif
