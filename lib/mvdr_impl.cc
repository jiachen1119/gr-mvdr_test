/* -*- c++ -*- */
/*
 * Copyright 2023 Kepeng Luan.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "matStruct.h"
#include "mvdr_impl.h"
#include "source_struct.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace mvdr_test {

using input_type = float;
using output_type = float;
mvdr::sptr mvdr::make(int num_inputs,
                      float sampling_frequency,
                      int taps,
                      int target_prn,
                      int ms_to_process)
{ return gnuradio::make_block_sptr<mvdr_impl>(num_inputs,
                                                sampling_frequency,
                                                taps,
                                                target_prn,
                                                ms_to_process); }


/*
 * The private constructor
 */
mvdr_impl::mvdr_impl(int num_inputs,
                     float sampling_frequency,
                     int taps,
                     int target_prn,
                     int ms_to_process)
    : gr::block("mvdr",
                gr::io_signature::make(
                    1 , 4 , sizeof(input_type)),
                gr::io_signature::make(
                    1 , 1 , sizeof(output_type))),
      num_inputs_(num_inputs),
      sampling_frequency_(sampling_frequency),
      taps_(taps),
      target_prn_(target_prn),
      ms_to_process_(ms_to_process)
{
}

/*
 * Our virtual destructor.
 */
mvdr_impl::~mvdr_impl() = default;

void mvdr_impl::forecast(int noutput_items, gr_vector_int& ninput_items_required)
{
    for (int source_index = 0; source_index < num_inputs_; ++source_index) {
        ninput_items_required[source_index]=noutput_items;
    }
}

int mvdr_impl::general_work(int noutput_items,
                            gr_vector_int& ninput_items,
                            gr_vector_const_void_star& input_items,
                            gr_vector_void_star& output_items)
{
    std::vector<const input_type*> in;
    auto out = static_cast<output_type*>(output_items[0]);
    for (int in_index = 0; in_index < num_inputs_; ++in_index) {
        auto temp_in = static_cast<const input_type*>(input_items[in_index]);
        in.push_back(temp_in);
    }
    std::vector<matlab_matRead> mat_file;
    std::string struct_name="trackResults";
    for (int matFileName_index = 1; matFileName_index <=num_inputs_ ; ++matFileName_index) {
        std::string temp_fileName="../trackingResults"+std::to_string(matFileName_index)+".mat";
        matlab_matRead temp_read(temp_fileName,struct_name);
        mat_file.push_back(temp_read);
    }
    std::vector<matStruct> mat_struct(num_inputs_);
    mat_struct[0].sync_index_=1;
    for (int i = 0; i < num_inputs_; ++i) {
        mat_struct[i].sync_index_=mat_file[0].calculate_xcor(mat_file[i],target_prn_);
    }

    for (int i = 0; i < noutput_items; ++i) {
        out[i]=in.at(0)[i]+in.at(1)[i];
    }

    consume_each(noutput_items);

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace mvdr_test */
} /* namespace gr */
