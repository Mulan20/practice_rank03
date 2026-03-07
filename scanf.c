//scanf.c u just need to fix the given code 

//Allowed functions: fgetc, ungetc, ferror, feof, isspace, 
// isdigit, stdin, va_start, va_arg, va_copy, va_end

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int ch = fgetc(f);
    if (ch == EOF && ferror(f))
        return -1;
    while (ch != EOF)
    {
        if (!is_space(ch))
        {
            unget(ch, f);
            break;
        }
        ch = fgetc(f);
    }
    if (ferror(f))
        return -1;
    return 1;
}

int match_char(FILE *f, char c)
{
    int ch = fgetc(f);

    if (ch == c)
        return 1;
    if (ch != EOF)
        ungetc(ch, f);

    return -1;
}

int scan_char(FILE *f, va_list ap)
{\
    int ch = fgetc(f);
    char *cp = va_arg(ap, char *);

    if (ch == EOF)
        return -1;

    *cp =(char) ch;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int ch = fgetc(f);
    int *ip = va_arg(ap, int *);
    int value = 0;
    int sign = 1;
    int count = 0;

    if (isspace(ch))
        ch = fgetc(f);

    if (ch == EOF)
        return -1;

    if (ch == '+')
        ch = fgetc(f);
    else if (ch == '-')
    {
        ch = fgetc(f);
        sign = -1;
    }

    if (!isdigit(ch))
    {
        ungetc(ch, f); //don't forget to return 
        return -1;
    }
        while (isdigit(ch))
    {
        value += value * 10 + (ch - '0');
        count++;
        ch = fgetc(f);
    }
    if (ch != EOF)
        ungetc(ch, f);
    if (count <= 0)
        return -1;
    *ip = value *sign;
    return 1;

}

int scan_string(FILE *f, va_list ap)
{
    int ch = fgetc(f);
    char *sp = va_arg(ap, char *);
    int len = 0;

    while (isspace(ch) && ch != EOF) //dont forget != EOF
        ch = fgetc(f);
    if (ch == EOF)
        return -1;

    do
    {
        sp[len] = ch;
        ch = fgetc(f);
        len++;
    } while (!isspace(ch) && ch != EOF);

    sp[len] = '\0'; //don't forget null terminator
    if (ch != EOF)
        ungetc(ch, f);
    if (len <= 0)
        return -1;
    return 1; 

}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
    va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}