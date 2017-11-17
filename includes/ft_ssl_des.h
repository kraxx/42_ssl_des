/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:41:57 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:34:26 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H

# include "libft.h"
# include "ft_des_num.h"
# include <pwd.h>
# include <errno.h>

# define CMD_COUNT	4
# define CMD_CIPHER "base64", "des", "des-ecb", "des-cbc"
# define FP_CIPHER &ft_base64, &ft_des_ecb, &ft_des_ecb, &ft_des_cbc

# define MASK_6BITS 63
# define MASK_32 	0x80000000
# define MASK_64 	0x8000000000000000

typedef struct	s_flags
{
	uint8_t	e:1;
	uint8_t	d:1;
	uint8_t	i:1;
	uint8_t	o:1;
	uint8_t	a:1;
	uint8_t	k:1;
	uint8_t	v:1;
	uint8_t	badread:1;
}				t_flags;

typedef union	u_32bits
{
	uint32_t	i;
	uint8_t		c[4];
}				t_32bits;

typedef union	u_64bits
{
	uint64_t	ll;
	uint32_t	i[2];
	uint8_t		c[8];
}				t_64bits;

void			ft_base64(int ac, char **av);
void			ft_des_ecb(int ac, char **av);
void			ft_des_cbc(int ac, char **av);

void			set_g_string(char *str);
void			process_keys(uint64_t k[]);

char			*en_base64(char *input, int len);
char			*de_base64(char *input);

void			generate_subkeys_en(uint32_t c[], uint32_t d[]);
void			generate_subkeys_de(uint32_t c[], uint32_t d[]);
void			generate_16keys(uint32_t c[], uint32_t d[], uint64_t k[]);

void			des_ecb_encrypt_64bits(uint64_t k[], char *new_string, int len);
void			des_cbc_encrypt_64bits(uint64_t k[], uint64_t vector,
									char *new_string, int len);

uint32_t		permutate_sbox(uint64_t e_block);
uint64_t		permutate_e(uint64_t r_block);
uint64_t		permutate(uint64_t block, const t_uc table[],
						int size, uint64_t mask);

void			write_exit(int n);
void			check_stdin(int opt);
void			endian_switch32(uint32_t *n);
void			endian_switch64(uint64_t *n);
char			*string_64bits(char *str);

void			get_input_from_stdin(void);
void			get_key_from_stdin(void);
void			get_vector_from_stdin(void);

static char		*g_commands[] = {
	CMD_CIPHER
};

static void		(*g_cmd_fp[CMD_COUNT])(int, char**) = {
	FP_CIPHER
};

extern int		g_output_fd;
extern char		*g_string;
extern char		*g_key_string;
extern char		*g_init_vector;
extern t_flags	g_flags;

#endif
