#pragma once

#include "sdsl/int_vector_buffer.hpp"
#include "collection.hpp"

namespace cstlm {

struct computed_context_result {
    uint64_t node_id;
    uint32_t f1;
    uint32_t f2;
    uint32_t f3;
    uint32_t f4;
    uint32_t f5;
    uint32_t f6;
    uint32_t f7;
    uint32_t f8;
    uint32_t f9;

    uint32_t fb;
    uint32_t b;
    uint32_t f1prime;
    uint32_t f2prime;
    uint32_t f3prime;
    uint32_t f4prime;
    uint32_t f5prime;
    uint32_t f6prime;
    uint32_t f7prime;
    uint32_t f8prime;
    uint32_t f9prime;

};

struct counts_writer {
    counts_writer(size_t id, collection& col)
        : m_id(id)
    {
        f1 = sdsl::int_vector_buffer<32>(col.temp_file("counts_f1", id), std::ios::out);
        f2 = sdsl::int_vector_buffer<32>(col.temp_file("counts_f2", id), std::ios::out);
	f3 = sdsl::int_vector_buffer<32>(col.temp_file("counts_f3", id), std::ios::out);
        f4 = sdsl::int_vector_buffer<32>(col.temp_file("counts_f4", id), std::ios::out);
        f5 = sdsl::int_vector_buffer<32>(col.temp_file("counts_f5", id), std::ios::out);
        f6 = sdsl::int_vector_buffer<32>(col.temp_file("counts_f6", id), std::ios::out);
        f7 = sdsl::int_vector_buffer<32>(col.temp_file("counts_f7", id), std::ios::out);
        f8 = sdsl::int_vector_buffer<32>(col.temp_file("counts_f8", id), std::ios::out);
        f9 = sdsl::int_vector_buffer<32>(col.temp_file("counts_f9", id), std::ios::out);

        fb = sdsl::int_vector_buffer<32>(col.temp_file("counts_fb", id), std::ios::out);
        b = sdsl::int_vector_buffer<32>(col.temp_file("counts_b", id), std::ios::out);
        f1p = sdsl::int_vector_buffer<32>(col.temp_file("counts_f1p", id), std::ios::out);
        f2p = sdsl::int_vector_buffer<32>(col.temp_file("counts_f2p", id), std::ios::out);
        f3p = sdsl::int_vector_buffer<32>(col.temp_file("counts_f3p", id), std::ios::out);
        f4p = sdsl::int_vector_buffer<32>(col.temp_file("counts_f4p", id), std::ios::out);
        f5p = sdsl::int_vector_buffer<32>(col.temp_file("counts_f5p", id), std::ios::out);
        f6p = sdsl::int_vector_buffer<32>(col.temp_file("counts_f6p", id), std::ios::out);
        f7p = sdsl::int_vector_buffer<32>(col.temp_file("counts_f7p", id), std::ios::out);
        f8p = sdsl::int_vector_buffer<32>(col.temp_file("counts_f8p", id), std::ios::out);
        f9p = sdsl::int_vector_buffer<32>(col.temp_file("counts_f9p", id), std::ios::out);

        ids = sdsl::int_vector_buffer<64>(col.temp_file("node_ids", id), std::ios::out);
    }

    void write_result(computed_context_result& res)
    {
        f1.push_back(res.f1);
        f2.push_back(res.f2);
        f3.push_back(res.f3);
        f4.push_back(res.f4);
        f5.push_back(res.f5);
        f6.push_back(res.f6);
        f7.push_back(res.f7);
        f8.push_back(res.f8);
        f9.push_back(res.f9);

        fb.push_back(res.fb);
        b.push_back(res.b);
        f1p.push_back(res.f1prime);
        f2p.push_back(res.f2prime);
        f3p.push_back(res.f3prime);
        f4p.push_back(res.f4prime);
        f5p.push_back(res.f5prime);
        f6p.push_back(res.f6prime);
        f7p.push_back(res.f7prime);
        f8p.push_back(res.f8prime);
        f9p.push_back(res.f9prime);

        ids.push_back(res.node_id);
    }

    void delete_temp_files()
    {
        f1.close(true);
        f2.close(true);
        f3.close(true);
        f4.close(true);
        f5.close(true);
        f6.close(true);
        f7.close(true);
        f8.close(true);
        f9.close(true);

        fb.close(true);
        b.close(true);
        f1p.close(true);
        f2p.close(true);
        f3p.close(true);
        f4p.close(true);
        f5p.close(true);
        f6p.close(true);
        f7p.close(true);
        f8p.close(true);
        f9p.close(true);

        ids.close(true);
    }
    size_t m_id;
    sdsl::int_vector_buffer<32> f1;
    sdsl::int_vector_buffer<32> f2;
    sdsl::int_vector_buffer<32> f3;
    sdsl::int_vector_buffer<32> f4;
    sdsl::int_vector_buffer<32> f5;
    sdsl::int_vector_buffer<32> f6;
    sdsl::int_vector_buffer<32> f7;
    sdsl::int_vector_buffer<32> f8;
    sdsl::int_vector_buffer<32> f9;

    sdsl::int_vector_buffer<32> fb;
    sdsl::int_vector_buffer<32> b;
    sdsl::int_vector_buffer<32> f1p;
    sdsl::int_vector_buffer<32> f2p;
    sdsl::int_vector_buffer<32> f3p;
    sdsl::int_vector_buffer<32> f4p;
    sdsl::int_vector_buffer<32> f5p;
    sdsl::int_vector_buffer<32> f6p;
    sdsl::int_vector_buffer<32> f7p;
    sdsl::int_vector_buffer<32> f8p;
    sdsl::int_vector_buffer<32> f9p;

    sdsl::int_vector_buffer<64> ids;
};

struct dummy_container {
    using size_type = uint64_t;
    using value_type = uint32_t;
    std::vector<sdsl::int_vector_buffer<32>*> bufs;
    size_type m_size = 0;
    dummy_container() = default;
    dummy_container(std::vector<sdsl::int_vector_buffer<32>*> b)
        : bufs(b)
    {
        m_size = 0;
        for (auto& buffer : bufs) {
            m_size += buffer->size();
        }
    }
    size_type size() const
    {
        return m_size;
    }

    value_type operator[](size_type idx) const
    {
        size_type cumsum = 0;
        for (size_t i = 0; i < bufs.size(); i++) {
            if (cumsum + bufs[i]->size() > idx) {
                size_t relidx = idx - cumsum;
                return (*bufs[i])[relidx];
            }
            cumsum += bufs[i]->size();
        }
        return 0;
    }
};

struct counts_merge_helper {
    counts_merge_helper(std::vector<counts_writer>& cws)
        : writers(cws)
    {
    }
    ~counts_merge_helper()
    {
        for (auto& w : writers) {
            w.delete_temp_files();
        }
    }

    sdsl::bit_vector get_bv(size_t n)
    {
        sdsl::bit_vector bv(n);
        for (auto& w : writers) {
            for (const auto& id : w.ids) {
                bv[id] = 1;
            }
        }
        return bv;
    }

    dummy_container get_counts_f1()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f1);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_f2()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f2);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_f3()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f3);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_f4()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f4);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_f5()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f5);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_f6()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f6);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_f7()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f7);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_f8()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f8);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_f9()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f9);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_fb()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.fb);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_b()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.b);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_f1prime()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f1p);
        }
        return dummy_container(bufs);
    }

    dummy_container get_counts_f2prime()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f2p);
        }
        return dummy_container(bufs);
    }
    dummy_container get_counts_f3prime()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f3p);
        }
        return dummy_container(bufs);
    }
    dummy_container get_counts_f4prime()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f4p);
        }
        return dummy_container(bufs);
    }
    dummy_container get_counts_f5prime()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f5p);
        }
        return dummy_container(bufs);
    }
    dummy_container get_counts_f6prime()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f6p);
        }
        return dummy_container(bufs);
    }
    dummy_container get_counts_f7prime()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f7p);
        }
        return dummy_container(bufs);
    }
    dummy_container get_counts_f8prime()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f8p);
        }
        return dummy_container(bufs);
    }
    dummy_container get_counts_f9prime()
    {
        std::vector<sdsl::int_vector_buffer<32>*> bufs;
        for (auto& w : writers) {
            bufs.push_back(&w.f9p);
        }
        return dummy_container(bufs);
    }

private:
    std::vector<counts_writer>& writers;
};
}
