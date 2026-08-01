/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 19:50:06 by edi-maio          #+#    #+#             */
/*   Updated: 2026/08/01 19:04:17 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

struct VElem { int val; int id; };
struct DElem { int val; int id; };

class PmergeMe
{
    public:
        PmergeMe();
        ~PmergeMe();
        int run(int ac, char **av) const;
    private:
        static std::vector<int> parseInput(int ac, char **av);
        static void printSeq(const std::vector<int> &v, const std::string &label);
        static std::size_t lowerBoundVec(const std::vector<VElem> &chain, std::size_t hiIdx, int val);
        static std::size_t lowerBoundDeq(const std::deque<DElem> &chain, std::size_t hiIdx, int val);
        static std::vector<VElem> sortVec(std::vector<VElem> a);
        static std::deque<DElem> sortDeq(std::deque<DElem> a);
};

#endif