#pragma once

#include "constants.hpp"
#include "collection.hpp"
#include "utils.hpp"

#include "sdsl/int_vector_mapper.hpp"
#include "sdsl/int_vector_mapped_buffer.hpp"

#include <future>

namespace cstlm {

struct raw_counts {
    typedef sdsl::int_vector<>::size_type size_type;
    raw_counts() = default;
    raw_counts(const raw_counts& cc) = default;
    raw_counts(raw_counts&& cc) = default;
    raw_counts& operator=(const raw_counts& cc) = default;
    raw_counts& operator=(raw_counts&& cc) = default;
    raw_counts(size_t ngram_count)
    {
        n1.resize(ngram_count + 1);
        n2.resize(ngram_count + 1);
        n3.resize(ngram_count + 1);
        n4.resize(ngram_count + 1);
        n5.resize(ngram_count + 1);
        n6.resize(ngram_count + 1);
        n7.resize(ngram_count + 1);
        n8.resize(ngram_count + 1);
        n9.resize(ngram_count + 1);
        n10.resize(ngram_count + 1);
        n11.resize(ngram_count + 1);

        n1_cnt.resize(ngram_count + 1);
        n2_cnt.resize(ngram_count + 1);
        n3_cnt.resize(ngram_count + 1);
        n4_cnt.resize(ngram_count + 1);
        n5_cnt.resize(ngram_count + 1);
        n6_cnt.resize(ngram_count + 1);
        n7_cnt.resize(ngram_count + 1);
        n8_cnt.resize(ngram_count + 1);
        n9_cnt.resize(ngram_count + 1);
        n10_cnt.resize(ngram_count + 1);
        n11_cnt.resize(ngram_count + 1);

        N1plus_dotdot = 0;
        N3plus_dot = 0;
        N1_dot = 0;
        N2_dot = 0;
    }
    std::vector<uint64_t> n1;
    std::vector<uint64_t> n2;
    std::vector<uint64_t> n3;
    std::vector<uint64_t> n4;
    std::vector<uint64_t> n5;
    std::vector<uint64_t> n6;
    std::vector<uint64_t> n7;
    std::vector<uint64_t> n8;
    std::vector<uint64_t> n9;
    std::vector<uint64_t> n10;
    std::vector<uint64_t> n11;

    std::vector<uint64_t> n1_cnt;
    std::vector<uint64_t> n2_cnt;
    std::vector<uint64_t> n3_cnt;
    std::vector<uint64_t> n4_cnt;
    std::vector<uint64_t> n5_cnt;
    std::vector<uint64_t> n6_cnt;
    std::vector<uint64_t> n7_cnt;
    std::vector<uint64_t> n8_cnt;
    std::vector<uint64_t> n9_cnt;
    std::vector<uint64_t> n10_cnt;
    std::vector<uint64_t> n11_cnt;

    uint64_t N1plus_dotdot;
    uint64_t N3plus_dot;
    uint64_t N1_dot;
    uint64_t N2_dot;
    size_type serialize(std::ostream& out, sdsl::structure_tree_node* v = NULL,
        std::string name = "") const
    {
        sdsl::structure_tree_node* child = sdsl::structure_tree::add_child(v, name, sdsl::util::class_name(*this));
        size_type written_bytes = 0;

        written_bytes += sdsl::write_member(N1plus_dotdot, out, child, "N1plus_dotdot");
        written_bytes += sdsl::write_member(N3plus_dot, out, child, "N3plus_dot");
        written_bytes += sdsl::write_member(N1_dot, out, child, "N1_dot");
        written_bytes += sdsl::write_member(N2_dot, out, child, "N2_dot");

        written_bytes += sdsl::serialize(n1, out, child, "n1");
        written_bytes += sdsl::serialize(n2, out, child, "n2");
        written_bytes += sdsl::serialize(n3, out, child, "n3");
        written_bytes += sdsl::serialize(n4, out, child, "n4");
        written_bytes += sdsl::serialize(n5, out, child, "n5");
        written_bytes += sdsl::serialize(n6, out, child, "n6");
        written_bytes += sdsl::serialize(n7, out, child, "n7");
        written_bytes += sdsl::serialize(n8, out, child, "n8");
        written_bytes += sdsl::serialize(n9, out, child, "n9");
        written_bytes += sdsl::serialize(n10, out, child, "n10");
        written_bytes += sdsl::serialize(n11, out, child, "n11");

        written_bytes += sdsl::serialize(n1_cnt, out, child, "n1_cnt");
        written_bytes += sdsl::serialize(n2_cnt, out, child, "n2_cnt");
        written_bytes += sdsl::serialize(n3_cnt, out, child, "n3_cnt");
        written_bytes += sdsl::serialize(n4_cnt, out, child, "n4_cnt");
        written_bytes += sdsl::serialize(n5_cnt, out, child, "n5_cnt");
        written_bytes += sdsl::serialize(n6_cnt, out, child, "n6_cnt");
        written_bytes += sdsl::serialize(n7_cnt, out, child, "n7_cnt");
        written_bytes += sdsl::serialize(n8_cnt, out, child, "n8_cnt");
        written_bytes += sdsl::serialize(n9_cnt, out, child, "n9_cnt");
        written_bytes += sdsl::serialize(n10_cnt, out, child, "n10_cnt");
        written_bytes += sdsl::serialize(n11_cnt, out, child, "n11_cnt");

        sdsl::structure_tree::add_size(child, written_bytes);

        return written_bytes;
    }

    void load(std::istream& in)
    {
        sdsl::read_member(N1plus_dotdot, in);
        sdsl::read_member(N3plus_dot, in);
        sdsl::read_member(N1_dot, in);
        sdsl::read_member(N2_dot, in);

        sdsl::load(n1, in);
        sdsl::load(n2, in);
        sdsl::load(n3, in);
        sdsl::load(n4, in);
        sdsl::load(n5, in);
        sdsl::load(n6, in);
        sdsl::load(n7, in);
        sdsl::load(n8, in);
        sdsl::load(n9, in);
        sdsl::load(n10, in);
        sdsl::load(n11, in);

        sdsl::load(n1_cnt, in);
        sdsl::load(n2_cnt, in);
        sdsl::load(n3_cnt, in);
        sdsl::load(n4_cnt, in);
        sdsl::load(n5_cnt, in);
        sdsl::load(n6_cnt, in);
        sdsl::load(n7_cnt, in);
        sdsl::load(n8_cnt, in);
        sdsl::load(n9_cnt, in);
        sdsl::load(n10_cnt, in);
        sdsl::load(n11_cnt, in);

    }

    raw_counts& operator+=(const raw_counts& other)
    {
        N1plus_dotdot += other.N1plus_dotdot;
        N3plus_dot += other.N3plus_dot;
        N1_dot += other.N1_dot;
        N2_dot += other.N2_dot;

        for (size_t i = 0; i < n1.size(); i++) {
            n1[i] += other.n1[i];
            n2[i] += other.n2[i];
            n3[i] += other.n3[i];
            n4[i] += other.n4[i];
            n5[i] += other.n5[i];
            n6[i] += other.n6[i];
            n7[i] += other.n7[i];
            n8[i] += other.n8[i];
            n9[i] += other.n9[i];
            n10[i] += other.n10[i];
            n11[i] += other.n11[i];

            n1_cnt[i] += other.n1_cnt[i];
            n2_cnt[i] += other.n2_cnt[i];
            n3_cnt[i] += other.n3_cnt[i];
            n4_cnt[i] += other.n4_cnt[i];
            n5_cnt[i] += other.n5_cnt[i];
            n6_cnt[i] += other.n6_cnt[i];
            n7_cnt[i] += other.n7_cnt[i];
            n8_cnt[i] += other.n8_cnt[i];
            n9_cnt[i] += other.n9_cnt[i];
            n10_cnt[i] += other.n10_cnt[i];
            n11_cnt[i] += other.n11_cnt[i];

        }

        return *this;
    }
};

struct precomputed_stats {
    typedef sdsl::int_vector<>::size_type size_type;
    uint64_t max_ngram_count;
    raw_counts counts;
    std::vector<double> Y;
    std::vector<double> Y_cnt;
    std::vector<double> D1;
    std::vector<double> D2;
    std::vector<double> D3;
    std::vector<double> D4;
    std::vector<double> D5;
    std::vector<double> D6;
    std::vector<double> D7;
    std::vector<double> D8;
    std::vector<double> D9;
    std::vector<double> D10;

    std::vector<double> D1_cnt;
    std::vector<double> D2_cnt;
    std::vector<double> D3_cnt;
    std::vector<double> D4_cnt;
    std::vector<double> D5_cnt;
    std::vector<double> D6_cnt;
    std::vector<double> D7_cnt;
    std::vector<double> D8_cnt;
    std::vector<double> D9_cnt;
    std::vector<double> D10_cnt;

    // FIXME: make these class or constructor template arguments
    typedef sdsl::rank_support_v<1> t_rank_bv;
    typedef sdsl::bit_vector::select_1_type t_select_bv;

    precomputed_stats() = default;

    template <class t_cst>
    precomputed_stats(collection& col, t_cst& cst, uint64_t max_ngram_len)
        : max_ngram_count(max_ngram_len)

    {
        counts = raw_counts(max_ngram_count);
        Y.resize(max_ngram_count + 1);
        Y_cnt.resize(max_ngram_count + 1);

        D1.resize(max_ngram_count + 1);
        D2.resize(max_ngram_count + 1);
        D3.resize(max_ngram_count + 1);
        D4.resize(max_ngram_count + 1);
        D5.resize(max_ngram_count + 1);
        D6.resize(max_ngram_count + 1);
        D7.resize(max_ngram_count + 1);
        D8.resize(max_ngram_count + 1);
        D9.resize(max_ngram_count + 1);
        D10.resize(max_ngram_count + 1);

        D1_cnt.resize(max_ngram_count + 1);
        D2_cnt.resize(max_ngram_count + 1);
        D3_cnt.resize(max_ngram_count + 1);
        D4_cnt.resize(max_ngram_count + 1);
        D5_cnt.resize(max_ngram_count + 1);
        D6_cnt.resize(max_ngram_count + 1);
        D7_cnt.resize(max_ngram_count + 1);
        D8_cnt.resize(max_ngram_count + 1);
        D9_cnt.resize(max_ngram_count + 1);
        D10_cnt.resize(max_ngram_count + 1);

        // compute the counts & continuation counts from the CST
        ncomputer(col, cst);

        for (auto size = 1ULL; size <= max_ngram_len; size++) {
            Y[size] = (double)counts.n1[size] / ((double)counts.n1[size] + 2 * (double)counts.n2[size]);
            if (counts.n1[size] != 0){
                D1[size] = 1 - 2 * Y[size] * (double)counts.n2[size] / (double)counts.n1[size];
                if  (D1[size] < 0)
                        D1[size] = D1[size-1];
	    }
            if (counts.n2[size] != 0){
                D2[size] = 2 - 3 * Y[size] * (double)counts.n3[size] / (double)counts.n2[size];
                if  (D2[size] < 0)
                        D2[size] = D2[size-1];
	    }
            if (counts.n3[size] != 0){
                D3[size] = 3 - 4 * Y[size] * (double)counts.n4[size] / (double)counts.n3[size];
                if  (D3[size] < 0)
                        D3[size] = D3[size-1];
	    }
	    if (counts.n4[size] != 0){
                D4[size] = 4 - 5 * Y[size] * (double)counts.n5[size] / (double)counts.n4[size];
                if  (D4[size] < 0)
                        D4[size] = D4[size-1];
	    }
            if (counts.n5[size] != 0){
                D5[size] = 5 - 6 * Y[size] * (double)counts.n6[size] / (double)counts.n5[size];
                if  (D5[size] < 0)
                        D5[size] = D5[size-1];
	    }
            if (counts.n6[size] != 0){
                D6[size] = 6 - 7 * Y[size] * (double)counts.n7[size] / (double)counts.n6[size];
                if  (D6[size] < 0)
                        D6[size] = D6[size-1];
	    }
            if (counts.n7[size] != 0){
                D7[size] = 7 - 8 * Y[size] * (double)counts.n8[size] / (double)counts.n7[size];
                if  (D7[size] < 0)
                        D7[size] = D7[size-1];
	    }
            if (counts.n8[size] != 0){
                D8[size] = 8 - 9 * Y[size] * (double)counts.n9[size] / (double)counts.n8[size];
                if  (D8[size] < 0)
                        D8[size] = D8[size-1];
	    }
            if (counts.n9[size] != 0){
                D9[size] = 9 - 10 * Y[size] * (double)counts.n10[size] / (double)counts.n9[size];
                if  (D9[size] < 0)
                        D9[size] = D9[size-1];
	    }
            if (counts.n10[size] != 0){
                D10[size] = 10 - 11 * Y[size] * (double)counts.n11[size] / (double)counts.n10[size];
                if  (D10[size] < 0)
                        D10[size] = D10[size-1];
	    }
        }

        for (auto size = 1ULL; size <= max_ngram_len; size++) {
            Y_cnt[size] = (double)counts.n1_cnt[size] / ((double)counts.n1_cnt[size] + 2 * (double)counts.n2_cnt[size]);
            if (counts.n1_cnt[size] != 0)
	    {
                D1_cnt[size] = 1 - 2 * Y_cnt[size] * (double)counts.n2_cnt[size] / (double)counts.n1_cnt[size];
		if  (D1_cnt[size] < 0)
			D1_cnt[size] = D1_cnt[size-1];
	    }
            if (counts.n2_cnt[size] != 0)
	    {
                D2_cnt[size] = 2 - 3 * Y_cnt[size] * (double)counts.n3_cnt[size] / (double)counts.n2_cnt[size];
                if  (D2_cnt[size] < 0)
                        D2_cnt[size] = D2_cnt[size-1];

	    }
            if (counts.n3_cnt[size] != 0)
	    {
                D3_cnt[size] = 3 - 4 * Y_cnt[size] * (double)counts.n4_cnt[size] / (double)counts.n3_cnt[size];
                if  (D3_cnt[size] < 0)
                        D3_cnt[size] = D3_cnt[size-1];
	    }
            if (counts.n4_cnt[size] != 0)
	    {
                D4_cnt[size] = 4 - 5 * Y_cnt[size] * (double)counts.n5_cnt[size] / (double)counts.n4_cnt[size];
                if  (D4_cnt[size] < 0)
                        D4_cnt[size] = D4_cnt[size-1];

	    }
            if (counts.n5_cnt[size] != 0)
	    {
                D5_cnt[size] = 5 - 6 * Y_cnt[size] * (double)counts.n6_cnt[size] / (double)counts.n5_cnt[size];
                if  (D5_cnt[size] < 0)
                        D5_cnt[size] = D5_cnt[size-1];

	    }
            if (counts.n6_cnt[size] != 0)
	    {
                D6_cnt[size] = 6 - 7 * Y_cnt[size] * (double)counts.n7_cnt[size] / (double)counts.n6_cnt[size];
                if  (D6_cnt[size] < 0)
                        D6_cnt[size] = D6_cnt[size-1];

	    }
            if (counts.n7_cnt[size] != 0)
	    {
                D7_cnt[size] = 7 - 8 * Y_cnt[size] * (double)counts.n8_cnt[size] / (double)counts.n7_cnt[size];
                if  (D7_cnt[size] < 0)
                        D7_cnt[size] = D7_cnt[size-1];

	    }
            if (counts.n8_cnt[size] != 0)
	    {
                D8_cnt[size] = 8 - 9 * Y_cnt[size] * (double)counts.n9_cnt[size] / (double)counts.n8_cnt[size];
                if  (D8_cnt[size] < 0)
                        D8_cnt[size] = D8_cnt[size-1];

	    }
            if (counts.n9_cnt[size] != 0)
	    {
                D9_cnt[size] = 9 - 10 * Y_cnt[size] * (double)counts.n10_cnt[size] / (double)counts.n9_cnt[size];
                if  (D9_cnt[size] < 0)
                        D9_cnt[size] = D9_cnt[size-1];

	    }
            if (counts.n10_cnt[size] != 0)
	    {
                D10_cnt[size] = 10 - 11 * Y_cnt[size] * (double)counts.n11_cnt[size] / (double)counts.n10_cnt[size];
                if  (D10_cnt[size] < 0)
                        D10_cnt[size] = D10_cnt[size-1];

	    }
        }
    }

    size_type serialize(std::ostream& out, sdsl::structure_tree_node* v = NULL,
        std::string name = "") const
    {
        sdsl::structure_tree_node* child = sdsl::structure_tree::add_child(v, name, sdsl::util::class_name(*this));
        size_type written_bytes = 0;

        written_bytes += sdsl::write_member(max_ngram_count, out, child, "max_ngram_count");

        written_bytes += sdsl::serialize(counts, out, child, "raw_counts");

        written_bytes += sdsl::serialize(Y, out, child, "Y");
        written_bytes += sdsl::serialize(Y_cnt, out, child, "Y_cnt");
        written_bytes += sdsl::serialize(D1, out, child, "D1");
        written_bytes += sdsl::serialize(D2, out, child, "D2");
        written_bytes += sdsl::serialize(D3, out, child, "D3");
        written_bytes += sdsl::serialize(D4, out, child, "D4");
        written_bytes += sdsl::serialize(D5, out, child, "D5");
        written_bytes += sdsl::serialize(D6, out, child, "D6");
        written_bytes += sdsl::serialize(D7, out, child, "D7");
        written_bytes += sdsl::serialize(D8, out, child, "D8");
        written_bytes += sdsl::serialize(D9, out, child, "D9");
        written_bytes += sdsl::serialize(D10, out, child, "D10");

        written_bytes += sdsl::serialize(D1_cnt, out, child, "D1_cnt");
        written_bytes += sdsl::serialize(D2_cnt, out, child, "D2_cnt");
        written_bytes += sdsl::serialize(D3_cnt, out, child, "D3_cnt");
        written_bytes += sdsl::serialize(D4_cnt, out, child, "D4_cnt");
        written_bytes += sdsl::serialize(D5_cnt, out, child, "D5_cnt");
        written_bytes += sdsl::serialize(D6_cnt, out, child, "D6_cnt");
        written_bytes += sdsl::serialize(D7_cnt, out, child, "D7_cnt");
        written_bytes += sdsl::serialize(D8_cnt, out, child, "D8_cnt");
        written_bytes += sdsl::serialize(D9_cnt, out, child, "D9_cnt");
        written_bytes += sdsl::serialize(D10_cnt, out, child, "D10_cnt");

        sdsl::structure_tree::add_size(child, written_bytes);

        return written_bytes;
    }

    void load(std::istream& in)
    {
        sdsl::read_member(max_ngram_count, in);

        sdsl::load(counts, in);

        sdsl::load(Y, in);
        sdsl::load(Y_cnt, in);
        sdsl::load(D1, in);
        sdsl::load(D2, in);
        sdsl::load(D3, in);
        sdsl::load(D4, in);
        sdsl::load(D5, in);
        sdsl::load(D6, in);
        sdsl::load(D7, in);
        sdsl::load(D8, in);
        sdsl::load(D9, in);
        sdsl::load(D10, in);

        sdsl::load(D1_cnt, in);
        sdsl::load(D2_cnt, in);
        sdsl::load(D3_cnt, in);
        sdsl::load(D4_cnt, in);
        sdsl::load(D5_cnt, in);
        sdsl::load(D6_cnt, in);
        sdsl::load(D7_cnt, in);
        sdsl::load(D8_cnt, in);
        sdsl::load(D9_cnt, in);
        sdsl::load(D10_cnt, in);
    }

    template <class t_nums>
    void display_vec(const char* name, const t_nums& nums,
        size_t ngramsize) const
    {
        LOG(INFO) << name << " = "
                  << t_nums(nums.begin() + 1,
                         nums.begin() + std::min(ngramsize + 1, nums.size()));
    }

    void print(bool ismkn, uint32_t ngramsize) const
    {
        LOG(INFO) << "------------------------------------------------";
        LOG(INFO) << "-------------PRECOMPUTED QUANTITIES-------------";
        LOG(INFO) << "-------------Based on actual counts-------------";

        display_vec("n1", counts.n1, ngramsize);
        display_vec("n2", counts.n2, ngramsize);
        display_vec("n3", counts.n3, ngramsize);
        display_vec("n4", counts.n4, ngramsize);
        display_vec("n5", counts.n5, ngramsize);
        display_vec("n6", counts.n6, ngramsize);
        display_vec("n7", counts.n7, ngramsize);
        display_vec("n8", counts.n8, ngramsize);
        display_vec("n9", counts.n9, ngramsize);
        display_vec("n10", counts.n10, ngramsize);
        display_vec("n11", counts.n11, ngramsize);

        LOG(INFO) << "------------------------------------------------";
        display_vec("Y", Y, ngramsize);
        if (ismkn) {
            display_vec("D1", D1, ngramsize);
            display_vec("D2", D2, ngramsize);
            display_vec("D3", D3, ngramsize);
            display_vec("D4", D4, ngramsize);
            display_vec("D5", D5, ngramsize);
            display_vec("D6", D6, ngramsize);
            display_vec("D7", D7, ngramsize);
            display_vec("D8", D8, ngramsize);
            display_vec("D9", D9, ngramsize);
            display_vec("D10", D10, ngramsize);
        }

        LOG(INFO) << "------------------------------------------------";
        LOG(INFO) << "-------------PRECOMPUTED QUANTITIES-------------";
        LOG(INFO) << "-------------Based on continuation counts-------";
        display_vec("n1c", counts.n1_cnt, ngramsize);
        display_vec("n2c", counts.n2_cnt, ngramsize);
        display_vec("n3c", counts.n3_cnt, ngramsize);
        display_vec("n4c", counts.n4_cnt, ngramsize);
        display_vec("n5c", counts.n5_cnt, ngramsize);
        display_vec("n6c", counts.n6_cnt, ngramsize);
        display_vec("n7c", counts.n7_cnt, ngramsize);
        display_vec("n8c", counts.n8_cnt, ngramsize);
        display_vec("n9c", counts.n9_cnt, ngramsize);
        display_vec("n10c", counts.n10_cnt, ngramsize);
        display_vec("n11c", counts.n11_cnt, ngramsize);
        LOG(INFO) << "------------------------------------------------";
        display_vec("Yc", Y_cnt, ngramsize);
        if (ismkn) {
            display_vec("D1c", D1_cnt, ngramsize);
            display_vec("D2c", D2_cnt, ngramsize);
            display_vec("D3c", D3_cnt, ngramsize);
            display_vec("D4c", D4_cnt, ngramsize);
            display_vec("D5c", D5_cnt, ngramsize);
            display_vec("D6c", D6_cnt, ngramsize);
            display_vec("D7c", D7_cnt, ngramsize);
            display_vec("D8c", D8_cnt, ngramsize);
            display_vec("D9c", D9_cnt, ngramsize);
            display_vec("D10c", D10_cnt, ngramsize);
        }
        LOG(INFO) << "------------------------------------------------";
        LOG(INFO) << "N1+(..) = " << counts.N1plus_dotdot;
        if (ismkn) {
            LOG(INFO) << "N1(.) = " << counts.N1_dot;
            LOG(INFO) << "N2(.) = " << counts.N2_dot;
            LOG(INFO) << "N3+(.) = " << counts.N3plus_dot;
        }
        LOG(INFO) << "------------------------------------------------";
        LOG(INFO) << "------------------------------------------------";
    }

private:
    template <typename t_cst>
    void ncomputer(collection& col, const t_cst& cst);

    template <typename t_cst>
    void process_subtree(const t_cst& cst, sdsl::int_vector_buffer<>& SA, t_rank_bv& sentinel_rank, t_select_bv& sentinel_select, typename t_cst::node_type cur_node, uint64_t counter, raw_counts& counts, uint64_t _max_ngram_count);
    template <class t_cst>
    typename t_cst::size_type
    distance_to_sentinel(sdsl::int_vector_buffer<>& SA,
        t_rank_bv& sentinel_rank, t_select_bv& sentinel_select,
        const t_cst& cst, const typename t_cst::node_type& node,
        const typename t_cst::size_type& offset) const
    {
        auto i = cst.lb(node);
        auto text_offset = SA[i];

        // find count (rank) of 1s in text from [0, offset]
        auto rank = sentinel_rank(text_offset + offset);
        // find the location of the next 1 in the text, this will be </S>
        auto sentinel = sentinel_select(rank + 1);
        return sentinel - text_offset;
    }
};

// optimised version
template <class t_cst>
void precomputed_stats::process_subtree(const t_cst& cst, sdsl::int_vector_buffer<>& SA, t_rank_bv& sentinel_rank, t_select_bv& sentinel_select, typename t_cst::node_type cur_node, uint64_t counter,
    raw_counts& tmp_cnts, uint64_t _max_ngram_count)
{
    static thread_local std::vector<typename t_cst::csa_type::wavelet_tree_type::value_type> preceding_syms(cst.csa.sigma);
    static thread_local std::vector<typename t_cst::csa_type::wavelet_tree_type::size_type> left(cst.csa.sigma);
    static thread_local std::vector<typename t_cst::csa_type::wavelet_tree_type::size_type> right(cst.csa.sigma);
    uint64_t num_syms;

    auto end = cst.end(cur_node);
    for (auto it = cst.begin(cur_node); it != end; ++it) {
        if (it.visit() == 1) {
            auto node = *it;
            auto parent = cst.parent(node);
            auto parent_depth = cst.depth(parent);
            // this next call is expensive for leaves, but we don't care in this
            // case
            // as the for loop below will terminate on the </S> symbol
            auto depth = (!cst.is_leaf(node)) ? cst.depth(node)
                                              : (max_ngram_count + 12345);
            auto freq = cst.size(node);
            assert(parent_depth < max_ngram_count);

            uint64_t max_n = 0;
            bool last_is_sentinel = false;
            if (counter == UNKNOWN_SYM || counter == PAT_END_SYM) {
                // only need to consider one symbol for UNK, <S>, </S> edges
                max_n = 1;
            }
            else {
                // need to consider several symbols -- minimum of
                // 1) edge length; 2) threshold; 3) reaching the </S> token
                auto distance = distance_to_sentinel(SA, sentinel_rank, sentinel_select, cst, node, parent_depth) + 1;
                max_n = std::min(max_ngram_count, depth);
                if (distance <= max_n) {
                    max_n = distance;
                    last_is_sentinel = true;
                }
            }

            // update continuation counts
            uint64_t n1plus_back = 0ULL;
            if (counter == PAT_START_SYM || freq == 1) {
                // special case where the pattern starts with <s>: actual count is
                // used
                // also when freq = 1 the pattern can only be preceeded by one
                // symbol
                n1plus_back = freq;
            }
            else {
                // no need to adjust for EOS symbol, as this only happens when
                // symbol = <S>
                auto lb = cst.lb(node);
                auto rb = cst.rb(node);
                num_syms = 0;
                sdsl::interval_symbols(cst.csa.wavelet_tree, lb, rb + 1, num_syms, preceding_syms, left, right);
                n1plus_back = num_syms;
            }

            for (auto n = parent_depth + 1; n <= max_n; ++n) {
                uint64_t symbol = NUM_SPECIAL_SYMS;
                if (n == 1)
                    symbol = counter;
                else if (n == max_n && last_is_sentinel)
                    symbol = PAT_END_SYM;

                // update frequency counts
                switch (freq) {
                case 1:
                    tmp_cnts.n1[n] += 1;
                    if (n == 1)
                        tmp_cnts.N1_dot++;
                    break;
                case 2:
                    tmp_cnts.n2[n] += 1;
                    if (n == 1)
                        tmp_cnts.N2_dot++;
                    break;
                case 3:
                    tmp_cnts.n3[n] += 1;
                    break;
                case 4:
                    tmp_cnts.n4[n] += 1;
                    break;
                case 5:
                    tmp_cnts.n5[n] += 1;
                    break;
                case 6:
                    tmp_cnts.n6[n] += 1;
                    break;
                case 7:
                    tmp_cnts.n7[n] += 1;
                    break;
                case 8:
                    tmp_cnts.n8[n] += 1;
                    break;
                case 9:
                    tmp_cnts.n9[n] += 1;
                    break;
                case 10:
                    tmp_cnts.n10[n] += 1;
                    break;
                case 11:
                    tmp_cnts.n11[n] += 1;
                    break;

                }

                if (n == 2)
                    tmp_cnts.N1plus_dotdot++;
                if (freq >= 3 && n == 1)
                    tmp_cnts.N3plus_dot++;

                switch (n1plus_back) {
                case 1:
                    tmp_cnts.n1_cnt[n] += 1;
                    break;
                case 2:
                    tmp_cnts.n2_cnt[n] += 1;
                    break;
                case 3:
                    tmp_cnts.n3_cnt[n] += 1;
                    break;
                case 4:
                    tmp_cnts.n4_cnt[n] += 1;
                    break;
                case 5:
                    tmp_cnts.n5_cnt[n] += 1;
                    break;
                case 6:
                    tmp_cnts.n6_cnt[n] += 1;
                    break;
                case 7:
                    tmp_cnts.n7_cnt[n] += 1;
                    break;
                case 8:
                    tmp_cnts.n8_cnt[n] += 1;
                    break;
                case 9:
                    tmp_cnts.n9_cnt[n] += 1;
                    break;
                case 10:
                    tmp_cnts.n10_cnt[n] += 1;
                    break;
                case 11:
                    tmp_cnts.n11_cnt[n] += 1;
                    break;
                }

                // can skip subtree if we know the EOS symbol is coming next

                if (counter == UNKNOWN_SYM || counter == PAT_END_SYM || symbol == PAT_END_SYM) {
                    // std::cerr << "\tquit 1\n";
                    it.skip_subtree();
                    break;
                }
            }

            if (depth >= _max_ngram_count) {
                // std::cerr << "\tquit 2\n";
                it.skip_subtree();
            }
        }
    }
}

// optimised version
template <class t_cst>
void precomputed_stats::ncomputer(collection& col, const t_cst& cst)
{
    // load up text and store in a bitvector for locating sentinel
    // symbols
    sdsl::bit_vector sentinel_bv;
    {
        sdsl::int_vector_buffer<t_cst::csa_type::alphabet_category::WIDTH> TEXT(col.file_map[KEY_TEXT]);
        sentinel_bv.resize(TEXT.size());
        sdsl::util::set_to_value(sentinel_bv, 0);
        for (uint64_t i = 0; i < TEXT.size(); ++i) {
            auto symbol = TEXT[i];
            if (symbol < NUM_SPECIAL_SYMS && symbol != UNKNOWN_SYM && symbol != PAT_START_SYM)
                sentinel_bv[i] = 1;
        }
    }
    t_rank_bv sentinel_rank(&sentinel_bv);
    t_select_bv sentinel_select(&sentinel_bv);

    /* load SA to speed up edge call */

    // need to visit subtree corresponding to:
    //      <S> -- PAT_START_SYM    (4)
    //      UNK -- UNKNOWN_SYM      (3)
    //      and all others >= NUM_SPECIAL_SYMS (6)

    // (1) handle all the special cases first
    uint64_t counter = 0; // counter = first symbol on child edge
    std::vector<std::pair<uint64_t, typename t_cst::node_type> > nodes;
    {
        sdsl::int_vector_buffer<> SA(col.file_map[KEY_SA]);
        for (auto child : cst.children(cst.root())) {
            if(counter != EOF_SYM && counter != EOS_SYM) {
                nodes.emplace_back(counter, child);
            }
            ++counter;
        }
    }

    // (2) parallelize the rest

    // (2a) randomize to get even thread distribution
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(nodes.begin(), nodes.end(), g);

    // (2b) split up into chunks
    int num_threads = std::thread::hardware_concurrency();
    if(cstlm::num_cstlm_threads != 0) num_threads = cstlm::num_cstlm_threads;
    size_t nodes_per_thread = nodes.size() / num_threads;
    auto itr = nodes.begin();
    std::vector<std::future<raw_counts> > results;
    for (auto i = 0; i < num_threads; i++) {
        auto end = itr + nodes_per_thread;
        if (i + 1 == num_threads)
            end = nodes.end();

        std::vector<std::pair<uint64_t, typename t_cst::node_type> > thread_nodes(itr, end);

        results.emplace_back(
            std::async(std::launch::async, [this, &cst, &col, &sentinel_rank, &sentinel_select](std::vector<std::pair<uint64_t, typename t_cst::node_type> > nodes) -> raw_counts {
                // sort the nodes by id
                std::sort(nodes.begin(), nodes.end());
                // compute stuff
                raw_counts local_count(this->max_ngram_count);
                sdsl::int_vector_buffer<> SA(col.file_map[KEY_SA]);
                for (const auto& np : nodes) {
                    auto counter = np.first;
                    const auto& node = np.second;
                    process_subtree(cst, SA, sentinel_rank, sentinel_select, node, counter, local_count, this->max_ngram_count);
                }
                return local_count;
            }, std::move(thread_nodes)));
        itr = end;
    }

    for (auto& fcnt : results) {
        auto cnt = fcnt.get();
        counts += cnt;
    }
}
}
