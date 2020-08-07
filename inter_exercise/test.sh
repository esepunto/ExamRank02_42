# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssacrist </var/mail/ssacrist>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/07 09:25:44 by ssacrist          #+#    #+#              #
#    Updated: 2020/08/07 09:26:43 by ssacrist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc -Wall -Werror -Wextra inter.c -o inter
echo "# Expected result (next line) Your result #"
echo "---"
echo "padinto$"
./inter zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
echo "---"
echo "df6ewg4$"
./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
echo "---"
echo "rien$"
./inter "rien" "cette phrase ne cache rien" | cat -e
echo "---"
echo "$"
./inter | cat -e
echo "---"
echo "$"
./inter "rien" | cat -e
rm -rf inter
