/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 19:50:23 by edi-maio          #+#    #+#             */
/*   Updated: 2026/08/01 19:07:27 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cerrno>
#include <cstdlib>
#include <climits>
#include <iomanip>
#include <iostream>
#include <ctime>

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

std::vector<int> PmergeMe::parseInput(int ac, char **av)
{
    std::vector<int> v;
    for (int i = 1; i < ac; ++i)
    {
        char *end;
        errno = 0;
        long n = std::strtol(av[i], &end, 10);
        if (errno == ERANGE || *end || end == av[i] || n <= 0 || n > INT_MAX)
        {
            v.clear();
            return v;
        }
        v.push_back(static_cast<int>(n));
    }
    return v;
}

void PmergeMe::printSeq(const std::vector<int> &v, const std::string &label)
{
    std::cout << label;
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << (i + 1 < v.size() ? " " : "");
    std::cout << std::endl;
}

std::vector<VElem> PmergeMe::sortVec(std::vector<VElem> a)
{
    if (a.size() < 2)
        return a;

    bool odd = a.size() % 2;
    std::vector<VElem> mains, pends;
    for (std::size_t i = 0; i + 1 < a.size(); i += 2)
    {
        if (a[i].val < a[i + 1].val)
        { mains.push_back(a[i + 1]); pends.push_back(a[i]); }
        else
        { mains.push_back(a[i]); pends.push_back(a[i + 1]); }
    }

    std::vector<VElem> sortedMains = sortVec(mains);

    std::vector<VElem> orderedPends(pends.size());
    for (std::size_t i = 0; i < sortedMains.size(); ++i)
        for (std::size_t k = 0; k < mains.size(); ++k)
            if (mains[k].id == sortedMains[i].id) { orderedPends[i] = pends[k]; break; }

    std::vector<VElem> chain;
    chain.push_back(orderedPends[0]);
    chain.insert(chain.end(), sortedMains.begin(), sortedMains.end());

    std::vector<std::size_t> mainPos(sortedMains.size());
    for (std::size_t i = 0; i < mainPos.size(); ++i)
        mainPos[i] = i + 1;

    std::size_t n = sortedMains.size(), done = 1, jPrev = 1, jCur = 1;
    while (done < n)
    {
        std::size_t jNext = jCur + 2 * jPrev;
        std::size_t upto = std::min(jNext, n);
        for (std::size_t idx = upto; idx > done; --idx)
        {
            std::size_t r = idx - 1;
            std::size_t insertIdx = lowerBoundVec(chain, mainPos[r], orderedPends[r].val);
            chain.insert(chain.begin() + insertIdx, orderedPends[r]);
            for (std::size_t m = 0; m < mainPos.size(); ++m)
                if (mainPos[m] >= insertIdx) mainPos[m]++;
        }
        if (upto >= n) break;
        done = upto; jPrev = jCur; jCur = jNext;
    }
    if (odd)
    {
        VElem last = a.back();
        std::size_t insertIdx = lowerBoundVec(chain, chain.size(), last.val);
        chain.insert(chain.begin() + insertIdx, last);
    }
    return chain;
}

std::deque<DElem> PmergeMe::sortDeq(std::deque<DElem> a)
{
    if (a.size() < 2)
        return a;

    bool odd = a.size() % 2;
    std::deque<DElem> mains, pends;
    for (std::size_t i = 0; i + 1 < a.size(); i += 2)
    {
        if (a[i].val < a[i + 1].val)
        { mains.push_back(a[i + 1]); pends.push_back(a[i]); }
        else
        { mains.push_back(a[i]); pends.push_back(a[i + 1]); }
    }

    std::deque<DElem> sortedMains = sortDeq(mains);

    std::deque<DElem> orderedPends(pends.size());
    for (std::size_t i = 0; i < sortedMains.size(); ++i)
        for (std::size_t k = 0; k < mains.size(); ++k)
            if (mains[k].id == sortedMains[i].id) { orderedPends[i] = pends[k]; break; }

    std::deque<DElem> chain;
    chain.push_back(orderedPends[0]);
    chain.insert(chain.end(), sortedMains.begin(), sortedMains.end());

    std::vector<std::size_t> mainPos(sortedMains.size());
    for (std::size_t i = 0; i < mainPos.size(); ++i)
        mainPos[i] = i + 1;

    std::size_t n = sortedMains.size(), done = 1, jPrev = 1, jCur = 1;
    while (done < n)
    {
        std::size_t jNext = jCur + 2 * jPrev;
        std::size_t upto = std::min(jNext, n);
        for (std::size_t idx = upto; idx > done; --idx)
        {
            std::size_t r = idx - 1;
            std::size_t insertIdx = lowerBoundDeq(chain, mainPos[r], orderedPends[r].val);
            chain.insert(chain.begin() + insertIdx, orderedPends[r]);
            for (std::size_t m = 0; m < mainPos.size(); ++m)
                if (mainPos[m] >= insertIdx) mainPos[m]++;
        }
        if (upto >= n) break;
        done = upto; jPrev = jCur; jCur = jNext;
    }

    if (odd)
    {
        DElem last = a.back();
        std::size_t insertIdx = lowerBoundDeq(chain, chain.size(), last.val);
        chain.insert(chain.begin() + insertIdx, last);
    }
    return chain;
}

int PmergeMe::run(int ac, char **av) const
{
    std::vector<int> input = parseInput(ac, av);
    if (input.empty())
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    printSeq(input, "Before: ");

    std::vector<VElem> vin;
    std::deque<DElem> din;
    for (std::size_t i = 0; i < input.size(); ++i)
    {
        VElem ve = { input[i], static_cast<int>(i) };
        DElem de = { input[i], static_cast<int>(i) };
        vin.push_back(ve);
        din.push_back(de);
    }

    struct timespec t0, t1, t2, t3;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    std::vector<VElem> sv = sortVec(vin);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    clock_gettime(CLOCK_MONOTONIC, &t2);
    std::deque<DElem> sd = sortDeq(din);
    clock_gettime(CLOCK_MONOTONIC, &t3);

    double vecUs = (t1.tv_sec - t0.tv_sec) * 1e6 + (t1.tv_nsec - t0.tv_nsec) / 1e3;
    double deqUs = (t3.tv_sec - t2.tv_sec) * 1e6 + (t3.tv_nsec - t2.tv_nsec) / 1e3;

    std::vector<int> sorted;
    for (std::size_t i = 0; i < sv.size(); ++i)
        sorted.push_back(sv[i].val);
    printSeq(sorted, "After: ");

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << sorted.size()
              << " elements with std::vector : " << vecUs << " us" << std::endl;
    std::cout << "Time to process a range of " << sd.size()
              << " elements with std::deque : " << deqUs << " us" << std::endl;
    return 0;
}

std::size_t PmergeMe::lowerBoundVec(const std::vector<VElem> &chain, std::size_t hiIdx, int val)
{
    std::size_t lo = 0, hi = hiIdx;
    while (lo < hi)
    {
        std::size_t mid = lo + (hi - lo) / 2;
        if (chain[mid].val < val)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

std::size_t PmergeMe::lowerBoundDeq(const std::deque<DElem> &chain, std::size_t hiIdx, int val)
{
    std::size_t lo = 0, hi = hiIdx;
    while (lo < hi)
    {
        std::size_t mid = lo + (hi - lo) / 2;
        if (chain[mid].val < val)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}