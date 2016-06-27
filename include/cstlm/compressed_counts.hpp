#pragma once

#include <iostream>

#include "sdsl/vectors.hpp"

#include "constants.hpp"
#include "collection.hpp"
#include "logging.hpp"
#include "utils.hpp"

#include "counts_writer.hpp"

namespace cstlm {

template <class t_bv = sdsl::rrr_vector<15>, class t_vec = sdsl::dac_vector<> >
struct compressed_counts {
    typedef sdsl::int_vector<>::size_type size_type;
    typedef t_bv bv_type;
    typedef typename bv_type::rank_1_type rank_type;
    typedef t_vec vector_type;

private:
    bv_type m_bv;
    rank_type m_bv_rank;
    vector_type m_counts_fb;
    vector_type m_counts_f1prime;
    vector_type m_counts_f2prime;
    vector_type m_counts_f3prime;
    vector_type m_counts_f4prime;
    vector_type m_counts_f5prime;
    vector_type m_counts_f6prime;
    vector_type m_counts_f7prime;
    vector_type m_counts_f8prime;
    vector_type m_counts_f9prime;

    vector_type m_counts_b;
    vector_type m_counts_f1;
    vector_type m_counts_f2;
    vector_type m_counts_f3;
    vector_type m_counts_f4;
    vector_type m_counts_f5;
    vector_type m_counts_f6;
    vector_type m_counts_f7;
    vector_type m_counts_f8;
    vector_type m_counts_f9;

    bool m_is_mkn;

public:
    compressed_counts() = default;
    compressed_counts(const compressed_counts& cc)
    {
        m_bv = cc.m_bv;
        m_bv_rank = cc.m_bv_rank;
        m_bv_rank.set_vector(&m_bv);
        m_counts_fb = cc.m_counts_fb;
        m_counts_f1prime = cc.m_counts_f1prime;
        m_counts_f2prime = cc.m_counts_f2prime;
        m_counts_f3prime = cc.m_counts_f3prime;
        m_counts_f4prime = cc.m_counts_f4prime;
        m_counts_f5prime = cc.m_counts_f5prime;
        m_counts_f6prime = cc.m_counts_f6prime;
        m_counts_f7prime = cc.m_counts_f7prime;
        m_counts_f8prime = cc.m_counts_f8prime;
        m_counts_f9prime = cc.m_counts_f9prime;

        m_counts_b = cc.m_counts_b;
        m_counts_f1 = cc.m_counts_f1;
        m_counts_f2 = cc.m_counts_f2;
        m_counts_f3 = cc.m_counts_f3;
        m_counts_f4 = cc.m_counts_f4;
        m_counts_f5 = cc.m_counts_f5;
        m_counts_f6 = cc.m_counts_f6;
        m_counts_f7 = cc.m_counts_f7;
        m_counts_f8 = cc.m_counts_f8;
        m_counts_f9 = cc.m_counts_f9;

        m_is_mkn = cc.m_is_mkn;
    }
    compressed_counts(compressed_counts&& cc)
    {
        m_bv = std::move(cc.m_bv);
        m_bv_rank = std::move(cc.m_bv_rank);
        m_bv_rank.set_vector(&m_bv);
        m_counts_fb = std::move(cc.m_counts_fb);
        m_counts_f1prime = std::move(cc.m_counts_f1prime);
        m_counts_f2prime = std::move(cc.m_counts_f2prime);
        m_counts_f3prime = std::move(cc.m_counts_f3prime);
        m_counts_f4prime = std::move(cc.m_counts_f4prime);
        m_counts_f5prime = std::move(cc.m_counts_f5prime);
        m_counts_f6prime = std::move(cc.m_counts_f6prime);
        m_counts_f7prime = std::move(cc.m_counts_f7prime);
        m_counts_f8prime = std::move(cc.m_counts_f8prime);
        m_counts_f9prime = std::move(cc.m_counts_f9prime);

        m_counts_b = std::move(cc.m_counts_b);
        m_counts_f1 = std::move(cc.m_counts_f1);
        m_counts_f2 = std::move(cc.m_counts_f2);
        m_counts_f3 = std::move(cc.m_counts_f3);
        m_counts_f4 = std::move(cc.m_counts_f4);
        m_counts_f5 = std::move(cc.m_counts_f5);
        m_counts_f6 = std::move(cc.m_counts_f6);
        m_counts_f7 = std::move(cc.m_counts_f7);
        m_counts_f8 = std::move(cc.m_counts_f8);
        m_counts_f9 = std::move(cc.m_counts_f9);

        m_is_mkn = cc.m_is_mkn;
    }
    compressed_counts& operator=(compressed_counts&& cc)
    {
        m_bv = std::move(cc.m_bv);
        m_bv_rank = std::move(cc.m_bv_rank);
        m_bv_rank.set_vector(&m_bv);
        m_counts_fb = std::move(cc.m_counts_fb);
        m_counts_f1prime = std::move(cc.m_counts_f1prime);
        m_counts_f2prime = std::move(cc.m_counts_f2prime);
        m_counts_f3prime = std::move(cc.m_counts_f3prime);
        m_counts_f4prime = std::move(cc.m_counts_f4prime);
        m_counts_f5prime = std::move(cc.m_counts_f5prime);
        m_counts_f6prime = std::move(cc.m_counts_f6prime);
        m_counts_f7prime = std::move(cc.m_counts_f7prime);
        m_counts_f8prime = std::move(cc.m_counts_f8prime);
        m_counts_f9prime = std::move(cc.m_counts_f9prime);

        m_counts_b = std::move(cc.m_counts_b);
        m_counts_f1 = std::move(cc.m_counts_f1);
        m_counts_f2 = std::move(cc.m_counts_f2);
        m_counts_f3 = std::move(cc.m_counts_f3);
        m_counts_f4 = std::move(cc.m_counts_f4);
        m_counts_f5 = std::move(cc.m_counts_f5);
        m_counts_f6 = std::move(cc.m_counts_f6);
        m_counts_f7 = std::move(cc.m_counts_f7);
        m_counts_f8 = std::move(cc.m_counts_f8);
        m_counts_f9 = std::move(cc.m_counts_f9);

        m_is_mkn = cc.m_is_mkn;
        return *this;
    }

    template <class t_cst>
    compressed_counts(collection& col, t_cst& cst, uint64_t max_node_depth,
        bool mkn_counts)
    {
        m_is_mkn = mkn_counts;
        if (!mkn_counts)
            initialise_kneser_ney(col, cst, max_node_depth);
        else
            initialise_modified_kneser_ney(col, cst, max_node_depth);
    }

    template <class t_cst, class t_node_type>
    uint32_t compute_contexts(t_cst& cst, t_node_type node, uint64_t& num_syms)
    {
        static std::vector<typename t_cst::csa_type::wavelet_tree_type::value_type> preceding_syms(
            cst.csa.sigma);
        static std::vector<typename t_cst::csa_type::wavelet_tree_type::size_type> left(cst.csa.sigma);
        static std::vector<typename t_cst::csa_type::wavelet_tree_type::size_type> right(
            cst.csa.sigma);
        auto lb = cst.lb(node);
        auto rb = cst.rb(node);
        num_syms = 0;
        sdsl::interval_symbols(cst.csa.wavelet_tree, lb, rb + 1, num_syms,
            preceding_syms, left, right);
        auto total_contexts = 0;
        auto node_depth = cst.depth(node);
        for (size_t i = 0; i < num_syms; i++) {
            auto new_lb = cst.csa.C[cst.csa.char2comp[preceding_syms[i]]] + left[i];
            auto new_rb = cst.csa.C[cst.csa.char2comp[preceding_syms[i]]] + right[i] - 1;
            if (new_lb == new_rb) {
                total_contexts++;
            }
            else {
                auto new_node = cst.node(new_lb, new_rb);
                if (cst.is_leaf(new_node) || cst.depth(new_node) != node_depth + 1) {
                    total_contexts++;
                }
                else {
                    auto deg = cst.degree(new_node);
                    total_contexts += deg;
                }
            }
        }
        return total_contexts;
    }

    template <class t_cst, class t_node_type>
    uint32_t compute_contexts_mkn(t_cst& cst, t_node_type node,
                                  uint64_t& num_syms, uint64_t& f1prime,
                                  uint64_t& f2prime, uint64_t& f3prime, 
                                  uint64_t& f4prime, uint64_t& f5prime, 
                                  uint64_t& f6prime, uint64_t& f7prime, 
                                  uint64_t& f8prime, uint64_t& f9prime)

    {
        static thread_local std::vector<typename t_cst::csa_type::wavelet_tree_type::value_type> preceding_syms(
            cst.csa.sigma);
        static thread_local std::vector<typename t_cst::csa_type::wavelet_tree_type::size_type> left(
            cst.csa.sigma);
        static thread_local std::vector<typename t_cst::csa_type::wavelet_tree_type::size_type> right(
            cst.csa.sigma);

        f1prime = 0;
        f2prime = 0;
 	f3prime = 0;
        f4prime = 0;
        f5prime = 0;
        f6prime = 0;
        f7prime = 0;
        f8prime = 0;
        f9prime = 0;

        uint64_t all = 0;
        auto child = cst.select_child(node, 1);
        while (child != cst.root()) {
            auto lb = cst.lb(child);
            auto rb = cst.rb(child);

            typename t_cst::csa_type::size_type num_syms = 0;
            sdsl::interval_symbols(cst.csa.wavelet_tree, lb, rb + 1, num_syms,
                preceding_syms, left, right);
            if (num_syms == 1)
                f1prime++;
            if (num_syms == 2)
                f2prime++;
            if (num_syms == 3)
                f3prime++;
	    if (num_syms == 4)
                f4prime++;
            if (num_syms == 5)
                f5prime++;
            if (num_syms == 6)
                f6prime++;
            if (num_syms == 7)
                f7prime++;
            if (num_syms == 8)
                f8prime++;
            if (num_syms == 9)
                f9prime++;
            all++;
            child = cst.sibling(child);
        }

        /* computes fb */
        auto total_contexts = 0;
        auto node_depth = cst.depth(node);

        auto lb = cst.lb(node);
        auto rb = cst.rb(node);
        num_syms = 0;
        sdsl::interval_symbols(cst.csa.wavelet_tree, lb, rb + 1, num_syms,
            preceding_syms, left, right);

        for (size_t i = 0; i < num_syms; i++) {
            auto new_lb = cst.csa.C[cst.csa.char2comp[preceding_syms[i]]] + left[i];
            auto new_rb = cst.csa.C[cst.csa.char2comp[preceding_syms[i]]] + right[i] - 1;
            if (new_lb == new_rb) {
                total_contexts++;
            }
            else {
                auto new_node = cst.node(new_lb, new_rb);
                if (cst.is_leaf(new_node) || cst.depth(new_node) != node_depth + 1) {
                    total_contexts++;
                }
                else {
                    auto deg = cst.degree(new_node);
                    total_contexts += deg;
                }
            }
        }
        return total_contexts;
    }

    template <class t_cst>
    void initialise_kneser_ney(collection& col, t_cst& cst,
        uint64_t max_node_depth)
    {
        sdsl::bit_vector tmp_bv(cst.nodes());
        sdsl::util::set_to_value(tmp_bv, 0);
        auto tmp_buffer_counts_fb = sdsl::int_vector_buffer<32>(col.temp_file("counts_fb"), std::ios::out);
        auto tmp_buffer_counts_b = sdsl::int_vector_buffer<32>(col.temp_file("counts_fb"), std::ios::out);
        uint64_t num_syms = 0;

        auto root = cst.root();
        for (const auto& child : cst.children(root)) {
            auto itr = cst.begin(child);
            auto end = cst.end(child);

            while (itr != end) {
                auto node = *itr;
                if (itr.visit() == 2) {
                    auto node_id = cst.id(node);

                    auto str_depth = cst.depth(node);
                    if (str_depth <= max_node_depth) {
                        tmp_bv[node_id] = 1;
                        auto c = compute_contexts(cst, node, num_syms);
                        tmp_buffer_counts_fb.push_back(c);
                        tmp_buffer_counts_b.push_back(num_syms);
                    }
                }
                else {
                    /* first visit */
                    if (!cst.is_leaf(node)) {
                        auto depth = cst.depth(node);
                        if (depth > max_node_depth) {
                            itr.skip_subtree();
                        }
                    }
                }
                ++itr;
            }
        }
        m_counts_b = vector_type(tmp_buffer_counts_b);
        tmp_buffer_counts_b.close(true);
        m_counts_fb = vector_type(tmp_buffer_counts_fb);
        tmp_buffer_counts_fb.close(true);
        m_bv = bv_type(tmp_bv);
        tmp_bv.resize(0);
        m_bv_rank = rank_type(&m_bv);

        LOG(INFO) << "precomputed " << m_bv_rank(m_bv.size()) << " entries out of "
                  << m_bv.size() << " nodes";
    }

    template <class t_cst, class t_node, class t_writer>
    void precompute_subtree(t_cst& cst, t_node start, t_writer& writer, std::vector<uint64_t[9]>& child_hist, uint64_t max_depth)
    {
        for (auto& v : child_hist)
             memset(v,0,sizeof(v));

        uint64_t node_depth = 1;
        auto prev = cst.root();
        auto itr = cst.begin(start);
        auto end = cst.end(start);

        std::vector<computed_context_result> results;
        uint64_t num_syms;
        uint64_t f1prime;
        uint64_t f2prime;
        uint64_t f3prime;
        uint64_t f4prime;
        uint64_t f5prime;
        uint64_t f6prime;
        uint64_t f7prime;
        uint64_t f8prime;
        uint64_t f9prime;

        while (itr != end) {
            auto node = *itr;
            if (cst.parent(node) == prev)
                node_depth++;

            if (itr.visit() == 2) {
                node_depth--;
                auto str_depth = cst.depth(node);
                if (str_depth <= max_depth) {
                    computed_context_result res;
                    res.node_id = cst.id(node);
                    auto& f123456789 = child_hist[node_depth];
                    res.f1 = f123456789[0];
                    res.f2 = f123456789[1];
                    res.f3 = f123456789[2];
                    res.f4 = f123456789[3];
                    res.f5 = f123456789[4];
                    res.f6 = f123456789[5];
                    res.f7 = f123456789[6];
                    res.f8 = f123456789[7];
                    res.f9 = f123456789[8];

                    auto c = compute_contexts_mkn(cst, node, num_syms, f1prime, f2prime, f3prime, 
                                                                       f4prime, f5prime, f6prime, 
                                                                       f7prime, f8prime, f9prime);
                    res.fb = c;
                    res.b = num_syms;
                    res.f1prime = f1prime;
                    res.f2prime = f2prime;
                    res.f3prime = f3prime;
                    res.f4prime = f4prime;
                    res.f5prime = f5prime;
                    res.f6prime = f6prime;
                    res.f7prime = f7prime;
                    res.f8prime = f8prime;
                    res.f9prime = f9prime;

                    writer.write_result(res);
                }
                memset(child_hist[node_depth],0,sizeof(child_hist[node_depth]));
            }
            else {
                /* first visit */
                if (!cst.is_leaf(node)) {
                    if (node_depth > max_depth) {
                        itr.skip_subtree();
                    }
                }
                int count = cst.size(node);
                if (count == 1)
                    child_hist[node_depth - 1][0] += 1;
                else if (count == 2)
                    child_hist[node_depth - 1][1] += 1;
                else if (count == 3)
                    child_hist[node_depth - 1][2] += 1;
                else if (count == 4)
                    child_hist[node_depth - 1][3] += 1;
                else if (count == 5)
                    child_hist[node_depth - 1][4] += 1;
                else if (count == 6)
                    child_hist[node_depth - 1][5] += 1;
                else if (count == 7)
                    child_hist[node_depth - 1][6] += 1;
                else if (count == 8)
                    child_hist[node_depth - 1][7] += 1;
                else if (count == 9)
                    child_hist[node_depth - 1][8] += 1;

            }
            prev = node;
            ++itr;
        }
    }

    // specific MKN implementation, 2-pass
    template <class t_cst>
    void initialise_modified_kneser_ney(collection& col, t_cst& cst,
        uint64_t max_node_depth)
    {
        // children of the root we are interested in
        std::vector<typename t_cst::node_type> nodes;
        auto root = cst.root();
        for (const auto& child : cst.children(root)) {
            nodes.push_back(child);
        }

        // now we split things up based on the leafs of each subtree
        int num_threads = std::thread::hardware_concurrency();
        if(cstlm::num_cstlm_threads != 0) num_threads = cstlm::num_cstlm_threads;
        size_t leafs_per_thread = cst.size() / num_threads;
        auto itr = nodes.begin();
        auto sentinal = nodes.end();
        std::vector<std::future<counts_writer> > results;
        for (auto i = 0; i < num_threads; i++) {

            size_t cur_num_nodes = 0;
            auto end = itr;
            size_t nodes_in_cur_thread = 0;
            while (end != sentinal && cur_num_nodes < leafs_per_thread) {
                const auto& cnode = *end;
                size_t leafs_in_subtree = cst.size(cnode);
                cur_num_nodes += leafs_in_subtree;
                nodes_in_cur_thread++;
                ++end;
            }
            if (i + 1 == num_threads) // process everything
                end = sentinal;

            LOG(INFO) << "\tThread " << i << " nodes = " << nodes_in_cur_thread;

            std::vector<typename t_cst::node_type> thread_nodes(itr, end);

            results.emplace_back(
                std::async(std::launch::async, [this, i, max_node_depth, &cst, &col](std::vector<typename t_cst::node_type> nodes) -> counts_writer {
                    counts_writer w(i, col);
                    // compute stuff
                    std::vector<uint64_t[9]> child_hist(max_node_depth + 2);
                    for (const auto& node : nodes) {
                        precompute_subtree(cst, node, w, child_hist, max_node_depth);
                    }
                    return w;
                }, std::move(thread_nodes)));
            itr = end;
        }

        std::vector<counts_writer> written_counts;
        for (auto& fcnt : results) {
            written_counts.emplace_back(fcnt.get());
        }

        LOG(INFO) << "store into compressed in-memory data structures";

        {
            counts_merge_helper wh(written_counts);
            {
                auto tmp_bv = wh.get_bv(cst.nodes());
                m_bv = bv_type(tmp_bv);
                tmp_bv.resize(0);
                m_bv_rank = rank_type(&m_bv);
            }
            {
                auto counts_f1 = wh.get_counts_f1();
                m_counts_f1 = vector_type(counts_f1);
            }
            {
                auto counts_f2 = wh.get_counts_f2();
                m_counts_f2 = vector_type(counts_f2);
            }
	    {
                auto counts_f3 = wh.get_counts_f3();
                m_counts_f3 = vector_type(counts_f3);
            }
            {
                auto counts_f4 = wh.get_counts_f4();
                m_counts_f4 = vector_type(counts_f4);
            }
            {
                auto counts_f5 = wh.get_counts_f5();
                m_counts_f5 = vector_type(counts_f5);
            }
            {
                auto counts_f6 = wh.get_counts_f6();
                m_counts_f6 = vector_type(counts_f6);
            }
            {
                auto counts_f7 = wh.get_counts_f7();
                m_counts_f7 = vector_type(counts_f7);
            }
            {
                auto counts_f8 = wh.get_counts_f8();
                m_counts_f8 = vector_type(counts_f8);
            }
	    {
                auto counts_f9 = wh.get_counts_f9();
                m_counts_f9 = vector_type(counts_f9);
            }
            {
                auto counts_b = wh.get_counts_b();
                m_counts_b = vector_type(counts_b);
            }
            {
                auto counts_fb = wh.get_counts_fb();
                m_counts_fb = vector_type(counts_fb);
            }
            {
                auto counts_f1p = wh.get_counts_f1prime();
                m_counts_f1prime = vector_type(counts_f1p);
            }
            {
                auto counts_f2p = wh.get_counts_f2prime();
                m_counts_f2prime = vector_type(counts_f2p);
            }
	    {
                auto counts_f3p = wh.get_counts_f3prime();
                m_counts_f3prime = vector_type(counts_f3p);
            }
            {
                auto counts_f4p = wh.get_counts_f4prime();
                m_counts_f4prime = vector_type(counts_f4p);
            }
            {
                auto counts_f5p = wh.get_counts_f5prime();
                m_counts_f5prime = vector_type(counts_f5p);
            }
            {
                auto counts_f6p = wh.get_counts_f6prime();
                m_counts_f6prime = vector_type(counts_f6p);
            }
            {
                auto counts_f7p = wh.get_counts_f7prime();
                m_counts_f7prime = vector_type(counts_f7p);
            }
            {
                auto counts_f8p = wh.get_counts_f8prime();
                m_counts_f8prime = vector_type(counts_f8p);
            }
            {
                auto counts_f9p = wh.get_counts_f9prime();
                m_counts_f9prime = vector_type(counts_f9p);
            }

        }

        LOG(INFO) << "precomputed " << m_bv_rank(m_bv.size()) << " entries out of "
                  << m_bv.size() << " nodes";
    }

    size_type serialize(std::ostream& out, sdsl::structure_tree_node* v = NULL,
        std::string name = "") const
    {
        sdsl::structure_tree_node* child = sdsl::structure_tree::add_child(v, name, sdsl::util::class_name(*this));
        size_type written_bytes = 0;
        written_bytes += sdsl::serialize(m_bv, out, child, "bv");
        written_bytes += sdsl::serialize(m_bv_rank, out, child, "bv_rank");
        written_bytes += sdsl::serialize(m_counts_fb, out, child, "counts_fb");
        written_bytes += sdsl::serialize(m_counts_b, out, child, "counts_b");
        written_bytes += sdsl::serialize(m_counts_f1, out, child, "counts_f1");
        written_bytes += sdsl::serialize(m_counts_f2, out, child, "counts_f2");
        written_bytes += sdsl::serialize(m_counts_f3, out, child, "counts_f3");
        written_bytes += sdsl::serialize(m_counts_f4, out, child, "counts_f4");
        written_bytes += sdsl::serialize(m_counts_f5, out, child, "counts_f5");
        written_bytes += sdsl::serialize(m_counts_f6, out, child, "counts_f6");
        written_bytes += sdsl::serialize(m_counts_f7, out, child, "counts_f7");
        written_bytes += sdsl::serialize(m_counts_f8, out, child, "counts_f8");
        written_bytes += sdsl::serialize(m_counts_f9, out, child, "counts_f9");
        written_bytes += sdsl::serialize(m_counts_f1prime, out, child, "counts_f1p");
        written_bytes += sdsl::serialize(m_counts_f2prime, out, child, "counts_f2p");
        written_bytes += sdsl::serialize(m_counts_f3prime, out, child, "counts_f3p");
        written_bytes += sdsl::serialize(m_counts_f4prime, out, child, "counts_f4p");
        written_bytes += sdsl::serialize(m_counts_f5prime, out, child, "counts_f5p");
        written_bytes += sdsl::serialize(m_counts_f6prime, out, child, "counts_f6p");
        written_bytes += sdsl::serialize(m_counts_f7prime, out, child, "counts_f7p");
        written_bytes += sdsl::serialize(m_counts_f8prime, out, child, "counts_f8p");
        written_bytes += sdsl::serialize(m_counts_f9prime, out, child, "counts_f9p");

        sdsl::structure_tree::add_size(child, written_bytes);
        return written_bytes;
    }

    void load(std::istream& in)
    {
        sdsl::load(m_bv, in);
        sdsl::load(m_bv_rank, in);
        m_bv_rank.set_vector(&m_bv);
        sdsl::load(m_counts_fb, in);
        sdsl::load(m_counts_b, in);
        sdsl::load(m_counts_f1, in);
        sdsl::load(m_counts_f2, in);
        sdsl::load(m_counts_f3, in);
        sdsl::load(m_counts_f4, in);
        sdsl::load(m_counts_f5, in);
        sdsl::load(m_counts_f6, in);
        sdsl::load(m_counts_f7, in);
        sdsl::load(m_counts_f8, in);
        sdsl::load(m_counts_f9, in);

        sdsl::load(m_counts_f1prime, in);
        sdsl::load(m_counts_f2prime, in);
        sdsl::load(m_counts_f3prime, in);
        sdsl::load(m_counts_f4prime, in);
        sdsl::load(m_counts_f5prime, in);
        sdsl::load(m_counts_f6prime, in);
        sdsl::load(m_counts_f7prime, in);
        sdsl::load(m_counts_f8prime, in);
        sdsl::load(m_counts_f9prime, in);

        m_is_mkn = (m_counts_f1.size() > 0);
    }

    // FIXME: could do this a bit more efficiently, without decompressing m_bv
    // e.g., if its depth <= max_node_depth (but beware querying this for leaves)
    template <class t_cst, class t_node_type>
    bool is_precomputed(t_cst& cst, t_node_type node) const
    {
        auto id = cst.id(node);
        return m_bv[id];
    }

    template <class t_cst, class t_node_type>
    void lookup_f12(t_cst& cst, t_node_type node, uint64_t& f1,
        uint64_t& f2, uint64_t& f3, uint64_t& f4, uint64_t& f5,
        uint64_t& f6, uint64_t& f7, uint64_t& f8, uint64_t& f9) const
    {
#ifdef ENABLE_CSTLM_TIMINGS
        auto timer = lm_bench::bench(timer_type::lookup_f12);
#endif
        assert(m_is_mkn);
        auto id = cst.id(node);
        auto rank_in_vec = m_bv_rank(id);
        f1 = m_counts_f1[rank_in_vec];
        f2 = m_counts_f2[rank_in_vec];
        f3 = m_counts_f3[rank_in_vec];
        f4 = m_counts_f4[rank_in_vec];
        f5 = m_counts_f5[rank_in_vec];
        f6 = m_counts_f6[rank_in_vec];
        f7 = m_counts_f7[rank_in_vec];
        f8 = m_counts_f8[rank_in_vec];
        f9 = m_counts_f9[rank_in_vec];
    }

    template <class t_cst, class t_node_type>
    uint64_t lookup_fb(t_cst& cst, t_node_type node) const
    {
#ifdef ENABLE_CSTLM_TIMINGS
        auto timer = lm_bench::bench(timer_type::lookup_fb);
#endif
        auto id = cst.id(node);
        auto rank_in_vec = m_bv_rank(id);
        return m_counts_fb[rank_in_vec];
    }

    template <class t_cst, class t_node_type>
    void lookup_f12prime(t_cst& cst, t_node_type node, uint64_t& f1prime,
                         uint64_t& f2prime, uint64_t& f3prime,
                         uint64_t& f4prime, uint64_t& f5prime,
                         uint64_t& f6prime, uint64_t& f7prime,
                         uint64_t& f8prime, uint64_t& f9prime) const
    {
#ifdef ENABLE_CSTLM_TIMINGS
        auto timer = lm_bench::bench(timer_type::lookup_f12prime);
#endif
        assert(m_is_mkn);
        auto id = cst.id(node);
        auto rank_in_vec = m_bv_rank(id);
        f1prime = m_counts_f1prime[rank_in_vec];
        f2prime = m_counts_f2prime[rank_in_vec];
        f3prime = m_counts_f3prime[rank_in_vec];
        f4prime = m_counts_f4prime[rank_in_vec];
        f5prime = m_counts_f5prime[rank_in_vec];
        f6prime = m_counts_f6prime[rank_in_vec];
        f7prime = m_counts_f7prime[rank_in_vec];
        f8prime = m_counts_f8prime[rank_in_vec];
        f9prime = m_counts_f9prime[rank_in_vec];
    }

    template <class t_cst, class t_node_type>
    uint64_t lookup_b(t_cst& cst, t_node_type node) const
    {
#ifdef ENABLE_CSTLM_TIMINGS
        auto timer = lm_bench::bench(timer_type::lookup_b);
#endif
        auto id = cst.id(node);
        auto rank_in_vec = m_bv_rank(id);
        return m_counts_b[rank_in_vec];
    }
};
}
