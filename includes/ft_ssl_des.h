/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:41:57 by jchow             #+#    #+#             */
/*   Updated: 2017/11/22 18:38:30 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H

# include "libft.h"
# include "ft_des_num.h"
# include <pwd.h>
# include <errno.h>

# define CMD_COUNT	6
# define CMD_CIPHER "base64", "des", "des-ecb", "des-cbc", "des3", "des3-cbc"

# define FP_CIPHER_PT1 &ft_base64, &ft_des_ecb, &ft_des_ecb, &ft_des_cbc,
# define FP_CIPHER_PT2 &ft_des3_cbc, &ft_des3_cbc
# define FP_CIPHER FP_CIPHER_PT1 FP_CIPHER_PT2

# define MASK_6BITS 63
# define MASK_32 	0x80000000
# define MASK_64 	0x8000000000000000

# define REDTXT		"[31m"
# define GRNTXT		"[32m"
# define MAGTXT		"[35m"
# define CYANTXT	"[36m"
# define ENDTXT		"[0m"

/*
** "nopad" flag does not emulate openssl's.
** Blocks are still padded to blocksize, with null terminating zeroes.
*/

typedef struct	s_flags
{
	uint8_t	e:1;
	uint8_t	d:1;
	uint8_t	i:1;
	uint8_t	o:1;
	uint8_t	a:1;
	uint8_t	k:1;
	uint8_t	v:1;
	uint8_t	p:1;
	uint8_t	nopad:1;
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

typedef struct	s_data
{
	size_t	len;
	int		output_fd;
	char	*input;
	char	*key_string;
	char	*init_vector;
	t_flags	flags;
}				t_data;

void			ft_base64(int ac, char **av, t_data *data);
void			ft_des_ecb(int ac, char **av, t_data *data);
void			ft_des_cbc(int ac, char **av, t_data *data);
void			ft_des3_cbc(int ac, char **av, t_data *data);

void			parse_opts_des_cbc(char *str, t_data *data);
void			parse_args_des_cbc(int ac, char **av, t_data *data);

void			generate_keys(uint64_t k[16], t_data *data);
void			generate_des3_keys(uint64_t k[3][16], t_data *data);

char			*en_base64(char *input, size_t len, t_data *data);
char			*de_base64(char *input, size_t len, t_data *data);
void			des_de_base64(t_data *data);
char			*des_en_base64(char *input, t_data *data);

void			des_cbc_xor_vector_en(uint64_t *buf, uint64_t *buf_prev,
				uint64_t *vector, t_data *data);
void			des_cbc_xor_vector_de(uint64_t *buf, uint64_t *buf_prev,
				uint64_t *vector, t_data *data);

void			des_remove_padding(char *output, t_data *data);
uint64_t		des_block_permutations(uint64_t k[], uint64_t buf);
uint64_t		des_string_to_buffer(size_t len, int i, t_data *data);

uint32_t		permutate_sbox(uint64_t e_block);
uint64_t		permutate_e(uint64_t r_block);
uint64_t		permutate(uint64_t block, const t_uc table[],
						int size, uint64_t mask);

void			write_exit(int n);
void			endian_switch32(uint32_t *n);
void			endian_switch64(uint64_t *n);
char			*string_truncate(char *str, int bytes);
char			*allocate_output_and_proc_de_base64(t_data *data);

void			read_input_from_file(char *str, t_data *data);
void			get_input_from_stdin(t_data *data);
void			get_key_from_stdin(t_data *data);
void			get_vector_from_stdin(t_data *data);
void			write_output(char *output, t_data *data);

static char		*g_commands[] = {
	CMD_CIPHER
};

static void		(*g_cmd_fp[CMD_COUNT])(int, char**, t_data*) = {
	FP_CIPHER
};

#endif
