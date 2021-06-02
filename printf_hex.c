#include "ft_printf.h"

void	align_hex(t_flags *flag, int len, int hex)
{
	if (flag->width > flag->precision && flag->left_align == 0)
	{
		if (flag->precision > len)
			align(flag->width - flag->precision);
		else if (flag->precision >= 0)
			align (flag->width - len);
		else if (flag->zero == 1)
			align_integer(flag->width - len);
	}
	if (flag->precision > len)
		align_integer(flag->precision - len);
	ft_puthex(hex);
	if (flag->left_align == 1)
	{
		if (flag->precision >= len)
			align(flag->width - flag->precision);
		else if (flag->precision < len)
			align (flag->width - len);
	}
}

int	return_x(t_flags *flag, int idx, int len)
{
	if (flag->width == 0 && flag->precision == -1)
		idx = len;
	else if (flag->width > flag->precision && flag->width > len)
		idx = flag->width;
	else if (flag->precision >= flag->width && flag->precision > len)
		idx = flag->precision;
	else
		idx = len;
	return (idx);
}

int	zero_arg_hex(int arg, t_flags *flag, int len, int hex)
{
	if (flag->precision == -1)
	{
		if (flag->left_align == 0 && flag->width > 0 && flag->precision == -1)
		{
			if (flag->zero == 0 && flag->precision == -1)
				align(flag->width - len);
			else if (flag->zero == 1)
				align_integer(flag->width - len);
			ft_puthex(hex);
			return (flag->width);
		}
	}
	else if (flag->precision > -1 && flag->width >= flag->precision && arg == 0)
	{
		if (flag->left_align == 0)
			align(flag->width - flag->precision);
		if (flag->precision != 0)
			align_integer(flag->precision);
		if (flag->left_align == 1)
			align(flag->width - flag->precision);
		return (flag->width);
	}
	return (-1);
}

int	parse_precision_hex(int arg, t_flags *flag, int len, int hex)
{
	int	idx;

	if (flag->precision == 0 && flag->width == 0)
	{
		if (arg == 0)
			return (0);
	}
	else if (flag->width >= flag->precision && arg == 0)
	{
		idx = zero_arg_hex(arg, flag, len, hex);
		if (idx >= 0)
			return (idx);
	}
	else if (flag->width <= flag->precision)
	{
		align_integer(flag->precision - len);
		ft_puthex(hex);
		return (flag->precision);
	}
	align_hex(flag, len, hex);
	return (-1);
}

int	parse_hexadecimal(ssize_t address, t_flags *flag)
{
	int	idx;
	int	len;

	idx = 0;
	len = count_addr(address);
	flag->width = flag->width - len - 2;
	if (flag->width > 0)
	{
		idx = flag->width;
		align(flag->width);
	}
	return (idx);
}