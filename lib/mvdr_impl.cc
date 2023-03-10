/* -*- c++ -*- */
/*
 * Copyright 2023 Kepeng Luan.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "matlab/matStruct.h"
#include "mvdr_impl.h"
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
    //1. get input data vector
    ms_to_process_= floor(noutput_items*sizeof(input_type)/(double)sampling_frequency_/1000);
    std::vector<const input_type*> in;
    auto out = static_cast<output_type*>(output_items[0]);
    for (int in_index = 0; in_index < num_inputs_; ++in_index) {
        auto temp_in = static_cast<const input_type*>(input_items[in_index]);
        in.push_back(temp_in);
    }
    //2. read mat files
    std::vector<matlab_matRead> mat_file;
    std::string struct_name="trackResults";
    for (int matFileName_index = 1; matFileName_index <=num_inputs_ ; ++matFileName_index) {
        std::string temp_fileName="../trackingResults"+std::to_string(matFileName_index)+".mat";
        matlab_matRead temp_read(temp_fileName,struct_name);
        mat_file.push_back(temp_read);
    }
    std::vector<matStruct> mat_struct(num_inputs_);
    mat_struct[0].sync_index_=0;
    mat_struct[0].start_sample_=mat_file[0].getAbsoluteSample(0,target_prn_);
    mat_struct[0].phase_mat_=mat_file[0].getCarrierPhase(0,target_prn_,ms_to_process_);
    mat_struct[0].differential_phase_=arma::zeros(1,ms_to_process_);
    //3. sync and get differential phase
    for (int i = 1; i < num_inputs_; ++i) {
        int temp_syncIndex=mat_file[0].calculate_xcor(mat_file[i],target_prn_);
        double temp_startSample=mat_file[i].getAbsoluteSample(temp_syncIndex,target_prn_);
        arma::mat temp_phase=mat_file[i].getCarrierPhase(temp_syncIndex,target_prn_,ms_to_process_);
        arma::mat temp_diffPhase=temp_phase-mat_struct[0].differential_phase_;
        for (int mod_index = 0; mod_index <(int) temp_diffPhase.size(); ++mod_index) {
            double mod_value= fmod(temp_diffPhase(0,mod_index),2*pi);
            if (mod_value<0)
                mod_value+=2*pi;
            temp_diffPhase(0,mod_index)=mod_value;
        }
        double temp_diffPh_peak=arma::mean(arma::mean(temp_diffPhase,1));
        mat_struct[i].sync_index_=temp_syncIndex;
        mat_struct[i].start_sample_=temp_startSample;
        mat_struct[i].phase_mat_=temp_phase;
        mat_struct[i].differential_phase_=temp_diffPhase;
        mat_struct[i].differential_PhasePeak_=temp_diffPh_peak;
    }
    //4. get steering vector
    arma::cx_vec steering_vector(num_inputs_);
    for (int vector_index = 0; vector_index < num_inputs_; ++vector_index) {
        steering_vector(vector_index)=
            std::complex<double>(std::cos(mat_struct[vector_index].differential_PhasePeak_),
                                 -std::sin(mat_struct[vector_index].differential_PhasePeak_));
    }
    //5. get matrix w C ns
    int size_w=num_inputs_*taps_;
    arma::cx_vec C=arma::zeros<arma::cx_vec>(size_w-num_inputs_);
    C=arma::join_vert(steering_vector,C);
    int Ns=(int)sampling_frequency_/1000-taps_;
    for (int i = 0; i < noutput_items; ++i) {
        out[i]=in.at(0)[i]+in.at(1)[i];
    }

    consume_each(noutput_items);

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace mvdr_test */
} /* namespace gr */
