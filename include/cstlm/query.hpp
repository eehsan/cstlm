#pragma once

#include <sdsl/int_vector.hpp>
#include <sdsl/int_vector_mapper.hpp>
#include "sdsl/suffix_arrays.hpp"
#include "sdsl/suffix_trees.hpp"
#include <sdsl/suffix_array_algorithm.hpp>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>
#include <iomanip>

#include "utils.hpp"
#include "collection.hpp"
#include "index_succinct.hpp"
#include "constants.hpp"

namespace cstlm {

// Returns the Kneser-Ney probability of a sentence, word at a
// time. Words are supplied using the append_symbol method which
// returns the conditional probability of that word given all
// previous words.

template <class t_idx>
class LMQueryMKN {
public:
    using value_type = typename t_idx::value_type;
    using node_type = typename t_idx::cst_type::node_type;
    using index_type = t_idx;

public:
    LMQueryMKN()
    {
        m_idx = nullptr;
    }
    LMQueryMKN(const index_type* idx, uint64_t ngramsize, uint64_t discount_depth, bool start_sentence = true);
    double append_symbol(const value_type& symbol);

    bool operator==(const LMQueryMKN& other) const;

    size_t hash() const;

    bool empty() const
    {
        return m_last_nodes_incl.size() == 1 && m_last_nodes_incl.back() == m_idx->cst.root();
    }

    bool is_start() const
    {
        return m_pattern.size() == 1 && m_pattern.back() == PAT_START_SYM;
    }

private:
    const index_type* m_idx;
    uint64_t m_ngramsize;
    uint64_t m_discount_depth;
    std::vector<node_type> m_last_nodes_incl;
    std::deque<value_type> m_pattern;
};

template <class t_idx>
LMQueryMKN<t_idx>::LMQueryMKN(const t_idx* idx, uint64_t ngramsize, uint64_t discount_depth, bool start_sentence)
    : m_idx(idx)
    , m_ngramsize(ngramsize)
    , m_discount_depth(discount_depth)
{
    auto root = m_idx->cst.root();
    m_last_nodes_incl.push_back(root);
    if (start_sentence) {
        auto node = root;
        auto r = backward_search_wrapper(*m_idx, node, PAT_START_SYM);
        (void)r;
        assert(r >= 0);
        m_last_nodes_incl.push_back(node);
        m_pattern.push_back(PAT_START_SYM);
    }
}

template <class t_idx>
double LMQueryMKN<t_idx>::append_symbol(const value_type& symbol)
{
    if (symbol == PAT_START_SYM && m_pattern.size() == 1 && m_pattern.front() == PAT_START_SYM)
        return log10(1);

    m_pattern.push_back(symbol);
    while (m_ngramsize > 0 && m_pattern.size() > m_ngramsize)
        m_pattern.pop_front();
    std::vector<value_type> pattern(m_pattern.begin(), m_pattern.end());

    // fast way, tracking state
    double p = 1.0 / (m_idx->vocab.size() - 4);
    node_type node_incl = m_idx->cst.root(); // v_F^all matching the full pattern, including last item
    auto node_excl_it = m_last_nodes_incl.begin(); // v_F     matching only the context, excluding last item
    node_type node_excl = *node_excl_it;
    auto pattern_begin = pattern.begin();
    auto pattern_end = pattern.end();

    size_t size = std::distance(pattern_begin, pattern_end);
    bool unk = (*(pattern_end - 1) == UNKNOWN_SYM);
    bool ok = !unk;
    std::vector<node_type> node_incl_vec({ node_incl });

    for (unsigned i = 1; i <= size; ++i) {
        auto start = pattern_end - i;
        if (i > 1 && *start == UNKNOWN_SYM)
            break;
        if (ok) {
            ok = backward_search_wrapper(*m_idx, node_incl, *start);
            if (ok)
                node_incl_vec.push_back(node_incl);
        }

        // recycle the node_incl matches from the last call to append_symbol
        // to serve as the node_excl values
        if (i >= 2) {
            node_excl_it++;
            if (node_excl_it == m_last_nodes_incl.end()) {
                break;
            } else {
                node_excl = *node_excl_it;
            }
        }

        double D1, D2, D3, D4, D5, D6, D7, D8, D9, D10p;
        m_idx->mkn_discount(i, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10p, i == 1 || i != m_ngramsize);

        double c, d;
        if ((i == m_ngramsize && m_ngramsize != 1) || (*start == PAT_START_SYM)) {
            c = (ok) ? m_idx->cst.size(node_incl) : 0;
            d = m_idx->cst.size(node_excl);
        } else if (i == 1 || m_ngramsize == 1) {
            c = (ok) ? m_idx->N1PlusBack(node_incl, start, pattern_end) : 0;
            d = (double)m_idx->discounts.counts.N1plus_dotdot;
        } else {
            c = (ok) ? m_idx->N1PlusBack(node_incl, start, pattern_end) : 0;
            d = m_idx->N1PlusFrontBack(node_excl, start, pattern_end - 1);
        }

        if (c == 1) {
            c -= D1;
        } else if (c == 2) {
            c -= D2;
        } else if (c >= 3) {
            if (m_discount_depth == 3) {
                c -= D3;
            } else if (m_discount_depth == 4) {
                if (c == 3) {
                    c -= D3;
                } else if (c >= 4) {
                    c -= D4;
                }
            } else if (m_discount_depth == 10) {
                if (c == 3) {
                    c -= D3;
                } else if (c == 4) {
                    c -= D4;
                } else if (c == 5) {
                    c -= D5;
                } else if (c == 6) {
                    c -= D6;
                } else if (c == 7) {
                    c -= D7;
                } else if (c == 8) {
                    c -= D8;
                } else if (c == 9) {
                    c -= D9;
                } else if (c >= 10) {
                    c -= D10p;
                }
            }
        }

        uint64_t f1 = 0;
        uint64_t f2 = 0;
        uint64_t f3 = 0;
        uint64_t f4 = 0;
        uint64_t f5 = 0;
        uint64_t f6 = 0;
        uint64_t f7 = 0;
        uint64_t f8 = 0;
        uint64_t f9 = 0;
        uint64_t f10p = 0;

        if ((i == m_ngramsize && m_ngramsize != 1) || (*start == PAT_START_SYM)) {
            m_idx->N123PlusFront(node_excl, start, pattern_end - 1, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10p);
        } else if (i == 1 || m_ngramsize == 1) {
            f1 = m_idx->discounts.counts.n1_cnt[1];
            f2 = m_idx->discounts.counts.n2_cnt[1];
            f3 = m_idx->discounts.counts.n3_cnt[1];
            f4 = m_idx->discounts.counts.n4_cnt[1];
            f5 = m_idx->discounts.counts.n5_cnt[1];
            f6 = m_idx->discounts.counts.n6_cnt[1];
            f7 = m_idx->discounts.counts.n7_cnt[1];
            f8 = m_idx->discounts.counts.n8_cnt[1];
            f9 = m_idx->discounts.counts.n9_cnt[1];
            f10p = (m_idx->vocab_size() - 2) - (f1 + f2 + f3 + f4 + f5 + f6 + f7 + f8 + f9);
        } else {
            m_idx->N123PlusFrontPrime(node_excl, start, pattern_end - 1, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10p);
        }

        //default assumes discount depth = 10
        double gamma = D1 * f1 + D2 * f2 + D3 * f3 + D4 * f4 + D5 * f5 + D6 * f6 + D7 * f7 + D8 * f8 + D9 * f9 + D10p * f10p;
        if (m_discount_depth == 3) {
            gamma = D1 * f1 + D2 * f2 + D3 * (f3 + f4 + f5 + f6 + f7 + f8 + f9 + f10p);
        } else if (m_discount_depth == 4) {
            gamma = D1 * f1 + D2 * f2 + D3 * f3 + D4 * (f4 + f5 + f6 + f7 + f8 + f9 + f10p);
        } 
        p = (c + gamma * p) / d;
    }

    m_last_nodes_incl = node_incl_vec;
    while (m_pattern.size() > m_last_nodes_incl.size())
        m_pattern.pop_front();

    return log10(p);
}

template <class t_idx>
bool LMQueryMKN<t_idx>::operator==(const LMQueryMKN& other) const
{
    if (m_idx != other.m_idx)
        return false;
    if (m_pattern.size() != other.m_pattern.size())
        return false;
    if (m_last_nodes_incl.size() != other.m_last_nodes_incl.size())
        return false;
    for (auto i = 0u; i < m_pattern.size(); ++i) {
        if (m_pattern[i] != other.m_pattern[i])
            return false;
    }
    for (auto i = 0u; i < m_last_nodes_incl.size(); ++i) {
        if (m_last_nodes_incl[i] != other.m_last_nodes_incl[i])
            return false;
    }
    return true;
}

template <class t_idx>
std::size_t LMQueryMKN<t_idx>::hash() const
{
    std::size_t seed = 0;
    for (auto& i : m_pattern) {
        seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    for (auto i = 0u; i < m_last_nodes_incl.size(); ++i) {
        auto id = m_idx->cst.id(m_last_nodes_incl[i]);
        seed ^= id + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}
}
