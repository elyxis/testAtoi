/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testAtoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gculot <gculot@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:12:35 by gculot            #+#    #+#             */
/*   Updated: 2024/04/22 20:13:58 by gculot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

char *increment_string_number(const char *input) {
    long number = atol(input);
    number++;
    int length = snprintf(NULL, 0, "%ld", number);
    char *result = malloc(length + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    snprintf(result, length + 1, "%ld", number);
    return result;
}

void test_large_range() {
    char buffer[50]; // Assez grand pour les grands nombres
    long long test_val;
    long long result_ft, result_std;
	
	test_val =	-2147483644 ;
    // Commencez à partir d'une valeur élevée, proche de LLONG_MAX, pour les types signés
    while (1) {
		test_val=test_val-1000000000000000000;											    
        sprintf(buffer, "%lld", test_val);
		//printf( "%s\n", buffer);
        result_std = atoi(buffer);  // Utilisation de atoll pour gérer les grands nombres
        result_ft = ft_atoi(buffer);

		printf( "%lld | %lld (atoll : %lld)\n", result_std, result_ft, atoll(buffer));
       
        if (result_std != result_ft || result_std == 0) {
            printf("Mismatch with value '%s': ft_atoi() = %lld, atoi() = %d, atoll() = %lld\n", buffer, result_ft,atoi(buffer), result_std);
			            return;
        }

		//if ( result_std != result) return ;
    }
}

////////////////////////////////////////


char* format_number(int64_t value) {
    // Calculer la longueur nécessaire pour la chaîne, y compris le signe et le caractère nul
    int length = snprintf(NULL, 0, "%" PRId64, value);
    char* result = malloc(length + 1); // Allouer de la mémoire pour la chaîne
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    snprintf(result, length + 1, "%" PRId64, value); // Écrire la valeur dans la chaîne
	//printf(" ----> %" PRId64 "\n", value); // Écrire la valeur dans la chaîne
    return result;
}

void generate_numbers(int n, int a_start, int a_end) {
    for (int i = n; i <= n; ++i) {
        uint64_t num = (uint64_t)1 << i;
		
		printf("\n*****************************\n");

        for (int a = a_start; a <= a_end; ++a) {
            uint64_t pos_val = num + a;
            int64_t neg_val = -(int64_t)num + a;

            char* pos_str = format_number(pos_val);
            char* neg_str = format_number(neg_val);

			
			if (pos_str != NULL && neg_str != NULL) {
                printf("2^%d + %d = %s\n", i, a, pos_str);
                printf("-(2^%d) + %d = %s\n", i, a, neg_str);
            }
if (atoi(pos_str) != ft_atoi(pos_str))
	printf("**");
if (atoi(pos_str) != strtoll(pos_str, NULL, 10))
	printf("\033[32m");
if (atoi(pos_str) != ft_atoi(pos_str))
	printf("\033[31m");

			printf(" %45s - ***** original : %d  -  ft_atoi : %d - (atoll : %lld)- (strtol : %lld)\033[0m\n", pos_str, atoi(pos_str), ft_atoi(pos_str), atoll(pos_str), strtoll(pos_str, NULL, 10));
if (atoi(neg_str) != ft_atoi(neg_str))
	printf("**");
if (atoi(neg_str) != strtoll(neg_str, NULL, 10))
	printf("\033[32m");
if (atoi(neg_str) != ft_atoi(neg_str))
	printf("\033[31m");
		
			printf(" %45s - ***** original : %d  -  ft_atoi : %d - (atoll : %lld)- (strtol : %lld)\033[0m\n", neg_str, atoi(neg_str), ft_atoi(neg_str), atoll(neg_str), strtoll(neg_str, NULL, 10));
			
            free(pos_str); // Libérer la mémoire allouée pour la chaîne
            free(neg_str); // Libérer la mémoire allouée pour la chaîne
        }
    }
}


////////////////////////////////////////////


int main ()
{

	
	// Signed: −(2n−1) to (2n−1 − 1) 
	// Unsigned: 0 to (2n − 1) 

	int  LenMax     = 35 ;    /* Specified Length    */ 
	char fillChar	= '5';
	for (int i =1; i<=LenMax; i++) // positif
	{
		char *str = malloc(i + 1);
		if (!str)
		{
			printf("erreur - Allocation mémoire");
			exit(0);
		}
		memset(str, fillChar, i);
		str[i] = '\0';
		
		if (atoi(str) != ft_atoi(str) || atoi(str) == 0 || atoi(str) == -1 )
		if (atoi(str) != ft_atoi(str))
		printf("\033[31m");
			printf(" %45s Longueur = %d - ***** original : %d  -  ft_atoi : %d - (atoll : %lld)\033[0m\n", str, i , atoi(str), ft_atoi(str), atoll(str) );
		free(str);
	}

	for (int i =1; i<=LenMax; i++) // négatif
	{
		char *str = malloc(i + 2);
		if (!str)
		{
			printf("erreur - Allocation mémoire");
			exit(0);
		}
		memset(str, fillChar, i);
		str[0] = '-';
		str[i] = '\0';
		
		if (atoi(str) != ft_atoi(str) || atoi(str) == 0 || atoi(str) == -1 )
		if (atoi(str) != ft_atoi(str))
		printf("\033[31m");	
			printf(" %45s Longueur = %d - ***** original : %d  -  ft_atoi : %d - (atoll : %lld)\033[0m\n", str, i , atoi(str), ft_atoi(str), atoll(str) );
		free(str);
	}

	
///////////////////////////////////
generate_numbers(15, -4, 4); // 16 -1
generate_numbers(31, -4, 4); // 32 -1
generate_numbers(63, -4, 4); // 64 -1
//test_large_range();

const char *tests_string[30] = {
	"-2147483648781521474836472147483647214748364721474836472147483647",
	"2147483648781521474836472147483647214748364721474836472147483647",
	"99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999",
	"-99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999",
	"+9223372036854775807",
	"+9223372036854775808",
	"+9223372036854775809",
	"-9223372036854775808",
	"-9223372036854775809",
	"-2147483648",
    "-2147483649",
    "\t fgjhbwlrkhjtng-123456",
	"135fgjhbwlrkhjtng-123456",
	"+45abc",
    "-1",
	"0",
	"1",
	"18446744073709551614",
	"18446744073709551615",
	"18446744073709551616",
	"18446744073709551617",
	"+0000000000000000000000000000000000000000000000000000123",
	"-0000000000000000000000000000000000000000000000000000321"
	};

int i = 0;
while (tests_string[i])
{
//printf("%s \n-> ***** original : %d  -  ft_atoi : %d *****\n\n",  s1 , atoi(s1),  ft_atoi(s1) );

	if (atoi(tests_string[i]) != ft_atoi(tests_string[i]) || atoi(tests_string[i]) == 0 || atoi(tests_string[i]) == -1 )
		if (atoi(tests_string[i]) != ft_atoi(tests_string[i]))
		printf("\033[31m");	
			printf(" %60s - ***** original : %d  -  ft_atoi : %d - (atoll : %lld)\033[0m\n", tests_string[i], atoi(tests_string[i]), ft_atoi(tests_string[i]), atoll(tests_string[i]) );
	i++;
}

return 0;
	
} 
